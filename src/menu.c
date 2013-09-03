#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <bcm2835.h>

// Define the GPIO pins
#define MotorA_Enable RPI_V2_GPIO_P1_11 //Motor controller Motor A & B - enable
#define MotorA_Input1 RPI_V2_GPIO_P1_12 //Motor controller Motor A input 1
#define MotorA_Input2 RPI_V2_GPIO_P1_13 //Motor controller Motor A input 2
#define MotorB_Input3 RPI_V2_GPIO_P1_16 //Motor controller Motor B - input 3
#define MotorB_Input4 RPI_V2_GPIO_P1_18 //Motor controller Motor B - input 4

#define Kill_Switch_Status RPI_V2_GPIO_P1_10	// Kill switch status

int varchar;

main()
{ 
	int ProgramExtit;
  	if (!bcm2835_init())
        	return 1;

	ProgramExtit = 1;

	setup();
		
	do{
		printf("PiBot Control Menu -v1.0 \n\n");
		printf("1. Setup\n");
		printf("2. Forward\n");
		printf("3. Reverse\n");
		printf("4. Left\n");
		printf("5. Right\n");
		printf("6. Stop\n");
		printf("7. Read GPIO 15 (kill switch status input \n");
		printf("8. Exit\n");

		varchar = getch();
 		printf("%c \n", varchar);  
 
		switch(varchar)
		{
			case '1' : printf("Setup \n" );
             		setup();
             		break;
  			case '2' : printf("Forward \n" );
	     		forward();
             		break;
  			case '3' : printf("Reverse \n" );
             		reverse();
             		break;
  			case '4' : printf("Left \n" );
             		left();
	     		break;
  			case '5' : printf("Right \n" );
             		right();
	     		break;
  			case '6' : printf("Stop \n");
 	     		stop();
             		break;
			case '7' : printf("Read GPIO 15 \n");
			readinput();
			break;
  			case '8' : printf("Exit \n");
			ProgramExtit = 0;
             		break;  
 		}
 	}
 	while(ProgramExtit == 1);

	bcm2835_close();
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

setup()
{
    // Set GPIO to outputs for Motor A control lines
    bcm2835_gpio_fsel(MotorA_Enable, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorA_Input1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorA_Input2, BCM2835_GPIO_FSEL_OUTP);
	
    // Set GPIO 15 as an input, to read the status of the kill switch
    bcm2835_gpio_fsel(Kill_Switch_Status, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_fsel(MotorB_Input3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorB_Input4, BCM2835_GPIO_FSEL_OUTP);
}

forward()
{
   uint8_t ReadInput;


	// Set GPIO to outputs  to drive forward
    bcm2835_gpio_write(MotorA_Enable, HIGH);	

    // Set motor A - Forward direction
    bcm2835_gpio_write(MotorA_Input1, HIGH);
    bcm2835_gpio_write(MotorA_Input2, LOW);

    // Set Motor B - Forward direction
    bcm2835_gpio_write(MotorB_Input3, HIGH);
    bcm2835_gpio_write(MotorB_Input4, LOW);

   // Read the kill switch status if set, stop  PiBot

	ReadInput = bcm2835_gpio_lev(Kill_Switch_Status);
	printf("read from pin 15: %d\n", ReadInput);
        if(ReadInput == 1)
	{
		printf("Kill switch has been activated - stopped \n");
		stop();
	}

}

reverse()
{
	// Set GPIO to outputs for Motor A control lines
    bcm2835_gpio_write(MotorA_Enable, HIGH);
//    bcm2835_gpio_write(MotorB_Enable, HIGH);	
   
	// Set GPIO to outputs for Motor A to rev	
    bcm2835_gpio_write(MotorA_Input1, LOW);
    bcm2835_gpio_write(MotorA_Input2, HIGH);
	
    // Set GPIO to outputs for Motor B to rev
    bcm2835_gpio_write(MotorB_Input3, LOW);
    bcm2835_gpio_write(MotorB_Input4, HIGH);
}

left()
{
  // Set GPIO to outputs for Motor A control lines
    bcm2835_gpio_write(MotorA_Enable, HIGH);
//    bcm2835_gpio_write(MotorB_Enable, HIGH);	
   
// Set GPIO to outputs for Motor A to rev	
	
    bcm2835_gpio_write(MotorA_Input1, LOW);
    bcm2835_gpio_write(MotorA_Input2, HIGH);
	
    // Set GPIO to outputs for Motor B to forward

    bcm2835_gpio_write(MotorB_Input3, HIGH);
    bcm2835_gpio_write(MotorB_Input4, LOW);


}

right()
{
 // Set GPIO to outputs for Motor A control lines
    bcm2835_gpio_write(MotorA_Enable, HIGH);
//    bcm2835_gpio_write(MotorB_Enable, HIGH);	
	
	// Set GPIO to outputs for Motor A to forward	
	
    bcm2835_gpio_write(MotorA_Input1, HIGH);
    bcm2835_gpio_write(MotorA_Input2, LOW);
	
	// Set GPIO to outputs for Motor B to rev

    bcm2835_gpio_write(MotorB_Input3, LOW);
    bcm2835_gpio_write(MotorB_Input4, HIGH);
}


stop()
{
  // Set GPIO to outputs to stop PiBot
	// Disable the two motor chip control lines
    bcm2835_gpio_write(MotorA_Enable, LOW);
//    bcm2835_gpio_write(MotorB_Enable, LOW);
	
	// Switch off the motor A control lines
    bcm2835_gpio_write(MotorA_Input1, LOW);
    bcm2835_gpio_write(MotorA_Input2, LOW);
	
	// Switch off the motor B control lines
    bcm2835_gpio_write(MotorB_Input3, LOW);
    bcm2835_gpio_write(MotorB_Input4, LOW);

}

readinput()
{
	uint8_t value = bcm2835_gpio_lev(Kill_Switch_Status);
	printf("read from pin 15: %d\n", value);

}
