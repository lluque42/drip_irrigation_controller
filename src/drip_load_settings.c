/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_load_settings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 08:38:38 by lluque            #+#    #+#             */
/*   Updated: 2025/08/14 13:37:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_print_settings(t_drip_settings *drip_settings)
{
	printf("Current settings:\n");
	printf("\tWater timed on at: '%s'\n",
			drip_settings->wtod[DRIP_TIME_STR_MAX_SIZE]);
	printf("\t\tParsed:\n");
	drip_rtc_datetime_print(drip_settings->wtod_alarm);
	printf("\tWater timed on every '%d' days\n", drip_settings->wexd);
	printf("\tWater will be on during '%d' seconds\n", drip_settings->dow_sec);
	printf("\tLights timed on at: '%s'\n",
			drip_settings->ltod[DRIP_TIME_STR_MAX_SIZE]);
	printf("\t\tParsed:\n");
	drip_rtc_datetime_print(drip_settings->ltod_alarm);
	printf("\tLights timed on every '%d' days\n", drip_settings->lexd);
	printf("\tLights will be on during '%d' seconds\n", drip_settings->dol_sec);
}
/*
	char		wtod[DRIP_TIME_STR_MAX_SIZE];
	datetime_t	wtod_alarm;
	int			wexd;
	int			dow_sec;
	char		ltod[DRIP_TIME_STR_MAX_SIZE];
	datetime_t	ltod_alarm;
	int			lexd;
	int			dol_sec;
*/
t_drip_settings	*drip_load_settings_default()
{
	t_drip_settings	*s;

	s = calloc(1, sizeof (t_drip_settings));
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
	drip_print_settings(s);
	return (s);
}
/*

 48 * wtod default: DRIP_WATER_TIME_OF_DAY                                           
 49 * wexd default: DRIP_WATER_EVERY_X_DAYS                                          
 50 * dow_sec default: DRIP_WATER_DURATION_SEC                                       
 51 *                                                                                
 52 * ltod default: DRIP_LIGHTS_TIME_OF_DAY                                          
 53 * lexd default: DRIP_LIGHTS_EVERY_X_DAYS                                         
 54 * dol_sec default: DRIP_LIGHTS_DURATION_SEC  

 58     char        *wtod;                                                           
 59     datetime_t  wtod_alarm;                                                      
 60     int         wexd;                                                            
 61     int         dow_sec;                                                         
 62     char        *ltod;                                                           
 63     datetime_t  ltod_alarm;                                                      
 64     int         lrxd;                                                            
 65     int         dol_sec;
*/
