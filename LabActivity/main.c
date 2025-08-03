/*
 * File: main.c
 * Description: Implements the M.A.S.H. game. Sets up the game database,
 *              displays it, prompts the user for their name, then randomly
 *              builds and displays their future.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DataNode.h"

// Enum for database indexes
enum
{
   HOME_LIST,
   FEMALE_SPOUSE_LIST,
   MALE_SPOUSE_LIST,
   OCCUPATION_LIST,
   TRANSPORTATION_LIST,
   HOMETOWN_LIST,
   NUM_CATEGORIES // Total number of lists
};

int main()
{
   // Seed the random number generator (do this only once!)
   srand(time(0));

   // Create the database array of DataNode pointers
   DataNode *database[NUM_CATEGORIES] = {NULL};

   // Define arrays for each category
   char *homes[] = {"mansion", "apartment", "shack", "house"};
   int numHomes = sizeof(homes) / sizeof(homes[0]);

   char *femaleSpouses[] = {"Robin", "Lily", "Nora", "Patrice", "Zoey", "Quinn"};
   int numFemaleSpouses = sizeof(femaleSpouses) / sizeof(femaleSpouses[0]);

   char *maleSpouses[] = {"Ted", "Marshall", "Barney", "Ranjit", "Carl", "Linus"};
   int numMaleSpouses = sizeof(maleSpouses) / sizeof(maleSpouses[0]);

   char *occupations[] = {"teacher", "architect", "lawyer", "newscaster", "undercover agent"};
   int numOccupations = sizeof(occupations) / sizeof(occupations[0]);

   char *transportations[] = {"walk", "ride the train", "ride a bus", "fly an airplane", "carpool"};
   int numTransportations = sizeof(transportations) / sizeof(transportations[0]);

   char *hometowns[] = {"Cleveland", "Queens", "The Bronx", "Brooklyn", "Manhattan", "Staten Island"};
   int numHometowns = sizeof(hometowns) / sizeof(hometowns[0]);

   // Build each list using BuildDataList and store in the database
   database[HOME_LIST] = BuildDataList(homes, numHomes);
   database[FEMALE_SPOUSE_LIST] = BuildDataList(femaleSpouses, numFemaleSpouses);
   database[MALE_SPOUSE_LIST] = BuildDataList(maleSpouses, numMaleSpouses);
   database[OCCUPATION_LIST] = BuildDataList(occupations, numOccupations);
   database[TRANSPORTATION_LIST] = BuildDataList(transportations, numTransportations);
   database[HOMETOWN_LIST] = BuildDataList(hometowns, numHometowns);

   // Display the complete Future Possibilities Database
   printf("--------------------- Future Possibilities Database ------------------------\n");
   printf("Home List: ");
   PrintDataList(database[HOME_LIST]);
   printf("Female Spouse List: ");
   PrintDataList(database[FEMALE_SPOUSE_LIST]);
   printf("Male Spouse List: ");
   PrintDataList(database[MALE_SPOUSE_LIST]);
   printf("Occupation List: ");
   PrintDataList(database[OCCUPATION_LIST]);
   printf("Transportation List: ");
   PrintDataList(database[TRANSPORTATION_LIST]);
   printf("Hometown List: ");
   PrintDataList(database[HOMETOWN_LIST]);
   printf("----------------------------------------------------------------------------\n\n");

   // Prompt the user for their name
   char name[50];
   printf("Please enter your name: ");
   scanf("%49s", name); // limit input to avoid buffer overflow

   // Randomly select one option from each list
   DataNode *homeNode = GetRandomDataNode(database[HOME_LIST]);
   DataNode *femaleSpouseNode = GetRandomDataNode(database[FEMALE_SPOUSE_LIST]);
   DataNode *maleSpouseNode = GetRandomDataNode(database[MALE_SPOUSE_LIST]);
   DataNode *occupationNode = GetRandomDataNode(database[OCCUPATION_LIST]);
   DataNode *transportationNode = GetRandomDataNode(database[TRANSPORTATION_LIST]);
   DataNode *hometownNode = GetRandomDataNode(database[HOMETOWN_LIST]);

   // Randomly choose between a male or female spouse
   char *spouse;
   if (rand() % 2 == 0)
   {
      spouse = maleSpouseNode ? maleSpouseNode->dataValue : "someone special";
   }
   else
   {
      spouse = femaleSpouseNode ? femaleSpouseNode->dataValue : "someone special";
   }

   // Display the user's future
   printf("\nWelcome %s, this is your future...\n", name);
   printf("You will marry %s and live in a %s.\n", spouse, homeNode ? homeNode->dataValue : "a cozy place");
   printf("After 7 years of marriage, you will finally get your dream job as a %s.\n",
          occupationNode ? occupationNode->dataValue : "mystery worker");
   printf("Your family will move to a %s where you will %s to work each day.\n",
          hometownNode ? hometownNode->dataValue : "an unknown town",
          transportationNode ? transportationNode->dataValue : "travel magically");

   // Free all dynamically allocated memory for each list
   for (int i = 0; i < NUM_CATEGORIES; i++)
   {
      DestroyDataList(database[i]);
   }

   return 0;
}
