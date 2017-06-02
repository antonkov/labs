#include <stdio.h>
#include <stdlib.h>

float ** create_float_array(int n) {
    float ** a;
    a = malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(float));
    }
    return a;
}
void delete_float_array(float ** a, int n) {
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
}
int main() {
    int n;
    scanf("%d", &n);
    float ** a = create_float_array(n);
    for (int i =0; i < n; i++){
        for (int j = 0; j < n; j++) {
            scanf("%f", &a[i][j]);
        }
    }
    float max = a[n - 1][n - 1];
    for (int i =0; i < n; i++){
        for (int j = 0; j < n; j++) {
            printf("%4.2f ", a[i][j]);
        }
        printf("\n");
    }
    int k = n-1;
    for (int i =0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j > k) {
                if (a[i][j] > max) {
                    max = a[i][j];
                }
            }
        }
        k--;
    }
    printf("%4.2f", max);
    delete_float_array(a, n);
    getchar();
}

