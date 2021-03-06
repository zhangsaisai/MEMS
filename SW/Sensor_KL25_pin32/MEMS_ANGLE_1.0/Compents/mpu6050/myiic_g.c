#include "myiic_g.h"
#include "MKL25Z4.h"
#include "PE_Types.h"


void IIC_Init_G(void)
{
    SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
    
    /* PORTB_PCR0: ISF=0,MUX=2 */
    PORTB_PCR0 = (uint32_t)((PORTB_PCR0 & (uint32_t)~(uint32_t)(
                  PORT_PCR_ISF_MASK |
                  PORT_PCR_MUX(0x06)
                 )) | (uint32_t)(
                  PORT_PCR_MUX(0x02)
                 ));  
    /* PORTB_PCR1: ISF=0,MUX=2 */
    PORTB_PCR1 = (uint32_t)((PORTB_PCR1 & (uint32_t)~(uint32_t)(
                  PORT_PCR_ISF_MASK |
                  PORT_PCR_MUX(0x06)
                 )) | (uint32_t)(
                  PORT_PCR_MUX(0x02)
                 ));    

    I2C0_F  = 0x20;
    I2C0_C1 = 0x80;
}
