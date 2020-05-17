# c-csv

A simple csv parser written in C.

## Example

`c-csv` implements two major functions

1. `enumerate_csv_from_file` which takes in 4 parameters:
   1. Path to the `csv` file.
   2. Delimiter used to seperate cells/columns of the rows.
   3. If the file has a header. Set it to `1` if it does, `0` otherwise.
   4. An instance of `CSV` struct passed by reference.
   and returns `Status`.
2. `free_csv` which takes in one parameters, the `CSV` enumerated using `enumerate_csv_from_file`.

## Minimal usage

```c
#include <stdio.h>

#include "c-csv.h"

void test()
{

  const char* file_path = "../data/AAPL.csv";

  CSV    apple_historical;
  Status read_status = CCSV_UNDEFINED;

  read_status = enumerate_csv_from_file(file_path, ",", 1, &apple_historical);

  if (read_status != CCSV_SUCCESS)
    {
      printf("Error parsing csv file: %s\n", file_path);
      printf("Error code is: %d\n", read_status);
    }
  else
    {

      puts("Header\n");

      for (int i = 0; i < apple_historical.number_of_columns; ++i)
        {
          printf("%s |", apple_historical.header[i]);
        }

      for (int i = 0; i < apple_historical.number_of_rows; ++i)
        {
          for (int j = 0; j < apple_historical.number_of_columns; ++j)
            {
              printf("%s |", apple_historical.table[i][j]);
            }
        }

      puts("\n");

      free_csv(&apple_historical);
    }
}
```
