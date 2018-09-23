/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:31:30 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/23 11:21:06 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_manager	g_manager;

static void	print_heap_header(t_malloc *heap, size_t sizetype)
{
	if (sizetype == TINY)
		ft_putstr("TINY : ");
	else if (sizetype == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_print_addr(heap);
	ft_putchar('\n');
}

static void	print_mallocs(t_malloc *curr, size_t st, int *total, int start)
{
	if (curr)
	{
		if (!curr->is_free)
		{
			if (start)
				print_heap_header(curr, st);
			ft_print_addr(curr->ret_ptr);
			ft_putstr(" - ");
			ft_print_addr(curr->ret_ptr + curr->len);
			ft_putstr(" : ");
			ft_print_unsigned_long(curr->len);
			ft_putstr(" octets\n");
			*total += curr->len;
			start = 0;
		}
		print_mallocs(curr->next, st, total, start);
	}
}

void		show_alloc_mem(void)
{
	int	total;

	total = 0;
	if (g_manager.tiny)
		print_mallocs(g_manager.tiny->head, TINY, &total, 1);
	if (g_manager.small)
		print_mallocs(g_manager.small->head, SMALL, &total, 1);
	if (g_manager.large)
		print_mallocs(g_manager.large, -1, &total, 1);
	ft_putstr("TOTAL: ");
	ft_print_unsigned_long(total);
	ft_putstr(" octets\n");
}
