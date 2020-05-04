#ifndef CSV_H
#define CSV_H

typedef char* Cell;

typedef struct CSV
{
  char         is_headered;
  unsigned int number_of_rows;
  unsigned int number_of_columns;

  Cell*  header;
  Cell** table;

} CSV;

#endif // CSV_H
