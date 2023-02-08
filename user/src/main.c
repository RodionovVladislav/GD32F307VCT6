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
//timer_oc_parameter_struct timer_ocinitpara;

void pb9_output_init(void);
uint32_t pb9_remap = 0;


void button_exti_init(void);
void button_isr(void);

void chipid_test(void);
void flash_test(void);

void leds_init(void);
void gpio_blink(uint16_t ms_on, uint16_t ms_off);
void gpio_test(uint8_t n_cycles, uint16_t n_ms);

void rcu_configuration(void);
void tmr3_ch3_init(void);
void tmr3_ch3_change_dt(void);
void pb9_mux_init(void);
void timer3_test(uint8_t n_cycles);

void pb9_init(MODE);
void pb9_remap_set(uint32_t remap);
void pb9_remap_reset(void);
//void pb9_mux_init(void);



void pb9_output_init(void)
{
	FlagStatus pb9_mode;
  pb9_mode = gpio_output_bit_get(GPIOB, GPIO_PIN_9);
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

/**void gpio_blink(uint16_t ms_on, uint16_t ms_off)
{
	gpio_bit_set(TARGET_GPIO, TARGET_PIN);
	delay_1ms(ms_on);
	gpio_bit_reset(TARGET_GPIO, TARGET_PIN);
	delay_1ms(ms_off);
}*/
void leds_init(void)
{
	systick_config();
	gd_eval_led_init(LED2);
	gd_eval_led_init(LED3);
	gd_eval_led_init(LED4);
	gd_eval_led_init(LED5);
}


void gpio_blink(uint16_t ms_on, uint16_t ms_off)
{
	leds_init();
	gd_eval_led_on(LED2);
	delay_1ms(ms_on);
	gd_eval_led_off(LED2);
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

void flash_test(void)
{
	const uint16_t page_size = 2048;
	const uint32_t erased = 0xffffffff;
	const uint32_t written = 0xcccccccc;
	uint8_t fault = 0;
	
	fmc_unlock();
	for (uint32_t addr = FMC_ADDR0; addr < FMC_BANK0_END_ADDRESS; addr += page_size)
	{
		
	}
}


void gpio_test(uint8_t n_cycles, uint16_t n_ms)
{
	pb9_output_init();
	for (uint8_t j = 0; j < n_cycles; j++)
	{
		gpio_blink(n_ms, n_ms);
	}
}

/**
  * @brief  configures the different peripheral clocks.
  * @param  none
  * @retval none
  */
void rcu_configuration(void)
{
	/* tmr3 clock enable */
	rcu_periph_clock_enable(RCU_TIMER3);
	/* gpiob clock enable */
	rcu_periph_clock_enable(GPIOB);
}

void tmr3_ch3_init(void)
{
	timer_parameter_struct timer_initpara;
	timer_initpara.prescaler = 107;
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 999;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 1;
	timer_init(TIMER3,&timer_initpara);
	
	
	timer_oc_parameter_struct timer_ocinitpara;
	timer_ocinitpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocinitpara.outputnstate = TIMER_CCXN_ENABLE;
	timer_ocinitpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocinitpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_ocinitpara.ocidlestate = TIMER_OC_IDLE_STATE_HIGH;
	timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
	timer_channel_output_config(TIMER3,TIMER_CH_3, &timer_ocinitpara);
	
	timer_channel_output_struct_para_init(&timer_ocinitpara);
	timer_channel_output_mode_config(TIMER3,TIMER_CH_3, TIMER_OC_MODE_PWM0);
	timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_3, tmr_dt);

	//tmr_output_channel_buffer_enable(TMR4, TMR_SELECT_CHANNEL_4, TRUE);

  //tmr_period_buffer_enable(TMR4, TRUE);

  //tmr_counter_enable(TMR4, TRUE);
}


void tmr3_ch3_change_dt(void)
{
	while(timer_flag_get(TIMER3, ) == RESET);
	timer_flag_clear(TIMER3, );
	tmr_dt += tmr_dt_inc;
	timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_3, tmr_dt);
}


void timer3_test(uint8_t n_cycles)
{
	rcu_configuration();
	pb9_mux_init();
	
}


void pb9_init(MODE)
{
	/* enable the gpiob clock */
	rcu_periph_clock_enable(GPIOB);
	
	gpio_init (GPIOB, MODE, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
}


void pb9_remap_set(uint32_t remap)
{
	  if (remap != 0)
  {
	pb9_remap = remap;
    gpio_pin_remap_config(pb9_remap, ENABLE);
  }
}


void pb9_remap_reset(void)
{
	  if (pb9_remap != 0)
  {
    gpio_pin_remap_config(pb9_remap, DISABLE);
    pb9_remap = 0;
  }
}

/**
  * @brief  PB9 initialization for OUTPUT functions.
  * @param  none
  * @retval none
  */
void pb9_out_init(void)
{
  pb9_init(GPIO_MODE_OUT_PP);
}


void pb9_mux_init(void)
{
	
}

/**
  * @brief  generates uint with n set bits (from 0x0 to 0xFFFFFFFF)
  * @param  n: number of bits to set (from 0 to 32)
  * @retval uint with n set bits
  */
uint32_t get_n_bits(uint8_t n)
{
  return n < 32 ? (1 << n) - 1 : 0xFFFFFFFF;
}


int main(void) 
{
	
	
	
	while(1)
	{
	  
		
		
	}
}
