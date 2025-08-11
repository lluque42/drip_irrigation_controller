/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_set_ip4_addr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:30:52 by lluque            #+#    #+#             */
/*   Updated: 2025/08/11 22:05:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_wifi_set_ip4_addr(void)
{
	ip_addr_t		addr;
	ip_addr_t		mask;
	ip_addr_t		gw;
	struct netif	*interface;
	int				i;

	// Change the string format to numeric, well ordered (byte-wise) format
	if (!ipaddr_aton(DRIP_IP4_ADDRESS, &addr)
			|| !ipaddr_aton(DRIP_IP4_MASK, &mask)
			|| !ipaddr_aton(DRIP_IP4_DEF_GW, &gw))
	{
		printf("Couldn't ipaddr_aton()\n");
		return (0);
	}
	interface = NULL;
	i = -1;
	while (interface == NULL)
		interface = netif_get_by_index(++i);
	if (interface == NULL)
	{
		printf("No network interface was found\n");
		return (0);
	}
	printf("The original dhcp ip = %d (%s)\n",
			interface->ip_addr,
			ipaddr_ntoa(&interface->ip_addr));
	netif_set_addr(interface, &addr, &mask, &gw);
	printf("The new static ip = %d (%s)\n",
			interface->ip_addr,
			ipaddr_ntoa(&interface->ip_addr));
	return (1);
}
