#include "yzcontract.h"
void contract_event1(int *cp,int i){
	if(*(cp+i)==0){
		*(cp+i)=1;
		gtxy(14,2*i+5);
		printf("◎");
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
	printf("合约等级：%2d",n);	
	int i;
	gtxy(2,22);
	printf("                    \n");
	printf("                    ");
	gtxy(2,22);
	for(i=0;i<n/2;i++){
		if(i%2==0){
			printf("▲");
		}
		else{
			printf("▼");
		}		
	}
	if(n%2==1){
		if((n/2)%2==0){
			printf("▲");
		}
		else{
			printf("▼");
		}		
	}
	gtxy(2,23);	
	for(i=0;i<n/2;i++){
		if(i%2==1){
			printf("▲");
		}
		else{
			printf("▼");
		}		
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
}
