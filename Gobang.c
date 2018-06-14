#include "Gamesupport.h"

broad tbroad;
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
	(tbroad.broad)[0][0]=NONE;
	steps=0;
	tsize.scan3x=5;
	tsize.scan3y=5;
	tsize.scan4x=9;
	tsize.scan4y=9;
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
		while(1){
			//printf("\n\"-1,-1\"to undo\n");
			ai(WorB);
			scanf("%d%*c%d",&todo.x0,&todo.y0);
			getchar();
			if (down(todo,WorB)) {
				if (winjudge(tbroad,todo,WorB)) {
					system("cls");
					putbroad(tbroad);
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
				scanf("%d%*c%d",&todo.x0,&todo.y0);
				getchar();
			}
			if (down(todo,WorB)) {
				if (winjudge(tbroad,todo,WorB)) {
					system("cls");
					putbroad(tbroad);
					break;
				}
				WorB*=-1;		
			}
			system("cls");
			putbroad(tbroad);
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
					system("cls");
					putbroad(tbroad);
					break;
				}
				WorB*=-1;		
			}
			system("cls");
			putbroad(tbroad);
		}
	}
	if (steps==225) {
		printf("DRAW!");
	} else {
		if (WorB==BLACK) {
			printf("BLACK is winner");
		} else {
			printf("WHITE is winner");
		}
	}
	return TRUE;
}
void putbroad(broad abroad) {
	printf("   ");		//打印棋盘
	for (int i=0; i<N; i++) {
		printf("%2d",i);
	}
	printf("\n     ");
	printf("\n");
	for (int j=0; j<N; j++) {
		printf("%2d  ",j);
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
	printf("\nsteps:%d",steps);
	printf("\nscaning times:%d",times);
	printf("\ntime cost:%dms",stop-start);
	printf("\nlastx:%d lasty:%d\n",tox,toy);
	return;
}
int down(coordinate todo,int WorB) {			//改变棋盘数据
	if (todo.x0>=0&&todo.y0>=0&&todo.x0<N&&todo.y0<N&&(tbroad.broad)[todo.x0][todo.y0]==NONE) {
		(tbroad.broad)[todo.x0][todo.y0]=WorB;
		tsize=expand(tsize,todo.x0,todo.y0);
		steps++;
		//hash^=status[WorB+1][x][y][x*y];//更新hash值
		return TRUE;
	}
	return FALSE;
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
/*int isDraw() {			//平局检测
	if (steps==225) {
		return TRUE;
	} else {
		return FALSE;
	}
}
void cheki() {			//悔棋
	if (x==-1&&y==-1) {
		n[lastx][lasty]=0;
		WorB*=-1;
		steps--;
		return;
	}
	return;
}*/

