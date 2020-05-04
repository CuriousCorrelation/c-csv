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

Status
enumerate_csv_from_file(const char* file_path, const char* delimiters, const char is_headered, CSV* csv);
void free_csv(CSV* csv);

#endif // C_CSV_H
