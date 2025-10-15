/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_time_print_datetime.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:03:50 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 21:42:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_time_print_datetime(datetime_t time)
{
	printf("\
			year = %d\n\
			month = %d\n\
			day = %d\n\
			dotw = %d\n\
			hour = %d\n\
			min = %d\n\
			sec = %d\n",
			time.year,
			time.month,
			time.day,
			time.dotw, 
			time.hour,
			time.min,
			time.sec);
}
