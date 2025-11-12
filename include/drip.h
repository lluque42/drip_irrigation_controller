/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:44:49 by lluque            #+#    #+#             */
/*   Updated: 2025/11/12 13:46:09 by lluque           ###   ########.fr       */
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

// To include program metadata into the binary.
// It may be examined by picotool.
#include "pico/binary_info.h"

#include "lwip/udp.h"		// Needed after setting #define LWIP_DHCP 0 in lwiopts.h

# define DRIP_WIFI_CONNECT_TIMEOUT_MS 10000

// Values for max and min duration (in seconds) for the relays 
// (W: water, L: lights) to remain activated when timed on.
# define DRIP_MIN_DOW 0
# define DRIP_MIN_DOL 0
# define DRIP_MAX_DOW 60 * 10
# define DRIP_MAX_DOL 60 * 60 * 24

// Values for max and min number of days between timed on relay activations.
// Note: A value of 0 means no timed on.
# define DRIP_MIN_WEXD 0
# define DRIP_MAX_WEXD 5
# define DRIP_MIN_LEXD 0
# define DRIP_MAX_LEXD INT_MAX
# define DRIP_WAIT_WIFI_MS 5
# define DRIP_WIFI_CHECK_MS 60000
# define DRIP_WIFI_STATE_MSG_BUFSIZE 512

// The "serialized" representation of the datetime_t struct
// used in UDP commands and timers_default_data.cmake
// yyyy:mm:dd:dow:hh:mm:ss	22 chars + '\0' == 23
# define DRIP_TIME_STR_MAX_SIZE 40

// The serialized version of a relay configuration
#define DRIP_RELAY_CONF_STR_MAX_SIZE 256

// The yyyy:mm:dd:dow: part to prefix a hh:mm:ss for a time
// of day setting to convert to datetime_t and set an alarm.
// The -1 values indicate don't care (i.e. any year, month...)
# define DRIP_TIME_STR_TIME_OF_DAY_PREFIX "-1:-1:-1:-1:"

// For the pico_w this is the pin connected to the on-board led. It's NOT
// a microcontroller's gpio BUT a CYW43 gpio.
// For pico board the on-board led does connect to a RP-2040 gpio, the pin 25.
# define ON_BOARD_LED CYW43_WL_GPIO_LED_PIN

// Th gpio for the electrovalve relay control
# define EV_REL_CTRL 6
# define LIGHTS_REL_CTRL 5

// Global variables defined in main.c
/*
 * This must be updated every time the rtc time is updated.
 * This variable represents the amount of microseconds
 * that the absolute_time_t counter is behind respective to
 * the epoch time of the rtc.
 *
 * Remember that the absolute_time_t represents usecs since boot, NOT epoch.
 */
extern uint64_t			drip_time_offset_epoch_us;

/*
* wtod default: DRIP_WATER_TIME_OF_DAY
* wexd default: DRIP_WATER_EVERY_X_DAYS
* dow_sec default: DRIP_WATER_DURATION_SEC
* 
* ltod default: DRIP_LIGHTS_TIME_OF_DAY
* lexd default: DRIP_LIGHTS_EVERY_X_DAYS
* dol_sec default: DRIP_LIGHTS_DURATION_SEC

*/
// The invalid/initialization value for the _alarm_id's is -1
typedef struct s_drip_conf
{
	char		wtod[DRIP_TIME_STR_MAX_SIZE];	// Only holds the default to init	// May be this should be updated when user changes configuration TODO
	datetime_t	wtod_alarm;						// Always holds current
	int			wexd;
	int			dow_sec;
	char		ltod[DRIP_TIME_STR_MAX_SIZE];	// Only holds the default to init	// May be this should be updated when user changes configuration TODO
	datetime_t	ltod_alarm;						// Always holds current
	int			lexd;
	int			dol_sec;
	// Not really configuration TODO
	datetime_t	*next_water_activation;
	datetime_t	*next_lights_activation;
	alarm_id_t	water_timed_next_on_alarm_id;			
	alarm_id_t	lights_timed_next_on_alarm_id;
	alarm_id_t	water_timed_next_off_alarm_id;
	alarm_id_t	lights_timed_next_off_alarm_id;
	alarm_id_t	water_manual_next_off_alarm_id;
	alarm_id_t	lights_manual_next_off_alarm_id;
	alarm_id_t	wifi_health_alarm_id;
} t_drip_conf;

typedef enum e_drip_relay
{
	D_WATER,
	D_LIGHTS,
}	t_drip_relay;

/* This function does the followint: it enables the station mode to be able to
 * connect to an access point; tries to establish a connection with the wlan;
 * sets the static ip address; and if everything is OK it calls 
 * drip_wifi_udp_server_init() to launch the UDP server.
 */
int			drip_wifi_init(t_drip_conf *drip_settings);

int			drip_wifi_set_ip4_addr(char *addr_str, char *mask_str, char *gw_str);

void		drip_wifi_print_pbufchain(struct pbuf *pbuf);

void		drip_wifi_recv_callback(void *arg,
									struct udp_pcb *pcb,
									struct pbuf *p,
									const ip_addr_t *addr,
									u16_t port);

int			drip_wifi_udp_server_init(t_drip_conf *drip_settings);

void		drip_io_init(void);

int			drip_time_rtc_init(void);

void		drip_time_print_datetime(datetime_t time);

int			drip_time_str2datetime(const char *timestr_period_field_delimiter,
									datetime_t *time,
									int has_dont_cares);

int			drip_time_get_epochus_from_current_rtc_datetime(time_t *time);

int			drip_time_get_epochus_from_datetime(time_t *time,
												datetime_t some_datetime);

/*
 * Given a -1 masked datetime_t time-of-day and the frequency (each_x_days)
 * this functione gets the currrent RTC date time and returns a pointer to a
 * new datetime_t storing the next instant in time that complies with the
 * frequency.
 */
datetime_t	*drip_time_get_next_instant(datetime_t freq,
										int each_x_days);

uint64_t	drip_time_compute_rtc_abs_offset(void);

int64_t		drip_exe_water_timed_on(alarm_id_t id, void *dow_sec);

int64_t		drip_exe_water_timed_off(alarm_id_t id, void *arg);

int64_t		drip_exe_lights_timed_on(alarm_id_t id, void *dol_sec);

int64_t		drip_exe_lights_timed_off(alarm_id_t id, void *arg);

struct pbuf	*drip_exe_client_request(struct pbuf *p, t_drip_conf *drip_settings);

/*
 * Creates the settings instructions for the program and initializes its
 * fields with the define values obtain at buildtime.
 */
t_drip_conf	*drip_conf_load_settings_default();

datetime_t	*drip_conf_set_next_timeofday_alarm(datetime_t time_of_day,
												int each_x_days,
												alarm_callback_t callback,
												t_drip_conf *drip_settings,
												alarm_id_t *alarm_id);

int			drip_conf_enforce_settings(t_drip_conf *drip_settings);

void		drip_conf_print_settings(t_drip_conf *drip_settings);

int64_t		drip_exe_lights_manual_off(alarm_id_t id, void *arg);

int64_t		drip_exe_water_manual_off(alarm_id_t id, void *arg);

void		drip_conf_cancel_all_alarms(t_drip_conf *drip_settings);

void		drip_bin_set_program_metadata(void);

#endif
