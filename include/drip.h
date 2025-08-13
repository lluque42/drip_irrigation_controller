/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:44:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/13 22:56:54 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRIP_H
# define DRIP_H

// For the printf, as usual.
# include <stdio.h>

// For the low-level part of time/date functions.
# include "hardware/rtc.h"

// For datetime_to_str() which is not documented in my local api doxygen
# include "pico/util/datetime.h"

// Obvious
# include "hardware/gpio.h"

// So far for the on-board LED which is connected to a wifi chip gpio.
# include "pico/cyw43_arch.h"

// For sleep_ms() and stdio_init_all()
# include "pico/stdlib.h"
/*
This is an umbrella header that includes:
	hardware_divider
	hardware_gpio
	hardware_uart
	pico_runtime
	pico_platform
	pico_stdio
	pico_time
	pico_util
*/

# define DRIP_WIFI_CONNECT_TIMEOUT_MS 10000

# ifndef DRIP_WIFI_AUTH
#  define DRIP_WIFI_AUTH
# endif

// For the pico_w this is the pin connected to the on-board led. It's NOT
// a microcontroller's gpio BUT a CYW43 gpio.
// For pico board the on-board led does connect to a RP-2040 gpio, the pin 25.
# define ON_BOARD_LED CYW43_WL_GPIO_LED_PIN

// Th gpio for the electrovalve relay control
# define EV_REL_CTRL 22
# define LIGHTS_REL_CTRL 21

// Global variables defined in main.c
extern bool	on_board_led_status;
extern bool	wifi_connected;

// Sets the static ip address using the build macro defines in
// the wlan_setup_data.cmake
int			drip_wifi_set_ip4_addr(void);

int			drip_rtc_init(void);

void		drip_io_init(void);

void		drip_wifi_print_pbufchain(struct pbuf *pbuf);

void		drip_wifi_recv_callback(void *arg,
									struct udp_pcb *pcb,
									struct pbuf *p,
									const ip_addr_t *addr,
									u16_t port);

int			drip_wifi_udp_server_init(void);

void		drip_rtc_datetime_print(datetime_t time);

datetime_t drip_rtc_str2datetime(const char *timestr_period_field_delimiter);

int			drip_wifi_init(void);

char		*drip_exe_client_request(char *request);

#endif
