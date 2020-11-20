void fill_rgbw(RGBW rgbw) {
  fill_rgbw_between(rgbw, 0, LED_COUNT);
}

void fill_rgbw_between(RGBW rgbw, int start, int limit) {
  for (int i = start; i < limit; i++) {
    strip.color32(i,Color::rgbwToBits(rgbw));
  }
}

void fill_rgbw_between_wrapping(RGBW rgbw, int start, int limit) {
  if (start > limit) {
    fill_rgbw_between(rgbw, start, LED_COUNT);
    fill_rgbw_between(rgbw, 0, limit);
  } else {
    fill_rgbw_between(rgbw, start, limit); 
  }
}

/**
 * todo subpixel interpolation below 2 length becomes weird!
 */
void feathered_wraping_fill(RGBW rgbw, float start, float limit, RGBW background) {

  start = fmod(start, LED_COUNT);
  limit = fmod(limit, LED_COUNT);
  int int_start = start;
  int int_limit = limit;

  float dif = abs(start - limit);
  
  if (dif > 2) {
    fill_rgbw_between_wrapping(rgbw, int_start +1, int_limit);

    strip.color32(int_start, Color::rgbwToBits(Color::mixRgbw(background, rgbw, start - int_start)));
    strip.color32(int_limit, Color::rgbwToBits(Color::mixRgbw(rgbw, background, limit - int_limit)));
  }
}
