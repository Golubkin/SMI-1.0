int floorSMI(double);
int ceilSMI(double);
int roundSMI(double);
double absSMI(double);
double powSMI(double, double);
double sqrtSMI(double, double);
unsigned long long int factSMI(unsigned int); // теперь работает до x = 20 включительно.
double sinSMI(double, unsigned int); // При x = pi + 2 * pi * k получается число, очень близкое к нулю, но не ноль. Вынес это в отдельный случай.
double cosSMI(double);
double tgSMI(double);
double expSMI(double, unsigned int);
double lnSMI(double, unsigned int);
double logSMI(double, double, unsigned int);
