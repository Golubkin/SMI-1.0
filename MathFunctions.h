int SMIfloor(double);
int SMIceil(double);
int SMIround(double);
double SMIabs(double);
double SMIpow(double, double);
double SMIsqrt(double, double);
unsigned long long int SMIfact(unsigned int); // теперь работает до x = 20 включительно
double SMIsin(double, unsigned int); // При x = pi + 2 * pi * k получается число, очень близкое к нулю, но не ноль. Вынес это в отдельный случай
double SMIcos(double);
double SMItg(double);
double SMIexp(double, unsigned int);
double SMIln(double, unsigned int);
double SMIlog(double, double, unsigned int);
