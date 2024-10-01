#ifndef _MY_READ_H
#define _MY_READ_H

enum keys
{
	Esc_k,
	L_k,
	S_k,
	R_k,
	T_k,
	I_k,
	F5_k,
	F6_k,
	Up_k,
	Down_k,
	Left_k,
	Right_k,
	Enter_k,
	Empty_k,
};

int rk_readKey(enum keys *);
int rk_myTermSave(void);
int rk_myTermRestore(void);
int rk_myTermRegime(int, int, int, int, int);

#endif // _MY_READ_H