/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:46:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/11 22:31:39 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

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
	datetime_t	alarm_pattern;

	stdio_init_all();

	if (cyw43_arch_init())
		while (1)
			printf("Error initializing cyw43, I'm hanging myself!\n");

	cyw43_arch_gpio_put(ON_BOARD_LED, 1);
	on_board_led_status = 1;

	drip_io_init();


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
	int	result = cyw43_arch_wifi_connect_timeout_ms(DRIP_WIFI_SSID,
			DRIP_WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK,
			DRIP_WIFI_CONNECT_TIMEOUT_MS);
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

	//hard_assert(drip_wifi_set_ip4_addr());
	drip_wifi_set_ip4_addr();

	while (1)
	{
		cyw43_arch_poll();

/*
void cyw43_arch_wait_for_work_until (absolute_time_t until)
Sleep until there is cyw43_driver work to be done.
*/


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
	}
	cyw43_arch_deinit();
}
//		char		time_str[256];
//
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
