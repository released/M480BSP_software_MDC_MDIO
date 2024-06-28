/*_____ I N C L U D E S ____________________________________________________*/
// #include <stdio.h>
#include "NuMicro.h"

#include "software_MDIO.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

#define USE_PB11_PB10
// #define USE_PE8_PE9

#if defined (USE_PB11_PB10)
#define GPIO_MDC                                        (PB11)
#define GPIO_MDIO                                       (PB10)
#elif defined (USE_PE8_PE9)
#define GPIO_MDC                                        (PE8)
#define GPIO_MDIO                                       (PE9)
#endif

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/


#if defined (FUNC_IN_SRAM)
#pragma arm section code="fastcode"
#endif

/*
    PB11/PE8 : MDC
    PB10/PE9 : MDIO
    2.5MHz = 400 ns
*/
void MDC_MDIO_Init(void) 
{
    // clock
    #if defined (USE_PB11_PB10)
	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB11MFP_Msk)) | (SYS_GPB_MFPH_PB11MFP_GPIO);    
	GPIO_SetMode(PB,BIT11,GPIO_MODE_OUTPUT);
    #elif defined (USE_PE8_PE9)
	SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE8MFP_Msk)) | (SYS_GPE_MFPH_PE8MFP_GPIO);    
	GPIO_SetMode(PE,BIT8,GPIO_MODE_OUTPUT);
    #endif
    // data
    #if defined (USE_PB11_PB10)
	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB10MFP_Msk)) | (SYS_GPB_MFPH_PB10MFP_GPIO);
	GPIO_SetMode(PB,BIT10,GPIO_MODE_OUTPUT);
    #elif defined (USE_PE8_PE9)
	SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE9MFP_Msk)) | (SYS_GPE_MFPH_PE9MFP_GPIO);
	GPIO_SetMode(PE,BIT9,GPIO_MODE_OUTPUT);    
    #endif
}

void MDIO_OUT(void)
{
    #if defined (USE_PB11_PB10)
	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB10MFP_Msk)) | (SYS_GPB_MFPH_PB10MFP_GPIO);
	GPIO_SetMode(PB,BIT10,GPIO_MODE_OUTPUT);
    #elif defined (USE_PE8_PE9)
	SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE9MFP_Msk)) | (SYS_GPE_MFPH_PE9MFP_GPIO);
	GPIO_SetMode(PE,BIT9,GPIO_MODE_OUTPUT);  
    #endif   
}

void MDIO_IN(void)
{
    #if defined (USE_PB11_PB10)
	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB10MFP_Msk)) | (SYS_GPB_MFPH_PB10MFP_GPIO);
	GPIO_SetMode(PB,BIT10,GPIO_MODE_INPUT);
    #elif defined (USE_PE8_PE9)
	SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE9MFP_Msk)) | (SYS_GPE_MFPH_PE9MFP_GPIO);
	GPIO_SetMode(PE,BIT9,GPIO_MODE_INPUT);
    #endif   
}

void MDC_Set(uint8_t value) 
{
    GPIO_MDC = value ? 1 : 0 ;
}

void MDIO_Set(uint8_t value) 
{
    GPIO_MDIO = value ? 1 : 0 ;
}

// uint8_t MDIO_Read(void) 
// {
//     uint8_t value = 0;

//     #if defined (USE_PB11_PB10)
// 	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB10MFP_Msk)) | (SYS_GPB_MFPH_PB10MFP_GPIO);
// 	GPIO_SetMode(PB,BIT10,GPIO_MODE_INPUT);
//     #elif defined (USE_PE8_PE9)
// 	SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE9MFP_Msk)) | (SYS_GPE_MFPH_PE9MFP_GPIO);
// 	GPIO_SetMode(PE,BIT9,GPIO_MODE_INPUT);
//     #endif   

//     value = GPIO_MDIO;

//     #if defined (USE_PB11_PB10)
// 	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB10MFP_Msk)) | (SYS_GPB_MFPH_PB10MFP_GPIO);
// 	GPIO_SetMode(PB,BIT10,GPIO_MODE_OUTPUT);
//     #elif defined (USE_PE8_PE9)
// 	SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE9MFP_Msk)) | (SYS_GPE_MFPH_PE9MFP_GPIO);
// 	GPIO_SetMode(PE,BIT9,GPIO_MODE_OUTPUT);
//     #endif   

//     return value;
// }

/*
    int volatile delay = SystemCoreClock / 1000000 * 10;
    for(; delay > 0UL; delay--)
    {
        __NOP();
    }

*/
// 2.5MHz = 400 ns
void MDIO_delay(void) 
{
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

void MDC_Cycle(void) 
{
    MDC_Set(1);
    MDIO_delay();
    MDC_Set(0);
    MDIO_delay();
}


uint8_t MDIO_ReadBit(void) 
{
    uint8_t val = 0;

    MDIO_IN();

    MDC_Set(1);
    MDIO_delay();

    val = GPIO_MDIO;

    MDC_Set(0);
    MDIO_delay();

    MDIO_OUT();

    return val;
}


void MDIO_WriteBit(uint8_t value) 
{
    MDIO_Set(value);
    MDC_Cycle();
}


uint16_t software_MDIO_ReadRegister(uint8_t phyAddr, uint8_t regAddr) 
{
    uint16_t rdata = 0;
    int i = 0;

    __disable_irq();
    
    MDIO_OUT();

    //PREAMBLE : send 32  x bit 1 
    for (i = 0; i < 32; i++) 
    {
        #if 1
        MDIO_WriteBit(1);
        #else
        MDIO_Set(1);
        MDC_Cycle();
        #endif
    }

    //START OF FRAME , 01
    #if 1
    MDIO_WriteBit(0);
    MDIO_WriteBit(1);
    #else
    MDIO_Set(0);
    MDC_Cycle();
    MDIO_Set(1);
    MDC_Cycle();
    #endif

    //OP , READ : 10
    #if 1
    MDIO_WriteBit(1);
    MDIO_WriteBit(0);
    #else
    MDIO_Set(1);
    MDC_Cycle();
    MDIO_Set(0);
    MDC_Cycle();
    #endif

    //PATAD : PHY addr 5 bit
    for (i = 4; i >= 0; i--) 
    {
        #if 1
        MDIO_WriteBit((phyAddr >> i) & 0x01);
        #else
        MDIO_Set((phyAddr >> i) & 0x01);
        MDC_Cycle();
        #endif
    }

    //DEVAD : reg addr 5 bit
    for (i = 4; i >= 0; i--) 
    {
        #if 1
        MDIO_WriteBit((regAddr >> i) & 0x01);
        #else
        MDIO_Set((regAddr >> i) & 0x01);
        MDC_Cycle();
        #endif
    }

    //TA : turn around , 2 clock , Z0
    #if 1
    MDIO_WriteBit(1);
    MDIO_WriteBit(1);
    #else
    MDIO_Set(1);
    MDC_Cycle();
    MDIO_Set(1);
    MDC_Cycle();
    #endif

    // read data 16 bit
    for (i = 15; i >= 0; i--) 
    {
        #if 1
        rdata |= (MDIO_ReadBit() << i);
        #else
        MDC_Cycle();
        data |= (MDIO_Read() << i);
        #endif
    }
    
    //TA : turn around
    #if 1
    MDIO_WriteBit(0);
    #else
    MDC_Cycle();
    MDIO_Set(0);
    #endif

    __enable_irq();

    return rdata;
}

void software_MDIO_WriteRegister(uint8_t phyAddr, uint8_t regAddr, uint16_t wdata) 
{
    int i = 0;

    __disable_irq();

    MDIO_OUT();

    //PREAMBLE : send 32  x bit 1 
    for (i = 0; i < 32; i++) 
    {
        #if 1
        MDIO_WriteBit(1);
        #else
        MDIO_Set(1);
        MDC_Cycle();
        #endif
    }

    //START OF FRAME , 01
    #if 1
    MDIO_WriteBit(0);
    MDIO_WriteBit(1);
    #else
    MDIO_Set(0);
    MDC_Cycle();
    MDIO_Set(1);
    MDC_Cycle();
    #endif

    //OP , WRITE :01
    #if 1
    MDIO_WriteBit(0);
    MDIO_WriteBit(1);
    #else
    MDIO_Set(0);
    MDC_Cycle();
    MDIO_Set(1);
    MDC_Cycle();
    #endif

    //PATAD : PHY addr 5 bit
    for (i = 4; i >= 0; i--) 
    {
        #if 1
        MDIO_WriteBit((phyAddr >> i) & 0x01);
        #else
        MDIO_Set((phyAddr >> i) & 0x01);
        MDC_Cycle();
        #endif
    }

    //DEVAD : reg addr 5 bit
    for (i = 4; i >= 0; i--) 
    {
        #if 1
        MDIO_WriteBit((regAddr >> i) & 0x01);
        #else
        MDIO_Set((regAddr >> i) & 0x01);
        MDC_Cycle();
        #endif
    }

    //TA : turn around , 2 clock , 10
    #if 1
    MDIO_WriteBit(1);
    MDIO_WriteBit(0);
    #else
    MDIO_Set(1);
    MDC_Cycle();
    MDIO_Set(0);
    MDC_Cycle();
    #endif

    // write data 16 bit
    for (i = 15; i >= 0; i--) 
    {
        #if 1
        MDIO_WriteBit((wdata >> i) & 0x01);
        #else
        MDIO_Set((data >> i) & 0x01);
        MDC_Cycle();
        #endif
    }

    //TA : turn around
    #if 1
    MDIO_WriteBit(0);
    #else
    MDIO_Set(0);
    MDC_Cycle();
    #endif

    __enable_irq();
}

#if defined (FUNC_IN_SRAM)
#pragma arm section
#endif
