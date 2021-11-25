#include "yzetmf.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];
extern int AIstep;

void entertainment6(){
	e_6();	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //控制台窗口句柄 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //输入设备句柄 
	int rt,st = 0;
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
								else if(X>18&&X<27){
									e6_course();
									e_6();
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
		if(play6()){
			return;
		}
	}	
}
void e_6(){
	clean();
	gtxy(0,1); 			
	printf(" 澪：\n"); 
	printf("   经过我们不懈努力\n");
	printf("   终于粉碎了炸弹人的入侵大梦\n");
	printf("   现在有一大队炸弹小飞人驾驶着飞行器想要逃离雷域\n");
	printf("   我将给予你天雷的控制权\n");
	printf("   帮助雷域将这些炸弹小飞人赶尽杀绝吧!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("   合理利用有限的雷能击败尽可能多的飞行器\n"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   gogogo!!!\n\n");
	printf("   |▔▔▔▔|     |▔▔▔▔|      |▔▔▔▔|\n"); 
	printf("   | ←返回 |     |  教程  |      | 开始 →|\n");
	printf("    ▔▔▔▔       ▔▔▔▔        ▔▔▔▔ \n"); 
}
void e6_course(){
	for(;;){
		switch(e6_rule_choice()){
			case 0:
				return;
			case 1:
				e6_operation();
				break;
			case 2:
				e6_debuff();
				break;
			case 3:
				e6_skill();
				break;
		}
	}
}
int e6_rule_choice(){
	clean();
	gtxy(0,1);	
	printf("  |▔▔▔▔|\n"); 
	printf("  | ←返回 |\n");
	printf("   ▔▔▔▔       \n"); 
	printf("    ▁▁▁▁▁▁▁▁▁  \n");	
	printf("  ▕                  ▏\n");
	printf("  ▕  Ⅰ 玩法         ▏\n");
	printf("  ▕------------------▏\n");
	printf("  ▕                  ▏\n");
	printf("  ▕  Ⅱ BOSS效果     ▏\n");	
	printf("  ▕------------------▏\n");
	printf("  ▕                  ▏\n");
	printf("  ▕  Ⅲ 技能         ▏\n");
	printf("  ▕                  ▏\n");
	printf("    ▔▔▔▔▔▔▔▔▔  ");
	
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
          					if(X>3&&X<22){
          						if(Y==5||Y==6){
          							return 1;
								  }
								else if(Y==8||Y==9){
									return 2;
								}
								else if(Y==11||Y==12||Y==13){
									return 3;
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void e6_operation(){
	lx=40;
	ly=10;
	e6_o1();
	e6_o2();
	e6_o3(); 
}
void e6_o1(){
	c_mine = 5;//boss
	mr[0] = 9999;//雷能
	mr[1] = 0;//技力
	clean();
    play6_frame();
   	c_blank = 18;//HP 
	gtxy(7,8);
	printf("<贪心>");
	gtxy(7,9);
	printf("▇▇▇");
	gtxy(7,10);
	printf("▇  ▇");
	gtxy(7,11);
	printf("▇▇▇");
	gtxy(5,12);
	printf("HP MAX: %2d",c_blank);
	gtxy(5,13);
	printf("TALENTS:");
	gtxy(7,14);
	printf("[被动]护甲");
	gtxy(7,15);
	printf("[被动]反伤");
	int emap[5][5] = {{0,2,2,2,0},
					  {0,2,0,2,0},
					  {0,2,2,2,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}};//0正常 1命中 2敌方 -1未命中 
	int wmap[10] = {0};
	int record[7] = {0};//0同生共死 1干扰 2割裂[0-10] 3沉默 4坐标x 5坐标y 6嗜血 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//备用
    int dc = mr[0];//锁血 
	int DS = 0;//圣盾术 
    p_p6_emap();
    p_p6_newHP();
	p_p6_c(DS);
	p_p6_a();
	p_p6_wmap(wmap);
	p_p6_skills(skillcd,record[3]);
	int y = 17;	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 欢迎来到新手教程                         ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 这是一个十分容易上手的游戏               ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 上图是游戏主面板                         ");
	gtxy(28,y++);
	printf(" 黑色的5*5雷图中放满了天雷                ");
	gtxy(28,y++);
	printf(" 边上的白色雷格则是天雷的引爆装置         ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
	gtxy(lx,ly+5);
	printf("▇"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 点击白色雷格即可引爆该行/列天雷          ");
	gtxy(28,y++);
	printf(" 点击一下试试吧                           ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                (鼠标点击绿色雷格)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,lx,ly+5,1,0);
	int i = 5,j;
	
	if(i>4){
		i -= 5;
		for(j=0;j<5;j++){
			emap[j][i]--;
		}
	}
	else{
		for(j=0;j<5;j++){
			emap[i][j]--;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
	gtxy(lx,ly+5);
	printf("▇");
	p_p6_le_cartoon1(emap,record);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 该列天雷都被引爆了!!!                    ");
	gtxy(28,y++);
	printf(" 雷图中红色雷格显示的即为                 ");
	gtxy(28,y++);
	printf(" 此时炸弹人的飞行器的位置                 ");
	gtxy(28,y++);
	printf(" 很可惜没有命中                           ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
}
void e6_o2(){
	c_mine = 5;//boss
	mr[0] = 9999;//雷能
	mr[1] = 2;//技力  
	clean();
    play6_frame();
   	c_blank = 18;//HP 
	gtxy(7,8);
	printf("<贪心>");
	gtxy(7,9);
	printf("▇▇▇");
	gtxy(7,10);
	printf("▇  ▇");
	gtxy(7,11);
	printf("▇▇▇");
	gtxy(5,12);
	printf("HP MAX: %2d",c_blank);
	gtxy(5,13);
	printf("TALENTS:");
	gtxy(7,14);
	printf("[被动]护甲");
	gtxy(7,15);
	printf("[被动]反伤");
	int emap[5][5] = {{0,0,0,0,0},
					  {0,0,2,2,2},
					  {0,0,2,0,2},
					  {0,0,2,2,2},
					  {0,0,0,0,0}};//0正常 1命中 2敌方 -1未命中 
	int wmap[10] = {0};
	int record[7] = {0};//0同生共死 1干扰 2割裂[0-10] 3沉默 4坐标x 5坐标y 6嗜血 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//备用
    int dc = mr[0];//锁血 
	int DS = 0;//圣盾术 
    p_p6_emap();
    p_p6_newHP();
	p_p6_c(DS);
	p_p6_a();
	p_p6_wmap(wmap);
	p_p6_skills(skillcd,record[3]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
	gtxy(lx+4,ly+5);
	printf("▇"); 
	int y = 17;	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 这次我们换一个雷格点击                   ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                (鼠标点击绿色雷格)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,lx+4,ly+5,1,0);
	int i = 7, j;
	if(i>4){
		i -= 5;
		for(j=0;j<5;j++){
			emap[j][i]--;
		}
	}
	else{
		for(j=0;j<5;j++){
			emap[i][j]--;
		}
	}
	int ct = p_p6_le_cartoon1(emap,record);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
	gtxy(lx+4,ly+5);
	printf("▇"); 
	y = 17;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ohhhh这次顺利命中了炸弹人飞行器          ");
	gtxy(28,y++);
	printf(" 蓝色雷格即表示被天雷炸到的飞行器部分     ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	if(c_mine==5&&ct!=0){
		c_blank+=2;
		mr[0]-=2;
	}
	if(c_blank<ct){
		ct = c_blank;
	}
	c_blank -= ct;
	p_p6_HPdown_cartoon(ct);
	y = 17;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 最上方BOSS's HP即为飞行器的血条          ");
	gtxy(28,y++);
	printf(" 当血条归零时飞行器就会被击落             ");
	gtxy(28,y++);
	printf(" 目前血条最后三格变为红色                 ");
	gtxy(28,y++);
	printf(" 就是天雷对它造成的伤害                   ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	p_p6_newHP();
	y = 17;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 红色格子消失后，                         ");
	gtxy(28,y++);
	printf(" 剩下的黄格为飞行器的剩余生命值           ");
	gtxy(28,y++);
	printf(" 因为这架飞行器的特殊天赋                 ");
	gtxy(28,y++);
	printf(" 它随时拥有两格护甲，即血条最后两格       ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
}
void e6_o3(){
	c_mine = 3;//boss
	mr[0] = 9999;//雷能
	mr[1] = 30;//技力
	clean();
    play6_frame();
	c_blank = 20;//HP
	gtxy(7,8);
	printf("<深海炸弹>");
	gtxy(7,9);
	printf("  ▇");
	gtxy(7,10);
	printf("▇▇▇");
	gtxy(5,11);
	printf("HP MAX: %2d",c_blank);
	gtxy(5,12);
	printf("TALENTS:");
	gtxy(7,13);
	printf("[被动]反击");
	gtxy(7,14);
	printf("[主动]割裂");
	int emap[5][5] = {{0,0,0,0,0},
					  {2,0,0,0,0},
					  {2,2,0,0,0},
					  {2,0,0,0,0},
					  {0,0,0,0,0}};//0正常 1命中 2敌方 -1未命中 
	int wmap[10] = {0};
	int record[7] = {0};//0同生共死 1干扰 2割裂[0-10] 3沉默 4坐标x 5坐标y 6嗜血 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//备用
    int dc = mr[0];//锁血 
	int DS = 0;//圣盾术 
    p_p6_emap();
    p_p6_newHP();
	p_p6_c(DS);
	p_p6_a();
	p_p6_wmap(wmap);
	p_p6_skills(skillcd,record[3]);
	int y = 17;	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 左侧上方雷能代表你的生命值               ");
	gtxy(28,y++);
	printf(" 当雷能为零时游戏将会结束                 ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 在左侧中间BOSS Details中                 ");
	gtxy(28,y++);
	printf(" 展示了飞行器的最大生命值、形状           ");
	gtxy(28,y++);
	printf(" 还有特殊能力                             ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 左侧下间DEBUFF                           ");
	gtxy(28,y++);
	printf(" 会给出飞行器对你施展的减益效果           ");
	gtxy(28,y++);
	printf(" 会对你的行动产生不良影响                 ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 右侧是技能栏                             ");
	gtxy(28,y++);
	printf(" 提供了四种技能供你使用                   ");
	gtxy(28,y++);
	printf(" 合理搭配使用技能能事半功倍               ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 现在让我们来试一下                       ");
	gtxy(28,y++);
	printf(" 首先点击技能<鹰眼术>                     ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	skillcd[0] = 1;
	skillcd[2] = 1;
	skillcd[3] = 1;
	p_p6_skills(skillcd,0);
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rmt,ttt = 1;
	while(ttt)
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
					  {
							if(X>73&&X<89){
								if(Y>16&&Y<19){
									if(mr[1]<8||skillcd[1]){
										break;
									}
									ttt = 0;
									mr[1] -= 8;
									skillcd[1] = 1;
					  				p_p6_a();
									p_p6_skill2(emap);
									p_p6_skills(skillcd,record[3]);
								}
							}
		   					break;
		   				}
				}
			} 		 
		 	break; 
		}
	}
	skillcd[2] = 0;
	p_p6_skills(skillcd,0);
	y = 17;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 再点击技能 <嗜血>                        ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	ttt = 1;
	while(ttt)
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
					  {
							if(X>73&&X<89){
								if(Y>19&&Y<22){
									if(mr[1]<12||skillcd[2]){
										break;
									}
									mr[1] -= 12;
									record[6] = 3;
									skillcd[2] = 1;
									p_p6_a();
									p_p6_skills(skillcd,record[3]);
									ttt = 0;
								}
							}
		   					break;
		   				}
				}
			} 		 
		 	break; 
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
	gtxy(lx,ly+5);
	printf("▇"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 最后点击绿色格子引爆天雷                 ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                (鼠标点击绿色雷格)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,lx,ly+5,1,0);
	if(p6_left_event(emap,wmap,Y-ly,record)){
		mr[1]+=2;
		if(mr[1]>30){
			mr[1] = 30;
		}
		p_p6_c(DS);
		p_p6_a();
		p6_reskills(skillcd);
		p_p6_skills(skillcd,record[3]); 
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" wow                                      ");
	gtxy(28,y++);
	printf(" 可怜的小飞行器一下就失去了9点生命值      ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" 更多游戏方法请自己去体验吧               ");
	gtxy(28,y++);
	printf(" bye~                                     ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (鼠标左键以继续)     ▼ ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);	
}
void e6_debuff(){
	e6_debuff_board();
	p_e6_boss(1);	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rt;
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
							if(X>2&&X<17){
								if(Y==3||Y==4){
									return;
								}
								else if(Y==6||Y==7){
									p_e6_boss(1);
								}
								else if(Y==9||Y==10){
									p_e6_boss(2);
								}
								else if(Y==12||Y==13){
									p_e6_boss(3);
								}
								else if(Y==15||Y==16){
									p_e6_boss(4);
								}
								else if(Y==19||Y==20||Y==21){
									p_e6_boss(5);
								}
								break;
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void e6_debuff_board(){
	clean();
	gtxy(0,1); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("◇BOSS能力：\n"); 
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕              ||||||||||                                      ▏\n");
	printf(" ▕    ←退出    |++++++++|                                      ▏\n");
	printf(" ▕--------------------------------------------------------------▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_e6_boss(int s){
	if(s==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,7);
	printf("<皇士墩>");
	if(s==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,10);
	printf("<闪光>");
	if(s==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,13);
	printf("<深海炸弹>");
	if(s==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,16);
	printf("<蓝色空间>");
	if(s==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,19);
	printf("<贪心>");
	p_e6_boss_detail(s);
}
void p_e6_boss_detail(int s){
	p_e5_skillc_clean();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	switch(s){
		case 1:
			gtxy(26,6);
			printf("<皇士墩>");
			gtxy(23,8);
			printf("[被动]: ");
			gtxy(23,11);
			printf("[主动]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("巨量生命");
			gtxy(27,10);
			printf("HP(MAX)达到55");
			gtxy(23,12);
			printf("同生共死(先手)");
			gtxy(27,13);
			printf("50%%概率附加DEBUFF[同生共死]");
			gtxy(27,14);
			printf("[同生共死]:受到伤害则扣除等量雷能");
			break;
		case 2:
			gtxy(26,6);
			printf("<闪光>");
			gtxy(23,8);
			printf("[主动]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("干扰(先手)");
			gtxy(27,10);
			printf("为随机四个引爆点附加DEBUFF[干扰]");
			gtxy(27,11);
			printf("扣除雷能4");
			gtxy(27,12);
			printf("[干扰]:被干扰的引爆点将无法使用");
			break;
		case 3:
			gtxy(26,6);
			printf("<深海炸弹>");
			gtxy(23,8);
			printf("[被动]: ");
			gtxy(23,13);
			printf("[主动]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			gtxy(27,17);
			printf("      <!-可叠加，最高10层>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("反击");
			gtxy(27,10);
			printf("<!-飞行器特殊部位受到伤害后触发>");
			gtxy(27,11);
			printf("为指定五个引爆点附加DEBUFF[干扰]");
			gtxy(27,12);
			printf("扣除雷能5");
			gtxy(23,14);
			printf("割裂(先手)");
			gtxy(27,15);
			printf("20%%概率附加DEBUFF[割裂]");
			gtxy(27,16);
			printf("[割裂]:每次引爆天雷都会扣除固定雷能");
			break;
		case 4:
			gtxy(26,6);
			printf("<蓝色空间>");
			gtxy(23,8);
			printf("[主动]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			gtxy(27,11);
			printf("     <!-与 [主动]同生共死 互斥>");
			gtxy(27,16);
			printf("     <!-与 [主动]沉默 互斥>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("沉默(先手)");
			gtxy(27,10);
			printf("50%%概率附加DEBUFF[沉默]");
			gtxy(27,12);
			printf("[沉默]:无法使用技能(<◇净化>除外)");
			gtxy(23,13);
			printf("同生共死(先手)");
			gtxy(27,14);
			printf("50%%概率附加DEBUFF[同生共死]");
			gtxy(27,15);
			printf("[同生共死]:受到伤害则扣除等量雷能");
			break;
		case 5:
			gtxy(26,6);
			printf("<贪心>");
			gtxy(23,8);
			printf("[被动]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("护甲");
			gtxy(27,10);
			printf("随时拥有2点护甲抵消伤害");
			gtxy(23,11);
			printf("反伤");
			gtxy(27,12);
			printf("扣除与护甲所抵消伤害等量的雷能");
			break;
	} 
} 
void e6_skill(){
	e6_skill_board();
	p_e6_skillc(1);
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rt;
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
							if(X>2&&X<17){
								if(Y==3||Y==4){
									return;
								}
								else if(Y==6||Y==7){
									p_e6_skillc(1);
								}
								else if(Y==9||Y==10){
									p_e6_skillc(2);
								}
								else if(Y==12||Y==13){
									p_e6_skillc(3);
								}
								else if(Y==15||Y==16||Y==17){
									p_e6_skillc(4);
								}
								break;
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void e6_skill_board(){
	clean();
	gtxy(0,1); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("◇技能详情：\n"); 
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕              ||||||||||                                      ▏\n");
	printf(" ▕    ←退出    |++++++++|                                      ▏\n");
	printf(" ▕--------------------------------------------------------------▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕--------------|                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf(" ▕              |                                               ▏\n");
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_e6_skillc(int s){
	if(s==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,7);
	printf("◇净化");
	if(s==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,10);
	printf("◇鹰眼术");
	if(s==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,13);
	printf("◇嗜血");
	if(s==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,16);
	printf("◇圣盾术");
	p_e6_skillc_detail(s);
}
void p_e6_skillc_detail(int s){//
	p_e5_skillc_clean();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(23,8);
	printf("A: ");
	gtxy(23,9);
	printf("技能描述：");
	switch(s){
		case 1:
			gtxy(26,6);
			printf("<◇净化>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("   8");
			gtxy(27,10);
			printf("清除当前全部DEBUFF。");
			break;
		case 2:
			gtxy(26,6);
			printf("<◇鹰眼术>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("   8");
			gtxy(27,10);
			printf("发现并标记雷图中飞行器位置。");
			break;
		case 3:
			gtxy(26,6);
			printf("<◇嗜血>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("  12");
			gtxy(27,10);
			printf("下一次引爆天雷将造成三倍伤害。");
			gtxy(27,11);
			printf("下下次引爆天雷将造成二倍伤害。");
			gtxy(27,12);
			printf(" <!-同类效果无法叠加>");
			break;
		case 4:
			gtxy(26,6);
			printf("<◇圣盾术>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("  15");
			gtxy(27,10);
			printf("免疫一切攻击和法术。");
			gtxy(27,11);
			printf("*直至下一次引爆天雷为止：");
			gtxy(27,12);
			printf("   任何行为都无法消耗雷能");
			gtxy(27,13);
			printf("   所有DEFUFF失效");
			gtxy(27,14);
			printf("俗称<无敌>");
			break;
	} 
}
int play6(){	
	lx=40;
	ly=10;
	c_mine = 3;//boss
	c_blank = 55;//HP  MAX55
	mr[0] = 9999;//雷能
	mr[1] = 10;//技力
	int tub = 0;//计数 
    
	clean();
    play6_frame();
    while(1){
    	if(play6_game()){
    		break;
		}
		tub++;
		mr[1] += 10;
		if(mr[1]>30){
			mr[1] = 30;
		}
	}
	return p6_result(tub);
}
int play6_game(){
	p6_randboss();
	int emap[5][5] = {0};//0正常 1命中 2敌方 -1未命中 
	int wmap[10] = {0};
	int record[7] = {0};//0同生共死 1干扰 2割裂[0-10] 3沉默 4坐标x 5坐标y 6嗜血 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//备用
    int dc = mr[0];//锁血 
	int DS = 0;//圣盾术 
    
    p_p6_emap();
    p_p6_newHP();
    p6_aeroset(emap,wmap,record);
    p6_debuff(record,wmap,DS);
	p_p6_c(DS);
	p_p6_a();
	p_p6_debuff(record);
	p_p6_wmap(wmap);
	p_p6_skills(skillcd,record[3]);

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
					  {
					  		if(X>69&&X<88&&Y>7&&Y<10){
					  			return 1;
							}
					  		if(X==lx+10||X==lx+11){
					  			if(Y>=ly&&Y<ly+5){
					  				if(p6_left_event(emap,wmap,Y-ly,record)){
					  					p6_rebuff(record,wmap);
					  					p6_debuff(record,wmap,DS);
					  					p_p6_debuff(record);
					  					p_p6_wmap(wmap);
					  					mr[1]+=2;
					  					if(mr[1]>30){
					  						mr[1] = 30;
										}
										if(DS){
											DS = 0;
											mr[0] = dc;
										}
										p_p6_c(DS);
					  					p_p6_a();
										p6_reskills(skillcd);
										p_p6_skills(skillcd,record[3]);
					  					break; 
									}
								}
							}
							else if(Y==ly+5){
								if(X>=lx&&X<lx+10){
									if(p6_left_event(emap,wmap,5+(X-lx)/2,record)){
										p6_rebuff(record,wmap);
					  					p6_debuff(record,wmap,DS);
					  					p_p6_debuff(record);
					  					p_p6_wmap(wmap);
					  					mr[1]+=2;
					  					if(mr[1]>30){
					  						mr[1] = 30;
										}
										if(DS){
											DS = 0;
											mr[0] = dc;
										}
										p_p6_c(DS);
					  					p_p6_a();
										p6_reskills(skillcd);
										p_p6_skills(skillcd,record[3]);
					  					break;
									}
								}
							}
							if(X>73&&X<89){
								if(Y>13&&Y<16){
									if(mr[1]<8||skillcd[0]){
										break;
									}
									mr[1] -= 8;
									p6_rebuff(record,wmap);
									record[2] = 0;
					  				p_p6_a();
					  				p_p6_debuff(record);
					  				p_p6_wmap(wmap);
					  				skillcd[0] = 1;
					  				p_p6_skills(skillcd,record[3]);
					  				break;
								}
								if(record[3]==1){
									break;
								}
								if(Y>16&&Y<19){
									if(mr[1]<8||skillcd[1]){
										break;
									}
									mr[1] -= 8;
									skillcd[1] = 1;
					  				p_p6_a();
									p_p6_skill2(emap);
									p_p6_skills(skillcd,record[3]);
								}
								else if(Y>19&&Y<22){
									if(mr[1]<12||skillcd[2]){
										break;
									}
									mr[1] -= 12;
									record[6] = 3;
									skillcd[2] = 1;
									p_p6_a();
									p_p6_skills(skillcd,record[3]);
								}
								else if(Y>22&&Y<26){
									if(mr[1]<15||skillcd[3]){
										break;
									}
									mr[1] -= 15;
									skillcd[3] = 1;
									DS = 1;
									int x = 0;
									for(;x<10;x++){
										wmap[x] = 0;
									}
									record[1] = 0;
					  				p_p6_debuff(record);
					  				p_p6_skill4();
					  				skillcd[0] = 1;
					  				p_p6_skills(skillcd,record[3]);
									p_p6_a();
									p_p6_c(DS);
									dc = mr[0];
								}
							}
		   					break;
		   				}
				}
			} 		 
		 	break; 
		}
		if(c_blank==0){
			return 0;
		}
		if(mr[0]<=0){
			return 1;
		}
	}
	return 1;
}
void p6_randboss(){
	int i;
	for(i=8;i<16;i++){
		gtxy(5,i);
		printf("               ");
	}
	srand(time(NULL));	
	c_mine = rand()%5+1;
	switch(c_mine){
		case 1:
			c_blank = 55;
			gtxy(7,8);
			printf("<皇士墩>");
			gtxy(7,9);
			printf(" ▇▇");
			gtxy(7,10);
			printf(" ▇▇");
			gtxy(5,11);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,12);
			printf("TALENTS:");
			gtxy(7,13);
			printf("[被动]巨量生命");
			gtxy(7,14);
			printf("[主动]同生共死"); 
			break;
		case 2:
			c_blank = 40;
			gtxy(7,8);
			printf("<闪光>");
			gtxy(7,9);
			printf("  ▇");
			gtxy(7,10);
			printf("▇  ▇");
			gtxy(7,11);
			printf("  ▇");
			gtxy(5,12);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,13);
			printf("TALENTS:");
			gtxy(7,14);
			printf("[主动]干扰");
			break;
		case 3:
			c_blank = 20;
			gtxy(7,8);
			printf("<深海炸弹>");
			gtxy(7,9);
			printf("  ▇");
			gtxy(7,10);
			printf("▇▇▇");
			gtxy(5,11);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,12);
			printf("TALENTS:");
			gtxy(7,13);
			printf("[被动]反击");
			gtxy(7,14);
			printf("[主动]割裂");
			break;
		case 4:
			c_blank = 30;
			gtxy(7,8);
			printf("<蓝色空间>");
			gtxy(7,9);
			printf("  ▇");
			gtxy(7,10);
			printf("  ▇▇");
			gtxy(7,11);
			printf("▇");
			gtxy(5,12);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,13);
			printf("TALENTS:");
			gtxy(7,14);
			printf("[主动]沉默");
			gtxy(7,15);
			printf("[主动]同生共死");
			break;
		case 5:
			c_blank = 18;
			gtxy(7,8);
			printf("<贪心>");
			gtxy(7,9);
			printf("▇▇▇");
			gtxy(7,10);
			printf("▇  ▇");
			gtxy(7,11);
			printf("▇▇▇");
			gtxy(5,12);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,13);
			printf("TALENTS:");
			gtxy(7,14);
			printf("[被动]护甲");
			gtxy(7,15);
			printf("[被动]反伤");
			break;
	}
}
void play6_frame(){
	gtxy(0,1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                                                                ▏\n");
	printf(" ▕                     |                                                                ▏\n");
	printf(" ▕                     |                                                                ▏\n");
	printf(" ▕---------------------|                                                                ▏\n");
	printf(" ▕                     |                                                                ▏\n");
	printf(" ▕                     |----------------------------------------------------------------▏\n");
	printf(" ▕                     |                                            |    战术撤退 →   |▏\n");
	printf(" ▕                     |                                            |    >>>>>>>>>>    |▏\n");
	printf(" ▕                     |                                             ▔▔▔▔▔▔▔▔▔ ▏\n");
	printf(" ▕                     |                                                |▔▔▔▔▔▔▔|▏\n");
	printf(" ▕                     |                                                |              |▏\n");
	printf(" ▕                     |                                                |xxxxxxxxxxxxxx|▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf(" ▕---------------------|                                                |---------------▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf(" ▕                     |                                                |---------------▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf(" ▕                     |                                                |---------------▏\n");
	printf(" ▕---------------------|                                                |               ▏\n");
	printf(" ▕---------------------|                                                |               ▏\n");
	printf(" ▕                     |                                                |               ▏\n");
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ");
	gtxy(5,3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("雷能C:");
	gtxy(75,12);
	printf("技力A:");
	gtxy(26,3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("BOSS's HP:");
	gtxy(5,6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("Boss details:"); 
	gtxy(5,17);
	printf("DEBUFF:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);	
}
void p_p6_emap(){
	int i,j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),96);
	for(i=0;i<5;i++){
		gtxy(lx,ly+i);
		for(j=0;j<5;j++){
			printf("▇");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_p6_wmap(int wp[10]){
	int i;
	for(i=0;i<5;i++){
		gtxy(lx+10,ly+i);
		if(wp[i]){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),104);
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
		}
		printf("▇");
	}
	for(i=0;i<5;i++){
		gtxy(lx+2*i,ly+5);
		if(wp[5+i]){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),104);
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
		}
		printf("▇");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int p6_left_event(int ep[5][5],int wp[10],int i,int rd[7]){
	if(wp[i]==1){
		return 0;
	}
	int j;
	if(i>4){
		i -= 5;
		for(j=0;j<5;j++){
			ep[j][i]--;
		}
	}
	else{
		for(j=0;j<5;j++){
			ep[i][j]--;
		}
	}
	int ct = p_p6_le_cartoon1(ep,rd);
	p_p6_le_cartoon2(ct,rd);
	p6_renew_ep(ep);
	p_p6_emap();
	p6_aeroset(ep,wp,rd);
	if(rd[2]){
		mr[0] -= rd[2];
	} 
	return 1;
}
int p_p6_le_cartoon1(int ep[5][5],int rd[7]){
	int i,j,t=0;
	for(i=0;i<5;i++){
		gtxy(lx,ly+i);
		for(j=0;j<5;j++){
			if(ep[i][j]==0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),96);
			}
			else if(ep[i][j]==2||ep[i][j]==4){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),100);
			}
			else if(ep[i][j]==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),107);
				t++;
			}
			else if(ep[i][j]==-1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),103);
			}
			else if(ep[i][j]==3){
				t++;
				if(i==rd[4]){
					AIstep = 1;
				}
				else if(j==rd[5]){
					AIstep = 6;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),211);
			}
			printf("▇");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	return t;
}
void p_p6_le_cartoon2(int ct,int rd[7]){
	if(c_mine==5&&ct!=0){
		c_blank+=2;
		mr[0]-=2;
	}
	if(c_blank<ct){
		ct = c_blank;
	}
	if(rd[6]){
		ct = rd[6]*ct;
		rd[6]--;
		if(c_blank<ct){
			ct = c_blank;
		}
	}
	if(rd[0]){
		mr[0] -= ct;
		rd[0] = 0;
	}
	c_blank -= ct;
	p_p6_HPdown_cartoon(ct);
	Sleep(800);
	p_p6_newHP();
}
void p_p6_newHP(){
	int i,j;
	gtxy(38,3);
	for(i=0;i<25;i++){
		printf("  ");
	}
	gtxy(28,5);
	for(i=0;i<30;i++){
		printf("  ");
	}
	if(c_blank<25){
		j = c_blank;
	}
	else{
		j = 25;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(38,3);
	for(i=0;i<j;i++){
		printf("▊");
	}
	if(c_mine==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		printf("▊▊");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	}
	gtxy(28,5);
	j = c_blank-j;
	for(i=0;i<j;i++){
		printf("▊");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_p6_HPdown_cartoon(int ct){
	int i,j;
	gtxy(38,3);
	for(i=0;i<25;i++){
		printf("  ");
	}
	gtxy(28,5);
	for(i=0;i<30;i++){
		printf("  ");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	if(c_blank<=25){
		gtxy(38,3);
		for(i=0;i<c_blank;i++){
			printf("▊");
		}
		if(c_blank+ct<25){
			j = c_blank+ct;
		}
		else{
			j = 25;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		for(;i<j;i++){
			printf("▊");
		}
		j = c_blank+ct-25;
		gtxy(28,5);
		for(i=0;i<j;i++){
			printf("▊");
		}
	}
	else{
		gtxy(38,3);
		for(i=0;i<25;i++){
			printf("▊");
		}
		j = c_blank-25;
		gtxy(28,5);
		for(i=0;i<j;i++){
			printf("▊");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		for(i=0;i<ct;i++){
			printf("▊");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p6_renew_ep(int ep[5][5]){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			ep[i][j] = 0;
		}
	}
} 
void p6_aeroset(int ep[5][5],int wp[10],int rd[7]){
	switch(c_mine){
		case 1:
			p6_aeroset1(ep,wp);
			break;
		case 2:
			p6_aeroset2(ep,wp);
			break;
		case 3:
			p6_aeroset3(ep,wp,rd);
			break;
		case 4:
			p6_aeroset4(ep,wp);
			break;
		case 5:
			p6_aeroset5(ep,wp);
			break;
	}
}
void p6_aeroset1(int ep[5][5],int wp[10]){
	srand(time(NULL));	
	int i = rand()%4, j = rand()%4;
	ep[i][j] = 2;
	ep[i+1][j] = 2;  //▇▇
	ep[i][j+1] = 2;  //▇▇
	ep[i+1][j+1] = 2;
}
void p6_aeroset2(int ep[5][5],int wp[10]){
	srand(time(NULL));	
	int i = rand()%3+1, j = rand()%3+1;
	ep[i][j-1] = 2;  //  ▇
	ep[i+1][j] = 2;  //▇  ▇
	ep[i][j+1] = 2;  //  ▇
	ep[i-1][j] = 2;
}
void p6_aeroset3(int ep[5][5],int wp[10],int rd[7]){
	srand(time(NULL));
	int i,j;
	for(;;){
		i = rand()%5;
		j = rand()%5;
		if((i==0||i==4)&&(j==0||j==4)){
			continue;
		}
		else{
			break;
		}
	}
	int c = 0;   //  ▇
	rd[4] = i;
	rd[5] = j;
	ep[i][j] = 2;//▇▇▇
	if(i<4){
		ep[i+1][j] = 2;
		c++;
	}
	if(j<4){
		ep[i][j+1] = 2;
		c++;
	}
	if(i>0){
		ep[i-1][j] = 2;
		c++;
	}
	if(j>0){
		ep[i][j-1] = 2;
		c++;
	}
	if(c==4){
		c = rand()%4;
		ep[i+(c-1)%2][j+(c-2)%2] = 0;
		ep[i-(c-1)%2][j-(c-2)%2] = 4;
	}
	else{
		if(i>=4){
			ep[i-1][j] = 4;
		}
		else if(j>=4){
			ep[i][j-1] = 4;
		}
		else if(i<=0){
			ep[i+1][j] = 4;
		}
		else if(j<=0){
			ep[i][j+1] = 4;
		}
	}
}
void p6_aeroset4(int ep[5][5],int wp[10]){
	srand(time(NULL));	
	int i = rand()%3+1, j = rand()%3+1;
	ep[i][j] = 2;
	int dx = rand()%2*2-1, dy = rand()%2*2-1;
	ep[i+dx][j+dy] = 2; //  ▇
	ep[i-dx][j] = 2;    //  ▇▇
	ep[i][j-dy] = 2;    //▇
}
void p6_aeroset5(int ep[5][5],int wp[10]){
	srand(time(NULL));	
	int i = rand()%3+1, j = rand()%3+1;
	ep[i+1][j+1] = 2; //▇▇▇
	ep[i-1][j-1] = 2; //▇  ▇
	ep[i][j-1] = 2;   //▇▇▇
	ep[i][j+1] = 2;
	ep[i+1][j] = 2;
	ep[i-1][j] = 2;
	ep[i-1][j+1] = 2;
	ep[i+1][j-1] = 2;
}
void p_p6_c(int ds){
	if(ds){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	gtxy(12,3);
	printf("%4d",mr[0]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_p6_a(){
	gtxy(82,12);
	printf("%2d",mr[1]);
}
void p6_debuff(int rd[7],int wp[10],int ds){
	if(ds){
		return;
	}
	srand(time(NULL));
	switch(c_mine){
		case 1:{
			if(rand()%2){
				rd[0] = 1;
			}
			break;
		}
		case 2:{
			int count = 4;
			mr[0] -= 4;
			while(count){
				int i = rand()%10;
				if(wp[i]==0){
					wp[i] = 1;
					count--;
				}
			}
			rd[1] = 1;
			break;
		}
		case 3:{
			if(!(rand()%5)){
				if(rd[2]<10){
					rd[2]++;
				}	
			}
			if(AIstep){
				int i;
				AIstep--;
				for(i=0;i<5;i++){
					wp[i+AIstep] = 1;
				}
				mr[0] -= 5 ;
				rd[1] = 1;
				AIstep = 0;
			}
			break;
		}
		case 4:{
			if(rand()%2){
				rd[0] = 1;
			}
			else{
				rd[3] = 1;
			}
			break;
		}
	}
}
void p6_rebuff(int rd[7],int wp[10]){
	rd[0] = 0;
	rd[1] = 0;
	rd[3] = 0;
	int i;
	for(i=0;i<10;i++){
		wp[i] = 0;
	}
}
void p_p6_debuff(int rd[7]){
	gtxy(6,18);
	printf("         ");
	gtxy(6,19);
	printf("         ");
	gtxy(6,20);
	printf("         ");
	gtxy(6,21);
	printf("         ");
	int y = 18;
	if(rd[0]){
		gtxy(6,y++);
		printf("同生共死");
	}
	if(rd[1]){
		gtxy(6,y++);
		printf("干扰");
	}
	if(rd[2]){
		gtxy(6,y++);
		printf("割裂%d层",rd[2]);
	}
	if(rd[3]){
		gtxy(6,y++);
		printf("沉默");
	}
}
void p_p6_skills(int scd[4],int rd3){
	if(mr[1]>=8&&scd[0]==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,14);
	printf("◇净化");
	gtxy(75,15);
	printf("A8");
	if(mr[1]>=8&&scd[1]==0&&rd3==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,17);
	printf("◇鹰眼术");
	gtxy(75,18);
	printf("A8");
	if(mr[1]>=12&&scd[2]==0&&rd3==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,20);
	printf("◇嗜血");
	gtxy(75,21);
	printf("A12");
	if(mr[1]>=15&&scd[3]==0&&rd3==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,23);
	printf("◇圣盾术");
	gtxy(75,24);
	printf("A15");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_p6_skill2(int ep[5][5]){
	int i,j;
	for(i=0;i<5;i++){
		gtxy(lx,ly+i);
		for(j=0;j<5;j++){
			if(ep[i][j]==0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),96);
			}
			else if(ep[i][j]==2||ep[i][j]==4){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),100);
			}
			else if(ep[i][j]==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),107);
			}
			else if(ep[i][j]==-1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),103);
			}
			else if(ep[i][j]==3){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),211);
			}
			printf("▇");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p6_reskills(int scd[4]){
	scd[0] = 0;
	scd[1] = 0;
	scd[2] = 0;
	scd[3] = 0;
}
void p_p6_skill4(){
	int i;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),107);
	for(i=0;i<5;i++){
		gtxy(lx+10,ly+i);
		printf("▇");
	}
	for(i=0;i<5;i++){
		gtxy(lx+2*i,ly+5);
		printf("▇");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int p6_result(int tu){
	char rv[100]="击败敌方单位";
	char s[6],v[4];
	itoa(tu,s,10);
	itoa(9999-mr[0],v,10);
	strcat(rv,s);
	strcat(rv,"\n共计消耗雷能");
	strcat(rv,v);
	strcat(rv,"\n重返战场？");
	return MessageBox(NULL,rv,"END",MB_YESNO)-6;
}
