# Отчет

# сборка
```
git clone https://github.com/arechesk/optimization_course.git
cd optimization_course
icl -Wall -Qopenmp ./matMul.cpp -o L3_miss

```

# запуск
- ```./L3_miss 0``` - запуск без оптимизации
- ```./L3_miss 1``` - запуск с оптимизацией 

# Описание performance проблемы
L3-cache miss - промахи кэша 3 уровня.

# Описание решаемой программой задачи
Программа перемножает две целочисленных матрицы размером 2200 на 2200.

# Оптимизация
1. Основная оптимизация для минимизации промахов кэша, транспонировал вторую матрицу.
2. Распараллелил внешний цикл средствами OpenMP.
3. Векторизовал внутренный цикл.

# Результат
После оптимизации производительность выросла в 13 раз.

|**без оптимизации**|**с оптимизацией**|
|--|--|
|![](./img/0.jpg)| ![](./img/1.jpg)|
