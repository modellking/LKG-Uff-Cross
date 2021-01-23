LUTBuilder inOutLut;

void inOutSetup() {
  // bottom
  inOutLut.addDescriptor(     [](int in){return in;},sh_sum[11], sh_sum[12]-1, 0);
  inOutLut.addDescriptor(     [](int in){return in;},         0, sh_sum[0]-1, SH_off);
  inOutLut.addDescriptor(                       SHds, sh_sum[0], sh_sum[1]-1);
  inOutLut.addDescriptor([](int in){return SHds-in;}, sh_sum[1], sh_sum[2]-1, 0);

  // right
  inOutLut.addDescriptor(       [](int in){return in * SHds / SHrs;}, sh_sum[2], sh_sum[3]-1, 0);
  inOutLut.addDescriptor(                                       SHds, sh_sum[3], sh_sum[4]-1);
  inOutLut.addDescriptor([](int in){return (SHds-in) * SHds / SHrs;}, sh_sum[4], sh_sum[5]-1, 0);

  // top
  inOutLut.addDescriptor(       [](int in){return in * SHds / SHts;}, sh_sum[5], sh_sum[6]-1, 0);
  inOutLut.addDescriptor(                                       SHds, sh_sum[6], sh_sum[7]-1);
  inOutLut.addDescriptor([](int in){return (SHds-in) * SHds / SHts;}, sh_sum[7], sh_sum[8]-1, 0);

  // left
  inOutLut.addDescriptor(       [](int in){return in * SHds / SHls;}, sh_sum[8], sh_sum[9]-1, 0);
  inOutLut.addDescriptor(                                       SHds, sh_sum[9], sh_sum[10]-1);
  inOutLut.addDescriptor([](int in){return (SHds-in) * SHds / SHls;}, sh_sum[10], sh_sum[11]-1, 0);

  inOutLut.printDebug();
}

void inOut() {
  
  float argu = (argument_slots[color_slot] * LED_COUNT) / (255.0 * 1);

  float short_t = fmod((t * SHds / (64.0 * LED_COUNT)), SHds);
  float maxi = fmod(short_t + argu, SHds);
  feathered_wraping_fill(color_slots[1], inOutLut[short_t], inOutLut[maxi], color_slots[1]);
}
