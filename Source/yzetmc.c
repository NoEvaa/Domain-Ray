#include "yzetmc.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

void entertainment3(){
	clean();
	gtxy(0,1); 			
	printf(" Ӱ�ӣ�\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("   ����ը����������������Ĺ����д����ƻ�\n");
	printf("   ���������⵽�ƻ�\n");
	printf("   �Զ��޸���...\n   ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);
	printf("ERROR");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
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
		   					break;
          			case 2: //���
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

