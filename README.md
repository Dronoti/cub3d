# Графический проект "Cub3D"

### Описание проекта
Данный проект основан на технологии [рейкастинга](https://ru.wikipedia.org/wiki/Ray_casting) -
это метод преобразования ограниченной формы данных
(карта этажа) в трёхмерную проекцию с помощью трассировки
лучей из точки обзора в объём обзора. На основе входного файла,
в котором содержатся пути к текстурам, цвета пола и потолка,
а также сама двумерная карта этажа, необходимо создать игровой
движок - аналог Wolfenstein 3D engine by ID Software.

Основная идея заключается в следующем: для каждой вертикальной полосы экрана
(координаты x) отправляется луч, который начинается в точке местоположения
игрока и имеет определенное направление, в зависимости от направления взгляда игрока
и от координаты x экрана. Затем этот луч начинает двигаться вперед по 2D-карте,
пока не столкнется с квадратом карты, который является стеной. После этого,
рассчитывается расстояние от этой точки попадания до игрока. На основе этого
расстояния определяется насколько высоко эта стена должна быть отрисована на экране:
чем дальше стена, тем она меньше и наоборот.

### Основные используемые переменные
**Библиотека mlx**
* WIN_WIDTH - ширина окна/изображения
* WIN_HEIGHT - высотка окна/изображения
* all->mlx.mlx - указатель на mlx (идентификатор инициализированной библиотеки mlx)
* all->mlx.win - указатель на открытое окно mlx (идентификатор открытого окна)
* all->mlx.img - указатель на изображение (идентификатор изображения)
* all->mlx.addr - указатель на начало области памяти, где хранится изображение
* all->mlx.bitspp - количество битов для представления цвета одного пикселя (глубина цвета). Как правило, 32 бита или 4 байта (32 / 8)
* all->mlx.line_l - количество байтов для одной строки изображения в памяти
* all->mlx.end - сообщает нужно ли хранить цвет пикселя в изображении (возвращает 0 или 1). Как правило, 0, т.к. цвет пикселя устанавливаем позже.

**Карта этажа**
* all->map.map - двумерный массив char для хранения символов карты
* all->map.height - количество строк карты
* all->map.no - указатель на начало области памяти, где хранится изображение для северной стороны текстур
* all->map.so - указатель на начало области памяти, где хранится изображение для южной стороны текстур
* all->map.we - указатель на начало области памяти, где хранится изображение для западной стороны текстур
* all->map.ea - указатель на начало области памяти, где хранится изображение для восточной стороны текстур
* all->map.f - цвет пола
* all->map.с - цвет потолка
* all->map.x - клетка карты по координате x откуда исходит луч
* all->map.y - клетка карты по координате y откуда исходит луч

**Игрок**
* all->plr.pos.x - позиция игрока на карте по х координате
* all->plr.pos.y - позиция игрока на карте по y координате
* all->plr.dir.x - горизонтальное направление взгляда игрока (1 - взгляд на восток, -1 - взгляд на запад)
* all->plr.dir.y - вертикальное направление взгляда игрока (1 - взгляд на юг, -1 - взгляд на север)
* all->plane.x - плоскость камеры игрока по координате x
* all->plane.y - плоскость камеры игрока по координате y

**Рейкастинг**
* FOV (Field  of view) - поле зрения игрока (угол обзора)
* SPD_P - скорость перемещения игрока
* SPD_R - скорость вращения игрока
* camera_x - координата x на плоскости камеры, для вычисления направления луча
* (-1 - самая левая точка экрана, 0 - середина, 1 -правая)
* all->ray.i - номер луча (номер вертикальной линии для ее отрисовки)
* all->ray.dir.x - направление луча по координате x
* all->ray.dir.y - направление луча по координате y
* all->ray.delta.x - шаг пересечения луча с клетками по координате x
* all->ray.delta.y - шаг пересечения луча с клетками по координате y
* all->ray.side.x - расстояние, которое должен пройти луч до первого столкновения с клеткой по координате x (с горизонтальной линией)
* all->ray.side.y - расстояние, которое должен пройти луч до первого столкновения с клеткой по координате y (с вертикальной линией)
* all->ray.step_x - определяет в каком направлении двигаться по оси x (либо 1, либо -1). Переход осуществляется сразу на одну клетку
* all->ray.step_y - определяет в каком направлении двигаться по оси y (либо 1, либо -1). Переход осуществляется сразу на одну клетку
* all->ray.vert_hit - сообщает было ли столкновение с горизонтальной линией y (1) или с вертикальной x (0)
* wall_x - точное значение места удара по стене
* scale - насколько увеличить координаты текстуры по y для каждого пикселя экрана

**Параметры стены**
* all->wall.height - высота стены
* all->wall.top - координата/точка начала стены по y
* all->wall.tex_x - координата текстуры по x
* all->wall.tex_y - координата текстуры по y
* all->wall.dist - расстояние/длина луча до стены

### Используемые функции сторонней графической библиотеки mlx
* mlx_init() - связывает программное обеспечение и дисплей (инициализирует библиотеку mlx)
* mlx_new_window() - создает новое окно на экране
* mlx_new_image() - создает новый образ изображения в памяти
* mlx_get_data_addr() - возвращает информацию о созданном изображении для его последующего изменения
* mlx_put_image_to_window() - выводит изображение на экран
* mlx_destroy_image() - уничтожает созданное изображение
* mlx_destroy_window() - уничтожает созданное окно
* my_mlx_pixel_put() - определяет адрес пикселя изображения и записывает в него заданный цвет
* mlx_xpm_file_to_image() - создает новый образ изображения в памяти на основе файла xpm