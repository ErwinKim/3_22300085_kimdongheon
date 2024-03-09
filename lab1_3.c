/*
Programming Studio C003
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findRoom(int persons[5]); // 5개의 호실 중 빈 베드가 있는 방을 찾아낸다. (리턴값 1~5)
void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc); // 배정 결과를 출력한다.

int main(){
	char mnames[10][20]; // 남학생명단(최대 10명)
	int mroom[10];		// 남학생명단별 호실 배정 목록
	char wnames[10][20]; // 여학생명단(최대 10명)
	int wroom[10];		// 여학생명단별 호실 배정 목록
	int person[2][5]={0};   // 2개 층별 5개 호실의 배정 인원 수 
	int mcount=0, wcount=0; // 인원 합계 (남, 여)
	int menu;

	srand(time(0));
	printf("===========================================\n");
	printf("생활관 호실 배정 프로그램\n");
	printf("===========================================\n");
	while(1){
		printf("메뉴 : 1.남학생 등록 2.여학생 등록 0.종료 > ");
		scanf("%d", &menu);
		int allcount = mcount + wcount;
		if(menu==0) break;
		else if(menu==1) {
			if(allcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				break;
			}
			printf("학생 이름은? > ");
			scanf("%s", mnames[mcount]);
			int roomno = findRoom(person[0]);
			mroom[mcount] = 100+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", mnames[mcount], mroom[mcount]);
			mcount++;
		}
		else if(menu==2) {
			if(allcount>=10) {
				printf("정원 초과입니다. 등록불가!\n");
				break;
			}
			printf("학생 이름은? > ");
			scanf("%s", wnames[wcount]);
			int roomno = findRoom(person[1]);
			wroom[wcount] = 200+roomno;
			printf("%s 학생 %d호실 배정되었습니다.\n", wnames[wcount], wroom[wcount]);
			wcount++;
		}
	}

	printf("===========================================\n");
	printf("생활관 호실 배정 결과는 다음과 같습니다.\n");
	printf("===========================================\n");
	printReport(mnames, mroom, mcount, wnames, wroom, wcount);

	return 0;
}

int findRoom(int persons[5]){
// 이 곳에 생각 정리와 코드 구현
// while loop를 활용해 1~5까지의 숫자를 랜덤으로 생성
// if 한 방의 인원 <2 방을 배정 roomno++ 
// 채워지면 while문 종료
// if 랜덤변수가 선택한 방이 2명이면 while문 계속
// return roomno
	
	int randomRoom;
	// 매개변수 생성
    int roomno;
	int roomMax = 5;

    while(1) {
        randomRoom = rand() % roomMax;
        if (persons[randomRoom] < 2) {
            roomno = randomRoom + 1;
            persons[randomRoom]++;
			break;
        }
    }

    return roomno;
}


void printReport(char mn[10][20], int mr[10], int mc, char wn[10][20], int wr[10], int wc){
// 이 곳에 생각 정리와 코드 구현
// 남학생 명단 출력: mc를 사용하여 남자 인원수 출력
// for문을 활용하여 mc만큼 순차적으로 입력된 남학생의 이름과 호실 출력
// 여학생 명단 출력: wc를 사용하여 여자 인원수 출력
// for문을 활용하여 wc만큼 순차적으로 입력된 여학생의 이름과 호실 출력
// 호실별 배정 명단 출력: 남자와 여자를 나눠서 출력
// for문을 사용하여 남자는 mc만큼 101호부터 105호까지 배정된 이름을 순차적으로 출력
// for문을 사용하여 여자는 wc만큼 201호부터 205호까지 배정된 이름을 순차적으로 출력

	printf("남학생 명단 (%d):\n", mc);
    for(int i=0; i<mc; i++) {
        printf("%d. %s [%d호]\n", i+1, mn[i], mr[i]);
    }

    printf("\n여학생 명단 (%d):\n", wc);
    for(int i=0; i<wc; i++) {
        printf("%d. %s [%d호]\n", i+1, wn[i], wr[i]);
    }

	printf("\n호실별 배정 명단\n");
	for(int i=0; i<mc; i++) {
		printf("%d호 : %s\n", 101+i, mn[i]);
	}
	for(int i=0; i<wc; i++) {
		printf("%d호 : %s\n", 201+i, wn[i]);
	}
	
}
