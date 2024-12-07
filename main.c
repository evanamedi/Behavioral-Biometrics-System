#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "config.h"

// let us ignore the mess for now

typedef struct Stack {
    char *data;
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
void push(Stack *stack, char character);
char pop(Stack *stack);
int isEmpty(Stack *stack);
void displayStack(Stack *stack);
void saveStackToFile(Stack *stack, const char *filename);
void clearScreen();
char getch();
void captureInput();
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
    initializeStack(&history_stack, 1024);
    initializeStack(&editable_stack, 1024);

    char input;
    int x_count = 0;

    printf("Start typing (Press 'x' 3 times to exit)\n");

    while (1) {
        input = getch();

        if (input == '\r') {
            // enter
            printf("\n");
        } else if (input == '\b' || input == 127) {
            // backspace
            if (editable_stack.top > 0) {
                pop(&editable_stack);
            }
        } else if (input == 'x') {
            x_count++;
            if (x_count == 3) {
                break;
            }
        } else {
            x_count = 0;
            push(&history_stack, input);
            push(&editable_stack, input);
        }

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

/* - - - - - - - - - - - - - - - STACK - - - - - - - - - - - - - - - */

void initializeStack(Stack *stack, int size) {
    stack->data = (char *) malloc(size * sizeof(char));
    stack->top = -1;
    stack->size = size;
}

void push(Stack *stack, char character) {
    if (stack->top < stack->size - 1) {
        stack->data[++stack->top] = character;
    } else {
        printf("Stack Overflow.\n");
    }
}

char pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void displayStack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        putchar(stack->data[i]);
    }
}

void saveStackToFile(Stack *stack, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    while (!isEmpty(stack)) {
        char c = pop(stack);
        fputc(c, file);
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

void startCommand() {
    printf("start command\n");
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
