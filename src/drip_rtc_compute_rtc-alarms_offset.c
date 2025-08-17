/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_rtc_compute_rtc-alarms_offset.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:12:35 by lluque            #+#    #+#             */
/*   Updated: 2025/08/16 22:27:47 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

uint64_t	drip_rtc_compute_rtc_alarms_offset(void)
{
	absolute_time_t	time_since_boot_us;
	time_t			time_rtc_epoch_us;

	hard_assert(drip_time_get_epochus_from_current_rtc_datetime(&time_rtc_epoch_us));
	time_since_boot_us = get_absolute_time();
	drip_time_offset_epoch_us = absolute_time_diff_us(time_since_boot_us,
			time_rtc_epoch_us);
	//printf("time_since_boot_us = %lld\n", time_since_boot_us);
	//printf("time_rtc_epoch_us= %lld\n", time_rtc_epoch_us);
	//printf("time_offset = %lld\n", drip_time_offset_epoch_us);
	return (drip_time_offset_epoch_us);
}
