// 2.	Case study 2 (LO 3 – L.Obj 2.2 – SO 2, 70%) :
// Download the file from link here: https://1drv.ms/u/s!AhuAx03LAKWtnOM9O1wlXSAR84Z67g?e=lVmH5x
// The file itself is a .csv file containing multiple rows and columns of data. Your task is to build several 
// functions as utility for the data itself, therefore you should implement function to read the .csv file into your program first. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 8
#define MAX_CHAR 1000
#define FILE_NAME "file.csv"

int isSelect = 1;


typedef struct apartement {
    char firstLocation[MAX_CHAR];
    char secondLocation[MAX_CHAR];
    double price;
    int roomQuantity;
    int bathroomQuantity;
    int carParksQuantity;
    char type[MAX_CHAR];
    char furnish[MAX_CHAR];    
} Apartement;

int enterToContinue() {   
    getchar() ;
    printf("Press enter to continue....\n");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { enter = getchar(); isSelect = 1; }
    return 0;
}

int displayMenu() {
    int T;
    char listOfMenus[5][50] = {
        "Display Data",
        "Search Data",
        "Sort Data",
        "Export Data",
        "Exit",
    };
    int sizeOfMenus =  sizeof(listOfMenus) / sizeof(listOfMenus[0]);

    printf("What do you want to do?\n");
    for (int i = 0; i < sizeOfMenus; i++)
    {
        printf("%d. %s\n", i + 1, listOfMenus[i]);
    }
    printf("Your choice: ");
    scanf("%d", &T);
    printf(T > 5 || T < 1 ? "Wrong Input\n" : "\n");
    
    return T;
}

int readData(Apartement listOfParkings[MAX_LINE_LENGTH], char fileName[100]) {
    FILE *file = fopen(fileName, "r");  // Open the CSV file in read mode
    char line[MAX_LINE_LENGTH];
    char *token;

    int countParameter = 800;
    int readCount = 0;

    if (file == NULL) return 400;
    
    // Read and print the header row    
    if (fgets(line, sizeof(line), file) != NULL) {                         
        do {
            token = strtok(line, ";");  // Split the line by commas
            int column = 0;
            
            
                while (token != NULL && readCount >= 1) {
                 char *endptr;
                    switch (column)
                    {
                        case 0: strcpy(listOfParkings[readCount].firstLocation, token);
                        case 1: strcpy(listOfParkings[readCount].secondLocation, token);
                        case 2: listOfParkings[readCount].price = strtod(token, &endptr);
                        case 3: listOfParkings[readCount].roomQuantity = atoi(token);
                        case 4: listOfParkings[readCount].bathroomQuantity = atoi(token);
                        case 5: listOfParkings[readCount].carParksQuantity = atoi(token);
                        case 6: strcpy(listOfParkings[readCount].type, token);
                        case 7: strcpy(listOfParkings[readCount].furnish, token);                            
                    }
                token = strtok(NULL, ";");
                column++;                
                }                                                
            readCount++;            
        } while (fgets(line, sizeof(line), file) != NULL && readCount < countParameter);  // Continue reading lines until the end of file        
    } else {
        return 400;
    }

    fclose(file);  // Close the file
    return 200;
}

int displayData(Apartement listOfApartements[MAX_LINE_LENGTH]) {    
    isSelect = 0;
    
    int T;
    // Input Number of Rows
    printf("Number of Rows: ");
    scanf("%d", &T);
    

    printf("----------------------------------------------------------------------------------------------------------\n");
            printf("%-5s %-20s %-20s %-10s %-6s %-10s %-10s %-10s %-8s\n", 
                "No",
               "Location 1", 
               "Location 2", 
               "Price", 
               "Rooms", 
               "Bathrooms", 
               "CarParks", 
               "Type", 
               "Furnish"
            );
            printf("----------------------------------------------------------------------------------------------------------\n");
    for (int i = 1; i < T + 1; i++)
    {
        printf("%-5d %-20s %-20s %-10.0f %-6d %-10d %-10d %-10s %-8s\n", 
        i,
        listOfApartements[i].firstLocation,
        listOfApartements[i].secondLocation,
        listOfApartements[i].price,
        listOfApartements[i].roomQuantity,
        listOfApartements[i].bathroomQuantity,
        listOfApartements[i].carParksQuantity,
        listOfApartements[i].type,
        listOfApartements[i].furnish
        );
    }    

   
    return enterToContinue();
}




int main() {    
    Apartement listOfApartements[MAX_LINE_LENGTH];

    // Reads File
    int readingStatus = readData(listOfApartements, FILE_NAME);
    if(readingStatus == 400) {
        printf("Could not open file\n");
        return 1;
    }

    // Display Menu
    
    while (isSelect == 1)
    {
        int menuInput = displayMenu();
        switch (menuInput)
        {
        case 1: displayData(listOfApartements);
        case 2:
        case 3:
        case 4:
        case 5:
        }
    }
        
    return 0;
}



