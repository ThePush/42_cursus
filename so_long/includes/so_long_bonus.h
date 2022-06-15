/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:52:53 by jsemel            #+#    #+#             */
/*   Updated: 2022/01/19 10:08:52 by jsemel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

// LIBRARIES
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "mlx.h"

// TERMINAL MESSAGES COLORS
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m" 

// ERROR CODES
# define WALLERROR -2
# define CHARERROR -3
# define COUNTERROR -4
# define ROWERROR -5
# define FILERROR -6

// TILE IMAGES PATHES
# define GROUND_0 "assets/ground.xpm"
# define WALL_1 "assets/wall.xpm"
# define COLLECTIBLE_C "assets/collectible.xpm"
# define EXIT_E "assets/exit.xpm"
# define PLAYER_P "assets/P_P.xpm"
# define PLAYER_W "assets/P_W.xpm"
# define PLAYER_W1 "assets/P_W1.xpm"
# define PLAYER_A "assets/P_A.xpm"
# define PLAYER_A1 "assets/P_A1.xpm"
# define PLAYER_S "assets/P_S.xpm"
# define PLAYER_S1 "assets/P_S1.xpm"
# define PLAYER_D "assets/P_D.xpm"
# define PLAYER_D1 "assets/P_D1.xpm"
# define TILESIZE 42

// KEY CODES
# define ESC 65307
# define UP_W 119
# define LEFT_A 97
# define DOWN_S 115
# define RIGHT_D 100
# define ARROW_UP 65362
# define ARROW_LEFT 65361
# define ARROW_DOWN 65364
# define ARROW_RIGHT 65363

/*---------------------------------------------------------------------------*
 * STRUCTURES																 *
 *---------------------------------------------------------------------------*/

// ALL GAME'S DATAS

typedef struct s_game
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*ground;
	void	*wall;
	void	*collectible;
	void	*escape;
	void	*p;
	void	*w;
	void	*a;
	void	*s;
	void	*d;
	void	*n;
	char	**map;
	int		x;
	int		y;
	int		img_width;
	int		img_height;
	int		window_width;
	int		window_height;
	int		collected;
	int		total_collectibles;
	int		input_key;
	int		moves;
	char	*dmove;
	char	*pball;
	int		game_over;
	int		frames;
	int		direction;
	void	*img_direction;
}	t_game;

// MAP CHECK TOOL
typedef struct s_checks
{
	int	p;
	int	e;
	int	c;
}	t_checks;

/*---------------------------------------------------------------------------*
 * ASCII ART																 *
 *---------------------------------------------------------------------------*/

void	print_ascii(void);

/*---------------------------------------------------------------------------*
 * MAP CHECKS UTILS															 *
 *---------------------------------------------------------------------------*/

void	checks_init(t_checks *check);
int		check_chars(char **map);
int		check_rowsnwalls(char **map);
int		check_counts(char **map, t_checks *check);
int		check_file_type(char *file);

/*---------------------------------------------------------------------------*
 * MAP CHECK AND ERROR MESSAGES												 *
 *---------------------------------------------------------------------------*/

int		valid_map(char **map, char *file);

/*---------------------------------------------------------------------------*
 * GAME INITIALISAITON														 *
 *---------------------------------------------------------------------------*/

void	window_size(t_game *game);
void	game_init(t_game *game);
void	count_collectibles(t_game *game);
void	xpm_init(t_game *game);
void	put_img(t_game *game, void *img, int x, int y);
void	xpm_map_load(t_game *game, int y, int x);
void	load_game(t_game *game);

/*---------------------------------------------------------------------------*
 * MAP CREATION																 *
 *---------------------------------------------------------------------------*/

char	**create_matrix(char *map_av);

/*---------------------------------------------------------------------------*
 * HEAP MEMORY LEAKS MANAGEMENT												 *
 *---------------------------------------------------------------------------*/

void	free_matrix(t_game *game);
void	free_game(t_game *game);
int		exit_game(t_game *game);

/*---------------------------------------------------------------------------*
 * MOVES																	 *
 *---------------------------------------------------------------------------*/

void	count_frames(t_game *game);
void	animate_player(t_game *game);
void	update_matrixnplayer(t_game *game, int c);
void	move_up(t_game *game);
void	move_left(t_game *game);
void	move_down(t_game *game);
void	move_right(t_game *game);

/*---------------------------------------------------------------------------*
 * HOOKS																	 *
 *---------------------------------------------------------------------------*/

int		init_resume_window(t_game *game);
int		key_hooks(int keycode, t_game *game);
void	inputs(t_game *game);

#endif
