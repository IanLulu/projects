//
// This program reads in file data from a GPS attached to participants of Le Tour De France and outputs an analysis of that data with the use of functions, pointers, linked list, etc.
// Author: Ian Lulu
// Class: CS107, Spring 2019
// Date: modified on 05/03/19
//

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
}

int countLocs(Location* headLoc){ // counts the number of locations in the linked list
   int count = 1; // since there is already a head location, count starts at 1
   while (headLoc->next != NULL) {
      headLoc = headLoc->next;
      count++;
   }
   return count;
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
}

double LocsToDist(double lat1, double long1, double lat2, double long2){ // converts coordinates of two locations into distance between them; parameters in degrees
   double radLatA = (lat1 * M_PI) / 180; // converts to radians
   double radLongA = (long1 * M_PI) / 180;
   double radLatB = (lat2 * M_PI) / 180;
   double radLongB = (long2 * M_PI) / 180;
   double dist; // in kilometers
   return dist = RADIUS_EARTH * acos(cos(radLatA) * cos(radLatB) * cos(radLongB - radLongA) + sin(radLatA) * sin(radLatB));
}

void convertTime(int seconds, int* outHrs, int* outMins, int* outSecs) { // converts inputted seconds into hours, mins, and seconds format
   *outHrs = seconds / 3600; // uses pointers to return more than 1 value
   *outMins = (seconds / 60) % 60;
   *outSecs = seconds % 60;
}

int main() {
   char fileName[50], rider1Name[20], riderLName[20], tourYear[20], tourStage[20], txtLong[20], txtLat[20], txtElev[20];
   int timeInterval, faultyData = 0, gpsDataPts = 0, gpsLinkData = 0, timeSec, outHrs, outMins, outSecs;
   double gpsLong, gpsLat, gpsElev, gpsMaxElev = 0, elevGain = 0, elevPrev = 0, longPrev = 0, latPrev = 0, distBiked, linkMaxElev;
   Location* HeadLoc = NULL;
   FILE* gpsFile = NULL;
   
   printf("Enter the filename: \n");
   scanf("%s", fileName);
   
   gpsFile = fopen(fileName, "r"); // opens file
   if (gpsFile == NULL) {
      printf("Could not open file.\n");
      return -1;
   } // reads in the extra "fluff" before the GPS data
   fscanf(gpsFile, "%s %s", rider1Name, riderLName);
   fscanf(gpsFile, "%s %s", tourYear, tourStage);
   fscanf(gpsFile, "%d", &timeInterval);
   fscanf(gpsFile, "%s %s %s", txtLong, txtLat, txtElev);
   //printf("%.1lf ", elevGain);
   //printf("%.1lf\n", elevPrev);
   while (!feof(gpsFile)) { // reads all of the data before end of file is reached
      fscanf(gpsFile, "%lf %lf %lf", &gpsLong, &gpsLat, &gpsElev);
      gpsDataPts++; // counts all data points
      //if (feof(gpsFile) == false) {
         if (gpsElev < 0) {
            faultyData++; // counts faulty data
         }
         else {
            if (gpsLinkData == 0) { // creates head node
               HeadLoc = (Location*)malloc(sizeof(Location));
               LocCreate(HeadLoc, gpsLong, gpsLat, gpsElev, NULL);
            }
            if (gpsElev > gpsMaxElev) { // gets maxElev
               gpsMaxElev = gpsElev;
            }
            if (gpsElev > elevPrev && elevPrev != 0) { // calculates elevation gain
               elevGain += (gpsElev - elevPrev);
               //printf("%.1lf ", (gpsElev - elevPrev));
            }
            if (longPrev != 0 && latPrev != 0) { // calculates distance biked
               distBiked += LocsToDist(latPrev, longPrev, gpsLat, gpsLong);
            }
            LocAdd(HeadLoc, gpsLong, gpsLat, gpsElev); // adds new location after every iteration of the loop to the linked list
            longPrev = gpsLong; // sets prev long, lat, and elev to compare to current gps data points in next iteration of the loop
            latPrev = gpsLat;
            elevPrev = gpsElev;
         }
         gpsLinkData++;
         //printf("%.1lf ", elevGain);
         //printf("%.1lf\n", elevPrev);
      }
   //}
//}
   // prints out the analysis of the data that was read in from the file
   printf("\nRider: %s %s\n", rider1Name, riderLName);
   printf("Race: %s %s\n", tourYear, tourStage);
   printf("Time Interval is %d seconds\n", timeInterval);
   
   timeSec = (gpsLinkData-1) * timeInterval;
   printf("\nTotal GPS Datapoints: %d\n", gpsDataPts);
   printf("Total Faulty GPS Datapoints: %d\n", faultyData);
   gpsLinkData = countLocs(HeadLoc);
   printf("Linked List Total GPS Datapoints: %d\n", gpsLinkData-1);
   printf("Total Time: %d s\n", timeSec);
   printf("Max Elevation: %.1lf m\n", gpsMaxElev);
   linkMaxElev = findMaxElev(HeadLoc);
   printf("Linked List Max Elevation: %.1lf m\n", linkMaxElev);
   printf("Elevation Gained: %.1lf m\n", elevGain);
   printf("Distance Biked: %.1lf km\n", distBiked);
   convertTime(timeSec, &outHrs, &outMins, &outSecs);
   printf("Formatted Total Time: %02d:%02d:%02d", outHrs, outMins, outSecs);
   //printf("Test: %.3lf %.3lf %.3lf", gpsLong, gpsLat, gpsElev);
   
   // 1533
   
   return 0;
}
