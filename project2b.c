//
// This program checks if exoplanets are habitable or unhabitable through multiple checks with the use of user-defined functions, arrays, loops, branching, etc.
// Author: Ian Lulu
// Class: CS107, Spring 2019
// Date: edited on: 03/08/19
//  TODO: this header, formatting, proper variable names, 
//        comment functions and main code blocks, etc.
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

//Global variables: DO NOT REMOVE, DO NOT MODIFY, DO NOT ADD ANY MORE
double const RADIUS_JUPITER = 43441.0; //miles
double const RADIUS_EARTH = 3959.0; //miles

// calcDistToStar: calculates planet distance to its star
// [in] starRadius: radius of star in units of Solar radii
// [in] planetRatio: ratio of (planet distance to star)/(star radius)
// [out] returns double: planet distance to star in units of AU
double calcDistToStar(double starRadius, double planetRatio){
   return (planetRatio * starRadius) / 215;
   //TODO: write the code to obtain the required functionality for this function
}

// countDataInInterval: "bins" the input data by counting entries in the specified interval
// [in] lowerBound: lower value of interval
// [in] upperBound: upper value of interval
// [in] data[size]: array of doubles to be binned (counted)
// [in] size: array size of data[]
// [out] returns int: count of values in data[] that fall in the specified interval
int countDataInInterval(double lowerBound, double upperBound, double data[], int size){
   int i, count = 0;
   
   for (i = 0; i < size; i++) {
      if (data[i] >= lowerBound && data[i] <= upperBound) {
         count++;
      }
   }
   
   return count;
   //TODO: write the code to obtain the required functionality for this function
}


// isItHabitable: apply conditions for "Habitable Exoplanet" to check if the planet is "habitable"
// [in] radius: planet radius (in miles)
// [in] orbitPer: orbital period for planet (in days)
// [in] temperature: equilibrium temperature of the planet (in K)
// [in] distance: to the star (in AU)
// [out] returns bool: true only if planet passes all the "habitable" tests, otherwise false
bool isItHabitable(double radius, double orbitPer, double temperature, double distance){
   double lowerRad = 0.2 * RADIUS_EARTH, upperRad = 5.0 * RADIUS_EARTH; // in miles
   
   if (radius >= lowerRad && radius <= upperRad) {
      if (orbitPer >= 91 && orbitPer <= 801) {
         if (temperature >= 183 && temperature <= 294) {
            if (distance >= 0.4 && distance <= 2.35) {
               return true;
            }
         }
      }
   }
   
   return false;
   //TODO: write the code to obtain the required functionality for this function
}

//TODO: WRITE THE FUNCTION isItVeryUnhabitable(), 
//      which takes in identical input argruments 
//      (numebr, type, etc.) as isItHabitable()
//      (make sure to include a description similar
//      to those in the provided code template)

// isItVeryUnhabitable: apply conditions for "Unhabitable Exoplanet" to check if the planet is "Unhabitable"
// [in] radius: planet radius (in miles)
// [in] orbitPer: orbital period for planet (in days)
// [in] temperature: equilibrium temperature of the planet (in K)
// [in] distance: to the star (in AU)
// [out] returns bool: true only if planet fails all the "Habitable" tests, otherwise false
bool isItVeryUnhabitable(double radius, double orbitPer, double temperature, double distance){
   double lowerRad = 0.2 * RADIUS_EARTH, upperRad = 5.0 * RADIUS_EARTH; // in miles
   
   if (radius <= lowerRad || radius >= upperRad) {
      if (orbitPer <= 91 || orbitPer >= 801) {
         if (temperature <= 183 || temperature >= 294) {
            if (distance <= 0.4 || distance >= 2.35) {
               return true;
            }
         }
      }
   }
   
   return false;
   //TODO: write the code to obtain the required functionality for this function
}

// debugging tools:
void printNames(char array[][20], int size) { // checks if string data is appropriate
   for (int i = 0; i < size; i++) {
      printf("%s " , array[i]);
   }
}
void printData(double array[], int size) { // checks if double values are appropriate
   for (int i = 0; i < size; i++) {
      printf("%lf " , array[i]);
   }
}
void printIntData(int array[], int size) { // checks if int values are appropriate
   for (int i = 0; i < size; i++) {
      printf("%d " , array[i]);
   }
}

int main(){
// ~~~~~~~~~~~~~~ START OF PROVIDED TEMPLATE CODE ~~~~~~~~~~~~~~~~~~~`    
// DO NOT MODIFY THE PROVIDED TEMPLATE CODE
// instead, add your code in main() below the provided code.
// The following provided template code...
//   1) allows the user to enter an integer, np
//   2) reads in data from a file for np planets
//   3) stores the planet data in 7 arrays

    FILE *inFile = NULL; // File pointer
    const int n = 300;  //max. number of data
    const int m = 20;  //buffer size
    
    //Arrays to store planet info
    char planetNames[n][m];  //planet names
    int planetIDs[n]; //planet IDs (from NASA)
    double planetRadiiJ[n]; //planet radius (units: # of Jupiter radii)
    double planetOrbPeriod[n]; //planet orbital period (units: days)
    double starRadii[n]; //star radius (units: solar radii)
    double planetEqTemp[n]; //planet equilibrium temperature (units: K)
    double planetDistOverRadius[n]; //ratio (distance planet to star)/(star radius)
    // added a couple arrays and variables:
    double planetRadiiMi[n]; //planet radius (units: Jupiter radii converted to miles)
    double planetDistToStarAu[n]; //uses calcDistToStar to obtain values in AU
    double lowerRad = 0.2 * RADIUS_EARTH, upperRad = 5.0 * RADIUS_EARTH; // for use with countDataInInterval radius check
    int hCount, uCount; // to count h = habitable and u = unhabitable planets
    
    int np = 0;
    printf("How many planets would you like to read in: ");
    scanf("%d",&np);
    int counter = 0;
    
    inFile = fopen("planets2.txt","r");
    if (inFile == NULL) {
        printf("Could not open file.\n");
        return -1; // -1 indicates error
    }
    while (counter < np){
        fscanf(inFile,"%d",&planetIDs[counter]);
        fscanf(inFile,"%s",planetNames[counter]);
        fscanf(inFile,"%lf",&planetOrbPeriod[counter]);
        fscanf(inFile,"%lf",&planetRadiiJ[counter]);
        fscanf(inFile,"%lf",&starRadii[counter]);
        fscanf(inFile,"%lf",&planetEqTemp[counter]);
        fscanf(inFile,"%lf",&planetDistOverRadius[counter]);
        counter++;
    }
    fclose(inFile);
    
    printf("Planets: ");
    printNames(planetNames, np); // test functionality of debugging user-defined function
    printf("\n");
    
    // ~~~~~~~~~~~~~~ END OF PROVIDED TEMPLATE CODE ~~~~~~~~~~~~~~~~~~~`
    // **** Enter your code below this comment ****
    for (int i = 0; i < np; i++) { // converts planet radii in units of Jupiters to miles
      planetRadiiMi[i] = planetRadiiJ[i] * RADIUS_JUPITER; 
    }
    for (int i = 0; i < np; i++) { // calculates planet distance to its star in AU
      planetDistToStarAu[i] = calcDistToStar(starRadii[i], planetDistOverRadius[i]);
    }
    
    printf("\n");
    // checks to see which planets pass the constraints of habitability
    printf("Total number of planets passing the radius check: %d\n", countDataInInterval(lowerRad, upperRad, planetRadiiMi, np));
    printf("Total number of planets passing the orbital period check: %d\n", countDataInInterval(91, 801, planetOrbPeriod, np));
    printf("Total number of planets passing the equilibrium temperature check: %d\n", countDataInInterval(183, 294, planetEqTemp, np));
    printf("Total number of planets passing the distance to star check: %d\n", countDataInInterval(0.4, 2.35, planetDistToStarAu, np));
    
    printf("\n");
    printf("Potentially Habitable Planets: \n");
    for (int i = 0; i < np; i++) { // uses isItHabitable function in a loop in order to list habitable planets
       if (isItHabitable(planetRadiiMi[i], planetOrbPeriod[i], planetEqTemp[i], planetDistToStarAu[i]) == true) {
          printf("%s\n", planetNames[i]);
          hCount++;
       }
    }
    printf("Total number of Potentially Habitable Planets: %d\n", hCount);
    
    printf("\n");
    printf("Very Unhabitable Planets: \n");
    for (int i = 0; i < np; i++) { // uses isItVeryUnhabitable function in a loop in order to list unhabitable planets
       if (isItVeryUnhabitable(planetRadiiMi[i], planetOrbPeriod[i], planetEqTemp[i], planetDistToStarAu[i]) == true) {
          printf("%s\n", planetNames[i]);
          uCount++;
       }
    }
    printf("Total number of Very Unhabitable Planets: %d\n", uCount);
    
    // TODO: implement calculations and functions calls to acheive the required programming tasks
    // XI:XVIII ante meridiem
    return 0;
}
