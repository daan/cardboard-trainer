



class RunningAverage
{
  public:

  RunningAverage(int size = 10) : mSize(size) {
    mValues = new float[mSize];
    clear();    
  }

  ~RunningAverage() {
    delete[] mValues;
  }

  void clear() {
    for(int i=0; i< mSize; i++) {
      mValues[i] = 0.0f;
    }
  }


  float calc() {
    float a = 0;
    for(int i=0; i< mSize; i++) {
      a += mValues[i];
    }
    return a/(float)mSize;
  }

  void add(float v) {
    mValues[mPtr] = v;
    mPtr = (mPtr+1) % mSize;
  }

protected:

  int mSize;
  float* mValues;
  int  mPtr = 0;

};
  
