#pragma once

#define EL_RAND_MAX RAND_MAX

// unit == 2�� ��� 0, 1 �� ���� ���� ����Ѵ�.
extern void EL_SetRandomSeed(unsigned int seed);
extern int EL_Random(int unit);
extern int EL_Random(int from, int to);
extern int EL_Dice(int num, int size);
