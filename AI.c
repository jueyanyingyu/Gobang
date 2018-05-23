#include "Gamesupport.h"
int pointjudge() {
    return PorC*(metacount(1,0)+metacount(1,1)+metacount(0,1)+metacount(-1,1));
}
int metacount(int dx,int dy) {
    int side=0,oside=0;
    int flag=1;
    int wall=0;
    for(int i=1; i<5; i++) {
        if (x+i*dx>=0&&x+i*dx<N&&y+i*dy>=0&&y+i*dy<N) {
            if (m[x+i*dx][y+i*dy]==WorB) {
                side++;
            } else if (m[x+i*dx][y+i*dy]==NONE) {
                if (flag>0) {
                    if (m[x+(i+1)*dx][y+(i+1)*dy]==WorB) {
                        flag--;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                wall++;
                break;
            }
        }
    }
    for(int i=1; i<5; i++) {
        if (x-i*dx>=0&&x-i*dx<N&&y-i*dy>=0&&y-i*dy<N) {
            if ((m[x-i*dx][y-i*dy]==WorB) {
            oside++;
        } else if (m[x-i*dx][y-i*dy]==NONE) {
            if (flag>0) {
                    if (m[x-(i+1)*dx][y-(i+1)*dy]==WorB) {
                        flag--;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                wall++;
                break;
            }
        }
    }
    if(side+oside==4&&flag==1) {
        return LianWu;
    } else if (side+oside==3&&flag==1&&wall==0) {
        return HuoSi;
    } else if (side+oside==3&&flag==1&&wall==1) {
        return ChongSi;
    } else if (side+oside==3&&flag==0) {
        return ChongSi;
    } else if (side+oside==2&&flag==1&&wall==0) {
        return HuoSan;
    } else if (side+oside==2&&flag==0) {
        return HuoSan;
    } else if (side+oside==2&&wall==0) {
        return MianSan;
    } else {
        return Normal;
    }
}
void scanning(int level,int x,int y,int score) {
    if (level<floor) {
        for (int x=scan1x; x<=scan2x; x++) {
            for (int y=scan1y; y<=scan2y; y++) {
                if (m[x][y]=NONE) {
                    score+=pointjudge();
                    m[x][y]=WorB;
                    if (x-1>=0) {
                        scan1x=x-1;
                    }
                    if (y-1>=0) {
                        scan1y=y-1;
                    }
                    if (x+1<N) {
                        scan2x=x+1;
                    }
                    if (y+1<N) {
                        scan2y=y+1;
                    }
                    todownx[level]=x;
                    todowny[level]=y;
                    WorB*=-1;
                    PorC*=-1;
                    scanning(level+1,x,y,score);
                }
            }
        }
        else {
            if (score>maxscore) {
                maxscore=score;
                for(int i=0; i<floor; i++) {
                    todownmaxx[i]=todownx[i];
                    todownmaxy[i]=todowny[i];
                }
            }
        }
        return;
    }
}
