#include "Gamesupport.h"

int main(int argc, char *argv[]) {
    int ComHd;
    printf("Select game mode\n");
    printf("'0' player vs player\n");
    printf("'1' player vs computer\n");
    if ('0'==getchar()) {
    	getchar();
        system("cls");
        putbroad();
        while(!winjudge()&&!isDraw()) {
            scanf("%d%*c%d",&x,&y);
            down();
            cheki();
            system("cls");
            putbroad();
        }
    } else if ('1'==getchar()) {
    	getchar();
        system("cls");
        putbroad();
        printf("'0' computer first\n");
        printf("'1' player first\n");
        if ('0'==getchar()) {
        	getchar();
			ComHd=BLACK;
        } else if ('1'==getchar()) {
        	getchar();
			ComHd=WHITE;
        }
        system("cls");
        putbroad();
        while(!winjudge()&&!isDraw()) {
            if (ComHd==WorB) {
            	ai();
			} else {
				scanf("%d%*c%d",&x,&y);
			}
            down();
            cheki();
            system("cls");
            putbroad();
        }
    } else {
    	return FALSE;
	}
    if (WorB==BLACK) {
        printf("BLACK is winner");
    } else {
        printf("WHITE is winner");
    }
    return TRUE;
}
void putbroad() {
    printf("   ");
    for (int i=0; i<N; i++) {
        printf("%2d",i);
    }
    printf("\n     ");
    printf("\n");
    for (int i=0; i<N; i++) {
        printf("%2d  ",i);
        for (int j=0; j<N; j++) {
            switch(n[j][i]) {
                case NONE: {
                        if (j==7&&i==7) {
                            printf("$ ");
                        } else if(i==14) {
                            printf("+ ");
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
    printf("\n\"-1,-1\"to undo\n");
    return;
}
int down() {
    char ch;
    while((ch=getchar())!='\n'&&ch!=EOF);
    if (x>=0&&y>=0&&x<N&&y<N&&n[x][y]==0) {
        n[x][y]=WorB;
        lastx=x;
        lasty=y;
        WorB=WorB*-1;
        steps++;
        return TRUE;
    }
    return FALSE;
}
int winjudge() {
    if(metajudge(1,0)) {
        return 1;
    } else if(metajudge(1,1)) {
        return 1;
    } else if(metajudge(0,1)) {
        return 1;
    } else if(metajudge(-1,1)) {
        return 1;
    } else {
        return 0;
    }
}
int metajudge(int dx,int dy) {
    int side=0,oside=0;
    //ÕýÏò¼ì²â
    for(int i=1; (x+i*dx>=0&&x+i*dx<N&&y+i*dy>=0&&y+i*dy<N)&&n[x+i*dx][y+i*dy]==WorB; i++) {
        side++;
    }
    for(int i=1; (x-i*dx>=0&&x-i*dx<N&&y-i*dy>=0&&y-i*dy<N)&&n[x-i*dx][y-i*dy]==WorB; i++) {
        oside++;
    }
    if(side+oside==4) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int isDraw() {
	if (steps==225-1) {
		return TRUE;
	} else {
		return FALSE;
	}
}
void cheki() {
    if (x==-1&&y==-1) {
        n[lastx][lasty]=0;
        return;
    }
    return;
}
void ai() {
	
}
