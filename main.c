#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1024 * 3 // 3KB
int memory[MEMORY_SIZE];
int memory_pointer = 0;

int run_token(char *t) {
  if(strncasecmp(t, "fort", 4) == 0) {
    memory_pointer++;
  } else if (strncasecmp(t, "nite", 4) == 0) {
    memory_pointer--;
  } else if (strncasecmp(t, "girl", 4) == 0) {
    memory[memory_pointer]++;
  } else if (strncasecmp(t, "boy", 3) == 0) {
    memory[memory_pointer]--;
  } else if (strncasecmp(t, "battleroyale", 12) == 0) {
    printf("%c", memory[memory_pointer]);
  } else {
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  memset(memory, 0, sizeof(memory));

  FILE *input_file = fopen(argv[1], "r");

  if (!input_file) {
    printf("Error opening file %s\n", argv[1]);
    return 1;
  }

  int current_line = 0;
  char line[256];
  while (fgets(line, sizeof(line), input_file)) {
    current_line++;

    if (line[0] == '/') {
      continue;
    }

    // extract all tokens from line
    char *token = strtok(line, " ");
    while (token) {
      if(token[0] == '\n') {
        goto skip;
      }

      if (run_token(token) == -1) {
        int col = line - token;
        fprintf(stderr, "[ERROR] [L:%d C:%d] \"%s\" is not a valid token\n", current_line, col, token);
        exit(1);
      }

skip:
      // get next token
      token = strtok(NULL, " ");
    }
  }

  return 0;
}
