/*
�汾��Ϣ
############################################################################################################
  VERSION1.0
    *������ɿ���άɨ�ף���άƽ��չ���������� 
    *�˻�����ʽ���ֽ̳̳�����
    *׷�ӳ���1��[������άɨ��/����������]������Ϸ������ 
    *��֧ѡ����
    
  VERSION1.0.1  win10��Ӧ-������ 
    *����������ݼ���ʽ����Ӧwin10�°�cmd 
############################################################################################################
  VERSION2.0
    *�Ż���׷�ӳ���1�������˸�2��<��ͽ>��������Ч{���׻�����ߺ��λ�ô���ʶ��13��ɫ -> 10��ɫ} 
    *�Ż���׷�ӳ���1���޸�ʧ���¼���Ч{�ؼ���λ�ô���ʶ��14��ɫ -> 78��ɫ}
    *�Ż�����Ϸʧ�ܺ���������λ��{�����<δչ��>�׿��Ƿ�Ϊ�� -> ��������<չ��>�׿��Ƿ�Ϊ��} 
    *׷�ӳ���2����άɨ������������Ϸ������
    *������ȫ�ֱ���tl�������и�ֵ��δ�������� 
############################################################################################################
  VERSION3.0
    *��������Ϸʧ�ܺ���������λ�ã���ӡλ���쳣���� 
	*׷�ӳ���7��˫��άɨ��[�໥�л�/����ʱ��]��Ϸ������
	*׷�ӳ���8�������άɨ��
	*����ϸ�ڵ��� 
############################################################################################################
  VERSION4.0
    *׷�ӳ���4��[�ȶ�����/�˻�����]˫ɫ����Ϸ������
    *�Ż���׷�ӳ���7���������{���ֻ�ʤ��ȼ�+1 -> ���ֻ�ʤ��ȼ��������������}
    *���������ֺ����оֲ�����δ����ʼֵ����
    *׷�ӳ���5���׸�����ս��Ϸ������ 
    *׷�ӳ���c1��һ�ʻ���Ϸ������
############################################################################################################
  VERSION5.0
    *׷�ӳ���6����ը�ɻ���Ϸ������
    *���䣺׷�ӳ���5���̳� 
    *���䣺׷�ӳ���5������2������3 
############################################################################################################
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<pthread.h>
#define N 6

HANDLE hInput; //��ȡ��׼�����豸��� 
INPUT_RECORD inRec;//�������ݼ�¼ 
DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
int Y,X;//X��Y������ 

int c_mine,c_blank;
int lx=0,ly=0;//��λ 
int tc=0,tl=0,tp=0;//��ʱ������ 
int mr[2];
int AIstep;

struct Map{
    int mine;//����λ��ͼ��<0F|1T> 
    int show;//չʾ����ͼ��<0δչ��|1չ��|2���>
    int nums;//��Χ����ͼ�� 
};

void gtxy(int x,int y);//����ƶ�
int mouseput();//������ж�
void HideCursor();//���ع��
void SetSize(short x,short y);//���ƴ��ڴ�С 

void set_mine(struct Map (*p)[N][N][N],int count,int Nc);//���� 
void get_mine(struct Map (*p)[N][N][N],int Nc);//����
int get_mine_nums(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//��ȡ����
int judge_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//����ж� 
void open_zero_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);
void open_t_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);
void show_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//���չ�� 

void p_s_xy(int x,int y);//��ӡ���� 
void p_m_xy(int x,int y);// ��ӡ��� 
void p_n_xy(int x,int y,int nums);//��ӡ���� 
void p_newmap(int lx,int ly,int Nc);//��ӡ��ͼ 
void p_m_nums(struct Map (*p)[N][N][N],int Nc,int me);//��ӡm1 m2
int count_mine(struct Map (*p)[N][N][N],int t,int Nc); 
void p_b_nums(struct Map (*p)[N][N][N],int Nc,int me);//��ӡb1 b2
int count_blank(struct Map (*p)[N][N][N],int t,int Nc);
void p_level(int le);//��ӡ�Ѷ�
void p_resu(int resu,int x,int y);//��ӡ���� 
void p_status();//��ӡ״̬
void p_d_mine(struct Map (*p)[N][N][N],int Nc);//ʧ�ܺ��ӡ�ױ� 

int victory(int le);//ʤ���¼� 
int defeat(int x,int y);//ʧ���¼� 
void *timer(void *arg);//��ʱ�� 
void timer_event(int t);

int game(int Nc,int M,int merge,int firstpro,int timelim,int signres,int reviveprop,int level);//ɨ�������� 
int left_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int fl,int me);//��� 
int left_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int fl);
void right_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int me);//�Ҽ� 
void right_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc);
void fir_pro(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//�״α��� 
int judge_sat(struct Map (*p)[N][N][N],int i,int j,int k,int x,int y,int z,int t,int Nc);
void change_loc(struct Map (*p)[N][N][N],int x,int y,int z,int t,int ax,int ay,int az,int Nc);

void clean();//�ֶ����� 
void progress();//�ܽ���
void frame();//��ӡ�����
int mode();//ģʽѡ�� 
void contract();//��Լ
void contract_event1(int *cp,int i);
int contract_event2(int *cp);
void contract_event3(int n);
void classic();//����
void course();//�̳�
int choice();//�̳�ѡ�� 
void go_on(int c,int x,int y,int ax,int ay);
void operation();
void o_1();
void o_2();
void o_3();
void rule();
void r_1();
void r_2();
void detail();
void d_1();
void d_2();
void d_3();
void d_clean();
void d_more(int s,int cd);
void entertainment1();//����1 
void et_event(int ec); 
int play1(int ec);//����1��Ϸ���� 
void play1_p_resu(int resu,int x,int y);
int play1_victory(int ec);
void play1_frame();
int left_key1(struct Map (*p)[N][N][N],int x,int y,int Nc,int *rx,int *ry,int *rz,int *rt,int *cli);
int left_key1_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int *rx,int *ry,int *rz,int *rt);
void play1_set_mine(struct Map (*p)[N][N][N],int count,int Nc);
void set_out_key(struct Map (*p)[N][N][N],int *x,int *y,int *z,int *t,int Nc);
void search(struct Map (*p)[N][N][N],int x,int y,int Nc,int rx,int ry,int rz,int rt);
void search_event(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc,int rx,int ry,int rz,int rt);
void search_judge(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc,int rx,int ry,int rz,int rt);
void p_cb_xy(int x,int y,int color);
void p_kout_xy(int x,int y,int i);
void entertainment();//����ģʽ
int e_choice();

void entertainment2();//����2 
int play2();//����2��Ϸ���� 
void play2_frame();
void play2_set_mine(struct Map (*p)[N],int count,int Nc);
void play2_get_mine(struct Map (*p)[N],int Nc);
int play2_get_mine_nums(struct Map (*p)[N],int x,int y,int Nc);
void pr_mine_nums(struct Map (*p)[N],int Nc);
void play2_right(struct Map (*p)[N],int x,int y);
void p_lm();
int check2(struct Map (*p)[N],int Nc);
void entertainment3();//����3
int play3();//����3��Ϸ����
void play3_frame();
void play3_set_mine(struct Map (*p)[4],int count,int Nc);
void play3_get_mine(struct Map (*p)[4],int Nc);
int play3_get_mine_nums(struct Map (*p)[4],int x,int y,int Nc);
void entertainment7();//����7
int play7();//����3��Ϸ����
int play7_event(struct Map (*p)[19],int lr,int Nc,int *revp);
void play7_set_mine(struct Map (*p)[19],int count,int Nc,int lr);
void empty_mine(struct Map (*p)[19],int Nc,int lr);
void play7_get_mine(struct Map (*p)[19]);
int play7_get_mine_nums(struct Map (*p)[19],int x,int y);
int play7_judge_board(struct Map (*p)[19],int x,int y,int Nc,int lr);
void play7_open_zero_board(struct Map (*p)[19],int x,int y,int Nc,int lr);
void play7_show_board(struct Map (*p)[19],int i,int j);
void play7_frame();
void p_play7_map(int lr,int Nc);
int play7_left_key(struct Map (*p)[19],int x,int y,int Nc,int lr);
void play7_fir_pro(struct Map (*p)[19],int x,int y,int Nc,int lr);
int play7_judge_sat(struct Map (*p)[19],int i,int j,int x,int y,int Nc);
void play7_change_loc(struct Map (*p)[19],int x,int y,int ax,int ay,int Nc,int lr);
void p7_m();
void p7_r(int r);
void p7_l(int l);
void p7_d_mine(struct Map (*p)[19]);
void entertainment8();//����8
int play8();//����8��Ϸ����
void play8_frame();
void play8_set_mine(struct Map (*p)[9],int count,int Nc);
void play8_get_mine(struct Map (*p)[9]);
int play8_get_mine_nums(struct Map (*p)[9],int x,int y);
int play8_judge_board(struct Map (*p)[9],int x,int y,int Nc);
void play8_open_zero_board(struct Map (*p)[9],int x,int y,int Nc);
void play8_show_board(struct Map (*p)[9],int i,int j);
int play8_left_key(struct Map (*p)[9],int x,int y,int Nc);
void play8_fir_pro(struct Map (*p)[9],int x,int y,int Nc);
int play8_judge_sat(struct Map (*p)[9],int i,int j,int x,int y);
void play8_change_loc(struct Map (*p)[9],int x,int y,int ax,int ay,int Nc);
void p8_d_mine(struct Map (*p)[9]);
void play8_right_key(struct Map (*p)[9],int x,int y);

void entertainment4();//����4
void e_4();
void e4_rule();
void e4_r1();
void e4_r2();
void e4_r3();
void e4_r4(); 
void p_choice_lv(int l);
void p_choice_od(int o);
int play4(int lv,int ord);//����4��Ϸ����
int play4_event(int (*p)[5],int x,int y,int op,int Nc);
void play4_max_judge(int (*p)[5],int Nc);
void play4_kaboom(int (*p)[5],int i,int j,int Nc,int v);
void p4_wmap(int (*p)[5],int Nc);
void p4_n_wb(int x,int y,int n);
void p_situ(int cb,int bl,int wh);
void p_lev(int lv);
void calcu_situ(int (*p)[5],int Nc);
void play4_frame();
int AI_Simple(int (*p)[5],int Nc);
int AI_Normal(int (*p)[5],int Nc); 
int AI_get_situ(int (*p)[5],int b[25],int Nc);
int AI_ALIce(int (*p)[5],int Nc);
int AI_Noah(int (*p)[5],int Nc);
void AI_event(int (*p)[5],int v);
void AI_Noah_laststep_pred(int (*p)[5],int Nc);
void AI_MinefieldCyberBrain_Kernel(int (*p)[5],int pn,unsigned long long *wi,unsigned long long *lo,unsigned long long *dr);
void AI_test_calcuall(int (*p)[5],int Nc);
void nbtest();
int SuperAI_BHR_MFCB_NOAHsARK(int (*p)[5],int Nc);
void entertainment5();//����5
void e_5();
int play5();//����5��Ϸ����
void play5_frame();
void p_ob_map(int (*p)[18]);
void p_c_choice(int v);
void p_c_n();
void p_tub(int tu);
void p_skills(int sk[5],int skco[5]);
int p5_check_c();
void p5_event(int (*p)[18],int x,int y);
void p5_event1(int (*p)[18],int x,int y);
void p5_event_c1(int (*p)[18],int x,int y);
void p5_event_c2(int (*p)[18],int x,int y);
void p5_event_c3(int (*p)[18],int x,int y);
void p5_event_c4(int (*p)[18],int x,int y);
void p5_event_c5(int (*p)[18],int x,int y);
void p_p5_event(int (*p)[18]);
void p5_event2(int (*p)[18],int x,int y);
void switch_tub(int (*p)[18]);
void first_tub(int (*p)[18]);
void switch_tub_cartoon(int (*p)[18]);
void p5_counting(int (*p)[18]);
void p_c_re();
void p5_skillscdd(int sk[5],int skco[5]);
void p5_skill1(int (*p)[18]);
void p5_skill1_cartoon(int (*p)[18]);
void p5_skill2(int (*p)[18]);
void p5_skill2_cartoon(int (*p)[18],int count);
void p5_skill3(int (*p)[18]);
int p5_result_v(int tu);
int p5_result_d(int tu);
void e5_course();//�̳� 
int e5_rule_choice();
void e5_operation();
void e5_rule();
void e5_skill();

void extra();//���� 
int extra_choice();
void entertainment_c1();//����1 
int e_c1_play();//����1��Ϸ���� 
void randomwalk(int bp[9][9]);
int check_rw_stop(int bp[9][9],int x,int y);
int check_rw_walk(int bp[9][9],int x,int y);
void e_c1_p_map(int bp[9][9]);
void e_c1_frame();
void e_c1_p_d(int nm);
int count_nm(int bp[9][9]);
int e_c1_left_event(int bp[9][9],int x,int y,int rx,int ry);
void entertainment6();//����6
void e_6();
void e6_course();
int e6_rule_choice();
void e6_operation();
void e6_debuff();
void e6_skill();
int play6();//����6��Ϸ����
int play6_game();
void p6_randboss();
void play6_frame();
void p_p6_emap();
void p_p6_wmap(int wp[10]);
int p6_left_event(int ep[5][5],int wp[10],int i,int rd[7]);
int p_p6_le_cartoon1(int ep[5][5],int rd[7]);
void p_p6_le_cartoon2(int ct,int rd[7]);
void p_p6_newHP();
void p_p6_HPdown_cartoon(int ct);
void p6_renew_ep(int ep[5][5]);
void p6_aeroset(int ep[5][5],int wp[10],int rd[7]);
void p6_aeroset1(int ep[5][5],int wp[10]);
void p6_aeroset2(int ep[5][5],int wp[10]);
void p6_aeroset3(int ep[5][5],int wp[10],int rd[7]);
void p6_aeroset4(int ep[5][5],int wp[10]);
void p6_aeroset5(int ep[5][5],int wp[10]);
void p_p6_c(int ds);
void p_p6_a();
void p6_debuff(int rd[7],int wp[10],int ds);
void p6_rebuff(int rd[7],int wp[10]);
void p_p6_debuff(int rd[7]);
void p_p6_skills(int scd[4],int rd3);
void p_p6_skill2(int ep[5][5]);
void p6_reskills(int scd[4]);
void p_p6_skill4();
int p6_result(int tu);

int main(){
	HideCursor();
	SetSize(92,30);
	for(;;){ 
		progress();
	}
	return 0;
} 
void gtxy(int x,int y){//����ƶ���X�����꣬Y�����ꡣ
	while(tp){
		Sleep(10);
	}
	COORD  coord;
	coord.X=x;
	coord.Y=y;
	HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼������
	SetConsoleCursorPosition(a,coord);//�Ա�׼����ľ��Ϊ�������ÿ���̨�������
}
void timer_event(int t){	
	COORD  coo;
	coo.X=15;
	coo.Y=2;
	HANDLE b=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(b,coo);
	printf("%4d",t);
}
int mouseput(){
  while(1)
  {
    COORD pos = {0,0};
    ReadConsoleInput(hInput,&inRec,1,&numRead);
    pos = inRec.Event.MouseEvent.dwMousePosition;
    Y = (int)pos.Y;
    X = (int)pos.X;
    if (inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==RIGHTMOST_BUTTON_PRESSED)  
      return 1;//����Ҽ�����
    if (inRec.EventType==MOUSE_EVENT&&inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)  
      return 2;//����������
  }
} 
void HideCursor(){  //���ع��                  
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); 
}
void SetSize(short x,short y){//����ͬ���Ļ������ʹ��ڴ�С
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
   	COORD pos = {x,y};
   	SMALL_RECT rc = {0,0,x-1,y-1};
   	SetConsoleWindowInfo(hOut,TRUE,&rc);
   	SetConsoleScreenBufferSize(hOut,pos);
}
void set_mine(struct Map (*p)[N][N][N],int count,int Nc){
	int x,y,z,c=count;
	srand(time(NULL));
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		z = rand()%Nc;
		if((*(*(*(*p+x)+y)+z)).mine==0)
		{
			(*(*(*(*p+x)+y)+z)).mine = 1;
			count--;
		}
	}
	while(c)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		z = rand()%Nc;
		if((*(*(*(*(p+1)+x)+y)+z)).mine==0)
		{
			(*(*(*(*(p+1)+x)+y)+z)).mine = 1;
			c--;
		}
	}
}
void get_mine(struct Map (*p)[N][N][N],int Nc){
	int i,j,k,t;
	for(t=0;t<2;t++){	
		for(i=0;i<Nc;i++){
			for(j=0;j<Nc;j++){
				for(k=0;k<Nc;k++){
					(*(*(*(*(p+t)+i)+j)+k)).nums = get_mine_nums(p,i,j,k,t,Nc);
				}
			}
		}
	}
}
int get_mine_nums(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	int count=0;
	Nc--;
	if(x>0){
		count+=(*(*(*(*(p+t)+x-1)+y)+z)).mine;
	}
	if(x<Nc){
		count+=(*(*(*(*(p+t)+x+1)+y)+z)).mine;
	}
	if(y>0){
		count+=(*(*(*(*(p+t)+x)+y-1)+z)).mine;
	}
	if(y<Nc){
		count+=(*(*(*(*(p+t)+x)+y+1)+z)).mine;
	}
	if(z>0){
		count+=(*(*(*(*(p+t)+x)+y)+z-1)).mine;
	}
	if(z<Nc){
		count+=(*(*(*(*(p+t)+x)+y)+z+1)).mine;
	}
	count+=(*(*(*(*(p+1-t)+x)+y)+z)).mine;
	return count;
}
int judge_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).show==1||(*(*(*(*(p+t)+x)+y)+z)).show==2){
		return 0;//��չ��||��� 
	}
	if((*(*(*(*(p+t)+x)+y)+z)).mine==1){
		return -1;//�� 
	}
	Nc--;
	if((*(*(*(*(p+t)+x)+y)+z)).nums==0){
		open_zero_board(p,x,y,z,t,Nc);
	}
	else{
		show_board(p,x,y,z,t,Nc);
	}
	open_t_board(p,x,y,z,1-t,Nc);
	return 0;	
}
void open_zero_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).show==0){
		show_board(p,x,y,z,t,Nc);	
		if((*(*(*(*(p+t)+x)+y)+z)).nums==0){
		
			if(x>0){
				open_zero_board(p,x-1,y,z,t,Nc);
			}
			if(x<Nc){
				open_zero_board(p,x+1,y,z,t,Nc);
			}
			if(y>0){
				open_zero_board(p,x,y-1,z,t,Nc);
			}
			if(y<Nc){
				open_zero_board(p,x,y+1,z,t,Nc);
			}
			if(z>0){
				open_zero_board(p,x,y,z-1,t,Nc);
			}
			if(z<Nc){
				open_zero_board(p,x,y,z+1,t,Nc);
			}
				open_zero_board(p,x,y,z,1-t,Nc);
		}
	}
}
void open_t_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).show==0&&(*(*(*(*(p+t)+x)+y)+z)).nums==0&&(*(*(*(*(p+t)+x)+y)+z)).mine==0){
		open_zero_board(p,x,y,z,t,Nc);
	}
}
void show_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	Nc++;
	(*(*(*(*(p+t)+x)+y)+z)).show = 1;
	p_n_xy(lx+2*x*(Nc+1)+2*z,ly+t*(Nc+1)+y,(*(*(*(*(p+t)+x)+y)+z)).nums);
	c_blank--;
}
void p_s_xy(int x,int y){
	gtxy(x,y);
	printf("�~");
}
void p_m_xy(int x,int y){
	gtxy(x,y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_n_xy(int x,int y,int nums){
	gtxy(x,y);
	printf("%2d",nums);
}
void p_newmap(int lx,int ly,int Nc){
	int i,j,k,t;
	for(t=0;t<2;t++){
		for(i=0;i<Nc;i++){
			for(j=0;j<Nc;j++){
				for(k=0;k<Nc;k++){
					p_s_xy(lx+2*((Nc+1)*j+k),ly+i+t*(Nc+1));
				}
			}
		}
	}
	gtxy(lx,ly+Nc);
	printf("--");
	for(i=0;i<Nc*(Nc+1)-3;i++){
		printf("  ");
	}
	printf("--");
}
void p_m_nums(struct Map (*p)[N][N][N],int Nc,int me){
	int m1=c_mine/2-count_mine(p,0,Nc)-mr[0],m2=c_mine/2-count_mine(p,1,Nc)-mr[1];
	if(me){
		if(m1+m2<0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		}
		gtxy(52,2);
		printf("%3d",m1+m2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		return;
	}
	if(m1<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(52,2);
	printf("%3d",m1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	if(m2<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(52,4);
	printf("%3d",m2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int count_mine(struct Map (*p)[N][N][N],int t,int Nc){
	int i,j,k,count=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			for(k=0;k<Nc;k++){
				if((*(*(*(*(p+t)+i)+j)+k)).show==2){
					count++;
				}				
			}
		}
	}
	return count;
}
void p_b_nums(struct Map (*p)[N][N][N],int Nc,int me){
	int b1 = count_blank(p,0,Nc),b2 = count_blank(p,1,Nc);
	if(me){
		gtxy(31,2);
		printf("%3d",b1+b2);
		return;
	}
	gtxy(31,2);
	printf("%3d",b1);
	gtxy(31,4);
	printf("%3d",b2);
}
int count_blank(struct Map (*p)[N][N][N],int t,int Nc){
	int i,j,k,count=0;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			for(k=0;k<Nc;k++){
				if((*(*(*(*(p+t)+i)+j)+k)).show!=1){
					count++;
				}				
			}
		}
	}
	return count;
}
void p_level(int le){
	if(le<2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	}
	else if(le<7){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	}
	else if(le<13){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	}
	else if(le<17){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(75,2);
	printf("%3d",le);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);	
}
void p_resu(int resu,int x,int y){
	if(resu<0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(18,4);
	printf("%4d",resu);
	if(x>=0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
		gtxy(x,y);
		printf("��");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_status(){
	tl = -2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gtxy(75,4);
	printf("��ʱ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_d_mine(struct Map (*p)[N][N][N],int Nc){
	int i,j,k,t;
	for(t=0;t<2;t++){
		for(i=0;i<Nc;i++){
			for(j=0;j<Nc;j++){
				for(k=0;k<Nc;k++){
					if((*(*(*(*(p+t)+i)+j)+k)).mine==1&&(*(*(*(*(p+t)+i)+j)+k)).show!=1){
						gtxy(lx+2*((Nc+1)*i+k),ly+j+t*(Nc+1));
						printf("��");
					}
				}
			}
		}
	}
}
int game(int Nc,int M,int merge,int firstpro,int timelim,int signres,int reviveprop,int level){
	clean();
	frame();
	
	lx=(92-Nc*(Nc+1)*2)/2+1;
	ly=7;
	c_blank = 2*Nc*Nc*Nc;
	c_mine = 20+M;
	mr[0]=0;
	mr[1]=0;
	
	p_newmap(lx,ly,Nc);
	struct Map newmap[2][N][N][N]={0,0,0}; 
	struct Map (*p)[N][N][N] = NULL;
    p = newmap;
    
    int revprop=3;
    if(reviveprop){
    	revprop=0;
	}
	tl = timelim;
    
	set_mine(p,c_mine/2,Nc);//
	get_mine(p,Nc);
    p_b_nums(p,Nc,merge);
    p_m_nums(p,Nc,merge);
    p_level(level);
    p_resu(revprop,-1,-1);
    
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
				if(X<lx||Y<ly||X>lx-2+(Nc+1)*Nc*2||Y>ly+1+Nc*2){
					break;
				}
		  		switch(rt){ 
		  			case 1: //�Ҽ� 
		  					if(signres){
		  						break;
							  }
		  					right_key(p,lx,ly,X,Y,Nc,merge);
		   					break;
          			case 2: //���
          				{
          					int u=X,v=Y;
          					if(left_key(p,lx,ly,X,Y,Nc,firstpro,merge)){    						
          						p_resu(--revprop,lx+2*((u-lx)/2)/(Nc+1)*(Nc+1)+2*((u-lx)/2)%(Nc+1),ly+(v-ly)/(Nc+1)*(Nc+1)+(v-ly)%(Nc+1));
          						p_b_nums(p,Nc,merge);
    							p_m_nums(p,Nc,merge);
          						if(revprop<0){
          							p_d_mine(p,Nc);
          							return defeat(lx+2*((u-lx)/2)/(Nc+1)*(Nc+1)+2*((u-lx)/2)%(Nc+1),ly+(v-ly)/(Nc+1)*(Nc+1)+(v-ly)%(Nc+1))-6;
								  }
							  }  
		   					break;
						}
		  		}
			} 		 
		 	break; 
		}
		if(c_blank==c_mine){
			return victory(level)-6;
		}
	}
	return 0;
}
/* 
  ά��   ���ʽ          ��ַ  ���� 
	x  ((x-lx)/2)%(Nc+1)  k z  !=Nc
	y  (y-ly)%(Nc+1)      j y  !=Nc
	z  ((x-lx)/2)/(Nc+1)  i x
	t  (y-ly)/(Nc+1)      t t
	
	lx+2*((x-lx)/2)/(Nc+1)*(Nc+1)+2*((x-lx)/2)%(Nc+1),ly+(y-ly)/(Nc+1)*(Nc+1)+(y-ly)%(Nc+1)
*/
int left_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int fl,int me){
	if(((x-lx)/2)%(Nc+1)==Nc||(y-ly)%(Nc+1)==Nc){
		return 0;
	}
	int i=((x-lx)/2)/(Nc+1),j=(y-ly)%(Nc+1),k=((x-lx)/2)%(Nc+1),t=(y-ly)/(Nc+1);
	if((*(*(*(*(p+t)+i)+j)+k)).show!=0){
		return 0;
	}
	if(left_key_event(p,i,j,k,t,Nc,fl)){
		return 1;
	}
	p_b_nums(p,Nc,me);
	return 0;
}
int left_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int fl){
	if(c_blank==2*Nc*Nc*Nc){
		if(fl==0){
			fir_pro(p,i,j,k,t,Nc);
			get_mine(p,Nc);
		}
		tc = 1;
	}
	if((*(*(*(*(p+t)+i)+j)+k)).mine==1&&(*(*(*(*(p+t)+i)+j)+k)).show==0){
		(*(*(*(*(p+t)+i)+j)+k)).show=1;
		mr[t]++;
		return 1;
	}
	judge_board(p,i,j,k,t,Nc);
	return 0;
}
void right_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int me){
	if(((x-lx)/2)%(Nc+1)==Nc||(y-ly)%(Nc+1)==Nc){
		return;
	}
	right_key_event(p,((x-lx)/2)/(Nc+1),(y-ly)%(Nc+1),((x-lx)/2)%(Nc+1),(y-ly)/(Nc+1),Nc);
	p_m_nums(p,Nc,me);
}
void right_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc){
	switch((*(*(*(*(p+t)+i)+j)+k)).show)
	{
		case 0:
			(*(*(*(*(p+t)+i)+j)+k)).show = 2;
			p_m_xy(lx+2*i*(Nc+1)+2*k,ly+t*(Nc+1)+j);
			break;
		case 1:
			break;
		case 2:
			(*(*(*(*(p+t)+i)+j)+k)).show = 0;
			p_s_xy(lx+2*i*(Nc+1)+2*k,ly+t*(Nc+1)+j);
			break;
	}
}
void fir_pro(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc){
	if((*(*(*(*(p+t)+x)+y)+z)).mine==1){
		change_loc(p,x,y,z,t,0,0,0,Nc);
	}
	if(x>0&&(*(*(*(*(p+t)+x-1)+y)+z)).mine==1){
		change_loc(p,x-1,y,z,t,1,0,0,Nc);
	}
	if(x<Nc-1&&(*(*(*(*(p+t)+x+1)+y)+z)).mine==1){
		change_loc(p,x+1,y,z,t,-1,0,0,Nc);
	}
	if(y>0&&(*(*(*(*(p+t)+x)+y-1)+z)).mine==1){
		change_loc(p,x,y-1,z,t,0,1,0,Nc);
	}
	if(y<Nc-1&&(*(*(*(*(p+t)+x)+y+1)+z)).mine==1){
		change_loc(p,x,y+1,z,t,0,-1,0,Nc);
	}
	if(z>0&&(*(*(*(*(p+t)+x)+y)+z-1)).mine==1){
		change_loc(p,x,y,z-1,t,0,0,1,Nc);
	}
	if(z<Nc-1&&(*(*(*(*(p+t)+x)+y)+z+1)).mine==1){
		change_loc(p,x,y,z+1,t,0,0,-1,Nc);
	}
	if((*(*(*(*(p+1-t)+x)+y)+z)).mine==1){
		change_loc(p,x,y,z,1-t,0,0,0,Nc);
	}	
}
int judge_sat(struct Map (*p)[N][N][N],int i,int j,int k,int x,int y,int z,int t,int Nc){
	if(i==x&&j==y&&(k==z-1||k==z+1||k==z)){
		return 0;
	}
	if(i==x&&k==z&&(j==y-1||j==y+1)){
		return 0;
	}
	if(k==z&&j==y&&(i==x-1||i==x+1)){
		return 0;
	}	
	if((*(*(*(*(p+t)+i)+j)+k)).mine==1){
		return 0;
	}
	return 1;
}
void change_loc(struct Map (*p)[N][N][N],int x,int y,int z,int t,int ax,int ay,int az,int Nc){
	int i,j,k,c=1;
	srand(time(NULL));
	while(c)
	{
		i = rand()%Nc;
		j = rand()%Nc;
		k = rand()%Nc;
		if(judge_sat(p,i,j,k,x+ax,y+ay,z+az,t,Nc))
		{
			(*(*(*(*(p+t)+i)+j)+k)).mine = 1;
			(*(*(*(*(p+t)+x)+y)+z)).mine = 0;
			c--;
		}
	}		
}
int victory(int le){
	tc = 0;
	if(tl<0){
		le+=tl;
	}
	tl = 0;
	char rv[100]="Contract Grade";
	//E0 D1-3 C4-6 B7-9 A10-12 S13-15 V16
	if(le==0){
		strcat(rv," - E\n");
	}
	else if(le>0&&le<4){
		strcat(rv," - D\n");
	}
	else if(le>3&&le<7){
		strcat(rv," - C\n");
	}
	else if(le>6&&le<10){
		strcat(rv," - B\n");
	}
	else if(le>9&&le<13){
		strcat(rv," - A\n");
	}
	else if(le>12&&le<16){
		strcat(rv," - S\n");
	}
	else if(le==16){
		strcat(rv," - V\n��ϲ��ϲ(*^��^*)\n˳����ҵ(��'��'��)\n�����ھְ�(*�R���Q)");
	}
	if(le!=16){
		strcat(rv,"��ϲ��໣��ò�����Ӯ��һ��~\n����һ�ְ�!");
	}	
	return MessageBox(NULL,rv,"VICTORY",MB_YESNO);//Y6 N7	 
}
int defeat(int x,int y){
	tc = 0;
	tl = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	gtxy(x,y);
	printf("��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	srand(time(NULL));
	char rv[100]="";
	switch(rand()%11){
		case 0:
			strcat(rv,"ʧ���ں󣬲�����������");
			break;
		case 1:
			strcat(rv,"ʧ�ܵ����£�����Ӧ����");
			break;
		case 2:
			strcat(rv,"�����ܷ���\n������û��ʧ�ܣ�ֻ�з���");
			break;
		case 3:
			strcat(rv,"ʧ�ܾ�������ɹ�Ӧ�����Ĵ���");
			break;
		case 4:
			strcat(rv,"��������ǳɹ���̤��ʯ\n�����ǰ��ʯ");
			break;
		case 5:
			strcat(rv,"ʧ�ܵý�ѵ���ɹ�����");
			break;
		case 6:
			strcat(rv,"ʧ��Ե�ں���ϸ��");
			break;
		case 7:
			strcat(rv,"���ڲ������ӵ�����˵\nû��ʧ�������");
			break;
		case 8:
			strcat(rv,"������ֹͣ����\n�������Զ������ʧ����");
			break;
		case 9:
			strcat(rv,"����ʧ�������Ӣ����������");
			break;
		case 10:
			strcat(rv,"ս����̫���ӣ���Ȼʧ��");
			break;
	}
	strcat(rv,"\n������һ��ô��");
	return MessageBox(NULL,rv,"DEFEAT",MB_YESNO);	 
}
void *timer(void *arg){
	int t;
	while(1)
        {
            t = 1;
            while(tc)
            {
            	Sleep(900);
            	tp=1;
            	Sleep(100);
            	timer_event(t);
            	tp=0;
                t+=1;
                if(tl==1&&t>301){
                	p_status();//���޸� 
				}
			}       
        }
}
void clean(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	int i;
	for(i=0;i<30;i++){
		gtxy(0,i);
		printf("                                                                                              ");
	}
}
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
void contract_event1(int *cp,int i){
	if(*(cp+i)==0){
		*(cp+i)=1;
		gtxy(14,2*i+5);
		printf("��");
	}
	else if(*(cp+i)==1){
		*(cp+i)=0;
		gtxy(14,2*i+5);
		printf("  ");
	}
	contract_event3(contract_event2(cp));
}
int contract_event2(int *cp){
	return *cp+*(cp+1)+*(cp+2)+2*(*(cp+3)+*(cp+4))+3*(*(cp+5)+*(cp+6)+*(cp+7));
}
void contract_event3(int n){
	if(n<2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	}
	else if(n<7){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	}
	else if(n<13){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	}
	else if(n<17){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	}
	gtxy(1,21);
	printf("��Լ�ȼ���%2d",n);	
	int i;
	gtxy(2,22);
	printf("                    \n");
	printf("                    ");
	gtxy(2,22);
	for(i=0;i<n/2;i++){
		if(i%2==0){
			printf("��");
		}
		else{
			printf("��");
		}		
	}
	if(n%2==1){
		if((n/2)%2==0){
			printf("��");
		}
		else{
			printf("��");
		}		
	}
	gtxy(2,23);	
	for(i=0;i<n/2;i++){
		if(i%2==1){
			printf("��");
		}
		else{
			printf("��");
		}		
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
}
void classic(){
	while(1){
		if(game(4,0,0,0,0,0,0,0)){
			return;
		}
	}	
}
void progress(){
	pthread_t tid; 
	int re;
	re = pthread_create(&tid,NULL,timer,NULL);//��ʱ���߳� 
	if(re!=0)
	{
		return; 
	}
	re = pthread_detach(tid);
	for(;;){
		switch(mode()){
			case 1:
				classic();
				break;
			case 2:
				contract();
				break;
			case 3:
				course();
				break;
			case 4:
				entertainment();
				break;
		}
	}
}
void frame(){
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
	printf("ʱ��:");
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
	printf("�Ѷ�:");
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
void go_on(int c,int x,int y,int ax,int ay){//c<0��|1��>
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
		  					if(c==0){
          						break;
							  }
							if(X>=x&&Y>=y&&X<=x+ax&&Y<=y+ay){
								return;
							}
		   					break;
          			case 2: //���
          					if(c==1){
          						break;
							  }
							if(X>=x&&Y>=y&&X<=x+ax&&Y<=y+ay){
								return;
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
} 
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
	printf(" ��ӭ�����������Ž̳�!           "); 
	gtxy(x,y++);
	printf(" ����һ��ʮ�ּ������ֵ���Ϸ��  ");
	gtxy(x,y++);
	printf(" ͨ��������Ҽ��������ȫ��������");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��--------------------------------------------------------------------------------------��\n");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("ʱ��:");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("�Ѷ�:");
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                     ");
	gtxy(x,y++);
	printf(" ���ǲ���������¼�˸þ��и�������                    "); 
	gtxy(x,y++);
	printf(" ����۲�������и������������ܹ��������յ�ǰ���ơ�  ");
	gtxy(x,y++);
	printf(" ������������������<�������>                    ");
	gtxy(x,y++);
	printf("                                                     ");
	gtxy(x,y++);
	printf("                              (�������Լ���)     ��");
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
	printf(" ������Ҫ������һ����Ϸ�л�������ͼ��       "); 
	gtxy(x,y++);
	printf("                                            ");
	gtxy(x,y++);
	printf("                     (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                            ");
	go_on(0,0,0,92,30);
	//1
	clean();
	x = 5;
	y = 8;
	gtxy(x,y++);
	printf("�~");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" �����һ���׿�                    "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,0,0,92,30);
	//2
	clean();
	x = 5;
	y = 6;
	gtxy(x,y++);
	printf("�~�~�~�~");
	gtxy(x,y++);
	printf("�~�~�~�~");
	gtxy(x,y++);
	printf("�~�~�~�~");
	gtxy(x,y++);
	printf("�~�~�~�~");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" ������һ��4*4����ͼ               "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (�������Լ���)     ��");
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
	printf(" �׿���Ψһ������������ͼ��      "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("            (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,0,0,92,30); 
	//4
	gtxy(7,8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("�~");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                   ");
	gtxy(x,y++);
	printf(" ��������������������ɫ���׿�    "); 
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("          (��������ɫ�׿�)     ��");
	gtxy(x,y++);
	printf("                                   ");
	go_on(0,7,8,1,0);
	//5
	clean();
	x = 5;
	y = 6;
	gtxy(x,y++);
	printf(" 0�~ 0 0");
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
	printf(" �������ͼ��չ���ˣ�              "); 
	gtxy(x,y++);
	printf(" ��ʣ��һ���׿�û���򿪣�          ");
	gtxy(x,y++);
	printf(" �һ���������������һ���ף�        ");
	gtxy(x,y++);
	printf(" ������һ����һ�����ɣ�          ");
	gtxy(x,y++);
	printf("                                   ");
	gtxy(x,y++);
	printf("          (����һ�ʣ���׿�)     ��");
	gtxy(x,y++);
	printf("                                   ");
	go_on(1,7,6,1,0);
	//6
	gtxy(7,6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("��");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                         ");
	gtxy(x,y++);
	printf(" �ܲ���                                  "); 
	gtxy(x,y++);
	printf(" �����Ǹ��׿鱻���Ϊ��ɫͼ�Σ�          ");
	gtxy(x,y++);
	printf(" �׿鱻���ʱ�����޷���������׿飬      ");
	gtxy(x,y++);
	printf(" ������ͨ���һ���ͼ�ν�����ԭ���׿�ͼ�Ρ�");
	gtxy(x,y++);
	printf("                                         ");
	gtxy(x,y++);
	printf("              (����һ�������׿�)     ��");
	gtxy(x,y++);
	printf("                                         ");
	go_on(1,7,6,1,0);
	//7
	gtxy(7,6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("�~");
	x = 15;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                         ");
	gtxy(x,y++);
	printf(" ������˰�                              "); 
	gtxy(x,y++);
	printf(" ͨ�����ʹ������Ҽ���                  ");
	gtxy(x,y++);
	printf(" ���ǿ��Կ��ٽ��������׵��׿���������  ");
	gtxy(x,y++);
	printf(" ��ֹ���Ȳ�����                        ");                         
	gtxy(x,y++);
	printf("                                         ");
	gtxy(x,y++);
	printf("                  (�������Լ���)     ��");
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
	printf("�~�~�~�~�~�~�~");
	gtxy(x,y++);
	printf("�~�~�~�~�~���~");
	gtxy(x,y++);
	printf("�~�~�~�~�~�~�~");
	gtxy(7,7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);	
	printf("��");
	gtxy(11,7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);	
	printf("��");
	x = 20;
	y = 6;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                        ");
	gtxy(x,y++);
	printf(" ����ߵ���ͼ����������ͬ��ɫ�Ĳ��     "); 
	gtxy(x,y++);
	printf(" ������Ϸ�г������ֲ��ʱ��             ");
	gtxy(x,y++);
	printf(" ��������ȵ�����!!                     "); 
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" ���ְײ��ͺ���ʱһ����������       "); 
	gtxy(x,y++);
	printf(" �����ȵ���ʱû������������           ");
	gtxy(x,y++);
	printf(" ���λ�ûᱻ�ϲ����档               "); 
	gtxy(x,y++);
	printf(" ���ͼ���޷������������Ҽ���         "); 
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Լ���)     ��");
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
	printf(" �����������Ѿ��˽�����Ϸ�Ĳ�������     "); 
	gtxy(x,y++);
	printf(" ��ȥѧϰһ����Ϸ�����~                ");
	gtxy(x,y++);
	printf("                                        ");
	gtxy(x,y++);
	printf("                 (�������Խ���)     ��");
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
	printf(" ��ӭ����������̳ܽ�!           "); 
	gtxy(x,y++);
	printf(" ����Ϸ����Ϊɨ�ף�              ");
	gtxy(x,y++);
	printf(" ��Ϊ�˽�����Ϸ�Ѷȣ�            ");
	gtxy(x,y++);
	printf(" �ʶ�ԭ��ɨ�׹�����м򻯡�      ");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (�������Լ���)     ��");
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
	printf(" ��ͼ��һ��2*4*4*4��������ͼ              "); 
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
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
	printf(" ͼʾ��ɫ����Ϊ��ά�ֽ���                 ");
	gtxy(x,y++);
	printf(" �����·�Ϊ����4*4*4����ά��ͼ            "); 
	gtxy(x,y++);
	printf("                                          ");
	gtxy(x,y++);
	printf("                   (�������Լ���)     ��");
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
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(14,2);
	printf("�~");
	gtxy(14,4);
	printf("�~");
	gtxy(12,3);
	printf("�~");
	gtxy(16,3);
	printf("�~");
	gtxy(4,3);
	printf("�~");
	gtxy(24,3);
	printf("�~");
	gtxy(14,8);
	printf("�~");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                           ");
	gtxy(x,y++);
	printf(" ���������׿�                                              ");
	gtxy(x,y++);
	printf(" ����ͳ������������ǰ���Լ�����άͬһλ�õ�����            "); 
	gtxy(x,y++);
	printf(" ��ͼ����ɫ�׿���������ȡ���ڻ�ɫ�׿��Ƿ�Ϊ��              ");
	gtxy(x,y++);
	printf(" ��Ȼ������Ϊ7                                             ");
	gtxy(x,y++);
	printf("                                                           ");
	gtxy(x,y++);
	printf("                                    (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                                           ");
	go_on(0,0,0,92,30);
	//4
	clean();
	p_newmap(2,2,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	gtxy(14,2);
	printf("�~");
	gtxy(2,10);
	printf("�~");
	gtxy(38,9);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(14,3);
	printf("�~");
	gtxy(12,2);
	printf("�~");
	gtxy(16,2);
	printf("�~");
	gtxy(4,2);
	printf("�~");
	gtxy(24,2);
	printf("�~");
	gtxy(14,7);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	gtxy(2,9);
	printf("�~"); 
	gtxy(4,10);
	printf("�~");
	gtxy(12,10);
	printf("�~");
	gtxy(2,5);
	printf("�~");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	gtxy(38,8);
	printf("�~");
	gtxy(38,10);
	printf("�~");
	gtxy(36,9);
	printf("�~");
	gtxy(28,9);
	printf("�~");
	gtxy(38,4);
	printf("�~");
	x = 2; 
	y = 12;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                           ");
	gtxy(x,y++);
	printf(" ���˹���                                                  ");
	gtxy(x,y++);
	printf(" λ��8�ǵ��׿���������Ϊ4                                  ");
	gtxy(x,y++);
	printf(" λ��12���ϵ��׿���������Ϊ5                               ");
	gtxy(x,y++);
	printf(" λ��6���ϵ��׿���������Ϊ6                                ");
	gtxy(x,y++);
	printf("                                                           ");
	gtxy(x,y++);
	printf("                                    (�������Լ���)     ��");
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
	printf(" ����������һ�²�����            "); 
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (�������Լ���)     ��");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
	//1
	clean();
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��--------------------------------------------------------------------------------------��\n");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("ʱ��:");
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(67,2);
	printf("�Ѷ�:");
	x = 5;
	y = 8;
	gtxy(x,y++);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	printf("                                                            ");
	gtxy(x,y++);
	printf(" ʱ�䣺�γɵ�ǰ��������ʱ������λ�룬��Χ1-9999             "); 
	gtxy(x,y++);
	printf(" ����ʮ���£���������ʱ��Ҫ�õ��Ĳ��ϡ�                     ");
	gtxy(x,y++);
	printf("             �����һ��С�Ĳȵ����ף����ý��ţ�             ");
	gtxy(x,y++);
	printf("             ֻҪ�����㹻������ʮ���£�����ܹ�����!        ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (�������Լ���)     ��");
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
	printf(" B1/B2����ͼ��δչ���׿������ͳ�ƣ����ֵΪȫδչ��ʱ      "); 
	gtxy(x,y++);
	printf("        B1Ϊ�ֽ����Ϸ�4*4*4��ͼͳ�ƣ�B2Ϊ�·�               ");
	gtxy(x,y++);
	printf(" M1/M2��ʣ��δ������������ֵΪȫδ���ʱ                  ");
	gtxy(x,y++);
	printf("        M1Ϊ�ֽ����Ϸ�4*4*4��ͼͳ�ƣ�M2Ϊ�·�               ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (�������Լ���)     ��");
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
	printf(" ע�����ȵ��ײ�ʹ������ʮ���¸����                         "); 
	gtxy(x,y++);
	printf("     ���׿�״̬��Ϊչ���������ӦB1/B2 -1                   ");
	gtxy(x,y++);
	printf("     �þ���Ϸ��������-1�������ӦM1/M2 -1                   ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (�������Լ���)     ��");
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
	printf(" �Ѷȣ���Լģʽ����ѡ��Լ�ȼ��ܺ�                           "); 
	gtxy(x,y++);
	printf("       ����ģʽ���Ѷ�Ϊ0                                    ");
	gtxy(x,y++);
	printf(" ״̬��һ��Ϊ<����>                                         ");
	gtxy(x,y++);
	printf("       ��Լģʽ�¸�����ѡ��Լ�����<��ʱ>                   ");
	gtxy(x,y++);
	printf("                                                            ");
	gtxy(x,y++);
	printf("                                     (�������Լ���)     ��");
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
	printf(" ��Ϸ����������                "); 
	gtxy(x,y++);
	printf(" ʣ�µľͿ����Լ�������~         ");
	gtxy(x,y++);
	printf(" GOOD LUCK                       ");
	gtxy(x,y++);
	printf("                                 ");
	gtxy(x,y++);
	printf("          (�������Խ���)     ��");
	gtxy(x,y++);
	printf("                                 ");
	go_on(0,0,0,92,30);
}
void detail(){
	clean();
	gtxy(0,1); 
	printf("��Լ���飺\n"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��              |               |               |               ��\n");
	printf(" ��              |               |               |               ��\n");
	printf(" ��              |               |               |               ��\n");
	printf(" ��--------------------------------------------------------------��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��------------------------|                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��                        |                                     ��\n");		
	printf(" ��------------------------|                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf(" ��                        |                                     ��\n");
	printf("   �������������������������������������������������������������� \n");
	gtxy(25,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("��");
	gtxy(40,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("����");
	gtxy(55,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("������");
	gtxy(6,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("������");
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
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
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
	printf("������+10");
	gtxy(4,12);
	printf("                     ");
	gtxy(4,12);
	printf("�ϲ��׿�������ͳ��");
	gtxy(4,16);
	printf("                     ");
	gtxy(4,16);
	printf("ȥ���״ε������");
	d_more(1,1);
}
void d_2(){
	gtxy(4,8);
	printf("                     ");
	gtxy(4,8);
	printf("��ά����+1��������+20");
	gtxy(4,12);
	printf("                     ");
	gtxy(4,12);
	printf("��ʱ300s");
	gtxy(4,16);
	printf("                     ");
	d_more(2,1);
}
void d_3(){
	gtxy(4,8);
	printf("                     ");
	gtxy(4,8);
	printf("��ά����+1��������+40");
	gtxy(4,12);
	printf("                     ");
	gtxy(4,12);
	printf("��ֹ����");
	gtxy(4,16);
	printf("                     ");
	gtxy(4,16);
	printf("ʧȥȫ������ʮ����");
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
					printf("<������+10>");
					gtxy(32,y++);
					printf("�þ���������������10");
					gtxy(32,y++);
					printf("��������ͼ������5");
					return;
				case 2:
					gtxy(34,y++);
					printf("<�ϲ��׿�������ͳ��>");
					gtxy(32,y++);
					printf("�þ���������ͼ��");
					gtxy(32,y++);
					printf(" δչ���׿������ϲ�չʾ");
					gtxy(32,y++);
					printf(" ��B1��B2ֵ��ӣ���B1����ʾ");
					gtxy(32,y++);
					gtxy(32,y++);
					printf(" �������ϲ�չʾ");
					gtxy(32,y++);
					printf(" ��M1��M2ֵ��ӣ���M1����ʾ");
					return;
				case 3:
					gtxy(34,y++);
					printf("<ȥ���״ε������>");
					gtxy(32,y++);
					printf("�ر�<��������>��");
					gtxy(32,y++);
					printf(" ����Ϸ�״ε��ʱ");
					gtxy(32,y++);
					printf(" ���׿���Χ������Ϊ0");
					gtxy(32,y++);
					printf("���״ε������Ϊ��");
					return;
			}
			break;
		}
		case 2:{
			switch(cd){
				case 1:
					gtxy(34,y++);
					printf("<��ά����+1��������+20>");
					gtxy(32,y++);
					printf("��ά��������1��");
					gtxy(32,y++);
					printf("����ͼ��Ϊ2*(N+1)*(N+1)*(N+1)");
					gtxy(32,y++);
					gtxy(32,y++);
					printf("�þ���������������20");
					gtxy(32,y++);
					printf("��������ͼ������10");
					return;
				case 2:
					gtxy(34,y++);
					printf("<��ʱ300s>");
					gtxy(32,y++);
					printf("�ڹ涨ʱ��300���������Ϸ");
					gtxy(32,y++);
					printf("��������涨ʱ��");
					gtxy(32,y++);
					printf("״̬�����Ϊ<��ʱ>");
					gtxy(32,y++);
					printf("����Ӱ����Ϸ����");
					gtxy(32,y++);
					printf("���<��ʱ>״̬�������Ϸ");
					gtxy(32,y++);
					printf("�ɻ��ʤ�������ú�ԼʧЧ");
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
					printf("<��ά����+1��������+40>");
					gtxy(32,y++);
					printf("��ά��������1��");
					gtxy(32,y++);
					printf("����ͼ��Ϊ2*(N+1)*(N+1)*(N+1)");
					gtxy(32,y++);
					gtxy(32,y++);
					printf("�þ���������������40");
					gtxy(32,y++);
					printf("��������ͼ������20");
					return;
				case 2:
					gtxy(34,y++);
					printf("<��ֹ����>");
					gtxy(32,y++);
					printf("No Flag!!!");
					gtxy(32,y++);
					printf("�����NFģʽ");
					gtxy(32,y++);
					printf("�����������������Ϸ");
					return;
				case 3:
					gtxy(34,y++);
					printf("<ʧȥȫ������ʮ����>");
					gtxy(32,y++);
					printf("Ŷ~");
					gtxy(32,y++);
					printf("�㲻�ܸ�����");
					gtxy(32,y++);
					printf("������ʮ��������Ϊ0");
					return;
			}
			break;
		}
	}	
}
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
				if(X<lx||Y<ly||X>lx-2+(N+1)*N*2||Y>ly+1+N*2){
					break;
				}
		  		switch(rmt){ 
		  			case 1: //�Ҽ� 
		  					right_key(p,lx,ly,X,Y,N,1);
		   					break;
          			case 2: //���
          				{
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
void entertainment3(){
	clean();
	gtxy(0,1); 			
	printf(" Ӱ�ӣ�\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("   ����ը����������������Ĺ����д����ƻ�\n");
	printf("   ���������⵽�ƻ�\n");
	printf("   �Զ��޸���...\n   ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);
	printf("ERROR");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
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
							if(Y>6&&Y<9){
								if(X>3&&X<12){
          							return;
								  }
								else if(X>34&&X<43){
									MessageBox(NULL,"No Available","ERROR",MB_OK);
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void V3_set_mine(struct Map (*p)[3][3],int count,int Nc);
void V3_get_mine(struct Map (*p)[3][3],int Nc);
int V3_get_mine_nums(struct Map (*p)[3][3],int x,int y,int z,int Nc);
void V3_set_mine(struct Map (*p)[3][3],int count,int Nc){//��άɨ��18����װ� 
	int x,y,z;
	srand(time(NULL));
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc;
		z = rand()%Nc;
		if((*(*(*(p+x)+y)+z)).mine==0)
		{
			(*(*(*(p+x)+y)+z)).mine = 1;
			count--;
		}
	}
	V3_get_mine(p,Nc);
}
void V3_get_mine(struct Map (*p)[3][3],int Nc){
	int i,j,k;	
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc;j++){
			for(k=0;k<Nc;k++){
				(*(*(*(p+i)+j)+k)).nums = V3_get_mine_nums(p,i,j,k,Nc);
			}
		}
	}
}
int V3_get_mine_nums(struct Map (*p)[3][3],int x,int y,int z,int Nc){
	int count=0;
	Nc--;
	if(x>0){
		count+=(*(*(*(p+x-1)+y)+z)).mine;
		if(y>0){
			count+=(*(*(*(p+x-1)+y-1)+z)).mine;
		}
		if(y<Nc){
			count+=(*(*(*(p+x-1)+y+1)+z)).mine;
		}
		if(z>0){
			count+=(*(*(*(p+x-1)+y)+z-1)).mine;
		}
		if(z<Nc){
			count+=(*(*(*(p+x-1)+y)+z+1)).mine;
		}
	}
	if(x<Nc){
		count+=(*(*(*(p+x+1)+y)+z)).mine;
		if(y>0){
			count+=(*(*(*(p+x+1)+y-1)+z)).mine;
		}
		if(y<Nc){
			count+=(*(*(*(p+x+1)+y+1)+z)).mine;
		}
		if(z>0){
			count+=(*(*(*(p+x+1)+y)+z-1)).mine;
		}
		if(z<Nc){
			count+=(*(*(*(p+x+1)+y)+z+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(*(p+x)+y-1)+z)).mine;
		if(z>0){
			count+=(*(*(*(p+x)+y-1)+z-1)).mine;
		}
		if(z<Nc){
			count+=(*(*(*(p+x)+y-1)+z+1)).mine;
		}
	}
	if(y<Nc){
		count+=(*(*(*(p+x)+y+1)+z)).mine;
		if(z>0){
			count+=(*(*(*(p+x)+y+1)+z-1)).mine;
		}
		if(z<Nc){
			count+=(*(*(*(p+x)+y+1)+z+1)).mine;
		}
	}
	if(z>0){
		count+=(*(*(*(p+x)+y)+z-1)).mine;
	}
	if(z<Nc){
		count+=(*(*(*(p+x)+y)+z+1)).mine;
	}
	return count;
}
void entertainment7(){
	clean();
	gtxy(0,1); 			
	printf(" �Σ�\n"); 
	printf("   �����Ƽ���������\n");
	printf("   ��ά�ռ�������ʱ�����ά�ռ�ļ���\n");
	printf("   ������������ʱ��Ķ�ά�ռ�������\n");
	printf("   �����һ����ʱ����������ֹ����ɨ��\n");
	printf("   �㣬\n");
	printf("   ��������һ��ô��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   ������վ���9*9 10�׶�άɨ��\n");
	printf("   ��ͼΪ9*19���\n");
	printf("   ��Ϊ��������9*10����壬��������10����\n");
	printf("   ÿ���һ���������1������ʮ����\n");
	printf("   <�������ع��������з���>\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);  
	printf("   ���ڣ��������ô��\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
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
		  			case 1: //�Ҽ� 
		   					break;
          			case 2: //���
							if(Y>14&&Y<17){
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
		if(play7()){
			return;
		}
	}	
}
int play7(){
	clean();
	play7_frame();
	
	lx = 18;
	ly = 9;
	tl = 2;
	int revprop = 1,level = 0;
	p7_l(level);
	mr[0] = 1;
	
	struct Map newmap[9][19]={0,0,0}; 
	struct Map (*p)[19] = NULL;
    p = newmap;
	while(play7_event(p,level%2,9,&revprop)){
		level += mr[0];
		p7_l(level);
		revprop++;
		if(level>9999){
			return MessageBox(NULL,"Sorry\nI need to have a rest\nLEVEL:MAX","Ohhhh",MB_OK);
		}
		else if(level>100){
			mr[0] = 1;
			if(revprop>20){
				mr[0]++;
			}
			if(revprop>35){
				mr[0]++;
			}
			if(revprop>50){
				mr[0]++;
			}
			if(revprop>100){
				mr[0]++;
			}
			gtxy(57,4);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			printf("%2d",mr[0]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		}
	}
	char rv[100]="GAME OVER!\nLEVEL:";
	char s[6];
	itoa(level,s,10);
	strcat(rv,s);
	return MessageBox(NULL,rv,"END",MB_RETRYCANCEL)-4;
}
int play7_event(struct Map (*p)[19],int lr,int Nc,int *revp){//lr<0����ͼ|1����ͼ> 
	c_blank = 90;
	c_mine = 10;
	
	p_play7_map(lr,Nc);
	play7_set_mine(p,c_mine,Nc,lr);
	p7_m();
	p7_r(*revp);
	
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
					  		{
          					if(X>65&&X<89&&Y>0&&Y<3){
          						//Sleep(100);
          						return 0;
					  		}
					  		if(X<lx+Nc*2*lr||Y<ly||X>lx+2*Nc+1+2*lr*Nc||Y>ly+Nc-1){
								break;
							}
							int u=(X-lx)/2,v=Y-ly;
							
          					if(play7_left_key(p,X,Y,Nc,lr)){
							    *revp-=mr[0];
								c_mine--;
								p7_m();					
          						p_resu(*revp,2*u+lx,v+ly);
          						if(*revp<0){
          							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
          							gtxy(2*u+lx,v+ly);
          							printf("��");
          							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          							p7_d_mine(p);
          							return 0;
								  }
							  }  
		   					break;
						   }
		  		}
			} 		 
		 	break; 
		}
		if(c_mine==c_blank){
			return 1;
		}
	}
	return 0;
}
void play7_set_mine(struct Map (*p)[19],int count,int Nc,int lr){
	empty_mine(p,Nc,lr);
	int x,y;
	srand(time(NULL));
	
	while(count)
	{
		x = rand()%Nc;
		y = rand()%Nc+lr*10;
		if((*(*(p+x)+y)).mine==0)
		{
			(*(*(p+x)+y)).mine = 1;
			count--;
		}
	}
	play7_get_mine(p);
}
void empty_mine(struct Map (*p)[19],int Nc,int lr){
	int i,j;
	int Ncc = Nc;
	Ncc+=lr*9+1;
	for(i=0;i<Nc;i++){
		for(j=0+lr*9;j<Ncc;j++){
			(*(*(p+i)+j)).mine = 0;
			(*(*(p+i)+j)).show = 0;
		}
	}
}
void play7_get_mine(struct Map (*p)[19]){
	int i,j;	
	for(i=0;i<9;i++){
		for(j=0;j<19;j++){
			(*(*(p+i)+j)).nums = play7_get_mine_nums(p,i,j);
		}
	}
}
int play7_get_mine_nums(struct Map (*p)[19],int x,int y){
	int count=0;
	if(x>0){
		count+=(*(*(p+x-1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x-1)+y-1)).mine;
		}
		if(y<18){
			count+=(*(*(p+x-1)+y+1)).mine;
		}
	}
	if(x<8){
		count+=(*(*(p+x+1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x+1)+y-1)).mine;
		}
		if(y<18){
			count+=(*(*(p+x+1)+y+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(p+x)+y-1)).mine;
	}
	if(y<18){
		count+=(*(*(p+x)+y+1)).mine;
	}
	return count;
}
int play7_judge_board(struct Map (*p)[19],int x,int y,int Nc,int lr){
	if((*(*(p+x)+y)).show==1||(*(*(p+x)+y)).show==2){
		return 0;//��չ��||��� 
	}
	if((*(*(p+x)+y)).mine==1){
		return -1;//��
	}
	Nc--;
	if((*(*(p+x)+y)).nums==0){
		play7_open_zero_board(p,x,y,Nc,lr);
	}
	else{
		play7_show_board(p,x,y);
	}
	return 0;
}
void play7_open_zero_board(struct Map (*p)[19],int x,int y,int Nc,int lr){
	if((*(*(p+x)+y)).show==0){
		play7_show_board(p,x,y);
		if((*(*(p+x)+y)).nums==0){
			if(x>0){
				play7_open_zero_board(p,x-1,y,Nc,lr);
				if(y>9*lr){
					play7_open_zero_board(p,x-1,y-1,Nc,lr);
				}
				if(y<9+lr*9){
					play7_open_zero_board(p,x-1,y+1,Nc,lr);
				}
			}
			if(x<Nc){
				play7_open_zero_board(p,x+1,y,Nc,lr);
				if(y>lr*9){
					play7_open_zero_board(p,x+1,y-1,Nc,lr);
				}
				if(y<9+lr*9){
					play7_open_zero_board(p,x+1,y+1,Nc,lr);
				}
			}
			if(y>lr*9){
				play7_open_zero_board(p,x,y-1,Nc,lr);
			}
			if(y<9+lr*9){
				play7_open_zero_board(p,x,y+1,Nc,lr);
			}
		}
	}
}
void play7_show_board(struct Map (*p)[19],int i,int j){
	(*(*(p+i)+j)).show = 1;
	c_blank--;
	p_n_xy(lx+2*j,ly+i,(*(*(p+i)+j)).nums);
}
void play7_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |       ��Ϸ��ֹ        ��\n");
	printf(" ��                     |                    |                   |-----------------------��\n");
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
	printf("�ȼ�:");
	gtxy(5,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	printf("����ʮ����:"); 
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("ʣ������:");
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("* ��ֹ����");
	gtxy(47,4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("* �������� 1");
	gtxy(67,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	gtxy(36,7);
	printf("��"); 
	gtxy(36,20);
	printf("��");  
	gtxy(75,5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void p_play7_map(int lr,int Nc){
	int i,j;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nc+1;j++){
			p_s_xy(lx+2*j+2*lr*Nc,ly+i);
		}
	}
}
int play7_left_key(struct Map (*p)[19],int x,int y,int Nc,int lr){
	int i=y-ly,j=(x-lx)/2;
	if(tl==2){
		if((*(*(p+i)+j)).nums!=0||(*(*(p+i)+j)).mine==1){
			play7_fir_pro(p,i,j,Nc,lr);
			play7_get_mine(p);
			}
		tl = 0;
	}
	if((*(*(p+i)+j)).show!=0){
		return 0;
	}
	if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show==0){
		(*(*(p+i)+j)).show=1;
		c_blank--;
		return 1;
	}
	play7_judge_board(p,i,j,Nc,lr);
	return 0;
}
void play7_fir_pro(struct Map (*p)[19],int x,int y,int Nc,int lr){
	if((*(*(p+x)+y)).mine==1){
		play7_change_loc(p,x,y,0,0,Nc,lr);
	}
	if(x>0){
		if((*(*(p+x-1)+y)).mine==1){
			play7_change_loc(p,x-1,y,1,0,Nc,lr);
		}
		if(y>0&&(*(*(p+x-1)+y-1)).mine==1){
			play7_change_loc(p,x-1,y-1,1,1,Nc,lr);
		}
		if(y<Nc-1&&(*(*(p+x-1)+y+1)).mine==1){
			play7_change_loc(p,x-1,y+1,1,-1,Nc,lr);
		}
	}
	if(x<Nc-1){
		if((*(*(p+x+1)+y)).mine==1){
			play7_change_loc(p,x+1,y,-1,0,Nc,lr);
		}
		
		if(y>0&&(*(*(p+x+1)+y-1)).mine==1){
			play7_change_loc(p,x+1,y-1,-1,1,Nc,lr);
		}
		if(y<Nc-1&&(*(*(p+x+1)+y+1)).mine==1){
			play7_change_loc(p,x+1,y+1,-1,-1,Nc,lr);
		}
	}
	if(y>0&&(*(*(p+x)+y-1)).mine==1){
		play7_change_loc(p,x,y-1,0,1,Nc,lr);
	}
	if(y<Nc-1&&(*(*(p+x)+y+1)).mine==1){
		play7_change_loc(p,x,y+1,0,-1,Nc,lr);
	}
}
int play7_judge_sat(struct Map (*p)[19],int i,int j,int x,int y,int Nc){
	if((i==x||i==x+1||i==x-1)&&(j==y||j==y+1||j==y-1)){
		return 0;
	}	
	if((*(*(p+i)+j)).mine==1){
		return 0;
	}
	return 1;
}
void play7_change_loc(struct Map (*p)[19],int x,int y,int ax,int ay,int Nc,int lr){
	int i,j,c=1;
	srand(time(NULL));
	while(c)
	{
		i = rand()%Nc;
		j = rand()%Nc;
		if(play7_judge_sat(p,i,j,x+ax,y+ay,Nc))
		{
			(*(*(p+i)+j)).mine = 1;
			(*(*(p+x)+y)).mine = 0;
			c--;
		}
	}		
}
void p7_m(){
	gtxy(36,4);
	printf("%2d",c_mine);
}
void p7_r(int r){
	gtxy(18,4);
	printf("%4d",r);
}
void p7_l(int l){
	gtxy(18,2);
	printf("%4d",l);
}
void p7_d_mine(struct Map (*p)[19]){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<19;j++){
			if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show!=1){
				gtxy(lx+2*j,ly+i);
				printf("��");
			}
		}
	}
}
void entertainment8(){
	clean();
	gtxy(0,1); 		
	printf(" �Σ�\n");
	printf("   ������Ŀǰ������\n");
	printf("   Ҫ���������������ܱ��������״���ĸ�άɨ��\n");
	printf("   ʵ���ǽ������Ŵ粽����\n");
	printf("   ����ܿ�ͽ�̮����\n");
	printf("   �Ὣ�������֮��\n");
	printf("   ��ӡ�����һ������������\n");
	printf("   ������δ��ĳһ�죬��ӡ�ᱻ�ٴ�����\n");
	printf("   �����ܹ����ܳ������Ӵ������\n");
	printf("   �������\n");
	printf("   ֻ������\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   ������򵥵�9*9 10�׶�άɨ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   �ܸ����ܹ�������\n");
	printf("   �����ˣ��ҵ����� >>\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
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
							if(Y>15&&Y<18){
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
		if(play8()){
			return;
		}
	}	
}
int play8(){	
	lx=18;
	ly=9;
	c_mine = 10;
	c_blank = 81;
	struct Map newmap[9][9]={0,0,0}; 
	struct Map (*p)[9] = NULL;
    p = newmap;
    int c_resj = c_mine;
    
	clean();
    play8_frame();
	play8_set_mine(p,c_mine,9);//

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
				if(X<lx||Y<ly||X>lx+17||Y>ly+8){
					break;
				}
		  		switch(rmt){ 
		  			case 1: //�Ҽ�
		  					play8_right_key(p,X,Y);
		  					gtxy(33,4);
		  					printf("%3d",c_mine);
		   					break;
          			case 2: //���
					  {
							int u=(X-lx)/2,v=Y-ly;
          					if(play8_left_key(p,X,Y,9)){
          						p8_d_mine(p);
          						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
          						gtxy(2*u+lx,v+ly);
          						printf("��");
          						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
          						tc = 0;
          						return MessageBox(NULL,"��ô��Ҳ���䣿\n�ٸ���λ����\nһ��ҪӮ��!","DEFEAT",MB_YESNO)-6;
							}  
		   					break;
		   				}
				}
			} 		 
		 	break; 
		}
		if(c_blank==c_resj){
			tc = 0;
			return MessageBox(NULL,"Ah, Minesweeper, now farewell, adieu. ","MISSION COMPLETED",MB_OK);
		}
	}
	tc = 0;
	return 0;
}
void play8_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |                       ��\n");
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
	printf("ʣ�� �� :");	
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬:");  
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gtxy(16,4);
	printf(" 10");
	gtxy(33,4);
	printf("%3d",c_mine);
	int j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			p_s_xy(lx+2*j,ly+i);
		}
	}
}
void play8_set_mine(struct Map (*p)[9],int count,int Nc){
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
	play8_get_mine(p);
}
void play8_get_mine(struct Map (*p)[9]){
	int i,j;	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			(*(*(p+i)+j)).nums = play8_get_mine_nums(p,i,j);
		}
	}
}
int play8_get_mine_nums(struct Map (*p)[9],int x,int y){
	int count=0;
	if(x>0){
		count+=(*(*(p+x-1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x-1)+y-1)).mine;
		}
		if(y<8){
			count+=(*(*(p+x-1)+y+1)).mine;
		}
	}
	if(x<8){
		count+=(*(*(p+x+1)+y)).mine;
		if(y>0){
			count+=(*(*(p+x+1)+y-1)).mine;
		}
		if(y<8){
			count+=(*(*(p+x+1)+y+1)).mine;
		}
	}
	if(y>0){
		count+=(*(*(p+x)+y-1)).mine;
	}
	if(y<8){
		count+=(*(*(p+x)+y+1)).mine;
	}
	return count;
}
int play8_judge_board(struct Map (*p)[9],int x,int y,int Nc){
	if((*(*(p+x)+y)).show==1||(*(*(p+x)+y)).show==2){
		return 0;//��չ��||��� 
	}
	if((*(*(p+x)+y)).mine==1){
		return -1;//��
	}
	Nc--;
	if((*(*(p+x)+y)).nums==0){
		play8_open_zero_board(p,x,y,Nc);
	}
	else{
		play8_show_board(p,x,y);
	}
	return 0;
}
void play8_open_zero_board(struct Map (*p)[9],int x,int y,int Nc){
	if((*(*(p+x)+y)).show==0){
		play8_show_board(p,x,y);
		if((*(*(p+x)+y)).nums==0){
			if(x>0){
				play8_open_zero_board(p,x-1,y,Nc);
				if(y>0){
					play8_open_zero_board(p,x-1,y-1,Nc);
				}
				if(y<8){
					play8_open_zero_board(p,x-1,y+1,Nc);
				}
			}
			if(x<Nc){
				play8_open_zero_board(p,x+1,y,Nc);
				if(y>0){
					play8_open_zero_board(p,x+1,y-1,Nc);
				}
				if(y<8){
					play8_open_zero_board(p,x+1,y+1,Nc);
				}
			}
			if(y>0){
				play8_open_zero_board(p,x,y-1,Nc);
			}
			if(y<8){
				play8_open_zero_board(p,x,y+1,Nc);
			}
		}
	}
}
void play8_show_board(struct Map (*p)[9],int i,int j){
	(*(*(p+i)+j)).show = 1;
	c_blank--;
	p_n_xy(lx+2*j,ly+i,(*(*(p+i)+j)).nums);
}
int play8_left_key(struct Map (*p)[9],int x,int y,int Nc){
	int i=y-ly,j=(x-lx)/2;
	if(c_blank==81){
		if((*(*(p+i)+j)).nums!=0||(*(*(p+i)+j)).mine==1){
			play8_fir_pro(p,i,j,Nc);
			play8_get_mine(p);
			}
		tc = 1;
	}
	if((*(*(p+i)+j)).show!=0){
		return 0;
	}
	if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show==0){
		return 1;
	}
	play8_judge_board(p,i,j,Nc);
	return 0;
}
void play8_fir_pro(struct Map (*p)[9],int x,int y,int Nc){
	if((*(*(p+x)+y)).mine==1){
		play8_change_loc(p,x,y,0,0,Nc);
	}
	if(x>0){
		if((*(*(p+x-1)+y)).mine==1){
			play8_change_loc(p,x-1,y,1,0,Nc);
		}
		if(y>0&&(*(*(p+x-1)+y-1)).mine==1){
			play8_change_loc(p,x-1,y-1,1,1,Nc);
		}
		if(y<Nc-1&&(*(*(p+x-1)+y+1)).mine==1){
			play8_change_loc(p,x-1,y+1,1,-1,Nc);
		}
	}
	if(x<Nc-1){
		if((*(*(p+x+1)+y)).mine==1){
			play8_change_loc(p,x+1,y,-1,0,Nc);
		}
		
		if(y>0&&(*(*(p+x+1)+y-1)).mine==1){
			play8_change_loc(p,x+1,y-1,-1,1,Nc);
		}
		if(y<Nc-1&&(*(*(p+x+1)+y+1)).mine==1){
			play8_change_loc(p,x+1,y+1,-1,-1,Nc);
		}
	}
	if(y>0&&(*(*(p+x)+y-1)).mine==1){
		play8_change_loc(p,x,y-1,0,1,Nc);
	}
	if(y<Nc-1&&(*(*(p+x)+y+1)).mine==1){
		play8_change_loc(p,x,y+1,0,-1,Nc);
	}
}
int play8_judge_sat(struct Map (*p)[9],int i,int j,int x,int y){
	if((i==x||i==x+1||i==x-1)&&(j==y||j==y+1||j==y-1)){
		return 0;
	}	
	if((*(*(p+i)+j)).mine==1){
		return 0;
	}
	return 1;
}
void play8_change_loc(struct Map (*p)[9],int x,int y,int ax,int ay,int Nc){
	int i,j,c=1;
	srand(time(NULL));
	while(c)
	{
		i = rand()%Nc;
		j = rand()%Nc;
		if(play8_judge_sat(p,i,j,x+ax,y+ay))
		{
			(*(*(p+i)+j)).mine = 1;
			(*(*(p+x)+y)).mine = 0;
			c--;
		}
	}		
}
void p8_d_mine(struct Map (*p)[9]){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if((*(*(p+i)+j)).mine==1&&(*(*(p+i)+j)).show!=1){
				gtxy(lx+2*j,ly+i);
				printf("��");
			}
		}
	}
}
void play8_right_key(struct Map (*p)[9],int x,int y){
	int i=y-ly,j=(x-lx)/2; 
	switch((*(*(p+i)+j)).show)
	{
		case 0:
			(*(*(p+i)+j)).show = 2;
			p_m_xy(lx+2*j,ly+i);
			c_mine--;
			break;
		case 1:
			break;
		case 2:
			(*(*(p+i)+j)).show = 0;
			p_s_xy(lx+2*j,ly+i);
			c_mine++;
			break;
	}
}
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
void AI_test_calcuall(int (*p)[5],int Nc){//�����Ӻ��� 
	srand(time(NULL));	
	int cache[25] = {0};//��¼�ո�λ�� 
	int comput_result[25] = {0};//��¼�����������Ž�� []=cache�±� 	
	AI_get_situ(p,cache,Nc);//��ǰ����
	int buffer = c_blank;//��ǰ�ո�����	
	int calcu_mod[5][5] = {0};//��ǰ��ͼ(��ʼ״̬)
	int (*q)[5] = NULL;
    q = calcu_mod;    
    unsigned long long wi,lo,dr;
    int i;//iѭ�� 
    for(i=0;i<buffer;i++){
    	wi=0;
		lo=0;
		dr=0;
		printf("[%d]:",i);
    	memcpy(q,p,25*sizeof(int));
    	if(play4_event(q,cache[i]/5,cache[i]%5,-1,5)){
    		calcu_situ(q,5);
    		AIstep--;
    		c_mine--;
    		AI_MinefieldCyberBrain_Kernel(q,1,&wi,&lo,&dr);
    		AIstep++;
    		c_mine++;
		}
		printf("%d:%d,%lld,%lld,%lld\n",i,cache[i],wi,lo,dr);
		//break;
	}
}
void nbtest(){//����ȫö�ٲ��� 
	c_blank = 25;//�ո�
	mr[0] = 0;//����
	mr[1] = 0;//����
	c_mine = 49;//����
	AIstep = 7; //7����  8���� 	
	//int situ[3] = {c_blank,0,0};//0-�ո� 1-���� 2-���� 
	/*int newmap[5][5] = {{2,0,1,1,1}, 
						{1,-1,-1,-1,-1},			
						{2,-1,0,0,0},			
						{2,-1,0,0,0},
						{2,0,1,1,1}};*/
	int newmap[5][5] = {{0,0,1,0,0},
						{0,0,1,0,0},			
						{1,1,1,1,1},			
						{0,0,1,0,0},
						{0,0,1,0,0}};//>0=����  <0=���� 
	int (*p)[5] = NULL;
    p = newmap;
    AI_test_calcuall(p,5);
    return;
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
void e5_o1();
void e5_o2();
void e5_o3();
void e5_o4();
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
void e5_skill_board();
void p_e5_skillc(int s);
void p_e5_skillc_detail(int s);
void p_e5_skillc_clean();
void p_e5_skillc_demo(int s);
void p_e5_skill1_demo();
void p_e5_skill1_boardset(int (*p)[18]);
void p_e5_skill2_demo();
void p_e5_skill3_demo();
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
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  ");	
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
	printf(" ��                     |                                                |---------------��\n");
	printf(" ��                     |                                                |               ��\n");
	printf(" ��                     |                                                |               ��\n");
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
void extra(){//
	for(;;){
		switch(extra_choice()){
			case 0:
				return;
			case 1:
				entertainment_c1();
				break;
			case 2:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
			case 3:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
			case 4:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
			case 5:
				MessageBox(NULL,"No Available","ERROR",MB_OK);
				break;
		}
	}
}
int extra_choice(){// 
	clean();
	gtxy(0,1); 	
	printf("  |��������|\n"); 
	printf("  | ������ |\n"); 
	printf("   ��������       \n"); 
	printf("    �x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf("  ��                      ��\n");
	printf("  ��   �����ĵ�ը���ˡ�   ��\n");
	printf("  ��xxxxxxxxxxxxxxxxxxxxxx��\n");
	printf("  ��                      ��\n");
	printf("  ��  �� ����!            ��\n");
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  ��                  ��\n");	
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  ��                  ��\n");
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  ��                  ��\n");
	printf("  ��----------------------��\n");
	printf("  ��                      ��\n");
	printf("  ��  ��                  ��\n");
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
								if(Y==8||Y==9){
									return 1;
								}
								else if(Y==11||Y==12){
									return 2;
								}
								else if(Y==14||Y==15){
									return 3;
								}
								else if(Y==17||Y==18){
									return 4;
								}
								else if(Y==20||Y==21||Y==22){
									return 5;
								}
							}		  
		   					break; 
		  		}
			} 		 
		 	break;
		}
	}
}
void entertainment_c1(){
	clean();
	gtxy(0,1); 			
	printf(" Ӱ�ӣ�\n");
	printf("   ը���������������ս���д��ȫ��\n");
	printf("   �����Ų�æ��̤�����ӳ�����ĵ�·\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);  
	printf("   ����ը�����ҵ�һ���뿪�ĵ�·��\n");
	printf("   ���̸����\n");
	printf("   ÿ������ֻ�ܾ���һ��\n");
	printf("   ��һ���������а׸��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("   HELP!!\n\n");
	printf("   |��������|                     |��������|\n"); 
	printf("   | ������ |                     | ��ʼ ��|\n");
	printf("    ��������                       �������� \n"); 
	
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
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
							if(Y>9&&Y<12){
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
		if(e_c1_play()){
			return;
		}
	}	
}
int e_c1_play(){
	lx=18;
	ly=9;	
	int nm = 9,rx = 4,ry = 4;
	int bmap[9][9] = {0};
	int nmap[9][9] = {0};
    
	clean();
	e_c1_frame();
	randomwalk(bmap);
	memcpy(nmap,bmap,81*sizeof(int));
	nmap[rx][ry] = 2;
	e_c1_p_map(nmap);
	nm = count_nm(nmap);
	e_c1_p_d(nm);
	
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
          					if(X>65&&X<89){
          						if(Y==4){
          							tc = 0;
          							rx = 4;
          							ry = 4;
          							memcpy(nmap,bmap,81*sizeof(int));
          							nmap[rx][ry] = 2;
									e_c1_p_map(nmap);
									nm = count_nm(nmap);
									e_c1_p_d(nm);
								  }
								else if(Y==6){
									tc = 0;
									return MessageBox(NULL,"Ah, you lost. \nAgain?","MISSION FAILED",MB_YESNO)-6;
								}
								break;
							}
							if(X>=lx&&Y>=ly&&X<=lx+17&&Y<ly+9){
								int rrx = Y-ly,rry = (X-lx)/2;
								if(e_c1_left_event(nmap,rrx,rry,rx,ry)){
									rx = rrx;
									ry = rry;
									e_c1_p_map(nmap);
									nm = count_nm(nmap);
									e_c1_p_d(nm);
									break;
								}
							}
		   					break;
				}
			} 		 
		 	break; 
		}
		if(nm == 0){
			tc = 0;
			return MessageBox(NULL,"Ah, you win. \nAgain?","MISSION COMPLETED",MB_YESNO)-6;
		}
	}
	return 0;
}
void randomwalk(int bp[9][9]){
	int i= 4,j = 4;
	if(bp[i][j]==0){
		bp[i][j] = 1;
	}
	srand(time(NULL));	
	for(;;){
		int d = rand()%4;
		int dx = (d-1)%2,dy = (d-2)%2;
		/*
		rand()%4  0  1  2  3
		(d-1)%2  -1  0  1  0
		(d-2)%2   0 -1  0  1
		*/
		if(check_rw_walk(bp,i+dx,j+dy)){
			i += dx;
			j += dy;
			bp[i][j] = 1;
		}
		if(check_rw_stop(bp,i,j)){
			return;
		}
	}
}
int check_rw_stop(int bp[9][9],int x,int y){
	if(x>0){
		if(bp[x-1][y]==0){
			return 0;
		}
	}
	if(y>0){
		if(bp[x][y-1]==0){
			return 0;
		}
	}
	if(x<8){
		if(bp[x+1][y]==0){
			return 0;
		}
	}
	if(y<8){
		if(bp[x][y+1]==0){
			return 0;
		}
	}
	return 1;
}
int check_rw_walk(int bp[9][9],int x,int y){
	if(x>=0&&x<9&&y>=0&&y<9){
		if(bp[x][y]==0){
			return 1;
		}
	}
	return 0;
}
void e_c1_p_map(int bp[9][9]){
	int i,j;
	for(i=0;i<9;i++){
		gtxy(lx,ly+i);
		for(j=0;j<9;j++){
			if(bp[i][j]==1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			}
			else if(bp[i][j]==2){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
			}
			else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
			}
			printf("�~");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void e_c1_frame(){
	gtxy(0,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);                           
	printf("   �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x  \n");	
	printf(" ��                     |                    |                   |                       ��\n");
	printf(" ��                     |                    |                   |        *����          ��\n");
	printf(" ��                     |                    |                   |-----------------------��\n");
	printf(" ��                     |                    |                   |     ���¿�ʼ����      ��\n");
	printf(" ��                     |                    |                   |-----------------------��\n");
	printf(" ��--------------------------------------------------------------|       ��ֹ����        ��\n");
	printf(" ��                                                              |-----------------------��\n");
	printf(" ��                                                              |                       ��\n");
	int i;
	for(i=0;i<13;i++){
		printf(" ��                                                              |                       ��\n");
	}
	printf("   ��������������������������������������������������������������������������������������  ");
	gtxy(5,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	printf("ʱ�䣺");
	gtxy(26,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("ʣ��ո���:");
	gtxy(47,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("״̬��");
	gtxy(55,2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	printf("����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void e_c1_p_d(int nm){
	gtxy(30,4);
	printf("%2d",nm);
}
int count_nm(int bp[9][9]){
	int nm = 0,i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(bp[i][j]==1){
				nm++;
			}
		}
	}
	return nm;
}
int e_c1_left_event(int bp[9][9],int x,int y,int rx,int ry){
	if(bp[x][y]==0){
		return 0;
	}
	if(x==4&&y==4){	
		return 0;
	}
	if(((x-rx)==0&&(y-ry)<2&&(y-ry)>-2)||(y-ry)==0&&((x-rx)<2&&(x-rx)>-2)){
		if(tc==0){
			tc = 1;
		}
		bp[rx][ry] = 0;
		bp[x][y] = 2;
		return 1;
	}
	return 0;
}
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
void e6_o1();
void e6_o2();
void e6_o3(); 
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
void e6_debuff_board();
void p_e6_boss(int s);
void p_e6_boss_detail(int s);
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
void e6_skill_board();
void p_e6_skillc(int s);
void p_e6_skillc_detail(int s); 
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
//NoEvaa
//2020-8-12 to 2020-9-8
