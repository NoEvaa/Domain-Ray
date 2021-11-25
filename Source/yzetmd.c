#include "yzetmd.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];
extern int AIstep;

void entertainment4(){
	e_4();	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //控制台窗口句柄 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //输入设备句柄 
	int rt,st = 0;
	int lv=1,od=0;
	p_choice_lv(lv);
	p_choice_od(od);
	while(1)
	{
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//读取1个输入事件 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{ 
		  		rt = mouseput();
		  		if(X<11&&X>42&&Y<16&&Y>26){
		  			break;
				  }
		  		switch(rt){ 
		  			case 1: //右键 
		   					break;
          			case 2: //左键
          					if(X>34&&X<43){
          						if(Y>15&&Y<19){
          							return;
								}
								else if(Y>23&&Y<27){
									st = 1;//start
								}
								else if(Y>19&&Y<23){
									e4_rule();
									e_4();
									p_choice_lv(lv);
									p_choice_od(od);
								}
							  }
							else if(X>10&&X<25){
								if(Y>15&&Y<18){
          							lv = 1;
          							p_choice_lv(lv);
								}
								else if(Y==19){
									lv = 2;
									p_choice_lv(lv);
								}
								else if(Y==21){
									lv = 3;
									p_choice_lv(lv);
								}
								else if(Y==23){
									lv = 4;
									p_choice_lv(lv);
								}
								else if(Y>24&&Y<27){
									lv = 5;
									p_choice_lv(lv);
								}
							}
							else if(X>25&&X<34){
								if(Y>15&&Y<21){
          							if(od==1){
          								od = 0;
          								p_choice_od(od);
									}
								}
								else if(Y>21&&Y<27){
									if(od==0){
          								od = 1;
          								p_choice_od(od);
									}
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
		if(play4(lv,od)){
			return entertainment4();
		}
	}	
}
void e_4(){
	clean();
	gtxy(0,1); 		
	printf(" 澪：\n"); 
	printf("   阴阳太极生两仪，五行八卦通天地\n");
	printf("   有黑便有白，雷也不例外\n");
	printf("   我们的研究团经过不懈努力，\n");
	printf("   终于成功发现我们雷域的雷都由黑雷和白雷构成!\n");
	printf("   * 黑雷/白雷单独放置雷图中时：\n");
	printf("     只显示出普通雷的性质\n");
	printf("   * 黑雷和白雷同时放置同一雷图中时：\n");
	printf("     黑雷与白雷会按照某一规则相抵消\n");
	printf("   * 雷图合成雷时只会表达为黑雷/白雷/空格三种形式\n");
	printf("   * 雷图最终表达形式由雷图中的黑雷和白雷决定\n"); 
	printf("   我们利用雷域的电子脑生成了将雷图转变为白雷的智能程序\n");
	printf("   现在需要你执掌雷图中的黑雷放置权\n");
	printf("   来与我们的程序一决高下吧!\n");
	printf("   \n");
	printf("   |▔▔▔|▔▔▔▔▔▔▔|▔▔▔▔|▔▔▔▔|\n"); 
	printf("   |      |     简单     |        | ←返回 |\n");
	printf("   |   A  |--------------|   先   |        |\n");
	printf("   |      |     普通     |   手   |--------|\n");
	printf("   |   I  |--------------|        |        |\n");
	printf("   |      |     ALIce    |--------|  规则  |\n");
	printf("   |  等  |--------------|        |        |\n");
	printf("   |      |     Noah     |        |--------|\n");
	printf("   |  级  |--------------|   后   |        |\n");
	printf("   |      |     Noah's   |   手   | 开始 →|\n");
	printf("   |      |     Ark      |        |        |\n");
	printf("    ▔▔▔ ▔▔▔▔▔▔▔ ▔▔▔▔ ▔▔▔▔\n");
}
void e4_rule(){
	e4_r1();
	e4_r2();
	e4_r3();
	e4_r4();
}
void e4_r1(){
	int x=1,y=2;
	//0
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                 ");
	gtxy(x,y++);
	printf(" 欢迎来学习游戏规则!             "); 
	gtxy(x,y++);
	printf(" 本游戏为运气与智慧的比拼，      ");
	gtxy(x,y++);
	printf(" 由于我也不知道怎么赢，          ");
	gtxy(x,y++);
	printf(" 所以主要还是看运气吧，          ");
	gtxy(x,y++);
	printf(" 下面介绍玩法及规则。            ");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	lx = 16;
	ly = 4;
	int newmap[5][5] = {0};//>0=黑雷  <0=白雷 
	int (*p)[5] = NULL;
    p = newmap;
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 上图是一个5*5的正常雷图                  ");
	gtxy(x,y++);
	printf(" 绿色的雷格表示这些雷格处于中立           ");
	gtxy(x,y++);
	printf(" 我们所能操作的只有这些绿色的雷格         ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	//2
	gtxy(18,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),236);
	printf("▇");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 我们的目标是让尽可能多的雷格变为黑雷     ");
	gtxy(x,y++);
	printf(" 现在让我们点击红色的雷格尝试一下         ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("             (鼠标左键点击指定位置)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,18,5,1,0);
	//3
	play4_event(p,1,1,1,5);
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" Nice job!                                ");
	gtxy(x,y++);
	printf(" 刚才我们所点击的雷格被转化为黑雷了       ");
	gtxy(x,y++);
	printf(" 并且该雷格所在的行和列也被标记为1黑雷    ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
} 
void e4_r2(){
	int x=2,y=12;
	//0
	clean();
	lx = 16;
	ly = 4;
	int newmap[5][5] = {0};//>0=黑雷  <0=白雷 
	int (*p)[5] = NULL;
    p = newmap;
    play4_event(p,2,3,-1,5);
    p4_wmap(p,5);
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 那如果遇到白雷会变成什么样呢？           ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	//1
	gtxy(18,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),236);
	printf("▇");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 我们还是点击红色的雷格尝试一下           ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("             (鼠标左键点击指定位置)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,18,4,1,0);
	//2
	play4_event(p,0,1,1,5);
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                              ");
	gtxy(x,y++);
	printf(" 哦。。。                                     ");
	gtxy(x,y++);
	printf(" 行和列上绿色的雷格都和刚才一样，变成黑雷了   ");
	gtxy(x,y++);
	printf(" 但是行和列上原有的白雷，又变回绿色雷格了！   ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                              ");
	go_on(0,0,0,92,30);
	//3
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                              ");
	gtxy(x,y++);
	printf(" 有意思吧                                     ");
	gtxy(x,y++);
	printf(" 正负得零，黑白1相互抵消了，变回了绿色雷格    ");
	gtxy(x,y++);
	printf(" 应该很好理解                                 ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                              ");
	go_on(0,0,0,92,30);
	//4
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                              ");
	gtxy(x,y++);
	printf(" 现在再接再厉                                 ");
	gtxy(x,y++);
	printf(" 一鼓作气将剩下的绿色雷格全部变为黑雷吧       ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                 (鼠标左键完成指定要求)     ▼");
	gtxy(x,y++);
	printf("                                              ");	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	int rmt;
	calcu_situ(p,5);
	while(1)
	{		
	    ReadConsoleInput(hInput,&inRec,1,&numRead);
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{
				rmt = mouseput();
				if(X<lx||Y<ly||X>lx+5*2-1||Y>ly+5-1){
						break;
					}
		  		switch(rmt){ 
		  			case 1: //右键
		   					break;
          			case 2: //左键
          					if(play4_event(p,Y-ly,(X-lx)/2,1,5)){
          						p4_wmap(p,5);
          						calcu_situ(p,5);
							}
		   					break;
		  		}
			} 		 
		 	break; 
		}
		if(c_blank==0){
			break;
		}
	}
	//5
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                              ");
	gtxy(x,y++);
	printf(" OK了                                         ");
	gtxy(x,y++);
	printf(" 这就是本游戏简单的操作方法                   ");
	gtxy(x,y++);
	printf(" 到时候电脑执白雷，你执黑雷                   ");
	gtxy(x,y++);
	printf(" 可别输得太惨哦~                              ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                              ");
	go_on(0,0,0,92,30);
}
void e4_r3(){
	int x=4,y=9;
	//0
	clean();
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ \n");	
	printf(" ▕                     |                    |                   |\n");
	printf(" ▕                     |                    |                   |\n");
	printf(" ▕                     |                    |                   |\n");
	printf(" ▕                     |                    |                   | \n");
	printf(" ▕                     |                    |                   | \n");
	printf(" ▕--------------------------------------------------------------| \n");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("剩余回合数:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("剩余空格数:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf(" BLACK:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),244);
	gtxy(26,4);
	printf(" WHITE:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("状态：");
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 接下来具体介绍一下参数栏中的各参数     "); 
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
	//1
	x=4;
	y=9;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 首先，剩余回合数：                     "); 
	gtxy(x,y++);
	printf(" 顾名思义，剩余的回合数，还能放几次雷   ");
	gtxy(x,y++);
	printf(" 是你和电脑共有的回合数                 ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
	//2
	x=4;
	y=9;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 剩余空格数：                           "); 
	gtxy(x,y++);
	printf(" 雷图上剩下绿色雷格的数量               ");
	gtxy(x,y++);
	printf(" 帮你统计好省得你去数了                 ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
	//3
	x=4;
	y=9;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 需注意                                 ");
	gtxy(x,y++);
	printf(" 当剩余回合数或剩余空格数之一为零时     "); 
	gtxy(x,y++);
	printf(" 游戏便会结束                           ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
	//4
	x=4;
	y=9;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" BLACK和WHITE：                         "); 
	gtxy(x,y++);
	printf(" 雷图上黑雷和白雷的数量                 ");
	gtxy(x,y++);
	printf(" 你要确保场上的黑雷数量大于白雷         ");
	gtxy(x,y++);
	printf(" 只有这样当游戏结束时你才能获得胜利     ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
	//4
	x=4;
	y=9;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 状态：                                 "); 
	gtxy(x,y++);
	printf(" 有Your Turn   你的回合                 ");
	gtxy(x,y++);
	printf(" Computing..   电脑计算中               ");
	gtxy(x,y++);
	printf(" 和Game Over   游戏结束                 ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
}
void e4_r4(){
	int x=1,y=2;
	//0
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                 ");
	gtxy(x,y++);
	printf(" XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX "); 
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	x = 1; 
	y = 2;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" 之前你也已经尝试过了              ");
	gtxy(x,y++);
	printf(" 应该能够发现，                    ");
	gtxy(x,y++);
	printf(" 同一雷格的黑雷/白雷数量可以叠加   "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,0,0,92,30);
	//2
	x = 1; 
	y = 2;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                              ");
	gtxy(x,y++);
	printf(" 规定叠加上限为9                              ");
	gtxy(x,y++);
	printf(" 为增加游戏趣味，特别地：                     ");
	gtxy(x,y++);
	printf(" 当某个雷格的雷数到达10时                     ");
	gtxy(x,y++);
	printf(" 该雷格雷数将变回0                            ");
	gtxy(x,y++);
	printf(" 并且其周围四角上的四格雷格将会增加对应雷数2  ");
	gtxy(x,y++);
	printf(" 如下                                         ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(8,14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇▇▇");
	gtxy(8,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("10");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	gtxy(8,16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇▇▇");
	gtxy(16,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("→");
	gtxy(20,14);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(" 2");
	gtxy(20,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇▇▇");
	gtxy(20,16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(" 2");
	gtxy(8,18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇▇▇");
	gtxy(8,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("10");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	gtxy(8,20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇▇▇");
	gtxy(20,18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	gtxy(20,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇▇▇");
	gtxy(20,20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	gtxy(16,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("→");
	go_on(0,0,0,92,30);
	//3 
	clean();
	lx = 16;
	ly = 4;
	int newmap[5][5] = {{-2,-4,-1,-4,-2},
						{-4, 8, 9, 8,-4},			
						{ 9, 9, 0, 9, 9},			
						{-4, 8, 9, 8,-4},
						{-2,-4,-1,-4,-2}};//>0=黑雷  <0=白雷 
	int (*p)[5] = NULL;
    p = newmap;
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 最后献上精制雷图一份                     ");
	gtxy(x,y++);
	printf(" 点开中间那个绿色雷格吧！                 ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,20,6,1,0);
	//4 
	play4_event(p,2,2,1,5);
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 至此规则教程就完全结束了                 ");
	gtxy(x,y++);
	printf(" 赶紧去与你的电脑一决胜负吧！             ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
}
void p_choice_lv(int l){
	int i = 1;
	for(;i<6;i++){
		gtxy(12,15+2*i);
		if(i==l){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i*17-7);
			printf("◎");
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			printf("  ");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_choice_od(int o){
	if(o){
		gtxy(29,17);
		printf("  ");
		gtxy(29,23);
		printf("◎");
	}
	else{
		gtxy(29,17);
		printf("◎");
		gtxy(29,23);
		printf("  ");
	}
}
int play4(int lv,int ord){//ord<0先手|1后手>
	clean();
	play4_frame();
	p_lev(lv);	
	lx = 18;
	ly = 9;
	c_blank = 25;//空格
	mr[0] = 0;//黑雷
	mr[1] = 0;//白雷
	c_mine = 50;//步数 	
	//int situ[3] = {c_blank,0,0};//0-空格 1-黑雷 2-白雷 
	int newmap[5][5] = {0};//>0=黑雷  <0=白雷 
	int (*p)[5] = NULL;
    p = newmap;    
    p4_wmap(p,5);
    p_situ(c_blank,mr[0],mr[1]); 
    if(ord){
    	Sleep(200);
    	gtxy(48,4);
		printf("Computing...");
		Sleep(900);
        AI_event(p,lv);
	}
	gtxy(48,4);
	printf("Your Turn   ");
    
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
          					if(Y>25&&Y<28){
          						if(X>67&&X<78){
          							return MessageBox(NULL,"和雷！","perfect",MB_OK);
								}
							}
							if(X<lx||Y<ly||X>lx+5*2-1||Y>ly+5-1){
								break;
							}
          					if(play4_event(p,Y-ly,(X-lx)/2,1,5)){
          						p4_wmap(p,5);
          						calcu_situ(p,5);
          						c_mine--;
          						p_situ(c_blank,mr[0],mr[1]);
          						if(c_blank==0||c_mine==0){
          							break;
								  }
								gtxy(48,4);
								printf("Computing...");
          						AI_event(p,lv);
          						gtxy(48,4);
								printf("Your Turn   ");
							}
		   					break;
		  		}
			} 		 
		 	break; 
		}
		if(c_blank==0){
			gtxy(48,4);
			printf("Game Over   ");
			return d_end(lv,mr[0]-mr[1])-6;
		}
		if(c_mine==0){
			gtxy(48,4);
			printf("Game Over   ");
			return d_end(lv,mr[0]-mr[1])-6;
		}
	}
	return 0;
}
int play4_event(int (*p)[5],int x,int y,int op,int Nc){
	if((*(*(p+x)+y))!=0){
		return 0;
	}
	int t;
	for(t=0;t<Nc;t++){
		(*(*(p+t)+y)) += op;
		(*(*(p+x)+t)) += op;
	}
	(*(*(p+x)+y)) -= op;
	play4_max_judge(p,Nc);
	return 1;
}
void play4_max_judge(int (*p)[5],int Nc){
	int i,j;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			if((*(*(p+i)+j))>=10||(*(*(p+i)+j))<=-10){
				play4_kaboom(p,i,j,Nc,(*(*(p+i)+j))/10);
				return play4_max_judge(p,Nc);
			}
		}
	}
}
void play4_kaboom(int (*p)[5],int i,int j,int Nc,int v){// 
	(*(*(p+i)+j)) = (*(*(p+i)+j))%10;
	Nc--;
	if(i>0){
		if(j>0){
			(*(*(p+i-1)+j-1)) += 2*v;
		}
		if(j<Nc){
			(*(*(p+i-1)+j+1)) += 2*v;
		}
	}
	if(i<Nc){
		if(j>0){
			(*(*(p+i+1)+j-1)) += 2*v;
		}
		if(j<Nc){
			(*(*(p+i+1)+j+1)) += 2*v;
		}
	}
}
void p4_wmap(int (*p)[5],int Nc){
	int i,j;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			p4_n_wb(lx+j*2,ly+i,(*(*(p+i)+j)));
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p4_n_wb(int x,int y,int n){
	gtxy(x,y);
	if(n==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
		printf("▇");
		return;
	}
	else if(n>0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);	
	}
	else{
		n =- n;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);	
	}
	printf("%2d",n);
}
void p_situ(int cb,int bl,int wh){
	gtxy(17,2);
	printf("%2d",c_mine);
	gtxy(17,4);
	printf("%2d",cb);
	gtxy(34,2);
	printf("%2d",bl);
	gtxy(34,4);
	printf("%2d",wh);
}
void p_lev(int lv){
	gtxy(70,2);
	printf("AI<");
	switch(lv){
		case 1:
			printf("E250");
			break;
		case 2:
			printf("3000A");
			break;
		case 3:
			printf("ALIce");
			break;
		case 4:
			printf("Noah");
			break;
		case 5:
			printf("Noah's Ark");
			break;
	}
	printf(">");
}
void calcu_situ(int (*p)[5],int Nc){
	c_blank = 0;
	mr[0] = 0;
	mr[1] = 0;
	int i,j;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			if((*(*(p+i)+j))==0){
				c_blank++;
			}
			else if((*(*(p+i)+j))>0){
				mr[0]++;
			}
			else if((*(*(p+i)+j))<0){
				mr[1]++;
			}
		}
	}
}
void play4_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
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
	printf("剩余回合数:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("剩余空格数:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf(" BLACK:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),244);
	gtxy(26,4);
	printf(" WHITE:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("状态：");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,26);
	printf("|▔▔▔▔▔|"); 
	gtxy(67,27);
	printf("|   求和   |");
	gtxy(67,28);
	printf(" ▔▔▔▔▔ "); 
}
int d_end(int v,int r){
	if(r==0){
		switch(v){
			case 1:
				return MessageBox(NULL,"平局了欸","AI-E250",MB_YESNO);
			case 2:
				return MessageBox(NULL,"我的线路状态很好。\n我不会再犯下同样的错误。\n我将完美完成任务。","AI-3000A",MB_YESNO);
			case 3:
				return MessageBox(NULL,"奇怪，到底是哪步出错了？","ALIce",MB_YESNO);
			case 4:
				return MessageBox(NULL,"切\n走狗屎运的渣渣","Noah",MB_YESNO);
			case 5:
				return MessageBox(NULL,"你，很不错","7000X",MB_YESNO);
		}
	}
	else if(r>0){
		switch(v){
			case 1:
				return MessageBox(NULL,"哇\n你赢了\n可喜可贺可喜可贺","AI-E250",MB_YESNO);
			case 2:
				return MessageBox(NULL,"过去的我只知道完美完成任务，\n却不懂人类的心。\n今天，我要偿还这一切。","AI-3000A",MB_YESNO);
			case 3:
				return MessageBox(NULL,"失算了，\n看来还需要更多计算才行！","ALIce",MB_YESNO);
			case 4:
				return MessageBox(NULL,"点儿背\n算你走运\n下一局，我可不会手下留情了","Noah",MB_YESNO);
			case 5:
				return MessageBox(NULL,"shutdown -r now","7000X",MB_YESNO);
		}
	}
	else if(r<0){
		switch(v){
			case 1:
				return MessageBox(NULL,"你怎么输了","AI-E250",MB_YESNO);
			case 2:
				return MessageBox(NULL,"我是最完美的,\n我完美的完成了任务,\n可，什么是感情？","AI-3000A",MB_YESNO);
			case 3:
				return MessageBox(NULL,"运筹帷幄","ALIce",MB_YESNO);
			case 4:
				return MessageBox(NULL,"就凭你，也妄想赢我？","Noah",MB_YESNO);
			case 5:
				return MessageBox(NULL,"目标达成\n一切正常","7000X",MB_YESNO);
		}
	}
}
int AI_Simple(int (*p)[5],int Nc){//预测单步结果取最坏 
	srand(time(NULL));
	if(c_blank==25){
		return rand()%25;
	}
	int cache[25] = {0};//记录空格位置 
	int comput_result[25] = {0};//记录单步计算最坏结果 []=cache下标 
	
	AI_get_situ(p,cache,Nc);//当前局势
	int buffer = c_blank;//当前空格数量	
	int calcu_mod[5][5] = {0};//当前雷图(起始状态)
	int (*q)[5] = NULL;
    q = calcu_mod;
	    
    int i,j=-1,k=0;//i循环 j数组计数 k最小结果 
    for(i=0;i<buffer;i++){
    	memcpy(q,p,25*sizeof(int));
    	//i=cache[i]/5 j=cache[i]%5
    	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    		calcu_situ(q,5);
    		if(j==-1){
    			j=0;
    			comput_result[j++] = i;
    			k = mr[0]-mr[1];
    			continue;
			}
			else{
				if(k<mr[0]-mr[1]){
					j=0;
    				comput_result[j++] = i;
    				k = mr[0]-mr[1];
    				continue;
				}
				else if(k==mr[0]-mr[1]){
    				comput_result[j++] = i;
    				continue;
				}
			}
		}
	}
	return cache[comput_result[rand()%j]];
}
int AI_Normal(int (*p)[5],int Nc){//随机取点
	int cache[25] = {0};
	srand(time(NULL));
	AI_get_situ(p,cache,Nc);
	return cache[rand()%c_blank];
}
int AI_get_situ(int (*p)[5],int b[25],int Nc){
	c_blank = 0;
	int i,j,r=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			if((*(*(p+i)+j))==0){
				b[c_blank++] = i*5+j;
			}
			else if((*(*(p+i)+j))>0){
				r++;
			}
			else if((*(*(p+i)+j))<0){
				r--;
			}
		}
	}
	return r;
}
int AI_ALIce(int (*p)[5],int Nc){//预测单步结果取最优 
	srand(time(NULL));
	if(c_blank==25){
		return rand()%25;
	}
	int cache[25] = {0};//记录空格位置 
	int comput_result[25] = {0};//记录单步计算最优结果 []=cache下标 	
	AI_get_situ(p,cache,Nc);//当前局势
	int buffer = c_blank;//当前空格数量	
	int calcu_mod[5][5] = {0};//当前雷图(起始状态)
	int (*q)[5] = NULL;
    q = calcu_mod;    
    int i,j=-1,k=0;//i循环 j数组计数 k最小结果 
    for(i=0;i<buffer;i++){
    	memcpy(q,p,25*sizeof(int));
    	//i=cache[i]/5 j=cache[i]%5
    	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    		calcu_situ(q,5);
    		if(j==-1){
    			j=0;
    			comput_result[j++] = i;
    			k = mr[0]-mr[1];
    			continue;
			}
			else{
				if(k>mr[0]-mr[1]){
					j=0;
    				comput_result[j++] = i;
    				k = mr[0]-mr[1];
    				continue;
				}
				else if(k==mr[0]-mr[1]){
    				comput_result[j++] = i;
    				continue;
				}
			}
		}
	}
	return cache[comput_result[rand()%j]];
}
int AI_Noah(int (*p)[5],int Nc){//
	srand(time(NULL));
	if(c_blank==25){
		return rand()%25;
	}
	int cache[25] = {0};//记录空格位置
	AI_get_situ(p,cache,Nc);//当前局势
	int buffer = c_blank;//当前空格数量
	if(buffer==1){
		return cache[0];
	}
	if(c_mine==1){		 
		int comput_result[25] = {0};//记录单步计算最优结果 []=cache下标 
		int calcu_mod[5][5] = {0};//当前雷图(起始状态)
		int (*q)[5] = NULL;
    	q = calcu_mod; 
    	int i,j=-1,k=0;//i循环 j数组计数 k最小结果
    	for(i=0;i<buffer;i++){
    		memcpy(q,p,25*sizeof(int));
    		if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    			calcu_situ(q,5);
    			if(j==-1){
    				j=0;
    				comput_result[j++] = i;
    				k = mr[0]-mr[1];
    				continue;
				}
				else{
					if(k>mr[0]-mr[1]){
						j=0;
    					comput_result[j++] = i;
    					k = mr[0]-mr[1];
    					continue;
					}
					else if(k==mr[0]-mr[1]){
    					comput_result[j++] = i;
    					continue;
					}
				}
				if(k<0){
					break;
				}
			}
		}
		return cache[comput_result[rand()%j]];
	}
	if(c_mine==2){
		int comput_result[3][25] = {0,0,0};//[0][]P [1][]胜 [2][]负
		int calcu_mod[5][5] = {0};//当前雷图(计算起始状态)
		int (*q)[5] = NULL;
  		q = calcu_mod;
 	 	int i,j=-1;//i循环 j数组定位 
  	 	for(i=0;i<buffer;i++){
    		memcpy(q,p,25*sizeof(int));
    		//i=cache[i]/5 j=cache[i]%5
   		 	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    			calcu_situ(q,5);
    			if(c_blank==0&&mr[0]<mr[1]){//获胜
    				return cache[i];
				}
				calcu_situ(q,5);
				AI_Noah_laststep_pred(q,Nc);
				comput_result[1][i] =  mr[0];
				comput_result[2][i] = mr[1];
				if(c_blank!=0){
					comput_result[0][i] = (c_blank-mr[1])*100/c_blank;
				}
				else{
					comput_result[0][i] = 0;
				}
			}
		}
		for(i=0;i<buffer;i++){
			if(comput_result[2][i]==comput_result[3][i]){
				return cache[i];
			}
			if(j==-1){
    			j = i;
    			continue;
			}
			else{
				if(comput_result[0][j]<comput_result[0][i]){
					if(comput_result[1][j]<=comput_result[1][i]){
						j = i;
						continue;
					}
					if(comput_result[2][j]>=comput_result[2][i]){
						j = i;
						continue;
					}
				}
				else if(comput_result[0][j]==comput_result[0][i]){
					if(comput_result[1][j]<comput_result[1][i]){
						j = i;
						continue;
					}
					else if(comput_result[1][j]==comput_result[1][i]){
						if(comput_result[2][j]>comput_result[2][i]){
							j = i;
							continue;
						}
					}
				}
			}
		}
		return cache[j];
	}
	
	int comput_result[25] = {0};//记录单步计算最优结果 []=cache下标 	
	int calcu_mod[5][5] = {0};//当前雷图(计算起始状态)
	int (*q)[5] = NULL;
    q = calcu_mod;   
    int i,j=-1,k=0;//i循环 j数组计数 k最小结果 
    for(i=0;i<buffer;i++){
    	memcpy(q,p,25*sizeof(int));
    	//i=cache[i]/5 j=cache[i]%5
    	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    		calcu_situ(q,5);
    		if(c_blank==0&&mr[0]<mr[1]){//获胜
    			j=0;
    			comput_result[j++] = i;
    			k = mr[0]-mr[1];
    			break;
			}
    		if(j==-1){
    			j=0;
    			comput_result[j++] = i;
    			k = mr[0]-mr[1];
    			continue;
			}
			else{
				if(k>mr[0]-mr[1]){
					j=0;
    				comput_result[j++] = i;
    				k = mr[0]-mr[1];
    				continue;
				}
				else if(k==mr[0]-mr[1]){
    				comput_result[j++] = i;
    				continue;
				}
			}
		}
	}
	return cache[comput_result[rand()%j]];
}
void AI_Noah_laststep_pred(int (*p)[5],int Nc){
	int cache[25] = {0};//记录空格位置	
	AI_get_situ(p,cache,Nc);//当前局势
	int buffer = c_blank;//当前空格数量	
	int calcu_mod[5][5] = {0};//当前雷图(起始状态)
	int (*q)[5] = NULL;
    q = calcu_mod;   
    int i,w=0,l=0;//i循环 w胜利局数 l失败局数 
    for(i=0;i<buffer;i++){
    	memcpy(q,p,25*sizeof(int));
    	//i=cache[i]/5 j=cache[i]%5
    	if(play4_event(q,cache[i]/5,cache[i]%5,1,5)){
    		calcu_situ(q,5);
    		if(mr[0]-mr[1]>0){
    			l++;
			}
			else if(mr[0]-mr[1]<0){
    			w++;
			}
		}
	}
	mr[0] = w;
	mr[1] = l;
	c_blank = buffer;
}
void AI_event(int (*p)[5],int v){
	Sleep(400);
	int buffer;
	for(;;){
		switch(v){
			case 1:
				buffer = AI_Simple(p,5);//简单 
				break;
			case 2:
				buffer = AI_Normal(p,5);//普通 
				break;
			case 3:
				buffer = AI_ALIce(p,5);
				break;
			case 4:
				buffer = AI_Noah(p,5);
				break;
			case 5:
				buffer = SuperAI_BHR_MFCB_NOAHsARK(p,5);
				break;
		}
		//i=buffer/5 j=buffer%5
		if(play4_event(p,buffer/5,buffer%5,-1,5)){
			Sleep(200);
			p4_wmap(p,5);
        	calcu_situ(p,5);
        	c_mine--;
        	p_situ(c_blank,mr[0],mr[1]);
        	break;
		}
	}
	Sleep(100);
}
void AI_MinefieldCyberBrain_Kernel(int (*p)[5],int pn,unsigned long long *wi,unsigned long long *lo,unsigned long long *dr){//全枚举内核 n(MAX)=25**50 
	int cache[25] = {0};//记录空格位置	
	AI_get_situ(p,cache,5);//当前局势
	int buffer = c_blank;//当前空格数量	
	int calcu_mod[5][5] = {0};//当前雷图(起始状态)
	int (*q)[5] = NULL;
    q = calcu_mod;
    int i;
    for(i=0;i<buffer;i++){
    	memcpy(q,p,25*sizeof(int));
    	//i=cache[i]/5 j=cache[i]%5
    	if(play4_event(q,cache[i]/5,cache[i]%5,pn,5)){
    		calcu_situ(q,5);
    		if(c_mine==1||AIstep==1||c_blank==0){
    			if(mr[0]-mr[1]>0){
    				(*lo)++;
				}
				else if(mr[0]-mr[1]<0){
					(*wi)++;
				}
				else if(mr[0]==mr[1]){
					(*dr)++;
				}
				continue;
			}
			else{
				AIstep--;
				c_mine--;
				AI_MinefieldCyberBrain_Kernel(q,-pn,wi,lo,dr);
				c_mine++;
				AIstep++;
			}
		}
	}
}
int SuperAI_BHR_MFCB_NOAHsARK(int (*p)[5],int Nc){
	srand(time(NULL));
	if(c_blank==25){
		gtxy(68,10);//
    	printf("R:0000   ");
		return rand()%25;
	}	
	int cache[25] = {0};//记录空格位置
	AI_get_situ(p,cache,Nc);//当前局势
	int buffer = c_blank;//当前空格数量
	if(buffer==1){
		gtxy(68,10);//
    	printf("L:%4d",cache[0]*100);
		return cache[0];
	}
	if(c_mine==49){
		gtxy(68,10);//
    	printf("R:0000   ");
		return cache[rand()%buffer];
	}
	if(c_mine==1){
		int comput_result[25] = {0};//记录单步计算最优结果 []=cache下标 
		int calcu_mod[5][5] = {0};//当前雷图(起始状态)
		int (*q)[5] = NULL;
    	q = calcu_mod;
    
    	int i,j=-1,k=0;//i循环 j数组计数 k最小结果
    	for(i=0;i<buffer;i++){
    		memcpy(q,p,25*sizeof(int));
    		//i=cache[i]/5 j=cache[i]%5
    		if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    			calcu_situ(q,5);
    			if(j==-1){
    				j=0;
    				comput_result[j++] = i;
    				k = mr[0]-mr[1];
    				continue;
				}
				else{
					if(k>mr[0]-mr[1]){
						j=0;
    					comput_result[j++] = i;
    					k = mr[0]-mr[1];
    					continue;
					}
					else if(k==mr[0]-mr[1]){
    					comput_result[j++] = i;
    					continue;
					}
				}
				if(k<0){
					break;
				}
			}
		}
		gtxy(68,10);//
    	printf("A:%4d",j*100);
		return cache[comput_result[rand()%j]];
	}	
	int comput_probability[25] = {0};//记录胜率
	int comput_result[25] = {0};//记录最优结果 []=cache下标 	
	int calcu_mod[5][5] = {0};//当前雷图(计算起始状态)
	int (*q)[5] = NULL;
    q = calcu_mod;
    
    if(c_mine%2==1){
    	AIstep = 7;
	}
	else{
		AIstep = 8;
	}
	if(AIstep>c_mine){
		AIstep = c_mine;
	}   
	unsigned long long wi,lo,dr;
    int i;//i循环
    for(i=0;i<buffer;i++){
    	wi = 0;
		lo = 0;
		dr = 0;
    	memcpy(q,p,25*sizeof(int));
    	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    		calcu_situ(q,5);
    		if(c_blank==0){
    			if(mr[0]-mr[1]<0){
    				return cache[i];
				}
				else if(mr[0]-mr[1]>0){
					lo++;
				}
				else if(mr[0]==mr[1]){
					dr++;
				}
				continue;
			}
    		AIstep--;
    		c_mine--;
    		AI_MinefieldCyberBrain_Kernel(q,1,&wi,&lo,&dr);
    		AIstep++;
    		c_mine++;
		}
		comput_probability[i] = (int)(wi*1000/(wi+lo+dr));
		//break;
	}
	int j=-1,k;
	for(i=0;i<buffer;i++){
		if(comput_probability[i]==1000){
			gtxy(68,10);//
    		printf("P:1000  ");
			return cache[i];
		}
		if(j==-1){
			j=0;
    		comput_result[j++] = i;
			k = comput_probability[i];
			continue;
		}
		else{
			if(k<comput_probability[i]){
				j=0;
    			comput_result[j++] = i;
    			k = comput_probability[i];
    			continue;
			}
			else if(k==comput_probability[i]){
    			comput_result[j++] = i;
    			continue;
			}
		}
	}
	gtxy(68,10);//
    printf("P:%4d",k);
	return cache[comput_result[rand()%j]];
}
