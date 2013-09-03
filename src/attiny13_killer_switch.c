#define F_CPU 9600000UL // Define software reference clock for delay duration
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define the state machine defintations
#define WAITING_RPI_DC_MOTOR_ENABLE		0x01
#define DC_MOTOR_IC_ENABLED				0x02
#define WAITING_RPI_DC_ENABLE_TO_GO_LOW 0x03

volatile uint8_t SM_Status, timer_overflow_count;

/*
 PORTB &= ~(1 << LED); // Set 0 on LED pin (led turn on)
 PORTB |= (1 << LED); // Set 1 on LED pin (led turn off)
*/

int main(void)
{
	uint8_t x;
	
	// ======================================================================
	// Setup the attiny13 GPIO
	// PB0 - Killer switch - input (Connector) [Resistor pull up enabled]
	// PB1 - RPi motor enable - input (RPi RPI_V2_GPIO_P1_11) [Resistor pull up enabled]
	// PB2 - Killer switch status - output (RPi RPI_V2_GPIO_P1_15)
	// PB4 - DC motor IC enable status - output (DC motor controller pin 1 & 9)
	// PB5 - Status LED - output
	// ======================================================================
	DDRB = 0x3c;
		
	DDRB &= ~(1 << PB0);		
	DDRB &= ~(1 << PB1);
	PORTB = 0x03;
	
	status_LED_switch_off();
	dc_motor_disable();
	kill_status_off();

	// prescale timer to 1/1024th the clock rate
	TCCR0B |= (1<<CS02) | (1<<CS00);

	// enable timer overflow interrupt
	TIMSK0 |=1<<TOIE0;
	sei();

	// Set the default state for the state machine
	SM_Status = WAITING_RPI_DC_MOTOR_ENABLE;
		
    while(1)
    {
        // State Machine - Waiting for DC motor enable to become activate * kill switch input deactive
        if(SM_Status == WAITING_RPI_DC_MOTOR_ENABLE) 
		{
	        // Read RPI DC motor input, if active set DC Motor IC enable
			if(bit_is_set(PINB, PB0))
			{
				if (bit_is_set(PINB, PB1)) 
				{
					SM_Status = DC_MOTOR_IC_ENABLED;
					PORTB |= (1 << 3); 		// Set the DC motor IC enable line low (pull up on the PIN)
					//dc_motor_enable();
					status_LED_switch_on();
					kill_status_off();
				}
			}	
			else
			{
				PORTB &= ~(1 << 3);			// Clear the DC motor enable line high
			}					
			
		}
		if(SM_Status == DC_MOTOR_IC_ENABLED)
		{
			if (bit_is_clear(PINB, PB1))	// RPi DC motor enable gone low
			{
				SM_Status = WAITING_RPI_DC_MOTOR_ENABLE;
				PORTB &= ~(1 << 3);			// Clear the DC motor enable line high
				//dc_motor_disable();
				status_LED_switch_off();	
				kill_status_off();
			}
			
			// If kill switch input is high, switch off the DC motor IC enable line immediately
			if (bit_is_clear(PINB, PB0))		// ToDo : Add some debouce <TBC>
			{
				// set the DC motor controller IC enable to low
				SM_Status = WAITING_RPI_DC_ENABLE_TO_GO_LOW;
				PORTB &= ~(1 << 3);			// Clear the DC motor enable line high
				//dc_motor_disable();
				kill_status_on();
			}
	    	
		}			
     
	    // Need to wait for the RPi Enable to go low to reset the kill switch/enable logic
        if(SM_Status == WAITING_RPI_DC_ENABLE_TO_GO_LOW)
        {
	        // Reset back to waiting
			if(bit_is_clear(PINB, PB1)) // RPi DC motor enable gone low
			{
				SM_Status = WAITING_RPI_DC_MOTOR_ENABLE;
				status_LED_switch_off();
				kill_status_off();
			}			

        }
				
    }
}

	   
void status_LED_switch_on()
{
	PORTB |= (1 << PB4); 		// Switch on the status LED		
}

void status_LED_switch_off()
{
	PORTB &= ~(1 << PB4); 		// Switch off the status LED
}

// ===========================================================
void dc_motor_enable()
{
	PORTB |= (1 << PB3); 			
}

void dc_motor_disable()
{
	PORTB &= ~(1 << PB3); 		
}

// ===========================================================
void kill_status_on()
{
	PORTB |= (1 << PB2); 			
}

void kill_status_off()
{
	PORTB &= ~(1 << PB2); 		
}


ISR(TIM0_OVF_vect) 
{
	if(SM_Status == WAITING_RPI_DC_ENABLE_TO_GO_LOW)
	{
		if (++timer_overflow_count > 2) 
		{   // a timer overflow occurs 4.6 times per second
			// Toggle Port B pin 4 output state
			PORTB ^= 1<<PB4;
			timer_overflow_count = 0;
		}		
	}
}
