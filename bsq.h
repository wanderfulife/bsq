#ifndef BSQ_H
#define BSQ_H
#include <stdio.h>
#include <stdlib.h>


typedef struct s_bsq {
    int     height;
    int     width;
    char    empty;
    char    full;
    char    obstacle;
    char    **map;
} t_bsq;

// Function declarations
void	free_map(char **map, int height);
int		ft_strlen(char *s);
int		min(int a, int b, int c);
int		process_file(char *filename);
char	**get_map(t_bsq *bsq, char *filename);
int		check_map(t_bsq *bsq);
int		solve_bsq(t_bsq *bsq);

#endif

