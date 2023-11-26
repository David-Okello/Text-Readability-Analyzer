# Text Readability Analyzer

## Problem Statement
- Some adults may struggle to find appropriate books for their children.
- Researchers may face challenges in writing project proposals that sponsors find hard to comprehend, leading to potential loss of funding.
- Teachers might create problem sets with complex language, making it difficult for students to understand and address the challenges.
- Businesses may use complicated language in reports, causing clients to lose interest.
- People often write essays, news, and other texts without assurance that their intended audience will understand the content.

## Solution Description
Our program addresses the above issues. It takes a text file name as a command line argument, reads through its characters, and analyzes the text using the Flesch Reading Ease algorithm. The program provides information on the number of words and sentences in the text file, as well as an assessment of the text's readability for a specific audience.

## Assumptions
- The text file is in English, following correct punctuation rules.
- Sentences end with ?, !, or ., including abbreviated words like "Mr."
- A word is considered any set of characters ending with a space, full stop, question mark, or exclamation mark.
- Vowels include a, e, i, o, u, y.
- Syllables are counted based on vowel patterns, with adjustments for words ending in 'e' or 'le.'

## Program Usage
In the terminal, run the following command:

```bash
./text_readability_analyzer.exe input_file.txt
```

## Code Structure
The program is written in C and consists of the following components:

 - main.c: The main program that reads the input text file, analyzes its content, and outputs readability statistics.
 - char_node: A custom data type to store a character and a pointer to the next character, used in creating a linked list for characters from the text file.
 - free_memory(): Function to free dynamically allocated memory.
 - count_sentences(): Function to count the number of sentences in the text file.
 - count_words(): Function to count the number of words in the text file.
 - count_syllables(): Function to count the number of syllables in the words of the text file.

## How to Run
Ensure that the executable file (e.g., text_readability_analyzer.exe) and your text file are in the same directory. Run the program in the terminal as described in the "Program Usage" section.

## Readability Metrics
The program calculates the Flesch Reading Ease score, providing an indication of how easy or difficult the text is to read. It also suggests the suitable audience age based on U.S. grade levels.

## License
This program is released under the MIT License.

## Acknowledgments
 - The Flesch Reading Ease algorithm is used to assess text readability.
 - Special thanks to the developers and contributors to the C programming language.
 - My team members who helped me work on this project

Feel free to contribute or provide feedback!