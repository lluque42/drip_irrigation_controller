/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_conf_set_next_timeofday_alarm.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:54:58 by lluque            #+#    #+#             */
/*   Updated: 2025/08/16 22:26:36 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

datetime_t	*drip_conf_set_next_timeofday_alarm(datetime_t time_of_day,
												int each_x_days,
												alarm_callback_t callback,
												t_drip_conf *drip_settings,
												alarm_id_t *alarm_id)
{
	datetime_t	*target_datetime;
	time_t		target_abs_time_us;

	target_datetime = drip_time_get_next_instant(time_of_day, each_x_days);
	printf("Next instant for the alarm:\n");
	drip_rtc_datetime_print(*target_datetime);
	if (!drip_time_get_epochus_from_datetime(&target_abs_time_us,
				*target_datetime))
		return (NULL);
	printf("(in epoch usec format: %lld)\n", target_abs_time_us);
	//printf("(now is: %lld)\n", get_rtc_time(&now)));
	*alarm_id = add_alarm_at(target_abs_time_us - drip_time_offset_epoch_us,
							callback,
							(void *)drip_settings,
							0);
	return (target_datetime);
}
