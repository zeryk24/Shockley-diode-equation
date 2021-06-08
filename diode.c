
/**
 * @author  Erik Báča
 * @date November 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double equation(double r, double up, double u0);

/*
 * This function is an implementation of binary search
 *
 * Parameters of this function are input voltage, resistance of resistor and approximation
 * Function returns voltage with right approximation
 */
double diode(double u0, double r, double eps)
{
    double a = 0;
    double b = u0;
    double middle = (a+b) / 2;
    double fmid = equation(r, middle, u0);
    double lastMiddle;
    while (fabs(fmid) > eps)
    {
        lastMiddle = middle;
        if (equation(r, a, u0) * fmid < 0)
            b = middle;
        else
            a = middle;
        if (fabs (fmid) > eps)
        {
            middle = (a+b) / 2;
            fmid = equation(r, middle, u0);
        }
        if (middle == lastMiddle) //validation of too little epsilon
            return middle;
    }
    return middle;
}

/*
 * This function is an implementation of Shockley diode equation
 *
 * Parameters of this function the resistance of resistor, the voltage across the diode, and input voltage
 * Function returns diode current
 */
double equation(double r, double up, double u0)
{
    double i0 = 1e-12;
    double ut = 0.0258563;
    double ip = r*i0*(exp(up/ut) - 1) - u0 + up;
    return ip;
}

int main(int argc, char *argv[])
{
    if (argc==4)
    {
        double u0 = strtod(argv[1],NULL);
        double r = strtod(argv[2],NULL);
        double eps = strtod(argv[3],NULL);

        if (u0 >= 0)
        {
            double up = diode(u0, r, eps);
            double ip = (u0-up)/r;
            if(ip != ip)
                ip = 1.0/0.0;
            printf("Ip=%g A\nUp=%g V\n", ip, up);
        } else
            printf("error: invalid arguments\n");
    } else
        printf("Invalid input.\n");
    return 0;
}