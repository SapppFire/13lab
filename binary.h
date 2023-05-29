
#ifndef STUDY_BINARY_H
#define STUDY_BINARY_H

#include "structures.h"
#include <stdbool.h>

bool read_train_from_binary_file(Train *train, const char *filename, int index);
void write_trains_to_binary_file(Train *trains, int size, const char *filename);

#endif //STUDY_BINARY_H