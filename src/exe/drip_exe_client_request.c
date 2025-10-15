/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_exe_client_request.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:55:23 by lluque            #+#    #+#             */
/*   Updated: 2025/08/28 16:07:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

struct pbuf	*drip_exe_build_pbuf_from_str(char *str)
{
	struct pbuf	*p;
	
	p = pbuf_alloc(	PBUF_TRANSPORT,
					strlen(str),
					PBUF_RAM);
	// if (== NULL...
	memcpy(p->payload, (void *)str, p->len);
	return (p);
}

/*
 * See README.md for details on the command message formats.
*/
struct pbuf	*drip_exe_client_request(struct pbuf *p, t_drip_conf *drip_settings)
{
	char	*token;
	char	*saveptr;	// For re-entrant strtok
	char	*request;


	// TODO chained pbuf??????? if so, error



	// Changed to a string for easier parsing
	request = calloc(p->len + 1, sizeof(char));
	//if (== NULL)...
	memcpy((void *)request, p->payload, p->len);
	// request comes from the pbuf: (char *)p->payload
	// It is free in the caller after this returns so...
	// I believe there's no issue with editing it.
	// NOT ANYMORE... now request is a temporary string
	// that MUST BE FREED HERE!
	//printf("p->len = '%d'\n", p->len);
	//printf("stringified payload: '%s'\n", request);
	token = strtok_r(request, ":", &saveptr);
	if (NULL)
		return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
	if (strcmp("SET", token) == 0)
	{
		token = strtok_r(NULL, ":", &saveptr);
		if (strcmp("DATETIME", token) == 0)
		{
			datetime_t	time;
			
			// The time_str actually begins after the \0 of DATETIME
			// so some manipulation must be done
			token = strtok_r(NULL, ":", &saveptr);
			// Now token is YYYY\0, then we change back the delimiter
			token[strlen(token)] = ':';
			if (!drip_time_str2datetime(token, &time, 0))
				return (free(request), drip_exe_build_pbuf_from_str("Couldn't set time, err1"));
			if (!rtc_set_datetime(&time))
				return (free(request), drip_exe_build_pbuf_from_str("Couldn't set time, err2"));
			//printf("[drip_exe_client_request] time set, re-scheduling activations...\n");
			//printf("[drip_exe_client_request] This is the current configuration...\n");
			//drip_conf_print_settings(drip_settings);
			if (!drip_conf_enforce_settings(drip_settings))
				return (free(request), drip_exe_build_pbuf_from_str("Time set but couldn't re-schedule timers!"));
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		else if (strcmp("WATER", token) == 0)
		{
			//SET:WATER:WTODHH:WTODmm:WTODSS:WEXD:DOW
			//	SET:WATER:18:50:23:2:120
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing hour"));
			else
			{
				errno = 0;
				drip_settings->wtod_alarm.hour = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->wtod_alarm.hour > 23
					|| drip_settings->wtod_alarm.hour < 0)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for hour"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing minute"));
			else
			{
				errno = 0;
				drip_settings->wtod_alarm.min = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->wtod_alarm.min > 59
					|| drip_settings->wtod_alarm.min < 0)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for minute"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing second"));
			else
			{
				errno = 0;
				drip_settings->wtod_alarm.sec = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->wtod_alarm.sec > 59
					|| drip_settings->wtod_alarm.sec < 0)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for sec"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing days between water"));
			else
			{
				errno = 0;
				drip_settings->wexd = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->wexd > DRIP_MAX_WEXD
					|| drip_settings->wexd < DRIP_MIN_WEXD)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for days between water"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing duration of water"));
			else
			{
				errno = 0;
				drip_settings->dow_sec = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->dow_sec > DRIP_MAX_DOW
					|| drip_settings->dow_sec < DRIP_MIN_DOW)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for days between water"));
			}
			//printf("[drip_exe_client_request] time set, re-scheduling activations...\n");
			//printf("[drip_exe_client_request] This is the current configuration...\n");
			//drip_conf_print_settings(drip_settings);
			if (!drip_conf_enforce_settings(drip_settings))
				return (free(request), drip_exe_build_pbuf_from_str("Time set but couldn't re-schedule timers!"));
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		else if (strcmp("LIGHTS", token) == 0)
		{
			//SET:LIGHTS:LTODHH:LTODmm:LTODSS:LEXD:DOL
			//	SET:DATETIME:2025:8:15:5:19:07:0
			//	SET:LIGHTS:19:07:23:2:12
			//	SET:WATER:19:07:33:1:12
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing hour"));
			else
			{
				errno = 0;
				drip_settings->ltod_alarm.hour = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->ltod_alarm.hour > 23
					|| drip_settings->ltod_alarm.hour < 0)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for hour"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing minute"));
			else
			{
				errno = 0;
				drip_settings->ltod_alarm.min = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->ltod_alarm.min > 59
					|| drip_settings->ltod_alarm.min < 0)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for minute"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing second"));
			else
			{
				errno = 0;
				drip_settings->ltod_alarm.sec = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->ltod_alarm.sec > 59
					|| drip_settings->ltod_alarm.sec < 0)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for sec"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing days between lights"));
			else
			{
				errno = 0;
				drip_settings->lexd = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->lexd > DRIP_MAX_LEXD
					|| drip_settings->lexd < DRIP_MIN_LEXD)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for days between lights"));
			}
			token = strtok_r(NULL, ":", &saveptr);
			if (token == NULL)
				return (free(request), drip_exe_build_pbuf_from_str("Malformed request, missing duration of lights"));
			else
			{
				errno = 0;
				drip_settings->dol_sec = (int)strtol(token, NULL, 10);
				if (errno != 0 || drip_settings->dol_sec > DRIP_MAX_DOL
					|| drip_settings->dow_sec < DRIP_MIN_DOL)
					return (free(request), drip_exe_build_pbuf_from_str("Malformed request, invalid value for days between lights"));
			}
			//printf("[drip_exe_client_request] time set, re-scheduling activations...\n");
			//printf("[drip_exe_client_request] This is the current configuration...\n");
			//drip_conf_print_settings(drip_settings);
			if (!drip_conf_enforce_settings(drip_settings))
				return (free(request), drip_exe_build_pbuf_from_str("Time set but couldn't re-schedule timers!"));
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
	}
	else if (strcmp("GET", token) == 0)
	{
		token = strtok_r(NULL, ":", &saveptr);
		if (strcmp("DATETIME", token) == 0)
		{
			datetime_t	time;
			char		time_str[DRIP_TIME_STR_MAX_SIZE];

			if (!rtc_get_datetime(&time))
				return (free(request), drip_exe_build_pbuf_from_str("Couldn't get time"));
			snprintf(time_str, DRIP_TIME_STR_MAX_SIZE,
						"%d:%d:%d:%d:%d:%d:%d",
						time.year,
						time.month,
						time.day,
						time.dotw, 
						time.hour,
						time.min,
						time.sec);
			return (free(request), drip_exe_build_pbuf_from_str(time_str));
		}
		else if (strcmp("WATER", token) == 0)
		{
			//		TimeOfDay HH mm SS
			//* Get WToD WeXD DoW YYYY MM DD HH mm SS
			//						(timestamp of next scheduled activation)
			//		GET:WATER
			// Response example:
			// 	22:0:0:1:120:2025:8:15:5:19:7:33
			// 	--ToD--      ---next scheduled activation
			// 	     eXD  Do
			char	buffer[DRIP_RELAY_CONF_STR_MAX_SIZE];

			if (drip_settings->next_water_activation != NULL)
			{
				snprintf(buffer, DRIP_RELAY_CONF_STR_MAX_SIZE,
							"%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",
							drip_settings->wtod_alarm.hour,
							drip_settings->wtod_alarm.min,
							drip_settings->wtod_alarm.sec,
							drip_settings->wexd,
							drip_settings->dow_sec,
							drip_settings->next_water_activation->year,
							drip_settings->next_water_activation->month,
							drip_settings->next_water_activation->day,
							drip_settings->next_water_activation->dotw, 
							drip_settings->next_water_activation->hour,
							drip_settings->next_water_activation->min,
							drip_settings->next_water_activation->sec);
			}
			else
			{
				snprintf(buffer, DRIP_RELAY_CONF_STR_MAX_SIZE,
							"%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",
							drip_settings->wtod_alarm.hour,
							drip_settings->wtod_alarm.min,
							drip_settings->wtod_alarm.sec,
							drip_settings->wexd,
							drip_settings->dow_sec,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1);
			}
			return (free(request), drip_exe_build_pbuf_from_str(buffer));
		}
		else if (strcmp("LIGHTS", token) == 0)
		{
			//		TimeOfDay HH mm SS
			//* Get LToD LeXD DoL YYYY MM DD HH mm SS
			//						(timestamp of next scheduled activation)
			//		GET:LIGHTS
			// Response example:
			// 	22:0:0:1:120:2025:8:15:5:19:7:33
			// 	--ToD--      ---next scheduled activation
			// 	     eXD  Do
			char	buffer[DRIP_RELAY_CONF_STR_MAX_SIZE];

			if (drip_settings->next_lights_activation != NULL)
			{
				snprintf(buffer, DRIP_RELAY_CONF_STR_MAX_SIZE,
							"%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",
							drip_settings->ltod_alarm.hour,
							drip_settings->ltod_alarm.min,
							drip_settings->ltod_alarm.sec,
							drip_settings->lexd,
							drip_settings->dol_sec,
							drip_settings->next_lights_activation->year,
							drip_settings->next_lights_activation->month,
							drip_settings->next_lights_activation->day,
							drip_settings->next_lights_activation->dotw, 
							drip_settings->next_lights_activation->hour,
							drip_settings->next_lights_activation->min,
							drip_settings->next_lights_activation->sec);
			}
			else
			{
				snprintf(buffer, DRIP_RELAY_CONF_STR_MAX_SIZE,
							"%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",
							drip_settings->ltod_alarm.hour,
							drip_settings->ltod_alarm.min,
							drip_settings->ltod_alarm.sec,
							drip_settings->lexd,
							drip_settings->dol_sec,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1,
							-1);
			}
			return (free(request), drip_exe_build_pbuf_from_str(buffer));
		}
		return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
	}
	else if (strcmp("MANUALON", token) == 0)
	{
		token = strtok_r(NULL, ":", &saveptr);
		if (strcmp("WATER", token) == 0)
		{
			gpio_put(EV_REL_CTRL, 1);
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		else if (strcmp("LIGHTS", token) == 0)
		{
			gpio_put(LIGHTS_REL_CTRL, 1);
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
	}
	else if (strcmp("MANUALOFF", token) == 0)
	{
		token = strtok_r(NULL, ":", &saveptr);
		if (strcmp("WATER", token) == 0)
		{
			gpio_put(EV_REL_CTRL, 0);
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		else if (strcmp("LIGHTS", token) == 0)
		{
			gpio_put(LIGHTS_REL_CTRL, 0);
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
	}
	else if (strcmp("TIMEDON", token) == 0)
	{
		token = strtok_r(NULL, ":", &saveptr);
		if (strcmp("WATER", token) == 0)
		{
			gpio_put(EV_REL_CTRL, 1);
			drip_settings->water_manual_next_off_alarm_id =
								add_alarm_in_ms(drip_settings->dow_sec * 1000,
													drip_exe_water_manual_off,
													NULL,
													0);
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		else if (strcmp("LIGHTS", token) == 0)
		{
			gpio_put(LIGHTS_REL_CTRL, 1);
			drip_settings->lights_manual_next_off_alarm_id =
								add_alarm_in_ms(drip_settings->dol_sec * 1000,
													drip_exe_lights_manual_off,
													NULL,
													0);
			return (free(request), drip_exe_build_pbuf_from_str("done"));
		}
		return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
	}
	return (free(request), drip_exe_build_pbuf_from_str("Malformed request"));
}

// The callback for manual timed activation of water relay
int64_t	drip_exe_water_manual_off(alarm_id_t id, void *arg)
{
	t_drip_conf	*drip_settings;

	// just for the warnings
	id = id;
	drip_settings = (t_drip_conf *)arg;
	gpio_put(EV_REL_CTRL, 0);
	drip_settings->lights_manual_next_off_alarm_id = -1;
	return (0);
}

// The callback for manual timed activation of lights relay
int64_t	drip_exe_lights_manual_off(alarm_id_t id, void *arg)
{
	t_drip_conf	*drip_settings;

	// just for the warnings
	id = id;
	drip_settings = (t_drip_conf *)arg;
	gpio_put(LIGHTS_REL_CTRL, 0);
	drip_settings->water_manual_next_off_alarm_id = -1;
	return (0);
}
