#include "16F877A.h"
#use    delay(crystal=20M)
#use    rs232(UART1)
#define Enter 13
#define Plus '+'
#define Minus '-'
#define Multiply '*'
#define Divide '/'
#define Exponent '^'
#define Factorial '!'

int a=0,b=0,i=0,sign1=0,sign2=0,skip=0;
char          MyKey;
signed long   Op1, Op2,Key,Sign,mul;
unsigned char msg1[] = " CALCULATOR PROGRAM";
unsigned char msg2[] = " Enter First Number: ";
unsigned char msg3[] = " Enter Second Number: ";
unsigned char msg4[] = " Enter Operation: ";
unsigned char msg5[] = " Result = ";

void baoloi()
{
   while(1)
   {
      output_toggle(PIN_B0);
       delay_ms(500);
   }
}

void checkdata(int data)
{
   if (!(((data >= '0')&& (data <= '9'))||(data=='+')||(data=='-')||(data=='*')||(data=='/')||(data=='^')||(data=='!')||data==13))
       baoloi();
}


#int_RDA
void isrtran()
{
   a=1;
   b= getc();
   checkdata(b);
}


void Newline() 
{
   putc(0x0D); //Insert a blank row
   putc(0x0A); 
} 

void Text_To_Usart(unsigned char *m) 
{
   unsigned char i;
   i = 0;
   while(m[i] != 0) 
   {
      putc(m[i]);
      i++;
   }
}

void main()
{  
   set_tris_C(0xC0);
   setup_uart(9600);
   enable_interrupts(int_RDA);
   enable_interrupts(global);
   
   for(;;) 
   {
      skip=0;
      sign1=0;
      sign2=0;
      MyKey = 0;
      Op1 = 0;
      Op2 = 0;
      Newline();
      Newline();
      Text_To_Usart(msg1);
      Newline();
      Newline();
      Text_To_Usart(msg2);

      while(1)
      {
         if(a==1)
         {
            MyKey=b;
            if(MyKey == Enter)
            {
               a=0;
               break;
            }
            putc(MyKey);
            if ((MyKey >= '0')&& (MyKey <= '9')) 
            {
               Key = MyKey - '0';
               Op1 = 10*Op1 + Key;
            }
            if (MyKey == '-') sign1=1;
            a=0;
         }
      }
      Newline();
      Text_To_Usart(msg4);
      while(1) 
      {
         if(a==1) 
         {
            MyKey=b;
            if(MyKey == Enter) 
            {
               a=0;
               break;
            }
            putc(MyKey);
            Sign = MyKey;
            a=0;
            if (Sign == '!') 
               skip=1;
         }
      }

      Newline();
      if (skip==0)
      {
         Text_To_Usart(msg3);
         while(1) 
         {
            if(a==1) 
            {
               MyKey=b;
               if(MyKey == Enter) 
               {
                  a=0;
                  break;
               }
               putc(MyKey);
               if ((MyKey >= '0')&& (MyKey <= '9')) 
               {
                  Key = MyKey - '0';
                  Op2= 10*Op2+ Key;
               }
               if (MyKey == '-') 
                  sign2=1;
               a=0;
            }
         }
      }
          
      Newline();
      Text_To_Usart(msg5);

      switch(Sign) 
      {
         case Plus:
            if (sign1==1)
               if (sign2==1) 
               {
                  putc('-');
                  printf("%ld",Op1+Op2);
               }
               else 
                     printf("%ld",Op2-Op1);
            else
               if (sign2 == 1) 
               {
                  printf("%ld",Op1-Op2);
               }
               else 
                  printf("%ld",Op1+Op2);
         break;

         case Minus:
            if (sign1==1)
               if (sign2==1) 
                  printf("%ld",Op2-Op1);
               else 
               {  
                  putc('-');
                  printf("%ld",Op2+Op1);
               }
            else
               if (sign2 == 1) 
                  printf("%ld",Op1+Op2);
               else 
                  printf("%ld",Op1-Op2);
         break;

         case Multiply:
            if (sign1==1)
               if (sign2==1) 
               {
                  printf("%ld",Op1*Op2);
               }
               else 
               {
                  putc('-');
                  printf("%ld",Op2*Op1);
               }
            else
               if (sign2 == 1) 
               {  
                  putc('-');
                  printf("%ld",Op1*Op2);
               }
               else 
                  printf("%ld",Op1*Op2);
         break;

         case Divide:
            if (Op2==0) baoloi();
            if ((sign1-sign2)!=0) 
               putc('-');
            mul=Op1/Op2;
            printf("%ld",mul);
            putc('.');
            if (((10*(Op1-mul*Op2))/Op2) == 0) 
               putc('0');
            Op1=100*(Op1-mul*Op2);
            mul=Op1/Op2;
            printf("%ld",mul);
         break;

         case Exponent:
            if ((sign1 == 1) && (Op2 % 2 ==1)) 
               putc('-');
            mul = 1;
         for (i=1;i<=Op2;i++)
            mul=mul*Op1;
         if (sign2==0)
            printf("%ld",mul);
         else
            if (mul==1) 
               printf("%ld",mul);
            else {
               mul=100/mul;
               putc('0'); putc('.');
               printf("%ld",mul);}
         break;

         case Factorial:
         if (sign1==1) 
            baoloi();
         mul = Op1;
         for (i=1;i<Op1;i++)
            mul=mul*(Op1-i);
         printf("%ld",mul);     
         break;

         default: baoloi();
      }
   }
}
