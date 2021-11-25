#include "yzetmg.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];

void entertainment7(){
	clean();
	gtxy(0,1); 			
	printf(" 澪：\n"); 
	printf("   光阴似箭岁月如梭\n");
	printf("   四维空间是所有时间的三维空间的集合\n");
	printf("   那倘若将所有时间的二维空间结合起来\n");
	printf("   便会是一个在时间线上永无止境的扫雷\n");
	printf("   你，\n");
	printf("   想来尝试一下么？\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   规则参照经典9*9 10雷二维扫雷\n");
	printf("   雷图为9*19面板\n");
	printf("   分为左右两个9*10的面板，各会生成10个雷\n");
	printf("   每完成一个面板便会获得1个重生十字章\n");
	printf("   <更多隐藏规则请自行发现>\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);  
	printf("   终于，快结束了么。\n\n");
	printf("   |▔▔▔▔|                     |▔▔▔▔|\n"); 
	printf("   | ←返回 |                     | 开始 →|\n");
	printf("    ▔▔▔▔                       ▔▔▔▔ \n"); 
	
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
		  			case 1: //右键 
		   					break;
          			case 2: //左键
							if(Y>14&&Y<17){
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
		if(play7()){
			return;
		}
	}	
}
int play7(){
	clean();
	play7_frame();
	
	lx = 18;
	ly = 9;
	tl = 2;
	int revprop = 1,level = 0;
	p7_l(level);
	mr[0] = 1;
	
	struct Map newmap[9][19]={0,0,0}; 
	struct Map (*p)[19] = NULL;
    p = newmap;
	while(play7_event(p,level%2,9,&revprop)){
		level += mr[0];
		p7_l(level);
		revprop++;
		if(level>9999){
			return MessageBox(NULL,"Sorry\nI need to have a rest\nLEVEL:MAX","Ohhhh",MB_OK);
		}
		else if(level>100){
			mr[0] = 1;
			if(revprop>20){
				mr[0]++;
			}
			if(revprop>35){
				mr[0]++;
			}
			if(revprop>50){
				mr[0]++;
			}
			if(revprop>100){
				mr[0]++;
			}
			gtxy(57,4);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			printf("%2d",mr[0]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		}
	}
	char rv[100]="GAME OVER!\nLEVEL:";
	char s[6];
	itoa(level,s,10);
	strcat(rv,s);
	return MessageBox(NULL,rv,"END",MB_RETRYCANCEL)-4;
}
int play7_event(struct Map (*p)[19],int lr,int Nc,int *revp){//lr<0左雷图|1右雷图> 
	c_blank = 90;
	c_mine = 10;
	
	p_play7_map(lr,Nc);
	play7_set_mine(p,c_mine,Nc,lr);
	p7_m();
	p7_r(*revp);
	
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
		  			case 1: //右键
		   					break;
          			case 2: //左键
					  		{
          					if(X>65&&X<89&&Y>0&&Y<3){
          						//Sleep(100);
          						return 0;
					  		}
					  		if(X<lx+Nc*2*lr||Y<ly||X>lx+2*Nc+1+2*lr*Nc||Y>ly+Nc-1){
								break;
							}
							int u=(X-lx)/2,v=Y-ly;
							
          					if(play7_left_key(p,X,Y,Nc,lr)){
							    *revp-=mr[0];
								c_mine--;
								p7_m();					
          						p_resu(*revp,2*u+lx,v+ly);
          						if(*revp<0){
          							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
          							gtxy(2*u+lx,v+ly);
          							printf("×");
          							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          							p7_d_mine(p);
          							return 0;
								  }
							  }  
		   					break;
						   }
		  		}
			} 		 
		 	break; 
		}
		if(c_mine==c_blank){
			return 1;
		}
	}
	return 0;
}
void play7_set_mine(struct Map (*p)[19],int count,int Nc,int lr){
	empty_mine(p,Nc,lr);
	int x,y;
	srand(time(NULL));
	
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc+lr*10;
		if((*(*(p+x)+y)).mine==0)
		{
			(*(*(p+x)+y)).mine = 1;
			count--;
		}
	}
	play7_get_mine(p);
}
void empty_mine(struct Map (*p)[19],int Nc,int lr){
	int i,j;
	int Ncc = Nc;
	Ncc+=lr*9+1;
	for(i=0;i<Nc;i++){
		for(j=0+lr*9;j<Ncc;j++){
			(*(*(p+i)+j)).mine = 0;
			(*(*(p+i)+j)).show = 0;
		}
	}
}
void play7_get_mine(struct Map (*p)[19]){
	int i,j;	
	for(i=0;i<9;i++){
		for(j=0;j<19;j++){
			(*(*(p+i)+j)).nums = play7_get_mine_nums(p,i,j);
		}
	}
}
int play7_get_mine_nums(struct Map (*p)[19],int x,int y){
	int count=0;
	if(x>0){
		count+=(*(*(p+x-1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x-1)+y-1)).mine;
		}
		if(y<18){
			count+=(*(*(p+x-1)+y+1)).mine;
		}
	}
	if(x<8){
		count+=(*(*(p+x+1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x+1)+y-1)).mine;
		}
		if(y<18){
			count+=(*(*(p+x+1)+y+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(p+x)+y-1)).mine;
	}
	if(y<18){
		count+=(*(*(p+x)+y+1)).mine;
	}
	return count;
}
int play7_judge_board(struct Map (*p)[19],int x,int y,int Nc,int lr){
	if((*(*(p+x)+y)).show==1||(*(*(p+x)+y)).show==2){
		return 0;//已展开||标记 
	}
	if((*(*(p+x)+y)).mine==1){
		return -1;//雷
	}
	Nc--;
	if((*(*(p+x)+y)).nums==0){
		play7_open_zero_board(p,x,y,Nc,lr);
	}
	else{
		play7_show_board(p,x,y);
	}
	return 0;
}
void play7_open_zero_board(struct Map (*p)[19],int x,int y,int Nc,int lr){
	if((*(*(p+x)+y)).show==0){
		play7_show_board(p,x,y);
		if((*(*(p+x)+y)).nums==0){
			if(x>0){
				play7_open_zero_board(p,x-1,y,Nc,lr);
				if(y>9*lr){
					play7_open_zero_board(p,x-1,y-1,Nc,lr);
				}
				if(y<9+lr*9){
					play7_open_zero_board(p,x-1,y+1,Nc,lr);
				}
			}
			if(x<Nc){
				play7_open_zero_board(p,x+1,y,Nc,lr);
				if(y>lr*9){
					play7_open_zero_board(p,x+1,y-1,Nc,lr);
				}
				if(y<9+lr*9){
					play7_open_zero_board(p,x+1,y+1,Nc,lr);
				}
			}
			if(y>lr*9){
				play7_open_zero_board(p,x,y-1,Nc,lr);
			}
			if(y<9+lr*9){
				play7_open_zero_board(p,x,y+1,Nc,lr);
			}
		}
	}
}
void play7_show_board(struct Map (*p)[19],int i,int j){
	(*(*(p+i)+j)).show = 1;
	c_blank--;
	p_n_xy(lx+2*j,ly+i,(*(*(p+i)+j)).nums);
}
void play7_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |       游戏终止        ▏\n");
	printf(" ▕                     |                    |                   |-----------------------▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕--------------------------------------------------------------------------------------▏\n");
	int i;
	for(i=0;i<15;i++){
		printf(" ▕                                                                                      ▏\n");
	}
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("等级:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	printf("重生十字章:"); 
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("剩余雷数:");
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("* 禁止标雷");
	gtxy(47,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("* 重生消耗 1");
	gtxy(67,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("状态:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(36,7);
	printf("▼"); 
	gtxy(36,20);
	printf("▲");  
	gtxy(75,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("正常");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_play7_map(int lr,int Nc){
	int i,j;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc+1;j++){
			p_s_xy(lx+2*j+2*lr*Nc,ly+i);
		}
	}
}
int play7_left_key(struct Map (*p)[19],int x,int y,int Nc,int lr){
	int i=y-ly,j=(x-lx)/2;
	if(tl==2){
		if((*(*(p+i)+j)).nums!=0||(*(*(p+i)+j)).mine==1){
			play7_fir_pro(p,i,j,Nc,lr);
			play7_get_mine(p);
			}
		tl = 0;
	}
	if((*(*(p+i)+j)).show!=0){
		return 0;
	}
	if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show==0){
		(*(*(p+i)+j)).show=1;
		c_blank--;
		return 1;
	}
	play7_judge_board(p,i,j,Nc,lr);
	return 0;
}
void play7_fir_pro(struct Map (*p)[19],int x,int y,int Nc,int lr){
	if((*(*(p+x)+y)).mine==1){
		play7_change_loc(p,x,y,0,0,Nc,lr);
	}
	if(x>0){
		if((*(*(p+x-1)+y)).mine==1){
			play7_change_loc(p,x-1,y,1,0,Nc,lr);
		}
		if(y>0&&(*(*(p+x-1)+y-1)).mine==1){
			play7_change_loc(p,x-1,y-1,1,1,Nc,lr);
		}
		if(y<Nc-1&&(*(*(p+x-1)+y+1)).mine==1){
			play7_change_loc(p,x-1,y+1,1,-1,Nc,lr);
		}
	}
	if(x<Nc-1){
		if((*(*(p+x+1)+y)).mine==1){
			play7_change_loc(p,x+1,y,-1,0,Nc,lr);
		}
		
		if(y>0&&(*(*(p+x+1)+y-1)).mine==1){
			play7_change_loc(p,x+1,y-1,-1,1,Nc,lr);
		}
		if(y<Nc-1&&(*(*(p+x+1)+y+1)).mine==1){
			play7_change_loc(p,x+1,y+1,-1,-1,Nc,lr);
		}
	}
	if(y>0&&(*(*(p+x)+y-1)).mine==1){
		play7_change_loc(p,x,y-1,0,1,Nc,lr);
	}
	if(y<Nc-1&&(*(*(p+x)+y+1)).mine==1){
		play7_change_loc(p,x,y+1,0,-1,Nc,lr);
	}
}
int play7_judge_sat(struct Map (*p)[19],int i,int j,int x,int y,int Nc){
	if((i==x||i==x+1||i==x-1)&&(j==y||j==y+1||j==y-1)){
		return 0;
	}	
	if((*(*(p+i)+j)).mine==1){
		return 0;
	}
	return 1;
}
void play7_change_loc(struct Map (*p)[19],int x,int y,int ax,int ay,int Nc,int lr){
	int i,j,c=1;
	srand(time(NULL));
	while(c)
	{
		i = rand()%Nc;
		j = rand()%Nc;
		if(play7_judge_sat(p,i,j,x+ax,y+ay,Nc))
		{
			(*(*(p+i)+j)).mine = 1;
			(*(*(p+x)+y)).mine = 0;
			c--;
		}
	}		
}
void p7_m(){
	gtxy(36,4);
	printf("%2d",c_mine);
}
void p7_r(int r){
	gtxy(18,4);
	printf("%4d",r);
}
void p7_l(int l){
	gtxy(18,2);
	printf("%4d",l);
}
void p7_d_mine(struct Map (*p)[19]){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<19;j++){
			if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show!=1){
				gtxy(lx+2*j,ly+i);
				printf("×");
			}
		}
	}
}
