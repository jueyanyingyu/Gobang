#define LianWu 1000
#define HuoSi 900
#define ChongSi 300
#define HuoSan 200
#define MianSan 100
#define Normal 50

#define floor 4

int todownx[floor];
int todowny[floor];
int todownmaxx[floor];
int todownmaxy[floor];
int maxscore=0;

int pointjudge();
int metacount(int dx,int dy);
void scanning(int level,int x,int y,int score);
