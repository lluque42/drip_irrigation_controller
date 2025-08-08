// For the printf, as usual
#include <stdio.h>

// For sleep_ms() and stdio_init_all()
// This is an umbrella header that includes:
/*
hardware_divider
hardware_gpio
hardware_uart
pico_runtime
pico_platform
pico_stdio
pico_time
pico_util
*/
#include "pico/stdlib.h"

int main()
{
	stdio_init_all();
	while (1)
	{
		printf("Hello world\n");
		sleep_ms(2000);

	}
}
