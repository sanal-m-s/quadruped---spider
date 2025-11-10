#include "FlexiTimer2.h"

unsigned long FlexiTimer2::time_units;
void (*FlexiTimer2::func)();
volatile unsigned long FlexiTimer2::count;
volatile char FlexiTimer2::overflowing;

#if defined(ESP32)
Ticker timerTicker;
unsigned long timerInterval = 0;
#endif

void FlexiTimer2::set(unsigned long ms, void (*f)()) {
    FlexiTimer2::set(ms, 0.001, f);
}

void FlexiTimer2::set(unsigned long units, double resolution, void (*f)()) {
  if (units == 0)
    time_units = 1;
  else
    time_units = units;
    
  func = f;

#if defined(ESP32)
  timerInterval = (unsigned long)(resolution * 1000000); // Convert to microseconds
#endif
}

void FlexiTimer2::start() {
  count = 0;
  overflowing = 0;
  
#if defined(ESP32)
  timerTicker.attach_ms(timerInterval / 1000, []() {
    FlexiTimer2::_overflow();
  });
#endif
}

void FlexiTimer2::stop() {
#if defined(ESP32)
  timerTicker.detach();
#endif
}

void FlexiTimer2::_overflow() {
  count += 1;
  
  if (count >= time_units && !overflowing) {
    overflowing = 1;
    count = count - time_units;
    (*func)();
    overflowing = 0;
  }
}