# c-csv

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Pipeline status](https://gitlab.com/CuriousCorrelation/c-csv/badges/master/pipeline.svg)](https://gitlab.com/CuriousCorrelation/c-csv/commits/master)

A simple csv parser written in C.

## Minimal setup

`c-csv.h` exports two functions

```c
Status enumerate_csv_from_file(const char* file_path,            // Path of the file.
                               const char* delimiters,           // Delimiter that seperates columns.
                               const char* substring_openblock,  // Open block to seperate.
                               const char* substring_closeblock, // Close block to seperate.
                               const char  is_headered,          // If the file is headered or not.
                               CSV*        csv                   // The CSV type storage variable.
);
```

```c
void free_csv(CSV* csv);
```

For any typical `.csv` file the following code will work without any tweaks.

```c
#include "c-csv.h"

const char* file_path = "example.csv";
CSV    csv_data;
Status read_status = CCSV_UNDEFINED;

read_status = enumerate_csv_from_file(file_path, ",", "\"", "\"", 1, &csv_data);

if(read_status != CCSV_SUCCESS)
    {
        // handle error
    }
else
    {
        // do stuff

        free(&csv_data);
    }
```

## Minimal complete usage
```c
#include <stdio.h>

#include "c-csv.h"

void test()
{

  const char* file_path = "../data/AAPL.csv";

  CSV    apple_historical;
  Status read_status = CCSV_UNDEFINED;

  read_status = enumerate_csv_from_file(file_path, ",", "\"", "\"", 1, &apple_historical);

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

## c-csv.h

```c
#ifndef C_CSV_H
#define C_CSV_H

typedef enum Status
{
  CCSV_UNDEFINED           = -1,
  CCSV_SUCCESS             = 00,
  CCSV_FILE_NOT_FOUND      = -2,
  CCSV_DIRECTORY_NOT_FOUND = -3,

  CCSV_DELIMITER_NOT_FOUND           = -10,
  CCSV_HEADER_TABLE_COLUMNS_MISMATCH = -11,
  CCSV_MEMORY_ALLOCATION_FAILURE     = -12

} Status;

typedef char* Cell;
typedef struct CSV
{
  char         is_headered;
  unsigned int number_of_rows;
  unsigned int number_of_columns;

  Cell*  header;
  Cell** table;

} CSV;

Status enumerate_csv_from_file(const char* file_path,            // Path of the file.
                               const char* delimiters,           // Delimiter that seperates columns.
                               const char* substring_openblock,  // Open block to seperate.
                               const char* substring_closeblock, // Close block to seperate.
                               const char  is_headered,          // If the file is headered or not.
                               CSV*        csv                   // The CSV type storage variable.
);

void free_csv(CSV* csv);

#endif // C_CSV_H
```

## Open and Close blocks

* Open block/Close block: `substring_openblock` and `substring_closeblock` are pair of string in which the delimiter will be ignores.

For example
```csv
year ,industry_name          ,grp                         ,unit
2011 ,"Agriculture, Forestry",Agro                        ,46134
2011 ,Mining                 ,f50-99                      ,12
2011 ,Construction           ,"Sales, government funding" ,1864
```

here if we set `","` as the `delimiter` **without** setting `substring_openblock` and `substring_closeblock` this is what we'll get:

```
year | industry_name | grp       | unit                | NULL
2011 | "Agriculture  | Forestry" | Agro                | 46134
2011 | Mining        | f50-99    | 12                  | NULL
2011 | Construction  | "Sales,   | government funding" | 1864
```

But if set `delimiter` to `","`, `substring_openblock` to `"\""` and `substring_closeblock` to `"\""`

we'll get this

```
year |industry_name           | grp                         | unit
2011 |"Agriculture, Forestry" | Agro                        | 46134
2011 |Mining                  | f50-99                      | 12
2011 |Construction            | "Sales, government funding" | 1864
```
