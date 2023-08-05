# ESP8266-WiFi-Client-Server-AES-Encrypted-Communication
This repository showcases a pair of ESP8266-based modules—one as a client and the other as a server. The client encrypts a message using the AES algorithm and sends it to the server, which then decrypts the message and displays the original content.

****Table of Contents****
Features
Installation
Usage
Potential Improvements
Contributing
License

<H1>Features</H1>

**Client**
AES Encryption: Securely encrypts messages using the AESLib library before sending.
WiFi Connectivity: Connects to a WiFi network and sends data to a specified server.
Regular Data Transmission: Dispatches encrypted data to the server every 5 seconds.

**Server**
AES Decryption: Uses the AESLib library to securely decrypt incoming messages.
WiFi Connectivity: Connects to a WiFi network and displays its local IP address for connectivity.
Web Server Functionality: Listens for incoming requests on port 80 at the /api endpoint.

****Installation****

**Prerequisites**
Install the Arduino IDE or PlatformIO.
Install the following libraries using the Arduino Library Manager or PlatformIO's Library Management:
AESLib
ESP8266WiFi
ESP8266WebServer

**Setup**
Clone this repository.
Navigate to the client and server directories and modify the respective configurations:

Update ssid and password with your WiFi details.
For the client, also specify the serverName with the server's address.
Upload the client code to one ESP8266 module and the server code to another ESP8266 module.

****Usage****

**Client**
After uploading, the client will:
Connect to the specified WiFi network.
Encrypt a predetermined message using the AES algorithm.
Send the encrypted data to the specified server every 5 seconds.

**Server**
Upon starting, the server will:

Connect to the specified WiFi network.
Display its IP address on the Serial monitor—this is the address the client should send data to.
Listen for incoming POST requests and decrypt received data.
Display decrypted messages on the Serial monitor.

****Potential Improvements****
Implement authentication for increased security.
Allow dynamic messages on the client side via an interface or external input.
Store, process, or act upon decrypted data on the server side.
Enhance encryption security through periodic key rotation or longer key lengths.

****Contributing****
Contributions are welcome! Please fork this repository and submit a Pull Request with your enhancements or bug fixes.

****License****
This project is open source and available under the MIT License.
