#include <stdio.h>
#include "yzprogress.h"
#define N 6

HANDLE hInput; //��ȡ��׼�����豸��� 
INPUT_RECORD inRec;//�������ݼ�¼ 
DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
int Y,X;//X��Y������ 

int c_mine,c_blank;//��Ҫ���ݼ�¼ 
int lx=0,ly=0;//��λ 
int tc=0,tl=0,tp=0;//��ʱ������ 
int mr[2];//�������ݼ�¼ 
int AIstep;

void progress();//������ 

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
	re = pthread_create(&tid,NULL,timer,NULL);//��ʱ���߳� 
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
