
//      This program will take a time and speed travelled and provide a total
//      distance travelled based on the two arguments. The program will first
//      check for arguments, and, if there are none, ask user for input.
//      Otherwise it will take the arguments and use them.
//
//      Created by Nick Chapman, 9-14-2026

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        
        //      Allocating space for distance, time, and speed
        //      on stack memory.
        //
        double distance = 0;
        double time = 0;
        double speed = 0;

        //      Check if the arguments are either not present, or
        //      do not match the requirements (exactly three).
        //
        if (argc != 3) {
                fputs("What is your average speed? ", stdout);
                scanf("%lf", &speed);
                fputs("What is the distance to travel? ", stdout);
                scanf("%lf", &distance);
        }
        //      If the arguments do match the requirements (exactly three),
        //      then we will parse the arguments into the speed and time
        //      variables.
        //
        else {
                speed = (double)atoi(argv[1]);
                distance = (double)atoi(argv[2]);
        }

        //      Total journey time = total distance / average speed
        //
        time = distance / speed;
         
        printf("Your journey should take you %.2lf time units\n", time);
        return 0;
}
