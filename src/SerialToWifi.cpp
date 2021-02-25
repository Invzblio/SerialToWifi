#include <SerialToWifi.h>

// Server IP Address of server (I.E 10.0.0.100), port is the listening port on the server that will handle serial
// inputs and outputs. Options is false for non or TIMESTAMP for a line by line timestamp mimicking the Arduino Serial Monitor
SerialToWifi::SerialToWifi(const char *server, int server_port, int options)
{
    m_server_port = server_port;
    m_server = server;

    m_connected = false;
    m_show_timestamp = true;
    m_timestamp_enabled = (options & TIMESTAMP);
    m_reconnect = (options & RECONNECT);
}

// private method
void SerialToWifi::showTimeStamp()
{
    if (m_timestamp_enabled && m_show_timestamp)
    {
        char timeStamp[20];
        sprintf(timeStamp, "%02d:%02d:%02d     ", hour(), minute(), second());
        client.write(timeStamp, strlen(timeStamp));
        m_show_timestamp = false;
    }
}


SerialToWifi::~SerialToWifi()
{
    client.stop();
}

// the baud parameter is specified but ignored for compatibility with the Serial library when used as a 
// drop-in replacement
int SerialToWifi::begin(unsigned long baud)    
{
    m_connected = true;
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
        m_connected = false;
    else
        if (!client.connect(m_server, m_server_port, 1000))
            m_connected = false;

    return m_connected;
}

// Check if connection is still live and reconnect if option 
int SerialToWifi::isConnected()
{
    m_connected = client.connected();
    if (!m_connected && m_reconnect) // attempt reconnection if option is enabled
    {
       if (!client.connect(m_server, m_server_port, 250))
        m_connected = false;
    }
    return m_connected;
}


int SerialToWifi::available()
{
    if (!isConnected())
        return 0;

    return client.available();
}
int SerialToWifi::read()
{
    if (!isConnected())
        return 0;
    return client.read();
}
int SerialToWifi::peek()
{
    if (!isConnected())
        return 0;

    return client.peek();
}
void SerialToWifi::flush()
{
    if (isConnected())
        client.flush();

}

void SerialToWifi::stop()
{
    client.stop();
}

size_t SerialToWifi::write(const uint8_t *buffer, size_t size)
{
    if (m_show_timestamp) // if this is a new line, check if the connection is alive (we don't want to check multiple times per lines)
    {
        m_connected = isConnected();
        if (m_connected)
            showTimeStamp(); // show the timestamp if the option is enabled
    }


    if ((size==2) && (*buffer==13) && (*(buffer+1)==10)) // if this is a new line, raise the flag so a timestamp will be printed on the next call
       m_show_timestamp = true;
    else
        m_show_timestamp = false;
    
    if (!m_connected) // don't send data, we're not conected
       return 0;

    // we're good, send data to the server       
     return client.write(buffer, size);
}

size_t SerialToWifi::write(uint8_t i)
{
    return client.write(&i, 1);
}
