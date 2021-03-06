/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:00:55 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 09:00:56 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

_Bool	parse_scene(t_scene_manager *manager)
{
	_Bool	result;

	if (!manager)
		return (FALSE);
	result = TRUE;
	init_checklist(manager);
	while (result && get_next_line(manager->fd, &manager->line) > 0)
	{
		if (!(manager->parts = ft_strsplit(manager->line, ' ')))
			result = FALSE;
		manager->option = *manager->line ? parse_field_option(*manager->parts)
						: option_separator;
		if (!result || manager->option == wrong_option_field
			|| !parse_option(manager))
			result = FALSE;
		manager->parts ? ft_astr_del(manager->parts) : FALSE;
		ft_strdel(&manager->line);
		if (manager->option == option_separator)
			break ;
	}
	result = is_valid_checklist(manager);
	return (result);
}
