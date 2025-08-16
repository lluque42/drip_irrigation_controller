/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_conf_enforce_settings.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:55:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/16 22:07:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_conf_cancel_all_allarms(t_drip_conf *drip_settings)
{
	if (cancel_alarm(drip_settings->water_timed_next_on_alarm_id))
		printf("\tWater alarm %ld successfully canceled\n",
				drip_settings->water_timed_next_on_alarm_id);
	else
		printf("\tWater alarm %ld doesn't exist\n",
				drip_settings->water_timed_next_on_alarm_id);
	drip_settings->water_timed_next_on_alarm_id = 0;
	if (cancel_alarm(drip_settings->lights_timed_next_on_alarm_id))
		printf("\tLights alarm %ld successfully canceled\n",
				drip_settings->lights_timed_next_on_alarm_id);
	else
		printf("\tLights alarm %ld doesn't exist\n",
				drip_settings->lights_timed_next_on_alarm_id);
	drip_settings->lights_timed_next_on_alarm_id = 0;

	if (cancel_alarm(drip_settings->water_timed_next_off_alarm_id))
		printf("\tWater alarm %ld successfully canceled\n",
				drip_settings->water_timed_next_off_alarm_id);
	else
		printf("\tWater alarm %ld doesn't exist\n",
				drip_settings->water_timed_next_off_alarm_id);
	drip_settings->water_timed_next_off_alarm_id = 0;
	if (cancel_alarm(drip_settings->lights_timed_next_off_alarm_id))
		printf("\tLights alarm %ld successfully canceled\n",
				drip_settings->lights_timed_next_off_alarm_id);
	else
		printf("\tLights alarm %ld doesn't exist\n",
				drip_settings->lights_timed_next_off_alarm_id);
	drip_settings->lights_timed_next_off_alarm_id = 0;

	if (cancel_alarm(drip_settings->water_manual_next_off_alarm_id))
		printf("\tWater alarm %ld successfully canceled\n",
				drip_settings->water_manual_next_off_alarm_id);
	else
		printf("\tWater alarm %ld doesn't exist\n",
				drip_settings->water_manual_next_off_alarm_id);
	drip_settings->water_manual_next_off_alarm_id = 0;
	if (cancel_alarm(drip_settings->lights_manual_next_off_alarm_id))
		printf("\tLights alarm %ld successfully canceled\n",
				drip_settings->lights_manual_next_off_alarm_id);
	else
		printf("\tLights alarm %ld doesn't exist\n",
				drip_settings->lights_manual_next_off_alarm_id);
	drip_settings->lights_manual_next_off_alarm_id = 0;
}

int	drip_conf_enforce_settings(t_drip_conf *drip_settings)
{
	datetime_t		current_datetime;

	printf("[drip_conf_enforce_settings] Enforcing settings...\n");
	alarm_pool_init_default();

	// Delete every pending alarm before reconfigure with new settings or time.
	printf("[drip_conf_enforce_settings] Clearing scheduled activations\n");
	drip_conf_cancel_all_allarms(drip_settings);

	// Turn off every output just in case
	gpio_put(EV_REL_CTRL, 0);
	gpio_put(LIGHTS_REL_CTRL, 0);

	// Update the datetime_t RTC vs absolute_time_t of alarms (us since boot)
	// In case the time has been set
	printf("[drip_conf_enforce_settings] Computing next water alarm\n");
	hard_assert(rtc_get_datetime(&current_datetime));
	drip_time_offset_epoch_us = drip_rtc_compute_rtc_alarms_offset();
	
	free(drip_settings->next_water_activation);
	if (drip_settings->wexd != 0)
	{
		drip_settings->next_water_activation = drip_conf_set_next_timeofday_alarm(
				drip_settings->wtod_alarm,
				drip_settings->wexd,
				drip_exe_water_timed_on,
				drip_settings,
				&drip_settings->water_timed_next_on_alarm_id);
		if (drip_settings->next_water_activation == NULL)
			return (0);
	}
	else
		drip_settings->next_water_activation = NULL;

	printf("[drip_conf_enforce_settings] Computing next lights alarm\n");
	free(drip_settings->next_lights_activation);
	if (drip_settings->lexd != 0)
	{
		drip_settings->next_lights_activation = drip_conf_set_next_timeofday_alarm(
				drip_settings->ltod_alarm,
				drip_settings->lexd,
				drip_exe_lights_timed_on,
				drip_settings,
				&drip_settings->lights_timed_next_on_alarm_id);
		if (drip_settings->next_lights_activation == NULL)
			return (0);
	}
	else
		drip_settings->next_lights_activation = NULL;
	return (1);
}
