#ifndef FlexiTimer2_h
#define FlexiTimer2_h

#if defined(ESP32)
  #include <Ticker.h>
#else
  #error FlexiTimer2 library only works on ESP32 architecture
#endif

namespace FlexiTimer2 {
  extern unsigned long time_units;
  extern void (*func)();
  extern volatile unsigned long count;
  extern volatile char overflowing;
  
  void set(unsigned long ms, void (*f)());
  void set(unsigned long units, double resolution, void (*f)());
  void start();
  void stop();
  void _overflow();
}

#endif