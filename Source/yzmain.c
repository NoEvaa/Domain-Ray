#include "yzmain.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];

void gtxy(int x,int y){//����ƶ���X�����꣬Y�����ꡣ
	while(tp){
		Sleep(10);
	}
	COORD  coord;
	coord.X=x;
	coord.Y=y;
	HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼������
	SetConsoleCursorPosition(a,coord);//�Ա�׼����ľ��Ϊ�������ÿ���̨�������
}
void timer_event(int t){	
	COORD  coo;
	coo.X=15;
	coo.Y=2;
	HANDLE b=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(b,coo);
	printf("%4d",t);
}
int mouseput(){
  while(1)
  {
    COORD pos = {0,0};
    ReadConsoleInput(hInput,&inRec,1,&numRead);
    pos = inRec.Event.MouseEvent.dwMousePosition;
    Y = (int)pos.Y;
    X = (int)pos.X;
    if (inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==RIGHTMOST_BUTTON_PRESSED)  
      return 1;//����Ҽ�����
    if (inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)  
      return 2;//����������
  }
} 
void HideCursor(){  //���ع��                  
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); 
}
void SetSize(short x,short y){//����ͬ���Ļ������ʹ��ڴ�С
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
   	COORD pos = {x,y};
   	SMALL_RECT rc = {0,0,x-1,y-1};
   	SetConsoleWindowInfo(hOut,TRUE,&rc);
   	SetConsoleScreenBufferSize(hOut,pos);
}
void *timer(void *arg){
	int t;
	while(1)
        {
            t = 1;
            while(tc)
            {
            	Sleep(900);
            	tp=1;
            	Sleep(100);
            	timer_event(t);
            	tp=0;
                t+=1;
                if(tl==1&&t>301){
                	p_status();//���޸� 
				}
			}       
        }
}
void p_status(){
	tl = -2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gtxy(75,4);
	printf("��ʱ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void clean(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	int i;
	for(i=0;i<30;i++){
		gtxy(0,i);
		printf("                                                                                              ");
	}
}
void go_on(int c,int x,int y,int ax,int ay){//c<0��|1��>
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);//����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);//�����豸��� 
	int rt;
	while(1)
	{
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//��ȡ1�������¼� 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{ 
		  		rt = mouseput();
		  		switch(rt){ 
		  			case 1: //�Ҽ� 
		  					if(c==0){
          						break;
							  }
							if(X>=x&&Y>=y&&X<=x+ax&&Y<=y+ay){
								return;
							}
		   					break;
          			case 2: //���
          					if(c==1){
          						break;
							  }
							if(X>=x&&Y>=y&&X<=x+ax&&Y<=y+ay){
								return;
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
} 

