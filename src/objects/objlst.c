/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:53:28 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/09 08:56:25 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objlst	*objlst_new(t_objtype type, void *obj)
{
	t_objlst	*new;

	new = malloc(sizeof(t_objlst));
	new->type = type;
	new->next = NULL;
	if (type == SPHERE)
		new->obj = (t_sphere *)obj;
	if (type == PLANE)
		new->obj = (t_plane *)obj;
	if (type == CYLINDER)
		new->obj = (t_cylinder *)obj;
	return (new);
}

t_objlst	*objlst_last(t_objlst *head)
{
	t_objlst	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	objlst_add_back(t_objlst **head, t_objlst *newend)
{
	if (!newend)
		return ;
	if (!*head)
	{
		*head = newend;
		return ;
	}
	objlst_last(*head)->next = newend;
}

void	objlst_clear(t_objlst *lst)
{
	t_objlst	*tmp;
	
	while(lst)
	{
		tmp = lst->next;
		free(lst->obj);
		free(lst);
		lst = tmp;
	}
}

void	objlst_print(t_objlst *lst)
{
	while (lst)
	{
		if (lst->type == SPHERE)
		{
			printf("  sphere { center=(%f,%f,%f), r=%f, r**2=%f"
					" colr=[%d,%d,%d]}\n",
					((t_sphere *)lst->obj)->center.x,
					((t_sphere *)lst->obj)->center.y,
					((t_sphere *)lst->obj)->center.z,
					((t_sphere *)lst->obj)->r,
					((t_sphere *)lst->obj)->r_squared,
					((t_sphere *)lst->obj)->colr.r,
					((t_sphere *)lst->obj)->colr.g,
					((t_sphere *)lst->obj)->colr.b);
		}
		lst = lst->next;
	}
}
