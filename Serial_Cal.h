#ifndef _Serial_Cal_
#define _Serial_Cal_

#include "16F877A.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define Enter 13
#define Plus '+'
#define Minus '-'
#define Multiply '*'
#define Divide '/'

class Serial_Cal
{
public:
    void isrtran();
    void Newline();
    void Text_To_Uart(unsigned char *m);
};


#endif