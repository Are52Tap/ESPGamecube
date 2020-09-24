## ESPGamecube - Gamecube Controller Protocol for ESP8266

I didn't have a logic level converter for 5V to 3.3V to communicate with a gamecube controller; instead I opted to use an ESP8266 which already had 3.3V logic, a perfect match for communicating with the ESP8266. With that I created my own Gamecube Controller communication for the ESP8266 plaform.

At this point in time, it requies the ESP8266 to run at 160Mhz, not 80Mhz. This will be speed optimized in the near feature I hope. At the moment this library only supports communicating with a GameCube controller and not a GameCube console.

If you want to make a contribution to this library, feel free to submit pull requests to this repo. I am a novice at the ESP8266.

