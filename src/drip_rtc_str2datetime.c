/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_rtc_str2datetime.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:06:35 by lluque            #+#    #+#             */
/*   Updated: 2025/08/14 13:36:54 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_rtc_str2datetime(const char *timestr_period_field_delimiter,
							datetime_t *time, int has_dont_cares)
{
	char		*time_str;
	char		*saveptr;	// Internally used by the re-entrant version
							// of strtok()
	char		*field;

	time_str = strdup(timestr_period_field_delimiter);
	
	//printf("[drip_rtc_str2datetime] Parsing '%s'\n", time_str);
	field = strtok_r(time_str, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing yy datetime field\n"), free(time_str), 0);
	errno = 0;
	time->year = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->year > INT_MAX || time->year < INT_MIN)
		return (printf("Invalid value in yy datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->year < 0)
		time->year = -1;
	if (!has_dont_cares && time->year == -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);

	field = strtok_r(NULL, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing mm datetime field\n"), free(time_str), 0);
	errno = 0;
	time->month = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->month > 12 || time->month < INT_MIN)
		return (printf("Invalid value in datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->month < 0)
		time->month = -1;
	if (!has_dont_cares && time->month == -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);
	
	field = strtok_r(NULL, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing dd datetime field\n"), free(time_str), 0);
	errno = 0;
	time->day = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->day > 31 || time->day < INT_MIN)
		return (printf("Invalid value in datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->day < 0)
		time->day = -1;
	if (!has_dont_cares && time->day == -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);
	
	field = strtok_r(NULL, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing dow datetime field\n"), free(time_str), 0);
	errno = 0;
	time->dotw = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->dotw > 6 || time->dotw < INT_MIN)
		return (printf("Invalid value in datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->dotw < 0)
		time->dotw = -1;
	if (!has_dont_cares && time-> dotw== -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);
	
	field = strtok_r(NULL, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing datetime field\n"), free(time_str), 0);
	errno = 0;
	time->hour = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->hour > INT_MAX || time->hour < INT_MIN)
		return (printf("Invalid value in hh datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->hour < 0)
		time->hour = -1;
	if (!has_dont_cares && time->hour == -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);
	
	field = strtok_r(NULL, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing datetime field\n"), free(time_str), 0);
	errno = 0;
	time->min = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->min > INT_MAX || time->min < INT_MIN)
		return (printf("Invalid value in min datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->min < 0)
		time->min = -1;
	if (!has_dont_cares && time->min == -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);
	
	field = strtok_r(NULL, ":", &saveptr);
	if (field == NULL)
		return (printf("Missing ss datetime field\n"), free(time_str), 0);
	errno = 0;
	time->sec = (int)strtol(field, NULL, 10);
	if (errno != 0 || time->sec > INT_MAX || time->sec < INT_MIN)
		return (printf("Invalid value in datetime field\n"), free(time_str), 0);
	// Just to be safe, any negative defaults to don't care value of -1.
	if (time->sec < 0)
		time->sec = -1;
	if (!has_dont_cares && time->sec == -1)
		return (printf("Error: don't care detected\n"), free(time_str), 0);

	free(time_str);
	return (1);
}
