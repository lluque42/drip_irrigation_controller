/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:46:49 by lluque            #+#    #+#             */
/*   Updated: 2025/10/15 11:01:10 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

uint64_t		drip_time_offset_epoch_us = 0;

int main()
{
	t_drip_conf	*drip_settings;

	drip_bin_set_program_metadata();
	stdio_init_all();
	sleep_ms(1000);
	if (cyw43_arch_init())
		printf("Error initializing cyw43\n");
	drip_io_init();
	hard_assert(drip_time_rtc_init());
	drip_settings = drip_conf_load_settings_default();
	hard_assert(drip_settings != NULL);
	// This function enables wifi station mode (to connect to other APs),
	// sets the static IPv4 address and connects to the wifi.
	// If successful, it launches the udp server and other network services.
	if (!drip_wifi_init(drip_settings))
		printf("Error initializing wifi\n");
	while (1)
	{
		cyw43_arch_poll();
		// Polling must NOT be very frequent
		sleep_ms(5);
	}
	cyw43_arch_deinit();
}
//	 Something else to try if the CYW43 keeps hanging after approx. a day:
/*	printf("These are the settings:\nCYW43_DEFAULT_PM: '%0X'\nCYW43_NONE_PM: '%x'\n\
CYW43_AGGRESSIVE_PM: '%x'\nCYW43_PERFORMANCE_PM: '%x'\n",
		(unsigned int)CYW43_DEFAULT_PM,
		(unsigned int)CYW43_NONE_PM,
		(unsigned int)CYW43_AGGRESSIVE_PM,
		(unsigned int)CYW43_PERFORMANCE_PM);
*/
//	uint32_t	current_pm;
//	
//	cyw43_wifi_get_pm(&cyw43_state, &current_pm);
//	printf("The original power mode has '%0X'\n", (unsigned int)current_pm);
//		cyw43_pm_value(CYW43_DEFAULT_PM),
//		cyw43_pm_value(CYW43_NONE_PM),
//		cyw43_pm_value(CYW43_AGGRESSIVE_PM),
//		cyw43_pm_value(CYW43_PERFORMANCE_PM));
//	if (cyw43_wifi_pm(&cyw43_state, CYW43_NO_POWERSAVE_MODE))
//		printf("Error initializing setting power mode for cyw43\n");
//	cyw43_wifi_get_pm(&cyw43_state, &current_pm);
//	printf("The new power mode has '%0X'\n", (unsigned int)current_pm);
		// WARNING: polling very frequently will eventually make the
		// CYW43 stall (a tight poll loop with no sleep/delay).
		// Apparently (as in not officially documented): "if you poll too
		// aggressively in a tight loop with no yield (busy loop),
		// the FreeRTOS/lwIP timeouts don’t advance properly, and eventually
		// DHCP, ARP cache, or internal timers can stall."
		// "The lwIP stack requires periodic timer servicing. Normally
		// sys_check_timeouts() is called from the polling loop. The Pico SDK
		// cyw43_arch_poll() will call it for you only if enough time has
		// elapsed. But if you never sleep, the "elapsed time" logic might
		// not trigger properly."
		// "Since you’re running a UDP server, ARP table expiry can break
		// communication after some hours if ARP requests are not serviced
		// properly. That again ties back to lwIP timers needing to run
		// consistently. If ARP table cleanup doesn’t happen, packets won’t get
		// delivered."
		//
		// Solutions:
		// 		* Adding sleep_ms(1);
		// 		* Adding tight_loop_contents(); which "expands to __wfe() (the
		// 		ARM “Wait For Event” instruction), which tells the CPU to idle
		// 		until an event happens, reducing power consumption and freeing
		// 		up cycles."
		// 		* Adding cyw43_arch_wait_for_work_until(some_time);
		// 			"Best for production UDP/TCP servers — integrates with lwIP
		// 			timers and Wi-Fi events properly, avoids wasting CPU cycles.
		// 			This is the most robust long-term choice for a polling UDP
		// 			server that should run for days/weeks."
		//
		// Didn't prevent the cyw43 with 5 ms
		//cyw43_arch_wait_for_work_until(make_timeout_time_ms(DRIP_WAIT_WIFI_MS));
		// Didn't prevent it. Tested along with the periodic
// This didn't prevent the wifi hang, it actually kept saying CYW43_LINK_JOIN
//int64_t	drip_wifi_check_health(alarm_id_t id, void *arg)
//{
//	t_drip_conf	*settings;
//	int			status;
//	datetime_t  t;
//	char		buffer[DRIP_WIFI_STATE_MSG_BUFSIZE];
//	
//	memset(buffer, 0, DRIP_WIFI_STATE_MSG_BUFSIZE);
//	id = id;				// Just to avoid the strict warnings
//	settings = (t_drip_conf *)arg;
//	settings = settings;	// Just to avoid the strict warnings
//	if (!rtc_get_datetime(&t))
//		return (DRIP_WIFI_CHECK_MS * 1000);					// TODO error check..................
//	datetime_to_str(buffer, DRIP_WIFI_STATE_MSG_BUFSIZE, &t);
//	buffer[strlen(buffer)] = ':';
//	status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
//	if (status == CYW43_LINK_DOWN)
//		memmove(buffer + strlen(buffer),
//				"CYW43_LINK_DOWN",
//				DRIP_WIFI_STATE_MSG_BUFSIZE - strlen(buffer));
//	if (status == CYW43_LINK_JOIN)
//		memmove(buffer + strlen(buffer),
//				"CYW43_LINK_JOIN",
//				DRIP_WIFI_STATE_MSG_BUFSIZE - strlen(buffer));
//	if (status == CYW43_LINK_FAIL)
//		memmove(buffer + strlen(buffer),
//				"CYW43_LINK_FAIL",
//				DRIP_WIFI_STATE_MSG_BUFSIZE - strlen(buffer));
//	if (status == CYW43_LINK_NONET)
//		memmove(buffer + strlen(buffer),
//				"CYW43_LINK_NONET",
//				DRIP_WIFI_STATE_MSG_BUFSIZE - strlen(buffer));
//	if (status == CYW43_LINK_BADAUTH)
//		memmove(buffer + strlen(buffer),
//				"CYW43_LINK_BADAUTH",
//				DRIP_WIFI_STATE_MSG_BUFSIZE - strlen(buffer));
//	puts(buffer);
//	return (DRIP_WIFI_CHECK_MS * 1000);
//}




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
