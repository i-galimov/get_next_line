# Проект GNL (Get_next_line) - Ecole 42

### Содержание
> *Здесь есть все, что нужно*
* [**Моя Версия**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/My_get_next_line)
* [**Пример 1**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line1)
* [**Пример 2**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line2)
* [**Пример 3**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line3)
* [**Пример 4**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line4)
* [**Тестер (актуально на декабрь 2021)**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/gnlTester)
* [**Функция main для проекта**](https://github.com/i-galimov/get_next_line/blob/main/get_next_line/main.c)
---
### [Пример кода](https://github.com/i-galimov/school21/blob/main/rev_print.c) 
> *Это не баг, а фича*
```
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}

char *ft_revprint(char *str)
{
	int	count;
	
	count = ft_strlen(str);
	while(count > 0)
	{
		write(1, &str[count - 1], 1);
		count--;
	}
	write(1, "\n", 1);
	return (str);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		write(1, "\n", 1);
	else
		ft_revprint(argv[1]);
}
```
********
> ***Корабль не тонет, когда он в воде, он тонет, когда вода в нём.***
> 
![Корабль](https://cdn.pixabay.com/photo/2016/05/02/10/13/ship-1366926_960_720.jpg)
