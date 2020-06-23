#include "Serial_Cal.h"
#include "16F877A.h"

void Serial_Cal::isrtran() //chec interupt
{
    a=1;
    b=0;
}
void Serial_Cal::Newline()  //new line!!
{
    putc(0x0D);
    putc(0x0A);
}
void Serial_Cal::Text_To_Uart(unsigned char *m) //send text to terminal
{
    unsigned char i=0;
    while (m[i]!=0)
    {
        putc(m[i]);
        i++;
    }
}