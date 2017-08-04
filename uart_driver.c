/* Lib Includes */
#include <msp430f2274.h>
#include <string.h>

/* Definitions */
#define UARTA0_PORT_NO		0x03	/* P3 */
#define UARTA0_PINS_MUX_VAL	0x30	/* P3.4(TXD) & P3.5(RXD) */

/* Globals */
char rec_uart_byte = 0;

/****************************************************************
 * Function Name	:uart_mux_pins
 * Description		:Configures GPIO P3.4 & P3.5 as UART pins
 * Returns		:None
 * Params		:None
 ****************************************************************/
static void
uart_mux_pins ()
{
  signed char ret;
  if (ret = gpio_mux (UARTA0_PORT_NO, UARTA0_PINS_MUX_VAL) == -1)
    {
      /* Debug Code - LED blinks 5 times indicating a fault */
    }
  else
    {
      /* Debug Code - LED blinks 2 times indicating all good */
    }
}

/****************************************************************
 * Function Name	:uart_configure
 * Description		:Configure the UARTA0 control registers
 * Returns		:None
 * Params		:None
 ****************************************************************/
static void
uart_configure ()
{
  /* Register Settings */
  UCA0CTL0 = 0x00;
  UCA0CTL1 |= UCSWRST + UCSSEL_2;
  UCA0BR0 = 0x41;
  UCA0BR1 = 0x03;
  UCA0MCTL = UCBRS_1;
  UCA0CTL1 &= ~UCSWRST;

  /* Enable RXD Interrupts */
  IE2 |= UCA0RXIE;

  /* Enable Global/Maskable Interrupts */
  _BIS_SR (GIE);
}

/****************************************************************
 * Function Name	:uart_init
 * Description		:Initialize the UARTA0
 * Returns		:None
 * Params		:None
 ****************************************************************/
void
uart_init ()
{
  uart_mux_pins ();
  uart_configure ();
}

/****************************************************************
 * Function Name	:Uart_PrintStr
 * Description		:Prints a string on the terminal
 * Returns		:Length of the string
 * Params		:@str_ptr = Pointer to a string.
 ****************************************************************/
unsigned char
Uart_PrintStr (char *str_ptr)
{
  int len = 0, i = 0, ret = 0;
  len = strlen (str_ptr);
  ret = len;
  while (len != 0)
    {
      while (!(IFG2 & UCA0TXIFG));
      UCA0TXBUF = str_ptr[i++];
      len--;
    }
  return (ret);
}

//-----------------------------------------------------------------------//
//                          Receive Interrupt                            //
//-----------------------------------------------------------------------//

#pragma vector = USCIAB0RX_VECTOR
__interrupt void
ReceiveInterrupt (void)
{
  rec_uart_byte = UCA0RXBUF;
  IFG2 &= ~UCA0RXIFG;
}
