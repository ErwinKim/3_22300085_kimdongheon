#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct shop {
    int code; // code of products
    char name[30]; // name of products
    int category; // category (1~6) of products
    int all; // total number of products 
};

char CNAME[6][30] = {"Food", "Drink", "Cleaning", "Devices", "Toys", "Furnitures"}; // Name of each category (1~6)

// allocate the contents of the products.txt into memory 
int readData(struct shop *p[]);
// reads the category code of each product in a defined range
int findCategory(int num);
// - Read 기능 – 전체 데이터 목록을 화면에 표시한다.
void printAllProducts(struct shop *p[], int size);
// Create 기능 – 새로운 데이터셋을 목록에 추가한다.
int addProduct(struct shop *p[], int size);
// - Update 기능 – 현재 데이터 목록 중에 하나의 데이터셋을 선택하여 내용을 변경한다.
void editShop(struct shop *p[], int size);
// - Delete 기능 – 현재 데이터 목록 중에 하나의 데이터셋을 선택하여 제거한다.
int deleteProduct(struct shop *p[], int size);
//- Search 기능 – 현재 데이터 목록 중에 특정 조건에 맞는 데이터셋들을 찾아 표시한다.
void findProduct(struct shop *p[], int size);
// - Save 기능 - 현재 변경된 데이터 목록을 데이터 파일로 저장한다.
// (이때 저장된 파일이 프로그램을 다시 시작할 때 데이터 목록 구축을 위해 읽혀진다.)
void saveProducts(struct shop *p[], int size);


int main() {
    int no; // number for menu selection
    struct shop *products[100]; // maximum of products

    int count = readData(products); // count = all kinds of product in the shop 
    printf("> Load %d products. \n", count);

    while(1) {
        printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Delete 6.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

        if(no==1) {
            printAllProducts(products, count);
        }
        else if(no==2) {
            count = addProduct(products, count);
        }
        else if(no==3) {
            editShop(products, count);
        }
        else if(no==4) {
            findProduct(products, count);
        }
        else if(no==5) {
            count = deleteProduct(products, count);
        }
        else if(no==6) {
            saveProducts(products, count);
        }
        else break;
    }

    return 0;
}

int findCategory(int num)
{
    int range[7]={0,1,2,3,4,5,6};
	for(int j=0;j<7;j++)
		if(num==range[j])
			return j;
	return 0;
}

int readData(struct shop *p[])
{
	int no = 0;
	FILE *file;

	file = fopen("products.txt", "r");
	while (!feof(file)) {
		struct shop*t = (struct shop*)malloc(sizeof(struct shop)); 
		int r = fscanf(file, "%d %s %d %d",&(t->code), (t->name), &(t->category), &(t->all));
		t->category = findCategory(t->category); // convert the category code of each product into the name
        p[no] = t;
		no++;
	}
	fclose(file);
	return no;
}

void printAllProducts(struct shop *p[], int size)
{   
    printf("> %d Products Loaded...\n\n", size);
    for (int i = 0; i < size; i++)
	{ 
		printf("[%02d] %-18s [%-4s] Total: %d\n", i+1, (p[i]->name), CNAME[(p[i]->category-1)], (p[i]->all)); 
	}
}

int addProduct(struct shop *p[], int size) 
{   

    struct shop* temp;
    temp = (struct shop*)malloc(sizeof(struct shop));;
    printf(">> Product name > ");
	scanf("%s", (temp->name));
    printf(">> Product Category (1:Food 2: Drink 3:Cleaning 4:Devices 5: Toys 6:Furnitures) > ");
	scanf("%d", &(temp->category));
    printf(">> Total > ");
	scanf("%d", &(temp->all));
	
	p[size] = temp;

    printf("> A new product is added.\n");
	printf("[%02d] %-18s [%-4s] Total: %d\n", size+1 ,(p[size]->name), CNAME[(p[size]->category-1)], (p[size]->all));

	return size+1; 
}

void editShop(struct shop *p[], int size) 
{   
    int newcode=0;
    char newname[100]={0};
	int newcategroy=0;
    int newall=0;

    printf("> Modify a Product\n");
	printf("> Enter the Code of the Product > ");
	scanf("%d", &newcode);

    for(int i=0; i<size; i++) {
        if(newcode == p[i]->code) {
            printf("> Selected Product: [%02d] %s [%s] Total: %d\n", i+1 ,(p[i]->name), CNAME[(p[i]->category-1)], (p[i]->all));
            printf("> Enter a New Name of the Product > ");
            scanf("%s", newname);
            strcpy(p[i]->name, newname);
            printf("> New Product Category (1:Food 2: Drink 3:Cleaning 4:Devices 5: Toys 6:Furnitures) > ");
            scanf("%d", &newcategroy);
            p[i]->category = newcategroy;
            printf("> New Total of the Product > ");
            scanf("%d", &newall);
            p[i]->all = newall;

            printf("\nProduct info modified.\n");
        } else {
            break;
        }     
    }
}

void findProduct(struct shop *p[], int size) 
{
    printf("> Search Products\n");
    printf("Choose one (1:by code, 2:by name, 3:by category) > ");
    int answer = 0;
    int thecode;
    char thename[30];
    int thecategory;
    scanf("%d", &answer);

    if(answer == 1) {
        printf("> Enter the code > ");
        scanf("%d", &thecode);
        printf("> Result:\n");
    
        for(int i=0; i<size; i++) {
            if(thecode == p[i]->code) {
                printf("[%02d] %s [%s] Total: %d\n", i+1 ,(p[i]->name), CNAME[(p[i]->category-1)], (p[i]->all));
            } 
            else {
                break;
            }
        }

    }
    else if(answer == 2) {
        printf("> Enter the Name > ");
        scanf("%s", thename);
        printf("> Result: \n");
        for(int i=0; i<size; i++) {
            if(strstr(p[i]->name, thename)) {
                printf("[%02d] %s [%s] Total: %d\n", i+1 ,(p[i]->name), CNAME[(p[i]->category-1)], (p[i]->all));
                break;
            } 
        }
    }
    if(answer == 3) {
        printf("> Enter the Category > ");
        scanf("%d", &thecategory);
        for(int i=0; i<size; i++) {
            for(int j=0; j<6;j++) {
                if(thecategory == p[i]->category) {
                    printf("[%02d] %s [%s] Total: %d\n", i+1 ,(p[i]->name), CNAME[(p[j]->category-1)], (p[i]->all));
                    break;
                }   
            }        
        }
    } else {
        printf("Error!\n");
    }
}

int deleteProduct(struct shop *p[], int size)
{
    int num;
    int yesno;
    printf("> Delete a Product\n");
    printf("> Enter the code of Products > ");
    scanf("%d", &num);

    for(int i=0; i<size; i++) {
		if(num-1 == i) {
			printf("> Channel Info.\n");
			printf("[%02d] %s [%s] Total: %d\n", i+1 ,(p[i]->name), CNAME[(p[i]->category-1)], (p[i]->all));
			printf("> Do you want to delete the channel? (1:Yes 0:No) > ");
			scanf("%d", &yesno);
			if(yesno == 1) {
				free(p[i]);
				for(int j=i; j<size-1; j++) {
					p[j]= p[j+1];
				}
				printf("Channel is deleted.\n");
				return size-1;
			} else {
				printf("> Canceled.\n");
				return size;
			}
		}
	}

    return size;
}


void saveProducts(struct shop *p[], int size) 
{
    printf("> All information of Products are saved into products.txt.\n");

    FILE *file;
	file = fopen("products.txt", "w");
	if(file==NULL) {
		printf("Fail to open the file.\n");
		return;
	}

    for (int i = 0; i < size; i++) { 
		fprintf(file, "%d %s %d %d\n", i+1, (p[i]->name), (p[i]->category), (p[i]->all));
	}

    fclose(file);

}


