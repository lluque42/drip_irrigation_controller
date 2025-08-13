/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_udp_server_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:52:12 by lluque            #+#    #+#             */
/*   Updated: 2025/08/13 20:29:20 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_wifi_udp_server_init(void)
{
	struct udp_pcb	*pcb;
	ip_addr_t		ipaddr;

	if (!ipaddr_aton(DRIP_IP4_ADDRESS, &ipaddr))
	{
		printf("[drip_wifi_udp_server_init] Couldn't ipaddr_aton(), ");
		printf("check the DRIP_IP4_ADDRESS setting\n");
		return (0);
	}
	pcb = udp_new_ip_type(IPADDR_TYPE_V4);
	if (pcb == NULL)
	{
		printf("[drip_wifi_udp_server_init] Couldn't allocate a pcb\n");
		return (0);
	}
	if (udp_bind(pcb, &ipaddr, DRIP_IP4_UDP_PORT) != ERR_OK)
	{
		printf("[drip_wifi_udp_server_init] Couldn't bind udp\n");
		return (0);
	}
	udp_recv(pcb, drip_wifi_recv_callback, NULL);
	printf("[drip_wifi_udp_server_init] UDP server correctly initialized\n");
	return (1);
}
