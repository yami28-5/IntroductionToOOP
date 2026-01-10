#define _CRT_SECURE_NO_WARNINGS
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

bool is_hex_number(const char str[]);
int hex_to_dec(const char str[]);

bool isMACaddress(const char str[]);
bool isIPaddress(const char str[]);
bool isIPaddressTok(const char str[]);

//NULL Terminated Lines
//#define LINES_BASICS_1
//#define LINES_BASICS_2
//#define NUMERICS

void main()
{
    cout << '?' << "\t" << '?' << endl;
    cout << (int)'?' << "\t" << (int)'?' << endl;
    cout << 'A' << "\t" << 'a' << endl;
    cout << (int)'A' << "\t" << (int)'a' << endl;;
    cout << 'A' - 'a' << endl;
    cout << endl;
    setlocale(LC_ALL, "");

#ifdef LINES_BASICS_1
    //char str[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
//char str[] = { 'H', 'e', 'l', 'l', 'o', 0 };
    char str[] = "Hello";
    cout << str << endl;
    cout << sizeof(str) << endl;
#endif // LINES_BASICS_1
#ifdef LINES_BASICS_2
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
#endif // LINES_BASICS_2
    cout << isMACaddress("00-FF-CA-06-DE-D8") << endl;
    cout << isMACaddress("4c-77-cb-e4-e8-2c") << endl;
    cout << isIPaddress("192.-16.100.1") << endl;
    cout << isIPaddress("8.8.8.8") << endl;
    cout << isIPaddressTok("192.-16.100.1") << endl;
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
bool is_hex_number(const char str[])
{
    bool prefix = false;
    if (str[0] == '0' && str[1] == 'x')prefix = true;
    for (int i = prefix ? 2 : 0; str[i]; i++)
    {
        if (
            !(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] >= 'A' && str[i] <= 'F') &&
            !(str[i] >= 'a' && str[i] <= 'f')
            )return false;
    }
    return true;
}
int hex_to_dec(const char str[])
{
    int decimal = 0;
    int weight = 1;
    int length = StringLength(str);
    bool prefix = false;
    if (str[0] == '0' && str[1] == 'x')prefix = true;
    for (int i = length - 1; i >= (prefix ? 2 : 0); i--)
    {
        int digit;
        if (str[i] >= '0' && str[i] <= '9')digit = str[i] - 48;
        if (str[i] >= 'A' && str[i] <= 'F')digit = str[i] - 55;
        if (str[i] >= 'a' && str[i] <= 'f')digit = str[i] - 87;
        decimal += digit * weight;
        weight *= 16;
    }
    return decimal;
}

bool isMACaddress(const char str[])
{
    if (strlen(str) != 17)return false;
    for (int i = 0; str[i]; i++)
    {
        if ((i + 1) % 3 == 0 && (str[i] == '-' || str[i] == ':'))continue;
        else if ((i + 1) % 3 == 0)return false;
        if (!isxdigit(str[i]))return false;
        /*if (
            !(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] >= 'A' && str[i] <= 'F') &&
            !(str[i] >= 'a' && str[i] <= 'f')
            )return false;*/
    }
    return true;
}
bool isIPaddress(const char str[])
{
    if (strlen(str) < 7 || strlen(str) > 15)return false;
    int start = 0;
    //int stop = 0;
    int points_count = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '.')
        {
            if (i - start > 3)return false;
            char sz_byte[4] = {};
            unsigned int i_byte = 0;
            int k = 0;
            for (int j = start; j < i; j++)
            {
                sz_byte[k++] = str[j];
            }
            i_byte = to_int_number(sz_byte);
            if (i_byte > 255)return false;
            start = i + 1;
            points_count++;
        }
    }
    return points_count == 3 ? true : false;
}
bool isIPaddressTok(const char str[])
{
    NULL;
    int size = strlen(str);
    if (size < 7 || size > 15)return false;
    char* buffer = new char[size + 1] {};
    strcpy(buffer, str);
    int n = 0;
    unsigned int bytes[4] = {};
    for (char* pch = strtok(buffer, "."); pch; pch = strtok(NULL, "."))
        bytes[n++] = std::atoi(pch);
    if (n < 4)return false;
    for (int i = 0; i < n; i++)
        if (bytes[i] > 255)return false;
    return true;
}