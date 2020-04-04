#include <iostream>
using namespace std;

int floorTEST(double);
int ceilTEST(double);
int roundTEST(double);
double absTEST(double);
double powTEST(double, double); // Как дописать функцию для действительных (в нашем случае - рациональных, в C++ нет иррациональных) n?
double slice(double, unsigned int); // Почему возвращает максимум 5 знаков после запятой? Если вводить n=6 и больше - выведет 5.
double sqrtTEST1(double, double); // Исправил. Теперь работает и для x < 1.
double sqrtTEST2(double, double); // Пока не работает.
int factTEST(int);
double sinTEST(double, unsigned int);
double cosTEST(double);
double tgTEST(double);
double ctgTEST(double);
double expTEST(double, unsigned int); // Почему работает хорошо только при x, близких к нулю ? (Как отрицательных, так и положительных).
double lnTEST(double, unsigned int); // Нужно огромное n для x, очень близких к нулю. Для остальных x отлично работает. Почему?

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
            return 1 / res;
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
    if (x < 0)
        return 9999999999.0; // Что вернуть, если значение не определено, а функция должна возвращать double?
    double low = 0.0;
    double high = (x > 1) ? x : 1.0;
    double result;
    double difference;
    while (low <= high)
    {
        result = (low + high) / 2;
        difference = powTEST(result, 2) - x;
        if (absTEST(difference) < epsilon)
            return result; // slice?
        else
        {
            if (difference < 0)
                low = result;
            else
                high = result;
        }
    }
}

// Возвращает квадратный корень числа x. sqrt(1+x) = 1 + x/2 - x^2 / 8 + x^3 / 16 - x^4 / 25.6 + ...  (n+1) - Число слагаемых в ряде Маклорена.
double sqrtTEST2(double x, unsigned int n = 5)
{

    double res = 1.0;
    if (x > 0 && x <= 2)
    {
        x--;
        while (n)
        {
            res += (double)(powTEST(-1, n) * factTEST(2 * n) * powTEST(x, n)) / ((1 - 2 * n) * factTEST(n) * factTEST(n) * powTEST(4, n));
            n--;
        }
        return res;
    }
    if (x > 2)
    {

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
        return -1; // Что возвращать?
}

// Возвращает синус угла х (радианы). n - количество слагаемых в ряде Маклорена.
double sinTEST(double x, unsigned int n = 10)
{
    double res = 0.0;
    int num = n * 2 - 1; // Число, участвующее в последнем члене ряда Маклорена.
    while (num + 1)
    {
        const int p = ((num + 1) / 2 % 2 == 0) ? -1 : 1;
        res += powTEST(x, num) / (double)(factTEST(num) * p); // По моему не обязательно приводить к double.
        num -= 2;
    }
    return res;
}

// Возвращает косинус угла х (радианы).
double cosTEST(double x)
{
    const double pi = 3.14159265358979323846;
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

// Возвращает число е в степени х. Почему работает хорошо только при x, близких к нулю? (Как отрицательных, так и положительных)
double expTEST(double x, unsigned int n = 10)
{
    double res = 1.0;
    while (n)
    {
        res += powTEST(x, n) / (double)factTEST(n);
        n--;
    }
    return res;
}

// Возвращает ln(x). ln(1 + x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ..., работает для |x| < 1. Нужно огромное n для x, очень близких к нулю.
double lnTEST(double x, unsigned int n = 1000)
{
    double res = 0.0;
    if (x > 0.0 && x <= 2.0)
    {
        x--;
        while (n)
        {
            const double p = (n % 2 == 0) ? -1.0 : 1.0; // Если n - чётное, то p = -1.0, иначе p = 1.0
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
        return 999999999999999.0;
}

int main()
{

}
