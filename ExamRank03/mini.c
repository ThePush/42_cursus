#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct s_zone{
	int		width;
	int		height;
	char	background;
}t_zone;

typedef struct s_list{
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
}t_list;

void	ft_perror(char *str)
{
	while (*str)
		write(1, str++, 1);
}

char	*get_zone(FILE *file, t_zone *zone)
{
	char	*array = NULL;
	int count = (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background));

	if (count == 3 && zone->width > 0 && zone->width <= 300 && zone->height > 0 && zone->height <= 300)
	{
		array = calloc((zone->width * zone->height + 1), 1);
		array = memset(array, zone->background, zone->width * zone->height);
	}
	return (array);
}

int is_rad(float x, float y, t_list *tmp)
{
	float dist = sqrtf(powf(x - tmp->x, 2.) + powf(y - tmp->y, 2.));

	if (dist <= tmp->radius) {
		if (tmp->radius - dist < 1.)
			return (2);
		return (1);
	}
	return (0);
}

void	get_draw(t_list *tmp, t_zone *zone, char *draw)
{
	int x = 0, y = 0, flag = 0;

	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			flag = is_rad((float)x, (float)y, tmp);
			if ((tmp->type == 'c' && flag == 2) || (tmp->type == 'C' && flag))
				draw[y * zone->width + x] = tmp->color;
			x++;
		}
		y++;
	}
}

bool	get_list(FILE *file, char *draw, t_zone *zone)
{
	int		count = 0;
	t_list	tmp = {0};
	
	while((count = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
	{
		if (!(tmp.radius > 0. && (tmp.type == 'c' || tmp.type == 'C')))
			return (false);
		get_draw(&tmp, zone, draw);
	}
	if (count != -1)
		return (false);
	return (true);
}

void	print_draw(char *draw, t_zone *zone)
{
	for (int i = 0; i < zone->height; i++)
	{
		write(1, draw + i * zone->width, zone->width);
		write(1, "\n", 1);
	}
}

int	main(int ac, char **av)
{
	FILE	*file = NULL;
	char	*draw = NULL;
	int		ret = 1;
	t_zone	zone = {0};

	if (ac != 2)
		ft_perror("Error: argument\n");
	else if (!(file = fopen(av[1], "r")))
		ft_perror("Error: Operation file corrupted\n");
	else if (!(draw = get_zone(file, &zone)))
		ft_perror("Error: Operation file corrupted\n");
	else if (!(get_list(file, draw, &zone)))
		ft_perror("Error: Operation file corrupted\n");
	else
	{
		print_draw(draw, &zone);
		ret = 0;
	}
	if (file)
		fclose(file);
	if (draw)
		free(draw);
	return (ret);
}
