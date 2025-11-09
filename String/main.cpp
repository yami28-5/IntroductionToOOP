#include<Windows.h>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---\n"

int StringLength(const char str[]);
char* ToUpper(char str[]);
char* ToLower(char str[]);
void shrink(char str[]);
bool is_palindrome(const char str[]);
bool is_int_number(const char str[]);
int to_int_number(const char str[]);
bool is_bin_number(const char str[]);
int bin_to_dec(const char str[]);

void main()
{
    setlocale(LC_ALL, "");

    const int SIZE = 256;
    char str[SIZE];

    cout << "Введите строку: ";
    SetConsoleCP(1251);
    cin.getline(str, SIZE);
    SetConsoleCP(866);

    cout << delimiter << "Исходная строка: " << str << endl;
    cout << "Длина строки: " << StringLength(str) << endl;

    cout << "В верхнем регистре: " << ToUpper(str) << endl;
    cout << "В нижнем регистре: " << ToLower(str) << endl;

    shrink(str);
    cout << "Без лишних пробелов: " << str << endl;

    cout << "Палиндром: " << (is_palindrome(str) ? "да" : "нет") << endl;
    cout << "Является целым числом: " << (is_int_number(str) ? "да" : "нет") << endl;

    if (is_int_number(str)) {
        cout << "Числовое значение: " << to_int_number(str) << endl;
    }

    cout << "Является двоичным числом: " << (is_bin_number(str) ? "да" : "нет") << endl;

    if (is_bin_number(str)) {
        cout << "Десятичное значение: " << bin_to_dec(str) << endl;
    }
}

int StringLength(const char str[]) {
    int i = 0;
    for (; str[i]; i++);
    return i;
}

char* ToUpper(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
        else if (str[i] >= 'а' && str[i] <= 'я')
            str[i] -= 32;
        else if (str[i] == 'ё')
            str[i] = 'Ё';
    }
    return str;
}

char* ToLower(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        else if (str[i] >= 'А' && str[i] <= 'Я')
            str[i] += 32;
        else if (str[i] == 'Ё')
            str[i] = 'ё';
    }
    return str;
}

void shrink(char str[]) {
    int i = 0, j = 0;
    bool space_flag = false;

    while (str[i] == ' ') i++;

    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i++];
            space_flag = false;
        }
        else {
            if (!space_flag) {
                str[j++] = ' ';
                space_flag = true;
            }
            i++;
        }
    }

    if (j > 0 && str[j - 1] == ' ') {
        j--;
    }

    str[j] = '\0';
}

bool is_palindrome(const char str[]) {
    int len = StringLength(str);
    for (int i = 0; i < len / 2; i++) {
        char left = str[i];
        char right = str[len - 1 - i];

        if (left >= 'A' && left <= 'Z') left += 32;
        if (right >= 'A' && right <= 'Z') right += 32;

        if (left != right) {
            return false;
        }
    }
    return true;
}

bool is_int_number(const char str[]) {
    if (!str || !str[0]) return false;

    int i = 0;
    if (str[0] == '-' || str[0] == '+') i++;

    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

int to_int_number(const char str[]) {
    if (!is_int_number(str)) return 0;

    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }
    else if (str[0] == '+') {
        i++;
    }

    for (; str[i]; i++) {
        result = result * 10 + (str[i] - '0');
    }

    return result * sign;
}

bool is_bin_number(const char str[]) {
    if (!str || !str[0]) return false;

    for (int i = 0; str[i]; i++) {
        if (str[i] != '0' && str[i] != '1') return false;
    }
    return true;
}

int bin_to_dec(const char str[]) {
    if (!is_bin_number(str)) return 0;

    int result = 0;
    int len = StringLength(str);
    int power = 1;

    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == '1') {
            result += power;
        }
        power *= 2;
    }
    return result;
}