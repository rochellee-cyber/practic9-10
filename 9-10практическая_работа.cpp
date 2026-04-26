#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int SIZE = 20;

enum type_movie { thriller, drama, melodrama, comedy };

const string pathWrite = "fileWrite.txt";
const string pathRead = "fileRead.txt";

const string pathBinWrite = "fileBinWrite.txt";
const string pathBinRead = "fileBinRead.txt";

// вложенная структура
struct person {
    char name[50];
};

struct movie {
    char name[50];
    person director;
    int year;
    int duration;
    int cost;
    float rating;
    person main_actor;
    type_movie genre;
};

movie* init() {
    movie* movies = new movie[SIZE];

    movies[0] = { "Project Hail Mary", {"Фил Лорд"}, 2026, 149, 108, 8.4, {"Райан Гослинг"}, drama };
    movies[1] = { "La La Land", {"Демьен Шазелл"}, 2016, 128, 30, 8.0, {"Райан Гослинг"}, melodrama };
    movies[2] = { "Blade Runner 2049", {"Дени Вильнёв"}, 2017, 164, 150, 8.0, {"Райан Гослинг"}, thriller };
    movies[3] = { "Drive", {"Николас Рефн"}, 2011, 100, 15, 7.3, {"Райан Гослинг"}, thriller };
    movies[4] = { "The Notebook", {"Ник Кассаветис"}, 2004, 124, 29, 8.3, {"Райан Гослинг"}, melodrama };
    movies[5] = { "The Nice Guys", {"Шейн Блэк"}, 2016, 116, 50, 7.3, {"Райан Гослинг"}, comedy };
    movies[6] = { "Barbie", {"Грета Гервиг"}, 2023, 114, 145, 6.6, {"Марго Робби"}, comedy };
    movies[7] = { "Monte Cristo", {"Матьё Делапорт"}, 2024, 178, 43, 8.2, {"Пьер Нинэ"}, thriller };
    movies[8] = { "Interstellar", {"Кристофер Нолан"}, 2014, 169, 165, 8.7, {"Макконахи"}, drama };
    movies[9] = { "The Gentlemen", {"Гай Ричи"}, 2019, 113, 22, 8.6, {"Макконахи"}, comedy };
    movies[10] = { "Shutter Island", {"Мартин Скорсезе"}, 2010, 138, 80, 8.5, {"Ди Каприо"}, thriller };
    movies[11] = { "Shawshank Redemption", {"Фрэнк Дарабонт"}, 1994, 142, 25, 9.1, {"Тим Роббинс"}, drama };
    movies[12] = { "Inside Out 2", {"Келси Манн"}, 2024, 96, 200, 7.7, {"Эми Полер"}, comedy };
    movies[13] = { "The Beekeeper", {"Дэвид Эйер"}, 2024, 105, 40, 7.2, {"Джейсон Стэйтем"}, thriller };
    movies[14] = { "Wrath of Man", {"Гай Ричи"}, 2021, 119, 40, 7.7, {"Джейсон Стэйтем"}, thriller };
    movies[15] = { "The Substance", {"Корали Фаржа"}, 2024, 141, 17, 6.3, {"Деми Мур"}, drama };
    movies[16] = { "Anora", {"Шон Бейкер"}, 2024, 139, 6, 6.4, {"Майки Мэдисон"}, drama };
    movies[17] = { "The Dark Knight", {"Кристофер Нолан"}, 2008, 152, 185, 8.5, {"Кристиан Бэйл"}, thriller };
    movies[18] = { "Intouchables", {"Оливье Накаш"}, 2011, 112, 9, 8.8, {"Франсуа Клюзе"}, drama };
    movies[19] = { "По щучьему велению", {"Александр Войтинский"}, 2023, 115, 660, 7.8, {"Никита Кологривый"}, comedy };

    return movies;
}

//Запись массива структур в файл
void writeToFile(movie* arr, int len) {
    ofstream f;
    f.open(pathWrite);
    if (f.is_open()) {
        for (int i = 0; i < len; i++)
        {
            f << arr[i].name << endl;
        }

    }
    f.close();
}

//Чтение массива структур из файла
void ReadToFile(movie* arr) {
    ifstream fin;
    int i = 0;
    fin.open(pathRead);
    if (fin.is_open()) {
        while (!fin.eof())
        {
            fin >> arr[i].name;
            cout << arr[i].name << endl;
            i++;
        }

    }
    fin.close();
}

void writeBinFile(movie* arr, int len) {
    ofstream out(pathBinWrite, ios::binary | ios::out);

    for (int i = 0; i < len; i++)
    {
        out.write((char*)&arr[i], sizeof(arr[i]));
    }

    out.close();

    cout << "Успешное чтение" << endl;
}

void binReadFile(movie* arr, int len) {
    fstream in(pathBinRead, ios::binary | ios::in);

    if (in.is_open()) {
        for (int i = 0; i < len; i++)
        {
            in.read((char*)&arr[i], sizeof(arr[i]));
        }
    }
    else
    {
        cout << "Файл не найден" << endl;
    }

    in.close();

    cout << "Успешное чтение" << endl;
    cout << arr[0].main_actor.name<< endl;
}

// вывод фильма
void printMovie(movie m) {
    cout << "Название: " << m.name << endl;
    cout << "Режиссер: " << m.director.name << endl;
    cout << "Год: " << m.year << endl;
    cout << "Длительность: " << m.duration << endl;
    cout << "Стоимость: " << m.cost << endl;
    cout << "Рейтинг: " << m.rating << endl;
    cout << "Актер: " << m.main_actor.name << endl;
    cout << "------------------------" << endl;
}

// оберточная функция
void printAll(movie* movies, int size) {
    for (int i = 0; i < size; i++) {
        printMovie(movies[i]);
    }
}

// фильтр Райан Гослинг
movie* filterGosling(movie* movies, int size, int& newSize) {
    movie* result = new movie[size];
    newSize = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(movies[i].main_actor.name, "Райан Гослинг") == 0) {
            result[newSize++] = movies[i];
        }
    }
    return result;
}

// сортировка пузырьком
void sortByName(movie* movies, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(movies[j].name, movies[j + 1].name) > 0) {
                swap(movies[j], movies[j + 1]);
            }
        }
    }
}

// изменение
void editMovie(movie& m) {
    strcpy(m.name, "Edited Film");
    m.year = 2025;
}

// топ 4 дорогих фильмов
void top4Expensive(movie* movies, int size) {
    movie temp[SIZE];
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (movies[i].year >= 2020) {
            temp[count++] = movies[i];
        }
    }

    // пузырёк по стоимости (убывание)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j].cost < temp[j + 1].cost) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }

    cout << "\nТОП-4 дорогих фильмов (2020+):\n";
    for (int i = 0; i < 4 && i < count; i++) {
        printMovie(temp[i]);
    }
}

// триллеры + фильмы с режиссером Дэвидом
movie* filterDavid(movie* movies, int size, int& newSize) {
    movie* result = new movie[size];
    newSize = 0;

    for (int i = 0; i < size; i++) {
        if (movies[i].genre == thriller &&
            strstr(movies[i].director.name, "Дэвид") != NULL) {
            result[newSize++] = movies[i];
        }
    }
    return result;
}

// сама программа

int main() {
    setlocale(LC_ALL, "Russian");

    movie* movies = init();

    cout << "ВСЕ ФИЛЬМЫ:\n";
    printAll(movies, SIZE);

    // фильмы с Гослингом
    int goslingSize;
    movie* gosling = filterGosling(movies, SIZE, goslingSize);

    sortByName(gosling, goslingSize);

    cout << "\nФИЛЬМЫ С ГОСЛИНГОМ:\n";
    printAll(gosling, goslingSize);

    // вывод одного фильма
    cout << "\nПЕРВЫЙ ФИЛЬМ:\n";
    printMovie(movies[0]);

    // изменение
    editMovie(movies[0]);

    // топ дорогих
    top4Expensive(movies, SIZE);

    // Дэвид
    int davidSize;
    movie* david = filterDavid(movies, SIZE, davidSize);

    cout << "\nТРИЛЛЕРЫ С РЕЖИССЕРОМ ДЭВИД:\n";
    printAll(david, davidSize);

    writeToFile(movies, SIZE);

    ReadToFile(movies);

    writeBinFile(movies, SIZE);

    binReadFile(movies, SIZE);

    delete[] movies;
    delete[] gosling;
    delete[] david;

    return 0;
}