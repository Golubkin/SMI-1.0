#include <iostream>
using namespace std;

int floorTEST(double);
int ceilTEST(double);
int roundTEST(double);
double absTEST(double);
double powTEST(double, double);
double sqrtTEST(double, double);
unsigned long long int factTEST(unsigned int); // теперь работает до x = 20 включительно.
double sinTEST(double, unsigned int); // При x = pi + 2 * pi * k получается число, очень близкое к нулю, но не ноль. Вынес это в отдельный случай.
double cosTEST(double);
double tgTEST(double);
double expTEST(double, unsigned int);
double lnTEST(double, unsigned int);
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
// Иррациональных чисел в C++ нет, поэтому будем вместо действительных рассматривать рациональные.
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
            return 1.0 / powTEST(x, -n);
    }
    else // Если n - действительное (в нашем случае - просто рациональное). При x < 0 ф-я не определена.
    {
        if (x == 0.0)
            return 0.0;
        if (x > 0.0)
            return expTEST(n * lnTEST(x, 100), 10); // Почему выдаёт ошибку, если не указывать 100 и 10? Это же аргументы по умолчанию.
    }
}

// Возвращает квадратный корень числа x.
double sqrtTEST(double x, double epsilon = 0.0001)
{
    if (x >= 0)
    {
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
}

// Возвращает факториал числа x. Для х > 20 не работает.
unsigned long long int factTEST(unsigned int x)
{
    if (x > 1)
        return x * factTEST(x - 1);
    if (x == 1)
        return 1;
    if (x == 0)
        return 1;
}

// Возвращает синус угла х (радианы). n - количество слагаемых в ряде Маклорена.
double sinTEST(double x, unsigned int n = 10)
{
    const double pi = 3.14159265358979323846;
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
    if (x == pi) // Без этого условия будет возвращать число, очень близкое к нулю. Но нужен именно 0.
        return 0.0;
    while (num + 1)
    {
        const double p = (((num + 1) / 2) % 2 == 0) ? -1.0 : 1.0; // (num + 1) / 2 - номер текущего члена.
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

// Возвращает ln(x). ln(1 + x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ..., работает для |x| < 1. Остальные х приводим к этому интервалу.
double lnTEST(double x, unsigned int n = 100)
{
    if (x >= 0.5 && x <= 2.0)
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
        return -lnTEST(1.0 / x, n);
    if (x > 0.0 && x < 0.5)
        return lnTEST(2 * x, n) + lnTEST(0.5, n);
}

// Возвращает логарифм по основанию base от аргумента argument.
double logTEST(double base, double argument, unsigned int n = 100)
{
    if (base > 0.0 && base != 1.0 && argument > 0.0)
        return (double)lnTEST(argument, n) / lnTEST(base, n);
}

int main()
{

}
