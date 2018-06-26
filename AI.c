#include "Gamesupport.h"

extern broad tbroad;
extern size tsize;
extern int steps;
extern int times;

int mscore[FLOOR];				//���������ֵ�����ڼ�֦��
int tox,toy;

coordinate ai(int WorB) {
	//��ʼ������Сֵ
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
	//�ĸ�����������
	if ((tpbd.broad)[x0][y0]==NONE) {
		return 0;
	} else {
		return metacount(1,0,x0,y0,tpbd)+metacount(1,1,x0,y0,tpbd)+metacount(0,1,x0,y0,tpbd)+metacount(-1,1,x0,y0,tpbd);
	}
}								//����������
int metacount(int dx,int dy,int x0,int y0,broad tpbd) {
	//���������ж�
	int color=(tpbd.broad)[x0][y0];
	//��ʼ��
	int side=0,oside=0;//һ��������
	int sides=0,osides=0;//��һ��������
	int flag1=1,flag2=1;//��¼����
	int wall=0;//����ǽ��
	int score=0;//����
	//����
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
	//�ж��������
	if (side+oside>=4) {			//��������
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
	//ȫ���ж�
	int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
	int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
	int score;
	int scoreC=0;
	int scoreP=0;
	//ɨ�������ҵ��ǿ�λ�ü������ȡ��߷�����
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
	//�Լ�ȡ���Է�ȡ��
	return scoreC-scoreP;
}
int gen(coordinate* cdlist,size tpsize,broad tpbd,int WorB) {
	int tx3=tpsize.scan3x,ty3=tpsize.scan3y;
	int tx4=tpsize.scan4x,ty4=tpsize.scan4y;
	int count=0;
	int tpscoreS;
	int tpscoreO;
	//ɨ�����̼����λ����˫������ ����¼�ۺ�ֵ�����ֱ������Է�ֵ
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
	int x,y;//��ʱ��¼���λ�� 
	int max=Small;
	int min=Large;
	broad newbroad;
	coordinate cdlist[N*N];
	int length=gen(cdlist,tpsize,tpbd,WorB);
	//���ۺϷ������� 
	sort(cdlist,0,length-1);
	if (level==0) {
		
		tox=(cdlist[0]).x0;
		toy=(cdlist[0]).y0;
	} 

	int tpscore;
	for (int i=0; i<length; i++) {
		//�ж��Ƿ��ֹ
		if ((cdlist[i]).scoreS>=LianWu) {
			if (PorC==COMPUTER) {
				return Large;
			} else {
				return Small;
			}
		}
		//������ʱ����׼��������� 
		newbroad=tpbd;
		(newbroad.broad)[(cdlist[i]).x0][(cdlist[i]).y0]=WorB;
		if (level==FLOOR-1) {
			//���һ�����ȫ�ַ��� 
			tpscore=broadcount(newbroad,tpsize,WorB);
		} else {
			//�ݹ���� 
			tpscore=scanning(level+1,expand(tpsize,(*(cdlist+i)).x0,(*(cdlist+i)).y0),-1*PorC,-1*WorB,newbroad);
		}
		//��֦���� 
		if (PorC==PLAYER&&tpscore<mscore[level]) {
			return tpscore;
		} else if (PorC==COMPUTER&&tpscore>mscore[level]) {
			return tpscore;
		}
		//δ��֦��¼�뼫ֵ 
		if (PorC==PLAYER) {
			if (tpscore<min) {
				min=tpscore;
			}
		} else {
			if (tpscore>max) {
				max=tpscore;
				//��һ�����λ�� 
				if (level==0) {
					x=(cdlist[i]).x0;
					y=(cdlist[i]).y0;
				}
			}
		}
	}
	//δ��֦����¼���Сֵ 
	if (PorC==PLAYER) {
		mscore[level]=min;
		return min;
	} else {
		mscore[level]=max;
		//��һ�����λ�� ,������ζ���Ļ�ѡ�ò��������� 
		if (max!=Small&&level==0) {
			tox=x;
			toy=y;
		}
		return max;
	}
}
size expand(size tpsize,int x0,int y0) {
	size newsize=tpsize;
	if (x0<=tpsize.scan3x&&x0-1>=0) {		//����ɨ�跶Χ
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
	//�鲢���� 
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
