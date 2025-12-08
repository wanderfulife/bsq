#include "bsq.h"

int min(int a, int b, int c)
{
    if (a < b && a < c)
        return (a);
    return (b < c ? b : c);
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

void free_map(char **map, int height)
{
    int i = 0;
    while (i < height)
        free(map[i++]);
    free(map);
}

int invalid(char c)
{
    return (c < 32 || c > 126);
}

char **get_map(t_bsq *bsq, char *filename)
{
    FILE *file = filename ? fopen(filename, "r") : stdin;
    char **map, *line = NULL;
    size_t len = 0;
    int i = 0;

    if (!file || fscanf(file, "%d %c %c %c\n", &bsq->height, &bsq->empty, &bsq->obstacle, &bsq->full) != 4 || bsq->height <= 0)
        return (filename && file && fclose(file), NULL);
    if (!(map = malloc(sizeof(char *) * bsq->height)))
        return (filename && fclose(file), NULL);
    while (i < bsq->height)
    {
        line = NULL;
        if (getline(&line, &len, file) == -1)
            return (free_map(map, i), filename && fclose(file), NULL);
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        map[i++] = line;
    }
    bsq->width = ft_strlen(map[0]);
    return (filename && fclose(file), map);
}

int check_map(t_bsq *bsq)
{
    int i = 0, j;

    if (!bsq->map || bsq->height < 1 || bsq->width < 1)
        return (0);
    if (invalid(bsq->empty) || invalid(bsq->full) || invalid(bsq->obstacle))
        return (0);
    if (bsq->empty == bsq->full || bsq->empty == bsq->obstacle || bsq->full == bsq->obstacle)
        return (0);
    while (i < bsq->height)
    {
        if (bsq->width != ft_strlen(bsq->map[i]))
            return (0);
        j = 0;
        while (j < bsq->width)
        {
            if (bsq->map[i][j] != bsq->empty && bsq->map[i][j] != bsq->obstacle)
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int process_file(char *filename)
{
    int i = 0;
    t_bsq *bsq = malloc(sizeof(t_bsq));
    if (!bsq)
        return (1);
    
    if (!(bsq->map = get_map(bsq, filename)) || !check_map(bsq) || solve_bsq(bsq))
    {
        if (bsq->map)
            free_map(bsq->map, bsq->height);
        return (free(bsq), fprintf(stderr, "map error\n"), 1);
    }
    while (i < bsq->height)
        fprintf(stdout,"%s\n", bsq->map[i++]);
    return (free_map(bsq->map, bsq->height), free(bsq), 0);
}

int solve_bsq(t_bsq *bsq)
{
    int max_i = 0;
    int max_j = 0;
    int max_size = 0;
    int i = 0, j;

    int **dp = malloc(sizeof(int *) * bsq->height);
    if (!dp)
        return (1);

    while (i < bsq->height)
    {
        dp[i] = malloc(sizeof(int *) * bsq->width);
        if (!dp[i])
            return (free_map((char **)dp, i), 1);
        
        j = 0;
        while (j < bsq->width)
        {
            if (bsq->map[i][j] == bsq->obstacle)
                dp[i][j] = 0;
            else if (i == 0 && j == 0)
                dp[i][j] = 1;
        }
    }
}

int main(int ac, char **av)
{
    int i = 1;
    if (ac == 1)
        return (process_file(NULL), 0);
    while (i < ac)
    {
        process_file(av[i]);
        if (i < ac - 1)
            fprintf(stdout, "\n");
        i++;
    }
    return (0);
}