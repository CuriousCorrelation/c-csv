#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c-csv.h"

Status
enumerate_csv_from_file(const char* file_path, const char* delimiters, const char is_headered, CSV* csv)
{
  Status operation_status = CCSV_UNDEFINED;
  FILE*  file_handle;

  file_handle = fopen(file_path, "r");

  if (!file_handle)
    {
      return CCSV_FILE_NOT_FOUND;
    }

  char*   line        = NULL;
  size_t  line_length = 0;
  ssize_t result;

  int  total_rows    = 0;
  int  total_columns = 0;
  char ch;

  if ((result = getline(&line, &line_length, file_handle) != -1))
    {
      for (char* substring = strtok(line, delimiters); substring != NULL;
           substring       = strtok(NULL, delimiters))
        {
          if (substring)
            {
              ++total_columns;
            }
        }
    }

  while ((result = getline(&line, &line_length, file_handle) != -1))
    {
      int current_number_of_columns = 0;
      for (char* substring = strtok(line, delimiters); substring != NULL;
           substring       = strtok(NULL, delimiters))
        {
          if (substring)
            {
              ++current_number_of_columns;
            }
        }

      if (current_number_of_columns != total_columns)
        {
          if (line)
            free(line);
          fclose(file_handle);
          return CCSV_HEADER_TABLE_COLUMNS_MISMATCH;
        }
    }

  rewind(file_handle);

  while ((ch = fgetc(file_handle)) != EOF)
    {
      if (ch == '\n')
        {
          ++total_rows;
        }
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
          fclose(file_handle);
          free_csv(csv);
          if (line)
            free(line);
          return CCSV_MEMORY_ALLOCATION_FAILURE;
        }

      if ((result = getline(&line, &line_length, file_handle) != -1))
        {
          for (char* substring = strtok(line, delimiters); substring != NULL;
               substring       = strtok(NULL, delimiters))
            {
              if (substring)
                {
                  csv->header[header_index] = malloc(sizeof(char) * (strlen(substring) + 1));
                  if (!(csv->header[header_index]))
                    {
                      if (line)
                        free(line);
                      fclose(file_handle);
                      csv->number_of_rows = 0;
                      free_csv(csv);
                      return CCSV_MEMORY_ALLOCATION_FAILURE;
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
      if (line)
        free(line);
      fclose(file_handle);
      csv->number_of_rows = 0;
      free_csv(csv);
      return CCSV_MEMORY_ALLOCATION_FAILURE;
    }

  while ((result = getline(&line, &line_length, file_handle) != -1))
    {
      csv->table[table_row_index] = malloc(sizeof(Cell) * total_columns);

      if (!csv->table[table_row_index])
        {
          if (line)
            free(line);
          fclose(file_handle);
          csv->number_of_rows = table_row_index + 1;
          free_csv(csv);
          return CCSV_MEMORY_ALLOCATION_FAILURE;
        }

      table_column_index = 0;
      for (char* substring = strtok(line, delimiters); substring != NULL;
           substring       = strtok(NULL, delimiters))
        {
          if (table_column_index >= total_columns)
            {
              if (line)
                free(line);
              fclose(file_handle);
              csv->number_of_rows = table_row_index + 1;
              free_csv(csv);
              return CCSV_HEADER_TABLE_COLUMNS_MISMATCH;
            }

          if (substring)
            {
              csv->table[table_row_index][table_column_index] =
                  malloc(sizeof(char) * (strlen(substring) + 1));
              if (!csv->table[table_row_index][table_column_index])
                {
                  if (line)
                    free(line);
                  fclose(file_handle);
                  csv->number_of_rows = table_row_index + 1;
                  free_csv(csv);
                  return CCSV_MEMORY_ALLOCATION_FAILURE;
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

  operation_status = CCSV_SUCCESS;

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
