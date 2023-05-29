#ifndef STUDY_CHEKING_H
#define STUDY_CHEKING_H

#include "structures.h"

Train *read_trains_from_file(int *size, const char *filename);
void get_train_by_properties(const char *filename);
void get_trains_by_index(const char *filename);
void sort_trains(Train *trains, int size);
void print_trains(Train *trains, int size);

#endif //STUDY_CHEKING_H
