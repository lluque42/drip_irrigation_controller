/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_conf_enforce_settings.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:55:49 by lluque            #+#    #+#             */
/*   Updated: 2025/08/15 10:56:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_conf_enforce_settings(t_drip_conf *drip_settings)
{
	datetime_t		*target_datetime;
	absolute_time_t	target_abs_time_us;

	// Provision for the future udp settings command to delete every pending
	// alarm before reconfigure.
	alarm_pool_destroy(alarm_pool_get_default());
	alarm_pool_init_default();

	free(drip_settings->next_water_activation);
	drip_settings->next_water_activation = drip_conf_set_next_timeofday_alarm(
			drip_settings->wtod_alarm,
			drip_settings->wexd,
			drip_exe_water_timed_on,
			drip_settings);

	free(drip_settings->next_lights_activation);
	drip_settings->next_lights_activation = drip_conf_set_next_timeofday_alarm(
			drip_settings->ltod_alarm,
			drip_settings->lexd,
			drip_exe_lights_timed_on,
			drip_settings);
	if (drip_settings->next_water_activation == NULL
		|| drip_settings->next_lights_activation == NULL)
		return (0);
	return (1);
}
