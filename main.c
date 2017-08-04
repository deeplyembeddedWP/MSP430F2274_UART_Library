/* Lib Includes */
#include <msp430f2274.h>
#include "common_utils.h"

/* Byte received from terminal */
extern char rec_uart_byte;

int
main ()
{
  unsigned char cnt = 0;

  WDTCTL = WDTPW + WDTHOLD;	// Stop the Watch dog

  if (CALBC1_8MHZ == 0xFF)	// If calibration constant erased
    {
      while (1);		// do not load, trap CPU!!
    }

  DCOCTL = 0;			// Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_8MHZ;	// Set range
  DCOCTL = CALDCO_8MHZ;		// Set DCO step + modulation 
  gpio_out_initdef ();		// Initialize GPIO DIR to default
  gpio_configure (0x01, BIT0, OUTPUT);	// Configure P1.0 as output
  for (cnt = 0; cnt < 3; cnt++)
    {
/*Blink LED for 3 times with 1 second delay */
      gpio_write (0x01, BIT0);
      __delay_cycles (8000000);
      gpio_write (0x01, 0x00);
      __delay_cycles (8000000);
    }

  uart_init ();			// Initialize the UART configuration
  Uart_PrintStr ("Welcome To DeeplyEmbedded!");	// Print string to terminal
  while (1)
    {
/* Reveive a byte from the terminal */
      if (rec_uart_byte == 'a')
	{
	  rec_uart_byte = 0;
	  Uart_PrintStr ("Hooray! The GPIO's and UART are up & running");
	}
    }
}
