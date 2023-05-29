#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cheking.h"
#include "binary.h"

Train *read_trains_from_file(int *size, const char *filename) {
    FILE *file = fopen("C:\\Users\\SapppFire\\Desktop\\structures.txt", "r"); //"r"-чтение обычного файла, внимательно используется указатель на fopren
    if (!file) {
        printf("Error opening file\n");
        return NULL;
    }

    fscanf(file, "%d", size);
    Train *trains = (Train *) malloc((*size) * sizeof(Train)); //Динамическое выделение памяти

    for (int i = 0; i < *size; i++) {
        fscanf(file, "%s %d %d:%d", trains[i].destination, &trains[i].number, &trains[i].departure_hour, &trains[i].departure_minute);//Чтение данных из обычного файла
    }

    fclose(file);//Закрытие потоков чтения/записи
    return trains;
}

void get_train_by_properties(const char *filename) {
    Train train;
    int size, found = 0;
    char dest[50];
    //int hour, minute; для поиска по времени

    printf("Enter destination: ");
    scanf("%s", dest);

/*
 * рабочая версия ввода поиска по ВРЕМЕНИ
    printf("Enter departure time (hh:mm): ");
    scanf("%d:%d", &hour, &minute);
*/
    FILE *file = fopen("C:\\Users\\SapppFire\\Desktop\\binary.txt", "rb"); //"rb"-формат чтения данных из бинарного.
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    fread(&size, sizeof(int), 1, file);

    for (int i=0; i<size && !found; i++) {
        fseek(file,sizeof(int)+i*sizeof(Train), SEEK_SET); //формат поиска по бинарному файлу, с передачей занимаемого объёма данных в памяти
        fread(&train,sizeof(Train),1,file);

        if (strcmp(train.destination,dest) == 0 /*|| (train.departure_hour==hour && train.departure_minute==minute)*/){
            //strcmp-Лексико-лингвистическая сортировка, закоменчен рабочий вариант сортировки по времени.
            printf("\nTrain #%d:\n Destination: %s\n Number of train: #%d\n Departure Time: %02d:%02d \n\n",i+1,
                   train.destination,
                   train.number,
                   train.departure_hour,
                   train.departure_minute
            );
            found=1;
        }

    }
    fclose(file);

    if(!found){
        fprintf(stderr,"Could not find any matching trains.\n");
    }
}

void get_trains_by_index(const char *filename){
    printf("Enter index of train to read from binary file: ");
    int index;
    scanf("%d", &index);
    Train train;
    if (read_train_from_binary_file(&train, "trains.bin", index)) {
        //Условие чтения данных из бинарного файла, внимательно, функция в условии булевая.
        printf("\nTrain #%d:\n Destination: %s\n Number of train: #%d\n Departure Time: %02d:%02d\n",index+1,
               train.destination,
               train.number,
               train.departure_hour,
               train.departure_minute
        );
    } else {
        fprintf(stderr,"Could not find any matching trains.\nYou entered wrong index!\n");//Вывод ошибки поиска
    }
}

void sort_trains(Train *trains, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            // Базовый BubbleSort
            if (strcmp(trains[i].destination, trains[j].destination) > 0) {
                Train temp = trains[i];
                trains[i] = trains[j];
                trains[j] = temp;
            }
        }
    }
}

void print_trains(Train *trains, int size) {
    int hour, minute;
    printf("\nRequired time (hh:mm): ");
    scanf("%d:%d", &hour, &minute);
    printf("Train departures after %02d:%02d:\n", hour, minute);
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (trains[i].departure_hour > hour || (trains[i].departure_hour == hour && trains[i].departure_minute >= minute)) {
            //Условие совпадения введёного времени с клавиатуры, с временем отправлений
            printf("%s, train #%d, departure time: %02d:%02d\n", trains[i].destination, trains[i].number, trains[i].departure_hour, trains[i].departure_minute);
            found = 1;
        }
    }
    if (!found) {
        printf("There are no departing trains after this time %02d:%02d\n", hour, minute);
    }
}