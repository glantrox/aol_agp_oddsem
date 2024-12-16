#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 5000
#define MAX_COLUMNS 10
#define MAX_STRING_LENGTH 100

// Structure to store data
typedef struct {
    char data[MAX_COLUMNS][MAX_STRING_LENGTH];
} Row;

Row rows[MAX_ROWS];
int rowCount = 0;
int columnCount = 0;

void readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char line[4000];
    rowCount = 0;
    while (fgets(line, sizeof(line), file)) {
        if (rowCount >= MAX_ROWS) {
            printf("Error: Maximum row limit reached.\n");
            break;
        }

        char *token = strtok(line, ",\n");
        int colIndex = 0;
        while (token) {
            if (colIndex >= MAX_COLUMNS) {
                printf("Error: Maximum column limit reached on row %d.\n", rowCount + 1);
                break;
            }
            strncpy(rows[rowCount].data[colIndex++], token, MAX_STRING_LENGTH - 1);
            rows[rowCount].data[colIndex - 1][MAX_STRING_LENGTH - 1] = '\0';
            token = strtok(NULL, ",\n");
        }
        if (columnCount == 0) {
            columnCount = colIndex;
        }
        rowCount++;
    }

    fclose(file);
}

void displayData(int n) {
    printf("\nDisplaying %d rows:\n", n);
    for (int i = 0; i < n && i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            printf("%-20s", rows[i].data[j]);
        }
        printf("\n");
    }
}

void selectRow(int columnIndex, const char *query) {
    if (columnIndex < 0 || columnIndex >= columnCount) {
        printf("Error: Column index out of range.\n");
        return;
    }

    printf("\nSearching for rows where column %d matches '%s':\n", columnIndex, query);
    int found = 0;
    for (int i = 0; i < rowCount; i++) {
        if (strcmp(rows[i].data[columnIndex], query) == 0) {
            for (int j = 0; j < columnCount; j++) {
                printf("%-20s", rows[i].data[j]);
            }
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Not Found\n");
    }
}

int compareAscending(const void *a, const void *b) {
    Row *rowA = (Row *)a;
    Row *rowB = (Row *)b;
    return strcmp(rowA->data[0], rowB->data[0]);
}

int compareDescending(const void *a, const void *b) {
    Row *rowA = (Row *)a;
    Row *rowB = (Row *)b;
    return strcmp(rowB->data[0], rowA->data[0]);
}

void sortBy(int columnIndex, const char *order) {
    if (columnIndex < 0 || columnIndex >= columnCount) {
        printf("Error: Column index out of range.\n");
        return;
    }

    if (strcmp(order, "asc") == 0) {
        qsort(rows, rowCount, sizeof(Row), compareAscending);
    } else if (strcmp(order, "desc") == 0) {
        qsort(rows, rowCount, sizeof(Row), compareDescending);
    } else {
        printf("Invalid order specified. Use 'asc' or 'desc'.\n");
        return;
    }

    printf("\nData sorted by column %d in %s order:\n", columnIndex, order);
    displayData(10); // Display top 10 rows
}

void exportData(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot write to file %s\n", filename);
        return;
    }

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            fprintf(file, "%s", rows[i].data[j]);
            if (j < columnCount - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Data successfully exported to %s\n", filename);
}

int main() {
    readCSV("file.csv");

    int choice;
    do {
        printf("\nWhat do you want to do?\n");
        printf("1. Display data\n");
        printf("2. Search data\n");
        printf("3. Sort data\n");
        printf("4. Export data\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int n;
                printf("Enter number of rows to display: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("Error: Number of rows must be positive.\n");
                } else {
                    displayData(n);
                }
                break;
            }
            case 2: {
                int columnIndex;
                char query[MAX_STRING_LENGTH];
                printf("Enter column index to search: ");
                scanf("%d", &columnIndex);
                printf("Enter query value: ");
                scanf("%s", query);
                selectRow(columnIndex, query);
                break;
            }
            case 3: {
                int columnIndex;
                char order[10];
                printf("Enter column index to sort by: ");
                scanf("%d", &columnIndex);
                printf("Enter order (asc/desc): ");
                scanf("%s", order);
                sortBy(columnIndex, order);
                break;
            }
            case 4: {
                char filename[MAX_STRING_LENGTH];
                printf("Enter filename to export data: ");
                scanf("%s", filename);
                exportData(filename);
                break;
            }
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}