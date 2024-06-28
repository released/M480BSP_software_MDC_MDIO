/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

void MDC_MDIO_Init(void);
uint16_t software_MDIO_ReadRegister(uint8_t phyAddr, uint8_t regAddr);
void software_MDIO_WriteRegister(uint8_t phyAddr, uint8_t regAddr, uint16_t wdata);

