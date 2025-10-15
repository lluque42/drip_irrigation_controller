/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_exe_water_timed_on.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:19:33 by lluque            #+#    #+#             */
/*   Updated: 2025/08/26 00:05:10 by lluque           ###   ########.fr       */
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
int64_t	drip_exe_water_timed_on(alarm_id_t id, void *arg)
{
	t_drip_conf	*settings;

	id = id;	// Just to avoid the strict warnings
	settings = (t_drip_conf *)arg;
	gpio_put(EV_REL_CTRL, 1);
	//printf("[drip_exe_water_timed_on] Triggered alarm_id %ld\n", id);
	//printf("[drip_exe_water_timed_on] Duration of water = %d\n", 
	//		settings->dow_sec);
	settings->water_timed_next_off_alarm_id =
									add_alarm_in_ms(settings->dow_sec * 1000,
													drip_exe_water_timed_off,
													arg,
													0);
	settings->water_timed_next_on_alarm_id = -1;
	return (0);
}

int64_t	drip_exe_water_timed_off(alarm_id_t id, void *arg)
{
	t_drip_conf	*settings;

	id = id;	// Just to avoid the strict warnings
	settings = (t_drip_conf *)arg;
	gpio_put(EV_REL_CTRL, 0);
	//printf("[drip_exe_water_timed_off] Triggered alarm_id %ld\n", id);
	//printf("[drip_exe_water_timed_off] Days for the next water = %d\n", 
	//		settings->wexd);
	free(settings->next_water_activation);
	settings->next_water_activation = drip_conf_set_next_timeofday_alarm(
									settings->wtod_alarm,
									settings->wexd,
									drip_exe_water_timed_on,
									settings,
									&settings->water_timed_next_on_alarm_id);
	hard_assert(settings->next_water_activation != NULL);
	settings->water_timed_next_off_alarm_id = -1;
	return (0);
}
