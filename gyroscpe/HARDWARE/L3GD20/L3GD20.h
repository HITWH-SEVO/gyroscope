#ifndef _L3GD20_H_
#define _L3GD20_H_
//#include <stm32f30x.h>
#include "stm32f4xx.h"
#include "mathTool.h"

#define L3GD20_SPI_CLK 				RCC_APB2Periph_SPI1
#define L3GD20_SPI_SCK_GPIO_CLK 	RCC_AHBPeriph_GPIOA
#define L3GD20_SPI_MISO_GPIO_CLK	RCC_AHBPeriph_GPIOA
#define L3GD20_SPI_MOSI_GPIO_CLK	RCC_AHBPeriph_GPIOA
#define L3GD20_SPI_CS_GPIO_CLK		RCC_AHBPeriph_GPIOE
#define L3GD20_SPI_INT1_GPIO_CLK	RCC_AHBPeriph_GPIOE
#define L3GD20_SPI_INT2_GPIO_CLK	RCC_AHBPeriph_GPIOE

#define L3GD20_SPI_CS_GPIO_PORT		GPIOC
//#define L3GD20_SPI_SCK_GPIO_PORT	GPIOA
//#define L3GD20_SPI_INT1_GPIO_PORT 	GPIOB
//#define L3GD20_SPI_INT2_GPIO_PORT 	GPIOB
//#define L3GD20_SPI_MISO_GPIO_PORT	GPIOA
//#define L3GD20_SPI_MOSI_GPIO_PORT	GPIOA

#define L3GD20_SPI_SCK_SOURCE GPIO_PinSource5
#define L3GD20_SPI_MISO_SOURCE GPIO_PinSource6
#define L3GD20_SPI_MOSI_SOURCE GPIO_PinSource7

#define L3GD20_SPI_SCK_AF GPIO_AF_5
#define L3GD20_SPI_MISO_AF GPIO_AF_5
#define L3GD20_SPI_MOSI_AF GPIO_AF_5

//#define L3GD20_SPI_SCK_PIN 		GPIO_Pin_5
//#define L3GD20_SPI_MOSI_PIN 	GPIO_Pin_7
//#define L3GD20_SPI_MISO_PIN 	GPIO_Pin_6
#define L3GD20_SPI_CS_PIN		GPIO_Pin_13
//#define L3GD20_SPI_INT1_PIN		GPIO_Pin_0
//#define L3GD20_SPI_INT2_PIN		GPIO_Pin_1

#define L3GD20_SPI SPI1

/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80) 
/* Multiple byte read/write command */ 
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)

/******************************************************************************/
/*************************** START REGISTER MAPPING  **************************/
/******************************************************************************/
#define L3GD20_WHO_AM_I_ADDR          0x0F  /* device identification register */
#define L3GD20_CTRL_REG1_ADDR         0x20  /* Control register 1 */
#define L3GD20_CTRL_REG2_ADDR         0x21  /* Control register 2 */
#define L3GD20_CTRL_REG3_ADDR         0x22  /* Control register 3 */
#define L3GD20_CTRL_REG4_ADDR         0x23  /* Control register 4 */
#define L3GD20_CTRL_REG5_ADDR         0x24  /* Control register 5 */
#define L3GD20_REFERENCE_REG_ADDR     0x25  /* Reference register */
#define L3GD20_OUT_TEMP_ADDR          0x26  /* Out temp register */
#define L3GD20_STATUS_REG_ADDR        0x27  /* Status register */
#define L3GD20_OUT_X_L_ADDR           0x28  /* Output Register X */
#define L3GD20_OUT_X_H_ADDR           0x29  /* Output Register X */
#define L3GD20_OUT_Y_L_ADDR           0x2A  /* Output Register Y */
#define L3GD20_OUT_Y_H_ADDR           0x2B  /* Output Register Y */
#define L3GD20_OUT_Z_L_ADDR           0x2C  /* Output Register Z */
#define L3GD20_OUT_Z_H_ADDR           0x2D  /* Output Register Z */ 
#define L3GD20_FIFO_CTRL_REG_ADDR     0x2E  /* Fifo control Register */
#define L3GD20_FIFO_SRC_REG_ADDR      0x2F  /* Fifo src Register */

#define L3GD20_INT1_CFG_ADDR          0x30  /* Interrupt 1 configuration Register */
#define L3GD20_INT1_SRC_ADDR          0x31  /* Interrupt 1 source Register */
#define L3GD20_INT1_TSH_XH_ADDR       0x32  /* Interrupt 1 Threshold X register */
#define L3GD20_INT1_TSH_XL_ADDR       0x33  /* Interrupt 1 Threshold X register */
#define L3GD20_INT1_TSH_YH_ADDR       0x34  /* Interrupt 1 Threshold Y register */
#define L3GD20_INT1_TSH_YL_ADDR       0x35  /* Interrupt 1 Threshold Y register */
#define L3GD20_INT1_TSH_ZH_ADDR       0x36  /* Interrupt 1 Threshold Z register */
#define L3GD20_INT1_TSH_ZL_ADDR       0x37  /* Interrupt 1 Threshold Z register */
#define L3GD20_INT1_DURATION_ADDR     0x38  /* Interrupt 1 DURATION register */

/******************************************************************************/
/**************************** END REGISTER MAPPING  ***************************/
/******************************************************************************/



#define L3GD20_MODE_ACTIVE 					(0x08)
#define L3GD20_OUTPUT_DATARATE_1 			(0x00)
#define L3GD20_AXES_ENABLE 					(0x07)
#define L3GD20_BANDWIDTH_4 					(0x30)
#define L3GD20_BlockDataUpdate_Continous 	(0x00)
#define L3GD20_BLE_LSB 						(0x00)
#define L3GD20_FULLSCALE_500 				(0x10)

#define ABS(x)                     (x < 0) ? (-x) : x
#define L3G_Sensitivity_250dps     (float)114.285f        /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_500dps     (float)57.1429f        /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps]  */
#define L3G_Sensitivity_2000dps    (float)14.285f         /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */


typedef struct
{
	unsigned int Power_Mode;
	unsigned int Output_DataRate;
	unsigned int Axes_Enable;
	unsigned int Band_Width;
	unsigned int BlockData_Update;
	unsigned int Endianness;
	unsigned int Full_Scale;
}L3GD20_InitTypeDef;

typedef struct
{
  uint8_t HighPassFilter_Mode_Selection;      /* Internal filter mode */
  uint8_t HighPassFilter_CutOff_Frequency;    /* High pass filter cut-off frequency */
}L3GD20_FilterConfigTypeDef;

#define L3GD20_CS_LOW()       GPIO_ResetBits(L3GD20_SPI_CS_GPIO_PORT, L3GD20_SPI_CS_PIN)
#define L3GD20_CS_HIGH()      GPIO_SetBits(L3GD20_SPI_CS_GPIO_PORT, L3GD20_SPI_CS_PIN)

void L3GD20_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
//void L3GD20_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void L3GD20_Write(uint8_t reg, uint8_t value);
//static uint8_t L3GD20_SendByte(uint8_t reg, uint8_t value);
void L3GD20_Init(L3GD20_InitTypeDef *L3GD20_InitStruct);
void Demo_GyroReadAngRate(Vector3f_t* pfData);

#endif

