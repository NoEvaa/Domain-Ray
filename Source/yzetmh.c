#include "yzetmh.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];

void entertainment8(){
	clean();
	gtxy(0,1); 		
	printf(" �Σ�\n");
	printf("   ������Ŀǰ������\n");
	printf("   Ҫ���������������ܱ��������״���ĸ�άɨ��\n");
	printf("   ʵ���ǽ������Ŵ粽����\n");
	printf("   ����ܿ�ͽ�̮����\n");
	printf("   �Ὣ�������֮��\n");
	printf("   ��ӡ�����һ������������\n");
	printf("   ������δ��ĳһ�죬��ӡ�ᱻ�ٴ�����\n");
	printf("   �����ܹ����ܳ������Ӵ������\n");
	printf("   �������\n");
	printf("   ֻ������\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   ������򵥵�9*9 10�׶�άɨ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   �ܸ����ܹ�������\n");
	printf("   �����ˣ��ҵ����� >>\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rt,st=0;
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
							if(Y>15&&Y<18){
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
		if(play8()){
			return;
		}
	}	
}
int play8(){	
	lx=18;
	ly=9;
	c_mine = 10;
	c_blank = 81;
	struct Map newmap[9][9]={0,0,0}; 
	struct Map (*p)[9] = NULL;
    p = newmap;
    int c_resj = c_mine;
    
	clean();
    play8_frame();
	play8_set_mine(p,c_mine,9);//

    HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rmt;
	while(1)
	{		
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//��ȡ1�������¼� 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{
				rmt = mouseput();
				if(X<lx||Y<ly||X>lx+17||Y>ly+8){
					break;
				}
		  		switch(rmt){ 
		  			case 1: //�Ҽ�
		  					play8_right_key(p,X,Y);
		  					gtxy(33,4);
		  					printf("%3d",c_mine);
		   					break;
          			case 2: //���
					  {
							int u=(X-lx)/2,v=Y-ly;
          					if(play8_left_key(p,X,Y,9)){
          						p8_d_mine(p);
          						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
          						gtxy(2*u+lx,v+ly);
          						printf("��");
          						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          						tc = 0;
          						return MessageBox(NULL,"��ô��Ҳ���䣿\n�ٸ���λ����\nһ��ҪӮ��!","DEFEAT",MB_YESNO)-6;
							}  
		   					break;
		   				}
				}
			} 		 
		 	break; 
		}
		if(c_blank==c_resj){
			tc = 0;
			return MessageBox(NULL,"Ah, Minesweeper, now farewell, adieu. ","MISSION COMPLETED",MB_OK);
		}
	}
	tc = 0;
	return 0;
}
void play8_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��--------------------------------------------------------------|                       ��\n");
	int i;
	for(i=0;i<15;i++){
		printf(" ��                                                              |                       ��\n");
	}
	printf("   ��������������������������������������������������������������������������������������  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("ʱ��:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("������:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("ʣ�� �� :");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");  
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(16,4);
	printf(" 10");
	gtxy(33,4);
	printf("%3d",c_mine);
	int j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			p_s_xy(lx+2*j,ly+i);
		}
	}
}
void play8_set_mine(struct Map (*p)[9],int count,int Nc){
	int x,y;
	srand(time(NULL));	
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		if((*(*(p+x)+y)).mine==0)
		{
			(*(*(p+x)+y)).mine = 1;
			count--;
		}
	}
	play8_get_mine(p);
}
void play8_get_mine(struct Map (*p)[9]){
	int i,j;	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			(*(*(p+i)+j)).nums = play8_get_mine_nums(p,i,j);
		}
	}
}
int play8_get_mine_nums(struct Map (*p)[9],int x,int y){
	int count=0;
	if(x>0){
		count+=(*(*(p+x-1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x-1)+y-1)).mine;
		}
		if(y<8){
			count+=(*(*(p+x-1)+y+1)).mine;
		}
	}
	if(x<8){
		count+=(*(*(p+x+1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x+1)+y-1)).mine;
		}
		if(y<8){
			count+=(*(*(p+x+1)+y+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(p+x)+y-1)).mine;
	}
	if(y<8){
		count+=(*(*(p+x)+y+1)).mine;
	}
	return count;
}
int play8_judge_board(struct Map (*p)[9],int x,int y,int Nc){
	if((*(*(p+x)+y)).show==1||(*(*(p+x)+y)).show==2){
		return 0;//��չ��||��� 
	}
	if((*(*(p+x)+y)).mine==1){
		return -1;//��
	}
	Nc--;
	if((*(*(p+x)+y)).nums==0){
		play8_open_zero_board(p,x,y,Nc);
	}
	else{
		play8_show_board(p,x,y);
	}
	return 0;
}
void play8_open_zero_board(struct Map (*p)[9],int x,int y,int Nc){
	if((*(*(p+x)+y)).show==0){
		play8_show_board(p,x,y);
		if((*(*(p+x)+y)).nums==0){
			if(x>0){
				play8_open_zero_board(p,x-1,y,Nc);
				if(y>0){
					play8_open_zero_board(p,x-1,y-1,Nc);
				}
				if(y<8){
					play8_open_zero_board(p,x-1,y+1,Nc);
				}
			}
			if(x<Nc){
				play8_open_zero_board(p,x+1,y,Nc);
				if(y>0){
					play8_open_zero_board(p,x+1,y-1,Nc);
				}
				if(y<8){
					play8_open_zero_board(p,x+1,y+1,Nc);
				}
			}
			if(y>0){
				play8_open_zero_board(p,x,y-1,Nc);
			}
			if(y<8){
				play8_open_zero_board(p,x,y+1,Nc);
			}
		}
	}
}
void play8_show_board(struct Map (*p)[9],int i,int j){
	(*(*(p+i)+j)).show = 1;
	c_blank--;
	p_n_xy(lx+2*j,ly+i,(*(*(p+i)+j)).nums);
}
int play8_left_key(struct Map (*p)[9],int x,int y,int Nc){
	int i=y-ly,j=(x-lx)/2;
	if(c_blank==81){
		if((*(*(p+i)+j)).nums!=0||(*(*(p+i)+j)).mine==1){
			play8_fir_pro(p,i,j,Nc);
			play8_get_mine(p);
			}
		tc = 1;
	}
	if((*(*(p+i)+j)).show!=0){
		return 0;
	}
	if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show==0){
		return 1;
	}
	play8_judge_board(p,i,j,Nc);
	return 0;
}
void play8_fir_pro(struct Map (*p)[9],int x,int y,int Nc){
	if((*(*(p+x)+y)).mine==1){
		play8_change_loc(p,x,y,0,0,Nc);
	}
	if(x>0){
		if((*(*(p+x-1)+y)).mine==1){
			play8_change_loc(p,x-1,y,1,0,Nc);
		}
		if(y>0&&(*(*(p+x-1)+y-1)).mine==1){
			play8_change_loc(p,x-1,y-1,1,1,Nc);
		}
		if(y<Nc-1&&(*(*(p+x-1)+y+1)).mine==1){
			play8_change_loc(p,x-1,y+1,1,-1,Nc);
		}
	}
	if(x<Nc-1){
		if((*(*(p+x+1)+y)).mine==1){
			play8_change_loc(p,x+1,y,-1,0,Nc);
		}
		
		if(y>0&&(*(*(p+x+1)+y-1)).mine==1){
			play8_change_loc(p,x+1,y-1,-1,1,Nc);
		}
		if(y<Nc-1&&(*(*(p+x+1)+y+1)).mine==1){
			play8_change_loc(p,x+1,y+1,-1,-1,Nc);
		}
	}
	if(y>0&&(*(*(p+x)+y-1)).mine==1){
		play8_change_loc(p,x,y-1,0,1,Nc);
	}
	if(y<Nc-1&&(*(*(p+x)+y+1)).mine==1){
		play8_change_loc(p,x,y+1,0,-1,Nc);
	}
}
int play8_judge_sat(struct Map (*p)[9],int i,int j,int x,int y){
	if((i==x||i==x+1||i==x-1)&&(j==y||j==y+1||j==y-1)){
		return 0;
	}	
	if((*(*(p+i)+j)).mine==1){
		return 0;
	}
	return 1;
}
void play8_change_loc(struct Map (*p)[9],int x,int y,int ax,int ay,int Nc){
	int i,j,c=1;
	srand(time(NULL));
	while(c)
	{
		i = rand()%Nc;
		j = rand()%Nc;
		if(play8_judge_sat(p,i,j,x+ax,y+ay))
		{
			(*(*(p+i)+j)).mine = 1;
			(*(*(p+x)+y)).mine = 0;
			c--;
		}
	}		
}
void p8_d_mine(struct Map (*p)[9]){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show!=1){
				gtxy(lx+2*j,ly+i);
				printf("��");
			}
		}
	}
}
void play8_right_key(struct Map (*p)[9],int x,int y){
	int i=y-ly,j=(x-lx)/2; 
	switch((*(*(p+i)+j)).show)
	{
		case 0:
			(*(*(p+i)+j)).show = 2;
			p_m_xy(lx+2*j,ly+i);
			c_mine--;
			break;
		case 1:
			break;
		case 2:
			(*(*(p+i)+j)).show = 0;
			p_s_xy(lx+2*j,ly+i);
			c_mine++;
			break;
	}
}
