#include "yzcourse.h"
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int lx,ly;//��λ 

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
