/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_time_rtc_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:29:02 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 21:43:07 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_time_rtc_init(void)
{
	datetime_t		time;

	hard_assert(drip_time_str2datetime(DRIP_BUILD_TIME, &time, 0));
	//drip_rtc_datetime_print(time);
	rtc_init();
	hard_assert(rtc_set_datetime(&time));
	sleep_ms(500);
	if (!rtc_running())
	{
		printf("After setting the time the RTC is not running\n");
		return (0);
	}
	drip_time_offset_epoch_us = drip_time_compute_rtc_abs_offset();
	return (1);
}
