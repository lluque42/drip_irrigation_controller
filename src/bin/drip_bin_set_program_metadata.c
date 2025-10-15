/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_bin_set_program_metadata.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:55:24 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 21:56:31 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_bin_set_program_metadata(void)
{
	bi_decl(bi_program_description("Drip irrigation controller. Designed to \
control one relay for a water electrovalve and a second relay for ornament \
lights. Both may be configured for independent one-time-a-day activation \
and to remain active a period of time. The days between activations is also \
configurable. Any relay may be disabled to stop their future scheduled \
activations. The configuration (get and set) and manual activation \
may be done remotely through the wifi connection with simple UDP messages. \
Water: GPIO22 Lights: GPIO21."));                                                        
	bi_decl(bi_program_url("https://github.com/lluque42/drip_irrigation_controller.git"));
}
