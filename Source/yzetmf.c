#include "yzetmf.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];
extern int AIstep;

void entertainment6(){
	e_6();	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //�����豸��� 
	int rt,st = 0;
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
	printf(" �Σ�\n"); 
	printf("   �������ǲ�иŬ��\n");
	printf("   ���ڷ�����ը���˵����ִ���\n");
	printf("   ������һ���ը��С���˼�ʻ�ŷ�������Ҫ��������\n");
	printf("   �ҽ����������׵Ŀ���Ȩ\n");
	printf("   ����������Щը��С���˸Ͼ�ɱ����!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("   �����������޵����ܻ��ܾ����ܶ�ķ�����\n"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   gogogo!!!\n\n");
	printf("   |��������|     |��������|      |��������|\n"); 
	printf("   | ������ |     |  �̳�  |      | ��ʼ ��|\n");
	printf("    ��������       ��������        �������� \n"); 
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
	printf("  |��������|\n"); 
	printf("  | ������ |\n");
	printf("   ��������       \n"); 
	printf("    �x�x�x�x�x�x�x�x�x  \n");	
	printf("  ��                  ��\n");
	printf("  ��  �� �淨         ��\n");
	printf("  ��------------------��\n");
	printf("  ��                  ��\n");
	printf("  ��  �� BOSSЧ��     ��\n");	
	printf("  ��------------------��\n");
	printf("  ��                  ��\n");
	printf("  ��  �� ����         ��\n");
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
void e6_operation(){
	lx=40;
	ly=10;
	e6_o1();
	e6_o2();
	e6_o3(); 
}
void e6_o1(){
	c_mine = 5;//boss
	mr[0] = 9999;//����
	mr[1] = 0;//����
	clean();
    play6_frame();
   	c_blank = 18;//HP 
	gtxy(7,8);
	printf("<̰��>");
	gtxy(7,9);
	printf("�~�~�~");
	gtxy(7,10);
	printf("�~  �~");
	gtxy(7,11);
	printf("�~�~�~");
	gtxy(5,12);
	printf("HP MAX: %2d",c_blank);
	gtxy(5,13);
	printf("TALENTS:");
	gtxy(7,14);
	printf("[����]����");
	gtxy(7,15);
	printf("[����]����");
	int emap[5][5] = {{0,2,2,2,0},
					  {0,2,0,2,0},
					  {0,2,2,2,0},
					  {0,0,0,0,0},
					  {0,0,0,0,0}};//0���� 1���� 2�з� -1δ���� 
	int wmap[10] = {0};
	int record[7] = {0};//0ͬ������ 1���� 2����[0-10] 3��Ĭ 4����x 5����y 6��Ѫ 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//����
    int dc = mr[0];//��Ѫ 
	int DS = 0;//ʥ���� 
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
	printf(" ��ӭ�������ֽ̳�                         ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ����һ��ʮ���������ֵ���Ϸ               ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ��ͼ����Ϸ�����                         ");
	gtxy(28,y++);
	printf(" ��ɫ��5*5��ͼ�з���������                ");
	gtxy(28,y++);
	printf(" ���ϵİ�ɫ�׸��������׵�����װ��         ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
	gtxy(lx,ly+5);
	printf("�~"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" �����ɫ�׸񼴿���������/������          ");
	gtxy(28,y++);
	printf(" ���һ�����԰�                           ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                (�������ɫ�׸�)     �� ");
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
	printf("�~");
	p_p6_le_cartoon1(emap,record);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" �������׶���������!!!                    ");
	gtxy(28,y++);
	printf(" ��ͼ�к�ɫ�׸���ʾ�ļ�Ϊ                 ");
	gtxy(28,y++);
	printf(" ��ʱը���˵ķ�������λ��                 ");
	gtxy(28,y++);
	printf(" �ܿ�ϧû������                           ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
}
void e6_o2(){
	c_mine = 5;//boss
	mr[0] = 9999;//����
	mr[1] = 2;//����  
	clean();
    play6_frame();
   	c_blank = 18;//HP 
	gtxy(7,8);
	printf("<̰��>");
	gtxy(7,9);
	printf("�~�~�~");
	gtxy(7,10);
	printf("�~  �~");
	gtxy(7,11);
	printf("�~�~�~");
	gtxy(5,12);
	printf("HP MAX: %2d",c_blank);
	gtxy(5,13);
	printf("TALENTS:");
	gtxy(7,14);
	printf("[����]����");
	gtxy(7,15);
	printf("[����]����");
	int emap[5][5] = {{0,0,0,0,0},
					  {0,0,2,2,2},
					  {0,0,2,0,2},
					  {0,0,2,2,2},
					  {0,0,0,0,0}};//0���� 1���� 2�з� -1δ���� 
	int wmap[10] = {0};
	int record[7] = {0};//0ͬ������ 1���� 2����[0-10] 3��Ĭ 4����x 5����y 6��Ѫ 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//����
    int dc = mr[0];//��Ѫ 
	int DS = 0;//ʥ���� 
    p_p6_emap();
    p_p6_newHP();
	p_p6_c(DS);
	p_p6_a();
	p_p6_wmap(wmap);
	p_p6_skills(skillcd,record[3]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),106);
	gtxy(lx+4,ly+5);
	printf("�~"); 
	int y = 17;	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ������ǻ�һ���׸���                   ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                (�������ɫ�׸�)     �� ");
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
	printf("�~"); 
	y = 17;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ohhhh���˳��������ը���˷�����          ");
	gtxy(28,y++);
	printf(" ��ɫ�׸񼴱�ʾ������ը���ķ���������     ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
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
	printf(" ���Ϸ�BOSS's HP��Ϊ��������Ѫ��          ");
	gtxy(28,y++);
	printf(" ��Ѫ������ʱ�������ͻᱻ����             ");
	gtxy(28,y++);
	printf(" ĿǰѪ����������Ϊ��ɫ                 ");
	gtxy(28,y++);
	printf(" �������׶�����ɵ��˺�                   ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
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
	printf(" ��ɫ������ʧ��                         ");
	gtxy(28,y++);
	printf(" ʣ�µĻƸ�Ϊ��������ʣ������ֵ           ");
	gtxy(28,y++);
	printf(" ��Ϊ��ܷ������������츳                 ");
	gtxy(28,y++);
	printf(" ����ʱӵ�����񻤼ף���Ѫ���������       ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
}
void e6_o3(){
	c_mine = 3;//boss
	mr[0] = 9999;//����
	mr[1] = 30;//����
	clean();
    play6_frame();
	c_blank = 20;//HP
	gtxy(7,8);
	printf("<�ը��>");
	gtxy(7,9);
	printf("  �~");
	gtxy(7,10);
	printf("�~�~�~");
	gtxy(5,11);
	printf("HP MAX: %2d",c_blank);
	gtxy(5,12);
	printf("TALENTS:");
	gtxy(7,13);
	printf("[����]����");
	gtxy(7,14);
	printf("[����]����");
	int emap[5][5] = {{0,0,0,0,0},
					  {2,0,0,0,0},
					  {2,2,0,0,0},
					  {2,0,0,0,0},
					  {0,0,0,0,0}};//0���� 1���� 2�з� -1δ���� 
	int wmap[10] = {0};
	int record[7] = {0};//0ͬ������ 1���� 2����[0-10] 3��Ĭ 4����x 5����y 6��Ѫ 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//����
    int dc = mr[0];//��Ѫ 
	int DS = 0;//ʥ���� 
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
	printf(" ����Ϸ����ܴ����������ֵ               ");
	gtxy(28,y++);
	printf(" ������Ϊ��ʱ��Ϸ�������                 ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ������м�BOSS Details��                 ");
	gtxy(28,y++);
	printf(" չʾ�˷��������������ֵ����״           ");
	gtxy(28,y++);
	printf(" ������������                             ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ����¼�DEBUFF                           ");
	gtxy(28,y++);
	printf(" ���������������ʩչ�ļ���Ч��           ");
	gtxy(28,y++);
	printf(" �������ж���������Ӱ��                 ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" �Ҳ��Ǽ�����                             ");
	gtxy(28,y++);
	printf(" �ṩ�����ּ��ܹ���ʹ��                   ");
	gtxy(28,y++);
	printf(" �������ʹ�ü������°빦��               ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ��������������һ��                       ");
	gtxy(28,y++);
	printf(" ���ȵ������<ӥ����>                     ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
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
	printf(" �ٵ������ <��Ѫ>                        ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	ttt = 1;
	while(ttt)
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
	printf("�~"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" �������ɫ������������                 ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                (�������ɫ�׸�)     �� ");
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
	printf(" ������С������һ�¾�ʧȥ��9������ֵ      ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
	gtxy(28,y++);
	printf("                                          ");
	go_on(0,0,0,92,30);
	y = 17;	
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf(" ������Ϸ�������Լ�ȥ�����               ");
	gtxy(28,y++);
	printf(" bye~                                     ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                                          ");
	gtxy(28,y++);
	printf("                  (�������Լ���)     �� ");
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
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
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
	printf("��BOSS������\n"); 
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��              ||||||||||                                      ��\n");
	printf(" ��    ���˳�    |++++++++|                                      ��\n");
	printf(" ��--------------------------------------------------------------��\n");
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
	printf(" ��--------------|                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf(" ��              |                                               ��\n");
	printf("   �������������������������������������������������������������� \n");
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
	printf("<��ʿ��>");
	if(s==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,10);
	printf("<����>");
	if(s==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,13);
	printf("<�ը��>");
	if(s==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,16);
	printf("<��ɫ�ռ�>");
	if(s==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,19);
	printf("<̰��>");
	p_e6_boss_detail(s);
}
void p_e6_boss_detail(int s){
	p_e5_skillc_clean();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	switch(s){
		case 1:
			gtxy(26,6);
			printf("<��ʿ��>");
			gtxy(23,8);
			printf("[����]: ");
			gtxy(23,11);
			printf("[����]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("��������");
			gtxy(27,10);
			printf("HP(MAX)�ﵽ55");
			gtxy(23,12);
			printf("ͬ������(����)");
			gtxy(27,13);
			printf("50%%���ʸ���DEBUFF[ͬ������]");
			gtxy(27,14);
			printf("[ͬ������]:�ܵ��˺���۳���������");
			break;
		case 2:
			gtxy(26,6);
			printf("<����>");
			gtxy(23,8);
			printf("[����]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("����(����)");
			gtxy(27,10);
			printf("Ϊ����ĸ������㸽��DEBUFF[����]");
			gtxy(27,11);
			printf("�۳�����4");
			gtxy(27,12);
			printf("[����]:�����ŵ������㽫�޷�ʹ��");
			break;
		case 3:
			gtxy(26,6);
			printf("<�ը��>");
			gtxy(23,8);
			printf("[����]: ");
			gtxy(23,13);
			printf("[����]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			gtxy(27,17);
			printf("      <!-�ɵ��ӣ����10��>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("����");
			gtxy(27,10);
			printf("<!-���������ⲿλ�ܵ��˺��󴥷�>");
			gtxy(27,11);
			printf("Ϊָ����������㸽��DEBUFF[����]");
			gtxy(27,12);
			printf("�۳�����5");
			gtxy(23,14);
			printf("����(����)");
			gtxy(27,15);
			printf("20%%���ʸ���DEBUFF[����]");
			gtxy(27,16);
			printf("[����]:ÿ���������׶���۳��̶�����");
			break;
		case 4:
			gtxy(26,6);
			printf("<��ɫ�ռ�>");
			gtxy(23,8);
			printf("[����]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			gtxy(27,11);
			printf("     <!-�� [����]ͬ������ ����>");
			gtxy(27,16);
			printf("     <!-�� [����]��Ĭ ����>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("��Ĭ(����)");
			gtxy(27,10);
			printf("50%%���ʸ���DEBUFF[��Ĭ]");
			gtxy(27,12);
			printf("[��Ĭ]:�޷�ʹ�ü���(<�󾻻�>����)");
			gtxy(23,13);
			printf("ͬ������(����)");
			gtxy(27,14);
			printf("50%%���ʸ���DEBUFF[ͬ������]");
			gtxy(27,15);
			printf("[ͬ������]:�ܵ��˺���۳���������");
			break;
		case 5:
			gtxy(26,6);
			printf("<̰��>");
			gtxy(23,8);
			printf("[����]: ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(23,9);
			printf("����");
			gtxy(27,10);
			printf("��ʱӵ��2�㻤�׵����˺�");
			gtxy(23,11);
			printf("����");
			gtxy(27,12);
			printf("�۳��뻤���������˺�����������");
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
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
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
	printf("�������飺\n"); 
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��              ||||||||||                                      ��\n");
	printf(" ��    ���˳�    |++++++++|                                      ��\n");
	printf(" ��--------------------------------------------------------------��\n");
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
void p_e6_skillc(int s){
	if(s==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,7);
	printf("�󾻻�");
	if(s==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,10);
	printf("��ӥ����");
	if(s==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,13);
	printf("����Ѫ");
	if(s==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	}
	gtxy(4,16);
	printf("��ʥ����");
	p_e6_skillc_detail(s);
}
void p_e6_skillc_detail(int s){//
	p_e5_skillc_clean();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(23,8);
	printf("A: ");
	gtxy(23,9);
	printf("����������");
	switch(s){
		case 1:
			gtxy(26,6);
			printf("<�󾻻�>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("   8");
			gtxy(27,10);
			printf("�����ǰȫ��DEBUFF��");
			break;
		case 2:
			gtxy(26,6);
			printf("<��ӥ����>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("   8");
			gtxy(27,10);
			printf("���ֲ������ͼ�з�����λ�á�");
			break;
		case 3:
			gtxy(26,6);
			printf("<����Ѫ>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("  12");
			gtxy(27,10);
			printf("��һ���������׽���������˺���");
			gtxy(27,11);
			printf("���´��������׽���ɶ����˺���");
			gtxy(27,12);
			printf(" <!-ͬ��Ч���޷�����>");
			break;
		case 4:
			gtxy(26,6);
			printf("<��ʥ����>");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			gtxy(26,8);
			printf("  15");
			gtxy(27,10);
			printf("����һ�й����ͷ�����");
			gtxy(27,11);
			printf("*ֱ����һ����������Ϊֹ��");
			gtxy(27,12);
			printf("   �κ���Ϊ���޷���������");
			gtxy(27,13);
			printf("   ����DEFUFFʧЧ");
			gtxy(27,14);
			printf("�׳�<�޵�>");
			break;
	} 
}
int play6(){	
	lx=40;
	ly=10;
	c_mine = 3;//boss
	c_blank = 55;//HP  MAX55
	mr[0] = 9999;//����
	mr[1] = 10;//����
	int tub = 0;//���� 
    
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
	int emap[5][5] = {0};//0���� 1���� 2�з� -1δ���� 
	int wmap[10] = {0};
	int record[7] = {0};//0ͬ������ 1���� 2����[0-10] 3��Ĭ 4����x 5����y 6��Ѫ 
	int skillcd[4] = {0,0,0,0};
    AIstep = 0;//����
    int dc = mr[0];//��Ѫ 
	int DS = 0;//ʥ���� 
    
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
			printf("<��ʿ��>");
			gtxy(7,9);
			printf(" �~�~");
			gtxy(7,10);
			printf(" �~�~");
			gtxy(5,11);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,12);
			printf("TALENTS:");
			gtxy(7,13);
			printf("[����]��������");
			gtxy(7,14);
			printf("[����]ͬ������"); 
			break;
		case 2:
			c_blank = 40;
			gtxy(7,8);
			printf("<����>");
			gtxy(7,9);
			printf("  �~");
			gtxy(7,10);
			printf("�~  �~");
			gtxy(7,11);
			printf("  �~");
			gtxy(5,12);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,13);
			printf("TALENTS:");
			gtxy(7,14);
			printf("[����]����");
			break;
		case 3:
			c_blank = 20;
			gtxy(7,8);
			printf("<�ը��>");
			gtxy(7,9);
			printf("  �~");
			gtxy(7,10);
			printf("�~�~�~");
			gtxy(5,11);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,12);
			printf("TALENTS:");
			gtxy(7,13);
			printf("[����]����");
			gtxy(7,14);
			printf("[����]����");
			break;
		case 4:
			c_blank = 30;
			gtxy(7,8);
			printf("<��ɫ�ռ�>");
			gtxy(7,9);
			printf("  �~");
			gtxy(7,10);
			printf("  �~�~");
			gtxy(7,11);
			printf("�~");
			gtxy(5,12);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,13);
			printf("TALENTS:");
			gtxy(7,14);
			printf("[����]��Ĭ");
			gtxy(7,15);
			printf("[����]ͬ������");
			break;
		case 5:
			c_blank = 18;
			gtxy(7,8);
			printf("<̰��>");
			gtxy(7,9);
			printf("�~�~�~");
			gtxy(7,10);
			printf("�~  �~");
			gtxy(7,11);
			printf("�~�~�~");
			gtxy(5,12);
			printf("HP MAX: %2d",c_blank);
			gtxy(5,13);
			printf("TALENTS:");
			gtxy(7,14);
			printf("[����]����");
			gtxy(7,15);
			printf("[����]����");
			break;
	}
}
void play6_frame(){
	gtxy(0,1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��---------------------|                                                                ��\n");
	printf(" ��                     |                                                                ��\n");
	printf(" ��                     |----------------------------------------------------------------��\n");
	printf(" ��                     |                                            |    ս������ ��   |��\n");
	printf(" ��                     |                                            |    >>>>>>>>>>    |��\n");
	printf(" ��                     |                                             ������������������ ��\n");
	printf(" ��                     |                                                |��������������|��\n");
	printf(" ��                     |                                                |              |��\n");
	printf(" ��                     |                                                |xxxxxxxxxxxxxx|��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��---------------------|                                                |---------------��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |---------------��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |---------------��\n");
	printf(" ��---------------------|                                                |               ��\n");
	printf(" ��---------------------|                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
	printf("   ��������������������������������������������������������������������������������������  ");
	gtxy(5,3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("����C:");
	gtxy(75,12);
	printf("����A:");
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
			printf("�~");
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
		printf("�~");
	}
	for(i=0;i<5;i++){
		gtxy(lx+2*i,ly+5);
		if(wp[5+i]){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),104);
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),111);
		}
		printf("�~");
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
			printf("�~");
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
		printf("��");
	}
	if(c_mine==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
		printf("����");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	}
	gtxy(28,5);
	j = c_blank-j;
	for(i=0;i<j;i++){
		printf("��");
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
			printf("��");
		}
		if(c_blank+ct<25){
			j = c_blank+ct;
		}
		else{
			j = 25;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		for(;i<j;i++){
			printf("��");
		}
		j = c_blank+ct-25;
		gtxy(28,5);
		for(i=0;i<j;i++){
			printf("��");
		}
	}
	else{
		gtxy(38,3);
		for(i=0;i<25;i++){
			printf("��");
		}
		j = c_blank-25;
		gtxy(28,5);
		for(i=0;i<j;i++){
			printf("��");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		for(i=0;i<ct;i++){
			printf("��");
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
	ep[i+1][j] = 2;  //�~�~
	ep[i][j+1] = 2;  //�~�~
	ep[i+1][j+1] = 2;
}
void p6_aeroset2(int ep[5][5],int wp[10]){
	srand(time(NULL));	
	int i = rand()%3+1, j = rand()%3+1;
	ep[i][j-1] = 2;  //  �~
	ep[i+1][j] = 2;  //�~  �~
	ep[i][j+1] = 2;  //  �~
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
	int c = 0;   //  �~
	rd[4] = i;
	rd[5] = j;
	ep[i][j] = 2;//�~�~�~
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
	ep[i+dx][j+dy] = 2; //  �~
	ep[i-dx][j] = 2;    //  �~�~
	ep[i][j-dy] = 2;    //�~
}
void p6_aeroset5(int ep[5][5],int wp[10]){
	srand(time(NULL));	
	int i = rand()%3+1, j = rand()%3+1;
	ep[i+1][j+1] = 2; //�~�~�~
	ep[i-1][j-1] = 2; //�~  �~
	ep[i][j-1] = 2;   //�~�~�~
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
		printf("ͬ������");
	}
	if(rd[1]){
		gtxy(6,y++);
		printf("����");
	}
	if(rd[2]){
		gtxy(6,y++);
		printf("����%d��",rd[2]);
	}
	if(rd[3]){
		gtxy(6,y++);
		printf("��Ĭ");
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
	printf("�󾻻�");
	gtxy(75,15);
	printf("A8");
	if(mr[1]>=8&&scd[1]==0&&rd3==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,17);
	printf("��ӥ����");
	gtxy(75,18);
	printf("A8");
	if(mr[1]>=12&&scd[2]==0&&rd3==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,20);
	printf("����Ѫ");
	gtxy(75,21);
	printf("A12");
	if(mr[1]>=15&&scd[3]==0&&rd3==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
	}
	gtxy(75,23);
	printf("��ʥ����");
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
			printf("�~");
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
		printf("�~");
	}
	for(i=0;i<5;i++){
		gtxy(lx+2*i,ly+5);
		printf("�~");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int p6_result(int tu){
	char rv[100]="���ܵз���λ";
	char s[6],v[4];
	itoa(tu,s,10);
	itoa(9999-mr[0],v,10);
	strcat(rv,s);
	strcat(rv,"\n������������");
	strcat(rv,v);
	strcat(rv,"\n�ط�ս����");
	return MessageBox(NULL,rv,"END",MB_YESNO)-6;
}
