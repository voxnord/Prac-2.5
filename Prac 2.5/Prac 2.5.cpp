#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct ExcellentStudent 
{
    char name[100];   // ФИО студента
    int groupNumber;  // Номер группы
};


vector<ExcellentStudent> readAndFindExcellentStudents(const string& filename) // Функция для чтения данных из текстового файла и получения списка отличников
{
    ifstream infile(filename);
    string line;
    vector<ExcellentStudent> excellentStudents;

    if (!infile) 
    {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return excellentStudents;
    }

    int maxScore = -1;

    string firstName, lastName, middleName;
    int groupNumber;
    int score;

    while (infile >> firstName >> lastName >> middleName >> groupNumber >> score)
    {
        string fullName = firstName + " " + lastName + " " + middleName;

        if (score > maxScore) 
        {
            // Нашли нового отличника, очищаем предыдущий список
            maxScore = score;
            excellentStudents.clear();
            ExcellentStudent student;
            strcpy_s(student.name, fullName.c_str());
            student.groupNumber = groupNumber;
            excellentStudents.push_back(student);
        }
        else if (score == maxScore) 
        {
            // Студент с таким же максимальным баллом, добавляем в список
            ExcellentStudent student;
            strcpy_s(student.name, fullName.c_str());
            student.groupNumber = groupNumber;
            excellentStudents.push_back(student);
        }
    }

    infile.close();
    return excellentStudents;
}

// Функция для записи списка отличников в бинарный файл
void writeBinaryFile(const string& filename, const vector<ExcellentStudent>& students) 
{
    ofstream outfile(filename, ios::binary);
    if (!outfile) 
    {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    for (const auto& student : students) 
    {
        outfile.write(reinterpret_cast<const char*>(&student), sizeof(ExcellentStudent));
    }

    outfile.close();
}

// Функция для чтения и вывода данных из бинарного файла
void readAndPrintBinaryFile(const string& filename) 
{
    ifstream infile(filename, ios::binary);
    if (!infile) 
    {
        cerr << "Не удалось открыть файл для чтения: " << filename << endl;
        return;
    }

    ExcellentStudent student;
    while (infile.read(reinterpret_cast<char*>(&student), sizeof(ExcellentStudent))) 
    {
        cout << "ФИО отличника: " << student.name << ", Номер группы: " << student.groupNumber << endl;
    }

    infile.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SetConsoleTitle(L"Семестр 2. Практическая работа 5");

    cout << "Вариант 10" << endl;

    string inputFilename = "C:\\Users\\knox\\source\\repos\\Prac 2.5\\src\\students.txt";
    string outputFilename = "C:\\Users\\knox\\source\\repos\\Prac 2.5\\src\\excellent_students.bin";
    
    vector<ExcellentStudent> excellentStudents = readAndFindExcellentStudents(inputFilename); // Шаг 1: Чтение данных и поиск отличников

    writeBinaryFile(outputFilename, excellentStudents); // Шаг 2: Запись отличников в бинарный файл

    readAndPrintBinaryFile(outputFilename); // Шаг 3: Чтение и вывод данных из бинарного файла

    return 0;
}