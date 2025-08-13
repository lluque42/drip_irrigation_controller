/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:24:00 by lluque            #+#    #+#             */
/*   Updated: 2025/08/13 21:44:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

// This function should work for either the first connection or to re-connect
// after losing the link to the access point.
int	drip_wifi_init(void)
{
	int	result;

	// This enables the Wi-Fi in Station mode such that connections
	// can be made to other Wi-Fi Access Points
	cyw43_arch_enable_sta_mode();

	// Attempting a connection
	result = cyw43_arch_wifi_connect_timeout_ms(DRIP_WIFI_SSID,
			DRIP_WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK,
			DRIP_WIFI_CONNECT_TIMEOUT_MS);
	if (result != 0)
		return (printf("[drip_wifi_init] Couldn't connect to WiFi. Error: %d\n",
				result), 0);
	else
		wifi_connected = 1;

	// Setting the static IP address
	if (!drip_wifi_set_ip4_addr())
	{
		printf("[drip_wifi_init] Couldn't set IPv4 address,\
				shutting down the connection\n");
		// This also closes every connection
		cyw43_arch_disable_sta_mode();
		return (0);
	}
	// Starting the server
	if (!drip_wifi_udp_server_init())
	{
		printf("[drip_wifi_init] Couldn't initialized UDP server,\
				shutting down the connection\n");
		// This also closes every connection
		cyw43_arch_disable_sta_mode();
		return (0);
	}
	return (1);
}
