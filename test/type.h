#ifndef __TYPE_H__
#define __TYPE_H__



typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;

typedef char int8;
typedef int  int16;
typedef long int32;

typedef volatile unsigned char vuint8;
typedef volatile unsigned int  vuint16;
typedef volatile unsigned long vuint32;


typedef union
{
	unsigned char ucIrData[17];
	unsigned long ulIrData; 
}IrData_u;

typedef struct 
{
	IrData_u  IrData;
	unsigned char FrameOK;
}IrData_Typ;

typedef struct
{
	unsigned int uiIrData[140];
	unsigned int uiIrHeard[2];
	unsigned char FrameOK;
}IIrData_Typ;

typedef struct
{
	uint16 SysUID;
	uint16 BaudRate;
}SysParameter_Tyep;

typedef enum
{
	TRUE = !0,
	FALSE = 0
}bool;


#endif
