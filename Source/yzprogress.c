#include "yzprogress.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
extern int mr[2];
extern int AIstep;

int mode(){
	clean();
	//SetSize(30,15);
	gtxy(1,1);
	printf("模式选择:\n");
	printf("   ▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕                  ▏\n");
	printf(" ▕ § 经典模式      ▏\n");
	printf(" ▕------------------▏\n");
	printf(" ▕                  ▏\n");
	printf(" ▕ ∞ 合约挑战      ▏\n");	
	printf(" ▕------------------▏\n");
	printf(" ▕                  ▏\n");
	printf(" ▕ ☆ 新手教程      ▏\n");
	printf(" ▕------------------▏\n");
	printf(" ▕                  ▏\n");
	printf(" ▕ ǘ 追加-娱乐      ▏\n");
	printf(" ▕                  ▏\n");
	printf("   ▔▔▔▔▔▔▔▔▔  "); 
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
          					if(X>2&&X<21){
          						if(Y==3||Y==4){
          							return 1;//经典 
								  }
								else if(Y==6||Y==7){
									return 2;//挑战 
								}
								else if(Y==9||Y==10){
									return 3;//教程
								}
								else if(Y==12||Y==13||Y==14){
									return 4;//娱乐 
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void classic(){
	while(1){
		if(game(4,0,0,0,0,0,0,0)){
			return;
		}
	}	
}
void contract(){
	clean(); 
	//SetSize(50,30);
	gtxy(0,1); 
	printf("  |▔▔▔▔|\n"); 
	printf("  | ←返回 |\n"); 
	printf("   ▔▔▔▔                   :合约选择\n"); 
	printf("   ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  \n");	
	printf(" ▕         |    总雷数+10             ▏\n");
	printf(" ▕         |--------------------------▏\n");
	printf(" ▕    ▲   |    合并雷块与雷数统计    ▏\n");
	printf(" ▕         |--------------------------▏\n");
	printf(" ▕         |    去除首次点击保护      ▏\n");
	printf(" ▕---------|--------------------------▏\n");
	printf(" ▕         |    三维阶数+1，总雷数+20 ▏\n");
	printf(" ▕   ▲▼  |--------------------------▏\n");
	printf(" ▕         |    限时300s              ▏\n");
	printf(" ▕---------|--------------------------▏\n");	
	printf(" ▕         |    三维阶数+1，总雷数+40 ▏\n");
	printf(" ▕         |--------------------------▏\n");
	printf(" ▕  ▲▼▲ |    禁止标雷              ▏\n");
	printf(" ▕         |--------------------------▏\n");
	printf(" ▕         |    失去全部重生十字章    ▏\n");
	printf("   ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔ \n");
	printf("                             |▔▔▔▔|\n"); 
	printf("                             | 开始 →|\n");
	printf("                              ▔▔▔▔ \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);//控制台窗口句柄 
	hInput = GetStdHandle(STD_INPUT_HANDLE);//输入设备句柄 
	int rt,cc[8]={0},control=0;
	while(1)
	{
	    ReadConsoleInput(hInput, &inRec, 1, &numRead);//读取1个输入事件 
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
          						return;
          						//返回 
							  }
							if(X>29&&X<38&&Y>20&&Y<23){
          						control = 1;//开始 
							  }
							if(X>12&&X<39){
								switch(Y){
									case 5:
										contract_event1(cc,0);
										break;
									case 7:
										contract_event1(cc,1);
										break;
									case 9:
										contract_event1(cc,2);
										break;
									case 11:
										contract_event1(cc,3);
										break;
									case 13:
										contract_event1(cc,4);
										break;
									case 15:
										contract_event1(cc,5);
										break;
									case 17:
										contract_event1(cc,6);
										break;
									case 19:
										contract_event1(cc,7);
										break;
								}
							}
		   					break; 
		  		}
			} 		 
		 	break;
		}
		if(control){
			break;
		}
	}
	int Nc=4,M=0;
	if(cc[0]){
		M+=10;
	}	
	if(cc[3]){
		Nc++;
		M+=20;
	}
	if(cc[5]){
		Nc++;
		M+=40;
	}
	//cc[1] merge
	//cc[2] firstpro
	//cc[4] timelim
	//cc[6] signres
	//cc[7] reviveprop	
	while(1){
		if(game(Nc,M,cc[1],cc[2],cc[4],cc[6],cc[7],contract_event2(cc))){
			return;
		}
	}
}
void course(){
	for(;;){
		switch(choice()){
			case 0:
				return;
			case 1:
				operation();
				break;
			case 2:
				rule();
				break;
			case 3:
				detail();
				break;
		}
	}
}
int choice(){
	clean();
	//SetSize(30,15);
	gtxy(0,1); 	
	printf("  |▔▔▔▔|\n"); 
	printf("  | ←返回 |\n"); 
	printf("   ▔▔▔▔       \n"); 
	printf("    ▁▁▁▁▁▁▁▁▁  \n");	
	printf("  ▕                  ▏\n");
	printf("  ▕  Ⅰ 操作入门     ▏\n");
	printf("  ▕------------------▏\n");
	printf("  ▕                  ▏\n");
	printf("  ▕  Ⅱ 规则简介     ▏\n");	
	printf("  ▕------------------▏\n");
	printf("  ▕                  ▏\n");
	printf("  ▕  Ⅲ 合约详情     ▏\n");
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
void entertainment(){// 
	for(;;){
		switch(e_choice()){
			case 0:
				return;
			case 1:
				entertainment1();
				break;
			case 2:
				entertainment2();
				break;
			case 3:
				entertainment3();
				break;
			case 4:
				entertainment4();
				break;
			case 5:
				entertainment5();
				break;
			case 6:
				entertainment6();
				break;
			case 7:
				entertainment7();
				break;
			case 8:
				entertainment8();
				break;
			case 9:
				extra();
				break;
		}
	}
}
int e_choice(){// 
	clean();
	gtxy(0,1); 	
	printf("  |▔▔▔▔|\n"); 
	printf("  | ←返回 |\n"); 
	printf("   ▔▔▔▔       \n"); 
	printf("    ▁▁▁▁▁▁▁▁▁▁▁               ▁▁▁▁▁▁▁▁▁▁▁ \n");	
	printf("  ▕                      ▏           ▕                      ▏\n");
	printf("  ▕  Ⅰ 初识!雷域捞针    ▏           ▕     Ⅹ  *番外篇      ▏\n");
	printf("  ▕----------------------▏           ▕                      ▏\n");
	printf("  ▕                      ▏             ▔▔▔▔▔▔▔▔▔▔▔  \n");
	printf("  ▕  Ⅱ 求助!逆向寻雷    ▏\n");	
	printf("  ▕----------------------▏\n");
	printf("  ▕   * BackingStore     ▏\n");
	printf("  ▕     Exception        ▏\n");//Ⅲ 
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅳ 御!日月          ▏\n");//黑白雷
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅴ 危机!炸弹人来袭  ▏\n");//雷图争夺 
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅵ 反击!引爆天雷    ▏\n");//打灰机
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅶ 缔!时光          ▏\n");//无尽扫雷 
	printf("  ▕----------------------▏\n");
	printf("  ▕                      ▏\n");
	printf("  ▕  Ⅷ 永别!雷之终焉    ▏\n");
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
          						if(Y==5||Y==6){
          							return 1;
								  }
								else if(Y==8||Y==9){
									return 2;
								}
								else if(Y==11||Y==12){
									return 3;
								}
								else if(Y==14||Y==15){
									return 4;
								}
								else if(Y==17||Y==18){
									return 5;
								}
								else if(Y==20||Y==21){
									return 6;
								}
								else if(Y==23||Y==24){
									return 7;
								}
								else if(Y==26||Y==27||Y==28){
									return 8;
								}
							}
							if(X>40&&X<63){
								if(Y>4&&Y<8){
									return 9;
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}






