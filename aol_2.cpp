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
// Utils
void enterToContinue() {      
    getchar();
    printf("Press enter to back....");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { 
        enter = getchar(); 
        isSelect = 1;         
    }
    printf("\e[1;1H\e[2J");
}
void showColumns() {
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
// Usecases
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
int fetchData(Apartement listOfApartements[MAX_LINE_LENGTH]) {    
    isSelect = 0;
    int T;    
    printf("Number of Rows: ");
    scanf("%d", &T);
    showColumns();
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
    enterToContinue();
    return 1;
}
int selectData(Apartement listOfApartements[MAX_LINE_LENGTH]) {
    
    
}

// Main Module
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
        // a. Display (15%)
        // This function needs 1 variable: number of rows to be displayed. 
        // This function will display data with n rows. n must be a positive integer number. 
        // If n > total number of rows, display all data.
        case 1: fetchData(listOfApartements);
        // b.	SelectRow (20%)
        // This function needs 2 variables as input: column and query value. 
        // This function will display rows that have the exact value with the query. 
        // If data is not found, print Not Found. If data is found, print data details as depicted in example below. 
         // If multiple data exist, display all data that matched the query.
        case 2: selectData(listOfApartements);
        // c.	SortBy (20%)
        // This function needs 2 variables as input: column and ascending or descending. 
        // After data was sorted, display the first 10 data.
        case 3:
        // d.	Export (15%)
        // This function needs 1 variable as input: filename (string). 
        // This function will write the data into a .csv file or comma separated- 
        // -value (,) with user specified filename in the same directory as your program. 
        case 4:
        case 5: return 0;
        }
    }
        
    return 0;
}



