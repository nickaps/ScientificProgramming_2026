
//      To convert from Faranheit to Celcius, you first
//      take the deg_f and subtract 32 and then multiply by
//      five before dividing by nine.
//
//      Created by Nick Chapman, 9-11-2026

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

        //      First check if there are two arguments. First is .exe name
        //      and second is provided argument (degrees in faranheit)
        //
        if (argc != 2) {
                printf("invalid. must provide degrees in faranheit.");
                return 1;
        }

        //      Set degrees Faranheit by casting int of ascii argument
        //
        double deg_f = (double)atoi(argv[1]);

        //      Set degrees Celcius by converting degrees Celcius using formula
        //
        double deg_c = ((deg_f - 32.0) * 5.0) / 9.0;
        
        //      Print degrees Celcius to console
        //
        printf("%.2lf deg Faranheit = %.2lf deg Celcius\n", deg_f, deg_c);

        //      return 0 to indicate all is well
        return 0;
}
