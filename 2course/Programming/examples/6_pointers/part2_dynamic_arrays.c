/*
    Основной материал по основам указателей в C расположен по адресу: https://github.com/posgen/OmsuMaterials/wiki/Variables-and-ponters:-basic

    Желательно ознакомиться с файлом part1_pointers.c в той же директории, что и данный файл.

    Для повторения: массив - это набор элементов, к каждому из которых имеется доступ по индексу.
    В языке C массиивы являются:
        1) типизированными, то есть могут содержать в себе только элементы одного конкретного типа (int, float, double, char);
        2) непрерывно расположенными в памяти. Гарантируется, что все элементы массива идут друг за другом в некотором блоке оперативной памяти.

    Пункт 2) позволяет использовать указатели для работы с масивами.
    Рассмотрим статический массив целых чисел из 5 элементов:
        int arr[] = {1, 3, 5, 7, 9};

    Графически расположение этого массива в памяти можно представить вот так (для тех, кому лень было статью выше открывать):
        < 1 >< 3 >< 5 >< 7 >< 9 >
    Здесь треугольные скобки означают блок памяти, необходимый для хранения переменной определённого типа. В примере - тип int.
    То есть - это не синтаксис языка, это просто ассоциативная картинка. И она как раз показывает тот факт, что все
    элементы расположены в памяти последовательно. Размер конкретного блока равен размеру переменной конкретного типа.

    Каждый отдельный элемент массива - arr[0], arr[1], arr[2] - по сути является отдельной переменной, поэтому
    у него можно получить адрес. А раз можно получить адрес, значит можно сохранить его в указатель
        int *p_arr;
        p_arr = &arr[1];

    Здесь мы записываем адрес второго (arr[1]) элемента массива в указатель p_arr. Теперь всё выглядит примерно так:
        < 1 >< 3 >< 5 >< 7 >< 9 >
             ^
             |
           p_arr

    Через указатель p_arr и его разыменование можно изменить значение конкретного элемента массива, но всё это уже было (pointers.c).

    Следующая операция, применяемая к указателям - прибавление целого числа (как положительного, так и отрицательного).
    Например:
        p_arr++; // или p_arr += 1;

    В этом случае адрес указателя меняется путём прибавления к нему sizeof(int) байт. И p_arr теперь указывает на
    третий элемент массива:
        < 1 >< 3 >< 5 >< 7 >< 9 >
                  ^
                  |
                p_arr

    При прибавлении отрицательного числа (или вычитании положительного), адрес указателя уменьшается на
    соотвествующее число байт. Так
        p_arr -= 2; // отнимаем целое число 2 от значения указателя
    приводит к тому, что в p_arr хранится адрес первого элемента массива arr:
        < 1 >< 3 >< 5 >< 7 >< 9 >
        ^
        |
      p_arr

    Здесь стоит добавить, что за изменением адресов памяти должен следить только автор программы, сам язык
    не проверяет - содержит ли указатель корректный адрес или нет.

    Далее следует следующий факт: переменная статического массива (в рассматриваемом случае - arr) по сути
    является постоянным (в смысле - неизменным) указателем на первый элемент массива. То есть:
        < 1 >< 3 >< 5 >< 7 >< 9 >
        ^
        |
       arr

    Это легко подтверждается, попыткой вывести адрес:
        printf("The address of arr is %p", arr);
        printf("The address of first element is %p\n", &arr[0]);
    Обе функции printf выведут один и тот же адрес.

    То, что arr является неизменным указателем на первый элемент массива, приводит к следующщему сакральному знанию,
    почему индексы элементов начинаются с нуля: фактически индекс является смещением на определённое количество байт
    относительно первого элемента массива.

    Операция индексации применима и к указателю:
        p_arr[0];
        p_arr[1];
    Причём, сам язык не делает никаких проверок - действительно ли ваш указатель связан с массивом или нет.
    Индексация и разыменование указателей связаны следующим образом:
        p_arr[1] это *(p_arr + 1) // что означает прибавление целого числа к указателю - смотреть выше.

    ************************************************************

    Динамические массивы.

    Статические массивы - это неплохо, но не всегда возможно определить - какого размера понадобится массив под конкретную задачу.
    Для решения этой проблемы, язык С предоставляет функции для динамического выделения блоков памяти. Данные функции
    объявлены в заголовочном файле <stdlib.h>. Основные из них:
        malloc и calloc
    Они объявляются как:
        void* malloc(size_t size) - функция возращает блок памяти размером size
            (size_t - специальный тип для хранения размеров размеров, обычно безнаковое целое - unsigned int или аналог)

        void* calloc(size_t num, size_t size) - функция возращает блок памяти размером num * size, при
            этом весь возращаемый блок будет обнулён (все биты устанавливаются в нуль)

    Освобождается память (удаляется ранее выделенный блок памяти) с помощью функции free:
        void free(void* ptr) - в неё передаётся указатель, который был выделен с помощью функций malloc/realloc.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // используется для генератора псевдослучайных чисел

void examples_with_static_arrays(void)
{
    // Определяем статический массив и указатель на int
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, *p_int;

    // записываем в p_int адрес пятого элемента
    p_int = &arr[4];

    // печатаем пятый элемент через указатель и разыменование
    printf("Current value of p_int is %d\n", *p_int);

    // печатаем седьмой элемент через указатель и индексацию
    // p_int[2] - сдвиг вправо на 2 позиции относительно начального положения p_int
    printf("Current value of p_int[2] is %d\n", p_int[2]);

    // печатаем четвёртый элемент через указатель и индексацию. Да, индекс может быть отрицательным
    printf("Current value of p_int[-1] is %d\n", p_int[-1]);
}

// Передаём в функцию 2 аргумента: размер массива типа float и размер массива типа int
void examples_of_dynamic_arrays(unsigned int float_arr_size, unsigned int int_arr_size)
{
    // Для работы с динамическим массивом необходим указатель
    float *f_arr;
    int *i_arr1, *i_arr2;
    unsigned int index;

    /*
        Выделяем блок памяти под массив из float_arr_size элементов.
        Нужное количество памяти вычисляется по формуле:
            кол_во_элементов * размер_типа_элемента

        Функция malloc просто возращает блок памяти нужного размера. Вообще говоря,
        этот блок может быть заполнен какими-то данными (зависит от ОС).

        В случае, если память выделить невозможно, функция возращает нулевой указатель - NULL.
        Под "нулевым" понимается адрес, который гарантированно не указывает ни на одну ячейку памяти.
        Вообще говоря, после каждого выделения необходима проверка того, была ли реально выделена память
    */
    f_arr = (float*) malloc(float_arr_size * sizeof(float));
    if ( f_arr == NULL ) {
        perror("Error with memory initialization"); // печатаем сообщение в стандартный поток для ошибок
        return; // выходим принудительно из функции
    }

    // Аналогичное выделение динамического массива под массив типа int
    i_arr1 = (int*) malloc(int_arr_size * sizeof(int));
    if ( i_arr1 == NULL ) {
        free( f_arr ); // если до сюда дошло, то массив под f_arr был выделен успешно, поэтому надо его удалить из памяти
        perror("Error with memory initialization"); // печатаем сообщение в стандартный поток для ошибок
        return; // выходим принудительно из функции
    }

    /*
        calloc отличается от malloc 2-мя вещами:
            1) синтаксис: calloc принимает два аргумента - количество элементов и размер каждого из них
            2) calloc инициализирует всю выделенную память нулями:
                то есть,
                    i_arr2[0] == 0
                    i_arr2[1] == 0
                    i_arr2[2] == 0
                    и так далее ...

                В случае malloc - не факт, что i_arr1[0] или i_arr1[1] - будут равны нулю. Возможно, там
                останутся другие значения (ещё раз, записит от выделения памяти в ОС).
    */
    i_arr2 = (int*) calloc(int_arr_size, sizeof(int));
    if ( i_arr2 == NULL ) {
        free( f_arr );
        free( i_arr1 );
        perror("Error with memory initialization"); // печатаем сообщение в стандартный поток для ошибок
        return; // выходим принудительно из функции
    }


    // заполняем и печатаем выше выделенные массивы значениями
    printf("\nFloat array:\n");
    for (index = 0; index < float_arr_size; ++index) {
        f_arr[index] = (float) rand() / RAND_MAX; // используется явное приведение к типу float - (float) - для того,
                                                  // чтобы операция деления была не целочисленной
        printf("%lf ", f_arr[index]);
    }

    printf("\nInt arrays:\n");
    for (index = 0; index < int_arr_size; ++index) {
        i_arr1[index] = rand() % 22;
        i_arr2[index] = rand() % 8;

        printf("i_arr1[%d] = %d  ", index, i_arr1[index]);
        printf("i_arr2[%d] = %d\n", index, i_arr2[index]);
    }

    /*
        Если нужно изменить (увеличить/уменьшить) блок уже выделенной динамической памяти,
        то к вашим услугам функция realloc:
            void* realloc(void *pointer, size_t size) - где pointer - указатель на существующий динамический массив,
                                                       size - новый размер памяти.
    */
    unsigned int new_size = int_arr_size + 10;
    i_arr2 = (int*) realloc(i_arr2, new_size * sizeof(int)); // увеличивыем массив i_arr2 на 10 элементов относительно числа int_arr_size
    if (i_arr2 == NULL ) {
        free(f_arr);
        free(i_arr1);

        perror("Error with memory reallocation");
        return;
    }

    printf("\ni_arr2, last 10 elements:\n");
    for (index = int_arr_size; index < new_size; ++index) {
        // заполняем новые 10 элементов в i_arr2
        i_arr2[index] = -5 + rand() % 6;
        printf("i_arr2[%d] = %d\n", index, i_arr2[index]);
    }

    // Освобождение памяти
    free(f_arr);
    free(i_arr1);
    free(i_arr2);
}

int main(void)
{
    srand( time(NULL) );
    examples_with_static_arrays();

    examples_of_dynamic_arrays(10, 20);
    return 0;
}