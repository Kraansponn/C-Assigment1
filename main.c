#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int arraysize = 7;
char myLetters[7];

const char filename = 'letter_values';
int letterValues[26];

/**
* Generates a number of random lower case letters.
* The letters will be stored in the given array.
*/
void generate_letters(int number, char *destination) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    int i;
    unsigned int rand_seed;
    printf("Number < 1000:\n");
    scanf("%d", &rand_seed); // initialise the PRNG
    getchar();
    srandom(rand_seed);

    // Half of the letters should be vowels
    for (i = 0; i < number / 2; i++, destination++)
        *destination = vowels[random() % 5];

    for (; i < number; i++, destination++)
        *destination = random() % 26 + 'a';
}

/**
* Tries to read the file into the array.
2
* Each line has one value.
*
* Returns the number of lines read or -1 in case of file open error.
*/
int read_array_from_file(const char *filepath, int *array, int array_length) {
    FILE *file;
    int i;

    if ((file = fopen(filepath, "r")) == NULL)
        return -1;

    for (i = 0; i < array_length; i++) {
        if (fscanf(file, "%d", &array[i]) == EOF)
            break;
    }

    return i;
}


/**
 *
 */
//
//char getNextChar(char *currentChar){
//    if (strcmp( currentChar, "") == 0){
//        return myLetters[0];
//    }
//
//    int count = 0;
//    int foundCurrentLetter = -1;
//    int foundNextLetter = -1;
//
//    while (foundCurrentLetter == -1 && foundNextLetter == -1){
//        count++;
//
//        if (strcmp(currentChar, &myLetters[count]) ==0 && strcmp(currentChar , &myLetters[count+1]) == 0){
//            // We found our current letter and the next letter is different
//
//            foundCurrentLetter = 1;
//            foundNextLetter = 1;
//
//        }
//
//    }
//
//    return myLetters[count+1];
//
//
//}


int main() {
    printf("Hello, World!\n");

    generate_letters(arraysize, myLetters);


    read_array_from_file(
            "C:\\Users\\Kornel\\Google Drive (kornel.oskroba@mycit.ie)\\Year 2\\Semester 2\\C programing\\Assigment1\\letter_values",
            letterValues, sizeof(letterValues));

    int loop;
    for (loop = 0; loop < arraysize; loop++) {
        printf("%c = %d \n", myLetters[loop], myLetters[loop]);
    }

    int loop2;
    for (loop2 = 0; loop2 < 26; loop2++) {
        printf("%d", letterValues[loop2]);
    }

    printf("%d", letterValues['f' - 97]);

    int myLettersCopy[7];

    int loop3 = 0;
    for (loop3 = 0; loop3 <= sizeof(myLetters); loop3++) {
        myLettersCopy[loop3] = myLetters[loop3];
    }


    int uniqueLetters[7];

    for (int i = 0; i < sizeof(myLettersCopy); i++) {
        char currentChar = &myLettersCopy[i];

        if (strcmp(currentChar, myLettersCopy[i])){

        }

    }





//    char mychatr = getNextChar("o");
//    printf("fgdfgdssfgdsfgd %c",mychatr);

    return 0;
}
