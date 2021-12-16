# Проект (Ecole 42) Get_next_line 

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
### [Пример кода](https://github.com/i-galimov/get_next_line/blob/main/get_next_line/My_get_next_line/get_next_line.c)
> *KISS (акроним для «Keep it simple, stupid» — «Делай проще, тупица»)*
```
char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_line(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_save_nextstr(str);
	return (line);
}

********
> ***Корабль не тонет, когда он в воде, он тонет, когда вода в нём.***
> 
![Корабль](https://cdn.pixabay.com/photo/2016/05/02/10/13/ship-1366926_960_720.jpg)
