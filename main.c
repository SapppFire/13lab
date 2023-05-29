#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#include "structures.h"
#include "binary.h"
#include "cheking.h"



int main() {
    int size;
    Train *trains = read_trains_from_file(&size, "structures.txt");//Инициализация Структуры и последующее считывание данных из обычного файла.
    if (!trains) {
        return 1;
    }

    //Поочерёдный вызов функций в main
    sort_trains(trains, size);
    print_trains(trains, size);



    write_trains_to_binary_file(trains, size, "binary.txt");

    sleep(1);//Сделано для красоты

    get_train_by_properties("binary.txt");

    sleep(1);//Сделано для красоты

    get_trains_by_index("binary.txt");

    free(trains);

    return 0;
}