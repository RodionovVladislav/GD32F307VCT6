#include "gd32f30x.h"                   // Device header
#include "gd32f30x_gpio.h"              // GigaDevice::Device:GD32F30x_StdPeripherals:GPIO
#include "gd32f30x_rcu.h"               // GigaDevice::Device:GD32F30x_StdPeripherals:RCU
#include <stdint.h>

void Delay (void)
{
	for ( uint16_t i = 0; i <= 50000; i++ )
		for( uint16_t j = 0; j <= 25; j++ );
}

int main(void) 
{
	RCU_APB2EN;
	
	
	while(1)
	{
	  GPIO_BOP_CR13;
		Delay();
		GPIO_BOP_CR13;
	}
}
