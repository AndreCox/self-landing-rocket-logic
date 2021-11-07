#include <unity.h>

#include "../configuration.h"

void test_led_pin_number(void) {
  TEST_ASSERT_EQUAL(13, LEDPin);
}
