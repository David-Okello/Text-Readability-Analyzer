/*
Problem
    - Some adults may not know appropriate books to give to their children. 
    - Some researchers may write challenging project proposals that sponsors may not easily comprehend; hence they lose their funding. 
    - Some teachers may create problem sets that may have a challenging language for their students; hence the student struggles to 
      address the challenge. Some businesses may also have complicated language in their reports, making their clients lose interest 
      in their work. People write essays, news, and other text files in our day-to-day activities without assurance that their 
      intended audience may understand their work.
Description of how the program solves the problem
    - Our program solves this issue. First, the program takes a text file name as a command line argument. 
    - Next, the program opens the given text file, reads through all the characters, and determines the number of words, sentences, 
      and syllables. Finally, the program determines how easy it is to read the text file using the Flesch Reading Ease algorithm.
    - The program outputs the number of words and sentences. It also shows the intended audience of the text file.
List of assumptions in the program
    - The language in the text file is in English and the text follows correct punctuation rules. English is used in counting syllables.
    - A sentence ends with only the following punctations: ?, ! and . This includes abbreviated words such as Mr. which will be 
      counted as a sentence.
    - A word is counted as so when character(s) has a space at the end (works even if there is a fullstop/question mark/exclamation 
      mark since grammar rules ensure a blank space between two sentences) and the last character of the text file and it is not a space.
    - Vowels are the letters: a, e, i, o, u, y
    - A syllable is counted as so when the first letter is a vowel, when two consecutive letters are such that a vowel is followed 
      by a consonant. When a word ends with the character 'e', one syllable is deducted. However, when a word ends with 'le' and the length of the word is more than two characters and the thirdlast character is not a vowel, a syllable is added. If no syllables have been added in a word, atleast one syllable will be added.
Usage of the program
    - In the terminal, run ./final_project.exe test.txt
    The program will use a text file called test.txt

Make sure to install a compiler first
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

// A custom data type to store a character and a pointer to the next character
typedef struct char_node
{
    // Store a character
    char c;
    // Store a pointer to the next node
    struct char_node *next;
}
char_node;

// A linked list to store all the characters from a text file
char_node *all_text = NULL;

// A function to free dynamic allocated memory
void free_memory();

// A function to count the sentences in the text file
int count_senctences();

// A function to count the words in the text file
int count_words();

// A function to count the syllables of the words in the text file
int count_syllables();

int main(int argc, char *agrv[])
{
    // Check for a invalid usage. Number of arguments must be 2.
    if (argc != 2)
    {
        printf("Usage: final_project_executable_file name_of_text_file i.e ./final_project test.txt\n");
        return 1;
    }

    // Check if the file has a .txt extension
    for(int i=0; i<strlen(agrv[1]); i++)
    {
        agrv[1][i]=tolower(agrv[1][i]);
    }
    char *check = strstr(agrv[1], ".txt");

    if (check == NULL)
    {
        printf("The file must have a .txt extension.\n");
        return 1;
    } 

    // Opening the .txt file
    FILE *TEXT_INPUT = fopen(agrv[1], "r");

    if (TEXT_INPUT == NULL)
    {
        printf("There is a problem in retrieving the file. Ensure the text file exists and present in the working directory.\n");
        return 1; 
    }

    // Store the given character read from a text file
    char temp_character; 

    // Read each character from the text file
    while ((temp_character = fgetc(TEXT_INPUT)) != EOF)
    {
        // Create a node for the character to store in the linked list
        char_node *new_node = malloc(sizeof(char_node));

        // Ensure enough memory is present
        if (new_node == NULL)
        {
            printf("Currently, there is not enough memory. Please try again later\n");
            // Free any present memory
            free_memory();
            return 1;
        }

        // Add the node at the last point of the linked list
        new_node->c = temp_character;
        new_node->next = NULL;

        // Check if the linked list is empty
        if (all_text == NULL)
        {
            all_text = new_node;
        }
        else
        {
            // Create a node to tranverse the linked list
            char_node *tmp_node = all_text;

            // Insert at the last node in the linked list
            while (tmp_node->next != NULL)
            {
                tmp_node = tmp_node->next;

            }

            tmp_node->next = new_node;
        }
    }

    // Close the file
    fclose(TEXT_INPUT);

    // Get the total number of sentences
    int sentences_number = count_senctences();

    // Get the total number of words
    int words_number = count_words();

    // Get the total number of syllables
    int syllables_number = count_syllables();

    // Store the average number of words per sentence
    double average_words_per_sentence = (double) words_number / sentences_number;

    // Store the average number of syllables in a word
    double average_syllables_per_word = (double) syllables_number / words_number;

    // Calculate Reading Ease value
    double reading_ease_value = round(206.835 - (1.015 * average_words_per_sentence) - (84.6 * average_syllables_per_word));

    // Calculate Grade Level
    int grade_level = round((0.39 * average_words_per_sentence) + (11.8 * average_syllables_per_word) - 15.59);

    printf("Number of sentences: %i sentences\n", sentences_number);
    printf("Number of words: %i words\n", words_number);
    printf("Number of syllables: %i syllables\n", syllables_number);

    printf("\nReadability:\t");
    // Display the readability level
    if (reading_ease_value < 30.0)
    {
        printf("Very difficult\n");
    }
    else if (reading_ease_value < 50.0)
    {
        printf("Difficult\n");
    }
    else if (reading_ease_value < 60.0)
    {
        printf("Fairly difficult\n");
    }
    else if (reading_ease_value < 70.0)
    {
        printf("Standard\n");
    }
    else if (reading_ease_value < 80.0)
    {
        printf("Fairly easy\n");
    }
    else if (reading_ease_value < 90.0)
    {
        printf("Easy\n");
    }
    else if (reading_ease_value < 100.0)
    {
        printf("Very easy\n");
    }

    // Since the algorithm returns a U.S grading level, grade 1 represents class 1 in 844 system. Approximate age of a class one student is 6yrs.
    printf("Suitable audience:\t %i years and above", grade_level + 6);

    return 0;
}

// A function to free dynamic allocated memory
void free_memory()
{
    // Check if the linked list is empty. If it is, return
    if (all_text == NULL)
    {
        return;
    }

    // If the linked list is not empty

    // Create a temporary node
    char_node *tmp = all_text;

    // Free the memory
    while (tmp != NULL)
    {
        all_text = tmp;
        tmp = tmp->next;

        free(all_text);
    }

    return;
}

// A function to count the sentences in the text file
int count_senctences()
{
    // Keep track of the number of sentences
    int number_of_sentences = 0;

    // Create a node to tranverse the linked list
    char_node *tmp_node = all_text;

    while (tmp_node != NULL)
    {
        //Check if the character is a period,question mark or exclamation point and if so add the number to sentences.
        if ((tmp_node->c == '!') || ( tmp_node->c == '?') || (tmp_node->c == '.'))
        {
            number_of_sentences++;
        }
        tmp_node = tmp_node->next;
    }

    return number_of_sentences;
}

// A function to count the words in the text file
int count_words()
{
    // Keep track of the number of words
    int number_of_words = 0;

    // Create a node to tranverse the linked list
    char_node *tmp_node = all_text;

    while (tmp_node != NULL)
    {
        // If it is the last node
        if ((tmp_node->next) == NULL)
        {
            // Check the character is not a blank space
            if ((tmp_node->c != ' '))
            {
                number_of_words++;
            }
        }

        //Check if the character is a blank space
        if ((tmp_node->c) == ' ')
        {
            number_of_words++;
        }
        tmp_node = tmp_node->next;
    }

    return number_of_words;
}

// A function to count the syllables of the words in the text file
int count_syllables()
{
    // Keep track of the number of syllables
    int number_of_syllables = 0;

    // Create a node to tranverse the linked list
    char_node *tmp_node = all_text;

    while (tmp_node != NULL)
    {
        // Create a linked list to store the characters of a word
        char_node *new_word = NULL;

        // Store number of characters in a word
        int number_of_characters = 0;

        // Perform a while loop. As along as it is not the last character/ a blank space.
        while((tmp_node->c != ' ') && ((tmp_node->next) != NULL))
        {
            // Store the current character
            char temp_character;

            // Check if the character is alphabetic. Only add alphabetic characters
            if ((isalpha(tmp_node->c)) != 0)
            {
                // Ensure the character is in lower case.
                temp_character = tolower(tmp_node->c);

                // Create a node for the character to store in the linked list
                char_node *new_node = malloc(sizeof(char_node));

                // Ensure enough memory is present
                if (new_node == NULL)
                {
                    printf("Currently, there is not enough memory. Please try again later\n");
                    // Free any present memory
                    free_memory();

                    // Free any memory used by the new_word linked list
                    if (new_word != NULL)
                    {
                        // Create a temporary node
                        char_node *temporary = new_word;

                        // Free the memory
                        while (temporary != NULL)
                        {
                            new_word = temporary;

                            temporary = temporary->next;

                            free(new_word);
                        }
                    }
                    exit(-1);
                }

                // Add the node at the last point of the linked list
                new_node->c = temp_character;
                new_node->next = NULL;

                // Check if the linked list is empty
                if (new_word == NULL)
                {
                    new_word = new_node;
                }
                else
                {
                    // Create a node to tranverse the linked list
                    char_node *temp_node = new_word;

                    // Insert at the last node in the linked list
                    while (temp_node->next != NULL)
                    {
                        temp_node = temp_node->next;
                    }

                    temp_node->next = new_node;
                }

                // Increment number of characters
                number_of_characters++;
            }

            // Proceed to the next node
            tmp_node = tmp_node->next;
        }

        // Proceed to the next node
        tmp_node = tmp_node->next;

        // Ensure at least there are some characters present to proceed with the steps below
        if (number_of_characters > 0)
        {

            // Create a string to store the word
            char current_word[number_of_characters + 1];

            // Create a temporary node
            char_node *temporary = new_word;

            // Keep track of the characters filled in the string
            int counter = 0;

            // Free memory as populate string
            while (temporary != NULL)
            {
                // Fill the character at a particular index
                current_word[counter] = temporary->c;

                // Increment the counter
                counter++;

                // Free memory
                new_word = temporary;
                temporary = temporary->next;

                free(new_word);
            }

            // Add the null character
            current_word[number_of_characters] = '\0';

            // Store initial value of syllables
            int initial_syllable_count = number_of_syllables;

            // The list of vowels
            const char* vowels = "aeiouy";

            // Check if the first character is a vowel. If so, add the number of syllables
            if (strchr(vowels, current_word[0]) != NULL)
            {
                number_of_syllables++;
            }
            // Loop through all characters in the string
            for (int i = 1; i < number_of_characters; i++)
            {
                // Check if the current character is a vowel and the previous character is not a vowel
                if (strchr(vowels, current_word[i]) != NULL && strchr(vowels, current_word[i - 1]) == NULL)
                {
                    number_of_syllables++;
                }
            }
            // Check if the last character ends with letter e
            if (current_word[number_of_characters - 1] == 'e')
            {
                number_of_syllables--;
            }
            // Check if the last character ends with letter e and second last character is l and length of word is greater than two and third last letter is not a vowel
            if ((strcmp(&current_word[number_of_characters - 2], "le") == 0) && (number_of_characters > 2) && (strchr(vowels, current_word[number_of_characters - 3]) == NULL))
            {
                number_of_syllables++;
            }
            // Ensure there is atleast one syllable is added
            if (initial_syllable_count == number_of_syllables)
            {
                number_of_syllables++;
            }
        }
    }

    return number_of_syllables;
}