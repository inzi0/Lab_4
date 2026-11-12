// Вариант 24, Соваренко Максим Васильевич
/*
Конструктор копирования и оператор присваивания я написал сам,
хотя это необязательно, так как компилятор умеет копировать
string и double автоматически. Перемещение сделал через = default,
так как компилятор умеет делать его сам. Но из-за моего
конструктора копирования пришлось отдельно указать, что перемещение
тоже нужно
 */

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Credit {
private:
    string name; // Название кредита
    double amount; // Сумма кредита
    string currency; // Тип валюты
    double rate; // Процентная ставка

public:
    // Конструктор по умолчанию + параметрический конструктор
    Credit() {
        name = "Пусто";
        amount = 0;
        currency = "Никакой";
        rate = 0;
    };
    Credit(string n, double a, string c, double r)
    : name(n), amount(a), currency(c), rate(r) {};

    // Конструктор копирования
    Credit(const Credit& c) : name(c.name),
    amount(c.amount), currency(c.currency), rate(c.rate) {};
    // Конструктор перемещения
    Credit(Credit&& c) = default;

    // Оператор копирующего присваивания
    Credit& operator=(const Credit& c) {
        name = c.name;
        amount = c.amount;
        currency = c.currency;
        rate = c.rate;
        return *this;
    }
    // Оператор перемещающего присваивания
    Credit& operator=(Credit&& c) = default;

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& out, const Credit& c ) {
        out << c.name << " ";
        out << c.amount << " ";
        out << c.currency << " ";
        out << c.rate;
        return out;
    }
    // Перегрузка оператора сравнения
    friend bool operator<(const Credit& c1, const Credit& c2) {
        return c1.rate < c2.rate;
    }
};

int main() {
    list<Credit> credits;
    vector<Credit> copied_credits;

    // Открытие файла для чтения данных
    ifstream in("input.txt");
    if (!in.is_open()) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }

    string n,c;
    double a,r;

    while (in >> n >> a >> c >> r) {
        credits.push_back(Credit(n,a,c,r));
    }
    in.close();

    // Открытие файла для записи данных
    ofstream out("output.txt");
    if (!out.is_open()) {
        cout << "Ошибка открытия файла для вывода!" << endl;
        return 1;
    }

    out << "Неотсортированные кредиты:" << endl;
    for (const Credit& c0 : credits) {
        out << c0 << endl;
    }
    out << endl;

    // Копирование объектов из списка в вектор (копирующее присваивание)
    copied_credits.resize(credits.size());
    copy(credits.begin(), credits.end(), copied_credits.begin());

    // Сортировка списка кредитов по увеличению процентной ставки
    credits.sort();

    out << "Отсортированные кредиты:" << endl;
    for (const Credit& c0 : credits) {
        out << c0 << endl;
    }
    out << endl;

    out << "Скопированные кредиты:" << endl;
    for (const Credit& c0 : copied_credits) {
        out << c0 << endl;
    }
    out << endl;

    out.close();
    return 0;
}
