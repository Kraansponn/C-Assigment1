#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
 * Finds all the unique letters in an array and adds them to an array
 */
int unique_elements(char arr[], int len, char *uniqueLetterArray) {

    char counted[len];
    int j, n, count, flag;

    counted[0] = arr[0];

    count = 1;/*one element is counted*/

    for (j = 0; j <= len - 1; ++j) {
        flag = 1;;
        /*the counted array will always have 'count' elements*/
        for (n = 0; n < count; ++n) {
            if (arr[j] == counted[n]) {
                flag = 0;
            }
        }
        if (flag == 1) {
            ++count;
            counted[count - 1] = arr[j];
            // add letter to new array
            uniqueLetterArray[count - 1] = counted[count - 1];
        }
    }

    uniqueLetterArray[0] = arr[0]; // Because it would get wrong letter

    return count;
}

/**
 * Finds all the unique letters in an array and Counts how many times they occur
 */

void get_unique_letter_count(char *myLetters, char *uniqueLetter, int *uniqueLettersCount) {
    for (int i = 0; i < sizeof(uniqueLetter); i++) {
        char currentLetter = uniqueLetter[i];
        int count = 0;

        for (int j = 0; j < sizeof(myLetters); j++) {

            if (strlen(&currentLetter) == 0) {
                break;
            }

            char anoherletter = myLetters[j];

            if (currentLetter == anoherletter) {
                count++;
                uniqueLettersCount[i] = count;
            }
        }
    }
}

/**
 * Makes a copy of the generated letters
 */

int copy_letters(char *myLetters, char *myLettersCopy) {

    for (int i = 0; i < sizeof(myLetters); i++) {
        myLettersCopy[i] = myLetters[i];
    }
}


/**
 *
 */

int check_if_word_is_valid(char *userWord, char *myLettersCopy) {
    int validLetters = 0;
    for (int j = 0; j < sizeof(myLettersCopy) - 1; j++) {

        char currentLetter = myLettersCopy[j];

        for (int i = 0; i < sizeof(userWord); i++) {

            char *currentWordLetter = userWord[i];

            if (currentLetter == currentWordLetter) {
                userWord[i] = '#';
                myLettersCopy[j] = '#';
                validLetters++;
                break;
            }

        }
    }

    if (validLetters == strlen(userWord)) {
        return 1;
    } else {
        return 0;
    }
}


/**
 *
 */

int get_value_of_word(int *letterValues, char *userWord) {
    int wordTotal = 0;
    for (int i = 0; i <= sizeof(userWord) - 2; i++) {
        char currentLetter = userWord[i];
        int letterPosition = currentLetter - 97;
        wordTotal = wordTotal + letterValues[letterPosition];
    }
    return wordTotal;

}

int main() {
    generate_letters(arraysize, myLetters);

    read_array_from_file(
            "C:\\Users\\Kornel\\Google Drive (kornel.oskroba@mycit.ie)\\Year 2\\Semester 2\\C programing\\Assigment1\\letter_values",
            letterValues, sizeof(letterValues));

    char uniqueLetters[sizeof(myLetters)];

    int numberOfUniqueLetters = unique_elements(myLetters, sizeof(myLetters), uniqueLetters);

    int uniqueLettersCount[sizeof(myLetters)];
    get_unique_letter_count(myLetters, uniqueLetters, uniqueLettersCount);

    printf("\n");
    printf("Your Letters and their count are:");
    for (int loop = 0; loop < numberOfUniqueLetters; loop++) {
        printf("\n %c --> %d", uniqueLetters[loop], uniqueLettersCount[loop]);
    }

    char wordInput[arraysize];
    char wordInputCopy[arraysize];

    int wordScore = 0;
    int currentScore = 0;

    char myLettersCopy[arraysize];

    int wordsEntered = 0;
    char *listOfWords[1000][arraysize+1];
    int *listOfScore[1000];


    int keepPlaying = 1;
    char keepPlayingChoice;

    while (keepPlaying == 1) {

        printf("\n");
        printf("Enter Word: ");
        scanf("%s", wordInput);

        for (int i = 0; wordInput[i]; i++) {
            wordInput[i] = tolower(wordInput[i]);
        }

            printf("%s, ", wordInput);

        copy_letters(myLetters, myLettersCopy);
        copy_letters(wordInput, wordInputCopy);
        copy_letters(wordInputCopy, wordInput);

        if (check_if_word_is_valid(wordInputCopy, myLettersCopy) == 1) {


            for (int i = 0; i < arraysize; ++i) {
                listOfWords[wordsEntered][i] = wordInput[i];
            }

            wordScore = get_value_of_word(letterValues, wordInput);

            listOfScore[wordsEntered] = wordScore;

        printf("Worth %d Points,",wordScore);

            currentScore = currentScore + wordScore;

            ++wordsEntered;
        } else {

            printf(" is invalid!");
            printf("\n");
        }


        printf(" Current Total Is %d Points \n", currentScore);
        getchar();
        printf("Try Again? Y/N : ");
        scanf("%c", &keepPlayingChoice);
        getchar();

        if ((keepPlayingChoice == 'n') || (keepPlayingChoice == 'N')) {
            keepPlaying = 0;
            printf("WE were here");
            printf("\n");
            for (int i = 0; i < wordsEntered; i++) {

                for (int z = 0; z < arraysize; z++) {
                    printf("%c", listOfWords[i][z]);
                }
                printf("---> %d", listOfScore[i]);
                printf("\n");
            }
        }

        printf("Total Score: %d",currentScore);
    }

    return 0;
}
