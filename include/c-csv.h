#ifndef C_CSV_H
#define C_CSV_H

typedef enum Status
{
  UNDEFINED           = -1,
  SUCCESS             = 00,
  FILE_NOT_FOUND      = -2,
  DIRECTORY_NOT_FOUND = -3,

  DELIMITER_NOT_FOUND           = -10,
  HEADER_TABLE_COLUMNS_MISMATCH = -11,
  MEMORY_ALLOCATION_FAILURE     = -12

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

Status
enumerate_csv_from_file(const char* file_path, const char* delimiters, const char is_headered, CSV* csv);
void free_csv(CSV* csv);

#endif // C_CSV_H
