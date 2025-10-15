/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_time_get_epochus_from_datetime.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:45:17 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 21:48:45 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_time_get_epochus_from_datetime(time_t *time,
										datetime_t some_datetime)
{
	if (!datetime_to_time(&some_datetime, time))	// pico/utils.h
		return (0);
	*time *= 1000000;
	return (1);
}
