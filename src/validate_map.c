
#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdio.h>
#include "utils.c"
#include <stdlib.h>



void fill_map_data(MapData **data)
{
    int (i), (j);
    (*data)->player_count = 0;
    (*data)->exit_count = 0;
    (*data)->collectible_count = 0;
    i = 0;
    while (i < (*data)->rows)
    {
        j = 0;
        while ((*data)->map[i][j] != '\0')
        {
            if ((*data)->map[i][j] == COLLECTIBLE)
                (*data)->collectible_count++;
            if ((*data)->map[i][j] == PLAYER)
                (*data)->player_count++;
            if ((*data)->map[i][j] == EXIT)
                (*data)->exit_count++;
            j++;
        }
        i++;
    }
}

int validate_map(MapData **data)
{
    int (i), (k), (first_rows_ln);

    if ((*data)->rows == 0)
    {
        printf("Eroor : map empty!\n");
        return (0);
    }
    first_rows_ln = ft_strlen((*data)->map[0]);
    i = 1;
    while (i < (*data)->rows - 1)
    {
        if (ft_strlen((*data)->map[i]) != first_rows_ln)
        {
            printf("Error: Map is not rectangular!\n");
            return (0);
        }
        i++;
    }
    (*data)->cols = first_rows_ln;
    i = 0;
    while (i < (*data)->rows)
    {
        k = 0;
        while (k < first_rows_ln - 1)
        {
            if (i == 0 || i == (*data)->rows - 1 || k == 0 || k == first_rows_ln - 2)
            {
                if ((*data)->map[i][k] != WALL)
                {
                    printf("Error: Map is not enclosed by walls!\n");
                    return (0);
                }
            }
            k++;
        }
        i++;
    }
    if ((*data)->player_count != 1 || (*data)->exit_count != 1 || (*data)->collectible_count < 1)
    {
        printf("invalid mapp!\n");
        return (0);
    }
    return(1);
}

void find_plyr_position(MapData *data, int *x, int *y)
{
    int (i), (j);

    i = 0;
    while (i < data->rows)
    {
        j = 0;
        while (j < data->cols)
        {
            if (data->map[i][j] == PLAYER)
            {
                *x = i;
                *y = j;
                return;
            }
            j++;
        }
        i++;
    }
    *x = -1;
    *y = -1;
}

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

int  check_accessibility(MapData *data)
{
    int (x), (y), (clcbtl_f), (exit_f), (i), (j);
    find_plyr_position(data, &x, &y);
    if (x == -1 || y == -1)
        return (0);
    int **visited = malloc(data->rows  * sizeof(int * ));
    if (!visited)
    {
        printf("Error: Memory allocation failed for visited array!\n");
        return (0);
    }
    i = 0;
    while (i < data->rows)
    {
        j = 0;
        visited[i] = malloc(sizeof(int) * data->cols);
        while (j < data->cols)
        {
            visited[i][j] = 0;
            j++;
        }
        i++;
    }
    clcbtl_f = 0;
    exit_f = 0;
    accessibility(data,x,y,&clcbtl_f,&exit_f,visited);
    if (clcbtl_f != data->collectible_count   || !exit_f)
    {
        printf("Error : unaccessibility (exit OR collectibles)!\n");
        return (0);
    }
    i = 0;
    while (++i < data->rows)
        free(visited[i]);
    free(visited);
    return (1);
}

int read_map(MapData *new_map )
{
    char *s;
    int (fd), (i);

    fd = open("maps/map.ber", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        free(new_map);
        return (0);
    }
    new_map->rows = 0;
    new_map->map = NULL;
    while (1)
    {
        s = get_next_line(fd);
        if (!s)
            break;
        free(s);
        new_map->rows++;
    }
    new_map->map = malloc((new_map->rows + 1) * sizeof(char *));
    if (!new_map->map)
    {
        printf("Err from malloc!\n");
        close(fd);
        free(new_map);
        return (0);
    }
    close(fd);
    fd = open("maps/map.ber", O_RDONLY);
    i = 0;
    while (1)
    {
        s = get_next_line(fd);
        if (!s)
            break;
        new_map->map[i++] = s;
    }
    new_map->map[i] = NULL;
    fill_map_data(&new_map);
    if (!validate_map(&new_map))
    {
        i = -1;
        while (++i < new_map->rows)
            free(new_map->map[i]);
        free(new_map->map);
        free(new_map);
        close(fd);
        return (0);
    }
    if (!check_accessibility(new_map))
    {
        i = -1;
        while (++i < new_map->rows)
            free(new_map->map[i]);
        free(new_map->map);
        free(new_map);
        close(fd);
        return (0);
    }
    return (1);
}

