#include <stdio.h>
#include <math.h>

double f(double x, double precision) {
    double accum = 1;
    double part = 1;
    
    for (int n = 1;; ++n) {
        part *= -1 * x;
        part *= 2*n * (2*n - 1);
        part /= 4 * n * n;
        part /= 1 - 2*n;
        
        accum += part;
        // printf("%d)%F\n", n, part);
        
        if ( fabs(part) < precision)
            break;
            
        part *= 1 - 2*n;
    }
    
    return accum;
}

int main()
{
    double x = 0.5;
    double precision = 0.00002;
    printf("%F\n%F", sqrt(1+x), f(x, precision));

    return 0;
}
