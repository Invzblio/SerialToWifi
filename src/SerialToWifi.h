#ifndef SERIALTOWIFI
    #define SERIALTOWIFI
    
    #include <Arduino.h>
    #include <WiFi.h>
    #include <TimeLib.h>

    // OPTIONS
    #define NO_OPTION       0
    #define TIMESTAMP       1
    #define NO_RECONNECT   2

    class SerialToWifi : public Stream
    {
        private:
            const char* m_server;
            int m_server_port;
            bool  m_connected;
            bool m_show_timestamp;
            bool m_timestamp_enabled;
            bool m_reconnect;

            void showTimeStamp();
            int isConnected();

        public:    
            WiFiClient client;    

            SerialToWifi(const char *server, int server_port, int options);
            virtual ~SerialToWifi();

            virtual int available();
            virtual int read();
            virtual int peek();
            virtual void flush();
            void stop();

            int begin(unsigned long baud);
        
            //print implementation
            virtual size_t write(uint8_t val);
            virtual size_t write(const uint8_t *buffer, size_t size);
            using Print::write; 
            

};
#endif

extern SerialToWifi serialToWifi;
#define Serial serialToWifi    
