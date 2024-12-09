#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "config.h"

// let us ignore the mess for now

typedef struct Stack {
    char **data;
    int top;
    int size;
} Stack;

// @formatter:off
char *parseText(const char *rawData);
char *extractInputData(const char *fileName);
void printCommands();
void startCommand();
void helpCommand();
void initializeStack(Stack *stack, int size);
void push(Stack *stack, const char *entry);
char *pop(Stack *stack);
int isEmpty(Stack *stack);
void displayStack(Stack *stack);
void saveStackToFile(Stack *stack, const char *filename);
void clearScreen();
char getch();
void captureInput();
char *getTimeInNanoSeconds();
char *combineTimeAndChar(const char *character, const char *time);
// @formatter:on


int main(void) {
    char command[1024];

    printf("\n%s\n %s\n\n %s %s %s\n%s\n", BREAK_TEXT, PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_DATE,
           PROGRAM_AUTHOR,
           BREAK_TEXT);

    char *formattedInputData = extractInputData(INPUT_FILE_NAME);

    while (1) {
        printCommands();

        if (fgets(command, sizeof(command), stdin) != NULL) {
            command[strcspn(command, "\n")] = 0;

            if (strcmp(command, "start") == 0) {
                captureInput();
            } else if (strcmp(command, "help") == 0) {
                helpCommand();
            } else if (strcmp(command, "text") == 0) {
                printf("%s\n", formattedInputData);
            } else if (strcmp(command, "exit") == 0) {
                printf("Exiting...\n");
                free(formattedInputData);
                return (0);
            } else {
                printf("Unknown command: %s\n", command);
            }
        } else {
            printf("Error reading input. Try again.\n");
        }
    }
}

/* - - - - - - - - - - - - - - - CAPTURE TEXT - - - - - - - - - - - - - - - */

void captureInput() {
    Stack history_stack, editable_stack;
    initializeStack(&history_stack, 10240);
    initializeStack(&editable_stack, 10240);

    int x_count = 0;

    printf("Start typing (Press 'x' 3 times to exit)\n");

    while (1) {
        char input = getch();
        if (input == '\0') continue;

        char *time_ns = getTimeInNanoSeconds();
        if (time_ns == NULL) continue;

        char *result = combineTimeAndChar(&input, time_ns);
        if (result == NULL) {
            free(time_ns);
            continue;
        }

        // enter
        if (input == '\r') {
            printf("\n");
        } else if (input == '\b' || input == 127) {
            // backspace
            if (editable_stack.top >= 0) {
                pop(&editable_stack);
            }
        } else if (input == 'x') {
            push(&history_stack, result);
            x_count++;
            if (x_count == 3) {
                break;
            }
        } else {
            x_count = 0;
            push(&history_stack, result);
            const char temp[2] = {input, '\0'};
            push(&editable_stack, temp);
        }

        free(time_ns);
        free(result);
        clearScreen();
        displayStack(&editable_stack);
    }

    saveStackToFile(&history_stack, OUTPUT_FILE_NAME);

    free(history_stack.data);
    free(editable_stack.data);
}

void clearScreen() {
    printf("\033[H\033[J");
}

char getch() {
    struct termios oldt, newt;
    char ch;

    // get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    // set new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // read a single character
    ch = (char) getchar();
    // restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

char *getTimeInNanoSeconds() {
    struct timespec ts;

    if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
        perror("clock_gettime");
        return NULL;
    }

    char *time_str = malloc(32);
    if (time_str == NULL) {
        perror("malloc");
        return NULL;
    }

    snprintf(time_str, 32, "%lld", (long long) ts.tv_sec * 1000000000LL + ts.tv_nsec);

    return time_str;
}

char *combineTimeAndChar(const char *character, const char *time) {
    size_t newLength = 2 + strlen(time) + 3;

    char *combinedArray = malloc(newLength);
    if (combinedArray == NULL) {
        perror("malloc failed");
        return NULL;
    }

    snprintf(combinedArray, newLength, "%s, %s\n", character, time);
    return combinedArray;
}


/* - - - - - - - - - - - - - - - STACK - - - - - - - - - - - - - - - */

void initializeStack(Stack *stack, int size) {
    stack->data = malloc(size);
    if (stack->data == NULL) {
        perror("Error allocation stack memory");
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->size = size;
}

void push(Stack *stack, const char *entry) {
    if (stack->top < stack->size - 1) {
        stack->data[++stack->top] = strdup(entry);
        if (stack->data[stack->top] == NULL) {
            perror("strdup failed");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Stack Overflow.\n");
    }
}

char *pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return NULL;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void displayStack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%s\n", stack->data[i]);
    }
}

void freeStack(Stack *stack) {
    while (stack->top >= 0) {
        free(stack->data[stack->top--]);
    }
    free(stack->data);
}

void saveStackToFile(Stack *stack, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i <= stack->top; i++) {
        fprintf(file, "%s\n", stack->data[i]);
    }

    fclose(file);
}


/* - - - - - - - - - - - - - - - INPUT TEXT - - - - - - - - - - - - - - - */

char *extractInputData(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *rawData = malloc(fileSize + 1);
    if (rawData == NULL) {
        perror("Error allocating memory for input data");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(rawData, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error reading input data");
        free(rawData);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    rawData[bytesRead] = '\0';

    fclose(file);

    char *parsedData = parseText(rawData);
    free(rawData);

    return parsedData;
}

char *parseText(const char *rawData) {
    char *parsedData = malloc(strlen(rawData) + 1);
    if (parsedData == NULL) {
        perror("Error allocating memory for parsed data");
        exit(EXIT_FAILURE);
    }

    const char *sourcePointer = rawData;
    char *destinationPointer = parsedData;

    while (*sourcePointer != '\0') {
        *destinationPointer = *sourcePointer;

        if (*sourcePointer == ' ') {
            while (*(sourcePointer + 1) == ' ') {
                sourcePointer++;
            }
        }

        sourcePointer++;
        destinationPointer++;
    }

    *destinationPointer = '\0';
    return parsedData;
}

/* - - - - - - - - - - - - - - - COMMANDS - - - - - - - - - - - - - - - */
void printCommands() {
    printf("\n"
        "start   |   start keystroke session\n"
        "help    |   provide additional resources and information\n"
        "text    |   print input text\n"
        "exit    |   exit the program\n"
    );
}

void helpCommand() {
    printf("help command\n");
}


/*
void start_logger() {
    // call initialize_capture()

    // call display_provided_text()

    // call run_session()
}

void stop_logger() {
}

int start_initialization() {
    // ensure CSV folder exists

    // print: program name, version #, author

    // provide introductory display and list of available commands

    // returns integer indicating successful initialization
}

int start_deinitialization() {
    // call cleanup_display()

    // call cleanup_storage()

    // call cleanup_timing()
}

void run_session() {
    // call start_countdown()

    // call start_logger()

    // call start_capture()
}
*/
