#include <stdio.h>
int main(){
    int a[30];
    int y = 1;
    int max = 1;
    for (int i = 0; i< 30; i++){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < 30; i++){
        if (i != 0 && a[i] == a[i-1]) {
            y++;
            if (y > max){
                max = y;
            }
        }
        else y = 1;
    }
    printf("%d ", max);
    getchar();
}

