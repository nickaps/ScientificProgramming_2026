
//      To convert from Celcius to Faranheit, we first multiply by 9
//      then we divide by 5. Afterwards we add 32 to the value.
//      This is the inverse of Faranheit to Celcius.
//
//      Created by Nick Chapman, 9-11-2026

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        
        //      First checking if there are only two arguments,
        //      the .exe name and the provided argument.
        //
        if (argc != 2) {
                printf("invalid. must provide degrees celcius");
                return 1;
        }

        //      Set degrees Celcius to first argument
        //
        double deg_c = (double)atoi(argv[1]);

        //      Set degrees Faranheit using conversion
        //
        double deg_f = ((deg_c * 9.0) / 5.0) + 32;

        //      Print conversion to the screen
        //
        printf("%.2lf deg Celcius = %.2lf deg Faranheit\n", deg_c, deg_f);

        //      return 0 to indicate all is well
        //
        return 0;
}
