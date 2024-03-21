// Enter your student ID and Fullname
// 22300085 김동헌  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 50

char LNAME[5][30]={"Graphite","Opal","Bronze","Silver","Gold"}; // labels by level

struct st_channel{
	char name[100]; // Channel name
	int count;	  // # of subscriptions
	int level;	  // index of level (0~4)
};

int loadData(struct st_channel* c[]); 
int findLevel(int num); 
void printStatistics(struct st_channel* c[], int size);
void printChannels(struct st_channel* c[], int size);
void pickupRandomChannels(struct st_channel* c[], int size);
void searchChannel(struct st_channel* c[], int size);
int addChannel(struct st_channel* c[], int size);
void updateChannel(struct st_channel* c[], int size);
int deleteChannel(struct st_channel* c[], int size);
void makeReport(struct st_channel* c[], int size); 

int main(void) {
	int no;	// amount of channels
	struct st_channel* clist[SIZE]; // channel list
	int menu; // menu number 

	srand(time(0));
	no = loadData(clist);

	while(1)
	{
		// Print menu
		printf("\n[1]List [2]Statistics [3]Random pick [4]Search [5]Add [6]Modify [7]Delete [8]Report [0]Exit\n> Enter a menu >> ");
		scanf("%d",&menu);	

		if(menu==1){
			printChannels(clist, no); // Print all list of channels
		}
		else if(menu==2){
			printStatistics(clist, no);	// Print statistics of each level
		}
		else if(menu==3){
			pickupRandomChannels(clist, no); // Pick up random channels
		}
		else if(menu==4){
			searchChannel(clist, no);	// Search a channel
		}
		else if(menu==5){
			no = addChannel(clist, no); // Add a channel
		}
		else if(menu==6){
			updateChannel(clist, no); // Modify a channel
		}
		else if(menu==7){
			no = deleteChannel(clist, no); // Delete a channel
		}
		else if(menu==8){
			makeReport(clist, no);	// Make a Report
		}
		else {
			break;
		}
	}
	return 0;
}

int loadData(struct st_channel* c[]){
	int no=0;
	FILE* file;

	file=fopen("channels.txt", "r");
	while(!feof(file)){
		struct st_channel* t = (struct st_channel*)malloc(sizeof(struct st_channel));
		int r=fscanf(file, "%s %d", t->name, &(t->count));
		if(r<2) break;
		t->level = findLevel(t->count);
		c[no] = t;
		no++;
	}
	fclose(file);
	printf("> %d channels are loaded.\n", no);
	return no;
}

int findLevel(int num){
	int range[5]={1000,10000,100000,1000000,10000000}; // range for level
	for(int j=0;j<5;j++)
		if(num<range[j])
			return j;
	return 0;
}

void printChannels(struct st_channel* c[], int size){
	printf("> List of Channels\n");
	for(int i=0; i<size; i++){
		printf("[%2d] %-20s %10d peoples [%s] \n",i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
	}
}

int addChannel(struct st_channel* c[], int size){
	struct st_channel* temp;
	printf("> Add a new Channel\n");
	temp = (struct st_channel*)malloc(sizeof(struct st_channel));
	printf("> Enter a name of channel > ");
	scanf("%s", temp->name);
	printf("> Enter an amount of peoples > ");
	scanf("%d", &(temp->count));
	temp->level = findLevel(temp->count);
	c[size] = temp;
	printf("> New channel is added.\n");
	printf("[%2d] %-20s %10d peoples [%s] \n",size+1, c[size]->name, c[size]->count,LNAME[c[size]->level]);
	return size+1;
}

void printStatistics(struct st_channel* c[], int size){
    printf("> Statistics of Channels\n");
	// save channel information channel[0] = total channels, channel[1] = average, channel[2] = Top channel
	float channel[5][3] = {0};
	// sum of each channels
	float sum[5]={0};
	// max of each channels
	int max[5]={0};
	// top channel name
	char topName[5][100];

	for(int i=0; i<size; i++) {
		for(int j=0; j<5; j++) {
			if(j == c[i]->level) {
				channel[j][0]++;
				sum[j] += c[i]->count;
				channel[j][1] = sum[j] / channel[j][0];

				if(c[i]->count > max[j]) {
				max[j] = c[i]->count;
				channel[j][2] = max[j];
				strcpy(topName[j], c[i]->name);
				}
			}
		}
	}

	for(int i=0; i<5; i++) {
		printf("%-10s : %-2.0f channels, Average %-10.1fpeoples, Top channel: %-17s (%-7.0f peoples)\n", LNAME[i], channel[i][0], channel[i][1], topName[i], channel[i][2]);
	}

}

void pickupRandomChannels(struct st_channel* c[], int size){
	printf("> Pick up Channels\n");
	printf("> How much channels you want to pick up? > ");
	int randCount=0; 
	scanf("%d", &randCount);

	for(int i=0; i<randCount; i++){
		int index = rand() % size;
		printf("[%2d] %s (%s level, %d peoples)\n", index+1, c[index]->name, LNAME[c[index]->level], c[index]->count);
	}

}

void searchChannel(struct st_channel* c[], int size){
	printf("> Search Channels\n");
	printf("> Choose one (1:by peoples 2:by names) > ");
	int answer; 
	int from; 
	int to;
	int total1=0;
	int total2=0;
	char names[100];
	scanf("%d", &answer);

	if(answer == 1) {
		printf("> Enter the range of peoples (from ~ to) > ");
		scanf("%d %d", &from, &to);
		printf("> Result:\n");
		for(int i=0; i<size; i++) {
			if(c[i]->count >= from && c[i]->count <= to) {
				printf("[%2d] %-20s %10d peoples [%s] \n", i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
				total1++;
			}
		}
		printf("%d channels are found.\n", total1);
	} else {
		printf("> Enter a names > ");
		scanf("%s", names);
		printf("> Result:\n");
		for(int i=0; i<size; i++) {
			if(strstr(c[i]->name, names)) {
				printf("[%2d] %-20s %10d peoples [%s] \n", i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
				total2++;
			}
		}
		printf("%d channels are found.\n", total2);
	}

}

void updateChannel(struct st_channel* c[], int size){
	printf("> Modify a new Channel\n");
	printf("> Enter a number of channel > ");
	int no;
	int total;
	char newname[100];
	int newpeople=0;
	scanf("%d", &no);
	
	if(no > size) {
		printf("> Wrong number.\n");
	}
	
	for(int i=0; i<size; i++) {
		if(no == i && no <= total) {
			printf("> Channel Info.\n");
			printf("[%2d] %-20s %10d peoples [%s] \n", i, c[i]->name, c[i]->count,LNAME[c[i]->level]);
			printf("> Eneter a new name of channel > ");
			scanf("%s", newname);
			strcpy(c[i-1]->name, newname);
			printf("> Eneter a new amount of peoples > ");
			scanf("%d", &newpeople);
			c[i-1]->count = newpeople;
			printf("> Channel info. is modified.\n");

		}
	}
	
}

int deleteChannel(struct st_channel* c[], int size){
	int no, yesno;
	printf("> Delete a new Channel\n");
	printf("> Enter a number of channel > ");
	scanf("%d", &no);

	for(int i=0; i<size; i++) {
		if(no-1 == i) {
			printf("> Channel Info.\n");
			printf("[%2d] %-20s %10d peoples [%s] \n", i+1, c[i]->name, c[i]->count,LNAME[c[i]->level]);
			printf("> Do you want to delete the channel? (1:Yes 0:No) > ");
			scanf("%d", &yesno);
			if(yesno == 1) {
				free(c[i]);
				for(int j=i; j<size-1; j++) {
					c[j]= c[j+1];
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


void makeReport(struct st_channel* c[], int size){


}