
#include "LSM303.h"
//#include "usart.h"
//#include "I2C.h"
#include  <math.h>    //Keil library  
#include "drv_spi.h"

void Spi_LSM303D_Enable(void)
{
    GPIO_ResetBits(BARO_CS_GPIO, BARO_CS_PIN);
}

void Spi_LSM303D_Disable(void)
{
    GPIO_SetBits(BARO_CS_GPIO, BARO_CS_PIN);
}

void Spi_LSM303_SingleWrite(uint8_t reg, uint8_t value)
{
	Spi_LSM303D_Enable();
	Spi_SingleWirteAndRead(1, reg);
	Spi_SingleWirteAndRead(1, value); 
	Spi_LSM303D_Disable();	
}
void Spi_LSM303D_MultiRead(uint8_t reg,uint8_t *data, uint8_t length)
{
	Spi_LSM303D_Enable();
	Spi_SingleWirteAndRead(1, reg | 0x80);
	SPI_MultiWriteAndRead(1, data, NULL, length);	
	Spi_LSM303D_Disable();	
}

//************初始化L3G4200D的加速度*********************************
uint8_t	val;
void LSM303A_Init( void )
{
	Spi_LSM303_SingleWrite(0x20, 0x67);
	Spi_LSM303_SingleWrite(0x23, 0x40);
	Spi_LSM303_SingleWrite(0x25, 0x00);
//	uint8_t	val;
//	uint8_t setbits = 0;
//	uint8_t clearbits = REG2_FULL_SCALE_BITS_A;
//	setbits |= REG2_FULL_SCALE_8G_A;
//	val = Spi_SingleWirteAndRead(GYRO_SPI, LSM303A_CTRL_REG2);
//	val &= ~clearbits;
//	val |= setbits;
//	
//	Spi_LSM303_SingleWrite(LSM303A_CTRL_REG1,
//			  REG1_X_ENABLE_A | REG1_Y_ENABLE_A | REG1_Z_ENABLE_A | REG1_BDU_UPDATE | REG1_RATE_800HZ_A);
//	SoftDelayMs(100);
//	Spi_LSM303_SingleWrite(LSM303A_CTRL_REG2,val);
	
//  Spi_LSM303_SingleWrite(LSM303A_CTRL_REG1, 0x67);
//	SoftDelayMs(100);
//	Spi_LSM303_SingleWrite(LSM303A_CTRL_REG4, 0x00);
//	SoftDelayMs(100);
	
//  I2C_WriteOneByte(I2C1,LSM303A_I2C_ADDR,LSM303A_CTRL_REG1, 0x37);
//  I2C_WriteOneByte(I2C1,LSM303A_I2C_ADDR,LSM303A_CTRL_REG4, 0x00);
}
bool LSM303M_Detect(void)
{
	uint8_t who_am_i;
//	Spi_LSM303D_Enable();
//	(void)Spi_SingleWirteAndRead(1,ADDR_WHO_AM_I);
//	Spi_LSM303D_Disable();	
	Spi_LSM303D_MultiRead(ADDR_WHO_AM_I, &who_am_i, 1);
	
	if(who_am_i == 0x49)
		return true;
	else 
		return false;
}

//************初始化L3G4200D的磁感应*********************************

void LSM303M_Init( void )
{
	Spi_LSM303_SingleWrite(LSM303M_CRB_REG, 0xa0);
	SoftDelayMs(100);
	Spi_LSM303_SingleWrite(LSM303M_MR_REG, 0x00);
	SoftDelayMs(100);
//	I2C_WriteOneByte(I2C1,LSM303M_I2C_ADDR,LSM303M_CRB_REG, 0xa0);
//	
//	I2C_WriteOneByte(I2C1,LSM303M_I2C_ADDR,LSM303M_MR_REG, 0x00);
}

//********读取磁感应数据************************************


void LAM303M_Read(float *Data)
{
  static unsigned char buffer[6]={0};   
	unsigned char f;
	unsigned int Magn_Sensitivity_XY = 0, Magn_Sensitivity_Z = 0;
	uint16_t cen=0;
	
	Spi_LSM303D_MultiRead(LSM303M_OUT_X_H, buffer, 6);	
	Spi_LSM303D_MultiRead(LSM303M_CRB_REG,&f,1);
	
//	I2C_Read(I2C1,LSM303M_I2C_ADDR,LSM303M_OUT_X_H,buffer,6);//|0x80
//	I2C_Read(I2C1,LSM303M_I2C_ADDR,LSM303M_CRB_REG,&f,1);
  switch(f & 0xE0)
  {
  case LSM303DLHC_FS_1_3_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_1_3Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_1_3Ga;
    break;
  case LSM303DLHC_FS_1_9_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_1_9Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_1_9Ga;
    break;
  case LSM303DLHC_FS_2_5_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_2_5Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_2_5Ga;
    break;
  case LSM303DLHC_FS_4_0_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_4Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_4Ga;
    break;
  case LSM303DLHC_FS_4_7_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_4_7Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_4_7Ga;
    break;
  case LSM303DLHC_FS_5_6_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_5_6Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_5_6Ga;
    break;
  case LSM303DLHC_FS_8_1_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_8_1Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_8_1Ga;
    break;
  }
 /* 
  for(i=0; i<2; i++)
  {
		cen=(int16_t)(((int16_t)buffer[2*i] << 8) + buffer[2*i+1]) ;
    Data[i]=(float)(cen)*1000/Magn_Sensitivity_XY;
  
  }
	*/
	cen=(int16_t)(((uint16_t)buffer[0] << 8) + buffer[1]);
  Data[0]=(float)((int16_t)cen)*1000/Magn_Sensitivity_Z;
	
  cen=(int16_t)(((uint16_t)buffer[2] << 8) + buffer[3]);
  Data[2]=(float)((int16_t)cen)*1000/Magn_Sensitivity_Z;

	cen=(int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]);
  Data[1]=(float)((int16_t)cen)*1000/Magn_Sensitivity_Z;
  /*
	cen=Data[1];
	Data[1]=Data[2];
	Data[2]=cen;
	*/
}
//********读取加速度数据************************************
void LAM303A_Read(Vector3f_t *Data)
{
  static unsigned char buffer[6]={0}, ctrlx[2],i; 
	unsigned char cDivider;
  signed short  int pnRawData[3];
	float LSM_Acc_Sensitivity;
	int16_t cen;
	LSM_Acc_Sensitivity = 0.061e-3f * LSM303D_ONE_G;
	
	Spi_LSM303D_MultiRead(0x28,&buffer[0],1);
	Spi_LSM303D_MultiRead(0x29,&buffer[1],1);
	Data->x = ((int16_t)((buffer[1] << 8) | buffer[0]))*LSM_Acc_Sensitivity;
	Spi_LSM303D_MultiRead(0x2A,&buffer[2],1);
	Spi_LSM303D_MultiRead(0x2B,&buffer[3],1);
	Data->y = ((int16_t)((buffer[3] << 8) | buffer[2]))*LSM_Acc_Sensitivity;
	Spi_LSM303D_MultiRead(0x2C,&buffer[4],1);
	Spi_LSM303D_MultiRead(0x2D,&buffer[5],1);
	Data->z = ((int16_t)((buffer[5] << 8) | buffer[4]))*LSM_Acc_Sensitivity;
	
//	Spi_LSM303D_MultiRead(LSM303A_OUT_X_L, buffer, 6);	//|0x80
//	Spi_LSM303D_MultiRead(LSM303A_CTRL_REG4|0x80,ctrlx,2);
	
	
	
//	I2C_Read(I2C1,LSM303A_I2C_ADDR,LSM303A_OUT_X_L|0x80,buffer,6);
//	I2C_Read(I2C1,LSM303A_I2C_ADDR,LSM303A_CTRL_REG4|0x80,ctrlx,2);
   
//  if(ctrlx[1]&0x40)
//    cDivider=64;
//  else
//    cDivider=16;

//  /* check in the control register4 the data alignment*/
//  if(!(ctrlx[0] & 0x40) || (ctrlx[1] & 0x40)) /* Little Endian Mode or FIFO mode */
//  {
//    for(i=0; i<3; i++)
//    {
//			pnRawData[i]=(int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i];
////      pnRawData[i]=(int16_t)(cen)/cDivider;
//     
//    }
//  }
//  else /* Big Endian Mode */
//  {
//    for(i=0; i<3; i++)
//      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1])/cDivider;
//  }
//  /* Read the register content */
//	Spi_LSM303D_MultiRead(LSM303A_CTRL_REG4, ctrlx, 2);	
////  I2C_Read(I2C1,LSM303A_I2C_ADDR,LSM303A_CTRL_REG4,ctrlx,2);


//  if(ctrlx[1]&0x40)
//  {
//    /* FIFO mode */
//    LSM_Acc_Sensitivity = 0.25;
//  }
//  else
//  {
//    /* normal mode */
//    /* switch the sensitivity value set in the CRTL4*/
//    switch(ctrlx[0] & 0x30)
//    {
//    case LSM303DLHC_FULLSCALE_2G:
//      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_2g;
//      break;
//    case LSM303DLHC_FULLSCALE_4G:
//      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_4g;
//      break;
//    case LSM303DLHC_FULLSCALE_8G:
//      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_8g;
//      break;
//    case LSM303DLHC_FULLSCALE_16G:
//      LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_16g;
//      break;
//    }
//  }

  /* Obtain the mg value for the three axis */
//  for(i=0; i<3; i++)
//  {
//    Data[i]=(float)pnRawData[i]*LSM_Acc_Sensitivity;
//  }
//	Data->x = (float)pnRawData[0]*LSM_Acc_Sensitivity;
//	Data->y = (float)pnRawData[1]*LSM_Acc_Sensitivity;
//	Data->z = (float)pnRawData[2]*LSM_Acc_Sensitivity;
}


/********************************************/
float Data_conversion(float *AccBuffer,float *MagBuffer)
{
  unsigned char i;
	float HeadingValue = 0.0f;
	float fNormAcc,fSinRoll,fCosRoll,fSinPitch,fCosPitch = 0.0f;
  float fTiltedX,fTiltedY = 0.0f;
	float fcosf=0;
	      for(i=0;i<3;i++)
        AccBuffer[i] /= 100.0f;
      
      fNormAcc = sqrt((AccBuffer[0]*AccBuffer[0])+(AccBuffer[1]*AccBuffer[1])+(AccBuffer[2]*AccBuffer[2]));
      
      fSinRoll = AccBuffer[1]/fNormAcc;
      fCosRoll = sqrt(1.0-(fSinRoll * fSinRoll));
      fSinPitch = AccBuffer[0]/fNormAcc;
      fCosPitch = sqrt(1.0-(fSinPitch * fSinPitch));

      
      fTiltedX = MagBuffer[0]*fCosPitch + MagBuffer[2]*fSinPitch;
      fTiltedY = MagBuffer[0]*fSinRoll*fSinPitch + MagBuffer[1]*fCosRoll - MagBuffer[2]*fSinRoll*fCosPitch;
			
      fcosf=fTiltedX /sqrt(fTiltedX*fTiltedX+fTiltedY*fTiltedY);
	
			if(fTiltedY>0)
			  HeadingValue = (float)(acos(fcosf)*180/PI);
			else
				HeadingValue =360-(float)(acos(fcosf)*180/PI);
			
      //HeadingValue = (float) ((atan2f((float)fTiltedY,(float)fTiltedX))*180)/PI;
      HeadingValue+=11;//地磁的北极和地球的北极相差11度左右。
			if(HeadingValue>360)
				HeadingValue=HeadingValue-360;
   
	    return HeadingValue ;
	
	
}






