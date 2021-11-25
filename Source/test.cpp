#include "test.h"
#include<iostream>
extern HANDLE hInput; //获取标准输入设备句柄 
extern INPUT_RECORD inRec;//返回数据记录 
extern DWORD numRead; //返回已读取的记录数 
extern int Y,X;//X和Y的坐标 

extern int c_mine,c_blank;
extern int lx,ly;//定位 
extern int tc,tl,tp;//计时器控制 
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
