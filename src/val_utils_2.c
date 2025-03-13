

#include "../includes/so_long.h"

void accessibility(MapData *data, int x, int y, int *colectibles_f, int *exit_f, int **visited)
{
    if (x < 0 || x >= data->rows || y < 0 || y >= data->cols)
        return;
    if (visited[x][y] || data->map[x][y] == WALL)
        return;
    visited[x][y] = 1;

    if (data->map[x][y] == COLLECTIBLE)
        (*colectibles_f)++;
    if (data->map[x][y] == EXIT)
        (*exit_f)++;
    accessibility(data,x + 1, y, colectibles_f, exit_f, visited);
    accessibility(data,x - 1, y, colectibles_f, exit_f, visited);
    accessibility(data,x, y + 1, colectibles_f, exit_f, visited);
    accessibility(data,x, y - 1, colectibles_f, exit_f, visited);
}

int **allocate_visited_array(MapData *data)
{
    int (i), (j);
    int **visited = malloc(data->rows  * sizeof(int *));
    if (!visited)
    {
        printf("Error: Memory allocation failed!\n");
        return (0);
    }
    i = 0;
    while (i < data->rows)
    {
        j = 0;
        visited[i] = malloc(sizeof(int) * data->cols);
        if (!visited[i])
            printf("Error: Memory allocation failed!\n");
        while (j < data->cols)
            visited[i][j++] = 0;
        i++;
    }
    return (visited);
}

int  check_accessibility(MapData *data)
{
    int (clcbtl_f), (exit_f), (i);
    int **visited;

    visited = allocate_visited_array(data);
    if (!visited || data->player_x == -1 || data->player_y == -1)
        return (0);
    clcbtl_f = 0;
    exit_f = 0;
    accessibility(data,data->player_x,data->player_y,&clcbtl_f,&exit_f,visited);
    i = -1;
    while (++i < data->rows)
        free(visited[i]);
    free(visited);
    if (clcbtl_f != data->collectible_count   || !exit_f)
    {
        printf("Error : unaccessibility (exit OR collectibles)!\n");
        return (0);
    }
    return (1);
}