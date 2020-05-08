int SMIfloor(double);
int SMIceil(double);
int SMIround(double);
double SMIabs(double);
unsigned long long int SMIfact(unsigned int); // теперь работает до x = 20 включительно.
double SMIln(double);
double SMIexp(double);
double SMIpow(double, double);
double SMIsqrt(double);
double SMIsin(double); // При x = pi + 2 * pi * k получается число, очень близкое к нулю, но не ноль. Вынес это в отдельный случай.
double SMIcos(double);
double SMItg(double);
double SMIctg(double);
double SMIlog(double, double);
