# Проект (Ecole 42) Get_next_line 

### Содержание
> *Здесь есть все, что нужно, чтобы понять GNL, но недостаточно много, чтобы понять жизнь.*
* [**Моя Версия**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/My_get_next_line)
* [**Пример 1**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line1)
* [**Пример 2**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line2)
* [**Пример 3**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line3)
* [**Пример 4**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/get_next_line4)
* [**Тестер (актуально на декабрь 2021)**](https://github.com/i-galimov/get_next_line/tree/main/get_next_line/gnlTester)
* [**Функция main для проекта**](https://github.com/i-galimov/get_next_line/blob/main/get_next_line/main.c)
---
### [Пример кода](https://github.com/i-galimov/get_next_line/blob/main/get_next_line/My_get_next_line/get_next_line.c)
> *KISS («Keep it simple, stupid» — «Делай проще, тупица»)*
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
```
********
> ***Каждая новая строчка порождает свой мир, который ограничен лишь нашей фантазией, сливаясь воедино строчки рисуют в голове сплетение мультивселенных. (Цитата придумана автором)***
> 
![Книга](https://cdn.pixabay.com/photo/2021/10/14/13/50/book-6709160_1280.jpg)
