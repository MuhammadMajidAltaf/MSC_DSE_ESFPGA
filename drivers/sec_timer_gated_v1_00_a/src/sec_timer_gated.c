//////////////////////////////////////////////////////////////////////////////
// Filename:          D:\Xtemp\hrm506_EMB\Lab56/drivers/sec_timer_gated_v1_00_a/src/sec_timer_gated.c
// Version:           1.00.a
// Description:       sec_timer_gated Driver Source File
// Date:              Fri Mar 18 16:29:04 2011 (by Create and Import Peripheral Wizard)
//////////////////////////////////////////////////////////////////////////////


/***************************** Include Files *******************************/

#include "sec_timer_gated.h"

/************************** Function Definitions ***************************/

/**
 *
 * Enable all possible interrupts from SEC_TIMER_GATED device.
 *
 * @param   baseaddr_p is the base address of the SEC_TIMER_GATED device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void SEC_TIMER_GATED_EnableInterrupt(void * baseaddr_p)
{
  Xuint32 baseaddr;
  baseaddr = (Xuint32) baseaddr_p;

  /*
   * Enable all interrupt source from user logic.
   */
  SEC_TIMER_GATED_mWriteReg(baseaddr, SEC_TIMER_GATED_INTR_IPIER_OFFSET, 0x00000001);

  /*
   * Enable all possible interrupt sources from device.
   */
  SEC_TIMER_GATED_mWriteReg(baseaddr, SEC_TIMER_GATED_INTR_DIER_OFFSET,
    INTR_TERR_MASK
    | INTR_DPTO_MASK
    | INTR_IPIR_MASK
    );

  /*
   * Set global interrupt enable.
   */
  SEC_TIMER_GATED_mWriteReg(baseaddr, SEC_TIMER_GATED_INTR_DGIER_OFFSET, INTR_GIE_MASK);
}

/**
 *
 * Example interrupt controller handler for SEC_TIMER_GATED device.
 * This is to show example of how to toggle write back ISR to clear interrupts.
 *
 * @param   baseaddr_p is the base address of the SEC_TIMER_GATED device.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void SEC_TIMER_GATED_Intr_DefaultHandler(void * baseaddr_p)
{
  Xuint32 baseaddr;
  Xuint32 IntrStatus;
Xuint32 IpStatus;
  baseaddr = (Xuint32) baseaddr_p;

  /*
   * Get status from Device Interrupt Status Register.
   */
  IntrStatus = SEC_TIMER_GATED_mReadReg(baseaddr, SEC_TIMER_GATED_INTR_DISR_OFFSET);

  xil_printf("Device Interrupt! DISR value : 0x%08x \n\r", IntrStatus);

  /*
   * Verify the source of the interrupt is the user logic and clear the interrupt
   * source by toggle write baca to the IP ISR register.
   */
  if ( (IntrStatus & INTR_IPIR_MASK) == INTR_IPIR_MASK )
  {
    xil_printf("User logic interrupt! \n\r");
    IpStatus = SEC_TIMER_GATED_mReadReg(baseaddr, SEC_TIMER_GATED_INTR_IPISR_OFFSET);
    SEC_TIMER_GATED_mWriteReg(baseaddr, SEC_TIMER_GATED_INTR_IPISR_OFFSET, IpStatus);
  }

}

