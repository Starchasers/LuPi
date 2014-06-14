struct SFrameBuferDescription {
  unsigned int width;
  unsigned int height;
  unsigned int vWidth;
  unsigned int vHeight;
  unsigned int pitch;
  unsigned int bitDepth;
  unsigned int x;
  unsigned int y;
  void* pointer;
  unsigned int size;
 };

typedef struct SFrameBuferDescription FrameBuferDescription;

FrameBuferDescription* InitialiseFrameBuffer(unsigned int  width,unsigned int  height, unsigned int  bitDepth);
