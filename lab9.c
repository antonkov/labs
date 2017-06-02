#include <stdio.h>
#include <stdlib.h>
int sum(int c, int k) {
    return c + k;
}
int fold(int *array, int size, int (*func)(int, int)) {
    int ans = 0;
    for(int i=0; i< size-1; i++){
        ans += (*func)(array[i], array[i+1]);
    }
    return ans;
}
int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", fold(a, n, &sum));
}