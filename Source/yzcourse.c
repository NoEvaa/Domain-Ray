#include "yzcourse.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int lx,ly;//定位 

void operation(){	
	o_1();
	o_2();
	o_3(); 
}
void o_1(){
	int x=1,y=2;
	//0
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                 ");
	gtxy(x,y++);
	printf(" 欢迎来到操作入门教程!           "); 
	gtxy(x,y++);
	printf(" 这是一个十分简单易上手的游戏，  ");
	gtxy(x,y++);
	printf(" 通过鼠标左右键即可完成全部操作。");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕--------------------------------------------------------------------------------------▏\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("难度:");
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                     ");
	gtxy(x,y++);
	printf(" 这是参数栏，记录了该局中各参数。                    "); 
	gtxy(x,y++);
	printf(" 合理观察参数栏中各参数，我们能够快速掌握当前局势。  ");
	gtxy(x,y++);
	printf(" 具体各参数的意义请见<Ⅱ规则简介>                    ");
	gtxy(x,y++);
	printf("                                                     ");
	gtxy(x,y++);
	printf("                              (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                     ");
	go_on(0,0,0,92,30);
}
void o_2(){
	int x=1,y=2;
	//0
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                            ");
	gtxy(x,y++);
	printf(" 接下来要来介绍一下游戏中会遇到的图形       "); 
	gtxy(x,y++);
	printf("                                            ");
	gtxy(x,y++);
	printf("                     (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                            ");
	go_on(0,0,0,92,30);
	//1
	clean();
	x = 5;
	y = 8;
	gtxy(x,y++);
	printf("▇");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" 左边是一个雷块                    "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,0,0,92,30);
	//2
	clean();
	x = 5;
	y = 6;
	gtxy(x,y++);
	printf("▇▇▇▇");
	gtxy(x,y++);
	printf("▇▇▇▇");
	gtxy(x,y++);
	printf("▇▇▇▇");
	gtxy(x,y++);
	printf("▇▇▇▇");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" 现在是一个4*4的雷图               "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,0,0,92,30); 
	//3 
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" 雷块是唯一能用鼠标左击的图形      "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,0,0,92,30); 
	//4
	gtxy(7,8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("▇");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" 现在让我们用鼠标左击绿色的雷块    "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("          (鼠标左击绿色雷块)     ▼");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,7,8,1,0);
	//5
	clean();
	x = 5;
	y = 6;
	gtxy(x,y++);
	printf(" 0▇ 0 0");
	gtxy(x,y++);
	printf(" 0 1 0 0");
	gtxy(x,y++);
	printf(" 0 0 0 0");
	gtxy(x,y++);
	printf(" 0 0 0 0");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" 真棒，雷图被展开了！              "); 
	gtxy(x,y++);
	printf(" 还剩下一个雷块没被打开，          ");
	gtxy(x,y++);
	printf(" 我怀疑在它下面埋了一个雷，        ");
	gtxy(x,y++);
	printf(" 先鼠标右击标记一下它吧！          ");
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("          (鼠标右击剩余雷块)     ▼");
	gtxy(x,y++);
	printf("                                   ");
	go_on(1,7,6,1,0);
	//6
	gtxy(7,6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("※");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                         ");
	gtxy(x,y++);
	printf(" 很不错                                  "); 
	gtxy(x,y++);
	printf(" 现在那个雷块被标记为红色图形，          ");
	gtxy(x,y++);
	printf(" 雷块被标记时我们无法再左击该雷块，      ");
	gtxy(x,y++);
	printf(" 但是能通过右击该图形将它还原成雷块图形。");
	gtxy(x,y++);
	printf("                                         ");
	gtxy(x,y++);
	printf("              (鼠标右击被标记雷块)     ▼");
	gtxy(x,y++);
	printf("                                         ");
	go_on(1,7,6,1,0);
	//7
	gtxy(7,6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("▇");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                         ");
	gtxy(x,y++);
	printf(" 变回来了吧                              "); 
	gtxy(x,y++);
	printf(" 通过灵活使用鼠标右键，                  ");
	gtxy(x,y++);
	printf(" 我们可以快速将疑似是雷的雷块标记起来，  ");
	gtxy(x,y++);
	printf(" 防止误点等操作。                        ");                         
	gtxy(x,y++);
	printf("                                         ");
	gtxy(x,y++);
	printf("                  (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                         ");
	go_on(0,0,0,92,30);	
}
void o_3(){
	int x,y;
	//0
	clean();
	x = 5;
	y = 6;
	gtxy(x,y++);
	printf("▇▇▇▇▇▇▇");
	gtxy(x,y++);
	printf("▇▇▇▇▇×▇");
	gtxy(x,y++);
	printf("▇▇▇▇▇▇▇");
	gtxy(7,7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);	
	printf("×");
	gtxy(11,7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);	
	printf("×");
	x = 20;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 在左边的雷图中有三个不同颜色的叉叉     "); 
	gtxy(x,y++);
	printf(" 当在游戏中出现这种叉叉时，             ");
	gtxy(x,y++);
	printf(" 代表这你踩到雷了!!                     "); 
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30); 
	//1
	x = 20;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 出现白叉叉和红叉叉时一般你已死亡       "); 
	gtxy(x,y++);
	printf(" 如果你踩到雷时没有立即死亡，           ");
	gtxy(x,y++);
	printf(" 则该位置会被紫叉叉代替。               "); 
	gtxy(x,y++);
	printf(" 叉叉图形无法被鼠标左键或右键。         "); 
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30);
	//2
	clean();
	x = 1;
	y = 2;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" 好了你现在已经了解了游戏的操作方法     "); 
	gtxy(x,y++);
	printf(" 再去学习一下游戏规则吧~                ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (鼠标左键以结束)     ▼");
	gtxy(x,y++);
	printf("                                        ");
	go_on(0,0,0,92,30); 	 
}
void rule(){
	r_1();
	r_2(); 
}
void r_1(){
	int x=1,y=2;
	//0
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                 ");
	gtxy(x,y++);
	printf(" 欢迎来到规则介绍教程!           "); 
	gtxy(x,y++);
	printf(" 本游戏虽名为扫雷，              ");
	gtxy(x,y++);
	printf(" 但为了降低游戏难度，            ");
	gtxy(x,y++);
	printf(" 故对原有扫雷规则进行简化。      ");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	p_newmap(2,2,4);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 上图是一个2*4*4*4的正常雷图              "); 
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	//2
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(2,6);
	printf("--");
	gtxy(38,6);
	printf("--");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" 图示绿色短线为四维分界线                 ");
	gtxy(x,y++);
	printf(" 将上下分为两个4*4*4的三维雷图            "); 
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	//3
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(2,6);
	printf("--");
	gtxy(38,6);
	printf("--");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(14,3);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(14,2);
	printf("▇");
	gtxy(14,4);
	printf("▇");
	gtxy(12,3);
	printf("▇");
	gtxy(16,3);
	printf("▇");
	gtxy(4,3);
	printf("▇");
	gtxy(24,3);
	printf("▇");
	gtxy(14,8);
	printf("▇");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                           ");
	gtxy(x,y++);
	printf(" 对于任意雷块                                              ");
	gtxy(x,y++);
	printf(" 它将统计其上下左右前后以及第四维同一位置的雷数            "); 
	gtxy(x,y++);
	printf(" 如图，绿色雷块最终雷数取决于黄色雷块是否为雷              ");
	gtxy(x,y++);
	printf(" 显然，上限为7                                             ");
	gtxy(x,y++);
	printf("                                                           ");
	gtxy(x,y++);
	printf("                                    (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                           ");
	go_on(0,0,0,92,30);
	//4
	clean();
	p_newmap(2,2,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(14,2);
	printf("▇");
	gtxy(2,10);
	printf("▇");
	gtxy(38,9);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(14,3);
	printf("▇");
	gtxy(12,2);
	printf("▇");
	gtxy(16,2);
	printf("▇");
	gtxy(4,2);
	printf("▇");
	gtxy(24,2);
	printf("▇");
	gtxy(14,7);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(2,9);
	printf("▇"); 
	gtxy(4,10);
	printf("▇");
	gtxy(12,10);
	printf("▇");
	gtxy(2,5);
	printf("▇");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	gtxy(38,8);
	printf("▇");
	gtxy(38,10);
	printf("▇");
	gtxy(36,9);
	printf("▇");
	gtxy(28,9);
	printf("▇");
	gtxy(38,4);
	printf("▇");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                           ");
	gtxy(x,y++);
	printf(" 按此规则                                                  ");
	gtxy(x,y++);
	printf(" 位于8角的雷块雷数上限为4                                  ");
	gtxy(x,y++);
	printf(" 位于12棱上的雷块雷数上限为5                               ");
	gtxy(x,y++);
	printf(" 位于6面上的雷块雷数上限为6                                ");
	gtxy(x,y++);
	printf("                                                           ");
	gtxy(x,y++);
	printf("                                    (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                           ");
	go_on(0,0,0,92,30);
}
void r_2(){
	int x=1,y=2;
	//0
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                 ");
	gtxy(x,y++);
	printf(" 现在来介绍一下参数栏            "); 
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕                     |                    |                   |                       ▏\n");
	printf(" ▕--------------------------------------------------------------------------------------▏\n");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("难度:");
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                            ");
	gtxy(x,y++);
	printf(" 时间：形成当前局势所用时长，单位秒，范围1-9999             "); 
	gtxy(x,y++);
	printf(" 重生十字章：萨满复活时需要用到的材料。                     ");
	gtxy(x,y++);
	printf("             如果你一不小心踩到了雷，不用紧张，             ");
	gtxy(x,y++);
	printf("             只要你有足够的重生十字章，你便能够复活!        ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                            ");
	go_on(0,0,0,92,30);
	//2
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                            ");
	gtxy(x,y++);
	printf(" B1/B2：雷图中未展开雷块的数量统计，最大值为全未展开时      "); 
	gtxy(x,y++);
	printf("        B1为分界线上方4*4*4雷图统计，B2为下方               ");
	gtxy(x,y++);
	printf(" M1/M2：剩余未标记雷数，最大值为全未标记时                  ");
	gtxy(x,y++);
	printf("        M1为分界线上方4*4*4雷图统计，M2为下方               ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                            ");
	go_on(0,0,0,92,30);	 
	//3
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                            ");
	gtxy(x,y++);
	printf(" 注：当踩到雷并使用重生十字章复活后                         "); 
	gtxy(x,y++);
	printf("     该雷块状态变为展开，即相对应B1/B2 -1                   ");
	gtxy(x,y++);
	printf("     该局游戏中总雷数-1，即相对应M1/M2 -1                   ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                            ");
	go_on(0,0,0,92,30);	
	//4
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                            ");
	gtxy(x,y++);
	printf(" 难度：合约模式下所选合约等级总和                           "); 
	gtxy(x,y++);
	printf("       经典模式下难度为0                                    ");
	gtxy(x,y++);
	printf(" 状态：一般为<正常>                                         ");
	gtxy(x,y++);
	printf("       合约模式下根据所选合约会出现<超时>                   ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (鼠标左键以继续)     ▼");
	gtxy(x,y++);
	printf("                                                            ");
	go_on(0,0,0,92,30); 
	//5
	x = 1;
	y = 2;
	clean();
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                 ");
	gtxy(x,y++);
	printf(" 游戏规则介绍完毕                "); 
	gtxy(x,y++);
	printf(" 剩下的就靠你自己摸索吧~         ");
	gtxy(x,y++);
	printf(" GOOD LUCK                       ");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (鼠标左键以结束)     ▼");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
}
void detail(){
	clean();
	gtxy(0,1); 
	printf("合约详情：\n"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕              |               |               |               ▏\n");
	printf(" ▕              |               |               |               ▏\n");
	printf(" ▕              |               |               |               ▏\n");
	printf(" ▕--------------------------------------------------------------▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕------------------------|                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");		
	printf(" ▕------------------------|                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf(" ▕                        |                                     ▏\n");
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ \n");
	gtxy(25,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("▲");
	gtxy(40,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("▲▼");
	gtxy(55,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("▲▼▲");
	gtxy(6,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("←返回");
	d_1();
	
	int slide = 1;
	
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
          					if(Y>=3&&Y<=5){
          						if(X>2&&X<17){
          							return;
								  }
								else if(X>17&&X<33){
									d_1();
									slide = 1;
								}
								else if(X>33&&X<49){
									d_2();
									slide = 2;
								}
								else if(X>49&&X<65){
									d_3();
									slide = 3;
								}
								break;
							  }
							if(X>2&&X<27){
								if(Y>=7&&Y<=9){
									d_more(slide,1);
								}
								else if(Y>=11&&Y<=13){
									d_more(slide,2);
								}
								else if(Y>=15&&Y<=17){
									d_more(slide,3);
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
} 
void d_1(){
	gtxy(4,8);
	printf("                     ");
	gtxy(4,8);
	printf("总雷数+10");
	gtxy(4,12);
	printf("                     ");
	gtxy(4,12);
	printf("合并雷块与雷数统计");
	gtxy(4,16);
	printf("                     ");
	gtxy(4,16);
	printf("去除首次点击保护");
	d_more(1,1);
}
void d_2(){
	gtxy(4,8);
	printf("                     ");
	gtxy(4,8);
	printf("三维阶数+1，总雷数+20");
	gtxy(4,12);
	printf("                     ");
	gtxy(4,12);
	printf("限时300s");
	gtxy(4,16);
	printf("                     ");
	d_more(2,1);
}
void d_3(){
	gtxy(4,8);
	printf("                     ");
	gtxy(4,8);
	printf("三维阶数+1，总雷数+40");
	gtxy(4,12);
	printf("                     ");
	gtxy(4,12);
	printf("禁止标雷");
	gtxy(4,16);
	printf("                     ");
	gtxy(4,16);
	printf("失去全部重生十字章");
	d_more(3,1);
}
void d_clean(){
	int y=8;
	for(y=8;y<=16;y++){
		gtxy(32,y);
		printf("                              ");
	}
}
void d_more(int s,int cd){
	d_clean();
	int y=8;
	switch(s){
		case 1:{
			switch(cd){
				case 1:
					gtxy(34,y++);
					printf("<总雷数+10>");
					gtxy(32,y++);
					printf("该局内雷数总量增加10");
					gtxy(32,y++);
					printf("即上下雷图各增加5");
					return;
				case 2:
					gtxy(34,y++);
					printf("<合并雷块与雷数统计>");
					gtxy(32,y++);
					printf("该局内上下雷图：");
					gtxy(32,y++);
					printf(" 未展开雷块数量合并展示");
					gtxy(32,y++);
					printf(" 即B1与B2值相加，在B1中显示");
					gtxy(32,y++);
					gtxy(32,y++);
					printf(" 总雷数合并展示");
					gtxy(32,y++);
					printf(" 即M1与M2值相加，在M1中显示");
					return;
				case 3:
					gtxy(34,y++);
					printf("<去除首次点击保护>");
					gtxy(32,y++);
					printf("关闭<保护条例>：");
					gtxy(32,y++);
					printf(" 新游戏首次点击时");
					gtxy(32,y++);
					printf(" 该雷块周围雷数必为0");
					gtxy(32,y++);
					printf("即首次点击可能为雷");
					return;
			}
			break;
		}
		case 2:{
			switch(cd){
				case 1:
					gtxy(34,y++);
					printf("<三维阶数+1，总雷数+20>");
					gtxy(32,y++);
					printf("三维阶数增加1阶");
					gtxy(32,y++);
					printf("即雷图变为2*(N+1)*(N+1)*(N+1)");
					gtxy(32,y++);
					gtxy(32,y++);
					printf("该局内雷数总量增加20");
					gtxy(32,y++);
					printf("即上下雷图各增加10");
					return;
				case 2:
					gtxy(34,y++);
					printf("<限时300s>");
					gtxy(32,y++);
					printf("在规定时间300秒内完成游戏");
					gtxy(32,y++);
					printf("如果超出规定时间");
					gtxy(32,y++);
					printf("状态将会变为<超时>");
					gtxy(32,y++);
					printf("但不影响游戏进程");
					gtxy(32,y++);
					printf("如果<超时>状态下完成游戏");
					gtxy(32,y++);
					printf("可获得胜利，但该合约失效");
					return;
				case 3:
					return;
			}
			break;
		}
		case 3:{
			switch(cd){
				case 1:
					gtxy(34,y++);
					printf("<三维阶数+1，总雷数+40>");
					gtxy(32,y++);
					printf("三维阶数增加1阶");
					gtxy(32,y++);
					printf("即雷图变为2*(N+1)*(N+1)*(N+1)");
					gtxy(32,y++);
					gtxy(32,y++);
					printf("该局内雷数总量增加40");
					gtxy(32,y++);
					printf("即上下雷图各增加20");
					return;
				case 2:
					gtxy(34,y++);
					printf("<禁止标雷>");
					gtxy(32,y++);
					printf("No Flag!!!");
					gtxy(32,y++);
					printf("经典的NF模式");
					gtxy(32,y++);
					printf("仅能用左键点击完成游戏");
					return;
				case 3:
					gtxy(34,y++);
					printf("<失去全部重生十字章>");
					gtxy(32,y++);
					printf("哦~");
					gtxy(32,y++);
					printf("你不能复活了");
					gtxy(32,y++);
					printf("即重生十字章数量为0");
					return;
			}
			break;
		}
	}	
}
