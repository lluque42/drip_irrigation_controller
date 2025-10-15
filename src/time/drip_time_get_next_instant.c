/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_time_get_next_instant.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:49:52 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 22:16:23 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

datetime_t	*drip_time_get_next_instant(datetime_t freq, int each_x_days)
{
	datetime_t	*rtc_time;
	time_t 		t;	// epoch seconds

	rtc_time = calloc(1, sizeof(datetime_t));
	hard_assert(rtc_time != NULL);
	hard_assert(rtc_get_datetime(rtc_time));
	if ((freq.hour < rtc_time->hour)
		|| (freq.hour == rtc_time->hour
				&& freq.min < rtc_time->min)
		|| (freq.hour == rtc_time->hour
				&& freq.min == rtc_time->min
				&& freq.sec <= rtc_time->sec))
	{
		datetime_to_time(rtc_time, &t);
		//t += 24 * 60 * 60;
		t += 24 * each_x_days * 60 * 60;	// If not today...
		time_to_datetime(t, rtc_time);
	}
	rtc_time->hour = freq.hour;
	rtc_time->min = freq.min;
	rtc_time->sec = freq.sec;
	return (rtc_time);
}
