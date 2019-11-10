//
// This program creates seating charts with user-inputted data, and also outputs seating charts that shows taken and open seats.
// Class: CS107, Spring 2019
// Author: Ian Lulu
// Date: 02/16/19
//

#include <stdio.h>

int main() {
   int numRows;
   int numSeats;
   char i; // both i & j are for the for loops
   int j;
   char equis = 'X'; // for taken seats
   int x = 0; // "every-other seating chart" head count; confusing but it works for me
   int X = 0; // "more-complicated seating chart" head count
   
   printf("Enter number of rows: \n");
   scanf("%d", &numRows); // scans row of columns desired by user for seating chart
   if (numRows <= 0) { // if negative number or zero, seating chart cannot be created
      printf("Number of rows must be at least 1.\n");
   }
   else if (numRows > 26) { // to prevent cpu over exhaustion from looping too many times
      printf("Too many rows! Max. number of rows is 26.\n");
   }
   else { // if fulfills two conditions, then can proceed to enter number of seats per row
      printf("Enter number of seats: \n");
      scanf("%d", &numSeats);
      if (numSeats <= 0) { // same deal just with seats
         printf("Number of seats per rows must be at least 1.\n");
      }
      else if (numSeats > 30) { // 
         printf("Too many seats per rows! Max. number of seats per row is 30.\n");
      }
      else {
         printf("\nEmpty Classroom Seating Chart: \n");  // when the classroom is empty
         for (i = 'A' + (numRows - 1); i >= 'A'; i--) { // generates letter for each row
            for (j = 1; j <= numSeats; j++) { // generates number for each seat
               printf("%c%02d ", i, j);
            }
            printf("\n");
         }
         printf("\nEvery-Other Seating Chart: \n"); // the classroom during a test
         for (i = 'A' + (numRows - 1); i >= 'A'; i--) {
            for (j = 1; j <= numSeats; j++) {
               if ( (i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0) ) { // only print when conditions are fulfilled, meaning the seat is open
                  printf("%c%02d ", i, j);
               }
               else { // otherwise, it's taken
                  printf(" %-2c ", equis);
                  ++x;
               }
            }
            printf("\n");
         }
         printf("*%d students have seats in this arrangement*\n", x); // shows how many students are present in class
         printf("\nMore-Complicated Seating Chart: \n"); // the classroom during ???
         for (i = 'A' + (numRows - 1); i >= 'A'; i--) {
            for (j = 1; j <= numSeats; j++) {
               if ( (i % 3 == 2 && j % 2 == 1) || (i % 3 == 0 && j % 3 == 0) || (i % 3 == 1 && (j % 4 == 0 || j % 4 == 1)) ) { // much more complicated logic for a more random seating chart
                  printf("%c%02d ", i, j);
               }
               else {
                  printf(" %-2c ", equis);
                  ++X;
               }
            }
            printf("\n");
         }
         printf("*%d students have seats in this arrangement*", X);
      }
   }
   // I:XLVI post meridiem
   return 0;
}