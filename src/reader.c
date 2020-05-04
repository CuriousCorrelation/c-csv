#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "reader.h"
#include "status.h"

Status enumerate_csv_from_file(const char* file_path, const char* delimiter, const char is_headered, CSV* csv)
{

  Status operation_status = UNDEFINED;
  FILE*  file_handle;

  file_handle = fopen(file_path, "r");

  if (!file_handle)
    {
      return FILE_NOT_FOUND;
    }

  char*   line        = NULL;
  size_t  line_length = 0;
  ssize_t result;

  int  total_rows    = 0;
  int  total_columns = 0;
  char ch;

  if ((result = getline(&line, &line_length, file_handle) != -1))
    {
      for (char* substring = strtok(line, delimiter); substring != NULL; substring = strtok(NULL, delimiter))
        {
          if (substring)
            {
              ++total_columns;
            }
        }
    }

  while ((ch = fgetc(file_handle)) != EOF)
    {
      if (ch == '\n')
        {
          ++total_rows;
        }
    }

  if (!is_headered)
    {
      total_rows += 1;
    }

  rewind(file_handle);

  csv->is_headered       = is_headered;
  csv->number_of_columns = total_columns;
  csv->number_of_rows    = total_rows;

  int header_index       = 0;
  int table_row_index    = 0;
  int table_column_index = 0;

  if (is_headered)
    {
      csv->header = malloc(sizeof(Cell) * total_columns);

      if (!csv->header)
        {
          return MEMORY_ALLOCATION_FAILURE;
        }

      if ((result = getline(&line, &line_length, file_handle) != -1))
        {
          for (char* substring = strtok(line, delimiter); substring != NULL;
               substring       = strtok(NULL, delimiter))
            {
              if (substring)
                {
                  csv->header[header_index] = malloc(sizeof(char) * (strlen(substring) + 1));
                  if (!(csv->header[header_index]))
                    {
                      return MEMORY_ALLOCATION_FAILURE;
                    }
                  else
                    {
                      strcpy(csv->header[header_index], substring);
                      ++header_index;
                    }
                }
            }
        }
    }

  csv->table = malloc(sizeof(Cell*) * total_rows);

  if (!csv->table)
    {
      return MEMORY_ALLOCATION_FAILURE;
    }

  while ((result = getline(&line, &line_length, file_handle) != -1))
    {

      csv->table[table_row_index] = malloc(sizeof(Cell) * total_columns);

      if (!csv->table[table_row_index])
        {
          return MEMORY_ALLOCATION_FAILURE;
        }

      table_column_index = 0;
      for (char* substring = strtok(line, delimiter); substring != NULL; substring = strtok(NULL, delimiter))
        {
          if (substring)
            {
              csv->table[table_row_index][table_column_index] =
                  malloc(sizeof(char) * (strlen(substring) + 1));
              if (!csv->table[table_row_index][table_column_index])
                {
                  return MEMORY_ALLOCATION_FAILURE;
                }
              else
                {
                  strcpy(csv->table[table_row_index][table_column_index], substring);
                  ++table_column_index;
                }
            }
        }
      ++table_row_index;
    }

  fclose(file_handle);

  if (line)
    free(line);

  operation_status = SUCCESS;

  return operation_status;
}

void free_csv(CSV* csv)
{
  if (csv->header)
    {
      for (int i = 0; i < csv->number_of_columns; ++i)
        {
          if (csv->header[i])
            {
              free(csv->header[i]);
            }
        }
      free(csv->header);
    }
  if (csv->table)
    {
      for (int i = 0; i < csv->number_of_rows; ++i)
        {
          if (csv->table[i])
            {
              for (int j = 0; j < csv->number_of_columns; ++j)
                {
                  if (csv->table[i][j])
                    {
                      free(csv->table[i][j]);
                    }
                }
              free(csv->table[i]);
            }
        }
      free(csv->table);
    }
}
