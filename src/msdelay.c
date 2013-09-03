#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

void forward();

int main(int argc, char *argv[])
{
int i;

if (!bcm2835_init())
        return 1;

        printf( "parameter %s", argv[1] );

	i = atoi (argv[1]);

        delay(i);
}

	
	
