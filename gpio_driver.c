/* Include's */
#include <msp430f2274.h>
#include "common_utils.h"

/* Definitions */
#define MAX_PIN_NO_INVALID  255

/****************************************************************
 * Function Name :      gpio_out_initdef
 * Description   :      Initialize  PxOUT registers to 0x00
 * Returns       :      None
 * Params        :      None
 ****************************************************************/
void
gpio_out_initdef ()
{
  P1OUT = P2OUT = P3OUT = P4OUT = 0x00;
}

/****************************************************************
 * Function Name :	gpio_configure
 * Description	 :	Configures GPIO as I/O
 * Returns	 :	0 = Success
                 	-1 = Fail
 * Params	 : 	@port_no = Port No.
                   	@pins_no = Pins in the port to configure
 ****************************************************************/
signed char
gpio_configure (unsigned char port_no, unsigned char pins_no,
		GPIO_E_CONF gpio_in_out)
{
  signed char ret = 0;
  if (pins_no > MAX_PIN_NO_INVALID)
    port_no = 0;
  if (gpio_in_out == OUTPUT)
    switch (port_no)
      {
      case 1:
	P1DIR = pins_no;
	break;
      case 2:
	P2DIR = pins_no;
	break;
      case 3:
	P3DIR = pins_no;
	break;
      case 4:
	P4DIR = pins_no;
	break;
      default:
	ret = -1;
      }
  if (gpio_in_out == INPUT)
    switch (port_no)
      {
      case 1:
	P1DIR &= ~pins_no;
	break;
      case 2:
	P2DIR &= ~pins_no;
	break;
      case 3:
	P3DIR &= ~pins_no;
	break;
      case 4:
	P4DIR &= ~pins_no;
	break;
      default:
	ret = -1;
      }
  return (ret);
}

/****************************************************************
 * Function Name :	gpio_write
 * Description	 :	Sets gpio HIGH or LOW
 * Returns	 :	0 = Success
                       -1 = Fail
 * Params	 :	@port_no = Port No.
                        @pins_no = Pins to set HIGH or LOW
 ****************************************************************/
signed char
gpio_write (unsigned char port_no, unsigned char pin_no_val)
{
  signed char ret = 0;
  if (pin_no_val > MAX_PIN_NO_INVALID)
    port_no = 0;
  switch (port_no)
    {
    case 1:
      P1OUT = pin_no_val;
      break;
    case 2:
      P2OUT = pin_no_val;
      break;
    case 3:
      P3OUT = pin_no_val;
      break;
    case 4:
      P4OUT = pin_no_val;
      break;
    default:
      ret = -1;
    }
  return (ret);
}

/****************************************************************
 * Function Name :	gpio_read
 * Description	 :	Reads the status of the gpio
 * Returns	 :	0 or 1 = Success
                       -1 = Fail
 * Params	 :	@port_no = Port No.
                        @pins_no = Pin to be read
 ****************************************************************/
signed char
gpio_read (unsigned char port_no, unsigned char pin_no)
{
  signed char ret = 0;
  if ((pin_no == BIT0) || (pin_no == BIT1) || (pin_no == BIT2)
      || (pin_no == BIT3) || (pin_no == BIT4) || (pin_no == BIT5)
      || (pin_no == BIT6) || (pin_no == BIT7))
    {
      /* Do Nothing */
    }
  else
    {
      port_no = 0;
    }
  switch (port_no)
    {
    case 1:
      ret = P1IN & pin_no;
      break;
    case 2:
      ret = P2IN & pin_no;
      break;
    case 3:
      ret = P3IN & pin_no;
      break;
    case 4:
      ret = P4IN & pin_no;
      break;
    default:
      ret = -1;
    }
  return (ret);
}

/****************************************************************
 * Function Name :	gpio_mux
 * Description   :	Select GPIO alternate function
 * Returns       :	0 = Success
                       -1 = Fail
 * Params        :      @port_no = Port No.
                        @pins_no = Pins to mux
 ****************************************************************/
signed char
gpio_mux (unsigned char port_no, unsigned char pins_no)
{
  signed char ret = 0;
  if (pins_no > MAX_PIN_NO_INVALID)
    port_no = 0;
  switch (port_no)
    {
    case 1:
      P1SEL |= pins_no;
      break;
    case 2:
      P2SEL |= pins_no;
      break;
    case 3:
      P3SEL |= pins_no;
      break;
    case 4:
      P4SEL |= pins_no;
      break;
    default:
      ret = -1;
    }
  return (ret);
}
