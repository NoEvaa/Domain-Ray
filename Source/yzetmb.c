#include "yzetmb.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];

void entertainment2(){
	clean();
	gtxy(0,1); 		
	printf(" Administrator：\n"); 
	printf("   呼~终于找到您了嘞\n");
	printf("   上次真是谢谢你帮我夺回了控制器\n");
	printf("   不过这次我又遇上了大麻烦\n");
	printf("   呃..事情是这样的\n");
	printf("   前不久不知道从哪儿飞来一张二向箔，\n");
	printf("   直接打在了我的雷图收藏室上，\n");
	printf("   把我的雷图全部变成二维了!!!\n");
	printf("   更可气的是我丢失了这些雷图中所有雷的位置\n");
	printf("   没有雷的精确位置我就没法用这些雷图调戏新来的冒险者们了\n");
	printf("   因此请您务必帮我!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   雷图为6*6面板\n");
	printf("   共有5个雷，随机分配至整个雷图中\n");
	printf("   你要做的是根据雷图中各雷块显示的数字，\n");
	printf("   推断出这5个雷的正确位置\n");
	printf("   当然你可以放心，这些雷不会被引爆\n");
	printf("   这项任务只有成功没有失败\n");
	printf("   当5个雷的位置同时正确时即可获得胜利\n");
	printf("   你也可以自己选择离开雷图的时机\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);  
	printf("   祝你好运~ 下次见面，就破例允许你，称呼我为<澪>吧!\n\n");
	printf("   |▔▔▔▔|                     |▔▔▔▔|\n"); 
	printf("   | ←返回 |                     | 开始 →|\n");
	printf("    ▔▔▔▔                       ▔▔▔▔ \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //控制台窗口句柄 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //输入设备句柄 
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
							if(Y>21&&Y<24){
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
		if(play2()){
			return;
		}
	}	
}
int play2(){
	clean();
	play2_frame();
	
	lx=18;
	ly=9;
	c_mine = 5;
	
	struct Map newmap[N][N]={0,0,0}; 
	struct Map (*p)[N] = NULL;
    p = newmap;
    
	play2_set_mine(p,c_mine,N);//
	pr_mine_nums(p,N);

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
		  					if(X<lx||Y<ly||X>lx+N*2-1||Y>ly+N-1){
								break;
							}
		  					play2_right(p,(X-lx)/2,Y-ly);
		   					break;
          			case 2: //左键
          					if(X>65&&X<89&&Y>0&&Y<3){
          						tc = 0;
          						Sleep(1000);
          						return 1;
					  		}
		   					break;
		  		}
			} 		 
		 	break; 
		}
		if(c_mine==0){
			if(check2(p,N)){
				tc = 0;
				return MessageBox(NULL,"ALL MINE FOUND\nCongratulations!\nagain?","VICTORY",MB_YESNO)-6; 
			}
		}
	}
	return 0;
}
void play2_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |         退出          ▏\n");
	printf(" ▕                     |                    |                   |-----------------------▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕--------------------------------------------------------------|                       ▏\n");
	int i;
	for(i=0;i<15;i++){
		printf(" ▕                                                              |                       ▏\n");
	}
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("时间:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("总雷数:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("剩余可标雷数:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("状态:");  
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("正常");	
	gtxy(68,11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("▇▇▇");
	gtxy(68,12);
	printf("▇▇▇");
	gtxy(68,13);
	printf("▇▇▇");
	gtxy(70,12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(16,4);
	printf(" 5");
	p_lm();
	gtxy(67,4);
	printf("<规则>");
	gtxy(66,5);
	printf("1.鼠标右键操作");
	gtxy(66,6);
	printf("2.满足条件后自动出现胜");
	gtxy(66,7);
	printf("  利弹窗");
	gtxy(66,8);
	printf("3.根据雷块上数字找出所");
	gtxy(66,9);
	printf("  有雷的位置并标记");
	gtxy(67,15);
	printf("以周围8格是否有雷计数");

}
void play2_set_mine(struct Map (*p)[N],int count,int Nc){
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
	play2_get_mine(p,Nc);
}
void play2_get_mine(struct Map (*p)[N],int Nc){
	int i,j;	
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			(*(*(p+i)+j)).nums = play2_get_mine_nums(p,i,j,Nc);
		}
	}
}
int play2_get_mine_nums(struct Map (*p)[N],int x,int y,int Nc){
	int count=0;
	Nc--;
	if(x>0){
		count+=(*(*(p+x-1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x-1)+y-1)).mine;
		}
		if(y<Nc){
			count+=(*(*(p+x-1)+y+1)).mine;
		}
	}
	if(x<Nc){
		count+=(*(*(p+x+1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x+1)+y-1)).mine;
		}
		if(y<Nc){
			count+=(*(*(p+x+1)+y+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(p+x)+y-1)).mine;
	}
	if(y<Nc){
		count+=(*(*(p+x)+y+1)).mine;
	}
	return count;
}
void pr_mine_nums(struct Map (*p)[N],int Nc){
	int i,j;
	for(i=0;i<Nc;i++){
		gtxy(lx,ly+i);
		for(j=0;j<Nc;j++){
			printf("%2d",(*(*(p+j)+i)).nums);
		}
	}
}
void play2_right(struct Map (*p)[N],int x,int y){
	if(tc==0){
		tc = 1;
	}
	if(c_mine>0&&(*(*(p+x)+y)).show==0){
		(*(*(p+x)+y)).show = 2;
		gtxy(x*2+lx,y+ly);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),192);
		printf("%2d",(*(*(p+x)+y)).nums);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		c_mine--;
		p_lm();
	}
	else if((*(*(p+x)+y)).show==2){
		(*(*(p+x)+y)).show = 0;
		gtxy(x*2+lx,y+ly);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		printf("%2d",(*(*(p+x)+y)).nums);
		c_mine++;
		p_lm();
	}
}
void p_lm(){
	gtxy(30,4);
	printf("%2d",c_mine);
}
int check2(struct Map (*p)[N],int Nc){
	int i,j,c=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			if((*(*(p+i)+j)).show==2&&(*(*(p+i)+j)).mine==1){
				c++;
			}
		}
	}
	if(c==5){
		return 1;
	}
	return 0;
}
