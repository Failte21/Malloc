/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:40:55 by lsimon            #+#    #+#             */
/*   Updated: 2018/09/11 09:44:04 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_manager	*manager;

static void	print_mallocs(t_malloc	*curr, int *total)
{
	if (curr)
	{
		if (!curr->is_free)
		{
			printf("%p - %p : %zu octets\n", curr->ret_ptr, curr->ret_ptr + curr->len, curr->len);
			*total += curr->len;
		}
		print_mallocs(curr->next, total);
	}
}

static void	print_heap(t_stock *heap, char *title, int *total)
{
	if (heap)
	{
		printf("%s : %p\n", title, heap);
		print_mallocs(heap->head, total);
		print_heap(heap->next, title, total);
	}
}

static void	print_large_heap(t_malloc *heap, int *total)
{
	if (heap)
	{
		printf("%s : %p\n", "LARGE", heap);
		printf("%p - %p : %zu octets\n", heap->ret_ptr, (void *)heap + heap->len, heap->len);
		*total += heap->len;
		print_large_heap(heap->next, total);
	}
}

void		show_alloc_mem(void)
{
	int	total;

	total = 0;
	if (manager)
	{
		print_heap(manager->tiny, "TINY", &total);
		print_heap(manager->small, "SMALL", &total);
		print_large_heap(manager->large, &total);
		printf("TOTAL: %d octets\n", total);
	}
}