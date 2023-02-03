#include "gd32f30x.h"                   // Device header
#include "gd32f30x_libopt.h"
#include "gd32f307c_eval.h"
#include "systick.h"
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

void pb9_output_init(void);
uint32_t pb9_remap = 0;


void button_exti_init(void);
void button_isr(void);

void chipid_test(void);

void gpio_blink(uint16_t ms_on, uint16_t ms_off);







void pb9_output_init(void)
{
  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_9);
}


void button_exti_init(void)
{
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_RISING);
	
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
	
	nvic_priority_group_set(NVIC_PRIGROUP_PRE0_SUB4);
	nvic_irq_enable(WWDGT_IRQn, 0, 0);
}


void button_isr(void)
{
  delay_1ms(5);
  exti_flag_clear(EXTI_0);
  if(SET == gpio_input_bit_get(GPIOA, GPIO_PIN_0))
  {
    if(g_speed == SLOW)
      g_speed = FAST;
    else
      g_speed = SLOW;
  }
}

void EXTI0_IRQHandler(void)
{
	button_isr();
}

void gpio_blink(uint16_t ms_on, uint16_t ms_off)
{
	gpio_bit_set();
	delay_1ms(ms_on);
	gpio_bit_reset();
	delay_1ms(ms_off);
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
