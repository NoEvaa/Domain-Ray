#include "yzetma.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];

void entertainment1(){
	clean();
	gtxy(0,1); 		
	printf(" Administrator��\n"); 
	printf("   ���ã���������Ĺ���Ա\n");
	printf("   �ƻ���ը����͵�����ҵ���ͼ������!\n");
	printf("   ��֪����������~�������ͼ���Ҷ�ؿ�������!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   ��ͼΪ2*6*6*6���\n");
	printf("   ����120���ף����������������ͼ��\n");
	printf("   �Ҹұ�֤����û�ѿ�������ը������һ��\n");
	printf("   �ҵ������������뿪��ͼ\n");
	printf("   �ҽ�������10������ʮ����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);  
	printf("   �Ͻ���ѡһ���˸����ս����~!\n\n");
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��              |            |              ��\n");
	printf(" ��    Ӣ����    |    ��ͽ    |    ����ʦ    ��\n");
	printf(" ��              |            |              ��\n");
	printf(" ��------------------------------------------��\n");
	printf(" ��                                          ��\n");
	printf(" ��                                          ��\n");
	printf(" ��                                          ��\n");
	printf(" ��                                          ��\n");	
	printf(" ��                                          ��\n");
	printf("   ������������������������������������������ \n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	int ec = 1,st = 0;
	et_event(ec);
	
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
          					if(Y>12&&Y<16){
          						if(X>2&&X<17){
          							ec = 1;
          							et_event(ec);
								  }
								else if(X>17&&X<30){
									ec = 2;
									et_event(ec);
								}
								else if(X>30&&X<45){
									ec = 3;
									et_event(ec);
								}
								break;
							  }
							if(Y>22&&Y<25){
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
		if(play1(ec)){
			return;
		}
	}	
}
void et_event(int ec){
	gtxy(5,17);
	printf("                                        ");
	gtxy(5,18);
	printf("                                        ");
	gtxy(5,19);
	printf("                                        ");
	switch(ec){
		case 1:
			gtxy(6,17);
			printf("<Ӣ����>"); 
			gtxy(6,18);
			printf("ӵ��99������ʮ����");
			break;
		case 2:
			gtxy(6,17);
			printf("<��ͽ>");
			gtxy(6,18);
			printf("ÿ�βȵ���ʱ��50%%���ʻ������");
			break;
		case 3:
			gtxy(6,17);
			printf("<����ʦ>");
			gtxy(6,18);
			printf("������-20");
			gtxy(6,19);
			printf("ÿ�βȵ��׶�����Ѱ��Χ7���Ƿ��п�����");
			break;
	}	
}
int play1(int ec){
	clean();
	play1_frame();
	
	gtxy(15,2);
	switch(ec){
		case 1:
			printf("<Ӣ����>");
			break;
		case 2:
			printf("<��ͽ>");
			break;
		case 3:
			printf("<����ʦ>");
			break;
	}
	
	lx=(92-N*(N+1)*2)/2+1;
	ly=7;
	c_blank = 2*N*N*N;
	c_mine = 120;
	mr[0]=0;
	mr[1]=0;	
	
	p_newmap(lx,ly,N);
	struct Map newmap[2][N][N][N]={0,0,0}; 
	struct Map (*p)[N][N][N] = NULL;
    p = newmap;
    
    int revprop=10;
    if(ec==1){
    	revprop=99;
	}
	else if(ec==3){
		c_mine-=20;
	}	
    
	play1_set_mine(p,c_mine,N);//
	get_mine(p,N);
    p_b_nums(p,N,1);
    p_m_nums(p,N,1);
    p_resu(revprop,-1,-1);
    
    int click = 0;
    int rx=-1,ry=0,rz=0,rt=0;//out

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
		  					if(X<lx||Y<ly||X>lx-2+(N+1)*N*2||Y>ly+1+N*2){
								break;
							}
		  					right_key(p,lx,ly,X,Y,N,1);
		   					break;
          			case 2: //���
          				{
          					if(Y>25&&Y<28){
          						if(X>67&&X<78){
          							return MessageBox(NULL,"���˳ɹ�","goodbye",MB_OK);;
								}
							}
          					if(X<lx||Y<ly||X>lx-2+(N+1)*N*2||Y>ly+1+N*2){
								break;
							}
          					int u=X,v=Y;
          					if(left_key1(p,X,Y,N,&rx,&ry,&rz,&rt,&click)){ 
							  	if(ec==2){//1/2�������� 
							  		srand(time(NULL));
							  		if(rand()%2){
							  			play1_p_resu(revprop,lx+2*((u-lx)/2)/(N+1)*(N+1)+2*((u-lx)/2)%(N+1),ly+(v-ly)/(N+1)*(N+1)+(v-ly)%(N+1));
									  }
									else{
										p_resu(--revprop,lx+2*((u-lx)/2)/(N+1)*(N+1)+2*((u-lx)/2)%(N+1),ly+(v-ly)/(N+1)*(N+1)+(v-ly)%(N+1));
									}
								  } 
								else{
								  	p_resu(--revprop,lx+2*((u-lx)/2)/(N+1)*(N+1)+2*((u-lx)/2)%(N+1),ly+(v-ly)/(N+1)*(N+1)+(v-ly)%(N+1));
								}
          						if(ec==3&&revprop>=0){//��Ѱ��Χ7��
          							search(p,u,v,N,rx,ry,rz,rt);
								  }
          						p_b_nums(p,N,1);
    							p_m_nums(p,N,1);
          						if(revprop<0){
          							p_d_mine(p,N);
          							p_kout_xy(lx+2*rx*(N+1)+2*rz,ly+rt*(N+1)+ry,1);
          							return defeat(lx+2*((u-lx)/2)/(N+1)*(N+1)+2*((u-lx)/2)%(N+1),ly+(v-ly)/(N+1)*(N+1)+(v-ly)%(N+1))-6;
								  }
							  } 
							gtxy(76,2);
							printf("%3d",click);
		   					break;
						}
		  		}
			} 		 
		 	break; 
		}
		if(rx>=0&&newmap[rt][rx][ry][rz].show==1){
			p_kout_xy(lx+2*rx*(N+1)+2*rz,ly+rt*(N+1)+ry,0);
			return play1_victory(ec)-6;
		}
	}
	return 0;
}
void play1_p_resu(int resu,int x,int y){
	if(resu<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(18,4);
	printf("%2d",resu);
	if(x>=0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
		gtxy(x,y);
		printf("��");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int play1_victory(int ec){
	char rv[100]="REGAIN CONTROL\nCongratulations!\n";
	if(ec==1){
		strcat(rv,"     for<Ӣ����>\n");
	}
	else if(ec==2){
		strcat(rv,"     for<��ͽ>\n");
	}
	else if(ec==3){
		strcat(rv,"     for<����ʦ>\n");
	}
	return MessageBox(NULL,rv,"VICTORY",MB_YESNO);//Y6 N7
}
void play1_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��--------------------------------------------------------------------------------------��\n");
	int i;
	for(i=0;i<15;i++){
		printf(" ��                                                                                      ��\n");
	}
	printf("   ��������������������������������������������������������������������������������������  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("�˸�:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	printf("����ʮ����:"); 
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
	printf("״̬:");  
	gtxy(75,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("�������:");
	gtxy(67,26);
	printf("|����������|"); 
	gtxy(67,27);
	printf("| ��ǰ���� |");
	gtxy(67,28);
	printf(" ���������� "); 
}
int left_key1(struct Map (*p)[N][N][N],int x,int y,int Nc,int *rx,int *ry,int *rz,int *rt,int *cli){
	if(((x-lx)/2)%(Nc+1)==Nc||(y-ly)%(Nc+1)==Nc){
		return 0;
	}
	int i=((x-lx)/2)/(Nc+1),j=(y-ly)%(Nc+1),k=((x-lx)/2)%(Nc+1),t=(y-ly)/(Nc+1);
	if((*(*(*(*(p+t)+i)+j)+k)).show!=0){
		return 0;
	}
	*cli+=1;
	if(left_key1_event(p,i,j,k,t,Nc,rx,ry,rz,rt)){
		return 1;
	}
	p_b_nums(p,Nc,1);
	return 0;
}
int left_key1_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int *rx,int *ry,int *rz,int *rt){
	int sok = 0;
	if(c_blank==2*Nc*Nc*Nc){
		fir_pro(p,i,j,k,t,Nc);
		get_mine(p,Nc);
		sok = 1;
	}
	if((*(*(*(*(p+t)+i)+j)+k)).mine==1&&(*(*(*(*(p+t)+i)+j)+k)).show==0){
		(*(*(*(*(p+t)+i)+j)+k)).show=1;
		mr[t]++;
		return 1;
	}
	judge_board(p,i,j,k,t,Nc);
	if(sok){
		set_out_key(p,rx,ry,rz,rt,Nc);
		//gtxy(0,29);
		//printf("%3d %3d %3d %2d",*rx,*ry,*rz,*rt);
	}
	return 0;
}
void play1_set_mine(struct Map (*p)[N][N][N],int count,int Nc){
	int x,y,z,t;
	srand(time(NULL));
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		z = rand()%Nc;
		t = rand()%2;
		if((*(*(*(*(p+t)+x)+y)+z)).mine==0)
		{
			(*(*(*(*(p+t)+x)+y)+z)).mine = 1;
			count--;
		}
	}
}
void set_out_key(struct Map (*p)[N][N][N],int *x,int *y,int *z,int *t,int Nc){
	srand(time(NULL));
	for(;;){
		*x = rand()%Nc;
		*y = rand()%Nc;
		*z = rand()%Nc;
		*t = rand()%2;
		if((*(*(*(*(p+*t)+*x)+*y)+*z)).show==0&&(*(*(*(*(p+*t)+*x)+*y)+*z)).mine==0){
			break;
		}
	}	
}
void search(struct Map (*p)[N][N][N],int x,int y,int Nc,int rx,int ry,int rz,int rt){
	if(((x-lx)/2)%(Nc+1)==Nc||(y-ly)%(Nc+1)==Nc){
		return;
	}
	search_event(p,((x-lx)/2)/(Nc+1),(y-ly)%(Nc+1),((x-lx)/2)%(Nc+1),(y-ly)/(Nc+1),Nc,rx,ry,rz,rt);
}
void search_event(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc,int rx,int ry,int rz,int rt){
	if(x>0){
		search_judge(p,x-1,y,z,t,Nc,rx,ry,rz,rt);
	}
	if(x<Nc-1){
		search_judge(p,x+1,y,z,t,Nc,rx,ry,rz,rt);
	}
	if(y>0){
		search_judge(p,x,y-1,z,t,Nc,rx,ry,rz,rt);
	}
	if(y<Nc-1){
		search_judge(p,x,y+1,z,t,Nc,rx,ry,rz,rt);
	}
	if(z>0){
		search_judge(p,x,y,z-1,t,Nc,rx,ry,rz,rt);
	}
	if(z<Nc-1){
		search_judge(p,x,y,z+1,t,Nc,rx,ry,rz,rt);
	}
	search_judge(p,x,y,z,1-t,Nc,rx,ry,rz,rt);
}
void search_judge(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc,int rx,int ry,int rz,int rt){
	if((*(*(*(*(p+t)+x)+y)+z)).show==0){
		if((*(*(*(*(p+t)+x)+y)+z)).mine==1){
			p_cb_xy(lx+2*x*(Nc+1)+2*z,ly+t*(Nc+1)+y,3);
		}
		else{
			if(t==rt&&x==rx&&y==ry&&z==rz){
				p_cb_xy(lx+2*x*(Nc+1)+2*z,ly+t*(Nc+1)+y,1);
			}
			else{
				p_cb_xy(lx+2*x*(Nc+1)+2*z,ly+t*(Nc+1)+y,2);
			}
		}			
	}
}
void p_cb_xy(int x,int y,int color){
	switch(color){
		case 1:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			break;
		case 2:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			break;
		case 3:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			break;
	}
	gtxy(x,y);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_kout_xy(int x,int y,int i){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	if(i){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),78);
	}
	gtxy(x,y);
	printf("��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
