#include "yzetmexb.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];

void entertainment_c2(){
	clean();
	gtxy(0,1); 			
	printf(" ������\n");
	printf("   \n");
	printf("   \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   \n");
	printf("   \n");
	printf("   \n");
	printf("   \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   HELP!!\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rt,st=0;
	while(1)
	{
	    ReadConsoleInput(hInput,&inRec,1,&numRead); 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{ 
		  		rt = mouseput();
		  		switch(rt){ 
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
							if(Y>9&&Y<12){
								if(X>3&&X<12){
          							return;
								  }
								else if(X>34&&X<43){
									st = 1;//start
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
		if(st==1){
			break;
		}
	}
	while(1){
		if(e_c2_play()){
			return;
		}
	}	
}
int e_c2_play(){
	lx=18;
	ly=9;	
	int nm = 9,rx = 4,ry = 4;
	int bmap[9][9] = {0};
	int nmap[9][9] = {0};
    
	clean();
	e_c1_frame();
	randomwalk(bmap);
	memcpy(nmap,bmap,81*sizeof(int));
	nmap[rx][ry] = 2;
	e_c1_p_map(nmap);
	nm = count_nm(nmap);
	e_c1_p_d(nm);
	
    HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rmt;
	while(1)
	{		
	    ReadConsoleInput(hInput,&inRec,1,&numRead); 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{
				rmt = mouseput();
		  		switch(rmt){ 
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
          					if(X>65&&X<89){
          						if(Y==4){
          							tc = 0;
          							rx = 4;
          							ry = 4;
          							memcpy(nmap,bmap,81*sizeof(int));
          							nmap[rx][ry] = 2;
									e_c1_p_map(nmap);
									nm = count_nm(nmap);
									e_c1_p_d(nm);
								  }
								else if(Y==6){
									tc = 0;
									return MessageBox(NULL,"Ah, you lost. \nAgain?","MISSION FAILED",MB_YESNO)-6;
								}
								break;
							}
							if(X>=lx&&Y>=ly&&X<=lx+17&&Y<ly+9){
								int rrx = Y-ly,rry = (X-lx)/2;
								if(e_c1_left_event(nmap,rrx,rry,rx,ry)){
									rx = rrx;
									ry = rry;
									e_c1_p_map(nmap);
									nm = count_nm(nmap);
									e_c1_p_d(nm);
									break;
								}
							}
		   					break;
				}
			} 		 
		 	break; 
		}
		if(nm == 0){
			tc = 0;
			return MessageBox(NULL,"Ah, you win. \nAgain?","MISSION COMPLETED",MB_YESNO)-6;
		}
	}
	return 0;
}
