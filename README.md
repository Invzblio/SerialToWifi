# SerialToWifi : OTA debugging made easy
This library is a drop-in replacement for the Serial Arduino library that manages i/o to a remote console over wifi.<br>
Simply include the SerialToWifi.h, configure your host address and port and all the calls to the Serial library will be redirected to your host via wifi. Commands like Serial.println() and Serial.readStringUntil() are all supported.<br>
The connection is initiated by your Arduino/ESP board to your host computer. This means that as long as your host's TCP port is reachable, the device will send its data over standard serial commands, wherever the board is on your local network or the Internet.<br>
To revert to the original Serial behavior, simply comment out the header file. <br>
Please read the "Options" section for potential impact of the library on performance.

# Installation
1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
2. The Library Manager will open.
3. Then search for SerialToWifi using the search bar.
4. Select the latest version and install it.
<br>
Example code is available in Sketch->Examples->SerialToWifi

# TCP Console
You need to install a TCP listener as a display console to manage the input/output from the library.
We recommend using NCat from the nmap project. Any other similar TCP listener should work fine.
If you are running Windows, a precompiled standalone version is available here: https://github.com/cyberisltd/NcatPortable
For other platforms, it can be downloaded from the nmap open source project and is available in the package binaries: https://nmap.org/download.html

Use this command line to have ncat listen on port 6767 on your host machine
```
ncat -k -l -p 6767 
```

# Library usage
Add the following to your code.
```
#include <SerialToWifi> // Comment this line to go back to the original Serial library behavior

#ifdef SERIALTOWIFI
    #define SERVER  "YOUR_HOST_IP"
    #define SERVER_PORT 6767
    SerialToWifi serialToWifi(SERVER, SERVER_PORT, TIMESTAMP|NO_RECONNECT);
    // TIMESTAMP: Displays a timestamp at the beginning of each line
    // NO_RECONNECT: Will not try to reconnect if the host is unreachable at some point. A reset is required to restart debug outputs.
#endif

void setup()
{
    startWifi();
    Serial.begin(115200);
    Serial.println("Starting");
}
```

# Options
Options for the SerialToWifi object are:<br>
<b>TIMESTAMP</b> : Displays a timestamp at the beginning of each line similar to the one in the Arduino console. This option is disabled by default.<br>
<b>NO_RECONNECT</b> : By default, the library will attempt to connect to the TCP console on each call to a Serial function. If the console is not reacheable, this can add significant delays to your program's excecution. Using the NO_RECONNECT option will stop this behavior and disable the sending of information if the console is not reachable. To restart debug outputs to the TCP console, a reset of the device is required.<br>
