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

char **get_map(t_bsq *bsq, char *filename)
{
    FILE *file = filename ? fopen(filename, "r") : stdin;
    char **map, *line;
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
        fprintf(stdout, "%s\n", bsq->map[i++]);
    return (free_map(bsq->map, bsq->height), free(bsq), 0);
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