#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//TODO: Inseret abolsulte path to the letters text file line 178

const int arraysize = 7; //declaring the variable that will set the size of the array for the randomly generated letters
char myLetters[7];

const char filename = 'letter_values';
int letterValues[26]; //array to store the letter values that will be imported form a file

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
 * Used to display how many of each letter will be available
 */
int unique_elements(char arr[], int len, char *uniqueLetterArray) {

    char counted[len];
    int j, n, count, flag;

    counted[0] = arr[0];

    count = 1;/*one element is counted*/

    for (j = 0; j <= len - 1; ++j) {
        flag = 1; //the counted array will always have unique elements
        for (n = 0; n < count; ++n) {
            if (arr[j] == counted[n]) {
                flag = 0;
            }
        }
        if (flag == 1) {
            ++count; //increase count of how many unique letters are avaliable
            counted[count - 1] = arr[j]; // add letter to new array
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
    for (int i = 0; i < sizeof(uniqueLetter); i++) { //loop for lenght of unique letters
        char currentLetter = uniqueLetter[i];
        int count = 0;

        for (int j = 0; j < sizeof(myLetters); j++) {

            if (strlen(&currentLetter) == 0) { //making sure the array isn't empty
                break;
            }

            char anoherletter = myLetters[j]; //getting a letter from the randomly generated letter array

            if (currentLetter == anoherletter) { //comparing if the letters are the same
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
 * Makes sure that all the letters of the word the user put is exist as an option
 */

int check_if_word_is_valid(char *userWord, char *myLettersCopy) {
    int validLetters = 0;
    for (int j = 0; j < sizeof(myLettersCopy) - 1; j++) {

        char currentLetter = myLettersCopy[j]; //gets a letter from letters array

        for (int i = 0; i < sizeof(userWord); i++) {

            char *currentWordLetter = userWord[i]; //gets a letter from the users word

            if (currentLetter == currentWordLetter) { //compares the letters
                userWord[i] = '#'; //replaces the letters with an unused character
                myLettersCopy[j] = '#';
                validLetters++; // counts how many letters were valid
                break;
            }

        }
    }

    if (validLetters == strlen(userWord)) { //compares amount of valid letters to the amount of letters in the user word
        return 1; // if the number is the same then the word is valid
    } else {
        return 0; //if the number is not the same the word is not valid
    }
}


/**
 *  claculates the value of the letters in the word and returns a total
 */

int get_value_of_word(int *letterValues, char *userWord) {
    int wordTotal = 0;
    for (int i = 0; i <= sizeof(userWord) - 2; i++) {
        char currentLetter = userWord[i];
        int letterPosition = currentLetter - 97; // it's minus 97 beacuse that will give the loaction of the letter in the alphabet
        wordTotal = wordTotal + letterValues[letterPosition]; // the position of the letter is then used to read in the value of the letter
    }
    return wordTotal;

}

int main() {
    generate_letters(arraysize, myLetters);

    //TODO: change the abolsulte path to the letters text file
    read_array_from_file(
            "C:\\Users\\Kornel\\Google Drive (kornel.oskroba@mycit.ie)\\Year 2\\Semester 2\\C programing\\Assigment1\\letter_values", // loacion of the file with the letter values
            letterValues, sizeof(letterValues));

    char uniqueLetters[sizeof(myLetters)];

    int numberOfUniqueLetters = unique_elements(myLetters, sizeof(myLetters), uniqueLetters);

    int uniqueLettersCount[sizeof(myLetters)];
    get_unique_letter_count(myLetters, uniqueLetters, uniqueLettersCount);

    printf("\n");
    printf("Your Letters and their count are:");
    for (int loop = 0; loop < numberOfUniqueLetters; loop++) {
        printf("\n %c --> %d", uniqueLetters[loop], uniqueLettersCount[loop]); //prints the unique letters and how many are available
    }

    char wordInput[arraysize]; //declaring an array for user input it's sized for arraysize as that is the maximum size any valid word can be
    char wordInputCopy[arraysize];

    int wordScore = 0;
    int currentScore = 0; // used to keep track of the total score

    char myLettersCopy[arraysize]; //copy of the letter availabe for use

    int wordsEntered = 0; //keeps track of how many valid words were entered
    char *listOfWords[1000][arraysize+1]; //used to keep all valid words
    int *listOfScore[1000]; // used to keep all the scores from vaild words


    int keepPlaying = 1; //used to run a while loop
    char keepPlayingChoice; //used when asking if the player wishes to continue

    while (keepPlaying == 1) {

        printf("\n");
        printf("Enter Word: ");
        scanf("%s", wordInput); //gets user input

        for (int i = 0; wordInput[i]; i++) { //makes all the letters lowercase
            wordInput[i] = tolower(wordInput[i]);
        }

        printf("%s, ", wordInput); // prints the users word out

        copy_letters(myLetters, myLettersCopy); //makes a copy of the letters availabe to be used later
        copy_letters(wordInput, wordInputCopy); //makes a copy of the users word
        copy_letters(wordInputCopy, wordInput);

        if (check_if_word_is_valid(wordInputCopy, myLettersCopy) == 1) { // check is the word entered is valid

            for (int i = 0; i < arraysize; ++i) { // saves the word
                listOfWords[wordsEntered][i] = wordInput[i];
            }

            wordScore = get_value_of_word(letterValues, wordInput); // gets the score of the word

            listOfScore[wordsEntered] = wordScore; //saves the score of the word

        printf("Worth %d Points,",wordScore);

            currentScore = currentScore + wordScore; //adds up the score to get a total

            ++wordsEntered;
        } else { //if the word ius not valid prints out a error message
            printf(" is invalid!");
            printf("\n");
        }


        printf(" Current Total Is %d Points \n", currentScore); // prints the total
        getchar();
        printf("Try Again? Y/N : ");
        scanf("%c", &keepPlayingChoice); //gets user input if they wish to continue playing
        getchar();

        if ((keepPlayingChoice == 'n') || (keepPlayingChoice == 'N')) { //checks if the while loops should end
            keepPlaying = 0;
            printf("You Provided The Following Words");
            printf("\n");
            for (int i = 0; i < wordsEntered; i++) {

                for (int z = 0; z < arraysize; z++) {
                    printf("%c", listOfWords[i][z]); //prints out the words
                }
                printf("---> %d", listOfScore[i]); //prints out the scores of each word
                printf("\n");
            }
        }

        printf("Total Score: %d",currentScore); //prints the final total score
    }

    return 0;
}
