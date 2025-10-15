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

void	drip_conf_cancel_all_alarms(t_drip_conf *drip_settings)
{
	if (drip_settings->water_timed_next_on_alarm_id != -1)
		cancel_alarm(drip_settings->water_timed_next_on_alarm_id);
	drip_settings->water_timed_next_on_alarm_id = -1;
	if (drip_settings->lights_timed_next_on_alarm_id != -1)
		cancel_alarm(drip_settings->lights_timed_next_on_alarm_id);
	drip_settings->lights_timed_next_on_alarm_id = -1;
	if (drip_settings->water_timed_next_off_alarm_id != -1)
		cancel_alarm(drip_settings->water_timed_next_off_alarm_id);
	drip_settings->water_timed_next_off_alarm_id = -1;
	if (drip_settings->lights_timed_next_off_alarm_id != -1)
		cancel_alarm(drip_settings->lights_timed_next_off_alarm_id);
	drip_settings->lights_timed_next_off_alarm_id = -1;
	if (drip_settings->water_manual_next_off_alarm_id != -1)
		cancel_alarm(drip_settings->water_manual_next_off_alarm_id);
	drip_settings->water_manual_next_off_alarm_id = -1;
	if (drip_settings->lights_manual_next_off_alarm_id != -1)
		cancel_alarm(drip_settings->lights_manual_next_off_alarm_id);
	drip_settings->lights_manual_next_off_alarm_id = -1;
}
