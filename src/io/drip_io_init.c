/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_io_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:09:07 by lluque            #+#    #+#             */
/*   Updated: 2025/08/11 22:13:34 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_io_init(void)
{
	gpio_init(EV_REL_CTRL);
	gpio_set_dir(EV_REL_CTRL, GPIO_OUT);
	gpio_put(EV_REL_CTRL, 0);
	gpio_init(LIGHTS_REL_CTRL);
	gpio_set_dir(LIGHTS_REL_CTRL, GPIO_OUT);
	gpio_put(LIGHTS_REL_CTRL, 0);
}
