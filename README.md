# SerialToWifi : OTA debugging made easy
This library is a drop-in replacement for the Serial Arduino library that outputs results to a remote server over wifi.

# Installation
1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
2. The Library Manager will open.
3. Then search for SerialToWifi using the search bar.
4. Select the latest version and install it.

# TCP Console
You will also need to install a TCP listener as a display console to manage the input/output from the library.
We recommend using NCat from the nmap project.

# Usage
Add the following to your code.
```
#include <SerialToWifi> // Comment this line to go back to the original Serial library

#ifdef SERIALTOWIFI
    #define SERVER  "10.0.0.101"
    #define SERVER_PORT 6767
    SerialToWifi serialToWifi(SERVER, SERVER_PORT, TIMESTAMP|NO_RECONNECT);
    #define Serial serialToWifi       
#endif

```

# Options
Options for the SerialToWifi object are:
<b>TIMESTAMP</b> : Will display a timestamp at the beginning of each line similar to the one in the Arduino console. This option is disabled by default.
NO_RECONNECT : By default, the library will attempt to connect to the TCP console on each call to a Serial function. If the console is not reacheable, this will add delays to your program's excecution. Using the NO_RECONNECT option will stop this behavior and disable the sending of information if the console is not reachable. To restart debug outputs to the console, a reset of the device will be required.
