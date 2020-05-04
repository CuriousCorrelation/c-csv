#ifndef READER_H
#define READER_H

#include "csv.h"
#include "status.h"

Status
     enumerate_csv_from_file(const char* file_path, const char* delimiter, const char is_headered, CSV* csv);
void free_csv(CSV* csv);

#endif // READER_H
