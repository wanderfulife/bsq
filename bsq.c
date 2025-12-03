#include "bsq.h"

void	free_map(char **map, int height)
{
	int i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int	min(int a, int b, int c)
{
	if (a < b && a < c)
		return (a);
	return (b < c ? b : c);
}

char	**get_map(t_bsq *bsq, char *filename)
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

int	check_map(t_bsq *bsq)
{
	int i = 0, j;

	if (!bsq->map || bsq->height < 1 || bsq->width < 1 ||
		bsq->empty < 32 || bsq->empty > 126 || bsq->full < 32 ||
		bsq->full > 126 || bsq->obstacle < 32 || bsq->obstacle > 126 ||
		bsq->empty == bsq->full || bsq->empty == bsq->obstacle ||
		bsq->full == bsq->obstacle)
		return (0);
	while (i < bsq->height)
	{
		if (ft_strlen(bsq->map[i]) != bsq->width)
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

int	solve_bsq(t_bsq *bsq)
{
	int max_i = 0, max_j = 0, max_size = 0, **dp, i = 0, j;

	if (!(dp = malloc(sizeof(int *) * bsq->height)))
		return (1);
	while (i < bsq->height)
	{
		if (!(dp[i] = malloc(sizeof(int) * bsq->width)))
			return (free_map((char **)dp, i), 1);
		j = 0;
		while (j < bsq->width)
		{
			dp[i][j] = (bsq->map[i][j] == bsq->obstacle) ? 0 :
				(i == 0 || j == 0) ? 1 :
				1 + min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]);
			if (dp[i][j] > max_size)
				(max_size = dp[i][j], max_i = i, max_j = j);
			j++;
		}
		i++;
	}
	i = max_i - max_size + 1;
	while (i <= max_i)
	{
		j = max_j - max_size + 1;
		while (j <= max_j)
			bsq->map[i][j++] = bsq->full;
		i++;
	}
	return (free_map((char **)dp, bsq->height), 0);
}

int	process_file(char *filename)
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

int	main(int ac, char **av) {
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