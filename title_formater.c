/******************************************************************
* title_formater.c: This program will ask the user to enter the   *
*                   name of the c program file and a description  *
*                   of the program; it will then print out a      *
*                   formatted version within the comment          *
*                   deliminator like so.                          *
******************************************************************/

#include <stdio.h>
#include <string.h>

#define WORD_SIZE 20
#define TITLE_BLOCK_SIZE 10000
#define ROW_WIDTH 65

int read_line(char *str, int len);
void print_row(char *lead_str, char *title_block);

int main(void) {
    char title_block[TITLE_BLOCK_SIZE];
    char title[WORD_SIZE];
 
    printf("Enter name of the title block (maximum 20 characters): ");
    read_line(title, WORD_SIZE);

    //printf("%s\n", title);
    printf("Now enter the block of title text: ");
    read_line(title_block, TITLE_BLOCK_SIZE);

    printf("\n\n\n");
    printf("/******************************************************************\n");
    print_row(title, title_block);

    printf("******************************************************************/");
    printf("\n\n\n");



    return 0;
}

void print_row(char *title, char *title_block) {
    int leading_space, i, r;
    int space_pos = 0;
    char row_text[ROW_WIDTH + 2] = "* ";
    int len_title_block = strlen(title_block);

    // create first row
    // * title.c: title_block stat here
    strcat(row_text, title);
    strcat(row_text, ": ");   
    
    // create a string to be used as spacer infront of 
    // tittle block
    // *          text start here
    leading_space = strlen(row_text);
    char str_leading_spaces[WORD_SIZE + 4] = "*"; 
    for (i = 1; i < (leading_space); i++) {
        str_leading_spaces[i] = ' ';
    }
    str_leading_spaces[i] = '\0';

    i = 0;
    
    while (1) {
        // printing each row
        // for each row, start after the resversed spaces
        // * title.c: title_block stat here, to the end of   *
        // *          line, then starts again to the end of  *
        // *          another line.                          *
        for (r = strlen(row_text); r < (ROW_WIDTH) && i < len_title_block; i++, r++) {
            // detects a white space, indicate the postiion before and after are words.
            // saving it for later use.
            if (title_block[i] == ' ')
                space_pos = i;
            row_text[r] = title_block[i];
        }  

        if (i == len_title_block) {
            // we have reached the last line, last character.
            for (; r< (ROW_WIDTH); r++)
                row_text[r] = ' ';            
        } else if (row_text[r] != ' ') {
            // if the row_text[r+1] is not a space, then most likely we are breaking
            // in the middle of a word. We do not want that.
            // *          title_block stat here, to the end of li*
            // *          ne blah blah                           *
            // should be: 
            // *          title_block stat here, to the end of   *
            // *          line blah blah                         *
            // in the above example, row_text[r+1] is character 'n'
            // need to back off until prevoius space position
            // and fill the remainder of the sentence with space.
            
            // Here, value r indicates the beginning index of white spaces 
            // that need to fill out for the remainder of this row.

            r = r - (i - space_pos);
            // if r is <= leading_space, then we know the word size exceeds the row length.
            // we need to pring it out regardless.
            if (r > leading_space) {
                i = space_pos + 1; // we want to start the next sentence with a letter, not a white space.
                for (; r< (ROW_WIDTH); r++)
                    row_text[r] = ' ';
            }
        }
        // with the row with ' *\n'
        strcat(row_text, " *");
        printf("%s\n", row_text);

        // get out of while loop
        if (i == len_title_block)
            break;

        // initialize row_text for next row
        //row_text[ROW_WIDTH + 1] = '\0';
        memset(row_text, 0, sizeof(row_text));
        strcat(row_text, str_leading_spaces);
    }
}

int read_line(char *str, int len) {
    int i = 0;
    char c = getchar();
    char *p = str;
    
    // remove white space first
    for (; c == ' '; c = getchar())
        ;
    
    for (; i < (len - 1); i++) {
        if (c == '\n' || c == EOF)
            break;
        else
            p[i] = c;
        c = getchar();
    }
    p[i] = '\0';
    
    return i;    
}
