#include "yzetmd.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];
extern int AIstep;

void entertainment4(){
	e_4();	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //�����豸��� 
	int rt,st = 0;
	int lv=1,od=0;
	p_choice_lv(lv);
	p_choice_od(od);
	while(1)
	{
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//��ȡ1�������¼� 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{ 
		  		rt = mouseput();
		  		if(X<11&&X>42&&Y<16&&Y>26){
		  			break;
				  }
		  		switch(rt){ 
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
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
	printf(" �Σ�\n"); 
	printf("   ����̫�������ǣ����а���ͨ���\n");
	printf("   �кڱ��аף���Ҳ������\n");
	printf("   ���ǵ��о��ž�����иŬ����\n");
	printf("   ���ڳɹ���������������׶��ɺ��׺Ͱ��׹���!\n");
	printf("   * ����/���׵���������ͼ��ʱ��\n");
	printf("     ֻ��ʾ����ͨ�׵�����\n");
	printf("   * ���׺Ͱ���ͬʱ����ͬһ��ͼ��ʱ��\n");
	printf("     ��������׻ᰴ��ĳһ���������\n");
	printf("   * ��ͼ�ϳ���ʱֻ����Ϊ����/����/�ո�������ʽ\n");
	printf("   * ��ͼ���ձ����ʽ����ͼ�еĺ��׺Ͱ��׾���\n"); 
	printf("   ������������ĵ����������˽���ͼת��Ϊ���׵����ܳ���\n");
	printf("   ������Ҫ��ִ����ͼ�еĺ��׷���Ȩ\n");
	printf("   �������ǵĳ���һ�����°�!\n");
	printf("   \n");
	printf("   |������|��������������|��������|��������|\n"); 
	printf("   |      |     ��     |        | ������ |\n");
	printf("   |   A  |--------------|   ��   |        |\n");
	printf("   |      |     ��ͨ     |   ��   |--------|\n");
	printf("   |   I  |--------------|        |        |\n");
	printf("   |      |     ALIce    |--------|  ����  |\n");
	printf("   |  ��  |--------------|        |        |\n");
	printf("   |      |     Noah     |        |--------|\n");
	printf("   |  ��  |--------------|   ��   |        |\n");
	printf("   |      |     Noah's   |   ��   | ��ʼ ��|\n");
	printf("   |      |     Ark      |        |        |\n");
	printf("    ������ �������������� �������� ��������\n");
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
	printf(" ��ӭ��ѧϰ��Ϸ����!             "); 
	gtxy(x,y++);
	printf(" ����ϷΪ�������ǻ۵ı�ƴ��      ");
	gtxy(x,y++);
	printf(" ������Ҳ��֪����ôӮ��          ");
	gtxy(x,y++);
	printf(" ������Ҫ���ǿ������ɣ�          ");
	gtxy(x,y++);
	printf(" ��������淨������            ");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	lx = 16;
	ly = 4;
	int newmap[5][5] = {0};//>0=����  <0=���� 
	int (*p)[5] = NULL;
    p = newmap;
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" ��ͼ��һ��5*5��������ͼ                  ");
	gtxy(x,y++);
	printf(" ��ɫ���׸��ʾ��Щ�׸�������           ");
	gtxy(x,y++);
	printf(" �������ܲ�����ֻ����Щ��ɫ���׸�         ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	//2
	gtxy(18,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),236);
	printf("�~");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" ���ǵ�Ŀ�����þ����ܶ���׸��Ϊ����     ");
	gtxy(x,y++);
	printf(" ���������ǵ����ɫ���׸���һ��         ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("             (���������ָ��λ��)     ��");
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
	printf(" �ղ�������������׸�ת��Ϊ������       ");
	gtxy(x,y++);
	printf(" ���Ҹ��׸����ڵ��к���Ҳ�����Ϊ1����    ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
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
	int newmap[5][5] = {0};//>0=����  <0=���� 
	int (*p)[5] = NULL;
    p = newmap;
    play4_event(p,2,3,-1,5);
    p4_wmap(p,5);
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" ������������׻���ʲô���أ�           ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                          ");
	//1
	gtxy(18,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),236);
	printf("�~");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" ���ǻ��ǵ����ɫ���׸���һ��           ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("             (���������ָ��λ��)     ��");
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
	printf(" Ŷ������                                     ");
	gtxy(x,y++);
	printf(" �к�������ɫ���׸񶼺͸ղ�һ������ɺ�����   ");
	gtxy(x,y++);
	printf(" �����к�����ԭ�еİ��ף��ֱ����ɫ�׸��ˣ�   ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (�������Լ���)     ��");
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
	printf(" ����˼��                                     ");
	gtxy(x,y++);
	printf(" �������㣬�ڰ�1�໥�����ˣ��������ɫ�׸�    ");
	gtxy(x,y++);
	printf(" Ӧ�úܺ����                                 ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (�������Լ���)     ��");
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
	printf(" �����ٽ�����                                 ");
	gtxy(x,y++);
	printf(" һ��������ʣ�µ���ɫ�׸�ȫ����Ϊ���װ�       ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                 (���������ָ��Ҫ��)     ��");
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
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
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
	printf(" OK��                                         ");
	gtxy(x,y++);
	printf(" ����Ǳ���Ϸ�򵥵Ĳ�������                   ");
	gtxy(x,y++);
	printf(" ��ʱ�����ִ���ף���ִ����                   ");
	gtxy(x,y++);
	printf(" �ɱ����̫��Ŷ~                              ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (�������Լ���)     ��");
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
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x \n");	
	printf(" ��                     |                    |                   |\n");
	printf(" ��                     |                    |                   |\n");
	printf(" ��                     |                    |                   |\n");
	printf(" ��                     |                    |                   | \n");
	printf(" ��                     |                    |                   | \n");
	printf(" ��--------------------------------------------------------------| \n");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("ʣ��غ���:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("ʣ��ո���:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf(" BLACK:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),244);
	gtxy(26,4);
	printf(" WHITE:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬��");
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" �������������һ�²������еĸ�����     "); 
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" ���ȣ�ʣ��غ�����                     "); 
	gtxy(x,y++);
	printf(" ����˼�壬ʣ��Ļغ��������ܷż�����   ");
	gtxy(x,y++);
	printf(" ����͵��Թ��еĻغ���                 ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" ʣ��ո�����                           "); 
	gtxy(x,y++);
	printf(" ��ͼ��ʣ����ɫ�׸������               ");
	gtxy(x,y++);
	printf(" ����ͳ�ƺ�ʡ����ȥ����                 ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" ��ע��                                 ");
	gtxy(x,y++);
	printf(" ��ʣ��غ�����ʣ��ո���֮һΪ��ʱ     "); 
	gtxy(x,y++);
	printf(" ��Ϸ������                           ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" BLACK��WHITE��                         "); 
	gtxy(x,y++);
	printf(" ��ͼ�Ϻ��׺Ͱ��׵�����                 ");
	gtxy(x,y++);
	printf(" ��Ҫȷ�����ϵĺ����������ڰ���         ");
	gtxy(x,y++);
	printf(" ֻ����������Ϸ����ʱ����ܻ��ʤ��     ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" ״̬��                                 "); 
	gtxy(x,y++);
	printf(" ��Your Turn   ��Ļغ�                 ");
	gtxy(x,y++);
	printf(" Computing..   ���Լ�����               ");
	gtxy(x,y++);
	printf(" ��Game Over   ��Ϸ����                 ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf("          (�������Լ���)     ��");
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
	printf(" ֮ǰ��Ҳ�Ѿ����Թ���              ");
	gtxy(x,y++);
	printf(" Ӧ���ܹ����֣�                    ");
	gtxy(x,y++);
	printf(" ͬһ�׸�ĺ���/�����������Ե���   "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (�������Լ���)     ��");
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
	printf(" �涨��������Ϊ9                              ");
	gtxy(x,y++);
	printf(" Ϊ������ϷȤζ���ر�أ�                     ");
	gtxy(x,y++);
	printf(" ��ĳ���׸����������10ʱ                     ");
	gtxy(x,y++);
	printf(" ���׸����������0                            ");
	gtxy(x,y++);
	printf(" ��������Χ�Ľ��ϵ��ĸ��׸񽫻����Ӷ�Ӧ����2  ");
	gtxy(x,y++);
	printf(" ����                                         ");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(x,y++);
	printf("                       (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                              ");
	gtxy(8,14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~�~�~");
	gtxy(8,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("10");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	gtxy(8,16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~�~�~");
	gtxy(16,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("��");
	gtxy(20,14);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(" 2");
	gtxy(20,15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~�~�~");
	gtxy(20,16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf(" 2");
	gtxy(8,18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~�~�~");
	gtxy(8,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("10");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	gtxy(8,20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~�~�~");
	gtxy(20,18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	gtxy(20,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~�~�~");
	gtxy(20,20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),234);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf(" 2");
	gtxy(16,19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("��");
	go_on(0,0,0,92,30);
	//3 
	clean();
	lx = 16;
	ly = 4;
	int newmap[5][5] = {{-2,-4,-1,-4,-2},
						{-4, 8, 9, 8,-4},			
						{ 9, 9, 0, 9, 9},			
						{-4, 8, 9, 8,-4},
						{-2,-4,-1,-4,-2}};//>0=����  <0=���� 
	int (*p)[5] = NULL;
    p = newmap;
    p4_wmap(p,5);
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                          ");
	gtxy(x,y++);
	printf(" ������Ͼ�����ͼһ��                     ");
	gtxy(x,y++);
	printf(" �㿪�м��Ǹ���ɫ�׸�ɣ�                 ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
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
	printf(" ���˹���̳̾���ȫ������                 ");
	gtxy(x,y++);
	printf(" �Ͻ�ȥ����ĵ���һ��ʤ���ɣ�             ");
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
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
			printf("��");
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
		printf("��");
	}
	else{
		gtxy(29,17);
		printf("��");
		gtxy(29,23);
		printf("  ");
	}
}
int play4(int lv,int ord){//ord<0����|1����>
	clean();
	play4_frame();
	p_lev(lv);	
	lx = 18;
	ly = 9;
	c_blank = 25;//�ո�
	mr[0] = 0;//����
	mr[1] = 0;//����
	c_mine = 50;//���� 	
	//int situ[3] = {c_blank,0,0};//0-�ո� 1-���� 2-���� 
	int newmap[5][5] = {0};//>0=����  <0=���� 
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
	    ReadConsoleInput(hInput,&inRec,1,&numRead);//��ȡ1�������¼� 
		switch(inRec.EventType)
		{ 
			case MOUSE_EVENT:
		  	{
				rmt = mouseput();
				
		  		switch(rmt){ 
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
          					if(Y>25&&Y<28){
          						if(X>67&&X<78){
          							return MessageBox(NULL,"���ף�","perfect",MB_OK);
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
		printf("�~");
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
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |-----------------------��\n");
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
	printf("ʣ��غ���:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("ʣ��ո���:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf(" BLACK:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),244);
	gtxy(26,4);
	printf(" WHITE:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,26);
	printf("|����������|"); 
	gtxy(67,27);
	printf("|   ���   |");
	gtxy(67,28);
	printf(" ���������� "); 
}
int d_end(int v,int r){
	if(r==0){
		switch(v){
			case 1:
				return MessageBox(NULL,"ƽ���˚G","AI-E250",MB_YESNO);
			case 2:
				return MessageBox(NULL,"�ҵ���·״̬�ܺá�\n�Ҳ����ٷ���ͬ���Ĵ���\n�ҽ������������","AI-3000A",MB_YESNO);
			case 3:
				return MessageBox(NULL,"��֣��������Ĳ������ˣ�","ALIce",MB_YESNO);
			case 4:
				return MessageBox(NULL,"��\n�߹�ʺ�˵�����","Noah",MB_YESNO);
			case 5:
				return MessageBox(NULL,"�㣬�ܲ���","7000X",MB_YESNO);
		}
	}
	else if(r>0){
		switch(v){
			case 1:
				return MessageBox(NULL,"��\n��Ӯ��\n��ϲ�ɺؿ�ϲ�ɺ�","AI-E250",MB_YESNO);
			case 2:
				return MessageBox(NULL,"��ȥ����ֻ֪�������������\nȴ����������ġ�\n���죬��Ҫ������һ�С�","AI-3000A",MB_YESNO);
			case 3:
				return MessageBox(NULL,"ʧ���ˣ�\n��������Ҫ���������У�","ALIce",MB_YESNO);
			case 4:
				return MessageBox(NULL,"�����\n��������\n��һ�֣��ҿɲ�������������","Noah",MB_YESNO);
			case 5:
				return MessageBox(NULL,"shutdown -r now","7000X",MB_YESNO);
		}
	}
	else if(r<0){
		switch(v){
			case 1:
				return MessageBox(NULL,"����ô����","AI-E250",MB_YESNO);
			case 2:
				return MessageBox(NULL,"������������,\n�����������������,\n�ɣ�ʲô�Ǹ��飿","AI-3000A",MB_YESNO);
			case 3:
				return MessageBox(NULL,"�˳���","ALIce",MB_YESNO);
			case 4:
				return MessageBox(NULL,"��ƾ�㣬Ҳ����Ӯ�ң�","Noah",MB_YESNO);
			case 5:
				return MessageBox(NULL,"Ŀ����\nһ������","7000X",MB_YESNO);
		}
	}
}
int AI_Simple(int (*p)[5],int Nc){//Ԥ�ⵥ�����ȡ� 
	srand(time(NULL));
	if(c_blank==25){
		return rand()%25;
	}
	int cache[25] = {0};//��¼�ո�λ�� 
	int comput_result[25] = {0};//��¼������������ []=cache�±� 
	
	AI_get_situ(p,cache,Nc);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
	int (*q)[5] = NULL;
    q = calcu_mod;
	    
    int i,j=-1,k=0;//iѭ�� j������� k��С��� 
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
int AI_Normal(int (*p)[5],int Nc){//���ȡ��
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
int AI_ALIce(int (*p)[5],int Nc){//Ԥ�ⵥ�����ȡ���� 
	srand(time(NULL));
	if(c_blank==25){
		return rand()%25;
	}
	int cache[25] = {0};//��¼�ո�λ�� 
	int comput_result[25] = {0};//��¼�����������Ž�� []=cache�±� 	
	AI_get_situ(p,cache,Nc);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
	int (*q)[5] = NULL;
    q = calcu_mod;    
    int i,j=-1,k=0;//iѭ�� j������� k��С��� 
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
	int cache[25] = {0};//��¼�ո�λ��
	AI_get_situ(p,cache,Nc);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����
	if(buffer==1){
		return cache[0];
	}
	if(c_mine==1){		 
		int comput_result[25] = {0};//��¼�����������Ž�� []=cache�±� 
		int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
		int (*q)[5] = NULL;
    	q = calcu_mod; 
    	int i,j=-1,k=0;//iѭ�� j������� k��С���
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
		int comput_result[3][25] = {0,0,0};//[0][]P [1][]ʤ [2][]��
		int calcu_mod[5][5] = {0};//��ǰ��ͼ(������ʼ״̬)
		int (*q)[5] = NULL;
  		q = calcu_mod;
 	 	int i,j=-1;//iѭ�� j���鶨λ 
  	 	for(i=0;i<buffer;i++){
    		memcpy(q,p,25*sizeof(int));
    		//i=cache[i]/5 j=cache[i]%5
   		 	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    			calcu_situ(q,5);
    			if(c_blank==0&&mr[0]<mr[1]){//��ʤ
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
	
	int comput_result[25] = {0};//��¼�����������Ž�� []=cache�±� 	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(������ʼ״̬)
	int (*q)[5] = NULL;
    q = calcu_mod;   
    int i,j=-1,k=0;//iѭ�� j������� k��С��� 
    for(i=0;i<buffer;i++){
    	memcpy(q,p,25*sizeof(int));
    	//i=cache[i]/5 j=cache[i]%5
    	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    		calcu_situ(q,5);
    		if(c_blank==0&&mr[0]<mr[1]){//��ʤ
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
	int cache[25] = {0};//��¼�ո�λ��	
	AI_get_situ(p,cache,Nc);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
	int (*q)[5] = NULL;
    q = calcu_mod;   
    int i,w=0,l=0;//iѭ�� wʤ������ lʧ�ܾ��� 
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
				buffer = AI_Simple(p,5);//�� 
				break;
			case 2:
				buffer = AI_Normal(p,5);//��ͨ 
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
void AI_MinefieldCyberBrain_Kernel(int (*p)[5],int pn,unsigned long long *wi,unsigned long long *lo,unsigned long long *dr){//ȫö���ں� n(MAX)=25**50 
	int cache[25] = {0};//��¼�ո�λ��	
	AI_get_situ(p,cache,5);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
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
	int cache[25] = {0};//��¼�ո�λ��
	AI_get_situ(p,cache,Nc);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����
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
		int comput_result[25] = {0};//��¼�����������Ž�� []=cache�±� 
		int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
		int (*q)[5] = NULL;
    	q = calcu_mod;
    
    	int i,j=-1,k=0;//iѭ�� j������� k��С���
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
	int comput_probability[25] = {0};//��¼ʤ��
	int comput_result[25] = {0};//��¼���Ž�� []=cache�±� 	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(������ʼ״̬)
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
    int i;//iѭ��
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
