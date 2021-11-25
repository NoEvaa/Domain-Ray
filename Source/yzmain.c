#include "yzmain.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];

void gtxy(int x,int y){//光标移动，X横坐标，Y纵坐标。
	while(tp){
		Sleep(10);
	}
	COORD  coord;
	coord.X=x;
	coord.Y=y;
	HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出句柄
	SetConsoleCursorPosition(a,coord);//以标准输出的句柄为参数设置控制台光标坐标
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
      return 1;//鼠标右键单击
    if (inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)  
      return 2;//鼠标左键单击
  }
} 
void HideCursor(){  //隐藏光标                  
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); 
}
void SetSize(short x,short y){//设置同样的缓冲区和窗口大小
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
                	p_status();//待修改 
				}
			}       
        }
}
void p_status(){
	tl = -2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gtxy(75,4);
	printf("超时");
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
void go_on(int c,int x,int y,int ax,int ay){//c<0左|1右>
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);//控制台窗口句柄 
	hInput = GetStdHandle(STD_INPUT_HANDLE);//输入设备句柄 
	int rt;
	while(1)
	{
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//读取1个输入事件 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{ 
		  		rt = mouseput();
		  		switch(rt){ 
		  			case 1: //右键 
		  					if(c==0){
          						break;
							  }
							if(X>=x&&Y>=y&&X<=x+ax&&Y<=y+ay){
								return;
							}
		   					break;
          			case 2: //左键
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

