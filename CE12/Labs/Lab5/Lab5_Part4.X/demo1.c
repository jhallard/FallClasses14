/*
 * File:   demo.c
 * Author: mrg
 *
 * Created on October 31, 2014, 9:29 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <p32xxxx.h>

int Fibonacci(int n)
{
if ( n == 0 )
return 0;
else if ( n == 1 )
return 1;
else
return ( Fibonacci(n-1) + Fibonacci(n-2) );
}

int main(void)
{


    int x = 0;
    return x;


}

