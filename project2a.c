//
// This program categorizes exoplanets compared to planets in our own solar system based on user input and presents the data with the use of lists and histograms through the use of arrays, loops, branching, etc.
// Author: Ian Lulu
// Class: CS107, Spring 2019
// Date: created on 02/28/19, updated on 03/04/19
//

#include <stdio.h>
#include <string.h>

int main() {
   const int PLANET_NAME_LENGTH = 20; //max length for string planetNames
   const int RADIUS_OF_JUPITER = 43441; //in miles
   const int numPlanets = 12; //number of items in arrays
   int userNumPlanets; //stores number of planets user wants to categorize
   int i; //for loops
   char planetNames[numPlanets][PLANET_NAME_LENGTH]; //contains numPLanets items and string length of PLANET_NAME_LENGTH
   double planetRadius[12] = {0.091135, 0.0475, 0.08465, 1.289, 1.19, 0.699, 0.371, 0.585, 0.144, 0.808, 0.903, 0.999}; //initialized given data in an array
   double planetRadiusInMi[12]; //converts planet radii into miles by multiplying them with the radius of Jupiter also in miles
   double starRadius[12] = {1, 1, 1, 1.24, 0.86, 1.6, 0.76, 1.52, 0.64, 0.79, 1, 0.59};
   double planetDistanceToStar[12] = {215.1, 327.8, 154.87, 7.7, 10.51, 5.792, 346, 43.1, 144, 45.1, 176.7, 12.63}; 
   double planetDistToStarInAu[12]; //converts distance to star ratios into Au and stores them in this array
   strcpy(planetNames[0], "Earth"); //used strcpy because initializing array strings is problematic
   strcpy(planetNames[1], "Mars");
   strcpy(planetNames[2], "Venus");
   strcpy(planetNames[3], "HAT-P-16");
   strcpy(planetNames[4], "K2-29");
   strcpy(planetNames[5], "KELT-4-A");
   strcpy(planetNames[6], "Kepler-421");
   strcpy(planetNames[7], "KOI-94");
   strcpy(planetNames[8], "Kepler-62");
   strcpy(planetNames[9], "Kepler-46");
   strcpy(planetNames[10], "PH2");
   strcpy(planetNames[11], "WASP-82");
   
   printf("Enter the number of planets to categorize (max 12): \n");
   scanf("%d", &userNumPlanets);
   
   printf("\nPlanets: \n"); //lists the planets to categorize
   for (i = 0; i < userNumPlanets; i++) {
      printf("%s ", planetNames[i]);
   }
   printf("\n");
   
   printf("\nPlanet radii (in miles): \n"); //lists radii of corresponding planets
   for (i = 0; i < userNumPlanets; i++) {
      planetRadiusInMi[i] = planetRadius[i] * RADIUS_OF_JUPITER;
      printf("%.0lf", planetRadiusInMi[i]);
      if (i < userNumPlanets - 1) {
         printf(", ");
      }
   }
   printf("\n");
   
   printf("\nPlanets by size: "); //creates a histogram that categorizes each planet based on its size relative to the Earth's and Jupiter's size of radii
   printf("\n<HalfEarth: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetRadiusInMi[i] < (planetRadiusInMi[0] / 2)) {
         printf("*");
      }
   }
   printf("\n    ~Earth: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetRadiusInMi[i] >= (planetRadiusInMi[0] / 2) && planetRadiusInMi[i] < (planetRadiusInMi[0] * 2)) {
         printf("*");
      }
   }
   printf("\n  <Jupiter: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetRadiusInMi[i] >= (planetRadiusInMi[0] * 2) && planetRadiusInMi[i] < RADIUS_OF_JUPITER) {
         printf("*");
      }
   }
   printf("\n  >Jupiter: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetRadiusInMi[i] >= RADIUS_OF_JUPITER) {
         printf("*");
      }
   }
   printf("\n");

   printf("\nPlanet distances to their stars (in AU): \n"); //lists ratio of corresponding planets
   for (i = 0; i < userNumPlanets; i++) {
      planetDistToStarInAu[i] = (planetDistanceToStar[i] * starRadius[i]) / 215; //const AU to be divided by; also converting the ratio to AU
      printf("%.3lf", planetDistToStarInAu[i]);
      if (i < userNumPlanets - 1) {
         printf(", ");
      }
   }
   printf("\n");
   
   printf("\nPlanets by distance to their stars: "); //creates a histogram that categorizes each planet based on its distance to its star
   printf("\n<HalfEarth: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetDistToStarInAu[i] < 0.5/*AU*/) {
         printf("*");
      }
   }
   printf("\n    ~Earth: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetDistToStarInAu[i] >= 0.5 && planetDistToStarInAu[i] < 2.0) {
         printf("*");
      }
   }
   printf("\n  <Jupiter: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetDistToStarInAu[i] >= 2.0 && planetDistToStarInAu[i] < 5.2) {
         printf("*");
      }
   }
   printf("\n  >Jupiter: ");
   for (i = 0; i < userNumPlanets; i++) {
      if (planetDistToStarInAu[i] >= 5.2) {
         printf("*");
      }
   }
   
   /* Type your code here. */
   
   // IX:XXIX ante meridiem
   return 0;
}
