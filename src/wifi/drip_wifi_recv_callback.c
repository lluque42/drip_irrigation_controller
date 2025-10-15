/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_recv_callback.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:50:21 by lluque            #+#    #+#             */
/*   Updated: 2025/08/25 23:27:35 by lluque           ###   ########.fr       */
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
	//err_t		status;
	struct pbuf	*reply_pbuf;
	t_drip_conf	*drip_settings;
	
	drip_settings = (t_drip_conf *)arg;
	//drip_wifi_print_pbufchain(p);
	reply_pbuf = drip_exe_client_request(p, drip_settings);
	pbuf_free(p);
	// Using this instead of udp_send(), allows me to reply without a new
	// pcb for the client, and without changing the state of the server's
	// pcb which is actually bound (and we wanna keep it that way).
	udp_sendto(pcb, reply_pbuf, addr, port);
	/*
	status = 
	if (status != ERR_OK)
		printf("[drip_wifi_recv_callback] Couldn't send back (err = %d)\n",
				status);
	// must de-allocate pbuf, otherwise it gets full and refuses connection
	*/
	pbuf_free(reply_pbuf);
}
//printf("[drip_wifi_recv_callback] %d pbufs de-allocated\n", pbuf_free(p));
