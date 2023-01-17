/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:41:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/14 19:16:08 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int ac, char **av)
{
	t_param		param;
	t_map		map;

	if (ac < 2)
		ft_error(NULL, "Must provide a map to launch the game");
	map = parse_map(*(av + 1));
	if (!map.map || !*map.map)
		ft_error(NULL, "Parsing of the map failed");
	init_param(&param, map);
	launch_game(&param);
	return (0);
}

void	launch_game(t_param	*param)
{
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	if (!mlx)
		ft_error(param, MLX_ERROR);
	win = mlx_new_window(mlx, param->map.width * NB_PIXEL,
			param->map.len * NB_PIXEL, "Welcome to So Long !");
	if (!win)
		ft_error(param, MLX_ERROR);
	param->mlx = mlx;
	param->win = win;
	init_images(param);
	images_to_map(param);
	mlx_loop_hook(mlx, &handle_live, param);
	mlx_hook(win, 2, (1L << 0), &handle_key, param);
	mlx_hook(win, 17, (1L << 1), &end_game, param);
	mlx_loop(mlx);
}

int	end_game(t_param *param)
{
	int	i;

	if (param)
	{
		if (param->img)
		{
			i = 0;
			while (i < NB_FILES)
			{
				mlx_destroy_image(param->mlx, param->img[i].img);
				++i;
			}
			free(param->img);
		}
		if (param->win)
			mlx_destroy_window(param->mlx, param->win);
		if (param->mlx)
		{
			//mlx_destroy_display(param->mlx);
			free(param->mlx);
		}
		free_map(param->map.map);
	}
	exit(0);
	return (0);
}
