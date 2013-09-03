#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

#define GPIO_0 RPI_V2_GPIO_P1_11
#define GPIO_1 RPI_V2_GPIO_P1_12
#define GPIO_2 RPI_V2_GPIO_P1_13
#define GPIO_3 RPI_V2_GPIO_P1_15
#define GPIO_4 RPI_V2_GPIO_P1_16
#define GPIO_5 RPI_V2_GPIO_P1_18

void forward();

int main(int argc, char *argv[])
{
int i, loop;

if (!bcm2835_init())
        return 1;


        printf( "parameter %s \n", argv[1] );

	i = atoi (argv[1]);

for(loop=0; loop<=250; loop++)
{
        printf( "Loop = %i \n", loop);

        forward();
        delay(i);
       // left(1800);
       // delay(i);
        reverse();
        delay(i);
       // left();
        //delay(1800);

}

}

stop()
{
// Set GPIO to outputs to stop PiBot
    bcm2835_gpio_write(GPIO_0, LOW);
    bcm2835_gpio_write(GPIO_1, LOW);
    bcm2835_gpio_write(GPIO_2, LOW);

    bcm2835_gpio_write(GPIO_3, LOW);
    bcm2835_gpio_write(GPIO_4, LOW);
    bcm2835_gpio_write(GPIO_5, LOW);
}

void forward()
{
    // Set GPIO to outputs  to drive forward
    bcm2835_gpio_write(GPIO_0, HIGH);
    bcm2835_gpio_write(GPIO_1, HIGH);
    bcm2835_gpio_write(GPIO_2, LOW);

    bcm2835_gpio_write(GPIO_3, HIGH);
    bcm2835_gpio_write(GPIO_4, HIGH);
    bcm2835_gpio_write(GPIO_5, LOW);
}

reverse()
{
    // Set GPIO to outputs  to drive  reverse
    bcm2835_gpio_write(GPIO_0, HIGH);
    bcm2835_gpio_write(GPIO_1, LOW);
    bcm2835_gpio_write(GPIO_2, HIGH);

    bcm2835_gpio_write(GPIO_3, HIGH);
    bcm2835_gpio_write(GPIO_4, LOW);
    bcm2835_gpio_write(GPIO_5, HIGH);
}

left()
{
// Set GPIO to outputs  to drive left
    bcm2835_gpio_write(GPIO_0, HIGH);
    bcm2835_gpio_write(GPIO_1, LOW);
    bcm2835_gpio_write(GPIO_2, HIGH);

    bcm2835_gpio_write(GPIO_3, HIGH);
    bcm2835_gpio_write(GPIO_4, HIGH);
    bcm2835_gpio_write(GPIO_5, LOW);
}

right()
{
// Set GPIO to outputs  to drive right
    bcm2835_gpio_write(GPIO_0, HIGH);
    bcm2835_gpio_write(GPIO_1, HIGH);
    bcm2835_gpio_write(GPIO_2, LOW);
    bcm2835_gpio_write(GPIO_3, HIGH);
    bcm2835_gpio_write(GPIO_4, LOW);
    bcm2835_gpio_write(GPIO_5, HIGH);
}
	
	
