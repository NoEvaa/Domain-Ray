#ifndef _YZETMF_H_
#define _YZETMF_H_

#include "yzetmf.h"
#include "yzmain.h"
#include "yzetme.h"

void entertainment6();//”È¿÷6
void e_6();
void e6_course();
int e6_rule_choice();
void e6_operation();
void e6_o1();
void e6_o2();
void e6_o3(); 
void e6_debuff();
void e6_debuff_board();
void p_e6_boss(int s);
void p_e6_boss_detail(int s);
void e6_skill();
void e6_skill_board();
void p_e6_skillc(int s);
void p_e6_skillc_detail(int s);
int play6();//”È¿÷6”Œœ∑Ω¯≥Ã
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

#endif
