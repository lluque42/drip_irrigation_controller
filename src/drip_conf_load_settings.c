/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_conf_load_settings.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:38:38 by lluque            #+#    #+#             */
/*   Updated: 2025/08/15 10:57:38 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

t_drip_conf	*drip_conf_load_settings_default()
{
	t_drip_conf	*s;

	s = calloc(1, sizeof (t_drip_conf));
	if (s == NULL)
		printf("[drip_load_settings_default] Couldn't allocate\n");
	strcpy(s->wtod, DRIP_TIME_STR_TIME_OF_DAY_PREFIX);
	strcpy(s->wtod + strlen(DRIP_TIME_STR_TIME_OF_DAY_PREFIX),
			DRIP_WATER_TIME_OF_DAY);
	//printf("[drip_load_settings_default] s->wtod = '%s'\n", s->wtod);
	s->wexd = atoi(DRIP_WATER_EVERY_X_DAYS);
	s->dow_sec = atoi(DRIP_WATER_DURATION_SEC);
	strcpy(s->ltod, DRIP_TIME_STR_TIME_OF_DAY_PREFIX);
	strcpy(s->ltod + strlen(DRIP_TIME_STR_TIME_OF_DAY_PREFIX),
			DRIP_LIGHTS_TIME_OF_DAY);
	//printf("[drip_load_settings_default] s->ltod = '%s'\n", s->ltod);
	s->lexd = atoi(DRIP_LIGHTS_EVERY_X_DAYS);
	s->dol_sec = atoi(DRIP_LIGHTS_DURATION_SEC);
	// Values check
	if (s->dow_sec < DRIP_MIN_DOW || s->dow_sec > DRIP_MAX_DOW)
		return (printf("Invalid value for DRIP_WATER_DURATION_SEC"),
				free(s), NULL);
	if (s->wexd < DRIP_MIN_WEXD || s->wexd > DRIP_MAX_WEXD)
		return (printf("Invalid value for DRIP_WATER_EVERY_X_DAYS"),
				free(s), NULL);
	if (s->dol_sec < DRIP_MIN_DOL || s->dol_sec > DRIP_MAX_DOL)
		return (printf("Invalid value for DRIP_LIGHTS_DURATION_SEC"),
				free(s), NULL);
	if (s->lexd < DRIP_MIN_LEXD || s->lexd > DRIP_MAX_LEXD)
		return (printf("Invalid value for DRIP_LIGHTS_EVERY_X_DAYS"),
				free(s), NULL);
	hard_assert(drip_rtc_str2datetime(s->wtod, &s->wtod_alarm, 1));
	hard_assert(drip_rtc_str2datetime(s->ltod, &s->ltod_alarm, 1));
	drip_conf_print_settings(s);
	hard_assert(drip_conf_enforce_settings(s));
	return (s);
}
//	target_datetime = drip_time_get_next_instant(drip_settings->wtod_alarm);
//	printf("Next instant for the water alarm:\n");
//	drip_rtc_datetime_print(*target_datetime);
//	hard_assert(drip_time_get_epochus_from_datetime(&target_abs_time_us, 
//				*target_datetime));
//	free(target_datetime);
//	printf("(in epoch usec format: %lld)\n", target_abs_time_us);
//	water_on_alarm_id = add_alarm_at(
//									target_abs_time_us - time_offset_epoch_us,
//									drip_exe_water_timed_on,
//									(void *)drip_settings,
//									0);
//	target_datetime = drip_time_get_next_instant(drip_settings->ltod_alarm);
//	printf("Next instant for the lights alarm:\n");
//	drip_rtc_datetime_print(*target_datetime);
//	hard_assert(drip_time_get_epochus_from_datetime(&target_abs_time_us,
//				*target_datetime));
//	free(target_datetime);
//	printf("(in epoch usec format: %lld)\n", target_abs_time_us);
//	lights_on_alarm_id = add_alarm_at(
//									target_abs_time_us - time_offset_epoch_us,
//									drip_exe_lights_timed_on,
//									(void *)drip_settings,
//									0);
