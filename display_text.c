#include <stdio.h>
#include <stdlib.h>

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


void display_provided_paragraph() {
}

void update_display(char key) {
}


void render_display() {
}

void cleanup_display() {
}
