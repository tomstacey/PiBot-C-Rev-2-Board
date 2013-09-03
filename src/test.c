#include <bcm2835.h>

#define GPIO_0 RPI_V2_GPIO_P1_11
#define GPIO_1 RPI_V2_GPIO_P1_12
#define GPIO_2 RPI_V2_GPIO_P1_13

#define GPIO_3 RPI_V2_GPIO_P1_15
#define GPIO_4 RPI_V2_GPIO_P1_16
#define GPIO_5 RPI_V2_GPIO_P1_18

int main(int argc, char **argv)
{

    delay(1000);

    if (!bcm2835_init())
        return 1;

// Set GPIO to outputs  to drive forward
    bcm2835_gpio_write(GPIO_0, HIGH);


// Motor A - Low High = Track Right - Rev 
//    bcm2835_gpio_write(GPIO_1, LOW);
//    bcm2835_gpio_write(GPIO_2, HIGH);

	bcm2835_gpio_write(GPIO_1, LOW);
	bcm2835_gpio_write(GPIO_2, HIGH);


// Motor controller B - enable
    bcm2835_gpio_write(GPIO_3, HIGH);

// Motor B
    bcm2835_gpio_write(GPIO_4, LOW);
   bcm2835_gpio_write(GPIO_5, HIGH);

}
