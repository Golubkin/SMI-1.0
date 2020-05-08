// Возвращает максимальное целое, не превышающее x.
int SMIfloor(double x)
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
int SMIceil(double x)
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
int SMIround(double x)
{
    if (x >= 0)
        return SMIfloor(x + 0.5);
    if (x < 0)
        return SMIceil(x - 0.5);
}

// Возвращает модуль числа x.
double SMIabs(double x)
{
    if (x >= 0)
        return x;
    else
        return -x;
}

// Возвращает x в степени n. При целом n число x - любое (кроме случая x = 0 и n <= 0). При действительном n число x >= 0.
// Иррациональных чисел в C++ нет, поэтому будем вместо действительных рассматривать рациональные
double SMIpow(double x, double n)
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
            return 1.0 / SMIpow(x, -n);
    }
    else // Если n - действительное (в нашем случае - просто рациональное). При x < 0 ф-я не определена.
    {
        if (x == 0.0)
            return 0.0;
        if (x > 0.0)
            return SMIexp(n * SMIln(x, 100), 10); // Почему выдаёт ошибку, если не указывать 100 и 10? Это же аргументы по умолчанию.
    }
}

// Возвращает квадратный корень числа x.
double SMIsqrt(double x, double epsilon = 0.0001)
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
            difference = SMIpow(result, 2) - x;
            if (SMIabs(difference) < epsilon)
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
unsigned long long int SMIfact(unsigned int x)
{
    if (x > 1)
        return x * SMIfact(x - 1);
    if (x == 1)
        return 1;
    if (x == 0)
        return 1;
}

// Возвращает синус угла х (радианы). n - количество слагаемых в ряде Маклорена.
double SMIsin(double x, unsigned int n = 10)
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
        res += SMIpow(x, num) / (double)(SMIfact(num) * p);
        num -= 2;
    }
    return res;
}

// Возвращает косинус угла х (радианы).
double SMIcos(double x)
{
    const double pi = 3.14159265358979323846;
    return SMIsin(pi / 2.0 - x);
}

// Возвращает тангенс угла х (радианы).
double SMItg(double x)
{
    return (double)SMIsin(x) / SMIcos(x);
}

// Возвращает котангенс угла x (радианы).
double SMIctg(double x)
{
    return (double)SMIcos(x) / SMIsin(x);
}

// Возвращает число е в степени х.
double SMIexp(double x, unsigned int n = 10)
{
    if (SMIabs(x) <= 1.0)
    {
        double res = 1.0;
        while (n)
        {
            res += SMIpow(x, n) / (double)SMIfact(n);
            n--;
        }
        return res;
    }
    double e = 2.71828182845904523536;
    if (x > 1.0)
    {
        double int_x = floorSMI(x), fract_x = x - int_x;
        return SMIpow(e, int_x) * SMIexp(fract_x);
    }
    if (x < -1.0)
    {
        double int_x = SMIceil(x), fract_x = x - int_x;
        return SMIpow(e, int_x) * SMIexp(fract_x);
    }
}

// Возвращает ln(x). ln(1 + x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ..., работает для |x| < 1. Остальные х приводим к этому интервалу.
double SMIln(double x, unsigned int n = 100)
{
    if (x >= 0.5 && x <= 2.0)
    {
        double res = 0.0;
        x--;
        while (n)
        {
            const double p = (n % 2 == 0) ? -1.0 : 1.0; // Если n - чётное, то p = -1.0, иначе p = 1.0.
            res += SMIpow(x, n) / (p * n);
            n--;
        }
        return res;
    }
    if (x > 2.0)
        return -SMIln(1.0 / x, n);
    if (x > 0.0 && x < 0.5)
        return SMIln(2 * x, n) + SMIln(0.5, n);
}

// Возвращает логарифм по основанию base от аргумента argument.
double SMIlog(double base, double argument, unsigned int n = 100)
{
    if (base > 0.0 && base != 1.0 && argument > 0.0)
        return (double)SMIln(argument, n) / SMIln(base, n);
}
