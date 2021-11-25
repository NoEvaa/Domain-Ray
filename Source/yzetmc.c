#include "yzetmc.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

void entertainment3(){
	clean();
	gtxy(0,1); 			
	printf(" 影子：\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("   由于炸弹人曾在入侵雷域的过程中大肆破坏\n");
	printf("   大量数据遭到破坏\n");
	printf("   自动修复中...\n   ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);
	printf("ERROR");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("\n\n");
	printf("   |▔▔▔▔|                     |▔▔▔▔|\n"); 
	printf("   | ←返回 |                     | 开始 →|\n");
	printf("    ▔▔▔▔                       ▔▔▔▔ \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
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
		   					break;
          			case 2: //左键
							if(Y>6&&Y<9){
								if(X>3&&X<12){
          							return;
								  }
								else if(X>34&&X<43){
									MessageBox(NULL,"No Available","ERROR",MB_OK);
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}

