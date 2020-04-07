#include <iostream>
using namespace std;

int floorTEST(double);
int ceilTEST(double);
int roundTEST(double);
double absTEST(double);
double powTEST(double, double); // Новая проблема (строка 114) - вместо 1.0 / expTEST(n * lnTEST(x)) возвращает expTEST(n * lnTEST(x)).
double sqrtTEST1(double, double); // Исправил. Теперь работает и для x < 1. Оставить ф-ю или переписать с применением ряда Тейлора?
int factTEST(int);
double sinTEST(double, unsigned int); // Исправил. Проблема была та же, что и в exp().
double cosTEST(double);
double tgTEST(double); // Неправильно работает при х = 3 * pi / 2 + 2 * pi * n. При x = pi / 2 + x = 2 * pi * n - правильно (inf).
double ctgTEST(double); // Неправильно работает при х = pi + 2 * pi * n. При x = 2 * pi * n - правильно (inf).
double expTEST(double, unsigned int); // Исправил (Описание проблемы - перед определением функции).
double lnTEST(double, unsigned int); // Нужно огромное n для x, очень близких к нулю и очень далёких от нуля. Для остальных x отлично работает.
// Проблема, по сути, лишь в маленьких х. Потому что большие х мы делаем обратными со знаком минус (1 / x получается очень маленьким).
// Проблема в том, что ф-и ln(1+x) и x - x^2 / 2 + x^3 / 3 - ... могут не совпадать в точках, очень близких к x = -1 справа.
// Для совпадения нужно брать огромное количество первых слагаемых ряда. Возьмите, например, lnTEST(0.000003).
// Правильное значение = -12.7168... Но у меня при количестве слагаемых n = 20000 lnTEST(0.000003) = -9.75783.

double logTEST(double, double, unsigned int);

// Возвращает максимальное целое, не превышающее x.
int floorTEST(double x)
{
    if (x >= 0)
        return (int)x;
    if (x < 0)
    {
        if (x == (double)((int)x))
            return (int)x;
        else
            return (int)x - 1;
    }
}

// Возвращает минимальное целое, которое не меньше x.
int ceilTEST(double x)
{
    if (x > 0)
    {
        if (x == (double)((int)x))
            return (int)x;
        else
            return (int)x + 1;
    }
    if (x <= 0)
        return (int)x;
}

// Возвращает округлённое значение числа x.
int roundTEST(double x)
{
    if (x >= 0)
        return floorTEST(x + 0.5);
    if (x < 0)
        return ceilTEST(x - 0.5);
}

// Возвращает модуль числа x.
double absTEST(double x)
{
    if (x >= 0)
        return x;
    else
        return -x;
}

// Возвращает x в степени n. При целом n число x - любое (кроме случая x = 0 и n <= 0). При действительном n число x >= 0.
// Иррациональных чисел в C++ нет ouble x, d(?), поэтому будем вместо действительных рассматривать рациональные.
double powTEST(double x, double n)
{
    if (n == (double)((int)n)) // Если n - целое, и его нельзя представить в виде дроби (т.к. тогда мы расширяем число до рациональных).
    {
        if (x == 0.0 && n <= 0.0)
        {
            // Ничего не возвращает.
        }
        if (x == 0.0 && n > 0.0)
            return 0.0;
        if (x != 0.0 && n == 0.0)
            return 1.0;
        if (n > 0.0)
        {
            double res = 1.0;
            while (n--)
            {
                res *= x;
            }
            return res;
        }
        if (x != 0.0 && n < 0.0)
        {
            double res = 1.0;
            while (n++)
            {
                res *= x;
            }
            return 1.0 / res;
        }
    }
    else // Если n - действительное (в нашем случае - просто рациональное)
    {
        if (x < 0.0)
        {
            // Ничего не возвращает.
        }
        if (x == 0.0)
            return 0.0;
        if (x > 0.0 && n > 0.0)
            return expTEST(n * lnTEST(x, 10000), 10);
        if (x > 0.0 && n < 0.0)
            return 1.0 / expTEST(n * lnTEST(x, 10000), 10);
    }
}

// Возвращает квадратный корень числа x.
double sqrtTEST(double x, double epsilon = 0.0001)
{
    if (x < 0)
    {
        // Ничего не возвращает.
    }
    double low = 0.0;
    double high = (x > 1) ? x : 1.0;
    double result;
    double difference;
    while (low <= high)
    {
        result = (low + high) / 2;
        difference = powTEST(result, 2) - x;
        if (absTEST(difference) < epsilon)
            return result;
        else
        {
            if (difference < 0)
                low = result;
            else
                high = result;
        }
    }
}

// Возвращает факториал числа x.
int factTEST(int x)
{
    if (x > 1)
        return x * factTEST(x - 1);
    if (x == 1)
        return 1;
    if (x == 0)
        return 1;
    if (x < 0)
    {
        // Ничего не возвращает.
    }
}

// Возвращает синус угла х (радианы). n - количество слагаемых в ряде Маклорена.
double sinTEST(double x, unsigned int n = 7) // Не желательно брать n > 7. При n = 10 получается, например, что sin(pi) = -26.4543.
{
    double pi = 3.14159265358979323846;
    double res = 0.0;
    int num = n * 2 - 1; // Число, участвующее в последнем члене ряда Маклорена.
    // Первые два цикла while приводят х к интервалу (-pi, pi).
    while (x > pi)
    {
        x -= 2.0 * pi;
    }
    while (x < -pi)
    {
        x += 2.0 * pi;
    }
    while (num + 1)
    {
        const int p = ((num + 1) / 2 % 2 == 0) ? -1 : 1; // (num + 1) / 2 - текущий номер члена.
        res += powTEST(x, num) / (double)(factTEST(num) * p);
        num -= 2;
    }
    return res;
}

// Возвращает косинус угла х (радианы).
double cosTEST(double x)
{
    const double pi = 3.14159265358979323846;
    return sinTEST(pi / 2.0 - x);
}

// Возвращает тангенс угла х (радианы).
double tgTEST(double x)
{
    return (double)sinTEST(x) / cosTEST(x);
}

// Возвращает котангенс угла x (радианы).
double ctgTEST(double x)
{
    return (double)cosTEST(x) / sinTEST(x);
}

// Возвращает число е в степени х. Почему работает хорошо только при x, близких к нулю? (Как отрицательных, так и положительных).

// Потому что хоть формула Тейлора-Маклорена для e^x верна для всех х (а не только для |x|<1, как в ln(1+x)), но чтобы график e^x
// и график 1 + x + x^2/2 + ... совпали, к примеру, в точке x = -50, нужно взять 100, или даже намного больше первых членов ряда.
// Ещё в формуле участвует факториал, поэтому числа в знаменателе каждого члена будут стремительно расти, и больше, например, 20-го
// члена ряда мы не сможем взять.  Поэтому в любом случае нужно вычислять e^x по формуле Тейлора-Маклорена только для х,
// принадлежащих маленькой окрестности точки х = 0, например для таких х, что |x| < 1. Остальные e^x, где |x| > 1, нужно
// свести к интервалу (-1, 1), как мы делали с lnTEST().
double expTEST(double x, unsigned int n = 10)
{
    if (absTEST(x) <= 1.0)
    {
        double res = 1.0;
        while (n)
        {
            res += powTEST(x, n) / (double)factTEST(n);
            n--;
        }
        return res;
    }
    double e = 2.71828182845904523536;
    if (x > 1.0)
    {
        double int_x = floorTEST(x), fract_x = x - int_x;
        return powTEST(e, int_x) * expTEST(fract_x);
    }
    if (x < -1.0)
    {
        double int_x = ceilTEST(x), fract_x = x - int_x;
        return powTEST(e, int_x) * expTEST(fract_x);
    }
}

// Возвращает ln(x). ln(1 + x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ..., работает для |x| < 1. Нужно огромное n для x, очень близких к нулю.

double lnTEST(double x, unsigned int n = 10000)
{
    if (x > 0.0 && x <= 2.0)
    {
        double res = 0.0;
        x--;
        while (n)
        {
            const double p = (n % 2 == 0) ? -1.0 : 1.0; // Если n - чётное, то p = -1.0, иначе p = 1.0.
            res += powTEST(x, n) / (p * n);
            n--;
        }
        return res;
    }
    if (x > 2.0)
    {
        return -lnTEST(1.0 / x, n);
    }
    if (x < 0.0)
    {
        // Ничего не возвращает.
    }
}

// Возвращает логарифм по основанию base от аргумента argument.
double logTEST(double base, double argument, unsigned int n = 10000)
{
    return (double)lnTEST(argument, n) / lnTEST(base, n);
}

int main()
{

}
