#include "yzetmb.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];

void entertainment2(){
	clean();
	gtxy(0,1); 		
	printf(" Administrator��\n"); 
	printf("   ��~�����ҵ�������\n");
	printf("   �ϴ�����лл����Ҷ���˿�����\n");
	printf("   ����������������˴��鷳\n");
	printf("   ��..������������\n");
	printf("   ǰ���ò�֪�����Ķ�����һ�Ŷ��򲭣�\n");
	printf("   ֱ�Ӵ������ҵ���ͼ�ղ����ϣ�\n");
	printf("   ���ҵ���ͼȫ����ɶ�ά��!!!\n");
	printf("   �����������Ҷ�ʧ����Щ��ͼ�������׵�λ��\n");
	printf("   û���׵ľ�ȷλ���Ҿ�û������Щ��ͼ��Ϸ������ð��������\n");
	printf("   ���������ذ���!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   ��ͼΪ6*6���\n");
	printf("   ����5���ף����������������ͼ��\n");
	printf("   ��Ҫ�����Ǹ�����ͼ�и��׿���ʾ�����֣�\n");
	printf("   �ƶϳ���5���׵���ȷλ��\n");
	printf("   ��Ȼ����Է��ģ���Щ�ײ��ᱻ����\n");
	printf("   ��������ֻ�гɹ�û��ʧ��\n");
	printf("   ��5���׵�λ��ͬʱ��ȷʱ���ɻ��ʤ��\n");
	printf("   ��Ҳ�����Լ�ѡ���뿪��ͼ��ʱ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);  
	printf("   ף�����~ �´μ��棬�����������㣬�ƺ���Ϊ<��>��!\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);  //����̨���ھ�� 
	hInput = GetStdHandle(STD_INPUT_HANDLE);   //�����豸��� 
	int rt,st=0;
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
							if(Y>21&&Y<24){
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
		if(play2()){
			return;
		}
	}	
}
int play2(){
	clean();
	play2_frame();
	
	lx=18;
	ly=9;
	c_mine = 5;
	
	struct Map newmap[N][N]={0,0,0}; 
	struct Map (*p)[N] = NULL;
    p = newmap;
    
	play2_set_mine(p,c_mine,N);//
	pr_mine_nums(p,N);

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
		  					if(X<lx||Y<ly||X>lx+N*2-1||Y>ly+N-1){
								break;
							}
		  					play2_right(p,(X-lx)/2,Y-ly);
		   					break;
          			case 2: //���
          					if(X>65&&X<89&&Y>0&&Y<3){
          						tc = 0;
          						Sleep(1000);
          						return 1;
					  		}
		   					break;
		  		}
			} 		 
		 	break; 
		}
		if(c_mine==0){
			if(check2(p,N)){
				tc = 0;
				return MessageBox(NULL,"ALL MINE FOUND\nCongratulations!\nagain?","VICTORY",MB_YESNO)-6; 
			}
		}
	}
	return 0;
}
void play2_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |         �˳�          ��\n");
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
	printf("ʱ��:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("������:");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("ʣ��ɱ�����:");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");  
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");	
	gtxy(68,11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("�~�~�~");
	gtxy(68,12);
	printf("�~�~�~");
	gtxy(68,13);
	printf("�~�~�~");
	gtxy(70,12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(16,4);
	printf(" 5");
	p_lm();
	gtxy(67,4);
	printf("<����>");
	gtxy(66,5);
	printf("1.����Ҽ�����");
	gtxy(66,6);
	printf("2.�����������Զ�����ʤ");
	gtxy(66,7);
	printf("  ������");
	gtxy(66,8);
	printf("3.�����׿��������ҳ���");
	gtxy(66,9);
	printf("  ���׵�λ�ò����");
	gtxy(67,15);
	printf("����Χ8���Ƿ����׼���");

}
void play2_set_mine(struct Map (*p)[N],int count,int Nc){
	int x,y;
	srand(time(NULL));
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		if((*(*(p+x)+y)).mine==0)
		{
			(*(*(p+x)+y)).mine = 1;
			count--;
		}
	}
	play2_get_mine(p,Nc);
}
void play2_get_mine(struct Map (*p)[N],int Nc){
	int i,j;	
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			(*(*(p+i)+j)).nums = play2_get_mine_nums(p,i,j,Nc);
		}
	}
}
int play2_get_mine_nums(struct Map (*p)[N],int x,int y,int Nc){
	int count=0;
	Nc--;
	if(x>0){
		count+=(*(*(p+x-1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x-1)+y-1)).mine;
		}
		if(y<Nc){
			count+=(*(*(p+x-1)+y+1)).mine;
		}
	}
	if(x<Nc){
		count+=(*(*(p+x+1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x+1)+y-1)).mine;
		}
		if(y<Nc){
			count+=(*(*(p+x+1)+y+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(p+x)+y-1)).mine;
	}
	if(y<Nc){
		count+=(*(*(p+x)+y+1)).mine;
	}
	return count;
}
void pr_mine_nums(struct Map (*p)[N],int Nc){
	int i,j;
	for(i=0;i<Nc;i++){
		gtxy(lx,ly+i);
		for(j=0;j<Nc;j++){
			printf("%2d",(*(*(p+j)+i)).nums);
		}
	}
}
void play2_right(struct Map (*p)[N],int x,int y){
	if(tc==0){
		tc = 1;
	}
	if(c_mine>0&&(*(*(p+x)+y)).show==0){
		(*(*(p+x)+y)).show = 2;
		gtxy(x*2+lx,y+ly);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),192);
		printf("%2d",(*(*(p+x)+y)).nums);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		c_mine--;
		p_lm();
	}
	else if((*(*(p+x)+y)).show==2){
		(*(*(p+x)+y)).show = 0;
		gtxy(x*2+lx,y+ly);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		printf("%2d",(*(*(p+x)+y)).nums);
		c_mine++;
		p_lm();
	}
}
void p_lm(){
	gtxy(30,4);
	printf("%2d",c_mine);
}
int check2(struct Map (*p)[N],int Nc){
	int i,j,c=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			if((*(*(p+i)+j)).show==2&&(*(*(p+i)+j)).mine==1){
				c++;
			}
		}
	}
	if(c==5){
		return 1;
	}
	return 0;
}
