#include<reg52.h>

sbit IN1=P1^0;	//��·
sbit IN2=P1^1;
sbit IN3=P1^2;	//��·
sbit IN4=P1^3;


sbit RED1=P3^4;	//�����
sbit RED2=P3^5;	//�Һ���

sbit ENA1=P2^4;	//��·ʹ��
sbit ENA2=P2^5;	//��·ʹ��

#define uint unsigned int
#define uchar unsigned char
	
#define L_go			{IN1=1,IN2=0;}	//��·�����ת
#define L_stop		{IN1=0,IN2=0;}	//��·���ֹͣ
#define L_back		{IN1=0,IN2=1;}	//��·�����ת
#define R_go			{IN3=1,IN4=0;}	//��·�����ת
#define R_stop		{IN3=0,IN4=0;}	//��·���ֹͣ
#define R_back		{IN3=0,IN4=1;}	//��·�����ת

void delay(int x)
	{
			uint i,j;
			for(i=x;i>0;i--)
				for(j=112;j>0;j--);
	}	

void run();
void back();
void stop();
void left();
void right();
void track();

void init();
void pwm_left_moto();
void pwm_right_moto();


uchar PWM_left=0;
uchar PUSH_left=0;
uchar PWM_right=0;
uchar PUSH_right=0;
uchar t=0;


void main()
	{	
		init();
		run();
		while(1)
		{
			track();
		}
	}	
	
	
void run()	//ǰ��
	{
		PUSH_left=4;
		PUSH_right=4;
		L_go;
		R_go;
	}
void left()	//��ת
	{
		PUSH_left=4;
		PUSH_right=8;
		R_go;
		L_go;	
	}
void right()	//��ת
	{
		PUSH_left=8;
		PUSH_right=4;
		L_go;
		R_go;	
	}
	
	
void track()
	{
			if(RED1==0&&RED2==0)
			{
				run();	
			}		
		else if(RED1==1&&RED2==0)
			{
				left();
			  delay(100);
			}
		else if(RED1==0&&RED2==1)
			{
				right();
				delay(100);
			}
		else
			{
				run();
			}
	}
	
	
void init()	
	{
		TMOD=0x01;
		TH0=(65536-100)/256;
		TL0=(65536-100)%256;
		EA =1;
		ET0=1;
		TR0=1;
	}
	
void timer0()interrupt 1	//�ж�
	{
		TH0=(65536-100)/256;
		TL0=(65536-100)%256;
		pwm_left_moto();
		pwm_right_moto();
		PWM_left++;
		PWM_right++;
		t++;
		if(t>=18)
			{	
				t=0;
				PWM_left=0;
				PWM_right=0;
			}
	}
	
	
void pwm_left_moto()
	{
		if(PWM_left<PUSH_left)
		{
			ENA1=1;
		}
		else
		{
			ENA1=0;
		}
	}	
	
void pwm_right_moto()
	{
		if(PWM_right<PUSH_right)
		{
			ENA2=1;
		}
		else
		{
			ENA2=0;	
		}
	}	
