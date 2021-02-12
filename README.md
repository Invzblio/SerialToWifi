# SerialToWifi : OTA debugging made easy
This library is a drop-in replacement for the Serial Arduino library that manages i/o to/from a remote console over wifi.

# Installation
1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
2. The Library Manager will open.
3. Then search for SerialToWifi using the search bar.
4. Select the latest version and install it.

# TCP Console
You need to install a TCP listener as a display console to manage the input/output from the library.
We recommend using NCat from the nmap project.

# Usage
Add the following to your code.
```
#include <SerialToWifi> // Comment this line to go back to the original Serial library behavior

#ifdef SERIALTOWIFI
    #define SERVER  "10.0.0.101"
    #define SERVER_PORT 6767
    SerialToWifi serialToWifi(SERVER, SERVER_PORT, TIMESTAMP|NO_RECONNECT);
    #define Serial serialToWifi       
#endif

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting");
    
    
}
```

# Options
Options for the SerialToWifi object are:<br>
<b>TIMESTAMP</b> : Displays a timestamp at the beginning of each line similar to the one in the Arduino console. This option is disabled by default.<br>
<b>NO_RECONNECT</b> : By default, the library will attempt to connect to the TCP console on each call to a Serial function. If the console is not reacheable, this can add significant delays to your program's excecution. Using the NO_RECONNECT option will stop this behavior and disable the sending of information if the console is not reachable. To restart debug outputs to the TCP console, a reset of the device is required.<br>
