#include "yzetmexc.h"
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 

class MS_Cryptography{
	public:
		int codemap[4][4];
		int size;
		MS_Cryptography(int s);
		~MS_Cryptography(){};
		void encryption(void);//加密 
		int checking(int password){//验证 
			if(password==plaintext){
				return 1;
			}
			return 0;
		}
		int showing(){
			printf("\n%d\n",plaintext);
			int i = 0, j = 0;
			for(;i<size;i++){
				for(j=0;j<size;j++){
					printf("%2d ",codemap[i][j]);
				}
				printf("\n");
			}
			for(i=0;i<size;i++){
				for(j=0;j<size;j++){
					printf("%2d ",minemap[i][j]);
				}
				printf("\n");
			}
		}
		int codeshowing(){
			int i = 0, j = 0;
			for(;i<size;i++){
				gtxy(9,8+i);
				for(j=0;j<size;j++){
					printf("%2d ",codemap[i][j]);
				}
			}		
		}
	private:
		int minemap[4][4];//0~2^16-1
		int plaintext;//明文 
		int count_mine(int i, int j){
			int nums = 0;
			if(i>0){
				nums += minemap[i-1][j];
			}
			if(j>0){
				nums += minemap[i][j-1];
			}
			if(i<size-1){
				nums += minemap[i+1][j];
			}
			if(j<size-1){
				nums += minemap[i][j+1];
			}
			return nums;
		}
};
MS_Cryptography::MS_Cryptography(int s){//s密码位数 [2/3/4] ?5
	if(s<2||s>4){
		s = 4;
	}
	if(s<3){
		size = 3;
	} 
	else{
		size = 4;
	}
	int temp = pow(10,s);
	srand(time(NULL));
	plaintext = rand()%temp;
	//gtxy(30,29);
	//printf("%4d",plaintext); 
	temp = plaintext;
	int i = 0, j = 0;
	for(;i<size;i++){
		for(j=0;j<size;j++){
			minemap[i][j] = temp%2;
			temp /= 2;
		}
	}
	encryption();
}
void MS_Cryptography::encryption(void){
	int i = 0, j = 0;
	for(;i<size;i++){
		for(j=0;j<size;j++){
			codemap[i][j] = count_mine(i, j);
		}
	}
} 
class Decodeblock{
	public:
		int blockmap[4][4];
		int size;
		int out;
		Decodeblock(int s);
		~Decodeblock(){};
		int decode(){
			out = 0;
			int i, j;
			for(i=0;i<size;i++){
				for(j=0;j<size;j++){
					out += blockmap[i][j]*pow(2,i*4+j);
				}
			}
			return out;
		}
		int operate(int i, int j){
			blockmap[i][j] = 1-blockmap[i][j];
			out += (blockmap[i][j]*2-1)*pow(2,i*4+j);
			return out;
		}
		void updata_singleblock(int i, int j){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
			gtxy(47+j*3,6+i);
			printf("%2d",blockmap[i][j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		}
		void updata_out(){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			gtxy(50,17);
			int o = out;
			if(o>9999){
				o = 9999;
			}
			printf(" %04d",o);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		}
		void blockshowing(){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
			int i = 0, j = 0;
			for(;i<size;i++){
				gtxy(47,6+i);
				for(j=0;j<size;j++){
					printf("%2d ",blockmap[i][j]);
				}
			}
			updata_out();
		}
};
Decodeblock::Decodeblock(int s){//s密码位数 [2/3/4] ?5
	if(s<2||s>4){
		s = 4;
	}
	if(s<3){
		size = 3;
	} 
	else{
		size = 4;
	}
	int i, j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			blockmap[i][j] = 0;
		}
	}
	decode();
}
class Inputboard{
	public:
		int password[4];
		Inputboard(void){
			int i = 0;
			for(;i<4;i++){
				password[i] = 0;
			}
		}
		~Inputboard(){};
		int getpw(){
			int pw = 0;
			int i = 0;
			for(;i<4;i++){
				pw *= 10;
				pw += password[i];
			}
			return pw;
		}
		void operate_r(int v){
			password[v]++;
			password[v] %= 10;
		}
		void operate_l(int v){
			password[v] += 10;
			password[v]--;
			password[v] %= 10;
		}
		void pwshowing(){
			int i;
			for(i=0;i<4;i++){
				gtxy(76,i*4+5);
				printf("%d",password[i]);
			}
		}
		void updata_singlepw(int v){
			gtxy(76,v*4+5);
			printf("%d",password[v]);
		}
};
void entertainment_c3(){
	e_c3_intr();
	
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
							if(Y>9&&Y<12){
								if(X>3&&X<12){
          							return;
								  }
								else if(X>34&&X<43){
									st = 1;//start
								}
								else if(X>24&&X<33){
									//Oracle
									MessageBox(NULL,"Oracle cannot access  : )","ERROR",MB_OK);
								}
								else if(X>13&&X<22){
									//rules
									c3_rule();
									e_c3_intr();
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
		int pw = e_c3_play();
		if(pw==-1){
			return;
		}
		animate_login(pw);
		if(MessageBox(NULL,"密码破译成功！！！\n恭喜你获得一组新密码！\n是否继续？","CONGRATULATIONS",MB_YESNO)-6){
			return;
		}
	}	
}
void e_c3_intr(){
	clean();
	gtxy(0,1); 			
	printf(" 恺撒：\n");
	printf("   雷域掌握着一种非常规的加密手段\n");
	printf("   通过一段时间的努力，我们已经基本找出了其加密方式\n");
	printf("   但是我们懒得去设计算法破译密文\n"); 	
	printf("   我们现在窃听到了一组有关雷域系统登入密码的密文\n");
	printf("   需要你手动破译密码来登入雷域的一个后台系统\n");
	printf("   说不定还能在系统中找到更加重要的密码来\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   COMEON!!\n\n"); 
	printf("   |▔▔▔▔||▔▔▔▔| |▔▔▔▔||▔▔▔▔|\n"); 
	printf("   | ←返回 ||  规则  | |  谕示  || 开始 →|\n");
	printf("    ▔▔▔▔  ▔▔▔▔   ▔▔▔▔  ▔▔▔▔ \n"); 
}
int e_c3_play(){
	lx=47;
	ly=6;
    
	clean();
	e_c3_frame();
	
	MS_Cryptography msc(4);
	msc.codeshowing();
	
	Decodeblock db(4);
	db.blockshowing();
	
	Inputboard ib;
	ib.pwshowing();
	
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
          					if(Y==1&&(X==85||X==86)){
          						return -1;
							}
							if(Y>20&&Y<24&&X>67&&X<84){
								if(msc.checking(ib.getpw())){
									return ib.getpw();
								}
								animate_error();
								break;
							}
							if(Y>3&&Y<19&&X>67&&X<84){
								//3~19
								if(Y%4==3){//Y!3/7/11/15/19
									break;
								}
								if(X<=78&&X>=73){
									break;
								}
								if(X<73){
									ib.operate_l((Y-3)/4);
								}
								if(X>78){
									ib.operate_r((Y-3)/4);
								}
								ib.updata_singlepw((Y-3)/4);
								break;
							}
							if(X>=48&&X<=57&&Y>=6&&Y<=9){
								if((X-48)%3!=0){
									break;
								}
								db.operate(Y-6,(X-48)/3);
								db.updata_singleblock(Y-6,(X-48)/3);
								db.updata_out();
								break;
							}
		   					break;
				}
			} 		 
		 	break; 
		}
	}
	return -1;
}
void e_c3_frame_basic(){
	int i = 0;
	gtxy(0,i);
	i += 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);                           
	printf("   ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇  ");
	for(;i<25;i+=2){
		gtxy(0,i);
		printf("   ▇                                                                                  ▇/>");
	}
	gtxy(0,i);
	printf("     ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇  ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	for(i=1;i<25;i+=2){
		gtxy(0,i);
		printf(">> ▇                                                                                  ▇ ");
	}
	gtxy(0,i);
	i += 2;
	printf("   ▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇▇  ");	
	gtxy(0,i);
	i += 2;
	printf(">>");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
	printf(" ▇  ▇  ▇  ▇  ▇                  ▇▇  ▇  ▇▇                  ▇  ▇  ▇  ▇  ▇  ");
	gtxy(0,i);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	printf("<<Task Completed/>");
}
void e_c3_frame_interface(){
	int i = 1, j = 84;
	gtxy(85,i++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("×");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(5,1);
	printf("▆▅▄▃▂▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁");	
	for(;i<20;i++){
		gtxy(j,i);
		printf(":▎");
	}
	gtxy(j,i++);
	printf(":▍");
	gtxy(j,i++);
	printf(":▌");
	gtxy(j,i++);
	printf(":▋");
	gtxy(j,i++);
	printf(":▊");
	gtxy(j,i++);
	printf(":▉");
	j = 67;
	gtxy(j,2);
	printf(":∷∷∷∷∷∷∷∷");
	for(i=4;i<20;i++){
		gtxy(j,i);
		printf(":   ▕      ▏");
	}
	for(i=0;i<5;i++){
		gtxy(j,i*4+3);
		printf(":----------------");
	}
	i = 20;
	gtxy(j,i++);
	printf(":----------------");
	for(;i<24;i++){
		gtxy(j,i);
		printf(":");
	}
	gtxy(j,i);
	printf(":∷∷∷∷∷∷∷∷");
	i = 2;
	j = 37;
	for(;i<19;i++){
		gtxy(j,i);
		printf("::");
	}
	gtxy(j,i);
	printf("::::::::::::::::::::::::::::::");
	gtxy(j+2,i-4);
	printf(":--------------------------:");
	gtxy(42,17);
	printf("OUT:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	i = 3;
	j = 5;
	gtxy(j,i++);
	printf(" root@*");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(":~#tcpdump -r code.cap");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(j,i++);
	printf(" Got 128 bytes keystream:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	gtxy(j,i++);
	printf("  ▁▁▁▁▁▁▁▁");
	for(;i<14;i++){
		gtxy(j,i);
		printf("▕                ▏");
	}
	gtxy(j,i);
	printf("  ▔▔▔▔▔▔▔▔");
	i += 2;
	gtxy(j,i++);
	printf(" root@*");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(":~#decodeblock start");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(j,i++);
	printf(" This is free software with");
	gtxy(j,i++);
	printf(" ABSOLUTELY NO WARRANTY.");
	gtxy(j,i);
	printf(" >>>>..");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(71,22);
	printf("< CHECK >");
	i = 3;
	j = 43;
	gtxy(j,i++);
	printf("  ▁▁▁▁▁▁▁▁");
	for(;i<12;i++){
		gtxy(j,i);
		printf("▕                ▏");
	}
	gtxy(j,i);
	printf("  ▔▔▔▔▔▔▔▔");
	j = 69;
	for(i=0;i<4;i++){
		gtxy(j,i*4+5);
		printf("<");
		gtxy(j+13,i*4+5);
		printf(">");
	}
}
void e_c3_frame(){
	e_c3_frame_basic();
	e_c3_frame_interface();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void animate_error(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	Sleep(100);
	gtxy(73,23);
	printf("ERROR");
	Sleep(500);
	gtxy(73,23);
	printf("     ");
	Sleep(350);
	gtxy(72,23);
	printf("<ERROR>");
	Sleep(500);
	gtxy(72,23);
	printf("       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
} 
void animate_login(int pw){
	int i, j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	i = 20;
	j = 5;
	gtxy(j,i++);
	printf(" root@*");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(":~#");
	Sleep(500);
	printf("s");
	Sleep(150);
	printf("sh ");
	Sleep(150);
	printf("*@");
	Sleep(100);
	printf("*");
	Sleep(400);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(j,i++);
	printf(" *@*\'s password: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	Sleep(500);
	printf("%d",pw/100);
	Sleep(150);
	printf("%d",(pw%100)/10);
	Sleep(100);
	printf("%d",pw%10);
	Sleep(500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(j,i++);
	printf(" login as: root");
	Sleep(500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	gtxy(j,i++);
	printf(" root@*");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(":~#");
	Sleep(600);
	printf("sc");
	Sleep(100);
	printf("p");
	Sleep(150);
	printf(" /v");
	Sleep(150);
	printf("ar/");
	Sleep(200);
	printf("bom");
	Sleep(100);
	printf("b");
	Sleep(150);
	printf(".o");
	Sleep(200);
	printf("ut ");
	Sleep(150);
	printf("*@");
	Sleep(100);
	printf("*:");
	Sleep(200);
	printf("/va");
	Sleep(150);
	printf("r/");
	Sleep(400);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	gtxy(j,i++);
	printf(" root@*");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(":~#");
	Sleep(500);
	printf("./");
	Sleep(150);
	printf("bo");
	Sleep(150);
	printf("m");
	Sleep(150);
	printf("b.");
	Sleep(150);
	printf("ou");
	Sleep(100);
	printf("t");
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	srand(time(NULL));
	for(i=0;i<5;i++){
		Sleep(40);
		for(j=0;j<35;j++){
			gtxy(37+j,i+3);
			printf("%d",rand()%2);
			gtxy(49+j,i+3);
			printf("%d",rand()%2);
			gtxy(37+j,i+13);
			printf("%d",rand()%2);
			gtxy(49+j,i+13);
			printf("%d",rand()%2);
			gtxy(37+j,i+8);
			printf("%d",rand()%2);
			gtxy(49+j,i+8);
			printf("%d",rand()%2);
			gtxy(37+j,i+18);
			printf("%d",rand()%2);
			gtxy(49+j,i+18);
			printf("%d",rand()%2);
			Sleep(10);
		}		
	}
	gtxy(37,i+19);
	printf(">>>..../.");
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	i = 10;
	j = 50;
	gtxy(j,i++);	
	printf("  ▁▁▁▁▁  ");
	gtxy(j,i++);
	printf("▕          ▏");
	gtxy(j,i++);
	printf("▕  ACCESS  ▏");
	gtxy(j,i++);
	printf("▕          ▏");
	gtxy(j,i++);
	printf("  ▔▔▔▔▔  ");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void c3_rule(){
	clean();
	gtxy(10,3);
	printf(">>雷域密码术加密方法");
	int cm[4][4] = {{0, 1, 0, 1},
					{1, 1, 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 0}};
	int dm[4][4] = {{2, 1, 2, 0},
					{1, 2, 2, 1},
					{1, 2, 0, 1},
					{0, 0, 1, 0}};
	int cme[3][3] = {{0, 1, 0},
					 {1, 0, 1},
					 {0, 1, 0}};
	int dme[3][3] = {{2, 0, 2},
					 {0, 4, 0},
					 {2, 0, 2}};
	int i, j;
	for(i=0;i<3;i++){
		gtxy(12,i+5);
		for(j=0;j<3;j++){
			if(cme[i][j]==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			}
			printf("%3d",cme[i][j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		}
	}
	gtxy(26,6);
	printf(">>>");
	for(i=0;i<3;i++){
		gtxy(32,i+5);
		for(j=0;j<3;j++){
			if(dme[i][j]==4){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			}
			printf("%3d",dme[i][j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		}
	}
	for(i=0;i<4;i++){
		gtxy(12,i+10);
		for(j=0;j<4;j++){
			printf("%3d",cm[i][j]);
		}
	}
	gtxy(28,12);
	printf(">>>");
	for(i=0;i<4;i++){
		gtxy(32,i+10);
		for(j=0;j<4;j++){
			printf("%3d",dm[i][j]);
		}
	}
	gtxy(16,15);
	printf("密码");
	gtxy(36,15);
	printf("密文");
	gtxy(10,18);
	printf("鼠标左键以继续>>");
	go_on(0,0,0,92,30);
	clean();
	i = 5;
	j = 5;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	gtxy(j,i++);
	printf("  ▁▁▁▁▁▁▁▁");
	for(;i<14;i++){
		gtxy(j,i);
		printf("▕                ▏");
	}
	gtxy(j,i);
	printf("  ▔▔▔▔▔▔▔▔");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	for(i=0;i<4;i++){
		gtxy(9,8+i);
		for(j=0;j<4;j++){
			printf("%2d ",dm[i][j]);
		}
	}
	gtxy(8,2);
	printf(">>操作界面");
	gtxy(j+6,i+12);
	printf("↑密文(可读)"); 
	gtxy(45,10+i);
	printf("↑密码块(可操作)");
	gtxy(44,19);
	printf("↑密码(可读)");
	int p[4] = {1,0,8,2};
	for(i=0;i<4;i++){
		gtxy(76,i*4+5);
		printf("%d",p[i]);
	}
	gtxy(72,24);
	printf("↑验证");
	gtxy(68,3);
	printf("↓密码输入调整↓");
	gtxy(10,24);
	printf("鼠标左键以结束>>");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(71,22);
	printf("< CHECK >");
	i = 3;
	j = 43;
	gtxy(j,i++);
	printf("  ▁▁▁▁▁▁▁▁");
	for(;i<12;i++){
		gtxy(j,i);
		printf("▕                ▏");
	}
	gtxy(j,i);
	printf("  ▔▔▔▔▔▔▔▔");
	j = 69;
	for(i=0;i<4;i++){
		gtxy(j,i*4+5);
		printf("<");
		gtxy(j+13,i*4+5);
		printf(">");
	}
	for(i=0;i<4;i++){
		gtxy(47,6+i);
		for(j=0;j<4;j++){
			printf("%2d ",cm[i][j]);
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(42,17);
	printf("OUT:");
	gtxy(50,17);
	printf("%5d",1082);
	gtxy(85,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("×");
	go_on(0,0,0,92,30);	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
} 
