/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:30:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/10 13:06:30 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              DEFINES
*/
# define BLUE       "\033[0;94m"
# define RED        "\033[0;31m"
# define WHITE      "\033[0;37m"

# define ERROR					0
# define NUMS_SORTED			1
# define ERROR_MALLOC_STACK_A	2
# define ERROR_MALLOC_STACK_B	3
# define ERROR_MALLOC_NODE		4
# define ROTATE_UP				0
# define ROTATE_DOWN			1
# define LIST_UNSORTED			0
# define LIST_SORTED			1

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include <unistd.h>    // for write
# include <stdlib.h>    // for exit, malloc
# include <limits.h>	// for INT_MAX && INT_MIN
# include <stddef.h>	// for NULL

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              STRUCT DECLARATIONS
*/
typedef struct s_node
{
	int				value;
	struct s_node	*next;
	size_t			parse;
}					t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	size_t	size;
	char	name;
}			t_stack;

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              FUNCTION PROTOTYPES
*/

void	init_program(int argc, char **argv);

void	ft_error_handler(int error);
void	detect_no_numbers(int argc, char **argv);
void	detect_duplicates_limits_and_order(int argc, char **argv);

t_stack	*ft_new_stack(t_stack *lst);
t_node	*ft_new_node(int number);
void	ft_add_node_front(t_stack *lst, t_node *new);

void	swap(t_stack *lst);
void	push(t_stack *lst_a, t_stack *lst_b);
void	rotate(t_stack *lst);
void	reverse_rotate(t_stack *lst);
void	rotate_both(t_stack *lst_a, t_stack *lst_b);

void	sort_stack(t_stack *lst_a, t_stack *lst_b);
void	sort_triplet(t_stack *lst);
void	sort_under_25(t_stack *lst_a, t_stack *lst_b);
void	sort_over_25(t_stack *lst_a, t_stack *lst_b);

size_t	smallest_nbr_position(t_stack *lst);
int		reverse_or_not_reverse(t_stack *lst, size_t *position);
int		list_is_sorted(t_stack *lst);
void	stack_parsing(t_stack *lst);
t_node	*stack_parsing_aux(t_node *aux_1, t_node *aux_2, int *min, size_t i);

size_t	rotates_to_top(t_stack *lst, size_t min, size_t max);
void	move_to_b(t_stack *lst_a, t_stack *lst_b, size_t a_sz, size_t chunk_sz);
void	move_back_to_stack_a(t_stack *lst_b, t_stack *lst_a);
void	rotate_or_reverse(int direction, t_stack *lst_b);
size_t	biggest_nbr_position(t_stack *lst, size_t *value);

long	ft_atoi(const char *str);
int		ft_isdigit(char c);
void	ft_total_free(t_stack *lst_a, t_stack *lst_b);

#endif