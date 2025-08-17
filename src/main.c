/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:46:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/17 01:47:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

uint64_t		drip_time_offset_epoch_us = 0;

void	drip_bin_set_program_metadata(void)
{
	bi_decl(bi_program_description("Drip irrigation controller. Designed to \
control one relay for a water electrovalve and a second relay for ornament \
lights. Both may be configured for independent one-time-a-day activation \
and to remain active a period of time. The days between activations is also \
configurable. Any relay may be disabled to stop their future scheduled \
activations. The configuration (get and set) and manual activation \
may be done remotely through the wifi connection with simple UDP messages. \
Water: GPIO22 Lights: GPIO21."));                                                        
	bi_decl(bi_program_url("https://github.com/lluque42/drip_irrigation_controller.git"));
}

int main()
{
	t_drip_conf	*drip_settings;

	drip_bin_set_program_metadata();
	stdio_init_all();
	sleep_ms(1000);
	if (cyw43_arch_init())
		printf("Error initializing cyw43\n");

	drip_io_init();
	hard_assert(drip_rtc_init());

	drip_settings = drip_conf_load_settings_default();
	hard_assert(drip_settings != NULL);

	// This function enables wifi station mode (to connect to other APs),
	// connects to the wifi and if successful sets the static IPv4
	// address and launches the udp server and other network services.
	if (!drip_wifi_init(drip_settings))
		printf("Error initializing wifi\n");
	while (1)
	{
		cyw43_arch_poll();
	}
	cyw43_arch_deinit();
}
//	// While debugging (or if the board was visible in this application,
//	// this comes handy as a heartbeat. Call from the main loop.
//		drip_toggle_on_board_led(&on_board_led_status);
//
//	// NOTE: I couldn't make it work as a callback with a timer may be because
//	// being a CWY43 GPIO it conflicts when manipulated from an IRQ
//	static void	drip_toggle_on_board_led(bool *on_board_led_status)
//	{
//		//	// It requrires this outside:
//		//	#define DRIP_TOGGLE_ON_BOARD_LED_MS 500
//		//
//		//	// It requrires this outside the loop:
//		//	//	bool			on_board_led_status;
//	
//		//	// After cyw43_arch_init()
//		//	cyw43_arch_gpio_put(ON_BOARD_LED, 1);
//		//	*on_board_led_status = true;
//		if (*on_board_led_status)
//		{
//			cyw43_arch_gpio_put(ON_BOARD_LED, 0);
//			*on_board_led_status = false;
//		}
//		else
//		{
//			cyw43_arch_gpio_put(ON_BOARD_LED, 1);
//			*on_board_led_status = true;
//		}
//		sleep_ms(DRIP_TOGGLE_ON_BOARD_LED_MS);
//	}
//	// To avoid IRQ-unsafe operations, just set a global flag in a callback
//	// but service it outside in the main loop.
//	// This global
//	int				print_settings_pending = 0;
//
//	// This inside the main loop:
//	if (print_settings_pending)
//	{
//		print_settings_pending = 0;
//		printf("[main] A print_settings_pending\n");
//		drip_conf_print_settings(drip_settings);
//	}
//
//
//	// Another useful heartbeat when having RTC applications is this 
//	// repeating low-level alarm.
//	// In main()
//	datetime_t	alarm_pattern;
//	
//	// Values of -1 indicate don't care, i.e. no need to match.
//	hard_assert (drip_rtc_str2datetime(	"-1:-1:-1:-1:-1:-1:0",
//											&alarm_pattern, 1));
//	//rtc_set_alarm(&alarm_pattern, timer_alarm);
//	
//	The callback:
//	void	timer_alarm(void)
//	{
//		datetime_t	t;
//		char		time_str[200];
//	
//		printf("[timer_alarm] Alarm works\n");
//		if (!rtc_get_datetime(&t))
//			printf("[timer_alarm] RTC not working\n");
//		else
//		{
//			datetime_to_str(time_str, sizeof(time_str), &t);
//			printf("%s\n", time_str);
//		}
//	}
