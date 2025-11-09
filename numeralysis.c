#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h> 

// Initialising variables

int screenW, screenH; 
int screenArea;

void help()
{
    printf("Numeralysis is a CLI program to analyse numbers and data sets.\n");
    printf("\nCommands include:\n");
    printf("help ->\nshows this help menu.\n\n");
    printf("quit ->\nquits the program immediately.\n\n");
    printf("average [n1] [n2] [n3] ... ->\ncalculates the mean, mode, median, and range of the given data set (there is a limit of 255 numbers and they must be seperated with spaces).\n\n");
}

void average(char *args)
{
    double numbers[255];  // Max numbers
    int count = 0;

    // Split the string into numbers
    char *token = strtok(args, " ");
    while (token != NULL && count < 255)
    {
        numbers[count++] = atof(token);
        token = strtok(NULL, " ");
    }

    if (count == 0)
    {
        printf("No numbers provided. Usage: /average [n1] [n2] [n3] ...\n");
        return;
    }

    // MEAN
    double sum = 0;
    for (int i = 0; i < count; i++)
        sum += numbers[i];
    double mean = sum / count;

    // SORT 
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (numbers[j] > numbers[j + 1])
            {
                double temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }

    // MEDIAN
    double median;
    if (count % 2 == 0)
        median = (numbers[count / 2 - 1] + numbers[count / 2]) / 2.0;
    else
        median = numbers[count / 2];

    // RANGE
    double range = numbers[count - 1] - numbers[0];

    // MODE
    double mode = numbers[0];
    int modeCount = 1;
    int currentCount = 1;
    bool hasMode = false;  // Flag for seeing if there is a mode

    for (int i = 1; i < count; i++)
    {
        if (numbers[i] == numbers[i - 1])
        {
            currentCount++;
            if (currentCount > modeCount)
            {
                modeCount = currentCount;
                mode = numbers[i];
                hasMode = true; // Found a repeating number
            }
        }
        else
        {
            currentCount = 1;
        }
    }

    printf("\nResults:\n");
    printf("Mean:   %g\n", mean);
    printf("Median: %g\n", median);
    if (hasMode)
        printf("Mode:   %g\n", mode);
    else
        printf("Mode:   Amodal — no numbers appears more than any other number.\n");
    printf("Range:  %g\n", range);
}

int main()
{
    // Initialisation of viewport variables (not needed currently due to the fact that this functionality will be provided in a later release to display graphs and charts)

    //printf("What is the width of your viewport in pixels?: ");
    //scanf("%d", &screenW);
    //printf("What is the height of your viewport in pixels?: ");
    //scanf("%d", &screenH);
    
    //int screenArea = screenW * screenH;

    //printf("\n%d characters need to be printed per frame.\n", screenArea);

    //printf("\n\033[31mWarning!\033[0m Changing the size of the viewport may lead to graphical issues, as this program depends on sending the same amount of characters each frame. Please refrain from changing the size of your viewport.\n");

    //sleep(2);

    //getchar();

    printf("\nWelcome to \033[31mNumeralysis.\033[0m\n");
    printf("\nTIP: Use 'help' to see a list of commands and how to use the software.\n");

    char input[4096]; // buffer for full input line

    while (true)
    {
        printf("\n~ ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        // remove trailing newline
        input[strcspn(input, "\n")] = 0;

        // handle commands
        if (strncmp(input, "help", 4) == 0)
        {
            help();
        }
        else if (strncmp(input, "average", 7) == 0)
        {
            char *args = input + 7; // skip past "average"
            while (*args == ' ') args++; // skip spaces

            average(args);
        }
        else if (strncmp(input, "quit", 4) == 0)
        {
            printf("Exiting Numeralysis...\n");
            break;
        }
        else if (strlen(input) > 0)
        {
            printf("Unknown command: %s\n", input);
        }
    }

    return 0;
}
