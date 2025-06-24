# IR-Blaster-using-Voice-Control

As part of our Tinkering course, we built an **IR blaster controlled via a voice assistant**. The objective was to use an **ESP32-WROOM-32** microcontroller to send IR signals that could operate a set-top box. We chose the ESP32-WROOM-32 as it was readily available in the lab and well-suited for general-purpose IoT applications.

#### System Overview:

We used **Google Assistant** through an Android app called **HTTP Shortcuts**. This app allowed us to create a custom voice command which, when triggered, would send an HTTP **GET** request to the ESP32 server. The request looked like this:

```
GET /sendir HTTP/1.1
```

Here, `GET` is the HTTP method, `/sendir` is the endpoint, and `HTTP/1.1` is the version.

The ESP32 handled this request via the following line of code:

```cpp
server.on("/sendir", handleSendIR);
```

This would invoke the `handleSendIR` function, which transmitted the corresponding IR signal.

#### Communication Details:

* The ESP32 was configured to act as a server on **port 80**, the default HTTP port.
* Once the ESP32 received the GET request, it responded with:

  ```
  HTTP/1.1 200 OK
  ```

  indicating a successful request.

Because HTTP is **stateless**, each interaction is independent. A new connection is established each time a command is sent, similar to hanging up and redialing a phone call.

#### IR Transmission:

For IR transmission, we used an **IR LED connected to GPIO2** of the ESP32. Since our set-top box didn’t support standard hexadecimal IR codes (unlike common TVs), we had to work with **raw IR values**. These raw values defined microsecond-long "on" and "off" pulses.

The transmission code was:

```cpp
irsend.sendRaw(powerToggleSignal, 35, 38);
```

* `powerToggleSignal`: array containing the raw pulse durations.
* `35`: number of entries in the array.
* `38`: frequency in kHz (typical for most IR remotes).

The **last entry** in the raw array is a large "off" duration, which serves as a **termination pulse** to prevent unintended toggling.
