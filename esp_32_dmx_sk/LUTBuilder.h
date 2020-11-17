#ifndef LUTB_H
#define LUTB_H 1

#include <deque>

class LUTBuilder {
  public:
  int start, end;
  std::deque<int> lut;

  void addDescriptor(int descriptor[], int descLen, int sstart = 0, int eend = -1) {
    if (eend == -1) eend = descLen;
    prepFor(sstart,eend);
    for (int i = start; i < end; i++)
      if (i < descLen)
        lut[i] = descriptor[i];
  }
  
  void addDescriptor(int (*descriptor)(int), int sstart = -1, int eend = -1) {
    if (sstart == -1) sstart = start;
    if (eend == -1) eend = end;
    prepFor(sstart,eend);
    for (int i = sstart; i < eend; i++) lut[i] = descriptor(i);
  }
  
  void addDescriptor(LUTBuilder * descriptor, int sstart = -1, int eend = -1) {
    if (sstart == -1) sstart = descriptor->start;
    if (eend = -1) eend = descriptor->end;
    prepFor(sstart, eend);
    for (int i = descriptor->start; i < descriptor->end; i++) lut[i] = (*descriptor)[i];
  }
  
  void addDescriptor(int descriptor, int sstart = -1, int eend = -1) {
    if (sstart == -1) sstart = start;
    if (eend = -1) eend = end;
    prepFor(sstart, eend);
    for (int i = sstart; i < eend; i++) lut[i] = descriptor;
  }
  
  LUTBuilder operator+(LUTBuilder other) {addDescriptor(&other);}
  
  int& operator [] (int i) {
    prepFor(i,i);
    return lut[i];
  }
  int operator [] (int i) const {return i < end && i > start ? lut[i] : 0;}
  int size() {
    return lut.size();
  }

  private:
  void prepFor(int sstart, int eend) {
    int enddiff = end - eend;
    if (enddiff < 0) end = eend;
    for (int i = enddiff; i < 0 ; i++) lut.push_back(0);
    
    int startdiff = start - sstart;
    if (startdiff > 0) start = sstart;
    for (int i = startdiff; i > 0; i--) lut.push_front(0);
  }
};

#endif
