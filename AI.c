#include "Gamesupport.h"

extern broad tbroad;
extern size tsize;
extern int steps;
extern int times;

int mscore[FLOOR];				//各层分数极值（用于剪枝）
int tox,toy;

coordinate ai(int WorB) {
	//初始化极大极小值
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
	return todo;
}
int pointjudge(int x0,int y0,broad tpbd) {
	//四个方向分数求和
	if ((tpbd.broad)[x0][y0]==NONE) {
		return 0;
	} else {
		return metacount(1,0,x0,y0,tpbd)+metacount(1,1,x0,y0,tpbd)+metacount(0,1,x0,y0,tpbd)+metacount(-1,1,x0,y0,tpbd);
	}
}								//单点计算分数
int metacount(int dx,int dy,int x0,int y0,broad tpbd) {
	//单个方向判断
	int color=(tpbd.broad)[x0][y0];
	//初始化
	int side=0,oside=0;//一侧连续子
	int sides=0,osides=0;//跳一子连续子
	int flag1=1,flag2=1;//纪录跳子
	int wall=0;//两侧墙数
	int score=0;//分数
	//两侧
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
	//判断输出分数
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
	//全局判断
	int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
	int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
	int score;
	int scoreC=0;
	int scoreP=0;
	//扫描棋盘找到非空位置计算分数取最高分棋型
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
	//自己取正对方取负
	return scoreC-scoreP;
}
int gen(coordinate* cdlist,size tpsize,broad tpbd,int WorB) {
	int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
	int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
	int count=0;
	int tpscoreS;
	int tpscoreO;
	//扫描棋盘计算空位对于双方分数 ，纪录综合值，并分别保留各自分值
	for (int x0=tx3; x0<=tx4; x0++) {
		for (int y0=ty3; y0<=ty4; y0++) {
			if ((tpbd.broad)[x0][y0]==NONE) {
				(cdlist[count]).x0=x0;
				(cdlist[count]).y0=y0;
				(tpbd.broad)[x0][y0]=WorB;
				tpscoreS=pointjudge(x0,y0,tpbd);
				(tpbd.broad)[x0][y0]=NONE;
				(tpbd.broad)[x0][y0]=-1*WorB;
				tpscoreO=pointjudge(x0,y0,tpbd);
				(tpbd.broad)[x0][y0]=NONE;
				(cdlist[count]).scoreS=tpscoreS;
				(cdlist[count]).scoreO=tpscoreO;
				(cdlist[count]).score=tpscoreS+tpscoreO;
				count++;
			}
		}
	}
	return count;
}
int scanning(int level,size tpsize,int PorC,int WorB,broad tpbd) {
	int x,y;//临时记录最好位置 
	int max=Small;
	int min=Large;
	broad newbroad;
	coordinate cdlist[N*N];
	int length=gen(cdlist,tpsize,tpbd,WorB);
	//按综合分数排序 
	sort(cdlist,0,length-1);
	if (level==0) {
		
		tox=(cdlist[0]).x0;
		toy=(cdlist[0]).y0;
	} 

	int tpscore;
	for (int i=0; i<length; i++) {
		//判断是否截止
		if ((cdlist[i]).scoreS>=LianWu) {
			if (PorC==COMPUTER) {
				return Large;
			} else {
				return Small;
			}
		}
		//更改临时棋盘准备传入参数 
		newbroad=tpbd;
		(newbroad.broad)[(cdlist[i]).x0][(cdlist[i]).y0]=WorB;
		if (level==FLOOR-1) {
			//最后一层分析全局分数 
			tpscore=broadcount(newbroad,tpsize,WorB);
		} else {
			//递归计算 
			tpscore=scanning(level+1,expand(tpsize,(*(cdlist+i)).x0,(*(cdlist+i)).y0),-1*PorC,-1*WorB,newbroad);
		}
		//剪枝部分 
		if (PorC==PLAYER&&tpscore<mscore[level]) {
			return tpscore;
		} else if (PorC==COMPUTER&&tpscore>mscore[level]) {
			return tpscore;
		}
		//未剪枝则录入极值 
		if (PorC==PLAYER) {
			if (tpscore<min) {
				min=tpscore;
			}
		} else {
			if (tpscore>max) {
				max=tpscore;
				//第一层更新位置 
				if (level==0) {
					x=(cdlist[i]).x0;
					y=(cdlist[i]).y0;
				}
			}
		}
	}
	//未剪枝则更新极大极小值 
	if (PorC==PLAYER) {
		mscore[level]=min;
		return min;
	} else {
		mscore[level]=max;
		//第一层更新位置 ,无论如何都输的话选该步最有利的 
		if (max!=Small&&level==0) {
			tox=x;
			toy=y;
		}
		return max;
	}
}
size expand(size tpsize,int x0,int y0) {
	size newsize=tpsize;
	if (x0<=tpsize.scan3x&&x0-1>=0) {		//扩大扫描范围
		newsize.scan3x=x0-1;
	}
	if (y0<=tpsize.scan3y&&y0-1>=0) {
		newsize.scan3y=y0-1;
	}
	if (x0>=tpsize.scan4x&&x0+1<N) {
		newsize.scan4x=x0+1;
	}
	if (y0>=tpsize.scan4y&&y0+1<N) {
		newsize.scan4y=y0+1;
	}
	return newsize;
}
void sort(coordinate* cdlist,int begin,int end) {
	//归并排序 
	if (end==begin) {
		return;
	} else {
		coordinate tplist[end-begin+1];
		sort(cdlist,begin,(begin+end-1)/2);
		sort(cdlist,(begin+end+1)/2,end);
		for (int i=0,j=begin,k=(begin+end+1)/2; i<end-begin+1; i++) {
			if (j<=(begin+end-1)/2&&k<=end) {
				if ((*(cdlist+j)).score>(*(cdlist+k)).score) {
					tplist[i]=*(cdlist+j);
					j++;
				} else {
					tplist[i]=*(cdlist+k);
					k++;
				}
			} else if (j>(begin+end-1)/2) {
				tplist[i]=*(cdlist+k);
				k++;
			} else {
				tplist[i]=*(cdlist+j);
				j++;
			}
		}
		for (int i=0; i<end-begin+1; i++) {
			*(cdlist+begin+i)=tplist[i];
		}
		return;
	}
}
