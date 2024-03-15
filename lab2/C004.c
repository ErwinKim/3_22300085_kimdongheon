// Enter your student ID and Fullname
// 22300085 김동헌

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_class
{
	int code;	   // class code
	char name[30]; // class name
	int unit;	   // credites
	int grading;   // grading (1:A+~F, 2:P/F)
};

char kname[2][10] = {"A+~F", "P/F"}; // String for grading

// Functions provided
int loadData(struct st_class *c[]);					   // Load all class list from data file.
void printAllClasses(struct st_class *c[], int csize); // Print all class list

// Functions for modifying
int addNewClass(struct st_class *c[], int csize);			   // Add a class into the list
void editClass(struct st_class *c[], int csize);			   // Modify a class in the list
void findClasses(char *name, struct st_class *c[], int csize); // Search a class by name from the list

// Functions for making
int applyMyClasses(int my[], int msize, struct st_class *c[], int csize);  // Apply a class
void printMyClasses(int my[], int msize, struct st_class *c[], int csize); // Print my classes
void saveMyClass(int my[], int msize, struct st_class *c[], int csize);	   // Save my classes
void saveAllClasses(struct st_class *c[], int csize);					   // Save all class list

int main(void)
{
	int no;						  // menu number
	struct st_class *classes[50]; // Class list (max. 50 classes)

	int myclass[10]; // My classes (max. 10 classes of code)
	int mycount = 0; // Amount of my classes

	srand(time(0));
	int count = loadData(classes);
	printf("> Load %d classes.\n", count);

	while (1)
	{
		printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

		if (no == 1)
		{
			printf("> 1.Class list (%d classes)\n", count);
			printAllClasses(classes, count);
		}
		else if (no == 2)
		{
			printf("> 2.Add a Class\n");
			count = addNewClass(classes, count);
		}
		else if (no == 3)
		{
			printf("> 3.Modify a Class\n");
			editClass(classes, count);
		}
		else if (no == 4)
		{
			printf("> 4.Search a Class\n");
			printf(">> Enter class name > ");
			char name[30];
			scanf("%s", name);
			findClasses(name, classes, count);
		}
		else if (no == 5)
		{
			printf("> 5.Apply a class\n");
			mycount = applyMyClasses(myclass, mycount, classes, count);
			printf("%d classes has been applied.\n", mycount);
		}
		else if (no == 6)
		{
			printf("> 6.My classes\n");
			printMyClasses(myclass, mycount, classes, count);
		}
		else if (no == 7)
		{
			printf("> 7.Save\n");
			saveMyClass(myclass, mycount, classes, count);
			printf("\n> All my classes ware saved to my_classes.txt.\n");
			saveAllClasses(classes, count);
			printf("\n> All of class list ware saved to classes.txt.\n");
		}
		else
			break;
	}
	return 0;
}

int loadData(struct st_class *c[])
{
	int count = 0;
	FILE *file;

	file = fopen("classes.txt", "r");
	while (!feof(file))
	{
		c[count] = (struct st_class *)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code), c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if (r < 4)
			break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class *c[], int csize)
{
	for (int i = 0; i < csize; i++)
	{
		printf("[%d] %s [credit %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading - 1]);
	}
}

void saveAllClasses(struct st_class *c[], int csize)
{
	FILE *file;
	file = fopen("classes.txt", "w");
	for (int i = 0; i < csize; i++)
	{
		fprintf(file, "%d %s %d %d\n", c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);
}

void findClasses(char *name, struct st_class *c[], int csize)
{
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for (int i = 0; i < csize; i++)
	{
		if (strstr(c[i]->name, name))
		{
			printf("[%d] %s [credit %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading - 1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// You must complete these functions.
int addNewClass(struct st_class *c[], int csize)
{
	// Caution : Don't allow the duplicate class code.
	// You must complete this function.
	/*
	1.  메모리가 할당 된 p가 NULL일시 오류가 발생하기 때문에 memory allocation failed라는 메세지와 함께 csize를 리턴한다.
	2.  class code가 duplicate 되는 경우를 방지하기 위해 i 변수를 선언 후 i를 csize 만큼 반복하는 forloop을 만들어준다
		만들어 준 forloop 안에 만약 새롭게 메모리 할당된 수업코드 p->code 가 이미 할당된 수업코드 c[i]->code 랑 같을 때
		Class duplicated! Retry. 라는 메세지와 함께 이전에 할당된 p 메모리를 free() 함수를 통해 deallocate하고 csize를 리턴한다.
	*/

	struct st_class *p = (struct st_class *)malloc(sizeof(struct st_class));

	if (p == NULL)
	{
		printf("memory allocation failed\n");
		return csize;
	}

	printf(">> code number > ");
	scanf("%d", &(p->code));

	for (int i = 0; i < csize; i++)
	{
		if (p->code == c[i]->code)
		{
			printf("Class duplicated! Retry.");
			free(p);
			return csize;
		}
	}

	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize + 1;
}

void editClass(struct st_class *c[], int csize)
{
	struct st_class *p;
	int code;
	printf(">> Enter a code of class > ");
	scanf("%d", &code);

	// You must complete this section.
	/*  1. forloop을 열어 입력한 수업코드 code 가 저장된 수업 코드 c[]->code에 있는지 찾는다
			찾았다면 구조체 포인터를 c[i]로 덮어쓰고 break;
		2. 같은 forloop에 입력한 수업코드 code 가 저장된 수업 코드 c[]->code에 없다면 No such class를 출력하고 메뉴로 리턴한다
	*/
	for (int i = 0; i < csize; i++)
	{
		if (c[i]->code == code)
		{
			p = c[i];
			break;
		}
		if (c[i]->code != code)
		{
			printf("No such class.\n");
			return;
		}
	}

	printf("> Current: [%d] %s [credits %d - %s]\n", p->code, p->name, p->unit, kname[p->grading - 1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));
	printf("> Modified.\n");
}

// You must make all these functions.

int applyMyClasses(int my[], int msize, struct st_class *c[], int csize)
{
	struct st_class *p;
	int code; 
	int answer; 
	msize =0;

	do {
		printf("Enter a class code > ");
		scanf("%d", &code);

		int found =0;
		for(int i=0; i<csize; i++) {
			if(c[i]->code == code) {
				p = c[i];
				found = 1;
				break;
			}
		}
		for(int j=0; j<msize; j++) {
			if(my[j] == code) {
			found = 2;
			j--;
			break;
			}
		}

		if(found==1) {
			my[msize++] = code;
			printf("> Current: [%d] %s [credits %d - %s]\n", p->code, p->name, p->unit, kname[p->grading - 1]);
			
		} else if(found ==2) {
			printf("Class code duplicated.\n");
		}
		else {
			printf("No such class.\n");
			break;
		}
		printf("Add more?(1:Yes 2:No) > ");
		scanf("%d", &answer);

	} while (answer == 1);

    return msize;
}

void printMyClasses(int my[], int msize, struct st_class *c[], int csize)
{
	// printf("My Classes:\n");
    // for (int i = 0; i < msize; i++) {
    //     for (int j = 0; j < csize; j++) {
    //         if (my[i] == c[j]->code) {
    //             printf("[%d] %s [credit %d - %s]\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
    //             break;
    //         }
    //     }
    // }


}

void saveMyClass(int my[], int msize, struct st_class *c[], int csize)
{
	// FILE *file;
    // file = fopen("my_classes.txt", "w");
    // if (file == NULL) {
    //     printf("Error opening file for writing.\n");
    //     return;
    // }
    
    // for (int i = 0; i < msize; i++) {
    //     for (int j = 0; j < csize; j++) {
    //         if (my[i] == c[j]->code) {
    //             fprintf(file, "%d %s %d %s\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
    //             break;
    //         }
    //     }
    // }
    
    // fclose(file);
    // printf("My classes have been saved to my_classes.txt.\n");
}