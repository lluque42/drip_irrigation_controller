/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drip_wifi_print_pbufchain.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:48:05 by lluque            #+#    #+#             */
/*   Updated: 2025/08/16 21:56:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drip.h"

void	drip_wifi_print_pbufchain(struct pbuf *pbuf)
{
	while (pbuf != NULL)
	{
		*((char *)pbuf->payload + pbuf->len - 1) = 0;
		printf("pbuf:\n");
		printf("\tpbuf->payload: %s\n", (char *)pbuf->payload);
		printf("\tpbuf->tot_len: %u\n", pbuf->tot_len);
		printf("\tpbuf->len: %u\n", pbuf->len);
		printf("\tpbuf->type_internal: %u\n", pbuf->type_internal);
		printf("\tpbuf->flags: %x\n", pbuf->flags);
		printf("\tpbuf->ref: %u\n", pbuf->ref);
		printf("\tpbuf->if_idx: %u\n", pbuf->if_idx);
		pbuf = pbuf->next;
	}
}
