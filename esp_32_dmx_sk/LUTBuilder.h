class LUTBuilder {
  public:
  LUTBuilder(int maxsize) {
    _lut = int[maxsize];
    _length = maxsize
  }

  void addDescriptor(int[] descriptor, int start = 0, int end = -1) {
    if (end == -1) {
      end = descriptor.length;
    }
    if (end > _length) {
      end = _length;
    }
    for (int i = start; i < end; i++) {
      _lut[i] = descriptor[i];
    }
  }
  
  void addDescriptor(int (*descriptor)(int), int start = 0, int end) {
    if (end > _length) {
      end = _length;
    }
    for (int i = start; i < end; i++) {
      _lut[i] = descriptor(i);
    }
  }
  
  void addDescriptor(LUTBuilder * descriptor, int start = 0, int end = -1) {
    if (end == -1) {
      end = descriptor.length;
    }
    if (end > _length) {
      end = _length;
    }
    for (int i = start; i < end; i++) {
      _lut[i] = descriptor[i];
    }
  }
  
  LUTBuilder operator+(LUTBuilder other) {
    addDescriptor(other, 0, other.length);
  }
  
  int operator[](int i) {
    return i < _length ? _lut[i] : 0;
  }
  
  int[] asArray() {
    return _lut;
  }
  int _length;
  int[] _lut;
};
