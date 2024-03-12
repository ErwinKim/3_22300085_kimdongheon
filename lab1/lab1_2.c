#include <stdio.h> 
int main() {
    int person[4][3]; // 4개 층별 3개 호실의 점호 인원 수
    int sum[3] = {0}; // 점호 인원 수 합계 (남, 여, 전체)
    float ratio[3]; // 점호 인원 수 비율 (남, 여, 전체)
    int i, j; // 반복문을 위한 변수

    printf("Check room (Men)\n");
    for(i=0; i<1; i++) {
        for(j=0; j<3; j++) {
            printf("Room #%d0%d > ", i+1, j+1);
            scanf("%d", &person[i][j]);
        }
    }
    for(int i=1; i<2; i++) {
        for(int j=0; j<3; j++) {
            printf("Room #%d0%d > ", i+1, j+1);
            scanf("%d", &person[i][j]);
        }
    }

    printf("Check room (Women)\n");
    for(i=2; i<3; i++) {
        for(j=0; j<3; j++) {
            printf("Room #%d0%d > ", i+1, j+1);
            scanf("%d", &person[i][j]);
        }
    }
    for(int i=3; i<4; i++) {
        for(int j=0; j<3; j++) {
            printf("Room #%d0%d > ", i+1, j+1);
            scanf("%d", &person[i][j]);
        }
    }

    
    printf("Check result\n");
    for(i=0; i<1; i++) {
        for(j=0; j<3; j++) {
            sum[0] += person[i][j];
        }
    }
    for(i=1; i<2; i++) {
        for(j=0; j<3; j++) {
            sum[0] += person[i][j];
        }
    }
    ratio[0] = 100*(float)sum[0]/24;
    printf("Men: %d/24 (%.1f%%)\n", sum[0], ratio[0]);

    for(i=2; i<3; i++) {
        for(j=0; j<3; j++) {
            sum[1] += person[i][j];
        }
    }
    for(i=3; i<4; i++) {
        for(j=0; j<3; j++) {
            sum[1] += person[i][j];
        }
    }
    ratio[1] = 100*(float)sum[1]/24;
    printf("Women: %d/24 (%.1f%%)\n", sum[1], ratio[1]);

    sum[2] = sum[0]+sum[1];
    ratio[2] = 100*(float)sum[2]/48; 
    printf("Total: %d/24 (%.1f%%)\n", sum[2], ratio[2]);

    return 0;
}