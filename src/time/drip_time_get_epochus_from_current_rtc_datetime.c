/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_time_get_epochus_from_current_rtc_dateti      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:48:55 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 21:52:31 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_time_get_epochus_from_current_rtc_datetime(time_t *time)
{
	datetime_t	t;

	if (!rtc_get_datetime(&t))
		return (0);
	if (!drip_time_get_epochus_from_datetime(time, t))
		return (0);
	return (1);
}
