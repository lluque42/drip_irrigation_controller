/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_exe_lights_timed_on.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:19:33 by lluque            #+#    #+#             */
/*   Updated: 2025/08/16 22:18:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

// Must be of alarm_callback_t type:
// typedef int64_t(* 	alarm_callback_t) (alarm_id_t id, void *user_data)
/*
Returns
<0 to reschedule the same alarm this many us from the time the alarm was previously scheduled to fire
>0 to reschedule the same alarm this many us from the time this method returns
0 to not reschedule the alarm
 */
int64_t	drip_exe_lights_timed_on(alarm_id_t id, void *arg)
{
	t_drip_conf	*settings;

	settings = (t_drip_conf *)arg;
	gpio_put(LIGHTS_REL_CTRL, 1);
	printf("[drip_exe_lights_timed_on] Triggered alarm_id %ld\n", id);
	printf("[drip_exe_lights_timed_on] Duration of lights = %d\n",
			settings->dol_sec);

	settings->lights_timed_next_off_alarm_id =
									add_alarm_in_ms(settings->dol_sec * 1000,
													drip_exe_lights_timed_off,
													arg,
													0);
	return (0);
}

int64_t	drip_exe_lights_timed_off(alarm_id_t id, void *arg)
{
	t_drip_conf	*settings;

	settings = (t_drip_conf *)arg;
	gpio_put(LIGHTS_REL_CTRL, 0);
	printf("[drip_exe_lights_timed_off] Triggered alarm_id %ld\n", id);
	printf("[drip_exe_lights_timed_off] Days for the next lights = %d\n", 
			settings->lexd);
	free(settings->next_lights_activation);
	settings->next_lights_activation = drip_conf_set_next_timeofday_alarm(
									settings->ltod_alarm,
									settings->lexd,
									drip_exe_lights_timed_on,
									settings,
									&settings->water_timed_next_on_alarm_id);
	hard_assert(settings->next_water_activation != NULL);
	return (0);
}
