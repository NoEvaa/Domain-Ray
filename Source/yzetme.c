#include "yzetme.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];
extern int AIstep;

void entertainment5(){
	e_5();
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //�����豸��� 
	int rt,st;
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
							if(Y>10&&Y<13){
								if(X>3&&X<12){
          							return;
								  }
								else if(X>18&&X<27){
									e5_course();
									e_5();
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
		if(play5()){
			return;
		}
	}	
}
void e_5(){
	clean();
	gtxy(0,1); 		
	printf(" �Σ�\n"); 
	printf("   ʱ����ȣ����Σ��\n");
	printf("   ��Ҫ���ǣ�����ţƤ\n");
	printf("   ��������������\n");
	printf("   ը����ͻȻ�����Ƿ���Ϯ��\n");
	printf("   ��������ȫ��ʧ�ݱ�������\n");
	printf("   ����Ӣ�۳�������\n");
	printf("   ��������ˮ�����֮��\n"); 
	printf("   \n\n");
	printf("   |��������|     |��������|      |��������|\n"); 
	printf("   | ������ |     |  �̳�  |      | ��ʼ ��|\n");
	printf("    ��������       ��������        �������� \n"); 
}
void e5_course(){
	for(;;){
		switch(e5_rule_choice()){
			case 0:
				return;
			case 1:
				e5_operation();
				break;
			case 2:
				e5_rule();
				break;
			case 3:
				e5_skill();
				break;
		}
	}
}
int e5_rule_choice(){
	clean();
	gtxy(0,1); 
	printf("  |��������|\n"); 
	printf("  | ������ |\n"); 
	printf("   ��������       \n"); 
	printf("    �x�x�x�x�x�x�x�x�x  \n");	
	printf("  ��                  ��\n");
	printf("  ��  �� ��������     ��\n");
	printf("  ��------------------��\n");
	printf("  ��                  ��\n");
	printf("  ��  �� ������     ��\n");	
	printf("  ��------------------��\n");
	printf("  ��                  ��\n");
	printf("  ��  �� ������ʾ     ��\n");
	printf("  ��                  ��\n");
	printf("    ������������������  ");
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);//����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);//�����豸��� 
	int rt;
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
          					if(X>2&&X<11&&Y>0&&Y<3){
          						return 0;//���� 
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
void e5_operation(){
	clean();
	lx = 33;
	ly = 11;
	int newmap[9][18] = {0};//0=��ռ�� 1=���� 2=ռ�� -1=���׵� 
	int (*p)[18] = NULL;
    p = newmap;	
	play5_frame();
	c_mine = 1;
	c_blank = 0;//����
	int skcd[5] = {8,-1,-1,-1,-1};//����cd
	int skcost[5] = {50,-1,-1,-1,-1};//��������
	int c_delta = 10;//��������
	p_c_choice(c_mine);
	p_c_n();
	p_skills(skcd,skcost);
	e5_o1();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	clean();
	lx = 28;
	ly = 11;
	c_blank = 9999;
	e5_o2();
	p_c_choice(c_mine);
	p_c_n();
	mr[0] = 0;
	mr[1] = 0;
	p_c_re();
	p_ob_map(p);
	e5_o3();
	p5_event(p,2,2);
	e5_o4();
}
void e5_o1(){
	int y = 11;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf(" ��ӭ�������ֽ̳�                     ");
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf("              (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                      ");
	go_on(0,0,0,92,30);
	y = 11;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf(" �Ϸ�Ϊ������                         ");
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf("              (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                      ");
	go_on(0,0,0,92,30);
	y = 11;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf(" �Ҳ�Ϊ������                         ");
	gtxy(28,y++);
	printf(" ���Ե��ʹ�ü���                     ");
	gtxy(28,y++);
	printf(" ��ע�⼼����������ȴʱ��             ");
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf("              (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                      ");
	go_on(0,0,0,92,30);
	y = 11;
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf(" ͨ�������������ѡ��������͵���   ");
	gtxy(28,y++);
	printf(" ÿ���׶�������һ������               ");
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf("              (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                      ");
	go_on(0,0,0,92,30);
	y = 11;
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf(" ��ǰ100���غ���                      ");
	gtxy(28,y++);
	printf(" ��ÿ�غ϶�����10������             ");
	gtxy(28,y++);
	printf(" ���������ú����ܲ������ɻ�ʤ       ");
	gtxy(28,y++);
	printf("                                      ");
	gtxy(28,y++);
	printf("              (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                      ");
	go_on(0,0,0,92,30);
}
void e5_o2(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��---------------------|                    |                   |                       ��\n");
	printf(" ��          |          |                    |                   |                       ��\n");
	printf(" ��          |          |                    |                   |                       ��\n");
	printf(" ��          |          |----------------------------------------|-----------------------��\n");
	printf(" ��          |          |                                        |      ��һ�غ� ��     |��\n");
	printf(" ��---------------------|                                        |      >>>>>>>>>>      |��\n");
	printf(" ��                     |                                         ���������������������� ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��---------------------|                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��---------------------|                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf("   ��������������������������������������������������������������������������������������  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("����C:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("�ҷ�:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("�з�:");	
	gtxy(67,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");  
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("�̳�");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("��ǰ�غ�:");
}
void e5_o3(){
	int y = 10;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  λ���м�ľ���      ");
	gtxy(66,y++);
	printf(" ��Ҫ���������ͼ��   ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  ����9*18����ͼ��    ");
	gtxy(66,y++);
	printf(" ��ֻ�ɵ�����д���   ");
	gtxy(66,y++);
	printf(" ���׵�İ�ɫ�׸�     ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  �����ܳ���������  ");
	gtxy(66,y++);
	printf(" �����ɫ�׸�         ");
	gtxy(66,y++);
	printf("  ���ɽ�����ѡ����    ");
	gtxy(66,y++);
	printf(" ��������ͼ��         ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("   (�������ɫ�׸�) ");
	gtxy(66,y++);
	printf("               ��     ");
	gtxy(lx+4,ly+2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
	printf("�~");
	go_on(0,lx+4,ly+2,1,0);
	gtxy(lx+4,ly+2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void e5_o4(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	int y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  ��ѡ�ױ���������ͼ  ");
	gtxy(66,y++);
	printf("  ��ɫ�׸񼴱�ʾ      ");
	gtxy(66,y++);
	printf(" ��λ���ѱ�����       ");
	gtxy(66,y++);
	printf(" ��Ϊ�ҷ�             ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  ��ɫ�׸����ʾ      ");
	gtxy(66,y++);
	printf(" ��λ��Ŀǰ��������   ");
	gtxy(66,y++);
	printf("  ���к�ɫ�׸��ʾ    ");
	gtxy(66,y++);
	printf(" ��λ���ѱ�����       ");
	gtxy(66,y++);
	printf(" ��Ϊ�з�             ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  �ڵ�һ���غ���      ");
	gtxy(66,y++);
	printf(" ը���˻����ѡȡ     ");
	gtxy(66,y++);
	printf(" 10��λ�ý�������     ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  �˺�ÿ���غ�        ");
	gtxy(66,y++);
	printf(" ը���˶������ѡȡ   ");
	gtxy(66,y++);
	printf(" 1�����׵�            ");
	gtxy(66,y++);
	printf(" ������Χ8���ض�λ��  ");
	gtxy(66,y++);
	printf(" ��������             ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  ��ը�������ֵ��׸�  ");
	gtxy(66,y++);
	printf(" �д��ڵ���ʱ         ");
	gtxy(66,y++);
	printf("  ���ױ�ᱻ����      ");
	gtxy(66,y++);
	printf(" ���׸���������   ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  ��֮�����㽫����    ");
	gtxy(66,y++);
	printf(" �����ڱ����ֵ��׸�ʱ ");
	gtxy(66,y++);
	printf("  ���׻���ը����      ");
	gtxy(66,y++);
	printf(" ͬ���ھ�             ");
	gtxy(66,y++);
	printf(" ���׸�Ҳ��������   ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  �򵥵�˵            ");
	gtxy(66,y++);
	printf("  ����Ҫͨ���κβ���  ");
	gtxy(66,y++);
	printf(" ʹ������ͼ��   ");
	gtxy(66,y++);
	printf(" ��ɫ�׸񾡿��ܶ�     ");
	gtxy(66,y++);
	printf(" ��ɫ�׸񾡿�����     ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Լ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	y = 10;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),252);
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("  Now,                ");
	gtxy(66,y++);
	printf("  it's your turn.     ");
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("                      ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(66,y++);
	printf("                      ");
	gtxy(66,y++);
	printf("    (�������Խ���)  ");
	gtxy(66,y++);
	printf("               ��     ");
	go_on(0,0,0,92,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void e5_rule(){
	clean();
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��---------------------|                    |                   |                       ��\n");
	printf(" ��          |          |                    |                   |                       ��\n");
	printf(" ��          |          |                    |                   |                       ��\n");
	printf(" ��          |          |----------------------------------------|-----------------------��\n");
	printf(" ��          |          |                                        |      ��һ�غ� ��     |��\n");
	printf(" ��---------------------|                                        |      >>>>>>>>>>      |��\n");
	printf(" ��                     |                                         ���������������������� ��\n");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("����C:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("�ҷ�:");
	gtxy(31,4);
	printf("90");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("�з�:");
	gtxy(52,4);
	printf("50");
	gtxy(67,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");  
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("��ǰ�غ�:"); 	
	gtxy(15,12);
	printf("���з��������ڵ���50ʱʧ��");
	gtxy(15,14);
	printf("���ҷ��������ڵ���90ʱ��ʤ");
	go_on(0,0,0,92,30);
}
void e5_skill(){
	e5_skill_board();	
	int skill = 1;
	p_e5_skillc(skill);	
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
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
							if(X>2&&X<17){
								if(Y==3||Y==4){
									skill = 1;
									p_e5_skillc(skill);
								}
								else if(Y==6||Y==7){
									skill = 2;
									p_e5_skillc(skill);
								}
								else if(Y==9||Y==10){
									skill = 3;
									p_e5_skillc(skill);
								}
								else if(Y==12||Y==13){
									skill = 4;
									p_e5_skillc(skill);
								}
								else if(Y==15||Y==16||Y==17){
									skill = 5;
									p_e5_skillc(skill);
								}
								break;
							}
							if(Y>2&&Y<5){
								if(X>45&&X<65){
									return;
								}
								else if(X>23&&X<44){
									p_e5_skillc_demo(skill);
									e5_skill_board();
									p_e5_skillc(skill);
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void e5_skill_board(){
	clean();
	gtxy(0,1); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("�������飺\n"); 
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��              |||||||                    ||                   ��\n");
	printf(" ��              |+++++|       ��ʾ         ||       �˳�        ��\n");
	printf(" ��--------------|-----------------------------------------------��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��--------------|                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��--------------|                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��--------------|                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf("   �������������������������������������������������������������� \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_e5_skillc(int s){// 
	if(s==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,4);
	printf("���ʽ��");
	if(s==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,7);
	printf("��������");
	if(s==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,10);
	printf("�������и�");
	if(s==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,13);
	printf("�󣿣���");
	if(s==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,16);
	printf("�󣿣���");
	p_e5_skillc_detail(s);
}
void p_e5_skillc_detail(int s){//
	p_e5_skillc_clean();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(23,8);
	printf("C: ");
	gtxy(23,9);
	printf("cd:");
	gtxy(23,10);
	printf("����������");
	switch(s){
		case 1:
			gtxy(26,6);
			printf("<���ʽ��>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf(" 50 / +5/ 200");
			gtxy(26,9);
			printf("  8 / - /  12");
			gtxy(27,11);
			printf("����������ͼ��");
			break;
		case 2:
			gtxy(26,6);
			printf("<��������>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf(" 70 /+10/ 200");
			gtxy(26,9);
			printf("  8 / - /  8");
			gtxy(27,11);
			printf("�����л᲻������һ�������أ�");
			gtxy(27,12);
			printf("�����ͼ�������ѷ��õĵ���");
			gtxy(27,13);
			printf("���������з������ĵ���������λ��");
			break;
		case 3:
			gtxy(26,6);
			printf("<�������и�>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf(" 10 / +1/  20");
			gtxy(26,9);
			printf(" 10 / +1/  20");
			gtxy(27,11);
			printf("���з�����ƶ�����ͼ�Ҳ��׸�");
			gtxy(27,12);
			printf("���ҷ������ƶ�����ͼ����׸�");
			break;
		case 4:
		case 5:
			gtxy(26,6);
			printf("<�󣿣���>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("  - / - /  - ");
			gtxy(26,9);
			printf("  - / - /  - ");
			gtxy(27,11);
			printf("#######################");
			break;
	} 
}
void p_e5_skillc_clean(){
	int y = 6;
	for(;y<18;y++){
		gtxy(20,y);
		printf("                                            ");
	}	
}
void p_e5_skillc_demo(int s){//
	switch(s){
		case 1:
			p_e5_skill1_demo();
			break;
		case 2:
			p_e5_skill2_demo(); 
			break;
		case 3:
			p_e5_skill3_demo();
			break;
		case 4:
			break;
		case 5:
			break;
	}
}
void p_e5_skill1_demo(){
	clean();
	lx = 33;
	ly = 11;
	int newmap[9][18] = {0};//0=��ռ�� 1=���� 2=ռ�� -1=���׵� 
	int (*p)[18] = NULL;
    p = newmap;
    c_mine = 1;
	c_blank = 50;//����
	int skcd[5] = {0,-1,-1,-1,-1};//����cd
	int skcost[5] = {50,-1,-1,-1,-1};//��������
	
	play5_frame();
	p_ob_map(p);
	p_c_n();
	gtxy(77,2);
	printf("   T");
	p_e5_skill1_boardset(p);
	p5_counting(p);
	p_c_re();
	p_skills(skcd,skcost);
	
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
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
          					if(X>65&&Y>6&&X<88&&Y<9){
								return;
							}
							if(X>73&&X<89&&Y>12&&Y<27){
								if(Y==13||Y==14){//skill1
									if(skcd[0]!=0){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("cd��..  ");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									c_blank -= skcost[0];
									if(skcost[0]<200){
										skcost[0] += 5;
									}
									skcd[0] = 12;
									p_c_n();
									p_skills(skcd,skcost);
									p5_skill1(p);
									break; 
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
void p_e5_skill1_boardset(int (*p)[18]){
	int count = 49;
	srand(time(NULL));
	while(count){
		int x = rand()%9;
		int y = rand()%18;
		if((*(*(p+x)+y))!=-1&&(*(*(p+x)+y))!=0){
			(*(*(p+x)+y))--;
			count--;
		}
	}
	count = 10;
	while(count){
		int x = rand()%9;
		int y = rand()%18;
		if((*(*(p+x)+y))==1){
			(*(*(p+x)+y))++;
			count--;
		}
	}
	p_p5_event(p);
}
void p_e5_skill2_demo(){
	clean();
	lx = 33;
	ly = 11;
	int newmap[9][18] = {0};//0=��ռ�� 1=���� 2=ռ�� -1=���׵� 
	int (*p)[18] = NULL;
    p = newmap;
    c_mine = 1;
	c_blank = 70;//����
	int skcd[5] = {-1,0,-1,-1,-1};//����cd
	int skcost[5] = {-1,70,-1,-1,-1};//��������
	
	play5_frame();
	p_ob_map(p);
	p_c_n();
	gtxy(77,2);
	printf("   T");
	p_e5_skill1_boardset(p);
	p5_counting(p);
	p_c_re();
	p_skills(skcd,skcost);
	
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
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
          					if(X>65&&Y>6&&X<88&&Y<9){
								return;
							}
							if(X>73&&X<89&&Y>12&&Y<27){
								if(Y==16||Y==17){//skill2
									if(skcd[1]!=0){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("cd��..  ");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									c_blank -= skcost[1];
									if(skcost[1]<200){
										skcost[1] += 10;
									}
									skcd[1] = 8;
									p_c_n();
									p_skills(skcd,skcost);
									p5_skill2(p);
									break; 
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
void p_e5_skill3_demo(){
	clean();	
	lx = 33;
	ly = 11;
	int newmap[9][18] = {0};//0=��ռ�� 1=���� 2=ռ�� -1=���׵� 
	int (*p)[18] = NULL;
    p = newmap;
    c_mine = 1;
	c_blank = 10;//����
	int skcd[5] = {-1,-1,0,-1,-1};//����cd
	int skcost[5] = {-1,-1,10,-1,-1};//��������
	
	play5_frame();
	p_ob_map(p);
	p_c_n();
	gtxy(77,2);
	printf("   T");
	p_e5_skill1_boardset(p);
	p5_counting(p);
	p_c_re();
	p_skills(skcd,skcost);
	
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
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
          					if(X>65&&Y>6&&X<88&&Y<9){
								return;
							}
							if(X>73&&X<89&&Y>12&&Y<27){
								if(Y==19||Y==20){//skill3
									if(skcd[2]!=0){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("cd��..  ");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									c_blank -= skcost[2];
									if(skcost[2]<20){
										skcost[2] += 1;
									}
									if(skcd[2]<20){
										skcd[2] += 1;
									}
									p_c_n();
									p_skills(skcd,skcost);
									p5_skill3(p);
									break; 
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
int play5(){
	clean();
	lx = 33;
	ly = 11;
	int newmap[9][18] = {0};//0=��ռ�� 1=���� 2=ռ�� -1=���׵� 
	int (*p)[18] = NULL;
    p = newmap;
	c_mine = 1;//���� 
	c_blank = 0;//����
	int tub = 0;//�غ�
	int skcd[5] = {8,8,12,-1,-1};//����cd
	int skcost[5] = {50,70,10,-1,-1};//��������
	int c_delta = 10;//�������� 
	
	play5_frame();
	p_ob_map(p);	
	p_c_choice(c_mine);
	p_c_n();
	p_tub(tub);
	p5_counting(p);
	p_c_re();
	p_skills(skcd,skcost);
	
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
		  			case 1: //�Ҽ�
		   					break;
          			case 2: //���
          					if(Y==25||Y==26){
          						if(X>60&&X<71){
          							return MessageBox(NULL,"���˳ɹ�","good luck",MB_OK);
								}
							}
          					if(X>2&&X<24){
          						if(Y>3&&Y<8){
          							if(X>2&&X<13){
          								c_mine = 1;
										p_c_choice(c_mine);
									  }
									  else if(X>13&&X<24){
									  	c_mine = 2;
										p_c_choice(c_mine);
									  }
								  }
								else if(Y>8&&Y<14){
									c_mine = 3;
									p_c_choice(c_mine);
								}
								else if(Y>14&&Y<20){
									c_mine = 4;
									p_c_choice(c_mine);
								}
								else if(Y>20&&Y<27){
									c_mine = 5;
									p_c_choice(c_mine);
								}
								break;
							  }
							if(X>=lx&&Y>=ly&&X<lx+36&&Y<ly+9){
								if(p5_check_c()){
									p5_event(p,(X-lx)/2,Y-ly);
									gtxy(75,4);
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
									printf("����    ");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
									break;
								}
								else{
									gtxy(75,4);
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
									printf("���ܲ���");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
								}
								break;
							}
							if(X>65&&Y>6&&X<88&&Y<9){
								if(tub==0){
									tub++;
									c_blank+=c_delta;
									p_c_n();
									p_tub(tub);
									p5_skillscdd(skcd,skcost);
									first_tub(p);
									break;
								}
								tub++;
								c_blank+=c_delta;
								p_c_n();
								p_tub(tub);
								p5_skillscdd(skcd,skcost);
								switch_tub(p);
								if(tub==100){
									c_delta = 20;
								}
								break;
							}
							if(X>73&&X<89&&Y>12&&Y<27){
								if(Y==13||Y==14){//skill1
									if(skcd[0]!=0){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("cd��..  ");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									if(c_blank<skcost[0]){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("���ܲ���");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									c_blank -= skcost[0];
									if(skcost[0]<200){
										skcost[0] += 5;
									}
									skcd[0] = 12;
									p_c_n();
									p_skills(skcd,skcost);
									p5_skill1(p);
									break; 
								}
								else if(Y==16||Y==17){//skill2
									if(skcd[1]!=0){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("cd��..  ");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									if(c_blank<skcost[1]){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("���ܲ���");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									c_blank -= skcost[1];
									if(skcost[1]<200){
										skcost[1] += 10;
									}
									skcd[1] = 8;
									p_c_n();
									p_skills(skcd,skcost);
									p5_skill2(p);
									break; 
								}
								else if(Y==19||Y==20){//skill3
									if(skcd[2]!=0){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("cd��..  ");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									if(c_blank<skcost[2]){
										gtxy(75,4);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
										printf("���ܲ���");
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
										break;
									}
									c_blank -= skcost[2];
									if(skcost[2]<20){
										skcost[2] += 1;
									}
									if(skcd[2]<20){
										skcd[2] += 1;
									}
									p_c_n();
									p_skills(skcd,skcost);
									p5_skill3(p);
									break; 
								}
								else if(Y==22||Y==23){//skill4
									
								}
								else if(Y==25||Y==26){//skill5
									
								}
								break;
							}
		   					break;
		  		}
			} 		 
		 	break; 
		}
		if(mr[0]>=50){
			return p5_result_d(tub);
		}
		if(mr[1]>=90){
			return p5_result_v(tub);
		}
	}
	return 0;
}
void play5_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��---------------------|                    |                   |                       ��\n");
	printf(" ��          |          |                    |                   |                       ��\n");
	printf(" ��          |          |                    |                   |                       ��\n");
	printf(" ��          |          |----------------------------------------|-----------------------��\n");
	printf(" ��          |          |                                        |      ��һ�غ� ��     |��\n");
	printf(" ��---------------------|                                        |      >>>>>>>>>>      |��\n");
	printf(" ��                     |                                         ���������������������� ��\n");
	printf(" ��                     |                                                |��������������|��\n");
	printf(" ��                     |                                                |  ��SKILLs    |��\n");
	printf(" ��                     |                                                |xxxxxxxxxxxxxx|��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��---------------------|                                                |               ��\n");
	printf(" ��                     |                                                |---------------��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |---------------��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��---------------------|                                                |               ��\n");
	printf(" ��                     |                                                |---------------��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                    �x�x�x�x�x  |---------------��\n");
	printf(" ��                     |                                   |          | |               ��\n");
	printf(" ��                     |                                   | ս������ | |               ��\n");
	printf("   ��������������������������������������������������������������������������������������  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("����C:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("�ҷ�:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("�з�:");	
	gtxy(67,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");  
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("��ǰ�غ�:");
}
void p_ob_map(int (*p)[18]){
	int i,j,k;
	gtxy(lx-2,ly-1);
	printf("��-------------------------------------��");
	for(i=0;i<9;i++){
		gtxy(lx-2,ly+i);
		printf(" |                                    |");
	}
	gtxy(lx-2,ly+9);
	printf("�t-------------------------------------�s");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),96);
	for(i=0;i<9;i++){
		gtxy(lx,ly+i);
		for(j=0;j<18;j++){
			(*(*(p+i)+j)) = 1;
			printf("�~");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
	j = 2;
	k = 7;
	for(i=0;i<18;i++){
		j=(j+2)%10;
		if(j!=0){
			(*(*(p+j-1)+i)) = -1;
			gtxy(lx+i*2,ly+j-1);
			printf("�~");
		}
		k=(k+2)%10;
		if(k!=0){
			(*(*(p+k-1)+i)) = -1;
			gtxy(lx+i*2,ly+k-1);
			printf("�~");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_c_choice(int v){
	if(v==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	int y = 4;
	gtxy(5,y++);
	printf("  �~");
	gtxy(5,y++);
	printf("�~");
	printf("�~");
	printf("�~");
	gtxy(5,y++);
	printf("  �~");
	gtxy(5,y++);
	printf("  C6  ");
	if(v==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	y = 4;
	gtxy(16,y++);
	printf("�~�~�~");
	gtxy(16,y++);
	printf("�~");
	printf("�~");
	printf("�~");
	gtxy(16,y++);
	printf("�~�~�~");
	gtxy(16,y++);
	printf("  C8  ");
	if(v==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	y = 9;
	gtxy(5,y++);
	printf("    �~");
	gtxy(5,y++);
	printf("    �~");
	gtxy(5,y++);
	printf("�~�~");
	printf("�~");
	printf("�~�~   C9");
	gtxy(5,y++);
	printf("    �~");
	gtxy(5,y++);
	printf("    �~");
	if(v==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	y = 15;
	gtxy(5,y++);
	printf("�~      �~");
	gtxy(5,y++);
	printf("  �~  �~");
	gtxy(5,y++);
	printf("    �~");
	printf("       C8");
	gtxy(5,y++);
	printf("  �~  �~");
	gtxy(5,y++);
	printf("�~      �~");
	if(v==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	y = 21;
	gtxy(5,y++);
	printf("  �~  �~");
	gtxy(5,y++);
	printf("�~�~  �~�~");
	gtxy(5,y++);
	printf("    �~");
	printf("       C7");
	gtxy(5,y++);
	printf("�~�~  �~�~");
	gtxy(5,y++);
	printf("  �~  �~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_c_n(){
	gtxy(12,2);
	printf("%4d",c_blank);
}
void p_tub(int tu){
	gtxy(77,2);
	printf("%4d",tu);
}
void p_skills(int sk[5],int skco[5]){//
	if(sk[0]==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else if(sk[0]==-1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(76,13);
	printf("���ʽ��");
	gtxy(76,14);
	printf("C%3d  cd%2d",skco[0],sk[0]);
	if(sk[1]==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else if(sk[1]==-1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(76,16);
	printf("��������");
	gtxy(76,17);
	printf("C%3d  cd%2d",skco[1],sk[1]);
	if(sk[2]==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else if(sk[2]==-1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(76,19);
	printf("�������и�");
	gtxy(76,20);
	printf("C%3d  cd%2d",skco[2],sk[2]);
	if(sk[3]==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else if(sk[3]==-1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(76,22);
	printf("�󣿣���");
	gtxy(76,23);
	printf("C???  cd??");
	if(sk[4]==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else if(sk[4]==-1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(76,25);
	printf("�󣿣���");
	gtxy(76,26);
	printf("C???  cd??");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int p5_check_c(){
	switch(c_mine){
		case 1:{
			if(c_blank<6){
				return 0;
			}
			return 1;
		}
		case 2:{
			if(c_blank<8){
				return 0;
			}
			return 1;
		}
		case 3:{
			if(c_blank<9){
				return 0;
			}
			return 1;
		}
		case 4:{
			if(c_blank<8){
				return 0;
			}
			return 1;
		}
		case 5:{
			if(c_blank<7){
				return 0;
			}
			return 1;
		}
	}
	return 0;
}
void p5_event(int (*p)[18],int x,int y){ 
	if((*(*(p+y)+x))!=-1){
		return;
	} 
	switch(c_mine){
		case 1:
			p5_event_c1(p,x,y);
			c_blank-=6;
			p_c_n();
			break;
		case 2:
			p5_event_c2(p,x,y);
			c_blank-=8;
			p_c_n();
			break;
		case 3:
			p5_event_c3(p,x,y);
			c_blank-=9;
			p_c_n();
			break;
		case 4:
			p5_event_c4(p,x,y);
			c_blank-=8;
			p_c_n();
			break;
		case 5:
			p5_event_c5(p,x,y);
			c_blank-=7;
			p_c_n();
			break;
	}
	p_p5_event(p);
	p5_counting(p);
	p_c_re();
}
void p5_event1(int (*p)[18],int x,int y){
	if((*(*(p+y)+x))==-1){
		return;
	}
	if((*(*(p+y)+x))==2){
		return;
	}
	(*(*(p+y)+x))++;
}
void p5_event_c1(int (*p)[18],int x,int y){
	if(y>0){
		p5_event1(p,x,y-1);
	}
	if(y<8){
		p5_event1(p,x,y+1);
	}
	if(x>0){
		p5_event1(p,x-1,y);
	}
	if(x<17){
		p5_event1(p,x+1,y);
	}
}
void p5_event_c2(int (*p)[18],int x,int y){
	if(y>0){
		p5_event1(p,x,y-1);
		if(x>0){
			p5_event1(p,x-1,y-1);
		}
		if(x<17){
			p5_event1(p,x+1,y-1);
		}
	}
	if(y<8){
		p5_event1(p,x,y+1);
		if(x>0){
			p5_event1(p,x-1,y+1);
		}
		if(x<17){
			p5_event1(p,x+1,y+1);
		}
	}
	if(x>0){
		p5_event1(p,x-1,y);
	}
	if(x<17){
		p5_event1(p,x+1,y);
	}
}
void p5_event_c3(int (*p)[18],int x,int y){
	if(y>0){
		p5_event1(p,x,y-1);
	}
	if(y<8){
		p5_event1(p,x,y+1);
	}
	if(x>0){
		p5_event1(p,x-1,y);
	}
	if(x<17){
		p5_event1(p,x+1,y);
	}
	if(y>1){
		p5_event1(p,x,y-2);
	}
	if(y<7){
		p5_event1(p,x,y+2);
	}
	if(x>1){
		p5_event1(p,x-2,y);
	}
	if(x<16){
		p5_event1(p,x+2,y);
	}
}
void p5_event_c4(int (*p)[18],int x,int y){
	if(y>0&&x>0){
		p5_event1(p,x-1,y-1);
	}
	if(y>0&&x<17){
		p5_event1(p,x+1,y-1);
	}
	if(y<8&&x>0){
		p5_event1(p,x-1,y+1);
	}
	if(y<8&&x<17){
		p5_event1(p,x+1,y+1);
	}
	if(y>1&&x>1){
		p5_event1(p,x-2,y-2);
	}
	if(y>1&&x<16){
		p5_event1(p,x+2,y-2);
	}
	if(y<7&&x>1){
		p5_event1(p,x-2,y+2);
	}
	if(y<7&&x<16){
		p5_event1(p,x+2,y+2);
	}
}
void p5_event_c5(int (*p)[18],int x,int y){
	if(y>0&&x>0){
		p5_event1(p,x-1,y-1);
		if(x>1){
			p5_event1(p,x-2,y-1);
		}
	}
	if(y>0&&x<17){
		p5_event1(p,x+1,y-1);
		if(y>1){
			p5_event1(p,x+1,y-2);
		}
	}
	if(y<8&&x>0){
		p5_event1(p,x-1,y+1);
		if(y<7){
			p5_event1(p,x-1,y+2);
		}
	}
	if(y<8&&x<17){
		p5_event1(p,x+1,y+1);
		if(x<16){
			p5_event1(p,x+2,y+1);
		}
	}
}
void p_p5_event(int (*p)[18]){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<18;j++){
			if((*(*(p+i)+j))==-1){
				continue;
			}
			gtxy(lx+j*2,ly+i);
			if((*(*(p+i)+j))==0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),108);
			}
			else if((*(*(p+i)+j))==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),96);
			}
			else if((*(*(p+i)+j))==2){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
			}
			printf("�~");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p5_event2(int (*p)[18],int x,int y){
	if((*(*(p+y)+x))==-1){
		return;
	}
	if((*(*(p+y)+x))==0){
		return;
	}
	(*(*(p+y)+x))--;
}
void switch_tub(int (*p)[18]){
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("������..");
	switch_tub_cartoon(p);
	Sleep(300);
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
} 
void first_tub(int (*p)[18]){
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("������..");
	int count = 10;
	srand(time(NULL));
	while(count){
		int x = rand()%9;
		int y = rand()%18;
		if((*(*(p+x)+y))!=-1&&(*(*(p+x)+y))!=0){
			(*(*(p+x)+y))--;
			count--;
		}
	}
	p_p5_event(p);
	p5_counting(p);
	p_c_re();
	Sleep(500);
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void switch_tub_cartoon(int (*p)[18]){
	srand(time(NULL));
	int x,y,i,j,k;
	x = rand()%33;
	j = 2;
	k = 7;
	for(i=0;i<18;i++){
		j=(j+2)%10;
		if(j!=0){
			x--;
			if(x<0){
				x = i;
				y = j-1;
				break;
			}
		}
		k=(k+2)%10;
		if(k!=0){
			x--;
			if(x<0){
				x = i;
				y = k-1;
				break;
			}
		}
	}
	gtxy(lx+x*2,ly+y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),105);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(lx+x*2,ly+13);
	printf("��");
	gtxy(lx-8,ly+y);
	printf("��");
	Sleep(700);
	gtxy(lx+x*2,ly+y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(lx+x*2,ly+13);
	printf("  ");
	gtxy(lx-8,ly+y);
	printf("  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(lx+x*2,ly+12);
	printf("��");
	gtxy(lx-6,ly+y);
	printf("��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),107);
	if(y>0&&x>0){
		p5_event2(p,x-1,y-1);
		gtxy(lx+(x-1)*2,ly+y-1);
		printf("�~");
	}
	if(y>0&&x<17){
		p5_event2(p,x+1,y-1);
		gtxy(lx+(x+1)*2,ly+y-1);
		printf("�~");
	}
	if(y<8&&x>0){
		p5_event2(p,x-1,y+1);
		gtxy(lx+(x-1)*2,ly+y+1);
		printf("�~");
	}
	if(y<8&&x<17){
		p5_event2(p,x+1,y+1);
		gtxy(lx+(x+1)*2,ly+y+1);
		printf("�~");
	}
	if(y>1){
		p5_event2(p,x,y-2);
		gtxy(lx+x*2,ly+y-2);
		printf("�~");
	}
	if(y<7){
		p5_event2(p,x,y+2);
		gtxy(lx+x*2,ly+y+2);
		printf("�~");
	}
	if(x>1){
		p5_event2(p,x-2,y);
		gtxy(lx+(x-2)*2,ly+y);
		printf("�~");
	}
	if(x<16){
		p5_event2(p,x+2,y);
		gtxy(lx+(x+2)*2,ly+y);
		printf("�~");
	}
	Sleep(600);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(lx+x*2,ly+12);
	printf("  ");
	gtxy(lx-6,ly+y);
	printf("  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(lx+x*2,ly+11);
	printf("��");
	gtxy(lx-4,ly+y);
	printf("��");
	p_p5_event(p);
	Sleep(400);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(lx+x*2,ly+11);
	printf("  ");
	gtxy(lx-4,ly+y);
	printf("  ");
	p5_counting(p);
	p_c_re();
}
void p5_counting(int (*p)[18]){
	int i,j;
	mr[0] = 0;
	mr[1] = 0;
	for(i=0;i<9;i++){
		for(j=0;j<18;j++){
			if((*(*(p+i)+j))==0){
				mr[0]++;
			}
			else if((*(*(p+i)+j))==2){
				mr[1]++;
			}
		}
	}
}
void p_c_re(){
	gtxy(30,4);
	printf("%4d",mr[1]);
	gtxy(51,4);
	printf("%4d",mr[0]);
}
void p5_skillscdd(int sk[5],int skco[5]){
	int i;
	for(i=0;i<5;i++){
		if(sk[i]>0){
			sk[i]--;
		}
	}
	p_skills(sk,skco);
}
void p5_skill1(int (*p)[18]){
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("SK-1    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<18;j++){
			if((*(*(p+i)+j))!=-1){
				(*(*(p+i)+j)) = 1;
			}
		}
	}
	p5_skill1_cartoon(p);
	p5_counting(p);
	p_c_re();
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p5_skill1_cartoon(int (*p)[18]){
	int i,j,k;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(lx-4,ly-1);
	printf("��");
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	for(i=0;i<9;i++){
		gtxy(lx-4,ly+i);
		printf("��");
		Sleep(70);
	}
	j = 2;
	k = 7;
	for(i=0;i<18;i++){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		gtxy(lx+i*2,ly+11);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),105);
		j=(j+2)%10;
		if(j!=0){
			(*(*(p+j-1)+i)) = -1;
			gtxy(lx+i*2,ly+j-1);
			printf("�~");
		}
		k=(k+2)%10;
		if(k!=0){
			(*(*(p+k-1)+i)) = -1;
			gtxy(lx+i*2,ly+k-1);
			printf("�~");
		}
		Sleep(90);
	}
	Sleep(500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	for(i=0;i<18;i++){
		gtxy(lx+i*2,ly+11);
		printf("  ");
		gtxy(lx+i*2,ly+10);
		printf("��");
	}
	p_p5_event(p);
	Sleep(500);
	j = 2;
	k = 7;
	for(i=0;i<18;i++){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		gtxy(lx+i*2,ly+10);
		printf("  ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
		j=(j+2)%10;
		if(j!=0){
			(*(*(p+j-1)+i)) = -1;
			gtxy(lx+i*2,ly+j-1);
			printf("�~");
		}
		k=(k+2)%10;
		if(k!=0){
			(*(*(p+k-1)+i)) = -1;
			gtxy(lx+i*2,ly+k-1);
			printf("�~");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(lx-4,ly-1);
	printf("  ");
	for(i=0;i<9;i++){
		gtxy(lx-4,ly+i);
		printf("  ");
	}
}
void p5_skill2(int (*p)[18]){
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("SK-2    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	int i,j,k=0;
	for(i=0;i<9;i++){
		for(j=0;j<18;j++){
			if((*(*(p+i)+j))==2){
				(*(*(p+i)+j)) = 10;
			}
			else if((*(*(p+i)+j))==0){
				k++;
			}
		}
	}
	p5_skill2_cartoon(p,k);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	p5_counting(p);
	p_c_re();
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p5_skill2_cartoon(int (*p)[18],int count){
	int i,j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(lx-4,ly-1);
	printf("��");
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	for(i=0;i<9;i++){
		gtxy(lx-4,ly+i);
		printf("��");
		Sleep(70);
	}
	for(i=0;i<18;i++){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		gtxy(lx+i*2,ly+11);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),105);
		for(j=0;j<9;j++){
			if((*(*(p+j)+i))==10){
				(*(*(p+j)+i)) = 1;
				gtxy(lx+i*2,ly+j);
				printf("�~");
			}
		}
		Sleep(90);
	}
	Sleep(500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	for(i=0;i<18;i++){
		gtxy(lx+i*2,ly+11);
		printf("  ");
		gtxy(lx+i*2,ly+10);
		printf("��");
	}
	p_p5_event(p);
	Sleep(500);
	srand(time(NULL));
	while(count){
		i = rand()%9;
		j = rand()%18;
		if((*(*(p+i)+j))==1){
			(*(*(p+i)+j)) = 2;
			count--;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(lx-4,ly-1);
	printf("  ");
	for(i=0;i<9;i++){
		gtxy(lx-4,ly+i);
		printf("  ");
	}
	for(i=17;i>=0;i--){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		gtxy(lx+i*2,ly+10);
		printf("  ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
		for(j=0;j<9;j++){
			if((*(*(p+j)+i))==2){
				gtxy(lx+i*2,ly+j);
				printf("�~");
			}
		}
		Sleep(90);
	}
	p_p5_event(p);	
}
void p5_skill3(int (*p)[18]){
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("SK-3    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	p5_counting(p);
	int ea = mr[0], mi = mr[1];
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<18;j++){
			if((*(*(p+i)+j))!=-1){
				(*(*(p+i)+j)) = 1;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(lx-4,ly-1);
	printf("��");
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	for(i=0;i<9;i++){
		gtxy(lx-4,ly+i);
		printf("��");
		Sleep(60);
	}
	for(i=0;i<18;i++){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		gtxy(lx+i*2,ly+11);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),105);
		Sleep(60);
	}
	p_p5_event(p);
	Sleep(400);
	for(j=0;j<18;j++){
		for(i=0;i<9;i++){
			if((*(*(p+i)+j))==-1){
				continue;
			}
			if(mi==0){
				break;
			}
			(*(*(p+i)+j)) = 2;
			mi--;
		}
	}
	for(j=17;j>=0;j--){
		for(i=8;i>=0;i--){
			if((*(*(p+i)+j))==-1){
				continue;
			}
			if(ea==0){
				break;
			}
			(*(*(p+i)+j)) = 0;
			ea--;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	for(i=0;i<18;i++){
		gtxy(lx+i*2,ly+11);
		printf("  ");
		gtxy(lx+i*2,ly+10);
		printf("��");
	}
	p_p5_event(p);
	Sleep(400);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	for(i=0;i<18;i++){
		gtxy(lx+i*2,ly+10);
		printf("  ");
	}
	gtxy(lx-4,ly-1);
	printf("  ");
	for(i=0;i<9;i++){
		gtxy(lx-4,ly+i);
		printf("  ");
	}
	p5_counting(p);
	p_c_re();
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����    ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int p5_result_v(int tu){
	char rv[100]="";
	if(tu<9){
		strcat(rv,"��ɳƺ�\n      <BUG��>\nʤ֮����");
	}
	else if(tu>9&&tu<=25){
		strcat(rv,"��ɳƺ�\n      <����>\n��������");
	}
	else if(tu>25&&tu<=70){
		strcat(rv,"��ɳƺ�\n      <������ս>\n�ɵ�Ư��");
	}
	else if(tu>70&&tu<=100){
		strcat(rv,"��ɳƺ�\n      <��ֲ�и>\nֵ�ñ���");
	}
	else if(tu>100){
		strcat(rv,"��ɳƺ�\n      <�۳־�ս>");
	}
	strcat(rv,"\n����һ�֣�");
	return MessageBox(NULL,rv,"DEFEAT",MB_YESNO)-6;
}
int p5_result_d(int tu){
	char rv[100]="";
	if(tu==5){
		strcat(rv,"��ɳƺ�\n      <ŷ��>\n�������");
	}
	else if(tu<5){
		strcat(rv,"��ɳƺ�\n      <BUG��>\n��ò�ԩ");
	}
	else if(tu>5&&tu<=10){
		strcat(rv,"��ɳƺ�\n      <����>\nҪ�����");
	}
	else if(tu>10&&tu<=50){
		strcat(rv,"��ɳƺ�\n      <Ӣ�·�ս>");
	}
	else if(tu>50&&tu<=100){
		strcat(rv,"��ɳƺ�\n      <��ǿ�ֿ�>");
	}
	else if(tu>100){
		strcat(rv,"��ɳƺ�\n      <����֮��>\n�������");
	}
	strcat(rv,"\n����һ�֣�");
	return MessageBox(NULL,rv,"DEFEAT",MB_YESNO)-6;
}
