#ifndef _YZETME_H_
#define _YZETME_H_

#include "yzetme.h"
#include "yzmain.h"

void entertainment5();//娱乐5
void e_5();
int play5();//娱乐5游戏进程
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
void e5_course();//教程 
int e5_rule_choice();
void e5_operation();
void e5_o1();
void e5_o2();
void e5_o3();
void e5_o4();
void e5_rule();
void e5_skill();
void e5_skill_board();
void p_e5_skillc(int s);
void p_e5_skillc_detail(int s);
void p_e5_skillc_clean();
void p_e5_skillc_demo(int s);
void p_e5_skill1_demo();
void p_e5_skill1_boardset(int (*p)[18]);
void p_e5_skill2_demo();
void p_e5_skill3_demo();

#endif
