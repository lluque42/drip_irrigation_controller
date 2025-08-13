/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_rtc_str2datetime.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:06:35 by lluque            #+#    #+#             */
/*   Updated: 2025/08/13 20:37:11 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

datetime_t drip_rtc_str2datetime(const char *timestr_period_field_delimiter)
{
	datetime_t	time;
	char		*time_str;
	char		*saveptr;	// Internally used by the re-entrant version
							// of strtok()

	time_str = strdup(timestr_period_field_delimiter);
	time.year = atoi(strtok_r(time_str, ".", &saveptr));
	time.month = atoi(strtok_r(NULL, ".", &saveptr));
	time.day = atoi(strtok_r(NULL, ".", &saveptr));
	time.dotw = atoi(strtok_r(NULL, ".", &saveptr));
	time.hour = atoi(strtok_r(NULL, ".", &saveptr));
	time.min = atoi(strtok_r(NULL, ".", &saveptr));
	time.sec = atoi(strtok_r(NULL, ".", &saveptr));
	free(time_str);
	return (time);
}
