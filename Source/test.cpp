#include "test.h"
#include<iostream>
extern HANDLE hInput; //��ȡ��׼�����豸��� 
extern INPUT_RECORD inRec;//�������ݼ�¼ 
extern DWORD numRead; //�����Ѷ�ȡ�ļ�¼�� 
extern int Y,X;//X��Y������ 

extern int c_mine,c_blank;
extern int lx,ly;//��λ 
extern int tc,tl,tp;//��ʱ������ 
extern int mr[2];
using namespace std;
void newtest(){
	//mode();
	c_mine=100;
	int i;
	cin>>i;
	cout<<i<<c_mine<<endl;
	//gtxy(0,0);
	//printf("100");
}
