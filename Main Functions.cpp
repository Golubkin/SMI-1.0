#include <iostream>
using namespace std;

int floorTEST(double);
int ceilTEST(double);
int roundTEST(double);
double absTEST(double);
double powTEST(double, double); // Как дописать функцию для действительных (в нашем случае - рациональных) n?
double slice(double, unsigned int); // Почему возвращает максимум 5 знаков после запятой? Если вводить n=6 и больше - выведет 5.
double sqrtTEST1(double, double); // Что вернуть, если значение не определено, а функция должна возвращать double?
double sqrtTEST2(double, double); // Почему не работает?
int factTEST(int);
double sinTEST(double);
double cosTEST(double);
double tgTEST(double);
double ctgTEST(double);
double expTEST(double);
double lnTEST(double); // Почему не работает?

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
// Иррациональных чисел в C++ нет (?), поэтому будем вместо действительных рассматривать рациональные.
double powTEST(double x, double n) 
{
    if (n == (double)((int)n)) // Если n - целое, и его нельзя представить в виде дроби (т.к. тогда мы расширяем число до рациональных).
    {
        if (x == 0.0 && n <= 0.0)
            return 999999999999999.0; // Что вернуть, если значение не определено, а функция должна возвращать double?
        if (x == 0.0 && n > 0.0)
            return 0.0;
        if (x != 0.0 && n == 0.0)
            return 1.0;
        if (n > 0.0)
        {
            double t = x;
            while (n != 1.0)
            {
                n--;
                x *= t;
            }
            return x;
        }
        if (x != 0.0 && n < 0.0)
        {
            double t = x;
            while (n != -1.0)
            {
                n++;
                x *= t;
            }
            return 1 / x;
        }
    }
    else // Если n - действительное (в нашем случае - просто рациональное)
    {
        if (x < 0.0)
            return 999999999999999.0;
        if (x == 0.0)
            return 0.0;
        if (x > 0.0 && n == 0.0)
            return 1.0;
        if (x > 0.0 && n > 0.0)
        {
           // ???
        }
        if (x > 0.0 && n < 0.0)
        {
           // ???
        }
    }
}

// Возвращает то же число, но до указанного числа знаков после запятой (Как сделать ту же функцию, но с округлением?) 
// Почему n=5 - максимум?
double slice(double x, unsigned int n)
{
    double var1 = x - (int)x; // дробная часть числа x с учётом знака.
    int var2 = powTEST(10, n); // 10^n;
    double var3 = var1 * var2;
    double var4 = var3 - (int)var3;
    double var5 = var4 / var2;
    return x - var5;
}

// Возвращает квадратный корень числа x.
double sqrtTEST1(double x, double epsilon = 0.0001)
{
    double low = 0.0;
    double high = x;
    double result;
    double difference;
    while (low <= high)
    {
        result = (low + high) / 2;
        difference = powTEST(result, 2) - x;
        if (absTEST(difference) < epsilon)
            return slice(result, 3); // slice?
        else
        {
            if (difference < 0)
                low = result;
            else
                high = result;
        }
    }
    return 9999999999; // Что вернуть, если значение не определено, а функция должна возвращать double?
}

// Возвращает квадратный корень числа x. sqrt(1+x) = 1 + x/2 - x^2 / 8 + x^3 / 16 - x^4 / 25.6 + ...
double sqrtTEST2(double x)
{
    if (x >= 0)
    {
        x -= 1.0;
        return 1.0 + x / 2 - powTEST(x, 2) / 8 + powTEST(x, 3) / 16 - powTEST(x, 4) / 25.6 + powTEST(x, 5) / 36.57142857;
    }
    else
        return 999999999999999.0;
    // В чём проблема?
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
        return -1; // Что возвращать?
}

// Возвращает синус угла х (радианы).
double sinTEST(double x)
{
    return x - (double)powTEST(x, 3) / factTEST(3) + (double)powTEST(x, 5) / factTEST(5)
        - (double)powTEST(x, 7) / factTEST(7) + (double)powTEST(x, 9) / factTEST(9)
        - (double)powTEST(x, 11) / factTEST(11) + (double)powTEST(x, 13) / factTEST(13);
}

// Возвращает косинус угла х (радианы).
double cosTEST(double x)
{
    double pi = 3.141593;
    return sinTEST(pi / 2 - x);
}

// Возвращает тангенс угла х (радианы).
double tgTEST(double x)
{
    return (double)sinTEST(x) / cosTEST(x);
}

// Возвращает котангенс угла x (радианы).
double ctgTEST(double x)
{
    return 1.0 / tgTEST(x);
}

// Возвращает число е в степени х.
double expTEST(double x)
{
    return 1.0 + x + (double)powTEST(x, 2) / factTEST(2) + (double)powTEST(x, 3) / factTEST(3)
        + (double)powTEST(x, 4) / factTEST(4) + (double)powTEST(x, 5) / factTEST(5)
        + (double)powTEST(x, 6) / factTEST(6) + (double)powTEST(x, 7) / factTEST(7)
        + (double)powTEST(x, 8) / factTEST(8) + (double)powTEST(x, 9) / factTEST(9)
        + (double)powTEST(x, 10) / factTEST(10) + (double)powTEST(x, 11) / factTEST(11);
}

// Возвращает ln(x). ln(1 + x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ...
double lnTEST(double x)
{
    if (x > 0)
    {
        x -= 1;
        return x - powTEST(x, 2) / 2 + powTEST(x, 3) / 3
            - powTEST(x, 4) / 4 + powTEST(x, 5) / 5
            - powTEST(x, 6) / 6 + powTEST(x, 7) / 7
            - powTEST(x, 8) / 8 + powTEST(x, 9) / 9
            - powTEST(x, 10) / 10;
    }
    else
        return 999999999999999.0;
    // Почему не работает?
}

int main()
{

}
