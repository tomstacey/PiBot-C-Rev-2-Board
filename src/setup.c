#include <bcm2835.h>

#define MotorA_Enable RPI_V2_GPIO_P1_11 //Motor controller Motor A - enable
#define MotorA_Input1 RPI_V2_GPIO_P1_12 //Motor controller Motor A input 1
#define MotorA_Input2 RPI_V2_GPIO_P1_13 //Motor controller Motor A input 2

#define MotorB_Enable RPI_V2_GPIO_P1_15 //Motor controller Motor B - enable
#define MotorB_Input3 RPI_V2_GPIO_P1_16 //Motor controller Motor B - input 3
#define MotorB_Input4 RPI_V2_GPIO_P1_18 //Motor controller Motor B - input 4

int main(int argc, char **argv)
{

	// Check the bcm driver is present
    if (!bcm2835_init())
        return 1;

    // Set GPIO to outputs for Motor A control lines
    bcm2835_gpio_fsel(MotorA_Enable, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorA_Input1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorA_Input2, BCM2835_GPIO_FSEL_OUTP);
	
	// Set GPIO to outputs for Motor B control lines
    bcm2835_gpio_fsel(MotorB_Enable, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorB_Input3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MotorB_Input4, BCM2835_GPIO_FSEL_OUTP);

}
