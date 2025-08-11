/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_rtc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:29:02 by lluque            #+#    #+#             */
/*   Updated: 2025/08/11 22:32:30 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_rtc_init(void)
{
	datetime_t	time;

	time.year = 2025;
	time.month = 8;
	time.day = 8;
	time.dotw = 5;
	time.hour = 22;
	time.min = 1;
	time.sec = 0;
	rtc_init();
	if (!rtc_set_datetime(&time))
		while (1)
			printf("Error setting time, I'm hanging myself!\n");
	sleep_ms(1000);
	if (!rtc_running())
		while (1)
			printf("After setting the time the RTC is not running, I'm hanging myself!\n");

}
