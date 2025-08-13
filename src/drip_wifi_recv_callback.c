/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_recv_callback.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:50:21 by lluque            #+#    #+#             */
/*   Updated: 2025/08/13 22:56:34 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

/*
 * Weirdnesses:
 *
 * It always seem to deallocate only one pbuf, there appears not to be
 * a "chain". Long messages are broken into different events with single
 * pbuf each time (len == tot_len == 1023 (max)).
 *
 * Even when sending a NUL terminated C-string and receiving the expected
 * len (the strlen + 1), printing with %s some times produces garbage.
 *
 * len and total_len always match.
 */
void	drip_wifi_recv_callback(void *arg,
								struct udp_pcb *pcb,
								struct pbuf *p,
								const ip_addr_t *addr,
								u16_t port)
{
	err_t		status;
	struct pbuf	*reply_buf;
	char		*reply_to_client;

	// Since we transmit chars (a string), here we make sure the NUL char is
	// actually '\0'. I don't know why yet but the same happens in the udp
	// client I made for debugging.
	*((char *)p->payload + p->len - 1) = 0;
	printf("[drip_wifi_recv_callback] %s:%u has sent '%s'\n",
			ipaddr_ntoa(addr), port, p->payload);
	//drip_wifi_print_pbufchain(p);
	reply_to_client = drip_exe_client_request((char *)p->payload);
	pbuf_free(p);
	reply_buf = pbuf_alloc(	PBUF_TRANSPORT,
							strlen(reply_to_client) + 1,
							PBUF_RAM);
	memcpy(reply_buf->payload, (void *)reply_to_client, reply_buf->len);
	// Using this instead of udp_send(), allows me to reply without a new
	// pcb for the client, and without changing the state of the server's
	// pcb which is actually bound (and we wanna keep it that way).
	status = udp_sendto(pcb, reply_buf, addr, port);
	if (status != ERR_OK)
		printf("[drip_wifi_recv_callback] Couldn't send back (err = %d)\n",
				status);
	// must de-allocate pbuf, otherwise it gets full and refuses connection
	pbuf_free(reply_buf);
}
//printf("[drip_wifi_recv_callback] %d pbufs de-allocated\n", pbuf_free(p));
