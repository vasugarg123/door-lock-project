/*
 * project1.c
 *
 * Created: 09/07/2017 02:41:04 AM
 *  Author: Vasu Garg
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>





   void cmd (unsigned char a)
   {
	   PORTC=a;
	   PORTA&=(~(1<<4));
	   PORTA|=(1<<6);
	   _delay_ms(5);
	   PORTA&=(~(1<<6));
	   _delay_ms(5);
	      
   }
   
   void data (unsigned char b)
   {
	   
	   PORTC=b;
	   PORTA|=(1<<4);
	   PORTA|=(1<<6);
	   _delay_ms(5);
	   PORTA&=(~(1<<6));
	   _delay_ms(5);
	   
   }
   
   void init (void)
   {
	   cmd(0x38);
	   cmd(0x0e);
	   cmd(0x06);
	   
   }
   
   void str (unsigned char *ptr)
   {
	  while(*ptr)
		  data(*ptr++);   
	   
   }
   
   int main(void)
   {
	   DDRC=0xff;
	   DDRA=0xff;
	   DDRD=0x07;
	   
	    init();
		cmd(0x82);
		str("DOOR LOCK");
		cmd(0xc1);
		str("BASED SYSTEM");
		_delay_ms(1000);
		cmd(0x01); 
	    cmd(0x81);
	   str("ENTER THE ");
	   cmd(0xc1);
	   str("PASSWORD");
	   _delay_ms(500);
	   cmd(0x01);
	   
	   
	   unsigned char pass[5]={"1234"};
	   unsigned char en[5];
	   
	   unsigned char no=0;
		while(no<3)
		{
			int count=0;
			while(count<4)
			{
				
			PORTD=(1<<0);
			if(PIND&(1<<3))
			{
				data('*');
				en[count]='1';
				count++;
					
				
			}
			else if(PIND&(1<<4))
			{
				data('*');
				en[count]='4';
				count++;
				
			}
			else if(PIND&(1<<5))
			{
				data('*');
				en[count]='7';
				count++;
			}
			_delay_ms(100);
			
			PORTD=(1<<1);
			if(PIND&(1<<3))
			{			
				data('*');
				en[count]='2';
				count++;
				
			}
			else if(PIND&(1<<4))
			{
				data('*');
				en[count]='5';
				count++;
				
			}
			else if(PIND&(1<<5))
			{
				data('*');
				en[count]='8';
				count++;
			}
			_delay_ms(100);
			
			PORTD=(1<<2);
			if(PIND&(1<<3))
			{
				data('*');
				en[count]='3';
				count++;
				
			}
			else if(PIND&(1<<4))
			{
				data('*');
				en[count]='6';
				count++;
			}
			else if(PIND&(1<<5))
			{
				data('*');
				en[count]='9';
				count++;
			}
			_delay_ms(100);
			
			
			}	
			cmd(0x01);			
			
			if(!strcmp(pass,en))
			{
				str("correct password") ;
				_delay_ms(500);
				
				PORTA=0x0A;
				
				
			}
			else
			{
				str("WRONG PASSWORD");
				_delay_ms(400);
				cmd(0x01);
				str("rewrite password");
				_delay_ms(400);
				
			}
			cmd(0x01);
			no++;
			
			}
			init();
			cmd(0x82);
			str("retry after");
			cmd(0xc2);
			str("some time");
			_delay_ms(1000);
			cmd(0x01);			
		}			
				
					  
	 
	 
	
	 
	 
	      
 