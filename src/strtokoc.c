#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strtokoc.h"

char* strtokoc(char* input, const char* delimiter, const char* openblock, const char* closeblock)
{
  static char* token         = NULL;
  char*        lead          = NULL;
  char*        block         = NULL;
  int          i_block       = 0;
  int          i_block_index = 0;

  if (input != NULL)
    {
      token = input;
      lead  = input;
    }
  else
    {
      lead = token;
      if (*token == '\0')
        {
          lead = NULL;
        }
    }

  while (*token != '\0')
    {
      if (i_block)
        {
          if (closeblock[i_block_index] == *token)
            {
              i_block = 0;
            }
          token++;
          continue;
        }
      if ((block = strchr(openblock, *token)) != NULL)
        {
          i_block       = 1;
          i_block_index = block - openblock;
          token++;
          continue;
        }
      if (strchr(delimiter, *token) != NULL)
        {
          *token = '\0';
          token++;
          break;
        }
      token++;
    }
  return lead;
}
