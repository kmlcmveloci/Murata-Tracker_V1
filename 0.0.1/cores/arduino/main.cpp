/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include "wiring_private.h"

#include "stm32l0_gpio.h"




#if defined(ARDUINO_MAKEFILE)

void setup(void) { 
}

void loop(void) {
}

#endif

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Initialize C library
extern "C" void __libc_init_array(void);

void (*g_serialEventRun)(void) = NULL;

/*
 * \brief Main entry point of Arduino application
 */
int main( void )
{


  init();
  initVariant();

		// power on TCXO
//		stm32l0_gpio_pin_configure(STM32L0_GPIO_PIN_PB9, (STM32L0_GPIO_PARK_NONE | STM32L0_GPIO_PUPD_NONE | STM32L0_GPIO_OSPEED_LOW | STM32L0_GPIO_OTYPE_PUSHPULL | STM32L0_GPIO_MODE_OUTPUT));
//		stm32l0_gpio_pin_write(STM32L0_GPIO_PIN_PB9  , HIGH);	


  __libc_init_array();

  delay(1);
#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  setup();

  for (;;)
  {
    loop();
    if (g_serialEventRun) (*g_serialEventRun)();
  }

  return 0;
}
