//#include <stm32f30x.h>
#include "L3GD20.h"
#include "stm32f4xx.h" 
#include "drv_spi.h"
#include "mathTool.h"


//��ʼ��L3GD20�˿����á����˿�����ΪSPIͨ�Žӿڡ�
//��Ƭ���˿ڳ�ʼ������I/O�˿ڣ�I/O�˿�spiϵͳʱ�ӡ�
 

//2.�����ǳ�ʼ������
//  ����������оƬ���ܺ�оƬ��ʼ������
//  ��Ӧ�Ĵ������ü����ܲο�LG3D20�����ֲ� 
void L3GD20_Init(L3GD20_InitTypeDef *L3GD20_InitStruct)
{
	L3GD20_InitTypeDef L3GD20_InitStructure;
	uint8_t ctrl1 = 0x00, ctrl4 = 0x00;
 
	
	L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;             //����ֵ0x08
	L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1; //����ֵ0x00
	L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;      //����ֵ0x07
	L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_4; //����ֵ0x30
	L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous; //����ֵ0x00
	L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB; //����ֵ0x00
	L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_500;       //����ֵ0x10
	
	if(L3GD20_InitStruct)
	{
		ctrl1 |= (uint8_t) (L3GD20_InitStruct->Power_Mode | L3GD20_InitStruct->Output_DataRate | \
									L3GD20_InitStruct->Axes_Enable | L3GD20_InitStruct->Band_Width);
		ctrl4 |= (uint8_t) (L3GD20_InitStruct->BlockData_Update | L3GD20_InitStruct->Endianness | \
									L3GD20_InitStruct->Full_Scale);
	}
	else
	{
		ctrl1 |= (uint8_t) (L3GD20_InitStructure.Power_Mode | L3GD20_InitStructure.Output_DataRate | \
									L3GD20_InitStructure.Axes_Enable | L3GD20_InitStructure.Band_Width);
		ctrl4 |= (uint8_t) (L3GD20_InitStructure.BlockData_Update | L3GD20_InitStructure.Endianness | \
									L3GD20_InitStructure.Full_Scale);
	}
	L3GD20_Write(L3GD20_CTRL_REG1_ADDR, ctrl1);
	SoftDelayMs(50);
	L3GD20_Write(L3GD20_CTRL_REG4_ADDR, ctrl4);
	SoftDelayMs(50);
	
 
}

 

 

//3.L3GD20����SPI���ݶ���д�Ĵ�������
//��ȡ����L3GD20_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)

void L3GD20_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
	if(NumByteToRead > 0x01)
	{
		ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
	}
	else
	{
		ReadAddr |= (uint8_t)READWRITE_CMD;
	}
	L3GD20_CS_LOW();
 
	Spi_SingleWirteAndRead(1, ReadAddr);
 
	SPI_MultiWriteAndRead(1, pBuffer, NULL, NumByteToRead);
	L3GD20_CS_HIGH();
}  

 

void L3GD20_Write(uint8_t reg, uint8_t value)
{
 
 
	L3GD20_CS_LOW();
	Spi_SingleWirteAndRead(1, reg);
	Spi_SingleWirteAndRead(1, value); 
	L3GD20_CS_HIGH();	
}

//4.��װ��ȡ������3�����ݺ���
//  ����ȡ���������ݽ��д������
//  Demo_GyroReadAngRate (float* pfData)

void Demo_GyroReadAngRate(Vector3f_t* pfData)
{
	uint8_t tmpbuffer[6] ={0};
	int16_t RawData[3] = {0};
	uint8_t tmpreg = 0;
	float sensitivity = 0;
	int i =0;
	L3GD20_Read(&tmpreg,L3GD20_CTRL_REG4_ADDR,1);
	L3GD20_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,6);
	if(!(tmpreg & 0x40))
	{
		for(i=0; i<3; i++)
		{
			RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
		}
	}
	else
	{
		for(i=0; i<3; i++)
		{
			RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i] << 8) + tmpbuffer[2*i+1]);
		}
	}
	switch(tmpreg & 0x30)
	{
		case 0x00:
			sensitivity=L3G_Sensitivity_250dps;//L3G_Sensitivity_500dps=360/pi
			break;
		case 0x10:
			sensitivity=L3G_Sensitivity_500dps;  //L3G_Sensitivity_500dps=180/pi=57.1429
			break;
		case 0x20:
			sensitivity=L3G_Sensitivity_2000dps;//L3G_Sensitivity_500dps=1/4*180/pi
			break;
	}
//	for(i=0; i<3; i++)
//	{
//		pfData[i]=(float)RawData[i]/sensitivity; //�������ݳ�������
//	}
	pfData->x = (float)RawData[0]/sensitivity; //�������ݳ�������
	pfData->y = (float)RawData[1]/sensitivity;
	pfData->z = (float)RawData[2]/sensitivity;
}  

