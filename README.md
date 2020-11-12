# LKG-Uff-Cross
A DMX-to-SK6812 Controller written in C++ using Arduino

## Features
- 6 Effects,
- Multi-color (default: 4-color) support,
- 8-channel controlability (even with the specific dirt cheap and not user friendly dmx-panal we use)

## To set up:
### Hardware:
#### You need:
ESP-32 (a version you can program with the Arduino IDE ensures compatibility, should be possible to archieve by other means, but then you wouldn't be here)
MAX-485

#### Setup:
1. Connect the DMX D+ / D- / Ground to the MAX-485 A / B / Ground (if D+ / D- to A / B get mixed up try the other way around)
2. Bridge !RX_enable and TX_enable from the MAX-485 to Ground
3. Connect the RX to pin 16 (UART-2 RX) on the ESP-32
4. Connect a pin (4 by default) of the ESP-32 to the first SK-6812 DI
5. Connect everythings corresponding Ground and 5V to a powersupply (some ESP-32 Dev Boards can use USB-power, others need 3.3V - adapt as required)

### Software:
1. Follow instructions to setup the Arduino IDE for an ESP-32:
https://github.com/espressif/arduino-esp32
2. Clone the project in a folder named "esp_32_dmx_sk"
3. Open the cloned project as a Arduino project (esp_32_dmx_sk.ino is the main project file)
4. Adapt as you wish!
5. Flash to ESP-32 (if you are new: do not forget to hold the BOOT button, if your board has one)

## Thanks to
uses in adapted form

https://github.com/luksal/ESP32-DMX-RX

https://github.com/gitpeut/SK6812-RGBW-ESP32

https://github.com/ratkins/RGBConverter
