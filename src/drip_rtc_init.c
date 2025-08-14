/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_rtc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:29:02 by lluque            #+#    #+#             */
/*   Updated: 2025/08/14 10:21:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_rtc_init(void)
{
	datetime_t	time;
	
	hard_assert(drip_rtc_str2datetime(DRIP_BUILD_TIME, &time, 0));
	//drip_rtc_datetime_print(time);
	rtc_init();
	if (!rtc_set_datetime(&time))
	{
		printf("Error setting time\n");
		return (0);
	}
	sleep_ms(1000);
	if (!rtc_running())
	{
		printf("After setting the time the RTC is not running\n");
		return (0);
	}
	return (1);
}
