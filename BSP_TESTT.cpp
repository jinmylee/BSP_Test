#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include<math.h>
using namespace std;

#define Size 60
int Dungeon[Size][Size];

typedef struct Dugeonlocaton {
	int r1, c1, r2, c2;
	int r3, c3, r4, c4;
};

Dugeonlocaton divideDugeon(int depth, int r1, int c1, int r2, int c2) {
	Dugeonlocaton Location;

	if (depth == 0 || (r2 - r1 <= 10 || c2 - c1<= 10)) {
		for (int i = r1 + 2; i < r2 - 2; i++) {
			for (int j = c1 + 2; j < c2 - 2; j++) {
				Dungeon[i][j] = 1;
			}
		}
		return { r1 + 2, c1 + 2, r2 - 3, c2 - 3, r1 + 2, c1 + 2, r2 - 3, c2 - 3 };
		


	}

	int rLen = r2 - r1;
	int cLen = c2 - c1;
	Dugeonlocaton temp1, temp2;
	if (rLen / cLen > 1 || (cLen / rLen <= 1 && rand() % 2)) { 
		int divideNum = (r2 - r1) * (rand() % 3 + 4) / 10;
		//¹æ ºÐÇÒ
		temp1 = divideDugeon(depth - 1, r1, c1, r1 + divideNum, c2);
		temp2 = divideDugeon(depth - 1, r1 + divideNum, c1, r2, c2);

	
		Dungeon[temp1.r4 + 1][(temp1.c3 + temp1.c4) / 2] = 4;
		Dungeon[temp1.r4 + 2][(temp1.c3 + temp1.c4) / 2] = 4;
		Dungeon[temp2.r1 - 1][(temp2.c1 + temp2.c2) / 2] = 4;
		Dungeon[temp2.r1 - 2][(temp2.c1 + temp2.c2) / 2] = 4;
		int rmin = min((temp1.c3 + temp1.c4) / 2, (temp2.c1 + temp2.c2) / 2);
		int rmax = max((temp1.c3 + temp1.c4) / 2, (temp2.c1 + temp2.c2) / 2);
		for (int i = rmin; i <= rmax; i++) {
			Dungeon[temp2.r1 - 2][i] = 4;
		}
	}
	else {

		int divideNum = (c2 - c1) * (rand() % 3 + 4) / 10;
		
		temp1 = divideDugeon(depth - 1, r1, c1, r2, c1 + divideNum);
		temp2 = divideDugeon(depth - 1, r1, c1 + +divideNum, r2, c2);

		
		Dungeon[(temp1.r3 + temp1.r4) / 2][temp1.c4 + 1] = 3;
		Dungeon[(temp1.r3 + temp1.r4) / 2][temp1.c4 + 2] = 3;
		Dungeon[(temp2.r1 + temp2.r2) / 2][temp2.c1 - 1] = 3;
		Dungeon[(temp2.r1 + temp2.r2) / 2][temp2.c1 - 2] = 3;

		int rmin = min((temp1.r3 + temp1.r4) / 2, (temp2.r1 + temp2.r2) / 2);
		int rmax = max((temp1.r3 + temp1.r4) / 2, (temp2.r1 + temp2.r2) / 2);
		for (int i = rmin; i <= rmax; i++) {
			Dungeon[i][temp2.c1 - 2] = 3;
		}
	}
	Location.r1 = temp1.r1, Location.r2 = temp1.r2, Location.c1 = temp1.c1, Location.c2 = temp1.c2;
	Location.r3 = temp2.r3, Location.r4 = temp2.r4, Location.c3 = temp2.c3, Location.c4 = temp2.c4;

	return Location;
}





void CreateDugeon() {
	memset(Dungeon, 0, sizeof(Dungeon));
	divideDugeon(1, 0, 0, Size, Size);
}

void printDugeon() {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			printf("%d", Dungeon[i][j]);
		}
		printf("\n");
	}
}
int main(void){
	CreateDugeon();
	printDugeon();
}