#include <stdio.h>
#include <stdlib.h>

// Attempt to replicate some basic behaviour and functions similar to std::string in C++
// with proper memory allocation and without leaks

typedef struct {
    char* contents;
    unsigned length;
} string;

void str_set(string *source, char *newString) {
    // Remove the currently saved contents within the input string
    if (source != NULL) free(source->contents);

    // Calculate size
    size_t i = 0;
    while (newString[i] != '\0') {
        i++;
    }
    // Allocate new memory for the string we plan to insert
    source->contents = (char *)malloc((i) * sizeof(char));
    
    // If there was an error, we'll stop here.
    if (source->contents == NULL) {
        return;
    }
    
    source->length = i;

    for (size_t i = 0; i < source->length; i++) {
        source->contents[i] = newString[i];
    }
    source->contents[source->length] = '\0';
}

void str_delete(string *source) {
    if (source != NULL) free(source->contents);
    // Length will automatically get deleted when it goes out of scope, as it is stored on the stack
    source->length = 0;
}

void str_reverse(string *source) {
    if (source == NULL) {
        fprintf(stderr, "Can't reverse an empty string");
        exit(EXIT_FAILURE);
    }

    // Assign our new memory space, into which we will copy over the reversed contents
    char *tmp = (char *)malloc(sizeof(source->contents));
    
    // Copy the string from source into tmp
    for (size_t i = 0; i < source->length; i++) {
        tmp[i] = source->contents[source->length-i-1];
    }

    // Add null character to make it a valid string
    tmp[source->length] = '\0';

    // We need to free the memory pointed to by source->contents prior to reassigning it, in order to prevent memory leaks
    free(source->contents);
    // As we are assigning our source contents directly to the memory pointed to by tmp, we don't need to use free(tmp) afterwards
    source->contents = tmp;
}

void str_append(string *source, char *toAppend) {
    if (source == NULL) {
        fprintf(stderr, "Can't reverse an empty string");
        exit(EXIT_FAILURE);
    }

    // Determine size of string to be appended
    size_t i = 0;

    while (toAppend[i] != '\0') {
        i++;
    }

    // Allocate new space for the extended string
    size_t newLength = (source->length + i)*sizeof(char);

    char* tmp = (char *)malloc(newLength);

    for (size_t i = 0; i < source->length; i++) {
        tmp[i] = source->contents[i];
    }

    for (size_t i = source->length; i < newLength; i++) {
        tmp[i] = toAppend[i-source->length];
    }

    tmp[newLength] = '\0';

    free(source->contents);

    source->contents = tmp;
    source->length = newLength;
}

string str_substr(string *source, size_t start, size_t end) {
    string output;
    output.length = end - start + 1;
    // Allocate space for the substring
    output.contents = (char *)malloc(output.length*sizeof(char));

    for (size_t i = 0; i < output.length; i++) {
        output.contents[i] = source->contents[i + start]; // in our source string we will offset by the start value
    }

    // In this case, there is no memory to free - this function exclusively creates new memory
    return output;
}



int main() {
    string str;
    str_set(&str, "Hello Lol");
    printf("%s\n", str.contents);
    printf("Length: %d\n", str.length);
    str_reverse(&str);
    printf("Reversed string: %s\n", str);
    str_reverse(&str);
    printf("Reversed string: %s\n", str);
    str_append(&str, ", hi!");
    printf("Appended string: %s\n", str);
    string sub = str_substr(&str, 1, 6);
    printf("Substring: %s", sub);
}