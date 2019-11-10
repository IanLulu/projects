//
// This program maps out a hike based on given input by the user (starting location, uphill, or downhill) with the use of structs, functions, loops, etc.
// Author: Ian Lulu
// Class: CS107, Spring 2019
// Date: created on 04/06/19, modified on 04/11/19
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

double max2(double num1, double num2) {
   if (num2 > num1) {
      return num2;
   }
   return num1;
}

double max4(double num1, double num2, double num3, double num4) {
   double max12 = max2(num1, num2);
   double max23 = max2(max12, num3);
   return max2(max23, num4);
}

double min2(double num1, double num2) {
   if (num2 < num1) {
      return num2;
   }
   return num1;
}

double min4(double num1, double num2, double num3, double num4) {
   double min12 = min2(num1, num2);
   double min23 = min2(min12, num3);
   return min2(min23, num4);
}

int main() {
   Hill innovHills[5]; // stores each of the 5 hills on Innovation Island
   double innovElev[15][19] = {0}; // array stores the sum of all the elevations of the island's hills; initializes all values of array to 0
   double maxVal = 0, minVal = 0, initialElev = 0;
   int i, j, k, xloc, yloc, hike, squares = 0;
   
   innovHills[0] = setHill("Ada's Apex", 12, 9, 20.0, 0.25); // setting up the 5 hills
   innovHills[1] = setHill("Turing's Top", 4, 3, 20.0, 0.33);
   innovHills[2] = setHill("Babbage's Bluff", 6, 13, 15.0, 0.33);
   innovHills[3] = setHill("Hopper's Hill", 14, 2, 15.0, 0.5);
   innovHills[4] = setHill("Katherine's Cliff", 1, 9, 10.0, 0.5);
   
   for (i = 1; i < 14; i++) { // both i and j loops start at 1 and end at 13 and 17 respectively since the edges of the map are supposed to represent the ocean
      for (j = 1; j < 18; j++) {
         for (k = 0; k < 5; k++) { // triple loop in order to access the data stored in the 5 hills array
            innovElev[i][j] += innovHills[k].height * exp(-pow(innovHills[k].slope, 2) * (pow((j - innovHills[k].loc[0]), 2) + pow(((14-i) - innovHills[k].loc[1]), 2))); // elevation formula
         } // my map is flipped vertically thats why i added 14 - i in order to pass the test cases. not sure if im wrong but i just copied the elev formula
      }
   }
   
   /*printf("Elevations for Innovation Island: \n");
   for (i = 0; i < 15; i++) {
      for (j = 0; j < 19; j++) {
         printf("%4.1lf ", innovElev[i][j]); // prints out the elevation map with formatted numbers in order to look cleaner
      }
      printf("\n");
   }
   printf("\n");*/
   
   printf("Enter your x-location (1-17): "); // asks user for coordinates to give the user back an elevation value at that point
   scanf("%d", &xloc);
   printf("Enter your y-location (1-13): ");
   scanf("%d", &yloc);
   
   printf("\nThe elevation for the point (%d,%d) is %.4lf\n", xloc, yloc, innovElev[14-yloc][xloc]); // once again flipped the y-value. im confused i feel like i did something wrong
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
   printf("\n");
   
   printf("\nDo you want to hike up or down? (1 = uphill, 2 = downhill): ");
   scanf("%d", &hike); // any other number will make the program stop and do nothing
   initialElev = innovElev[14-yloc][xloc]; // user inputted location is stored here to be used later for change in elevation
   if (hike == 1) {
      printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]); // prints current position first
      maxVal = max4(innovElev[14-yloc-1][xloc], innovElev[14-yloc+1][xloc], innovElev[14-yloc][xloc-1], innovElev[14-yloc][xloc+1]); // max4 is assigned to a variable so that the lines using this function arent super long
      //printf("%.4f\n", maxVal); printf("%.4f\n", innovElev[14-yloc-1][xloc]); just testing
      while (maxVal > innovElev[14-yloc][xloc]) { // keeps iterating until the peak is reached
         if (fabs(maxVal - innovElev[14-yloc-1][xloc]) < 0.00001) { // going up? (-1 is up because my whole elev map is flipped)
            yloc++; // if statements check to see which variable to increment, the x location or the y location
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]); // then prints new current location
         }
         else if (fabs(maxVal - innovElev[14-yloc+1][xloc]) < 0.00001) { // going down? etc.
            yloc--;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         else if (fabs(maxVal - innovElev[14-yloc][xloc-1]) < 0.00001) {
            xloc--;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         else if (fabs(maxVal - innovElev[14-yloc][xloc+1]) < 0.00001) {
            xloc++;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         squares++; // counts each square traveled or every iteration of the loop
         maxVal = max4(innovElev[14-yloc-1][xloc], innovElev[14-yloc+1][xloc], innovElev[14-yloc][xloc-1], innovElev[14-yloc][xloc+1]); // updates maxVal
      }
      printf("\n");
      
      printf("You hiked %d squares, with elevation change %.4f\n", squares, (innovElev[14-yloc][xloc] - initialElev));
      if (xloc == 12 && yloc == 9) { // checks which one of these hills were the peak of the hike
         printf("You hiked to the top of Ada's Apex!");
      }
      else if (xloc == 4 && yloc == 3) {
         printf("You hiked to the top of Turing's Top!");
      }
      else if (xloc == 6 && yloc == 13) {
         printf("You hiked to the top of Babbage's Bluff!");
      }
      else if (xloc == 14 && yloc == 2) {
         printf("You hiked to the top of Hopper's Hill!");
      }
      else if (xloc == 1 && yloc == 9) {
         printf("You hiked to the top of Katherine's Cliff!");
      }
      else { // might not be necessary but just in case
         printf("You are not at the peak of a hill.");
      }
   }
   else if (hike == 2) { // same thing as above but goes downhill instead
      printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
      minVal = min4(innovElev[14-yloc-1][xloc], innovElev[14-yloc+1][xloc], innovElev[14-yloc][xloc-1], innovElev[14-yloc][xloc+1]);
      while (minVal < innovElev[14-yloc][xloc]) {
         if (fabs(minVal - innovElev[14-yloc-1][xloc]) < 0.00001) { //going up? (-1 is up because my whole elev map is flipped)
            yloc++;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         else if (fabs(minVal - innovElev[14-yloc+1][xloc]) < 0.00001) { //going down? etc.
            yloc--;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         else if (fabs(minVal - innovElev[14-yloc][xloc-1]) < 0.00001) {
            xloc--;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         else if (fabs(minVal - innovElev[14-yloc][xloc+1]) < 0.00001) {
            xloc++;
            printf("(%d,%d)  elev: %.4f\n", xloc, yloc, innovElev[14-yloc][xloc]);
         }
         squares++;
         minVal = min4(innovElev[14-yloc-1][xloc], innovElev[14-yloc+1][xloc], innovElev[14-yloc][xloc-1], innovElev[14-yloc][xloc+1]);
      }
      printf("\n");
      
      printf("You hiked %d squares, with elevation change %.4f\n", squares, (innovElev[14-yloc][xloc] - initialElev));
      if (fabs(innovElev[14-yloc][xloc] - innovElev[0][0]) < 0.00001) {
         printf("You hiked to the ocean.");
      }
      else {
         printf("Your hike ended at a lake on the island.");
      }
   }

   // 1439
   return 0;
}
