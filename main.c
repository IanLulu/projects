//
// This program checks if a seat is open or taken in a classroom with 11 rows of seats, each with 16 seats.
// Class: CS107, Spring 2019
// Author: Ian Lulu
//

#include <stdio.h>

int main() {
   char rowLetter;
   int seatNum;
   int rowNum;
   
   printf("Enter the seat row letter: ");
   scanf(" %c", &rowLetter);
   if ( (rowLetter >= 'A') && (rowLetter <= 'K') ) { // letters A-K are valid
      printf("%c\n", rowLetter);
      rowNum = rowLetter;
      printf("Enter the seat number: ");
      scanf("%d", &seatNum);
      if ( (seatNum >= 1) && (seatNum <= 16) ) { // number 1-16 are valid
         printf("%d\n", seatNum);
         if ( ((rowNum % 3) == 2) ) { // checks the row number
            if ( ((seatNum % 2) == 0) ) {
               if (seatNum < 10) { // adds 0 to the seat combination if seat number is less than 10 to pass test cases
                  printf("Seat %c0%d is taken!", rowLetter, seatNum);
               }
               else { // if not less than 10, then no need to add 0
                  printf("Seat %c%d is taken!", rowLetter, seatNum);
               }
            }
            else {
               if (seatNum < 10) { // same thing as above
                  printf("Seat %c0%d is open!", rowLetter, seatNum);
               }
               else {
                  printf("Seat %c%d is open!", rowLetter, seatNum);
               }
            }
         }
         else if ( ((rowNum % 3) == 0) ) { // rows after the first one with the same pattern are checked
            if ( ((seatNum % 3) == 0) ) {
                if (seatNum < 10) {
                    printf("Seat %c0%d is open!", rowLetter, seatNum);
                }
                else {
                    printf("Seat %c%d is open!", rowLetter, seatNum);
                }
            }
            else {
                if (seatNum < 10) {
                    printf("Seat %c0%d is taken!", rowLetter, seatNum);
                }
                else {
                    printf("Seat %c%d is taken!", rowLetter, seatNum);
                }
            }
         }
         else if ( ((rowNum % 3) == 1) ) { // rows after the first and second with the same pattern are checked
             if ( (seatNum == 2) || (seatNum == 3) || (seatNum == 6) || (seatNum == 7) ) { // for seat numbers less than 10
                 printf("Seat %c0%d is taken!", rowLetter, seatNum);
             }
             else if ( (seatNum == 10) || (seatNum == 11) || (seatNum == 14) || (seatNum == 15) ) {
                 printf("Seat %c%d is taken!", rowLetter, seatNum);
             }
             else if (seatNum < 10) {
                 printf("Seat %c0%d is open!", rowLetter, seatNum);
             }
             else {
                 printf("Seat %c%d is open!", rowLetter, seatNum);
             }
         }
      }
      else { // otherwise, not a valid seat number
         printf("Not a valid seat number!");
      }
   }
   else { // otherwise, not a valid row
      printf("%c\n", rowLetter);
      printf("Not a valid row!");
   }
   
   return 0;
}