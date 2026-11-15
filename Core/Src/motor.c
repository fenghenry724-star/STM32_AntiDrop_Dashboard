#include "motor.h"
#include "main.h"
extern TIM_HandleTypeDef htim2;

//初始化电机
void Motor_Init()
{
    //让Tim2通道1输出PWM波
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    //初始状态速度为0
    Motor_SetSpeed(0);
}

//速度控制函数
void Motor_SetSpeed(int16_t speed)
{
    //1.限速
    if(speed > 1000)
    {
        speed = 1000;
    }
    else if(speed < -1000)
    {
        speed = -1000;
    }

    //2.方向控制
    if(speed > 0)
    {
        //正转
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
    else if(speed < 0)
    {
        //反转
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        speed = -speed;//绝对值
    }
    else
    {
        //停止
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }

    //3.设置PWM占空比
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, speed);

}
