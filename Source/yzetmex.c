#include "yzetmex.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];

void extra(){//
	for(;;){
		switch(extra_choice()){
			case 0:
				return;
			case 1:
				entertainment_c1();
				break;
			case 2:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
			case 3:
				entertainment_c3();
				break;
			case 4:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
			case 5:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
		}
	}
}
int extra_choice(){// 
	clean();
	gtxy(0,1); 	
	printf("  |▔▔▔▔|\n"); 
	printf("  | ←返回 |\n"); 
	printf("   ▔▔▔▔       \n"); 
	printf("    ▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf("  ▕                      ▏\n");
	printf("  ▕   →无聊的炸弹人←   ▏\n");
	printf("  ▕xxxxxxxxxxxxxxxxxxxxxx▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅰ 逃亡!            ▏\n");
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅱ 量子炸弹!        ▏\n");	
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅲ 雷域密码术!      ▏\n");
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅳ                  ▏\n");
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅴ                  ▏\n");
	printf("  ▕                      ▏\n");
	printf("    ▔▔▔▔▔▔▔▔▔▔▔  "); 
	
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
		   					break;
          			case 2: //左键
          					if(X>2&&X<11&&Y>0&&Y<3){
          						return 0;//返回 
							  }
          					if(X>3&&X<26){
								if(Y==8||Y==9){
									return 1;
								}
								else if(Y==11||Y==12){
									return 2;
								}
								else if(Y==14||Y==15){
									return 3;
								}
								else if(Y==17||Y==18){
									return 4;
								}
								else if(Y==20||Y==21||Y==22){
									return 5;
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void entertainment_c1(){
	clean();
	gtxy(0,1); 			
	printf(" 影子：\n");
	printf("   炸弹人在入侵雷域的战役中大获全败\n");
	printf("   正不慌不忙地踏上了逃出雷域的道路\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   帮助炸弹人找到一条离开的道路吧\n");
	printf("   从绿格出发\n");
	printf("   每个格子只能经过一次\n");
	printf("   请一次走完所有白格吧\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   HELP!!\n\n");
	printf("   |▔▔▔▔|                     |▔▔▔▔|\n"); 
	printf("   | ←返回 |                     | 开始 →|\n");
	printf("    ▔▔▔▔                       ▔▔▔▔ \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rt,st=0;
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
		if(e_c1_play()){
			return;
		}
	}	
}
int e_c1_play(){
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
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//读取1个输入事件 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{
				rmt = mouseput();
		  		switch(rmt){ 
		  			case 1: //右键
		   					break;
          			case 2: //左键
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
void randomwalk(int bp[9][9]){
	int i= 4,j = 4;
	if(bp[i][j]==0){
		bp[i][j] = 1;
	}
	srand(time(NULL));	
	for(;;){
		int d = rand()%4;
		int dx = (d-1)%2,dy = (d-2)%2;
		/*
		rand()%4  0  1  2  3
		(d-1)%2  -1  0  1  0
		(d-2)%2   0 -1  0  1
		*/
		if(check_rw_walk(bp,i+dx,j+dy)){
			i += dx;
			j += dy;
			bp[i][j] = 1;
		}
		if(check_rw_stop(bp,i,j)){
			return;
		}
	}
}
int check_rw_stop(int bp[9][9],int x,int y){
	if(x>0){
		if(bp[x-1][y]==0){
			return 0;
		}
	}
	if(y>0){
		if(bp[x][y-1]==0){
			return 0;
		}
	}
	if(x<8){
		if(bp[x+1][y]==0){
			return 0;
		}
	}
	if(y<8){
		if(bp[x][y+1]==0){
			return 0;
		}
	}
	return 1;
}
int check_rw_walk(int bp[9][9],int x,int y){
	if(x>=0&&x<9&&y>=0&&y<9){
		if(bp[x][y]==0){
			return 1;
		}
	}
	return 0;
}
void e_c1_p_map(int bp[9][9]){
	int i,j;
	for(i=0;i<9;i++){
		gtxy(lx,ly+i);
		for(j=0;j<9;j++){
			if(bp[i][j]==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			}
			else if(bp[i][j]==2){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			}
			else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
			}
			printf("▇");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void e_c1_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |        *操作          ▏\n");
	printf(" ▕                     |                    |                   |-----------------------▏\n");
	printf(" ▕                     |                    |                   |     重新开始本局      ▏\n");
	printf(" ▕                     |                    |                   |-----------------------▏\n");
	printf(" ▕--------------------------------------------------------------|       终止本局        ▏\n");
	printf(" ▕                                                              |-----------------------▏\n");
	printf(" ▕                                                              |                       ▏\n");
	int i;
	for(i=0;i<13;i++){
		printf(" ▕                                                              |                       ▏\n");
	}
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("时间：");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("剩余空格数:");
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("状态：");
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("正常");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void e_c1_p_d(int nm){
	gtxy(30,4);
	printf("%2d",nm);
}
int count_nm(int bp[9][9]){
	int nm = 0,i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(bp[i][j]==1){
				nm++;
			}
		}
	}
	return nm;
}
int e_c1_left_event(int bp[9][9],int x,int y,int rx,int ry){
	if(bp[x][y]==0){
		return 0;
	}
	if(x==4&&y==4){	
		return 0;
	}
	if(((x-rx)==0&&(y-ry)<2&&(y-ry)>-2)||(y-ry)==0&&((x-rx)<2&&(x-rx)>-2)){
		if(tc==0){
			tc = 1;
		}
		bp[rx][ry] = 0;
		bp[x][y] = 2;
		return 1;
	}
	return 0;
}
