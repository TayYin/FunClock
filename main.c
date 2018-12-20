#include <reg51.h>
#include <string.h> //后面字符串函数中取得数组的个数中用到;调用strlen函数

extern void delay(int i);
extern void delay_second();
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void digital_display(int time);
extern void digital_display_init();
extern void lcd_init();
extern void digital_display(int time);
extern int set_time(int order);
extern void count_time(int time, int order);

// 声明常量
/** 定义字符串 **/
const unsigned char code str_title[] = {"Multi-Function Clock"}; // 标题
const unsigned char code str_forward[] = {"Key 8: forward"};     // 正计时
const unsigned char code str_backward[] = {"Key 7: backward"};   // 倒计时
const unsigned char code str_set_time[] = {"Please set time"};   // 设置时间
const unsigned char code str_confirm[] = {"Repress to confirm"};     // 确认
const unsigned char code str_complete[] = {"Time's up!"};     // complete

/** 按键配置 **/
sbit forward_btn = P2 ^ 7;  //key8
sbit backward_btn = P2 ^ 6; //key7
sbit confirm_btn = P2 ^ 5;  //key6
sbit reset_btn = P2 ^ 4;    //key5 (不需要软件实现)
sbit t2_btn = P2 ^ 1;       //key2
sbit t1_btn = P2 ^ 0;       //key1
sbit beep = P1^3;

void do_beep(){
	int i,j;
	for(i=0;i<500;i++){
		for(j=0;j<300;j++){
			beep = ~beep;
		}
	}
	for(i=0;i<500;i++){
		for(j=0;j<200;j++){
			beep = ~beep;
		}
	}
	for(i=0;i<500;i++){
		for(j=0;j<80;j++){
			beep = ~beep;
		}
	}
}

/**
 * @brief 初始化至初始状态
 * 
 */
void init_all()
{
  delay(15);              //长延时
  lcd_init();             //初始化LCD
  digital_display_init(); //初始化数码管

  display_string(0, 0, str_forward);  //显示正计时提示
  display_string(1, 0, str_backward); //显示倒计时提示
}

/**
 * @brief 主函数
 * 
 */
void main()
{
  int realtime;

  lcd_init();
  display_string(0, 0,str_title);

  delay(2000);

  init_all();



  while (1) // 开始循环状态
  {
    realtime = 0;
    if (forward_btn == 1) // 按下正计时开关
    {
      lcd_init();                         // 清屏
      display_string(0, 0, str_set_time); //显示设置时间提示
      display_string(1, 0, str_confirm);  //显示确认提示

      realtime = set_time(1);   //设置时间，等待确认
      count_time(realtime, 1); //开始正计时
	  lcd_init();
	  display_string(0, 0, str_complete);
	  do_beep();
	  delay(2000);
      init_all();
    }

    if (backward_btn == 1) // 按下倒计时开关
    {
      lcd_init();                         // 清屏
      display_string(0, 0, str_set_time); //显示设置时间提示
      display_string(1, 0, str_confirm);  //显示确认提示

      realtime = set_time(-1);    //设置时间，等待确认
      count_time(realtime, -1); //开始倒计时
      lcd_init();
	  display_string(0, 0, str_complete);
	  do_beep();
	  delay(1000);
      init_all();
    }
  }
}
