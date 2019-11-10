//
// This program sets up the structure for the next half of the project where we use functions that manipulate location data as well as store them with linked lists.
// Author: Ian Lulu
// Class: CS107, Spring 2019
// Date: modified on 04/22/19
//
// DEVELOP HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

const double RADIUS_EARTH = 6368.0; //in km

typedef struct Location_struct {
    double longitude;
    double latitude;
    double elevation;
    struct Location_struct* next; //pointer to the next Location
} Location;

//Location Constructor
void LocCreate(Location* thisLoc, double thisLong, double thisLat, double thisElev, Location* nextLoc) {
    thisLoc->longitude = thisLong;
    thisLoc->latitude = thisLat;
    thisLoc->elevation = thisElev;
    thisLoc->next = nextLoc;
}

void LocAdd(Location* headLoc, double newLong, double newLat, double newElev){ // traverses the linked list until it reaches null and adds a new location and that new location points to null
   Location* newLoc = (Location*)malloc(sizeof(Location));
   LocCreate(newLoc, newLong, newLat, newElev, NULL);
   Location* currLoc = headLoc;
   
   while (currLoc->next != NULL) {
      currLoc = currLoc->next;
   }
   currLoc->next = newLoc;
   //DEVELOP FUNCTIONALITY HERE
}

int countLocs(Location* headLoc){ // counts the number of locations in the linked list
   int count = 1; // since there is already a head location, count starts at 1
   while (headLoc->next != NULL) {
      headLoc = headLoc->next;
      count++;
   }
   return count;
   //DEVELOP FUNCTIONALITY HERE
}

double findMaxElev(Location* headLoc){ // traverses the list and finds the maxiumum elevation among the location data
   double maxElev = headLoc->elevation;
   while (headLoc->next != NULL) {
      headLoc = headLoc->next;
      if (headLoc->elevation > maxElev) {
         maxElev = headLoc->elevation;
      }
   }
   return maxElev;
   //DEVELOP FUNCTIONALITY HERE
}

double LocsToDist(double lat1, double long1, double lat2, double long2){ // converts coordinates of two lactions into distance between them; parameters in degrees
   double radLatA = (lat1 * M_PI) / 180; // converts to radians
   double radLongA = (long1 * M_PI) / 180;
   double radLatB = (lat2 * M_PI) / 180;
   double radLongB = (long2 * M_PI) / 180;
   double dist; // in kilometers
   return dist = RADIUS_EARTH * acos(cos(radLatA) * cos(radLatB) * cos(radLongB - radLongA) + sin(radLatA) * sin(radLatB));
   //DEVELOP FUNCTIONALITY HERE
}

//WRITE THE FUNCTION
void convertTime(int seconds, int* outHrs, int* outMins, int* outSecs) { // converts inputted seconds into hours, mins, and seconds format
   *outHrs = seconds / 3600; // uses pointers to return more than 1 value
   *outMins = (seconds / 60) % 60;
   *outSecs = seconds % 60;
}

int main() {
   //DEVELOP YOUR OWN TEST CASES HERE
   //DO NOT PASS TEST CASE #1!!! we will use the failed test case to see your output...
   
   /*int seconds = 20565;
   int H = 0, M = 0, S = 0;
   convertTime(seconds, &H, &M, &S);
   printf("%d, %d, %d\n", H, M, S);
   
   Location* headLoc = NULL;
   headLoc = (Location*)malloc(sizeof(Location));
   LocCreate(headLoc, 41.8781, 87.6298, 594, NULL);
   LocAdd(headLoc, 43.0389, 87.9065, 617);
   int count = 0; 
   count = countLocs(headLoc);
   printf("%d\n", count);
   
   double test = LocsToDist(headLoc->longitude, headLoc->latitude, 43.0389, 87.9065);
   printf("%lf\n", test);
   
   double elevTest = findMaxElev(headLoc);
   printf("%lf\n", elevTest);*/
   
   Location* headLoc = NULL;
   //Location* nextLoc = headLoc->next;
   int seconds1, seconds2, outHrs, outMins, outSecs, locCount;
   double distTest, elevTest;
   
   // test cases based on project prompt
   seconds1 = 20565;
   convertTime(seconds1, &outHrs, &outMins, &outSecs);
   printf("%d seconds is %d hours, %d minutes, and %d seconds\n", seconds1, outHrs, outMins, outSecs);
   
   headLoc = (Location*)malloc(sizeof(Location));
   LocCreate(headLoc, 41.8781, 87.6298, 594, NULL); // Chicago location
   LocAdd(headLoc, 43.0389, 87.9065, 617); // Milwaukee location
   locCount = countLocs(headLoc);
   printf("Number of locations stored in linked list: %d\n", locCount);
   
   //distTest = LocsToDist(headLoc->longitude, headLoc->latitude, nextLoc->longitude, nextLoc->latitude);
   distTest = LocsToDist(headLoc->longitude, headLoc->latitude, 43.0389, 87.9065);
   printf("Distance between Chicago and Milwaukee is %.1lf\n", distTest);
   elevTest = findMaxElev(headLoc);
   printf("Max elevation between Chicago and Milwaukee is %.1lf\n\n", elevTest);
   
   // my own test cases
   seconds2 = 10000;
   convertTime(seconds2, &outHrs, &outMins, &outSecs);
   printf("%d seconds is %d hours, %d minutes, and %d seconds\n", seconds2, outHrs, outMins, outSecs);
   
   headLoc = (Location*)malloc(sizeof(Location)); // just testing
   LocAdd(headLoc, 49.2827, 123.1207, 501); // Vancouver location
   LocAdd(headLoc, 32.5149, 117.0382, 65); // Tijuana location
   locCount = countLocs(headLoc);
   printf("Number of locations stored in linked list: %d\n", locCount);
   
   distTest = LocsToDist(49.2827, 123.1207, 32.5149, 117.0382);
   printf("Distance between Vancouver, Canada and Tijuana, Mexico is %.1lf\n", distTest);
   elevTest = findMaxElev(headLoc);
   printf("Max elevation between Vancouver and Tijuana is %.1lf\n", elevTest);
   
   // 2042
   
    printf("\n\n");
    return 0;
}
