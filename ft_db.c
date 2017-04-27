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
	char	cont[100];
	FILE	*fp;
	int		fd;

	cont[0] = 'y';
	cont[1] = '\0';
	path = ft_strjoin(table, "/");
	path = ft_strjoin(path, "default");
	if ((fd = open(path, O_RDONLY)) >= 0)
		return (0);
	close(fd);
	fp = fopen(path, "ab+");
	while (ft_strequ(cont, "y") || ft_strequ(cont, "Y"))
	{
		printf("Name of Field:\n");
		scanf("%s", name);
		printf("Type: \n");
		scanf("%s", type);
		fprintf(fp, "%s : %s\n", name, type);
		printf("continue: [Y/N]?");
		scanf("%s", cont);
	}
	fclose(fp);
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

int		edit(char *table, char *object)
{

}

int		add_object(char *table, char *object)
{
	FILE		*fp;
	int			fd;
	struct stat	buff;
	char		*path;
	char		*def;
	char		*line;
	char		data[100];
	char		**split;

	if (stat(table, &buff) == -1)
		return (0);
	path = ft_strjoin(table, "/");
	path = ft_strjoin(path, object);
	def = ft_strjoin(table, "/");
	def = ft_strjoin(def, "default");
	if ((fd = open(path, O_RDONLY)) >= 0)
		return (0);
	close(fd);
	if ((fd = open(def, O_RDONLY)) < 0)
		return (0);
	fp = fopen(path, "ab+");
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, ' ');
		printf("Enter %s (%s):", split[0], split[2]);
		scanf("%s", data);
		fprintf(fp, "%s : %s\n", split[0], data);
	}
	fclose(fp);
	return (1);
}

int		add_table(char *name)
{
	struct stat buff;

	if (stat(name, &buff) == -1)
	{
		mkdir(name, 0700);
		create_default(name);
		return (1);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	add_table("students");
	add_object("students", "rmatos");
	char *data = pull_object("students", "rmatos");
	printf("%s", data);
	return (0);
}
