#include "preferences.h"
#include "utility.h"
#include "sk.h"

#include "Color.h"
#include "LUTBuilder.h"
#include "shape.h"

#if DEBUG
#define DMX_START_ADDRESS 1
#endif
#include "dmx.h"

#if USE_INFIELD_ADDRESSING
#include "inFieldAddressing.cpp"
#endif

auto strip = sk();

int start_address = DMX_START_ADDRESS;

byte r,g,b,w = 0;
byte effect, effect_argument, color_slot = 0;
double timescale = 0.0;
long t = 0;
unsigned long total_time = 0;

RGBW color_slots[COLOR_SLOT_COUNT];
byte argument_slots[COLOR_SLOT_COUNT];

double timescale_lookup(byte ts) {
  // maps ts from 0..255 to about -3.0..3.0 with a deadzone and passing through 0;
  if (ts == 0) {
    return 0.0;
  }
  if (ts < 127-T_DEADZONE_SIZE) {
    return -0.0003 * (ts+T_DEADZONE_SIZE-127) * (ts+T_DEADZONE_SIZE-127);
  }
  if (ts < 127+T_DEADZONE_SIZE) {
    return 0.0;
  }
  return 0.0003 * (ts-127-T_DEADZONE_SIZE) * (ts-127-T_DEADZONE_SIZE);
}

void (*effect_inits[])(void) = {
  shapeInit, inOutSetup
};

void setup() {
#if DEBUG
  Serial.begin(115200);
#endif
  strip.begin(LED_PIN,LED_COUNT); // pin, LED_count
  DMX::Initialize();

  int effect_inits_len = sizeof(effect_inits) / sizeof(effect_inits[0]);
  for (int i = 0; i < effect_inits_len; i++) {
    effect_inits[i]();
  }

#if USE_INFIELD_ADDRESSING
  start_address = fetchDmxStartAddress();
#endif
}

void noop() {}

void (*effects[])(void) = { // todo: fade/strobe, Directions
  full, snakes, hue_rotate, inOut, noop, noop, sparkle, noop, noop // last reserved for update_lock
};
const byte effectCount =  SIZEOF(effects);

int readcycle = 0;
int writecycle = 0;

bool lock_update = false;
byte last_raw_col_slot = 0;
byte last_raw_effect = 0;

void loop() {
  unsigned long rdiff = millis() - readcycle;
  unsigned long wdiff = millis() - writecycle;
  
  if (rdiff > POLLRATE) {
    readcycle = millis();
    
    if(DMX::HasChanged())
    {
      byte raw_col_slot = DMX::Read(start_address+7);
      byte raw_effect = DMX::Read(start_address+4);
      if (raw_effect == 255 && last_raw_effect < 255 - (255 / effectCount)) {
        lock_update ^= true; // Flip on falling edge (so the correct slot is selected when unlocking)
      }

      last_raw_effect = raw_effect;
      
      if (lock_update || raw_effect == 255) { // Keep locked also during HIGH to prevent the 255 set right after the lock

      } else {
        if (raw_col_slot == 0) // reset all color slots when col slot is low
          for (int i = 1; i < 4; i++)
            color_slots[i] = Color::getBlack();

        if (raw_col_slot != 255) {
          color_slot = SEGB(raw_col_slot, COLOR_SLOT_COUNT);
          color_slots[color_slot].r = DMX::Read(start_address);
          color_slots[color_slot].g = DMX::Read(start_address+1);
          color_slots[color_slot].b = DMX::Read(start_address+2);
          color_slots[color_slot].w = DMX::Read(start_address+3);
        }
        effect = SEGB(raw_effect, effectCount);
        timescale = timescale_lookup(DMX::Read(start_address+5));
        
        argument_slots[color_slot] = DMX::Read(start_address+6);
      }

#if DEBUG
      Serial.print("DMX update: ");
      for (int i = start_address; i <= start_address + 8; i++) {
        Serial.print(String(DMX::Read(i), HEX) + " ");
      }
      Serial.println("");
#endif
    }
    if (!DMX::IsHealthy()) {
      fill_rgbw(Color::getBlack());
    }
    strip.show();
  }
  
  if (wdiff > UPDATETIME) {
    writecycle = millis();
    t = (t + (int)(wdiff * timescale)) % T_MAX;
    if (t<0) {
      t += T_MAX;
    }
    effects[effect]();
  }
}
