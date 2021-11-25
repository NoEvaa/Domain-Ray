#include "yzgame.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];

void set_mine(struct Map (*p)[N][N][N],int count,int Nc){
	int x,y,z,c=count;
	srand(time(NULL));
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		z = rand()%Nc;
		if((*(*(*(*p+x)+y)+z)).mine==0)
		{
			(*(*(*(*p+x)+y)+z)).mine = 1;
			count--;
		}
	}
	while(c)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		z = rand()%Nc;
		if((*(*(*(*(p+1)+x)+y)+z)).mine==0)
		{
			(*(*(*(*(p+1)+x)+y)+z)).mine = 1;
			c--;
		}
	}
}
void get_mine(struct Map (*p)[N][N][N],int Nc){
	int i,j,k,t;
	for(t=0;t<2;t++){	
		for(i=0;i<Nc;i++){
			for(j=0;j<Nc;j++){
				for(k=0;k<Nc;k++){
					(*(*(*(*(p+t)+i)+j)+k)).nums = get_mine_nums(p,i,j,k,t,Nc);
				}
			}
		}
	}
}
int get_mine_nums(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	int count=0;
	Nc--;
	if(x>0){
		count+=(*(*(*(*(p+t)+x-1)+y)+z)).mine;
	}
	if(x<Nc){
		count+=(*(*(*(*(p+t)+x+1)+y)+z)).mine;
	}
	if(y>0){
		count+=(*(*(*(*(p+t)+x)+y-1)+z)).mine;
	}
	if(y<Nc){
		count+=(*(*(*(*(p+t)+x)+y+1)+z)).mine;
	}
	if(z>0){
		count+=(*(*(*(*(p+t)+x)+y)+z-1)).mine;
	}
	if(z<Nc){
		count+=(*(*(*(*(p+t)+x)+y)+z+1)).mine;
	}
	count+=(*(*(*(*(p+1-t)+x)+y)+z)).mine;
	return count;
}
int judge_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).show==1||(*(*(*(*(p+t)+x)+y)+z)).show==2){
		return 0;//已展开||标记 
	}
	if((*(*(*(*(p+t)+x)+y)+z)).mine==1){
		return -1;//雷 
	}
	Nc--;
	if((*(*(*(*(p+t)+x)+y)+z)).nums==0){
		open_zero_board(p,x,y,z,t,Nc);
	}
	else{
		show_board(p,x,y,z,t,Nc);
	}
	open_t_board(p,x,y,z,1-t,Nc);
	return 0;	
}
void open_zero_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).show==0){
		show_board(p,x,y,z,t,Nc);	
		if((*(*(*(*(p+t)+x)+y)+z)).nums==0){
		
			if(x>0){
				open_zero_board(p,x-1,y,z,t,Nc);
			}
			if(x<Nc){
				open_zero_board(p,x+1,y,z,t,Nc);
			}
			if(y>0){
				open_zero_board(p,x,y-1,z,t,Nc);
			}
			if(y<Nc){
				open_zero_board(p,x,y+1,z,t,Nc);
			}
			if(z>0){
				open_zero_board(p,x,y,z-1,t,Nc);
			}
			if(z<Nc){
				open_zero_board(p,x,y,z+1,t,Nc);
			}
				open_zero_board(p,x,y,z,1-t,Nc);
		}
	}
}
void open_t_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).show==0&&(*(*(*(*(p+t)+x)+y)+z)).nums==0&&(*(*(*(*(p+t)+x)+y)+z)).mine==0){
		open_zero_board(p,x,y,z,t,Nc);
	}
}
void show_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	Nc++;
	(*(*(*(*(p+t)+x)+y)+z)).show = 1;
	p_n_xy(lx+2*x*(Nc+1)+2*z,ly+t*(Nc+1)+y,(*(*(*(*(p+t)+x)+y)+z)).nums);
	c_blank--;
}
void p_s_xy(int x,int y){
	gtxy(x,y);
	printf("▇");
}
void p_m_xy(int x,int y){
	gtxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("※");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_n_xy(int x,int y,int nums){
	gtxy(x,y);
	printf("%2d",nums);
}
void p_newmap(int lx,int ly,int Nc){
	int i,j,k,t;
	for(t=0;t<2;t++){
		for(i=0;i<Nc;i++){
			for(j=0;j<Nc;j++){
				for(k=0;k<Nc;k++){
					p_s_xy(lx+2*((Nc+1)*j+k),ly+i+t*(Nc+1));
				}
			}
		}
	}
	gtxy(lx,ly+Nc);
	printf("--");
	for(i=0;i<Nc*(Nc+1)-3;i++){
		printf("  ");
	}
	printf("--");
}
void p_m_nums(struct Map (*p)[N][N][N],int Nc,int me){
	int m1=c_mine/2-count_mine(p,0,Nc)-mr[0],m2=c_mine/2-count_mine(p,1,Nc)-mr[1];
	if(me){
		if(m1+m2<0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		}
		gtxy(52,2);
		printf("%3d",m1+m2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		return;
	}
	if(m1<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(52,2);
	printf("%3d",m1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	if(m2<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(52,4);
	printf("%3d",m2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int count_mine(struct Map (*p)[N][N][N],int t,int Nc){
	int i,j,k,count=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			for(k=0;k<Nc;k++){
				if((*(*(*(*(p+t)+i)+j)+k)).show==2){
					count++;
				}				
			}
		}
	}
	return count;
}
void p_b_nums(struct Map (*p)[N][N][N],int Nc,int me){
	int b1 = count_blank(p,0,Nc),b2 = count_blank(p,1,Nc);
	if(me){
		gtxy(31,2);
		printf("%3d",b1+b2);
		return;
	}
	gtxy(31,2);
	printf("%3d",b1);
	gtxy(31,4);
	printf("%3d",b2);
}
int count_blank(struct Map (*p)[N][N][N],int t,int Nc){
	int i,j,k,count=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			for(k=0;k<Nc;k++){
				if((*(*(*(*(p+t)+i)+j)+k)).show!=1){
					count++;
				}				
			}
		}
	}
	return count;
}
void p_level(int le){
	if(le<2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	}
	else if(le<7){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	}
	else if(le<13){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	}
	else if(le<17){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(75,2);
	printf("%3d",le);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);	
}
void p_resu(int resu,int x,int y){
	if(resu<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(18,4);
	printf("%4d",resu);
	if(x>=0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
		gtxy(x,y);
		printf("×");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_d_mine(struct Map (*p)[N][N][N],int Nc){
	int i,j,k,t;
	for(t=0;t<2;t++){
		for(i=0;i<Nc;i++){
			for(j=0;j<Nc;j++){
				for(k=0;k<Nc;k++){
					if((*(*(*(*(p+t)+i)+j)+k)).mine==1&&(*(*(*(*(p+t)+i)+j)+k)).show!=1){
						gtxy(lx+2*((Nc+1)*i+k),ly+j+t*(Nc+1));
						printf("×");
					}
				}
			}
		}
	}
}
int game(int Nc,int M,int merge,int firstpro,int timelim,int signres,int reviveprop,int level){
	clean();
	frame();
	
	lx=(92-Nc*(Nc+1)*2)/2+1;
	ly=7;
	c_blank = 2*Nc*Nc*Nc;
	c_mine = 20+M;
	mr[0]=0;
	mr[1]=0;
	
	p_newmap(lx,ly,Nc);
	struct Map newmap[2][N][N][N]={0,0,0}; 
	struct Map (*p)[N][N][N] = NULL;
    p = newmap;
    
    int revprop=3;
    if(reviveprop){
    	revprop=0;
	}
	tl = timelim;
    
	set_mine(p,c_mine/2,Nc);//
	get_mine(p,Nc);
    p_b_nums(p,Nc,merge);
    p_m_nums(p,Nc,merge);
    p_level(level);
    p_resu(revprop,-1,-1);
    
    
    
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
				if(X<lx||Y<ly||X>lx-2+(Nc+1)*Nc*2||Y>ly+1+Nc*2){
					break;
				}
		  		switch(rt){ 
		  			case 1: //右键 
		  					if(signres){
		  						break;
							  }
		  					right_key(p,lx,ly,X,Y,Nc,merge);
		   					break;
          			case 2: //左键
          				{
          					int u=X,v=Y;
          					if(left_key(p,lx,ly,X,Y,Nc,firstpro,merge)){    						
          						p_resu(--revprop,lx+2*((u-lx)/2)/(Nc+1)*(Nc+1)+2*((u-lx)/2)%(Nc+1),ly+(v-ly)/(Nc+1)*(Nc+1)+(v-ly)%(Nc+1));
          						p_b_nums(p,Nc,merge);
    							p_m_nums(p,Nc,merge);
          						if(revprop<0){
          							p_d_mine(p,Nc);
          							return defeat(lx+2*((u-lx)/2)/(Nc+1)*(Nc+1)+2*((u-lx)/2)%(Nc+1),ly+(v-ly)/(Nc+1)*(Nc+1)+(v-ly)%(Nc+1))-6;
								  }
							  }  
		   					break;
						}
		  		}
			} 		 
		 	break; 
		}
		if(c_blank==c_mine){
			return victory(level)-6;
		}
	}
	return 0;
}
/* 
  维数   表达式          地址  条件 
	x  ((x-lx)/2)%(Nc+1)  k z  !=Nc
	y  (y-ly)%(Nc+1)      j y  !=Nc
	z  ((x-lx)/2)/(Nc+1)  i x
	t  (y-ly)/(Nc+1)      t t
	
	lx+2*((x-lx)/2)/(Nc+1)*(Nc+1)+2*((x-lx)/2)%(Nc+1),ly+(y-ly)/(Nc+1)*(Nc+1)+(y-ly)%(Nc+1)
*/
int left_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int fl,int me){
	if(((x-lx)/2)%(Nc+1)==Nc||(y-ly)%(Nc+1)==Nc){
		return 0;
	}
	int i=((x-lx)/2)/(Nc+1),j=(y-ly)%(Nc+1),k=((x-lx)/2)%(Nc+1),t=(y-ly)/(Nc+1);
	if((*(*(*(*(p+t)+i)+j)+k)).show!=0){
		return 0;
	}
	if(left_key_event(p,i,j,k,t,Nc,fl)){
		return 1;
	}
	p_b_nums(p,Nc,me);
	return 0;
}
int left_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int fl){
	if(c_blank==2*Nc*Nc*Nc){
		if(fl==0){
			fir_pro(p,i,j,k,t,Nc);
			get_mine(p,Nc);
		}
		tc = 1;
	}
	if((*(*(*(*(p+t)+i)+j)+k)).mine==1&&(*(*(*(*(p+t)+i)+j)+k)).show==0){
		(*(*(*(*(p+t)+i)+j)+k)).show=1;
		mr[t]++;
		return 1;
	}
	judge_board(p,i,j,k,t,Nc);
	return 0;
}
void right_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int me){
	if(((x-lx)/2)%(Nc+1)==Nc||(y-ly)%(Nc+1)==Nc){
		return;
	}
	right_key_event(p,((x-lx)/2)/(Nc+1),(y-ly)%(Nc+1),((x-lx)/2)%(Nc+1),(y-ly)/(Nc+1),Nc);
	p_m_nums(p,Nc,me);
}
void right_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc){
	switch((*(*(*(*(p+t)+i)+j)+k)).show)
	{
		case 0:
			(*(*(*(*(p+t)+i)+j)+k)).show = 2;
			p_m_xy(lx+2*i*(Nc+1)+2*k,ly+t*(Nc+1)+j);
			break;
		case 1:
			break;
		case 2:
			(*(*(*(*(p+t)+i)+j)+k)).show = 0;
			p_s_xy(lx+2*i*(Nc+1)+2*k,ly+t*(Nc+1)+j);
			break;
	}
}
void fir_pro(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).mine==1){
		change_loc(p,x,y,z,t,0,0,0,Nc);
	}
	if(x>0&&(*(*(*(*(p+t)+x-1)+y)+z)).mine==1){
		change_loc(p,x-1,y,z,t,1,0,0,Nc);
	}
	if(x<Nc-1&&(*(*(*(*(p+t)+x+1)+y)+z)).mine==1){
		change_loc(p,x+1,y,z,t,-1,0,0,Nc);
	}
	if(y>0&&(*(*(*(*(p+t)+x)+y-1)+z)).mine==1){
		change_loc(p,x,y-1,z,t,0,1,0,Nc);
	}
	if(y<Nc-1&&(*(*(*(*(p+t)+x)+y+1)+z)).mine==1){
		change_loc(p,x,y+1,z,t,0,-1,0,Nc);
	}
	if(z>0&&(*(*(*(*(p+t)+x)+y)+z-1)).mine==1){
		change_loc(p,x,y,z-1,t,0,0,1,Nc);
	}
	if(z<Nc-1&&(*(*(*(*(p+t)+x)+y)+z+1)).mine==1){
		change_loc(p,x,y,z+1,t,0,0,-1,Nc);
	}
	if((*(*(*(*(p+1-t)+x)+y)+z)).mine==1){
		change_loc(p,x,y,z,1-t,0,0,0,Nc);
	}	
}
int judge_sat(struct Map (*p)[N][N][N],int i,int j,int k,int x,int y,int z,int t,int Nc){
	if(i==x&&j==y&&(k==z-1||k==z+1||k==z)){
		return 0;
	}
	if(i==x&&k==z&&(j==y-1||j==y+1)){
		return 0;
	}
	if(k==z&&j==y&&(i==x-1||i==x+1)){
		return 0;
	}	
	if((*(*(*(*(p+t)+i)+j)+k)).mine==1){
		return 0;
	}
	return 1;
}
void change_loc(struct Map (*p)[N][N][N],int x,int y,int z,int t,int ax,int ay,int az,int Nc){
	int i,j,k,c=1;
	srand(time(NULL));
	while(c)
	{
		i = rand()%Nc;
		j = rand()%Nc;
		k = rand()%Nc;
		if(judge_sat(p,i,j,k,x+ax,y+ay,z+az,t,Nc))
		{
			(*(*(*(*(p+t)+i)+j)+k)).mine = 1;
			(*(*(*(*(p+t)+x)+y)+z)).mine = 0;
			c--;
		}
	}		
}
int victory(int le){
	tc = 0;
	if(tl<0){
		le+=tl;
	}
	tl = 0;
	char rv[100]="Contract Grade";
	//E0 D1-3 C4-6 B7-9 A10-12 S13-15 V16
	if(le==0){
		strcat(rv," - E\n");
	}
	else if(le>0&&le<4){
		strcat(rv," - D\n");
	}
	else if(le>3&&le<7){
		strcat(rv," - C\n");
	}
	else if(le>6&&le<10){
		strcat(rv," - B\n");
	}
	else if(le>9&&le<13){
		strcat(rv," - A\n");
	}
	else if(le>12&&le<16){
		strcat(rv," - S\n");
	}
	else if(le==16){
		strcat(rv," - V\n恭喜恭喜(*^▽^*)\n顺利毕业(〃'▽'〃)\n再来亿局吧(*≧▽≦)");
	}
	if(le!=16){
		strcat(rv,"恭喜你嗷，好不容易赢了一把~\n再来一局吧!");
	}	
	Sleep(500);
	return MessageBox(NULL,rv,"VICTORY",MB_YESNO);//Y6 N7	 
}
int defeat(int x,int y){
	tc = 0;
	tl = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gtxy(x,y);
	printf("×");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	srand(time(NULL));
	char rv[100]="";
	switch(rand()%11){
		case 0:
			strcat(rv,"失败于后，不如审慎于先");
			break;
		case 1:
			strcat(rv,"失败的是事，绝不应是人");
			break;
		case 2:
			strcat(rv,"决不能放弃\n世界上没有失败，只有放弃");
			break;
		case 3:
			strcat(rv,"失败就是迈向成功应付出的代价");
			break;
		case 4:
			strcat(rv,"打击与挫败是成功的踏脚石\n而不是绊脚石");
			break;
		case 5:
			strcat(rv,"失败得教训，成功获经验");
			break;
		case 6:
			strcat(rv,"失败缘于忽视细处");
			break;
		case 7:
			strcat(rv,"对于不屈不挠的人来说\n没有失败这回事");
			break;
		case 8:
			strcat(rv,"除非你停止尝试\n否则就永远不会是失败者");
			break;
		case 9:
			strcat(rv,"经历失败愈多的英雄愈有韧力");
			break;
		case 10:
			strcat(rv,"战略若太复杂，必然失败");
			break;
	}
	strcat(rv,"\n想再来一局么？");
	Sleep(500);
	return MessageBox(NULL,rv,"DEFEAT",MB_YESNO);	 
}
void frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
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
	printf("时间:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	printf("重生十字章:"); 
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("B1:");
	gtxy(26,4);
	printf("B2:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("M1:");
	gtxy(47,4);
	printf("M2:");	
	gtxy(67,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("状态:");  
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("正常");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("难度:");
}
