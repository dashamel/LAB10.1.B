#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // для підтримки кирилиці

using namespace std;

// Перелік спеціальностей
enum Speciality { ComputerScience, Informatics, MathAndEconomics, PhysicsAndInformatics, LaborEducation };
string specialityStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

// Об'єднання для третьої оцінки
union ExtraGrade
{
    int programmingGrade;
    int numericalMethodsGrade;
    int pedagogyGrade;
};

// Структура для представлення студента
struct Student {
    string surname;
    int course;
    Speciality speciality;
    int physicsGrade;
    int mathGrade;
    ExtraGrade extraGrade;
};

// Прототипи функцій
void Create(Student* s, const int N);
void Print(const Student* s, const int N);
int CountGoodGrades(const Student* s, const int N, int subjectIndex);
double CalculateExcellentPercent(const Student* s, const int N);

int main() {
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    Student* s = new Student[N];
    int menuItem;

    do {
        cout << "\n\nВиберіть дію:\n";
        cout << " [1] - введення даних студентів\n";
        cout << " [2] - вивід даних на екран\n";
        cout << " [3] - підрахунок кількості оцінок 'добре' з кожного предмету\n";
        cout << " [4] - обчислення процента студентів, які отримали '5' з фізики і математики\n";
        cout << " [0] - вихід\n";
        cout << "Введіть значення: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            cout << "Кількість оцінок 'добре' (4) з фізики: " << CountGoodGrades(s, N, 0) << endl;
            cout << "Кількість оцінок 'добре' (4) з математики: " << CountGoodGrades(s, N, 1) << endl;
            cout << "Кількість оцінок 'добре' (4) з програмування: " << CountGoodGrades(s, N, 2) << endl;
            break;
        case 4:
            cout << "Процент студентів, які отримали '5' і з фізики, і з математики: "
                << CalculateExcellentPercent(s, N) << "%" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Неправильний вибір" << endl;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N) {
    int speciality;
    for (int i = 0; i < N; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        cout << " Прізвище: ";
        cin >> s[i].surname;
        cout << " Курс: ";
        cin >> s[i].course;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> speciality;

        s[i].speciality = static_cast<Speciality>(speciality);
        cout << " Оцінка з фізики: ";
        cin >> s[i].physicsGrade;
        cout << " Оцінка з математики: ";
        cin >> s[i].mathGrade;

        // Введення третьої оцінки залежно від спеціальності
        switch (s[i].speciality) {
        case ComputerScience:
            cout << " Оцінка з програмування: ";
            cin >> s[i].extraGrade.programmingGrade;
            break;
        case Informatics:
            cout << " Оцінка з чисельних методів: ";
            cin >> s[i].extraGrade.numericalMethodsGrade;
            break;
        default:
            cout << " Оцінка з педагогіки: ";
            cin >> s[i].extraGrade.pedagogyGrade;
            break;
        }
    }
}

void Print(const Student* s, const int N) 
{
    cout << "===============================================================================================================================\n"; 
    cout << "| №  | Прізвище       | Курс | Спеціальність           |  Фізика | Математика | Програмування | Чисельні методи  | Педагогіка |\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(15) << left << s[i].surname << "| "
            << setw(4) << s[i].course << " | "
            << setw(24) << left << specialityStr[s[i].speciality] << "| "
            << setw(7) << s[i].physicsGrade << " | "
            << setw(10) << s[i].mathGrade << " | ";  

        // Вивід третьої оцінки залежно від спеціальності
        if (s[i].speciality == ComputerScience)
        {
            cout << setw(13) << s[i].extraGrade.programmingGrade << " | "
                << setw(16) << "-" << " | "
                << setw(10) << "-" << " |";
        }
        else
            if (s[i].speciality == Informatics) 
        {
            cout << setw(13) << "-" << " | "
                << setw(16) << s[i].extraGrade.numericalMethodsGrade << " | "
                << setw(10) << "-" << " |";
        }
        else
        {
            cout << setw(13) << "-" << " | "
                << setw(16) << "-" << " | "
                << setw(10) << s[i].extraGrade.pedagogyGrade << " |";       
        }
        cout << "\n";
    }
    cout << "===============================================================================================================================\n";
}

// Функція для підрахунку оцінок 'добре' (4)
int CountGoodGrades(const Student* s, const int N, int subjectIndex) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        int grade = 0;
        switch (subjectIndex) {
        case 0: grade = s[i].physicsGrade; break;
        case 1: grade = s[i].mathGrade; break;
        case 2:
            if (s[i].speciality == ComputerScience)
                grade = s[i].extraGrade.programmingGrade;
            else if (s[i].speciality == Informatics)
                grade = s[i].extraGrade.numericalMethodsGrade;
            else
                grade = s[i].extraGrade.pedagogyGrade;
            break;
        }
        if (grade == 4)
            count++;
    }
    return count;
}

// Функція для обчислення процента студентів, які отримали '5' з фізики і математики
double CalculateExcellentPercent(const Student* s, const int N)
{
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (s[i].physicsGrade == 5 && s[i].mathGrade == 5) count++;
    }
    return (N > 0) ? (static_cast<double>(count) / N) * 100 : 0;
}
