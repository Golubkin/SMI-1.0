/*!
    \brief Функция округления вниз.

    Функция возвращает максимальное целое, не превышающее x.

    1.Если число типа double больше или равно нуля, то функция возвращает это число преобразованное в тип int.

    2.Если число типа double меньше нуля и без остатка, то функция возвращает это число преобразованное в тип int.
    В случае, если число отрицательное и дробое, то функция возвращает число преобразованное в int, уменьшенное на единицу.(Например, число -3,5 округлится до -4)

    \param[in] x входящий параметр типа double.

*/
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

/*!
    \brief Функция округления вверх.

    Функция возвращает минимальное целое, которое не меньше x.

    1.Если число типа double положительное и без остатка, то функция возвращает это число, округленное в тип int. В случае если число с остатком,
    то возвращается число преобразованное в тип int и увеличенное на единицу.

    2.Если число типа double меньше либо равно нулю,  то функция возвращает число преобразованное в тип int.

    
    \param[in] x входящий параметр типа double.
*/
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

/*!
    \brief Модуль числа.

    Функция возвращает модуль числа x.

    1.Если число типа double больше либо равно нулю, то функция возвращает это число.


    2.Если число типа double меньше нуля, то функция возвращает противоположное число.


    \param[in] x входящий параметр типа double.
*/
double SMIabs(double x)
{
    if (x >= 0)
        return x;
    else
        return -x;
}

/*!
    \brief Факториал числа.

    Функция возвращает факториал числа x.

    \warning Функция не работает для x > 20. Так как факториал очень быстро растет.

    1.Функция работает по принципу рекурсии. Если число x типа unsigned int больше единицы, то значение x умножаем на вызов функции. 
    И так до тех пор, пока x не станет равным единице или нулю. 
    
    2.Если число x типа unsigned int равняется единице или нулю, то функция возвращает единицу.


    \param[in] x входящий параметр типа unsigned int .
*/
unsigned long long int SMIfact(unsigned int x)
{
    if (x > 1)
        return x * SMIfact(x - 1);
    if (x == 1)
        return 1;
    if (x == 0)
        return 1;
}


/*!
    \brief Натуральный логарифм числа.

    Функция ln(x). \f$\ ln(1+x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + ...\f$

    \warning Функция для |x| < 1. Остальные x приводим к этому интервалу.


    \param[in] x входящий параметр типа double
    
*/
double SMIln(double x)
{
    unsigned int n = 100; // Вынес из параметра по умолчанию для облегчения работы с Bison.
    if (x >= 0.5 && x <= 2.0)
    {
        double res = 0.0;
        x--;
        while (n)
        {
            const double p = (n % 2 == 0) ? -1.0 : 1.0; // Если n - чётное, то p = -1.0, иначе p = 1.0.
            double powValue = 1.0; 
            for(int i = n; i != 0; i--){ powValue *= x; }
            res += powValue / (p * n);
            n--;
        }
        return res;
    }
    if (x > 2.0)
        return -SMIln(1.0 / x);
    if (x > 0.0 && x < 0.5)
        return SMIln(2 * x) + SMIln(0.5);
}

/*!
    \brief Число е в степени x.

    Функция возвращает e степени x. Онована на ряде Маклорена \f$\ e^x = 1 + x / 1! + x^2 / 2! + x^3 / 3! + ...\f$


    \param[in] x входящий параметр типа double

*/
double SMIexp(double x)
{
    unsigned int n = 10;
    if (SMIabs(x) <= 1.0)
    {
        double res = 1.0;
        while (n)
        {
            double powValue = 1.0; 
            for(int i = n; i != 0; i--){ powValue *= x; }
            res += powValue / (double)SMIfact(n);
            n--;
        }
        return res;
    }
    double e = 2.71828182845904523536;
    if (x > 1.0)
    {
        double int_x = SMIfloor(x), fract_x = x - int_x;
        double powValue = 1.0;
        for(int i = int_x; i != 0; i--){ powValue *= e; }
        return powValue * SMIexp(fract_x);
    }
    if (x < -1.0)
    {
        double int_x = SMIceil(x), fract_x = x - int_x;
        double powValue = 1.0;
        for(int i = int_x; i != 0; i++){ powValue *= e; powValue = 1.0 / powValue; }
        return powValue * SMIexp(fract_x);
    }
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
            return SMIexp(n * SMIln(x));
    }
}

// Возвращает квадратный корень числа x.
double SMIsqrt(double x)
{
    double epsilon = 0.0001;
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

// Возвращает синус угла х (радианы). n - количество слагаемых в ряде Маклорена.
double SMIsin(double x)
{
    unsigned int n = 10;
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

// Возвращает логарифм по основанию base от аргумента argument.
double SMIlog(double base, double argument)
{
    unsigned int n = 100;
    if (base > 0.0 && base != 1.0 && argument > 0.0)
        return (double)SMIln(argument) / SMIln(base);
}
