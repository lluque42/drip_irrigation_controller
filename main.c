// For the printf, as usual.
#include <stdio.h>

// For the low-level part of time/date functions.
#include "hardware/rtc.h"

// For datetime_to_str() which is not documented in my local api doxygen
#include "pico/util/datetime.h"

// Obvious
#include "hardware/gpio.h"

// So far for the on-board LED which is connected to a wifi chip gpio.
#include "pico/cyw43_arch.h"

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


#define WIFI_CONNECT_TIMEOUT_MS 10000



// For the pico_w this is the pin connected to the on-board led. It's NOT
// a microcontroller's gpio BUT a CYW43 gpio.
// For pico board the on-board led does connect to a RP-2040 gpio, the pin 25.
const uint ON_BOARD_LED = CYW43_WL_GPIO_LED_PIN;

// Th gpio for the electrovalve relay control
const uint EV_REL_CTRL = 22;
const uint LIGHTS_REL_CTRL = 21;

bool	on_board_led_status;

void	timer_alarm(void)
{
	
	printf("Wakey wakey hands off snakey, world\n");
	if (on_board_led_status)
	{
		cyw43_arch_gpio_put(ON_BOARD_LED, 0);
		on_board_led_status = 0;
		gpio_put(EV_REL_CTRL, 1);
	}
	else
	{
		cyw43_arch_gpio_put(ON_BOARD_LED, 1);
		on_board_led_status = 1;
		gpio_put(EV_REL_CTRL, 0);
	}
}

int main()
{
	datetime_t	time;
	datetime_t	alarm_pattern;
	char		time_str[256];

	stdio_init_all();

	if (cyw43_arch_init())
		while (1)
			printf("Error setting time, I'm hanging myself!\n");

	cyw43_arch_gpio_put(ON_BOARD_LED, 1);
	on_board_led_status = 1;

	gpio_init(EV_REL_CTRL);
	gpio_set_dir(EV_REL_CTRL, GPIO_OUT);
	gpio_put(EV_REL_CTRL, 0);

	gpio_init(LIGHTS_REL_CTRL);
	gpio_set_dir(LIGHTS_REL_CTRL, GPIO_OUT);
	gpio_put(LIGHTS_REL_CTRL, 0);


	time.year = 2025;
	time.month = 8;
	time.day = 8;
	time.dotw = 5;
	time.hour = 22;
	time.min = 1;
	time.sec = 0;
	rtc_init();
	if (!rtc_set_datetime(&time))
		while (1)
			printf("Error setting time, I'm hanging myself!\n");
	sleep_ms(1000);
	if (!rtc_running())
		while (1)
			printf("After setting the time the RTC is not running, I'm hanging myself!\n");


	// Values of -1 indicate don't care, i.e. no need to match.
	alarm_pattern.year = -1;
	alarm_pattern.month = -1;
	alarm_pattern.day = -1;
	alarm_pattern.dotw = -1;
	alarm_pattern.hour = -1;
	alarm_pattern.min = -1;
	alarm_pattern.sec = 0;

	//rtc_set_alarm(&alarm_pattern, timer_alarm);

	sleep_ms(5000);
	// This enables the Wi-Fi in Station mode such that connections
	// can be made to other Wi-Fi Access Points
	cyw43_arch_enable_sta_mode();

	// This connects to the wifi
	int	result = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID,
			WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, WIFI_CONNECT_TIMEOUT_MS);
	if (result != 0)
	{
		printf("Couldn't connect, error: %d\n", result);
		cyw43_arch_gpio_put(ON_BOARD_LED, 0);
		gpio_put(EV_REL_CTRL, 1);
		gpio_put(LIGHTS_REL_CTRL, 1);
		sleep_ms(1000);
		
	}
	cyw43_arch_gpio_put(ON_BOARD_LED, 1);
	gpio_put(EV_REL_CTRL, 0);
	gpio_put(LIGHTS_REL_CTRL, 0);

	ip_addr_t	addr;
	ip_addr_t	mask;
	ip_addr_t	gw;
	struct netif	*interface;

	if (!ipaddr_aton("192.168.1.250", &addr))
	{
		printf("Couldn't ipaddr_aton(addr)\n");
	}
	if (!ipaddr_aton("255.255.255.0", &mask))
	{
		printf("Couldn't ipaddr_aton(mask)\n");
	}
	if (!ipaddr_aton("192.168.1.254", &gw))
	{
		printf("Couldn't ipaddr_aton(gw)\n");
	}
	printf("%d - %d - %d\n", addr, mask, gw);
	interface = NULL;
	int	i = -1;
	while (interface == NULL)
	{
		interface = netif_get_by_index(++i);	// Assumming lots of things here who allocates, should I free?
		printf("Couldn't netif_get_by_index(%d)\n", i);
	}
	printf("The ip = %d (%s)\n", interface->ip_addr, ipaddr_ntoa(&interface->ip_addr));
	
	
	netif_set_addr(interface, &addr, &mask, &gw);



	while (1)
	{
		printf("Wakey wakey hands off snakey, world\n");
		if (on_board_led_status)
		{
			cyw43_arch_gpio_put(ON_BOARD_LED, 0);
			on_board_led_status = 0;
			gpio_put(EV_REL_CTRL, 1);
		}
		else
		{
			cyw43_arch_gpio_put(ON_BOARD_LED, 1);
			on_board_led_status = 1;
			gpio_put(EV_REL_CTRL, 0);
		}
		sleep_ms(2000);
//		if (!rtc_get_datetime(&time))
//			while (1)
//				printf("Error getting time, I'm hanging myself!\n");
//		sleep_ms(1124);
//		datetime_to_str(time_str, sizeof(256), &time);
////		printf("Hello world, the time is: %s\n", time_str);
//		printf("Hello world, the time is: %d-%d-%d-[%d]_%d:%d:%d\n",
//			time.year,
//			time.month,
//			time.day,
//			time.dotw,
//			time.hour,
//			time.min,
//			time.sec);
//		sleep_ms(1145);
//
	}
	cyw43_arch_deinit();
}
