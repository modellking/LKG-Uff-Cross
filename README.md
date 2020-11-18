# LKG-Uff-Cross
A DMX-to-SK6812 Controller written in C++ using Arduino (for the ESP-32)

## Features
- 6 Effects,
- Multi-color (default: 4-color) support,
- 8-channel controlability (even with the specific dirt cheap and not user friendly dmx-panal we use)

## To set up:
Expect about 2 days of work to set this up for a normal sized cross. We (2 men) took 2 evenings á 4 hours to solder the strip and secure the hardware. Software should be doable with in an hour
### Hardware:
#### You need:
- ESP-32 (I used the Dev-Module)
- MAX-485

#### Setup:
1. Connect the DMX D+ / D- / Ground to the MAX-485 A / B / Ground (if D+ / D- to A / B get mixed up try the other way around)
2. Bridge !RX_enable and TX_enable from the MAX-485 to Ground
3. Connect the RX to pin 16 (UART-2 RX) on the ESP-32. (To change use another UART2 RX enabled pin and edit dmx.cpp:3 later)
4. Connect a pin (4 by default) of the ESP-32 to the first SK-6812 DI (Unmodified the Code only works if the start of the strip is somewhere on the left side of the lower arm (viewed from the front))
5. Connect everythings corresponding Ground and 5V to a powersupply (some ESP-32 Dev Boards can use USB-power, others need 3.3V - adapt as required)

To identify the pins on the ESP-32 you might want to look at this: https://content.instructables.com/ORIG/F14/JLPV/JQGYDSLJ/F14JLPVJQGYDSLJ.png

### Software:
1. Download the Arduino IDE: https://www.arduino.cc/en/software (No you cannot use the online version)
2. Follow instructions to setup the Arduino IDE for an ESP-32: https://github.com/espressif/arduino-esp32
3. Download and unpack this project https://github.com/modellking/LKG-Uff-Cross/archive/main.zip (Release Folder will come)
4. Generate and download a configuration file with this tool https://modellking.github.io/LKG-Uff-Cross/setup_tool_gui.html
5. Place the configuration file in /esp_32_dmx_sk/
6. Open the cloned project as a Arduino project (esp_32_dmx_sk.ino is the main project file)
7. Adapt as/if you wish!
8. Flash to ESP-32 (if you are new: do not forget to hold the BOOT button, if your board has one)

## Thanks to
uses in adapted form

https://github.com/luksal/ESP32-DMX-RX

https://github.com/gitpeut/SK6812-RGBW-ESP32

https://github.com/ratkins/RGBConverter

## Project Background

This project serves to allow me to learn a little C++ and handling an embedded Environment (well using Arduino at least)
It might be possible to achieve the same result with an Arduino Nano or other weaker chips, but between timing issues and a deadline I was happy to jump in the ESP-32 wagon and use existing libraries to manage my interfaces. Besides: 10 Bucks is certainly not breaking the bank compared to saved development (time) costs.
