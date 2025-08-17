/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_udp_server_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:52:12 by lluque            #+#    #+#             */
/*   Updated: 2025/08/15 12:46:17 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

int	drip_wifi_udp_server_init(t_drip_conf *drip_settings)
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
	udp_recv(pcb, drip_wifi_recv_callback, (void *)drip_settings);
	printf("[drip_wifi_udp_server_init] UDP server correctly initialized\n");
	return (1);
}
