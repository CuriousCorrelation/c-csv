#ifndef STATUS_H
#define STATUS_H

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

#endif // STATUS_H
