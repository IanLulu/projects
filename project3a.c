//
// This program creates an elevation map while allowing the user to enter an x and y location to get the elevation at that point.
// If the location entered is at a peak, it specifies which hill the user is on.
// All of these functionalities are achieved through the use of structures, functions, 2D arrays, loops, etc.
// Author: Ian Lulu
// Class: CS107, Spring 2019
// Date: 03/24/19
//

#include <stdio.h>
#include <string.h> // added this to use strcpy function
#include <math.h> // added to use math functions

typedef struct Hill_struct { // easier to group together data related to each other with a struct
   char name[20];
   int loc[2];
   double height;
   double slope;
} Hill;

Hill setHill(char name[], int xloc, int yloc, double height, double slope) { // struct type function that creates a new hill with parameters that correspond to each data type in the struct
   Hill newHill;
   
   strcpy(newHill.name, name);
   newHill.loc[0] = xloc;
   newHill.loc[1] = yloc;
   newHill.height = height;
   newHill.slope = slope;
   
   return newHill;
}

int main() {
   Hill innovHills[5]; // stores each of the 5 hills on Innovation Island
   double innovElev[15][19]; // stores the sum of all the elevations of the island's hills
   int i, j, k, xloc, yloc;
   
   innovHills[0] = setHill("Ada's Apex", 12, 9, 20.0, 0.25); // setting up the 5 hills
   innovHills[1] = setHill("Turing's Top", 4, 3, 20.0, 0.33);
   innovHills[2] = setHill("Babbage's Bluff", 6, 13, 15.0, 0.33);
   innovHills[3] = setHill("Hopper's Hill", 14, 2, 15.0, 0.5);
   innovHills[4] = setHill("Katherine's Cliff", 1, 9, 10.0, 0.5);
   
   for (i = 0; i < 15; i++) { // initializing each value of innovElev to 0 so that there are no "junk" data used
      for (j = 0; j < 19; j++) {
         innovElev[i][j] = 0.0;
      }
   }
   
   for (i = 1; i < 14; i++) { // both i and j loops start at 1 and end at 13 and 17 respectively since the edges of the map are supposed to represent the ocean
      for (j = 1; j < 18; j++) {
         for (k = 0; k < 5; k++) { // triple loop in order to access the data stored in the 5 hills array
            innovElev[i][j] += innovHills[k].height * exp(-pow(innovHills[k].slope, 2) * (pow((j - innovHills[k].loc[0]), 2) + pow(((14-i) - innovHills[k].loc[1]), 2))); // elevation formula
         } // my map is flipped vertically thats why i added 14 - i in order to pass the test cases. not sure if im wrong but i just copied the elev formula
      }
   }
   
   printf("Elevations for Innovation Island: \n");
   for (i = 0; i < 15; i++) {
      for (j = 0; j < 19; j++) {
         printf("%4.1lf ", innovElev[i][j]); // prints out the elevation map with formatted numbers in order to look cleaner
      }
      printf("\n");
   }
   printf("\n");
   
   printf("Enter your x-location (1-17): \n"); // asks user for coordinates to give the user back an elevation value at that point
   scanf("%d", &xloc);
   printf("Enter your y-location (1-13): \n\n");
   scanf("%d", &yloc);
   
   printf("The elevation for the point (%d,%d) is %.4lf\n", xloc, yloc, innovElev[14-yloc][xloc]); // once again flipped the y-value. im confused i feel like i did something wrong
   if (xloc == 12 && yloc == 9) { // determines whether the user is at a peak or not (5 hills)
      printf("You are at the peak of Ada's Apex!");
   }
   else if (xloc == 4 && yloc == 3) {
      printf("You are at the peak of Turing's Top!");
   }
   else if (xloc == 6 && yloc == 13) {
      printf("You are at the peak of Babbage's Bluff!");
   }
   else if (xloc == 14 && yloc == 2) {
      printf("You are at the peak of Hopper's Hill!");
   }
   else if (xloc == 1 && yloc == 9) {
      printf("You are at the peak of Katherine's Cliff!");
   }
   else { // otherwise:
      printf("You are not at the peak of a hill.");
   }

   /* Type your code here. */

   // spring break woo
   return 0;
}
