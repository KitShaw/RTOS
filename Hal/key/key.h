
/*
 * key.h
 */
 
#ifndef __KEY_H
#define __KEY_H

//ʹ��λ��������
#define K_UP PAin(0)
#define K_DOWN PEin(3)
#define K_LEFT PEin(2)
#define K_RIGHT PEin(4)

void key_init(void);
void key_task(void);
unsigned char key_scan(void);

#endif
