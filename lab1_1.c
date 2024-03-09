#include <stdio.h>

int main() {
    int size; // 크기
    int stars, blank1, blank2; // 별의 갯수, 빈칸1의 갯수, 빈칸2의 갯수 
    int i, j; // 반복문을 위한 변수

    printf("size? "); 
    scanf("%d" ,&size);

    for(i=0; i<size; i++) {
        for(j=0; j<i; j++) {
            printf(" ");
        }
        printf("*");
         for(j=0; j<2*size-2-2*i; j++) {
            printf(" ");
        }
        printf("*"); 
        printf("\n");
    }

    for(i=0; i<size; i++) {
        for(j=0; j<2*size; j++) {
            printf("*");
        }
        printf("\n");
    }

    for(i=0; i<size; i++) {
        for(j=0; j<i; j++) {
            printf(" ");
        }
        for(j=0; j<2*size-(i*2); j++) {
            printf("*"); 
        }
        printf("\n");
    }

    for(i=0; i<2*size; i++) {
        printf("*");
    }

    return 0; 
}
