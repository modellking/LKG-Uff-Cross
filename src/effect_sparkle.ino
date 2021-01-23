/**
 * Sparkles various Colors over a Background color. Sparkles fade over time.
 */
byte sparklePattern[LED_COUNT];
byte sparkleFades[LED_COUNT];
byte sparkleSubDivisionCounter = 0;
void sparkle() {
  if (sparkleSubDivisionCounter > abs(timescale) * 6) {
    // Add new Sparkles
    for (int i = 0; i < LED_COUNT; i++) {
      byte lastHigh = 0;
      for (int j = 0; j < COLOR_SLOT_COUNT; j++) {
        if (j == 1) continue; // Skip background
        int myValue = argument_slots[j] - random(0, 255);
        if (lastHigh < myValue) {
          sparklePattern[i] = j;
          sparkleFades[i] = 255;
          lastHigh = myValue;
        }
      }
    }
    sparkleSubDivisionCounter = 0;
  }
  
  // Print current State
  for (int i = 0; i < LED_COUNT; i++) {
    float fac = sparkleFades[i] / 255.0f;
    strip.color32(i,
      Color::rgbwToBits(
        Color::mixRgbw(
          color_slots[1],
          color_slots[sparklePattern[i]],
          fac
        )
      )
    );
    
  // Decay sparkleFades
    int attemptedSet = sparkleFades[i] - 12 * abs(timescale); // decay per ~16 ms
    sparkleFades[i] = attemptedSet < 0 ? 0 : attemptedSet;
  }
  
  // Add Subdivision
  sparkleSubDivisionCounter++;
}
