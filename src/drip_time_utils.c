/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_time_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:06:01 by lluque            #+#    #+#             */
/*   Updated: 2025/08/15 01:04:43 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_time_get_epochus_from_current_rtc_datetime(uint64_t *time)
{
	datetime_t	t;

	if (!rtc_get_datetime(&t))
		return (0);
	if (!datetime_to_time(&t, time))	// pico/utils.h
		return (0);
	*time *= 1000000;
	return (1);
}

int	drip_time_get_epochus_from_datetime(uint64_t *time,
										datetime_t some_datetime)
{
	datetime_t	t;

	if (!datetime_to_time(&some_datetime, time))	// pico/utils.h
		return (0);
	*time *= 1000000;
	return (1);
}

// Given the RTC full date time and a -1 masked datetime_t frequency,
// this function returns a pointer to a new datetime_t storing the next
// instant in time that complies with the frequency.
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
