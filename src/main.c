/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:46:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/14 13:23:27 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

bool			on_board_led_status = 0;
bool			wifi_connected = 0;
t_drip_settings *drip_settings = NULL;

void	timer_alarm(void)
{
	datetime_t	t;
	char		time_str[200];

	printf("[timer_alarm] Alarm works\n");
	if (!rtc_get_datetime(&t))
		printf("[timer_alarm] RTC not working\n");
	else
	{
		datetime_to_str(time_str, sizeof(time_str), &t);
		printf("%s\n", time_str);
	}
}

int main()
{
	datetime_t	alarm_pattern;

	stdio_init_all();
	sleep_ms(1000);
	if (cyw43_arch_init())
		printf("Error initializing cyw43\n");
	cyw43_arch_gpio_put(ON_BOARD_LED, 1);
	on_board_led_status = 1;
	drip_io_init();



	drip_settings = drip_load_settings_default();
	hard_assert(drip_settings != NULL);


	hard_assert(drip_rtc_init());	// No way this could work without a clock

	// Values of -1 indicate don't care, i.e. no need to match.
	hard_assert (drip_rtc_str2datetime(	"-1:-1:-1:-1:-1:-1:0",
											&alarm_pattern, 1));
	rtc_set_alarm(&alarm_pattern, timer_alarm);

	// This function enables wifi station mode (to connect to other APs),
	// connects to the wifi and if successful sets the static IPv4
	// address and launches the udp server and other network services.
	if (!drip_wifi_init())
	{
		wifi_connected = 0;
	}
	while (1)
	{
		cyw43_arch_poll();
		if (wifi_connected)
			sleep_ms(250);
		else
			sleep_ms(1500);
		if (on_board_led_status)
		{
			cyw43_arch_gpio_put(ON_BOARD_LED, 0);
			on_board_led_status = 0;
		}
		else
		{
			cyw43_arch_gpio_put(ON_BOARD_LED, 1);
			on_board_led_status = 1;
		}
		/*
		void cyw43_arch_wait_for_work_until (absolute_time_t until)
		Sleep until there is cyw43_driver work to be done.
		*/
	}
	cyw43_arch_deinit();
}
