/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_exe_client_request.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:55:23 by lluque            #+#    #+#             */
/*   Updated: 2025/08/13 22:57:17 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

char	*drip_exe_client_request(char *request)
{
	if (request[0] == '1' && strlen(request) == 1)
		gpio_put(EV_REL_CTRL, 1);
	if (request[0] == '2' && strlen(request) == 1)
		gpio_put(LIGHTS_REL_CTRL, 1);
	if (request[0] == '3' && strlen(request) == 1)
		gpio_put(EV_REL_CTRL, 0);
	if (request[0] == '4' && strlen(request) == 1)
		gpio_put(LIGHTS_REL_CTRL, 0);
	return ("ok");
}
