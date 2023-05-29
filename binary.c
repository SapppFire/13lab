#include <stdio.h>
#include <stdbool.h>

#include "cheking.h"

void write_trains_to_binary_file(Train *trains, int size, const char *filename) {
    FILE *file = fopen("C:\\Users\\SapppFire\\Desktop\\binary.txt", "wb"); //"wb"-создание бинарного файла с последующей записью данных
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    fwrite(&size, sizeof(int), 1, file);
    fwrite(trains, sizeof(Train), size, file);
    //Функции записи данных

    fclose(file);
}

bool read_train_from_binary_file(Train *train, const char *filename, int index) {
    FILE *file = fopen("C:\\Users\\SapppFire\\Desktop\\binary.txt", "rb"); //"rb"-формат чтения данных из бинарного.
    if (!file) {
        printf("Error opening file\n");
        return false;
    }

    int size;
    fread(&size, sizeof(int), 1, file);

    if (index < 0 || index >= size) {
        fclose(file);
        return false;
    }

    fseek(file, sizeof(int) + index * sizeof(Train), SEEK_SET);
    fread(train, sizeof(Train), 1, file);
    //Функции чтения данных из бинарного файла
    fclose(file);
    return true;
}