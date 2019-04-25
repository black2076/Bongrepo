#include <avr/io.h> 
#include <util/delay.h> 
#include <stdio.h>
#include <avr/interrupt.h>
#include <math.h>
#include "lcd.h"


// 7segment : ��������ð�
// LCD : �뷡����
// DotMatrix : �Ҹ��������ĵ�
// LED : (�������ļֶ�õ���) ���� ON,OFF
// Switch : ���,���� ��� ��ư����
// ADC : ���� ������ ����

#define SEI() sei()
#define CLI() cli()

#define ON 1
#define OFF 2

#define C0 C1 / 2 //�� 4��Ÿ�� ���ļ�
#define C0_ C1_ / 2
#define D0 D1 / 2
#define D0_ D1_ / 2
#define E0 E1 / 2
#define F0 F1 / 2
#define F0_ F1_ / 2
#define G0 G1 / 2
#define G0_ G1_ / 2
#define A0 A1 / 2
#define A0_ A1_ / 2
#define B0 B2 / 2

#define C1 523      //��    //5��Ÿ�� ���ļ� 
#define C1_ 554
#define D1 293  //��
#define D1_ 622
#define E1 659  //��
#define F1 699  //��
#define F1_ 740
#define G1 784  //��
#define G1_ 831
#define A1 880  //��
#define A1_ 932
#define B1 988  //��

 

#define C2 C1 * 2 //�� 6��Ÿ�� ���ļ�
#define C2_ C1_ * 2
#define D2 D1 * 2
#define D2_ D1_ * 2
#define E2 E1 * 2
#define F2 F1 * 2
#define F2_ F1_ * 2
#define G2 G1 * 2
#define G2_ G1_ * 2
#define A2 A1 * 2
#define A2_ A1_ * 2
#define B2 B2 * 2

 

#define DLY_1 DLY_4 * 4
#define DLY_2 DLY_4 * 2
#define DLY_205 DLY_4 * 2.5
#define DLY_4 400
#define DLY_8 DLY_4 / 2
#define DLY_16 DLY_8 / 2


volatile long T1HIGHCNT = 0xFD, T1LOWCNT = 0x86;
volatile int SoundState = ON;
volatile int Soundonoff = ON;

#define EX_LCD_DATA  (*(volatile unsigned char *)0x8000)
#define EX_LCD_CONTROL  (*(volatile unsigned char *)0x8001)
#define EX_SS_DATA (*(volatile unsigned char *)0x8002)
#define EX_SS_SEL (*(volatile unsigned char *)0x8003)
#define EX_LED (*(volatile unsigned char *)0x8008)
#define EX_DM_SEL   (*(volatile unsigned char *)0x8004)
#define EX_DM_DATA   (*(volatile unsigned char *)0x8006)


unsigned char segment_data[10] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f };

// ���� 0,1,2,3,4,5,6,7,8,9 ǥ�� //
unsigned char display_num[4] = { 0xfe,0xfd,0xfb,0xf7 };

//�뷡
//int music[3][50] = { C1, D1, E1, F1, G1, A1, B1};
int scale = 0;

//�ð躯��(��, ��)
int i = 0;

//Ÿ�̸� 1�� ī��Ʈ
unsigned int sec = 0;
unsigned int sec2 = 0;
int keydata; //����ġ���� (��������)
char control_sound = 0;
unsigned int mode = 0;
unsigned int sound_count = 1;
unsigned int adc_data;

int dm_data[10] = { 0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000 };
int dmi = 0; // ���� ����� �� ����

int stop; //���� ���� ��ġ
int select = 0; //��� ���� ��ȣ
int wait = 2; //���� ��� ����
int music[3][100] =
{ { C1,C1,G1,G1,A1,A1,G1,G1,F1,F1,E1,E1,D1,D1,C1,C1,G1,G1,F1,F1,E1,E1,D1,D1,G1,G1,F1,F1,E1,E1,D1,D1,C1,C1,G1,G1,A1,A1,G1,G1,F1,F1,E1,E1,D1,D1,C1,C1 }, //������
{ C1, D1, E1, F1, G1, A1, B1, A1, G1, F1, E1, D1, C1 }, //���� ������� �������� ���
{ C1, E1, G1, C1, E1, G1, A1, A1, A1, G1,G1,G1, F1, F1, F1,E1, E1, E1,D1, D1, D1,C1 } }; //������ ������ �Ȱ�����

void sound(int freq)
{

 Soundonoff = ON;
 T1HIGHCNT = (0xFFFF - floor(2000000 / freq)) / 0x100;
 T1LOWCNT = 0xFFFF - floor(2000000 / freq) - 0xFF00;
}

void nosound(void)
{
 sound_count++;
 if (sound_count >= 9)
 {
  lcdClear();
  sound_count = 1;
 }
 Soundonoff = OFF;
 _delay_ms(100);
}

void port_init(void)
{ // void port_init()
 PORTA = 0X00;
 DDRA = 0XFF;
 PORTB = 0x00;
 DDRB = 0X00;
 PORTC = 0X00;
 DDRC = 0XFF;
 PORTD = 0X00;
 DDRD = 0XFF;
 PORTE = 0X00;
 DDRE = 0X00;
 PORTF = 0X00;
 DDRF = 0X00;
 PORTG = 0X00;
 DDRG = 0XFF;
} // void port_init()

void timer1_init(void)
{ // void time1_init()
 TCCR1B = 0x00;
 TCNT1H = 0xFD;   //TCNT1 �ʱ�ȭ(ū �ǹ� ����)
 TCNT1L = 0x66;
 TCCR1A = 0x00;
 TCCR1B = 0x02; // start timer  //���ֺ� 8
}

 

SIGNAL(TIMER1_OVF_vect)
{ // SIGNAL(SIG_OVERFLOW1)
 TCNT1H = T1HIGHCNT;  //���ϴ� ���ļ��� ����
 TCNT1L = T1LOWCNT;

 if (Soundonoff == ON)
 {
  PORTG = PORTG ^ 0x10;  //��ƮG�� 4���� XOR �������� ���ļ� ����
 }

} // SIGNAL(SIG_OVERFLOW1)

void timer0_init(void)
{ // void time0_init()

 TCCR0 = 0x04;    //���������Ϸ�(���ֺ�)=64          16000000(16MHz)/64/1000(1ms) = 250(250 Ŭ������ 1ms)     
 TCNT0 = 0x06;    // 256 - 250 = 6

}

void init_devices()
{ // void init_devices()
 cli(); // disable interrupt

 port_init();
 timer0_init();
 timer1_init();
 MCUCR = 0X80;   //�ܺ� �޸� ���
 TIMSK = 0X05;   //Timer0 and 1 �����÷ο� ���ͷ�Ʈ Enable

 sei(); // enable interrupt
} // void init_devices()

 

 


ISR(TIMER0_OVF_vect)
{ // 

 TCNT0 = 0x06; //TCNT0 ���� 6���� �ʱ�ȭ
 sec++;
 sec2++;

 if (sec >= 1000)  //1ms �����÷ο� 1000���̸� 1��
 {
  //��������ð�
  ////////////////////////////////////////////////////

  i++;
  sec = 0;

  /////////////////////////////////////////////////////

  //��Ʈ��Ʈ���� (��������� ���� ����ũ���ĵ�)
  ////////////////////////////////////////////////////

  //��Ʈ��Ʈ���� ��
  //EX_DM_DATA = 0x001 << dmi;
  //EX_DM_SEL = 9; //9��°
  //dmi++;
  // if( dmi > 9 ) dmi = 0;

  //��Ʈ��Ʈ���� ��

 


  ////////////////////////////////////////////////////
 }
 if (sec2 >= 4)
 {
  if (mode == 0)
  {
   EX_SS_SEL = display_num[0]; //DIGIT[0] ���� //
   EX_SS_DATA = segment_data[(i / 600) % 10]; // 0~9 //
   mode = 1;
  }
  else if (mode == 1)
  {
   EX_SS_SEL = display_num[1]; //DIGIT[1] ���� //
   EX_SS_DATA = segment_data[(i / 60) % 10]; // 0~9 //
   mode = 2;
  }
  else if (mode == 2)
  {
   EX_SS_SEL = display_num[2]; //DIGIT[2] ���� //
   EX_SS_DATA = segment_data[(i / 10) % 6]; // 0~6 //
   mode = 3;
  }
  else if (mode == 3)
  {
   EX_SS_SEL = display_num[3]; //DIGIT[3] (1�� �ڸ�) ���� //
   EX_SS_DATA = segment_data[(i / 1) % 10]; // 0~9 //
   mode = 0;
  }
  sec2 = 0;
 }

 

 


} //


void adc_init(void)   // adc  �ʱ�ȭ
{
 ADCSRA = 0x00; //disable adc
 ADMUX = 0x00; //select adc input 0

 ADCSRA = 0x87; //adc enable, ���� 128
       //adc�� ���� ���ļ� = 16mhz/128=125khz
}

void adc_startConversion(void)   // adc��ȯ
{
 ADCSRA &= 0x07; //  128���ֺ� ���
 ADMUX = 0x00;

 ADCSRA |= 0xC0;  // ADC ON
}

unsigned int  adc_readData(void)   // adc��ȯ
{
 volatile unsigned int adc_temp;

 while ((ADCSRA & 0x10) == 0); //��ȯ�Ϸ�ɶ����� ��ٸ�
 adc_temp = (int)ADCL + (int)ADCH * 256;

 return adc_temp;
}

void delay(int wait_) //��������ŭ ������Ű�� �Լ�
{
 switch (wait_)
 {
 case 1:
  _delay_ms(100);
  break;
 case 2:
  _delay_ms(150);
  break;
 case 3:
  _delay_ms(200);
  break;
 }
}

void Matrix(int sid) //��Ʈ������ ���� ���̸�ŭ �������� ǥ��(�ݺ���� �̺�� �̱���)
{
 for (int j = 0; j < 10; j++)
 {
  dm_data[i] = dm_data[i] << 1;
  if (j < sid)
   dm_data[i]++;
 }
 return;
}

void runDotMatrix(void)
{
 EX_DM_SEL = 0;
 EX_DM_DATA = dm_data[dmi]; // dmi ��° �� ������ ���
 EX_DM_SEL = 1 << dmi; // dmi ��° �� ����
 dmi++;
 if (dmi>9) dmi = 0;
}

void stop_music() //��� ��� ������ ���ѷ��� �����ϴ� �Լ�
{
 while (1)
 {
  keydata = (PINB & 0xff);
  switch (keydata)
  {
  case 0x01: //���
   return;
  case 0x08:  //���� �ӵ� ����
   if (wait < 3)
    wait++;
   _delay_ms(500);
   break;
  case 0x10:  //���� �ӵ� ����
   if (wait > 1)
    wait--;
   _delay_ms(500);
   break; //������ ����
  case 0x20:
   i = 0;
   if (select < 2)
    select++;
   _delay_ms(500);
   break;
  case 0x40: //������ ����
   i = 0;
   if (select > 0)
    select--;
   _delay_ms(500);
   break;

  }
 }
}

void play_music(int start) //���� ��� �Լ�
{
 unsigned int ah0, al0;
 float voltage;

 init_devices();
 lcdInit();
 lcdClear();

 EX_SS_SEL = 0x0f; // �ʱⰪ���� ����Ʈ OFF

 adc_init();

 adc_startConversion();
 adc_data = adc_readData();
 voltage = (float)(5.*adc_data) / 1024.;

 //LCD����� ���� ��Ʈ
 lcdClear();

 control_sound = (adc_data / 50); // 0 ~ 1023�� ���ڸ� 0 ~ 20�� ������ ǥ��

          //��������(adc_data)�� �̿��� ���� �ٸ� �뷡 ���
 lcd_gotoxy(14, 2);
 lcd_putn2(control_sound);
 for (int i = start; i < 100; i++)
 {
  if (music[select][i] == NULL) //������ ������ ����
  {
   stop = 0;
   return;
  }

  lcd_gotoxy(1, 1);
  lcd_putn2(control_sound); //LCD
  if (control_sound <= 6) {
   sound(music[select][i] / 2); //���� ��Ÿ���� �뷡���
  }
  else if (control_sound > 6 && control_sound <= 14) {
   sound(music[select][i]); //���� ��Ÿ��(�⺻)�� �뷡���
  }
  else {
   sound(music[select][i] * 2); //���� ��Ÿ���� �뷡���
  }
  switch (music[select][i]) //���� LED, LCD, ��Ʈ���� �Լ�ó��
  {
  case C1:
   EX_LED = 0x01;
   lcd_putss("DO");
   Matrix(1);
   break;
  case D1:
   EX_LED = 0x02;
   lcd_putss("RE");
   Matrix(2);
   break;
  case E1:
   EX_LED = 0x04;
   lcd_putss("ME");
   Matrix(3);
   break;
  case F1:
   EX_LED = 0x08;
   lcd_putss("FA");
   Matrix(4);
   break;
  case G1:
   EX_LED = 0x10;
   lcd_putss("SL");
   Matrix(5);
   break;
  case A1:
   EX_LED = 0x20;
   lcd_putss("RA");
   Matrix(6);
   break;
  case B1:
   EX_LED = 0x40;
   lcd_putss("SI");
   Matrix(7);
   break;
  default:
   break;
  }
  /*for (int k = 0; k<10; k++)
  runDotMatrix();*/
  keydata = (PINB & 0xff);
  switch (keydata)
  {
  case 0x02: //����
   stop = 0;
   nosound();
   _delay_ms(500);
   return;
  case 0x04: //�Ͻ�����
   stop = i;
   nosound();
   _delay_ms(500);
   return;
  case 0x08:  //���� �ӵ� ����
   if (wait<3)
    wait++;
   _delay_ms(500);
   break;
  case 0x10:  //���� �ӵ� ����
   if (wait>1)
    wait--;
   _delay_ms(500);
   break; //������ ����
  case 0x20:
   i = 0;
   if (select<2)
    select++;
   _delay_ms(500);
   break;
  case 0x40: //������ ����
   i = 0;
   if (select>0)
    select--;
   _delay_ms(500);
   break;
  default:
   break;
  }
  delay(wait); //���� �ӵ��� ���߾� ������
  nosound();
 }
 stop = 0;

 return;
}

 


int main(void)
{
 unsigned int ah0, al0;
 float voltage;

 init_devices();
 lcdInit();
 lcdClear();

 EX_SS_SEL = 0x0f; // �ʱⰪ���� ����Ʈ OFF

 adc_init();

 adc_startConversion();
 adc_data = adc_readData();
 voltage = (float)(5.*adc_data) / 1024.;

 //LCD����� ���� ��Ʈ
 lcdClear();

 control_sound = (adc_data / 50); // 0 ~ 1023�� ���ڸ� 0 ~ 20�� ������ ǥ��

          //��������(adc_data)�� �̿��� ���� �ٸ� �뷡 ���
 lcd_gotoxy(14, 2);
 lcd_putn2(control_sound);


 while (1)
 {
  stop_music(); //���� ��� ��� ���
  play_music(stop); //���� ���
 }

 return 0;
}
