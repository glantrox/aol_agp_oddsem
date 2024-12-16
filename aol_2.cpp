// 2.	Case study 2 (LO 3 – L.Obj 2.2 – SO 2, 70%) :
// Download the file from link here: https://1drv.ms/u/s!AhuAx03LAKWtnOM9O1wlXSAR84Z67g?e=lVmH5x
// The file itself is a .csv file containing multiple rows and columns of data. Your task is to build several 
// functions as utility for the data itself, therefore you should implement function to read the .csv file into your program first. 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LENGTH 5000
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

struct utils {
  int showSearch() {
    printf("Select column to search:\n");
    printf("1. Location\n");
    printf("2. City\n");
    printf("3. Price\n");
    printf("4. Rooms\n");
    printf("5. Bathrooms\n");
    printf("6. CarParks\n");
    printf("7. Type\n");
    printf("8. Furnish\n");
    printf("Enter column number: ");
  }
  int enterToContinue() {
    isSelect = 0;
    printf("Press enter to back....");
    char enter = 0;
    while (enter != '\r' && enter != '\n') {
      enter = getchar();
      isSelect = 1;
    }
    printf("\e[1;1H\e[2J");
    return enter;
  }
  void showColumns() {
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-20s %-20s %-10s %-6s %-10s %-10s %-10s %-8s\n",
      "No",
      "Location",
      "City",
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
    int sizeOfMenus = sizeof(listOfMenus) / sizeof(listOfMenus[0]);
    printf("What do you want to do?\n");
    for (int i = 0; i < sizeOfMenus; i++) {
      printf("%d. %s\n", i + 1, listOfMenus[i]);
    }
    printf("Your choice: ");
    scanf("%d", & T);
    printf("\e[1;1H\e[2J");
    printf(T > 5 || T < 1 ? "Wrong Input\n" : "\n");
    return T;
  }
}
Utils;

struct usecase {
  void exportApartmentsToCSV() {

    Apartement listOfApartements[50] = {
      {
        "Downtown",
        "Near Mall",
        250000.50,
        3,
        2,
        1,
        "Condo",
        "Furnished"
      },
      {
        "Uptown",
        "Near Park",
        320000.75,
        4,
        3,
        2,
        "Duplex",
        "Semi-Furnished"
      },
      {
        "Suburb",
        "Near School",
        150000.00,
        2,
        1,
        1,
        "Flat",
        "Unfurnished"
      },
      {
        "Beachside",
        "Ocean View",
        450000.00,
        5,
        4,
        3,
        "Villa",
        "Luxury"
      },
      {
        "City Center",
        "Near Office",
        270000.00,
        3,
        2,
        1,
        "Condo",
        "Furnished"
      },
      {
        "Countryside",
        "Near Forest",
        120000.00,
        2,
        1,
        1,
        "Cottage",
        "Unfurnished"
      },
      {
        "Midtown",
        "Near Market",
        200000.00,
        3,
        2,
        2,
        "Apartment",
        "Semi-Furnished"
      },
      {
        "Historic District",
        "Near Museum",
        350000.00,
        4,
        3,
        2,
        "Townhouse",
        "Furnished"
      },
      {
        "Industrial Area",
        "Near Factory",
        100000.00,
        1,
        1,
        0,
        "Studio",
        "Unfurnished"
      },
      {
        "Lakeside",
        "Scenic View",
        400000.00,
        4,
        3,
        2,
        "Villa",
        "Luxury"
      }
    };
    int apartmentCount = sizeof(listOfApartements) / sizeof(listOfApartements[0]);

    // Input Filename
    char fileName[50];
    printf("File name: ");
    scanf("%s", fileName);
    char fileExtension[50] = ".csv";

    strcat(fileName, fileExtension);

    // Open the file in write mode
    FILE * file = fopen(fileName, "w");

    // Check if the file was opened successfully
    if (file == NULL) {
      printf("Error opening file '%s' for writing!\n", fileName);
      return;
    }

    // Write the header row to the CSV file
    fprintf(file, "First Location,Second Location,Price,Room Quantity,Bathroom Quantity,Car Parks Quantity,Type,Furnish\n");

    // Write each apartment's data as a CSV row
    for (int i = 0; i < apartmentCount; i++) {
      fprintf(file, "\"%s\",\"%s\",%.2f,%d,%d,%d,\"%s\",\"%s\"\n",
        listOfApartements[i].firstLocation,
        listOfApartements[i].secondLocation,
        listOfApartements[i].price,
        listOfApartements[i].roomQuantity,
        listOfApartements[i].bathroomQuantity,
        listOfApartements[i].carParksQuantity,
        listOfApartements[i].type,
        listOfApartements[i].furnish);
    }

    // Close the file after writing
    fclose(file);

    // Print a message indicating the file was saved successfully
    printf("Data has been successfully exported to '%s'.\n", fileName);
  }
  int fetchData(Apartement listOfParkings[MAX_LINE_LENGTH], char fileName[100]) {
    FILE * file = fopen(fileName, "r"); // Open the CSV file in read mode
    char line[MAX_LINE_LENGTH];
    char * token;
    int readCount = 0;
    if (file == NULL) return 400;
    // Read and print the header row    
    if (fgets(line, sizeof(line), file) != NULL) {
      do {
        token = strtok(line, ","); // Split the line by commas
        int column = 0;
        while (token != NULL) {
          char * endptr;
          switch (column) {
          case 0:
            strcpy(listOfParkings[readCount].firstLocation, token);
            break;
          case 1:
            strcpy(listOfParkings[readCount].secondLocation, token);
            break;
          case 2:
            listOfParkings[readCount].price = strtod(token, & endptr);
            break;
          case 3:
            listOfParkings[readCount].roomQuantity = atoi(token);
            break;
          case 4:
            listOfParkings[readCount].bathroomQuantity = atoi(token);
            break;
          case 5:
            listOfParkings[readCount].carParksQuantity = atoi(token);
            break;
          case 6:
            strcpy(listOfParkings[readCount].type, token);
            break;
          case 7:
            strcpy(listOfParkings[readCount].furnish, token);
            break;
          }
          token = strtok(NULL, ",");
          column++;
        }
        readCount++;
        if (readCount >= MAX_LINE_LENGTH) {
          return 500; // Error: Exceeded maximum allowed data
        }
      } while (fgets(line, sizeof(line), file) != NULL); // Continue reading lines until the end of file        
    } else {
      return 400;
    }
    fclose(file); // Close the file
    return 200;
  }
  int readData(Apartement listOfApartements[MAX_LINE_LENGTH]) {
    int T;
    printf("Number of Rows: ");
    scanf("%d", & T);
    getchar();
    Utils.showColumns();
    for (int i = 1; i < T + 1; i++) {
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
    return 0;
  }
  int selectData(Apartement listOfApartements[MAX_LINE_LENGTH]) {
    int column;
    char queryValue[MAX_CHAR];
    Utils.showSearch();
    scanf("%d", & column);
    printf("Enter query value: ");
    getchar(); // Consume newline character
    fgets(queryValue, MAX_CHAR, stdin);
    queryValue[strcspn(queryValue, "\n")] = 0; // Remove newline character
    int found = 0;
    Utils.showColumns();
    int sizeOfApartements = MAX_LINE_LENGTH;
    for (int i = 0; i < sizeOfApartements; i++) {
      int match = 0;
      switch (column) {
      case 1:
        match = strcmp(listOfApartements[i].firstLocation, queryValue) == 0;
        break;
      case 2:
        match = strcmp(listOfApartements[i].secondLocation, queryValue) == 0;
        break;
      case 3:
        match = (fabs(listOfApartements[i].price - atof(queryValue)) < 0.0001);
        break; // Floating point comparison
      case 4:
        match = (listOfApartements[i].roomQuantity == atoi(queryValue));
        break;
      case 5:
        match = (listOfApartements[i].bathroomQuantity == atoi(queryValue));
        break;
      case 6:
        match = (listOfApartements[i].carParksQuantity == atoi(queryValue));
        break;
      case 7:
        match = strcmp(listOfApartements[i].type, queryValue) == 0;
        break;
      case 8:
        match = strcmp(listOfApartements[i].furnish, queryValue) == 0;
        break;
      default:
        printf("Invalid column number.\n");
        return -1;
      }
      if (match) {
        printf("%-5d %-20s %-20s %-10.0f %-6d %-10d %-10d %-10s %-8s\n",
          i + 1,
          listOfApartements[i].firstLocation,
          listOfApartements[i].secondLocation,
          listOfApartements[i].price,
          listOfApartements[i].roomQuantity,
          listOfApartements[i].bathroomQuantity,
          listOfApartements[i].carParksQuantity,
          listOfApartements[i].type,
          listOfApartements[i].furnish);
        found = 1;
      }
    }
    if (!found) {
      printf("No results found for Query \"%s\" \n", queryValue);
    }
    return found;
  }
} Usecase;

// Main Module
int main() {

  Apartement * listOfApartements = (Apartement * ) malloc(sizeof(Apartement) * MAX_LINE_LENGTH);
  // Reads File
  int response = Usecase.fetchData(listOfApartements, FILE_NAME);
  if (response == 400) {
    printf("Could not open file\n");
    return 1;
  }
  // Display Menu
  while (isSelect) {
    int menuInput = Utils.displayMenu();
    switch (menuInput) {
      // a. Display (15%)
      // This function needs 1 variable: number of rows to be displayed. 
      // This function will display data with n rows. n must be a positive integer number. 
      // If n > total number of rows, display all data.
    case 1:
      Usecase.readData(listOfApartements);
      Utils.enterToContinue();
      break;
      // b.	SelectRow (20%)
      // This function needs 2 variables as input: column and query value. 
      // This function will display rows that have the exact value with the query. 
      // If data is not found, print Not Found. If data is found, print data details as depicted in example below. 
      // If multiple data exist, display all data that matched the query.
    case 2:
      Usecase.selectData(listOfApartements);
      Utils.enterToContinue();
      break;
      // c.	SortBy (20%)
      // This function needs 2 variables as input: column and ascending or descending. 
      // After data was sorted, display the first 10 data.
    case 3:
      break;
      // d.	Export (15%)
      // This function needs 1 variable as input: filename (string). 
      // This function will write the data into a .csv file or comma separated- 
      // -value (,) with user specified filename in the same directory as your program. 
    case 4:
      Usecase.exportApartmentsToCSV();
      Utils.enterToContinue();
      break;
    case 5:
      return 0;
    }
  }
  return 0;
}