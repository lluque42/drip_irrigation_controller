/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_exe_lights_timed_on.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:19:33 by lluque            #+#    #+#             */
/*   Updated: 2025/08/15 10:53:18 by lluque           ###   ########.fr       */
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
	printf("[drip_exe_lights_timed_on]  triggered alarm_id %d\n", id);
	printf("[drip_exe_lights_timed_on] Duration of lights = %d\n",
			settings->dol_sec);

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
	printf("[drip_exe_lights_timed_off] triggered alarm_id %d\n", id);
	printf("[drip_exe_lights_timed_off] Days for the next lights = %d\n", 
			settings->lexd);
	free(settings->next_lights_activation);
	settings->next_lights_activation = drip_conf_set_next_timeofday_alarm(
													settings->ltod_alarm,
													settings->lexd,
													drip_exe_lights_timed_on,
													settings);
	hard_assert(settings->next_water_activation != NULL);
	print_settings_pending = 1;
	return (0);
}
