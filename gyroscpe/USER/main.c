#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "drv_spi.h"
#include "board.h"
#include "mpu6000.h"
#include "mpu6500.h"
#include "L3GD20.h"
 #include "LSM303.h"
//#include "lsm303dlhc_driver.h"
 
//要写入到W25Q16的字符串数组
const u8 TEXT_Buffer[]={"Explorer STM32F4 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
bool detect = false;
Vector3f_t mpu6500_acc;
Vector3f_t mpu6500_gyro;
Vector3f_t l3gd20_gyro;
Vector3f_t lsm303d_acc;

int32_t _mpu6500_acc_x;
int32_t _mpu6500_acc_y;
int32_t _mpu6500_acc_z;

int32_t _mpu6500_gyro_x;
int32_t _mpu6500_gyro_y;
int32_t _mpu6500_gyro_z;

int32_t _l3gd20_gyro_x;
int32_t _l3gd20_gyro_y;
int32_t _l3gd20_gyro_z;

int32_t _lsm303d_acc_x;
int32_t _lsm303d_acc_y;
int32_t _lsm303d_acc_z;

void transation(void)
{
	_mpu6500_acc_x = (int32_t)(mpu6500_acc.x*1000);
	_mpu6500_acc_y = (int32_t)(mpu6500_acc.y*1000);
	_mpu6500_acc_z = (int32_t)(mpu6500_acc.z*1000);
	
	_mpu6500_gyro_x = (int32_t)(mpu6500_gyro.x*1000);
	_mpu6500_gyro_y = (int32_t)(mpu6500_gyro.y*1000);
	_mpu6500_gyro_z = (int32_t)(mpu6500_gyro.z*1000);
	
	_l3gd20_gyro_x = (int32_t)(l3gd20_gyro.x*1000);
	_l3gd20_gyro_y = (int32_t)(l3gd20_gyro.y*1000);
	_l3gd20_gyro_z = (int32_t)(l3gd20_gyro.z*1000);
	
	_lsm303d_acc_x = (int32_t)(lsm303d_acc.x*100);
	_lsm303d_acc_y = (int32_t)(lsm303d_acc.y*100);
	_lsm303d_acc_z = (int32_t)(lsm303d_acc.z*100);
}
int main(void)
{ 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	delay_init(168);     //初始化延时函数
//	uart_init(115200);	//初始化串口波特率为115200

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	Spi_GPIO_Init();
  Spi_Open(GYRO_SPI);
//    Spi_Open(BARO_SPI);
	
	detect = MPU6000_Detect();
	detect = MPU6500_Detect();
	detect = LSM303M_Detect();
	MPU6500_Init();
	L3GD20_Init(0);
//	lsm303d_init();
	LSM303A_Init();
//	LSM303M_Init();
	
	while(1)
	{
		MPU6500_ReadAcc(&mpu6500_acc);
		MPU6500_ReadGyro(&mpu6500_gyro);
		Demo_GyroReadAngRate(&l3gd20_gyro);
//		GetAccAxesRaw(&lsm303d_acc);
		LAM303A_Read(&lsm303d_acc);
		transation();
		delay_ms(1);
	}       
}

