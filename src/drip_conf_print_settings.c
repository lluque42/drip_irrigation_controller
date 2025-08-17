/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_conf_print_settings.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:56:30 by lluque            #+#    #+#             */
/*   Updated: 2025/08/16 21:53:58 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_conf_print_settings(t_drip_conf *drip_settings)
{
	printf("Current settings:\n");
	printf("\tWater timed on at: '%s'\n",
			drip_settings->wtod);
	printf("\t\tParsed:\n");
	drip_rtc_datetime_print(drip_settings->wtod_alarm);
	printf("\tWater timed on every '%d' days\n", drip_settings->wexd);
	printf("\tWater will be on during '%d' seconds\n", drip_settings->dow_sec);
	printf("\t\tNext water activation:\n");
	if (drip_settings->next_water_activation == NULL)
		printf("\t\t\tNot set\n");
	else
	{
		drip_rtc_datetime_print(*drip_settings->next_water_activation);
		printf("\t\tNext water activation is triggered by alarm_id '%ld'\n",
				drip_settings->water_timed_next_on_alarm_id);
	}
	printf("\tLights timed on at: '%s'\n",
			drip_settings->ltod);
	printf("\t\tParsed:\n");
	drip_rtc_datetime_print(drip_settings->ltod_alarm);
	printf("\tLights timed on every '%d' days\n", drip_settings->lexd);
	printf("\tLights will be on during '%d' seconds\n", drip_settings->dol_sec);
	printf("\t\tNext lights activation:\n");
	if (drip_settings->next_lights_activation == NULL)
		printf("\t\t\tNot set\n");
	else
	{
		drip_rtc_datetime_print(*drip_settings->next_lights_activation);
		printf("\t\tNext lights activation is triggered by alarm_id '%ld'\n",
				drip_settings->water_timed_next_on_alarm_id);
	}
	printf ("Other alarm_ids: ManOffLights=%ld ManOffWater=%ld \
TimedOffLights%ld TimedOffWater%ld\n",
			drip_settings->lights_manual_next_off_alarm_id,
			drip_settings->water_manual_next_off_alarm_id,
			drip_settings->lights_timed_next_off_alarm_id,
			drip_settings->water_timed_next_off_alarm_id);
}
