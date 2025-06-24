##  Challenges Faced and How They Were Addressed

###  Challenge 1: Initial Setup of ESP32
- We faced difficulty in identifying correct port and required libraries for ESP32.  
- We researched about it and then installed the correct ESP32 drivers (CP210x_Universal_Windows_Driver) and IRremoteESP8266 library.

---

###  Challenge 2: Verifying IR Transmission
- We did not have access to any IR controlled device initially. So, it was impossible to tell if the IR LED was transmitting with the naked eye. It was hard to test.  
- We learnt that we could see the IR LED through a phone camera. It can detect the faint flash of IR light and that helped us confirm.

---

###  Challenge 3: Unavailability of Buck Converter in the Lab
- We initially planned to use 7.4V battery pack (using two 3.7V Lithium ion batteries) and a buck converter.  
- However, there was no availability of a buck converter (LM2596) in the lab, despite multiple requests.  
- We were forced to use our laptop as a power source (as shown in the video).
