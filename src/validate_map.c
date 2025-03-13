
#include "../includes/so_long.h"




int validate_file_extension(char *file)
{
    char **fileval;

    fileval = ft_split(file, '.');
    if (ft_strcmp(fileval[1] , "ber") != 0)
    {
        printf("Error : the map must be .ber!\n");
        free_split(fileval,ft_strlen_2d(fileval));
        return (0);
    }
    free_split(fileval,ft_strlen_2d(fileval));
    return (1);
}

int count_map_row(char *file)
{
    char *s;
    int (fd), (rows);

    rows = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (-1);
    }
    while (1)
    {
        s = get_next_line(fd);
        if (!s)
            break;
        free(s);
        rows++;
    }
    close(fd);
    return (rows);
}

char **allocate_and_read_map(int rows, char *file)
{
    int (fd), (i);
    char *s, **map;

    map = malloc((rows + 1) * sizeof(char *));
    if (!map)
    {
        printf("Err from malloc!\n");
        return (NULL);
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf ("Error : opening file!\n");
        return (NULL);
    }
    i = 0;
    while (1)
    {
        s = get_next_line(fd);
        if (!s)
            break;
        map[i++] = s;
    }
    map[i] = NULL;
    close(fd);
    return (map);
}
int read_map(MapData *new_map , char *file)
{
    int i;

    if (!validate_file_extension(file))
        return (0);
    
    new_map->rows = count_map_row(file);
    if (new_map->rows <= 0)
        return (0);
    
    new_map->map = allocate_and_read_map(new_map->rows, file);
    if (!new_map->map)
        return (0);

    fill_map_data(&new_map);

    if (!validate_map(&new_map) || !check_accessibility(new_map))
    {
        i = -1;
        while (++i < new_map->rows)
            free(new_map->map[i]);
        free(new_map->map);
        return (0);
    }
    return (1);
}