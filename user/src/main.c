#include "gd32f30x.h"                   // Device header
#include "gd32f30x_gpio.h"              // GigaDevice::Device:GD32F30x_StdPeripherals:GPIO
#include "gd32f30x_rcu.h"               // GigaDevice::Device:GD32F30x_StdPeripherals:RCU
#include <stdint.h>

#define DEVICE_ID (uint32_t 0x)

#define DELAY			100
#define FAST			1
#define SLLOW			4

uint8_t g_speed = FAST;
uint16_t timer_pr = 0xFFFF;
uint16_t timer_dt = 0x0001;
uint16_t timer_dt_inc = 0x008F;
uint16_t presceler_value = 0;
timer_channel_output_config timer_oc_init_structure;

void button_exint_init(void)
{
  
}

void button_isr(void)
{

}

void EXINT0_IRQHandler(void)
{
  button_isr();
}


int main(void) 
{
	
	
	
	while(1)
	{
	  
		
		
	}
}
