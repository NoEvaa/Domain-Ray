#include "yzprogress.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];
extern int AIstep;

int mode(){
	clean();
	//SetSize(30,15);
	gtxy(1,1);
	printf("ģʽѡ��:\n");
	printf("   �x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                  ��\n");
	printf(" �� �� ����ģʽ      ��\n");
	printf(" ��------------------��\n");
	printf(" ��                  ��\n");
	printf(" �� �� ��Լ��ս      ��\n");	
	printf(" ��------------------��\n");
	printf(" ��                  ��\n");
	printf(" �� �� ���ֽ̳�      ��\n");
	printf(" ��------------------��\n");
	printf(" ��                  ��\n");
	printf(" �� �� ׷��-����      ��\n");
	printf(" ��                  ��\n");
	printf("   ������������������  "); 
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
          					if(X>2&&X<21){
          						if(Y==3||Y==4){
          							return 1;//���� 
								  }
								else if(Y==6||Y==7){
									return 2;//��ս 
								}
								else if(Y==9||Y==10){
									return 3;//�̳�
								}
								else if(Y==12||Y==13||Y==14){
									return 4;//���� 
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
	printf("  |��������|\n"); 
	printf("  | ������ |\n"); 
	printf("   ��������                   :��Լѡ��\n"); 
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��         |    ������+10             ��\n");
	printf(" ��         |--------------------------��\n");
	printf(" ��    ��   |    �ϲ��׿�������ͳ��    ��\n");
	printf(" ��         |--------------------------��\n");
	printf(" ��         |    ȥ���״ε������      ��\n");
	printf(" ��---------|--------------------------��\n");
	printf(" ��         |    ��ά����+1��������+20 ��\n");
	printf(" ��   ����  |--------------------------��\n");
	printf(" ��         |    ��ʱ300s              ��\n");
	printf(" ��---------|--------------------------��\n");	
	printf(" ��         |    ��ά����+1��������+40 ��\n");
	printf(" ��         |--------------------------��\n");
	printf(" ��  ������ |    ��ֹ����              ��\n");
	printf(" ��         |--------------------------��\n");
	printf(" ��         |    ʧȥȫ������ʮ����    ��\n");
	printf("   ������������������������������������ \n");
	printf("                             |��������|\n"); 
	printf("                             | ��ʼ ��|\n");
	printf("                              �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);//����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);//�����豸��� 
	int rt,cc[8]={0},control=0;
	while(1)
	{
	    ReadConsoleInput(hInput, &inRec, 1, &numRead);//��ȡ1�������¼� 
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
          						return;
          						//���� 
							  }
							if(X>29&&X<38&&Y>20&&Y<23){
          						control = 1;//��ʼ 
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
	printf("  ��  �� ��Լ����     ��\n");
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
	printf("  |��������|\n"); 
	printf("  | ������ |\n"); 
	printf("   ��������       \n"); 
	printf("    �x�x�x�x�x�x�x�x�x�x�x               �x�x�x�x�x�x�x�x�x�x�x \n");	
	printf("  ��                      ��           ��                      ��\n");
	printf("  ��  �� ��ʶ!��������    ��           ��     ��  *����ƪ      ��\n");
	printf("  ��----------------------��           ��                      ��\n");
	printf("  ��                      ��             ����������������������  \n");
	printf("  ��  �� ����!����Ѱ��    ��\n");	
	printf("  ��----------------------��\n");
	printf("  ��   * BackingStore     ��\n");
	printf("  ��     Exception        ��\n");//�� 
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  �� ��!����          ��\n");//�ڰ���
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  �� Σ��!ը������Ϯ  ��\n");//��ͼ���� 
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  �� ����!��������    ��\n");//��һ�
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  �� ��!ʱ��          ��\n");//�޾�ɨ�� 
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  �� ����!��֮����    ��\n");
	printf("  ��                      ��\n");
	printf("    ����������������������  "); 
	
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






