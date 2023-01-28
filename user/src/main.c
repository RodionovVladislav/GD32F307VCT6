#include "gd32f30x.h"                   // Device header
#include "gd32f30x_libopt.h"
#include "gd32f307c_eval.h"
#include <stdint.h>

#define DEVICE_ID ((uint32_t) 0x1FFFF7E0)

#define DELAY			100
#define FAST			1
#define SLOW			4

uint8_t g_speed = FAST;
uint16_t timer_pr = 0xFFFF;
uint16_t timer_dt = 0x0001;
uint16_t timer_dt_inc = 0x008F;
uint16_t presceler_value = 0;
timer_oc_parameter_struct timer_ocinitpara;

void button_exint_init(void);
void button_isr(void);

void chipid_test(void);

void gpio_blink(uint16_t ms_on, uint16_t ms_off);








void button_exint_init(void)
{
	
	
	
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
}


void pb9_output_init(void)
{
  FlagStatus bit_state;
  bit_state = gpio_output_bit_get(GPIOB,GPIO_PIN_9);
}


void button_isr(void)
{
  delay(5);
  exti_flag_clear(EXTI_0);
  if(SET == gpio_input_data_bit_read(USER_BUTTON_PORT, USER_BUTTON_PIN))
  {
    if(g_speed == SLOW)
      g_speed = FAST;
    else
      g_speed = SLOW;
  }
}


void chipid_test(void)
{
	uint32_t device_id = dbg_id_get();
	if (device_id != DEVICE_ID)
	{
		pb9_output_init();
		while(1)
		{
			gpio_blink(100, 1000);
		}
	}
}


int main(void) 
{
	
	
	
	while(1)
	{
	  
		
		
	}
}
