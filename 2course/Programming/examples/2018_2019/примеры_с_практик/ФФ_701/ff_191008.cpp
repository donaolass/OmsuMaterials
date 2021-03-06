#include "ffhelpers.h"

using namespace std;
using namespace ffomsu;

/**
    Пример работы с ГПСЧ.

    Расчёт определённого интеграла для функции одной переменной.
*/


/**
    Определяем функцию, которая будет проинтегрированна.

    Входящие параметры:
        * x - значение для расчёта (конкретный аргумент функции)

    Возращаемое значение:
        * вычисленное выражение для переданного аргумента
*/
double f(double x)
{
  return x + x*x + x*x*x;
}


int main()
{
    show_rus_letters();
    /// Строки 32 - 36: получение входных значений для программы
    double a ,b;
    get_value(a, "Введите левую границу: ");
    get_value(b, "Введите правую границу: ");
    size_t count_nums;
    get_value(count_nums, "Введите количество случайных чисел: ");

    /// Строки 39-43: обработка входных значений нужным алгоритмом
    double sum = 0.0;
    for (size_t i = 1; i <= count_nums; i++) {
       double xi = rand_a_b_incl(a, b);
       sum += f(xi);
    }

    /// Строка 46: вывод выходных значений на экран (в данном случае, всего одного)
    print("Интеграл равен ", ((b - a) / count_nums)* sum);
}
