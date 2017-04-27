#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <get_next_line.h>

int		create_default(char *table)
{
	char	*path;
	char	name[100];
	char	type[100];
	FILE	*fp;
	int		fd;

	path = ft_strjoin(table, "/");
	path = ft_strjoin(path, "default");
	if ((fd = open(path, O_RDONLY)) >= 0)
		return (0);
	close(fd);
	fp = fopen(path, "ab+");
	while (!ft_strequ(name, "QUIT"))
	{
		printf("Name of Field:\n");
		scanf("%s", name);
		printf("Type: \n");
		scanf("%s", type);
		fprintf(fp, "%s : %s\n", name, type);
	}
	return (1);
}

char	*pull_object(char *table, char *object)
{
	char	*path;
	char	*buff;
	char	*result;
	int		fd;

	path = ft_strjoin(table, "/");
	path = ft_strjoin(path, object);
	result = "";
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	printf("hi\n");
	while (get_next_line(fd, &buff))
	{
		buff = ft_strjoin(buff, "\n");
		result = ft_strjoin(result, buff);
	}
	close(fd);
	return (result);
}

int		add_object(char *table, char *object, char *data)
{
	FILE		*fp;
	int			fd;
	struct stat	buff;
	char		*path;

	if (stat(table, &buff) == -1)
		return (0);
	path = ft_strjoin(table, "/");
	path = ft_strjoin(path, object);
	if ((fd = open(path, O_RDONLY)) >= 0)
		return (0);
	close(fd);
	fp = fopen(path, "ab+");
	fprintf(fp, "%s", data);
	fclose(fp);
	return (1);
}

int		add_table(char *name)
{
	struct stat buff;

	if (stat(name, &buff) == -1)
	{
		mkdir(name, 0700);
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	add_table("students");
	int i = add_object("students", "rmatos", "test");
	char *data = pull_object("students", "rmatos");
	printf("%i:%s", i, data);
	create_default("students");
	return (0);
}
