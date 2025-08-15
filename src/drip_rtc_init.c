/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_rtc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:29:02 by lluque            #+#    #+#             */
/*   Updated: 2025/08/14 22:06:27 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_rtc_init(void)
{
	datetime_t		time;
	absolute_time_t	time_since_boot_us;
	uint64_t		time_rtc_epoch_us;

	hard_assert(drip_rtc_str2datetime(DRIP_BUILD_TIME, &time, 0));
	//drip_rtc_datetime_print(time);
	rtc_init();
	hard_assert(rtc_set_datetime(&time));
	sleep_ms(500);
	if (!rtc_running())
	{
		printf("After setting the time the RTC is not running\n");
		return (0);
	}
	hard_assert(drip_time_get_epochus_from_current_rtc_datetime(&time_rtc_epoch_us));
	time_since_boot_us = get_absolute_time();
	time_offset_epoch_us = absolute_time_diff_us(time_since_boot_us,
			time_rtc_epoch_us);
	printf("time_since_boot_us = %lld\n", time_since_boot_us);
	printf("time_rtc_epoch_us= %lld\n", time_rtc_epoch_us);
	printf("time_offset = %lld\n", time_offset_epoch_us);
	return (1);
}
