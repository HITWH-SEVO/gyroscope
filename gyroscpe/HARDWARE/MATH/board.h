#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f4xx.h"

/**********************************************************************************************************
*飞控软件版本
**********************************************************************************************************/
//#define SOFTWARE_VERSION_HIGH   0
//#define SOFTWARE_VERSION_MID    4
//#define SOFTWARE_VERSION_LOW    17

///**********************************************************************************************************
//*飞控硬件类型
//**********************************************************************************************************/
//enum
//{
//    BOARD_BLUESKY_V3,
//	BOARD_FUTURESKY
//};

/**********************************************************************************************************
*定义硬件类型
**********************************************************************************************************/
#define BLUESKY_V3

/**********************************************************************************************************
*传感器配置
**********************************************************************************************************/
#define GYRO_TYPE            ICM20689       //陀螺仪型号
#define BARO_TYPE            MS5611         //气压计型号
#define MAG_TYPE             QMC5883        //罗盘型号

#define configUSE_SENSORHEAT 1              //是否使用传感器恒温

#define GYRO_SPI             1              //陀螺仪SPI配置
#define GYRO_CS_GPIO         GPIOC
#define GYRO_CS_PIN          GPIO_Pin_2

#define GYRO2_SPI            1              //陀螺仪2SPI配置
#define GYRO2_CS_GPIO        GPIOC
#define GYRO2_CS_PIN         GPIO_Pin_13

#define BARO_SPI             1              //气压计SPI配置
#define BARO_CS_GPIO         GPIOC
#define BARO_CS_PIN          GPIO_Pin_15

/**********************************************************************************************************
*SPI引脚及参数配置
**********************************************************************************************************/
#define SPI1_GPIO_MOSI          GPIOA
#define SPI1_GPIO_MISO          GPIOA
#define SPI1_GPIO_SCK           GPIOA
#define SPI1_PINSOURCE_MOSI     GPIO_PinSource7
#define SPI1_PINSOURCE_MISO     GPIO_PinSource6
#define SPI1_PINSOURCE_SCK      GPIO_PinSource5
#define SPI1_PIN_MOSI           GPIO_Pin_7
#define SPI1_PIN_MISO           GPIO_Pin_6
#define SPI1_PIN_SCK            GPIO_Pin_5
#define SPI1_CLOCKDIV           SPI_BaudRatePrescaler_8

#define SPI2_GPIO_MOSI          GPIOC
#define SPI2_GPIO_MISO          GPIOC
#define SPI2_GPIO_SCK           GPIOB
#define SPI2_PINSOURCE_MOSI     GPIO_PinSource3
#define SPI2_PINSOURCE_MISO     GPIO_PinSource2
#define SPI2_PINSOURCE_SCK      GPIO_PinSource13
#define SPI2_PIN_MOSI           GPIO_Pin_3
#define SPI2_PIN_MISO           GPIO_Pin_2
#define SPI2_PIN_SCK            GPIO_Pin_13
#define SPI2_CLOCKDIV           SPI_BaudRatePrescaler_8

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

//硬件配置头文件包含
//#ifdef BLUESKY_V3
//	#include "boardConfigBlueSkyV3.h"
//    #define BOARD_TYPE BOARD_BLUESKY_V3
//#endif

//typedef struct
//{
//    int16_t roll;   
//    int16_t pitch;   
//    int16_t yaw;      
//    int16_t throttle;  
//    int16_t aux1;  
//    int16_t aux2;  
//    int16_t aux3;  
//    int16_t aux4;  
//    int16_t aux5;  
//    int16_t aux6;   
//    int16_t aux7;  
//    int16_t aux8;  
//    int16_t aux9;  
//    int16_t aux10;     
//    int16_t aux11;  
//    int16_t aux12;  
//}RCDATA_t;

//enum
//{
//    MPU6000,
//    MPU6500,
//    ICM20602,
//    ICM20689
//};

//enum
//{
//    BMP280,
//    MS5611,
//    _2SMPB,
//    LPS22HB
//};

//enum
//{
//    HMC5883,
//    QMC5883,
//    IST8310
//};

//enum
//{
//    SBUS,
//    PPM
//};

void BoardInit(void);
void SoftDelayMs(uint32_t ms);
void SoftDelayUs(uint32_t us);
void OsDelayMs(uint32_t ms);

uint64_t GetSysTimeUs(void);
uint32_t GetSysTimeMs(void);

#endif






