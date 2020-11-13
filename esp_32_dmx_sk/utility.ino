/**
 * finds the index of the segment of a byte-value
 */
int segb(byte x, byte seg_cnt) {
   return x * seg_cnt / 256;
}
