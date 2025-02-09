
#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdio.h>
#include "utils.c"

#define WALL '1'
#define PLAYER 'P'
#define EXIT 'E'
#define COLLECTIBLE 'C'
#define EXPTY '0'

typedef struct s_data
{
   char **map;
   int rows;
   int cols;
   int player_count;
   int exit_count;
   int collectible_count; 
}   MapData;

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
    int (i);
    int first_rows_ln;
    int curnt_rows_ln;

    first_rows_ln = ft_strlen((*data)->map[0]);
    i = 1;
    while (i < (*data)->rows)
    {
        
        curnt_rows_ln = ft_strlen((*data)->map[i]);
        if (curnt_rows_ln != first_rows_ln || (*data)->map[i][0] != '1')
        {
            printf("invalid map!\n");
            return (0);
        }
        i++;
    }
    if ((*data)->player_count != 1 || (*data)->exit_count != 1 || (*data)->collectible_count < 1)
    {
        printf("invalid map!\n");
        return (0);
    }
    return(1);
}


int read_map()
{
    MapData *new_map = malloc(sizeof(MapData));
    char *s;
    int (fd), (i);

    fd = open("maps/map.ber", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return 1;
    }
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
        return (1);
    close(fd);
    fd = open("maps/map.ber", O_RDONLY);
    i = 0;
    while (1)
    {
        s = get_next_line(fd);
        if (!s)
            break;
        new_map->map[i] = s;
        i++;
    }
    new_map->map[i] = NULL;
    fill_map_data(&new_map);
    validate_map(&new_map);
    return 0;
}

