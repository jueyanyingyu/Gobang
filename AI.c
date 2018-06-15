#include "Gamesupport.h"

extern broad tbroad;
extern int steps;
extern size tsize;
extern int times;
extern int status[3][N][N][N*N];
extern int hash;

int mscore[FLOOR];				//各层分数极值（用于剪枝）
int* hashlist;
int tox,toy;

coordinate ai(int WorB) {
    for (int i=0; i<FLOOR; i++) {
        if (i%2==0) {
            mscore[i]=Large;
        } else {
            mscore[i]=Small;
        }
    }
    coordinate todo;
    todo.score=scanning(0,tsize,COMPUTER,WorB,tbroad);
    todo.x0=tox;
    todo.y0=toy;
    //printf("\n%d %d %d",todo.score,todo.x0,todo.y0);
    //getchar();
    return todo;
}
int pointjudge(int x0,int y0,broad tpbd) {
    if ((tpbd.broad)[x0][y0]==NONE) {
        return 0;
    } else {
        return metacount(1,0,x0,y0,tpbd)+metacount(1,1,x0,y0,tpbd)+metacount(0,1,x0,y0,tpbd)+metacount(-1,1,x0,y0,tpbd);
    }
}								//单点计算分数
int metacount(int dx,int dy,int x0,int y0,broad tpbd) {
    int color=(tpbd.broad)[x0][y0];		//单个方向判断
    int side=0,oside=0;
    int sides=0;
    int osides=0;
    int flag1=1;
    int flag2=1;
    int wall=0;
    int score=0;
    for (int i=1; i<5; i++) {
        if (x0+i*dx>=0&&x0+i*dx<N&&y0+i*dy>=0&&y0+i*dy<N) {
            if ((tpbd.broad)[x0+i*dx][y0+i*dy]==color) {
                if (flag1==1) {
                    side++;
                } else {
                    sides++;
                }
            } else if ((tpbd.broad)[x0+i*dx][y0+i*dy]==NONE) {
                if (flag1>0) {
                    if ((tpbd.broad)[x0+(i+1)*dx][y0+(i+1)*dy]==color) {
                        flag1--;
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
        } else {
            wall++;
            break;
        }
    }
    for (int i=1; i<5; i++) {
        if (x0-i*dx>=0&&x0-i*dx<N&&y0-i*dy>=0&&y0-i*dy<N) {
            if ((tpbd.broad)[x0-i*dx][y0-i*dy]==color) {
                if (flag2==1) {
                    oside++;
                } else {
                    osides++;
                }
            } else if ((tpbd.broad)[x0-i*dx][y0-i*dy]==NONE) {
                if (flag2>0) {
                    if ((tpbd.broad)[x0-(i+1)*dx][y0-(i+1)*dy]==color) {
                        flag2--;
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
        } else {
            wall++;
            break;
        }
    }
    if (side+oside>=4) {			//返回类型
        score=LianWu;
    } else if (side+oside==3&&wall==0) {
        score=HuoSi;
    } else if (side+oside==3&&wall==1) {
        score=ChongSi;
    } else if (side+oside+sides+osides==3&&flag1+flag2==1) {
        score=ChongSi;
    } else if (side+oside==2&&wall==0) {
        score=HuoSan;
    } else if (side+oside+sides+osides==2&&flag1+flag2==1&&wall==0) {
        score=HuoSan;
    } else if (side+oside==2&&wall==1) {
        score=MianSan;
    } else if (side+oside+sides+osides==2&&flag1+flag2==1&&wall==1) {
        score=MianSan;
    } else if (side+oside==1&&wall==0) {
        score=HuoEr;
    } else if (side+oside+sides+osides==1&&flag1+flag2==1&&wall==0) {
        score=HuoEr;
    } else if (side+oside+sides+osides==1&&flag1+flag2==1&&wall==1) {
        score=MianEr;
    } else if (side+oside==1&&wall==1) {
        score=MianEr;
    } else if (side+oside==0&&wall==0) {
        score=DanYi;
    } else {
        score=Normal;
    }
    return score;
}
int broadcount(broad newbroad,size tpsize,int WorB) {
    int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
    int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
    int score;
    int scoreC=0;
    int scoreP=0;
    for (int k=tx3; k<=tx4; k++) {
        for (int l=ty3; l<=ty4; l++) {
            if ((newbroad.broad)[k][l]!=NONE) {
                score=pointjudge(k,l,newbroad);
                times++;
                if ((newbroad.broad)[k][l]==WorB) {
                    if (score>scoreP) {
                        scoreP=score;
                    }
                } else {
                    if (score>scoreC) {
                        scoreC=score;
                    }
                }
            }
        }
    }
    return scoreC-scoreP;
}
int gen(coordinate* cdlist,size tpsize,broad tpbd,int WorB) {
    int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
    int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
    int count=0;
    for (int x0=tx3; x0<=tx4; x0++) {
        for (int y0=ty3; y0<=ty4; y0++) {
            if ((tpbd.broad)[x0][y0]==NONE) {
                (cdlist[count]).x0=x0;
                (cdlist[count]).y0=y0;
                (tpbd.broad)[x0][y0]=WorB;
                (cdlist[count]).score=pointjudge(x0,y0,tpbd);
                (tpbd.broad)[x0][y0]=NONE;
                count++;
            }
        }
    }
    return count;
}
int scanning(int level,size tpsize,int PorC,int WorB,broad tpbd) {
    int x,y;
    int max=Small;
    int min=Large;
    coordinate cdlist[N*N];
    int length=gen(cdlist,tpsize,tpbd,WorB);
    sort(PorC,tpbd,cdlist,length);
    //迭代加深
    if ((cdlist[0]).score>=LianWu) {
        if (PorC==COMPUTER) {
            if (level==0) {
                tox=(cdlist[0]).x0;
                toy=(cdlist[0]).y0;
            }
            mscore[level]=Large;
            return Large;
        } else {
        	mscore[level]=Small;
            return Small;
        }
    } else {
        int tpscore;
        broad newbroad;
        for (int i=0; i<length; i++) {
            newbroad=tpbd;
            (newbroad.broad)[(cdlist[i]).x0][(cdlist[i]).y0]=WorB;
            if (level==FLOOR-1) {
                tpscore=broadcount(newbroad,tpsize,WorB);
            } else {
                tpscore=scanning(level+1,expand(tpsize,(*(cdlist+i)).x0,(*(cdlist+i)).y0),-1*WorB,-1*PorC,newbroad);
            }
            
            if (PorC==PLAYER&&tpscore<mscore[level]) {
                return tpscore;
            } else if (PorC==COMPUTER&&tpscore>mscore[level]) {
                return tpscore;
            }

            if (PorC==PLAYER&&tpscore<=min) {
                min=tpscore;
            } else if (PorC==COMPUTER&&tpscore>=max) {
                max=tpscore;
                if (level==0) {
                    x=(cdlist[i]).x0;
                    y=(cdlist[i]).y0;
                }
            }
        }
        if (PorC==PLAYER) {
            mscore[level]=min;
            return min;
        } else {
            mscore[level]=max;
            if (level==0) {
                tox=x;
                toy=y;
            }
            return max;
        }
    }
}
size expand(size tpsize,int x0,int y0) {
    size newsize=tpsize;
    if (x0==tpsize.scan3x&&x0-2>=0) {		//扩大扫描范围
        newsize.scan3x--;
    }
    if (y0==tpsize.scan3y&&y0-2>=0) {
        newsize.scan3y--;
    }
    if (x0==tpsize.scan4x&&x0+2<N) {
        newsize.scan4x++;
    }
    if (y0==tpsize.scan4y&&y0+2<N) {
        newsize.scan4y++;
    }
    return newsize;
}
void sort(int PorC,broad tpbd,coordinate* cdlist,int length) {
    int max=Small;
    int maxid;
    for (int i=0; i<length; i++) {
        for (int j=i; j<length; j++) {
            if ((*(cdlist+j)).score>max) {
                max=(*(cdlist+j)).score;
                maxid=j;
            }
        }
        coordinate temp=*(cdlist+maxid);
        *(cdlist+maxid)=*(cdlist+i);
        *(cdlist+i)=temp;
        max=Small;
    }
    return;
}
int kill(size tpsize,int PorC,int WorB,broad tpbd,int lastscore) {
    int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
    int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
    coordinate cdlist[N*N];
    int length=gen(cdlist,tpsize,tpbd,WorB);
    sort(PorC,tpbd,cdlist,length);
    if ((cdlist[0]).score>=LianWu) {
        if (PorC==PLAYER) {
            return Small;
        } else {
            return Large;
        }
    }
    broad newbroad;
    int tpscore;
    for (int i=0; i<length; i++) {
        newbroad=tpbd;
        
        if ((cdlist[i]).score<HuoSan) {
        	break;
		}
		
        if ((cdlist[i]).score<=lastscore) {
            (newbroad.broad)[(cdlist[i]).x0][(cdlist[i]).y0]=WorB;
            tpscore=kill(expand(tpsize,(*(cdlist+i)).x0,(*(cdlist+i)).y0),-1*PorC,-1*WorB,newbroad,(cdlist[i]).score);
        } else {
            if (PorC==PLAYER) {
                return broadcount(newbroad,tpsize,-1*WorB);
            } else {
                (newbroad.broad)[(cdlist[i]).x0][(cdlist[i]).y0]=WorB;
                return broadcount(newbroad,tpsize,WorB);
            }
        }

    }

}
/*
	int hashtp=zobrist(list,level,WorB);
	if (searchhash(hashtp)) {
		temp=list;
		temp.ifcut=1;
		return temp;
	} else {
		int length=sizeof(hashlist);
		hashlist=(int*)realloc(hashlist,length+sizeof(int));
		if (hashlist!=NULL) {
			*(hashlist+length/sizeof(int))=hashtp;
		}


		point tm;
		tm=scanning(level+1,scan3x,scan3y,scan4x,scan4y,-1*PorC,-1*WorB,list,tpbroad);
		m[x0][y0]=NONE;
		scan3x=tx3;					//回复范围
		scan3y=ty3;
		scan4x=tx4;
		scan4y=ty4;

		if (tm.ifwin==COMPUTER) {
			temp=tm;
			continue;
		} else if (tm.ifwin==PLAYER) {
			temp=tm;
			temp.ifcut=1;
			continue;
		}

		if (tm.ifcut==1) {			//检测剪枝与否
			continue;
		} else if (PorC==PLAYER&&tm.score<mscore[level]||PorC==COMPUTER&&tm.score>mscore[level]) {
			temp.ifcut=1;
			return temp;
		} else {
			if (PorC==COMPUTER&&tm.score>max) {
				max=tm.score;
				temp=tm;
			} else if (PorC==PLAYER&&tm.score<min) {
				min=tm.score;
				temp=tm;
			}
		}
	}
}
}
}
if (PorC==COMPUTER&&max>mscore[level]) {
	mscore[level]=max;
} else if(PorC==PLAYER&&min<mscore[level]) {
	mscore[level]=min;
}
return temp;
} else {
	for (int x0=tx3; x0<=tx4; x0++) {
		for (int y0=ty3; y0<=ty4; y0++) {
			if (m[x0][y0]==NONE) {
				list.todownx[level]=x0;
				list.todowny[level]=y0;
				int hashtp=zobrist(list,level);
				if (searchhash(hashtp)) {
					temp.ifcut=1;
					return temp;
				} else {
					times++;
					int length=sizeof(hashlist);
					hashlist=(int*)realloc(hashlist,length+sizeof(int));
					if (hashlist!=NULL) {
						*(hashlist+length/sizeof(int))=hashtp;
					}
					m[x0][y0]=WorB;
					for (int k=tx3; k<=tx4; k++) {
						for (int l=ty3; l<=ty4; l++) {
							if (m[k][l]!=NONE) {
								list.score+=pointjudge(k,l,PorC);
							}
						}
					}
					m[x0][y0]=NONE;
					if (PorC==PLAYER&&list.score<mscore[level]||PorC==COMPUTER&&list.score>mscore[level]) {
						temp.ifcut=1;
						return temp;
					} else {
						if (PorC==COMPUTER&&list.score>max) {
							max=list.score;
							temp=list;
						} else if (PorC==PLAYER&&list.score<min) {
							min=list.score;
							temp=list;
						}
					}
				}
			}
		}
	}
}
if (PorC==COMPUTER&&max>mscore[level]) {
	mscore[level]=max;
} else if(PorC==PLAYER&&min<mscore[level]) {
	mscore[level]=min;
}
return temp;
}
int MonteCarlo(int level,int scan3x,int scan3y,int scan4x,int scan4y,int PorC) {
	srand((unsigned)time(NULL));
	if (level==0) {
		int maxcount=0;
		int count;
		int tx3=scan3x,ty3=scan3y;		//扫描函数
		int tx4=scan4x,ty4=scan4y;
		for (int i=tx3; i<=tx4; i++) {
			for (int j=ty3; j<=ty4; j++) {
				if (m[i][j]==NONE) {
					m[i][j]=WorB;
					if (i==scan3x&&i-1>=0) {		//扩大扫描范围
						scan3x--;
					}
					if (j==scan3y&&j-1>=0) {
						scan3y--;
					}
					if (i==scan4x&&i+1<N) {

						scan4x++;
					}
					if (j==scan4y&&j+1<N) {
						scan4y++;
					}
					WorB*=-1;
					for (int i=0; i<COUNT; i++) {
						count+=MonteCarlo(level+1,scan3x,scan3y,scan4x,scan4y,-1*PorC);
					}
					WorB*=-1;
					if (count>maxcount) {
						maxx=i;
						maxy=j;
					}
					m[i][j]=NONE;
					scan3x=tx3;					//回复范围
					scan3y=ty3;
					scan4x=tx4;
					scan4y=ty4;
				}
				count=0;
			}
		}
		return 1;
	} else {
		int randx;
		int randy;
		int ifwin;
		do {
			randx=rand()%(scan4x-scan3x+1)+scan3x;
			randy=rand()%(scan4y-scan3y+1)+scan3y;
		} while (m[randx][randy]!=NONE);
		m[randx][randy]=WorB;
		if (randx==scan3x&&randx-1>=0) {		//扩大扫描范围
			scan3x--;
		}
		if (randy==scan3y&&randy-1>=0) {
			scan3y--;
		}
		if (randx==scan4x&&randx+1<N) {
			scan4x++;
		}
		if (randy==scan4y&&randy+1<N) {
			scan4y++;
		}
		if (pointjudge(randx,randy,PorC)<200000) {
			WorB*=-1;
			ifwin=MonteCarlo(level+1,scan3x,scan3y,scan4x,scan4y,-1*PorC);
			WorB*=-1;
		} else {
			if (PorC==COMPUTER) {
				cpybroad();
				return 1;
			} else {
				cpybroad();
				return 0;
			}
		}
		return ifwin;
	}
}
int zobrist(point list,int level,int WorB) {
	int hashtp=hash;
	for (int i=0; i<=level; i++) {
		hashtp^=status[WorB+1][list.todownx[i]][list.todowny[i]][list.todownx[i]*list.todowny[i]];
	}
	return hashtp;
}
int searchhash(int hashtp) {
	int length=sizeof(hashlist)/sizeof(int);
	for (int i=0; i<length; i++) {
		if (*(hashlist+i)==hashtp) {
			return TRUE;
		}
	}
	return FALSE;
}
*/
