#include "Gamesupport.h"

broad tbroad;
broad history[N*N];
coordinate historyxy[N*N];
size historysize[N*N];
int steps;				//步骤
size tsize;
int times;				//检索次数
int status[3][N][N][N*N];//白 空 黑 x y rand
int hash;
clock_t start;
clock_t stop;		//计时工具

extern int tox,toy;

int main(int argc, char *argv[]) {
	srand(time(NULL));
	times=0;
	tox=7;
	toy=7;
	tsize.scan3x=7;
	tsize.scan3y=7;
	tsize.scan4x=7;
	tsize.scan4y=7;
	(tbroad.broad)[0][0]=NONE;
	history[0]=tbroad;
	(historyxy[0]).x0=tox;
	(historyxy[0]).y0=toy;
	historysize[0]=tsize;
	steps=0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<N; j++) {
			for(int k=0; k<N; k++) {
				for(int l=0; l<N*N; l++) {
					status[i][j][k][l]=rand()%8192;
				}
			}
		}
	}
	hash=0;
	/*
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			hash^=status[n[i][j]+1][i][j][i*j];
		}
	}	*/				//初始化全局变量
	printf("Select game mode\n");
	printf("'0' player vs player\n");
	printf("'1' player vs computer\n");
	printf("'2' computer vs computer\n");
	coordinate todo;
	int WorB=BLACK;
	int gamemode;		//选择游戏类型
	scanf("%d",&gamemode);
	if (gamemode==0) {
		getchar();
		system("cls");
		putbroad(tbroad);
		while(1) {
			//printf("\n\"-1,-1\"to undo\n");
			todo=input(todo);
			if (down(todo,WorB)) {
				if (winjudge(tbroad,todo,WorB)) {
					break;
				} else if(isDraw()) {
					break;
				}
				WorB*=-1;
			}
			system("cls");
			putbroad(tbroad);
		}
	} else if (gamemode==1) {
		getchar();
		system("cls");
		printf("'0' computer first\n");
		printf("'1' player first\n");
		int ComHd;
		if ('0'==getchar()) {
			ComHd=BLACK;
		} else {
			ComHd=WHITE;
		}
		getchar();
		system("cls");
		putbroad(tbroad);
		while(1) {
			if (ComHd==WorB) {
				times=0;
				printf("waiting...");
				start=clock();
				todo=ai(WorB);
				stop=clock();
			} else {
				todo=input(todo);
			}
			if (down(todo,WorB)) {
				if (winjudge(tbroad,todo,WorB)) {
					break;
				} else if(isDraw()) {
					break;
				}
				WorB*=-1;
			}
			system("cls");
			putbroad(tbroad);
			printf("\nscaning times:%d",times);
			printf("\ntime cost:%dms\n",stop-start);
		}
	} else {
		getchar();
		system("cls");
		putbroad(tbroad);
		while(1) {
			times=0;
			printf("waiting...\n");
			start=clock();
			todo=ai(WorB);
			stop=clock();
			if (down(todo,WorB)) {
				if (winjudge(tbroad,todo,WorB)) {
					break;
				} else if(isDraw()) {
					break;
				}
				WorB*=-1;
			}
			system("cls");
			putbroad(tbroad);
			printf("\nscaning times:%d",times);
			printf("\ntime cost:%dms\n",stop-start);
		}
	}
	system("cls");
	putbroad(tbroad);
	if (steps==225) {
		printf("\nDRAW!");
	} else {
		if (WorB==BLACK) {
			printf("\nBLACK is winner");
		} else {
			printf("\nWHITE is winner");
		}
	}
	return TRUE;
}
void putbroad(broad abroad) {
	printf("   0 1 2 3 4 5 6 7 8 91011121314\n");
	for (int j=0; j<N; j++) {
		printf("%2d ",j);
		for (int i=0; i<N; i++) {
			switch((abroad.broad)[i][j]) {
				case NONE: {
					if (j==7&&i==7) {
						printf("$ ");
					} else {
						printf("+ ");
					}
					break;
				}
				case BLACK: {
					printf("X ");
					break;
				}
				case WHITE: {
					printf("O ");
					break;
				}
				default : {
					break;
				}
			}
		}
		printf("\n");
	}
	printf("\nsteps:%d player:",steps+1);
	if (steps%2==0) {
		printf("X\n");
	} else {
		printf("O\n");
	}
	if (steps!=0) {
		printf("\nlastx:%d lasty:%d\n",tox,toy);
	}
	return;
}
int down(coordinate todo,int WorB) {			//改变棋盘数据
	if (todo.x0>=0&&todo.y0>=0&&todo.x0<N&&todo.y0<N&&(tbroad.broad)[todo.x0][todo.y0]==NONE) {
		(tbroad.broad)[todo.x0][todo.y0]=WorB;
		tsize=expand(tsize,todo.x0,todo.y0);
		steps++;
		history[steps]=tbroad;
		(historyxy[steps]).x0=todo.x0;
		(historyxy[steps]).y0=todo.y0;
		historysize[steps]=tsize;
		//hash^=status[WorB+1][x][y][x*y];//更新hash值
		tox=todo.x0;
		toy=todo.y0;
		return TRUE;
	} else {
		return FALSE;
	}
}
int winjudge(broad abroad,coordinate todo,int WorB) {		//胜利判断
	if(metajudge(abroad,todo,1,0,WorB)) {
		return 1;
	} else if(metajudge(abroad,todo,1,1,WorB)) {
		return 1;
	} else if(metajudge(abroad,todo,0,1,WorB)) {
		return 1;
	} else if(metajudge(abroad,todo,-1,1,WorB)) {
		return 1;
	} else {
		return 0;
	}
}						//单个方向胜利判断
int metajudge(broad abroad,coordinate todo,int dx,int dy,int WorB) {
	int side=0,oside=0;
	for(int i=1; todo.x0+i*dx>=0&&todo.x0+i*dx<N&&todo.y0+i*dy>=0&&todo.y0+i*dy<N&&(abroad.broad)[todo.x0+i*dx][todo.y0+i*dy]==WorB; i++) {
		side++;
	}
	for(int i=1; (todo.x0-i*dx>=0&&todo.x0-i*dx<N&&todo.y0-i*dy>=0&&todo.y0-i*dy<N)&&(abroad.broad)[todo.x0-i*dx][todo.y0-i*dy]==WorB; i++) {
		oside++;
	}
	if(side+oside>=4) {
		return TRUE;
	} else {
		return FALSE;
	}
}
void gotoxy(int x, int y) {
	COORD coord = {x+3, y+1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
coordinate input(coordinate todo) {
	gotoxy(2*tox,toy);
	char command='-';
	int i,j;
	int x=2*tox;
	int y=toy;
	do {
		i=0;
		j=0;
		command=getch();
		switch (command) {
			case 's': {
				i=0;
				j=1;
				break;
			}
			case 'd': {
				i=2;
				j=0;
				break;
			}
			case 'w': {
				i=0;
				j=-1;
				break;
			}
			case 'a': {
				i=-2;
				j=0;
				break;
			}
			default: {
				break;
			}
		}
		if (x+i<0||x+i>=2*N) {
			i=0;
		}
		if (y+j<0||y+j>=N) {
			j=0;
		}
		gotoxy(x+i,y+j);
		x=x+i;
		y=y+j;
		if (command==27) {
			if (cheki()) {
				todo.x0=-1;
				todo.y0=-1;
				return todo;
			}
		}
	} while (command!=' ');
	todo.x0=x/2;
	todo.y0=y;
	return todo;
}
int isDraw() {			//平局检测
	if (steps==225) {
		return TRUE;
	} else {
		return FALSE;
	}
}
int cheki() {			//悔棋
	if (steps>1) {
		steps-=2;
		tbroad=history[steps];
		tox=(historyxy[steps]).x0;
		toy=(historyxy[steps]).y0;
		tsize=historysize[steps];
		return TRUE;
	} else {
		return FALSE;
	}
}

