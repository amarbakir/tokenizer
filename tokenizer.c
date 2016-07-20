/*
 * tokenizer.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 * Holds a char string and the length of the current string being stored.
 */

struct TokenizerT_ {
  char token[500];
  int tklength;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
  TokenizerT *token;
  int charcount;
  int i;
  // Making copies of the arguments for TKCreate.
  char separatorstring[strlen(separators) + 1];
  char tstring[strlen(ts) + 1];
  token = (TokenizerT *)malloc(sizeof(TokenizerT));
  strcpy(separatorstring, separators);
  strcpy(tstring, ts);
  // Making sure the copies are null termiated.
  separatorstring[strlen(separators)] = '\0';
  tstring[strlen(ts)] = '\0';
  charcount = 0;
  /* 
   * Loop that runs through the length of the token string starting at a valid 
   * non-separator character looking for a separator or the end of the string 
   * so it can store a full token. 
  */
  for (i = 0; i < (strlen(ts)) + 1; i++) {
    // End of string or separator so we have our token.
    if (strchr(separators, ts[i]) != NULL || ts[i] == '\0') {
      token->tklength = charcount;
      token->token[charcount] = '\0';
      return token;
    }
    // Nothing to do keep going and copy the current char to the Tokenizer buffer.
    else if (strchr(separators, ts[i]) == NULL) {
      token->token[charcount] = ts[i];
      charcount++;
    }
  }
  return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
  // Simply frees the tokenizer object it receives via a pointer.
  free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
  char *token;
  /* 
   * Creates the char string memory location using the size of the token held as
   * an int in the Tokenizer object's tklength parameter. Then the token is copied.
   */
  token = (char *) calloc((tk->tklength + 1), sizeof(char));
  strncpy(token, tk->token, tk->tklength + 1);
  token[tk->tklength] = '\0';
  return token;
}

/*
 * TKPrint prints a character string with the required format for special
 * characters.
 */

void TKPrint(char *token) {
  int i;
  for(i = 0; i < strlen(token); i++) {
    switch (token[i]) {
      // For special characters converts them to the proper hex output.
    case 0x0a:
      printf("[0x0a]");
      break;
    case 0x09:
      printf("[0x09]");
      break;
    case 0x0b:
      printf("[0x0b]");
      break;
    case 0x08:
      printf("[0x08]");
      break;
    case 0x0d:
      printf("[0x0d]");
      break;
    case 0x0c:
      printf("[0x0c]");
      break;
    case 0x07:
      printf("[0x07]");
      break;
    case 0x5c:
      printf("[0x5c]");
      break;
    case 0x22:
      printf("[0x22]");
      break;
      // For nonspecial characters simply prints the character out.
    default:
      printf("%c", token[i]);
      break;
    }
  }
  if (i == strlen(token)) {
    printf("\n");
  }
}

/*
 * This function accepts a character string and returns a string that coincides
 * with the requirements outlined in the project description. Special characters
 * are transformed into their respective hex values and any rogue backslashes
 * are removed (including ones at the end of a string). The integer holds a
 * value 0 or 1. 1 indicates a ts (to remove ending backslashes) and 0 means a 
 * separator string.
 */

char *PreProcessString(char *s, int x) {
  char string[strlen(s) + 1];
  int counter = 0;
  int i = 0;
  while (i < strlen(s)) {
    // Check on first character.
    switch (s[i]) {
    case '\\':
      // If the first character is a backslash, check the second character.
      switch (s[i+1]) {
      case '\0':
	i++;
	break;
      case '\\':
	/*
	 * If the second character is a backslash check to see if the next
	 * would form a special character.
	 */
	switch (s[i+2]) {
	case '\0':
	  i++;
	  break;
	case '\\':
	  string[counter] = 0x5c;
	  counter++;
	  i += 2;
	  break;
	case 'n':
	  string[counter] = 0x0a;
	  counter++;
	  i += 3;
	  break;
	case 't':
	  string[counter] = 0x09;
	  counter++;
	  i += 3;
	  break;
	case 'v':
	  string[counter] = 0x0b;
	  counter++;
	  i += 3;
	  break;
	case 'b':
	  string[counter] = 0x08;
	  counter++;
	  i += 3;
	  break;
	case 'r':
	  string[counter] = 0x0d;
	  counter++;
	  i += 3;
	  break;
	case 'f':
	  string[counter] = 0x0c;
	  counter++;
	  i += 3;
	  break;
	case 'a':
	  string[counter] = 0x07;
	  counter++;
	  i += 3;
	  break;
	case '"':
	  string[counter] = 0x22;
	  counter++;
	  i += 3;
	  break;
	default:
	  i++;
	  break;
	}
	break;
      case 'n':
	string[counter] = 0x0a;
	counter++;
	i += 2;
	break;
      case 't':
	string[counter] = 0x09;
	counter++;
	i += 2;
	break;
      case 'v':
	string[counter] = 0x0b;
	counter++;
	i += 2;
	break;
      case 'b':
	string[counter] = 0x08;
	counter++;
	i += 2;
	break;
      case 'r':
	string[counter] = 0x0d;
	counter++;
	i += 2;
	break;
      case 'f':
	string[counter] = 0x0c;
	counter++;
	i += 2;
	break;
      case 'a':
	string[counter] = 0x07;
	counter++;
	i += 2;
	break;
      case '"':
	string[counter] = 0x22;
	counter++;
	i += 2;
	break;
      default:
	i++;
	break;
      }
      break;
    default:
      string[counter] = s[i];
      counter++;
      i++;
      break;
    }
  }
  string[counter] = '\0';
  /* Loop to remove any backslashes at the end of the processed string if this
   * is the toens tring (x = 1).
   */
  if (x == 1) {
    while (string[counter - 1] == '\\' && counter > 0) {
      counter--;
    }
  }
  string[counter] = '\0';
  /* 
   * Copying the string over to a character string of the proper size with a
   * nnull terminating character.
   */
  char *finalstring;
  finalstring = (char *) calloc((counter + 1), sizeof(char));
  strncpy(finalstring, string, counter + 1);
  return finalstring;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  // Error check for an inproper number of arguments.
  if (argc != 3) {
    printf("This program requires that you input only two string:\nA string of separators and a string to be tokenized.\n");
    printf("%d\n", argc);
    return 1;
  }
  char *ppts;
  char *ppseparators;
  // Preprocessing string for special characters and rogue backslashes.
  ppts = PreProcessString(argv[2], 1);
  ppseparators = PreProcessString(argv[1], 0);
  char ts[strlen(ppts) + 1];
  char separators[strlen(ppseparators) + 1];
  TokenizerT *temptoken;
  char *tempstring;
  int i;
  // Copies strings over along with the null character.
  strncpy(ts, ppts, strlen(ppts) + 1);
  strncpy(separators, ppseparators, strlen(ppseparators) + 1);
  free(ppts);
  free(ppseparators);
  i = 0;
  /*
   * Main loop of the program. This loop runs through ts until it finds a valid
   * non-separator character and starts the tokenizing process on that. Once it
   * completes that, it creates the token, prints it, and frees up any memory
   * used by tokenizing process.
   */
  while (i < strlen(ts) && ts[i] != '\0') {
    // Separating character. The loop keeps moving.
    if (strchr(separators, ts[i]) != NULL) {
      i++;
    }
    // Non-separating character. This starts the tokenizing process.
    else if (strchr(separators, ts[i]) == NULL) {
      char string[strlen(ts) - i + 1];
      /* A copy of the token string that hasn't been parsed already is passed to
       * the tokenizer before it is then made into a token, and printed out.
       * Then all dynamically allocated memory is freed.
       */
      strncpy(string, ts + i, (strlen(ts) - i));
      string[strlen(ts) - i] = '\0';
      temptoken = TKCreate(separators, string);
      tempstring = TKGetNextToken(temptoken);
      TKPrint(tempstring);
      i += temptoken->tklength;
      // Freeing dyamically used memory.
      free(tempstring);
      TKDestroy(temptoken);
    }
  }
  return 0;
}
