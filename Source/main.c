#include <stdio.h>
#include "yzprogress.h"
#define N 6

HANDLE hInput; //获取标准输入设备句柄 
INPUT_RECORD inRec;//返回数据记录 
DWORD numRead; //返回已读取的记录数 
int Y,X;//X和Y的坐标 

int c_mine,c_blank;//主要数据记录 
int lx=0,ly=0;//定位 
int tc=0,tl=0,tp=0;//计时器控制 
int mr[2];//备用数据记录 
int AIstep;

void progress();//主进程 

int main(int argc, char *argv[]) {
	HideCursor();
	SetSize(92,30);
	for(;;){ 
		//entertainment_c2();
		progress();
	}
	return 0;
}
void progress(){
	pthread_t tid; 
	int re;
	re = pthread_create(&tid,NULL,timer,NULL);//计时器线程 
	if(re!=0)
	{
		return; 
	}
	re = pthread_detach(tid);
	for(;;){
		switch(mode()){
			case 1:
				classic();
				break;
			case 2:
				contract();
				break;
			case 3:
				course();
				break;
			case 4:
				entertainment();
				break;
		}
	}
}















































//NoEvaa
