#include <stdio.h>
#include <stdlib.h>

#define START_SIZE 1024

struct Stack {
    int top;
    int items[START_SIZE];
};

void initialize_stack(struct Stack *stack) {
    stack->top = -1;
}


void start() {
    // temp file name
    const char *filename = "test.txt";

    // grab the text in the test.txt file & store returned data in 'text'
    char *text = load_text(filename);
    if (text) {
        printf("File content:\n%s\n", text);
        free(text);
    }

    // create keystrokes stack
    struct Stack keystrokes;
    initialize_stack(&keystrokes);

    // create buffer display stack
    struct Stack buffer_display;
    initialize_stack(&buffer_display);
}

char *load_text(const char *filename) {
    // read text from input file and store it in an array
    // open file in read mode
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("failed to open file");
        return NULL;
    }

    // seek to the end to determine file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file); // move back to the start of the file

    // allocate memory for the array (+1 for the null terminator)
    char *textArray = (char *) malloc((fileSize + 1) * sizeof(char));
    if (!textArray) {
        perror("failed to allocate memory for textArray");
        fclose(file);
        return NULL;
    }

    // read the file content into the array
    size_t bytesRead = fread(textArray, sizeof(char), fileSize, file);
    if (bytesRead != fileSize) {
        perror("failed to read file");
        free(textArray);
        fclose(file);
        return NULL;
    }

    // null-terminate the string
    textArray[fileSize] = '\0';

    // close the file
    fclose(file);

    // return the pointer to the array
    return textArray;
}


void exit() {
    // gracefully end program and begin de-initialization sequence
}

void help() {
    // provide list of commands
}
