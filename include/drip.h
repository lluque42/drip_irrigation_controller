/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:44:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/14 12:39:32 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRIP_H
# define DRIP_H

// For the printf, as usual.
# include <stdio.h>

#include <errno.h>

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

// Values for max and min duration (in seconds) for the relays 
// (W: water, L: lights) to remain activated when timed on.
# define DRIP_MIN_DOW 1
# define DRIP_MIN_DOL 1
# define DRIP_MAX_DOW 60 * 10
# define DRIP_MAX_DOL 60 * 60 * 24

// Values for max and min number of days between timed on relay activations.
// Note: A value of 0 means no timed on.
# define DRIP_MIN_WEXD 0
# define DRIP_MAX_WEXD 5
# define DRIP_MIN_LEXD 0
# define DRIP_MAX_LEXD INT_MAX

// The "serialized" representation of the datetime_t struct
// used in UDP commands and timers_default_data.cmake
// yyyy:mm:dd:dow:hh:mm:ss	22 chars + '\0' == 23
# define DRIP_TIME_STR_MAX_SIZE 23

// The yyyy:mm:dd:dow: part to prefix a hh:mm:ss for a time
// of day setting to convert to datetime_t and set an alarm.
# define DRIP_TIME_STR_TIME_OF_DAY_PREFIX "-1:-1:-1:-1:"

/*
* wtod default: DRIP_WATER_TIME_OF_DAY
* wexd default: DRIP_WATER_EVERY_X_DAYS
* dow_sec default: DRIP_WATER_DURATION_SEC
* 
* ltod default: DRIP_LIGHTS_TIME_OF_DAY
* lexd default: DRIP_LIGHTS_EVERY_X_DAYS
* dol_sec default: DRIP_LIGHTS_DURATION_SEC

*/
typedef struct drip_settings
{
	char		wtod[DRIP_TIME_STR_MAX_SIZE];
	datetime_t	wtod_alarm;
	int			wexd;
	int			dow_sec;
	char		ltod[DRIP_TIME_STR_MAX_SIZE];
	datetime_t	ltod_alarm;
	int			lexd;
	int			dol_sec;
} t_drip_settings;



// For the pico_w this is the pin connected to the on-board led. It's NOT
// a microcontroller's gpio BUT a CYW43 gpio.
// For pico board the on-board led does connect to a RP-2040 gpio, the pin 25.
# define ON_BOARD_LED CYW43_WL_GPIO_LED_PIN

// Th gpio for the electrovalve relay control
# define EV_REL_CTRL 22
# define LIGHTS_REL_CTRL 21

// Global variables defined in main.c
extern bool				on_board_led_status;
extern bool				wifi_connected;
extern t_drip_settings	*drip_settings;

// Sets the static ip address using the build macro defines in
// the wlan_setup_data.cmake
int						drip_wifi_set_ip4_addr(void);

int						drip_rtc_init(void);

void					drip_io_init(void);

void					drip_wifi_print_pbufchain(struct pbuf *pbuf);

void					drip_wifi_recv_callback(void *arg,
												struct udp_pcb *pcb,
												struct pbuf *p,
												const ip_addr_t *addr,
												u16_t port);

int						drip_wifi_udp_server_init(void);

void					drip_rtc_datetime_print(datetime_t time);

int						drip_rtc_str2datetime(const char *timestr_period_field_delimiter,
												datetime_t *time,
												int has_dont_cares);

int						drip_wifi_init(void);

char					*drip_exe_client_request(char *request);

t_drip_settings			*drip_load_settings_default();

#endif
