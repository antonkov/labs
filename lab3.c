#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float h = 0.1;
    for (float x = -1; x <=1; x+=h){
        float y;
        if (x > 0) y = sin(2*x) / x;
        else if (x == 0) y = 2;
        else y = 2 * cos(x) * exp(-x);
        printf("%4.2f %4.2f\n", x, y);
    }
    getchar();
}
