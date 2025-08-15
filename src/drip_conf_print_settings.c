/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_conf_print_settings.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:56:30 by lluque            #+#    #+#             */
/*   Updated: 2025/08/15 10:56:46 by lluque           ###   ########.fr       */
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
		drip_rtc_datetime_print(*drip_settings->next_water_activation);
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
		drip_rtc_datetime_print(*drip_settings->next_lights_activation);
}
