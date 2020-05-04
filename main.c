#include <stdio.h>
#include <stdlib.h>

#include "c-csv.h"

int main()
{

  CSV         csv;
  const char* file_path        = "../database/EQ310119.CSV";
  Status      operation_status = UNDEFINED;
  const char* delimiters       = ",";

  operation_status = enumerate_csv_from_file(file_path, delimiters, 1, &csv);

  if (operation_status == SUCCESS)
    {

      printf("csv.number_of_columns: %d\n", csv.number_of_columns);
      printf("csv.number_of_rows: %d\n", csv.number_of_rows);
      printf("Operation status: %d\n", operation_status);

      for (int i = 0; i < csv.number_of_rows; ++i)
        {
          for (int j = 0; j < csv.number_of_columns; ++j)
            {
              printf("%s |", csv.table[i][j]);
            }
        }

      free_csv(&csv);
    }
}
