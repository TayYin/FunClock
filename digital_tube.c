#include <reg51.h>

/**
 * @brief 显示指定的数字
 * 
 * @param time 计时时间(十进制)
 */
void digital_display(int time)
{
    int unitPlace = time / 1 % 10;                   //个位
    int decadePlace = time / 10 % 10;                //十位
    int display_time = unitPlace + decadePlace * 16; //传递给数码管的数值
    P3 = display_time;
}

/**
 * @brief 初始化数码管，显示00
 * 
 */
void digital_display_init()
{
    digital_display(0);
}