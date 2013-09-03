#include <bcm2835.h>

#define GPIO_0 RPI_V2_GPIO_P1_11
#define GPIO_1 RPI_V2_GPIO_P1_12
#define GPIO_2 RPI_V2_GPIO_P1_13
#define GPIO_3 RPI_V2_GPIO_P1_15
#define GPIO_4 RPI_V2_GPIO_P1_16
#define GPIO_5 RPI_V2_GPIO_P1_18

int main(int argc, char **argv)
{

    if (!bcm2835_init())
        return 1;

    // Set GPIO to outputs
    bcm2835_gpio_fsel(GPIO_0, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_5, BCM2835_GPIO_FSEL_OUTP);

}
