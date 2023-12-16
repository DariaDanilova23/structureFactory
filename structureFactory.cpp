#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <locale.h>
#include <ctype.h>

using namespace std;
const int len = 20;

struct data {
    int no_z, no_f; //No завода,No филиала
    char material[5]; //материальные ценностей на начало периода
    double get_m, lose_m; // получено мат ценностей на сумму, выбыло на сумму
    char fio[len]; //  Фамилия ответственного за материальные ценности
};

struct list {
    data inf;
    list* next, * prev; // указатель на следующий и предыдущий
};

list vvod()
{
    list z;
    char symbol;
    int fl;
    int c = 1;
    char t;
    do {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите номер завода" << endl;
        cin >> z.inf.no_z;
        if (!cin)
            cout << "НЕ корректный ввод:номер завода не может быть символом или буквой. Введите заново" << endl;
    } while (!cin);

    do {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите номер филиала" << endl;
        cin >> z.inf.no_f;
        if (!cin)
            cout << "НЕ корректный ввод:номер филиала не может быть символом или буквой. Введите заново" << endl;
    } while (!cin);

    cout << "Есть ли материальные ценности на начало периода Да/Нет" << endl;

    while ((symbol = _getch()) and (symbol != 13)) {

        switch (symbol) {
        case 75:
            c = 1;
            cout << "Да \r";
            break;
        case 77:
            c = 2;
            cout << "Нет \r";
            break;
        default:
            break;
        }
    }
    switch (c) {
    case 1:
        cout << "Да" << endl;
        strcpy(z.inf.material, "Да");
        break;
    case 2:
        cout << "Нет" << endl;
        strcpy(z.inf.material, "Нет");
        break;
    }
    if (c == 1) {
        do {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Сумма полученных материальных ценностей " << endl;
            cin >> z.inf.get_m;
            if (!cin)
                cout << "НЕ корректный ввод:Сумма не может быть символом или буквой. Введите заново" << endl;
        } while (!cin);

        do {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Выбыло материальных ценностей на сумму " << endl;
            cin >> z.inf.lose_m;
            if (!cin)
                cout << "НЕ корректный ввод:Сумма не может быть символом или буквой. Введите заново" << endl;
        } while (!cin);
    }
    else {
        z.inf.get_m = 0;
        z.inf.lose_m = 0;
    }
    //cin.clear();
    //cin.ignore(10,'\n');
    cout << "Фамилия ответственного за материальные ценности " << endl;
    cin.get();
    cin.getline(z.inf.fio, len);
    for (int t = 0; t <= len; t++)
        if (isdigit(z.inf.fio[t]) or (sizeof(z.inf.fio) > len)) {
            z.inf.fio[t] = '\0';
        }
    return z;
}

list* first(list*& beg)
{
    list NewElement = vvod();
    beg = new list;
    *beg = NewElement;
    beg->next = 0;
    beg->prev = 0;
    return beg;
}

void add(list* beg)
{
    list* temp = beg;
    while (temp->next != 0) {
        temp = temp->next;
    }
    list* newE = new list;
    *newE = vvod();
    newE->next = 0;
    temp->next = newE;
    newE->prev = temp;
}
list* showpage(list* temp)
{
    int i;
    system("cls");
    while (temp) {
        cout << "Номер завода             " << temp->inf.no_z << endl;
        cout << "Номер филиала      " << temp->inf.no_f << endl;
        cout << "Наличие материальных ценностей         " << temp->inf.material << endl;
        cout << "Сумма полученных материальных ценностей      " << temp->inf.get_m << endl;
        cout << "Выбыло материальных ценностей         " << temp->inf.lose_m << endl;
        cout << "Фамилия ответственного за материальные ценности                " << temp->inf.fio << endl;
        cout << endl;
        i++;
        temp = temp->next;
        if (i > 5) return temp;
    }
    return temp;
}

int watch(list* beg)
{
    list z;
    int fl = 0;
    int i = 1;
    list* start;
    list* temp = beg;
    char key;
    system("cls");
    while (1) {
        start = temp;
        temp = showpage(temp);
        cout << "Выход-esc" << endl;
        key = getch();
        if (key == 0) key = getch();
        switch (key) {
        case 27:
            return 1;
        case 13:
        case 80:
        case 81:
            if (!temp)
                temp = start;
            break;
        case 72:
        case 73:
            temp = start;
            for (i = 1; (i <= 5) && (temp); i++)
                temp = temp->prev;
            if (!temp)
                temp = beg;
            break;
        }
    }
}

list* del(list* beg)
{
    list* temp;
    if (!beg) {
        cout << "Пустой список" << endl;
        return 0;
    }
    temp = beg;
    beg = beg->next;
    cout << "Список удалён" << endl;
    delete beg;
    return beg;
}

void edit(list*& beg)
{
    int findNo;
    char symbol;
    int v;
    int c = 1;

    watch(beg);
    cout << "Введите номер завода запись о котором нужно отредактировать " << endl;
    cin >> findNo;
    system("cls");
    list* temp = beg;
    while (temp) {
        if (temp->inf.no_z == findNo) {
            list* k = temp;
            data s;
            cout << "Ввдите номер поля записи которое нужно отредактировать" << endl;
            cout << "1-Номер завода             " << endl;
            cout << "2-Номер филиала      " << endl;
            cout << "3-Наличие материальных ценностей         " << endl;
            cout << "4-Сумма полученных материальных ценностей      " << endl;
            cout << "5-Выбыло материальных ценностей         " << endl;
            cout << "6-Фамилия ответственного за материальные ценности                " << endl;
            cin >> v;
            switch (v) {
            case 1: {
                do {
                    cin.clear();
                    cin.ignore(10, '\n');
                    cout << "Введите номер завода" << endl;
                    cin >> s.no_z;
                    if (!cin)
                        cout << "НЕ корректный ввод:номер завода не может быть символом или буквой. Введите заново" << endl;
                } while (!cin);
                k->inf.no_z = s.no_z;
                break;
            }
            case 2: {
                do {
                    cin.clear();
                    cin.ignore(10, '\n');
                    cout << "Введите номер филиала" << endl;
                    cin >> s.no_f;
                    if (!cin)
                        cout << "НЕ корректный ввод:номер филиала не может быть символом или буквой. Введите заново" << endl;
                } while (!cin);

                k->inf.no_f = s.no_f;
                break;
            }
            case 3: {
                cout << "Есть ли материальные ценностей на начало периода да/нет" << endl;
                while ((symbol = _getch()) and (symbol != 13)) {

                    switch (symbol) {
                    case 75:
                        c = 1;
                        cout << "Да \r";
                        break;
                    case 77:
                        c = 2;
                        cout << "Нет \r";
                        break;
                    default:
                        break;
                    }
                }
                switch (c) {
                case 1:
                    cout << "Да" << endl;
                    strcpy(s.material, "Да");
                    break;
                case 2:
                    cout << "Нет" << endl;
                    strcpy(s.material, "Нет");
                    break;
                };
                for (int t; t <= 5; t++)
                    k->inf.material[t] = s.material[t];
                break;
            }
            case 4:
                if (strcmp(k->inf.material, "Нет") != 0) {
                    do {
                        cin.clear();
                        cin.ignore(10, '\n');
                        cout << "Сумма полученных материальных ценностей " << endl;
                        cin >> s.get_m;
                        if (!cin)
                            cout << "НЕ корректный ввод:Сумма не может быть символом или буквой. Введите заново" << endl;
                    } while (!cin);

                    k->inf.get_m = s.get_m;
                    break;
                }
                else {
                    cout << "Невозможно редактирование этого поля из-за отсутствия материальных ценностей" << endl;
                    break;
                }
            case 5:
                if (strcmp(k->inf.material, "Нет") != 0) {
                    cout << "Выбыло материальных ценностей на сумму " << endl;

                    do {
                        cin.clear();
                        cin.ignore(10, '\n');
                        cout << "Выбыло материальных ценностей на сумму " << endl;
                        cin >> s.lose_m;
                        if (!cin)
                            cout << "НЕ корректный ввод:Сумма не может быть символом или буквой. Введите заново" << endl;
                    } while (!cin);

                    k->inf.lose_m = s.lose_m;
                    break;
                }
                else {
                    cout << "Невозможно редактирование этого поля из-за отсутствия материальных ценностей" << endl;
                    cin.get();
                    break;
                }
            case 6: {
                cout << "Фамилия ответственного за материальные ценности " << endl;
                cin.get();
                cin.getline(s.fio, len);
                for (int l = 0; l <= len; l++)
                    if (isdigit(s.fio[l]) or (sizeof(s.fio) > len)) {
                        s.fio[l] = '\0';
                    }
                for (int p = 0; p <= len; p++)
                    k->inf.fio[p] = s.fio[p];
                break;
            }
            }
            k->next = temp->next;
            k->prev = temp->prev;
            system("cls");
            watch(beg);
            return;
        }
        else
            temp = temp->next;
    }
}

void del_elem(list*& beg)
{
    int findNo;
    system("cls");
    watch(beg);
    cout << "Введите номер завода запись о котором нужно удалить ";
    cin >> findNo;
    system("cls");
    list* temp = beg;
    list* tempF = beg;
    list* temp_pr, * temp_next;
    while (temp) {
        if (temp->inf.no_z == findNo) {
            if (temp == beg) {
                beg = beg->next;
                beg->prev = 0;
                delete (temp);
            }
            else if (temp->next == 0) {
                temp->prev->next = 0;
                delete (temp);
            }
            else {
                temp_pr = temp->prev;
                temp_next = temp->next;
                temp_pr->next = temp_next;
                temp_next->prev = temp_pr;
                delete (temp);
            };
            system("cls");
            watch(beg);
            return;
        }
        temp = temp->next;
    }
}

void find(list* beg)
{
    list* temp = beg;
    int n, fl1 = 0, fl2 = 0, fl3 = 0, fl4 = 0, fl5 = 0, fl6 = 0;
    int No1, No2;
    float sum, lost;
    char sname[len], mat[5];
    cout << "Введите номер поля по которому будет происходить поиск" << endl;
    cout << "--------------" << endl;
    cout << "1-Номер завода             " << endl;
    cout << "2-Номер филиала      " << endl;
    cout << "3-Наличие материальных ценностей         " << endl;
    cout << "4-Сумма полученных материальных ценностей      " << endl;
    cout << "5-Выбыло материальных ценностей         " << endl;
    cout << "6-Фамилия ответственного за материальные ценности                " << endl;
    cin >> n;
    system("cls");
    cout << "|Номер завода|Номер филиала|Наличие материальных ценностей|Получено материальных ценностей,руб|Выбыло материальных ценностей, руб|Фамилия ответственного|" << endl;
    cout << " ------------------------------------------------------------------------------------------------------------------------" << endl;
    switch (n) {

    case 1: {
        cout << "Номер завода запись о котором нужно найти ";
        cin >> No1;
        cin.get();
        while (temp->next != NULL) {
            if (temp->inf.no_z == No1) {
                cout << "|" << setw(11) << temp->inf.no_z << " ";
                cout << "|" << setw(12) << temp->inf.no_f << " ";
                cout << "|" << setw(29) << temp->inf.material << " ";
                cout << "|" << setw(34) << temp->inf.get_m << " ";
                cout << "|" << setw(33) << temp->inf.lose_m << " ";
                cout << "|" << setw(21) << temp->inf.fio << "\n";
                cout << setw(60) << "_________________________________________________________________________________________________________________________________________________________" << endl;
                fl1 = 1;
            }
            temp = temp->next;
        }
        if (fl1 == 0)
            cout << "Записи не найдены" << endl;
        break;
    }
    case 2: {
        cout << "Номер филиала запись о котором нужно найти";
        cin >> No2;
        cin.get();
        while (temp->next != NULL) {
            if (temp->inf.no_f == No2) {
                cout << "|" << setw(10) << temp->inf.no_z << " ";
                cout << "|" << setw(10) << temp->inf.no_f << " ";
                cout << "|" << setw(10) << temp->inf.material << " ";
                cout << "|" << setw(10) << temp->inf.get_m << " ";
                cout << "|" << setw(10) << temp->inf.lose_m << " ";
                cout << "|" << setw(10) << temp->inf.fio << "\n";
                fl2 = 1;
            }
            temp = temp->next;
        };
        if (fl2 == 0)
            cout << "Записи не найдены" << endl;
        break;
    }
    case 3: {
        cout << "Поиск по наличию материальных ценностей " << endl;
        cin.getline(mat, 5);
        cin.get();
        while (temp->next != NULL) {
            if (strcmp(temp->inf.material, mat) == 0) {
                cout << "|" << setw(10) << temp->inf.no_z << " ";
                cout << "|" << setw(10) << temp->inf.no_f << " ";
                cout << "|" << setw(10) << temp->inf.material << " ";
                cout << "|" << setw(10) << temp->inf.get_m << " ";
                cout << "|" << setw(10) << temp->inf.lose_m << " ";
                cout << "|" << setw(10) << temp->inf.fio << "\n";
                fl3 = 1;
            }
            temp = temp->next;
        };
        if (fl3 == 0)
            cout << "Записи не найдены" << endl;
        break;
    }
    case 4: {
        cout << "Поиск по сумме материальных ценностей " << endl;
        cin >> sum;
        cin.get();
        while (temp->next != NULL) {
            if (temp->inf.get_m == sum) {
                cout << "|" << setw(10) << temp->inf.no_z << " ";
                cout << "|" << setw(10) << temp->inf.no_f << " ";
                cout << "|" << setw(10) << temp->inf.material << " ";
                cout << "|" << setw(10) << temp->inf.get_m << " ";
                cout << "|" << setw(10) << temp->inf.lose_m << " ";
                cout << "|" << setw(10) << temp->inf.fio << "\n";
                fl4 = 1;
            }
            temp = temp->next;
        };
        if (fl4 == 0)
            cout << "Записи не найдены" << endl;
        break;
    }
    case 5: {
        cout << "Поиск по сумме выбывших материальных ценностей " << endl;
        cin >> lost;
        cin.get();
        while (temp->next != NULL) {
            if (temp->inf.lose_m == lost) {
                cout << "|" << setw(10) << temp->inf.no_z << " ";
                cout << "|" << setw(10) << temp->inf.no_f << " ";
                cout << "|" << setw(10) << temp->inf.material << " ";
                cout << "|" << setw(10) << temp->inf.get_m << " ";
                cout << "|" << setw(10) << temp->inf.lose_m << " ";
                cout << "|" << setw(10) << temp->inf.fio << "\n";
                fl5 = 1;
            }
            temp = temp->next;
        };
        if (fl5 == 0)
            cout << "Записи не найдены" << endl;
        break;
    }
    case 6: {
        cout << "Поиск по фамилии ответственного за материальные ценности " << endl;
        cin.get();
        cin.getline(sname, len);
        cin.get();
        while (temp->next != NULL) {
            if (strcmp(temp->inf.fio, sname) == 0) {
                cout << "|" << setw(10) << temp->inf.no_z << " ";
                cout << "|" << setw(10) << temp->inf.no_f << " ";
                cout << "|" << setw(10) << temp->inf.material << " ";
                cout << "|" << setw(10) << temp->inf.get_m << " ";
                cout << "|" << setw(10) << temp->inf.lose_m << " ";
                cout << "|" << setw(10) << temp->inf.fio << "\n";
                fl6 = 1;
            }
            temp = temp->next;
        };
        if (fl6 == 0)
            cout << "Записи не найдены" << endl;
        break;
    }
    }
}

void s_b_sort(list* beg)
{
    int key;
    cout << "----------------------------------------" << endl;
    cout << "1-Номер завода " << endl;
    cout << "2-Номер филиала " << endl;
    cout << "3-Сумма полученных материальных ценностей " << endl;
    cout << "4-Выбыло материальных ценностей " << endl;
    cout << "5-Фамилия ответственного за материальные ценности " << endl;
    cout << "----------------------------------------" << endl;
    cout << "Введите номер поля для сортировки - ";
    cin >> key;
    switch (key) { //проверка по ключу //поиск минимального элемента
    case 1: //по номеру завода
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.no_z < j->inf.no_z) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        };
        break;
    case 2: //по номеру филиала
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.no_f < j->inf.no_f) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    case 3: //по полученным мат ценностям
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.get_m < j->inf.get_m) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    case 4: // по выбывшим мат ценностям
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.lose_m < j->inf.lose_m) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    case 5: // по фамилии
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (strcmp(i->inf.fio, j->inf.fio) < 0) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    }
    watch(beg);
    cin.get();
}

void b_s_sort(list* beg)
{
    int key;
    cout << "----------------------------------------" << endl;
    cout << "1-Номер завода " << endl;
    cout << "2-Номер филиала " << endl;
    cout << "3-Сумма полученных материальных ценностей " << endl;
    cout << "4-Выбыло материальных ценностей " << endl;
    cout << "5-Фамилия ответственного за материальные ценности " << endl;
    cout << "----------------------------------------" << endl;
    cout << "Введите номер поля для сортировки - ";
    cin >> key;
    switch (key) { //проверка по ключу //поиск минимального элемента
    case 1: //по номеру завода
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.no_z > j->inf.no_z) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        };
        break;
    case 2: //по номеру филиала
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.no_f > j->inf.no_f) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    case 3: //по полученным мат ценностям
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.get_m > j->inf.get_m) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    case 4: // по выбывшим мат ценностям
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (i->inf.lose_m > j->inf.lose_m) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    case 5: // по фамилии
        for (list* i = beg; i; i = i->next) {
            for (list* j = beg; j; j = j->next) {
                if (strcmp(i->inf.fio, j->inf.fio) > 0) {
                    data r = i->inf;
                    i->inf = j->inf;
                    j->inf = r;
                }
            }
        }
        break;
    }
    watch(beg);
    cin.get();
}

int write_binFile(char* filenamebin, list*& beg)
{
    ofstream fout(filenamebin, ios::out | ios::binary);
    int Sizeoftable = sizeof(list);
    list* temp = beg;
    while (temp != 0) {
        fout.write((char*)&(temp->inf), Sizeoftable);
        temp = temp->next;
    }
    cout << "Информация записана в файл" << endl;
    fout.close();
    return 0;
}

int read_binFile(char* filenamebin, list*& beg)
{
    ifstream fin(filenamebin, ios::in | ios::binary);
    if (!fin) {
        cout << "Не могу открыть файл" << filenamebin << endl;
        return 1;
    }
    list d;
    int i;
    list* NewE = beg, * elem = 0;
    int SizeofTimetable = sizeof(list);
    beg = 0;
    while (1) {
        fin.read((char*)&d, SizeofTimetable);
        if (!fin.eof()) {
            if (!NewE) {
                NewE = new list;
                *NewE = d;
                NewE->next = 0;
                NewE->prev = 0;
                beg = NewE;
            }
            else {
                elem = new list;
                *elem = d;
                NewE->next = elem;
                elem->next = 0;
                elem->prev = NewE;
                NewE = NewE->next;
            }
        }
        else
            break;
    }
    fin.close();
    watch(beg);
}

int write_txtFile(char* filename, list*& beg)
{
    fstream fout(filename, ios::out);
    int Sizeoftable = sizeof(list);
    list* temp = beg;
    while (temp != 0) {
        fout << temp->inf.no_z << " ";
        fout << temp->inf.no_f << " ";
        fout << temp->inf.material << " ";
        fout << temp->inf.get_m << " ";
        fout << temp->inf.lose_m << " ";
        fout << temp->inf.fio << " \n";
        temp = temp->next;
    }
    fout.close();
    cout << "Информация записана в файл" << endl;
    return 0;
}

int read_txtFile(char* filename, list*& beg)
{
    ifstream fin(filename, ios::in);
    if (!fin) {
        cout << "Не могу открыть файл" << filename << endl;
        return 1;
    }
    list* temp = beg;
    data d;
    list* NewE = beg, * elem = 0;
    int SizeofTimetable = sizeof(list);
    beg = 0;
    while (1) {

        if (!NewE) {
            NewE = new list;

            fin >> d.no_z;
            fin >> d.no_f;
            fin >> d.material;
            fin >> d.get_m;
            fin >> d.lose_m;
            fin >> d.fio;
            NewE->inf = d;
            NewE->next = 0;
            NewE->prev = 0;
            beg = NewE;
        }
        else {
            elem = new list;

            fin >> d.no_z;
            if (fin.eof())
                break;
            fin >> d.no_f;
            fin >> d.material;
            fin >> d.get_m;
            fin >> d.lose_m;
            fin >> d.fio;
            elem->inf = d;
            NewE->next = elem;
            elem->next = 0;
            elem->prev = NewE;
            NewE = NewE->next;
        }
    }
    watch(beg);
    fin.close();
}

int vedomost(char* data, list*& beg)
{
    fstream fout(data, ios::out);
    int Sizeoftable = sizeof(list);
    list* temp = beg;
    fout << setw(141) << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    ;
    fout << "|Номер завода|Номер филиала|Наличие материальных ценностей|Получено материальных ценностей,руб|Выбыло материальных ценностей, руб|Фамилия ответственного|" << endl;
    fout << setw(141) << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while (temp != 0) {
        fout << "|" << setw(11) << temp->inf.no_z << " |";
        fout << setw(12) << temp->inf.no_f << " |";
        fout << setw(29) << temp->inf.material << " |";
        fout << setw(34) << temp->inf.get_m << " |";
        fout << setw(34) << temp->inf.lose_m << " |";
        fout << setw(21) << temp->inf.fio << " |\n";
        fout << setw(60) << "_________________________________________________________________________________________________________________________________________________________" << endl;
        temp = temp->next;
    }
    cout << "Ведомость записана в файл " << data << endl;
    return 0;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 70");
    list z;
    list* beg = 0;
    int c = 1;
    char filename[24]; // = "spisok.txt";
    char file[20];
    char filenamebin[24];
    char filebin[20];
    char data[] = "vedomost.txt";
    char symbol;

    while (1) {
        cout << "1-Организация \n";
        cout << "2-Просмотр\n";
        cout << "3-Удаление всего списка\n";
        cout << "4-Редактирование списка\n";
        cout << "5-Удаление элемента из списка\n";
        cout << "6-Сортировка по возрастанию\n";
        cout << "7-Сортировка по убыванию\n";
        cout << "8-Поиск\n";
        cout << "9-Запись в бинарный файл\n";
        cout << "10-Чтение из бинарного файла\n";
        cout << "11-Запись в текстовый файл\n";
        cout << "12-Чтение из текстового файла\n";
        cout << "13-Отчетная ведомость\n";
        cout << "14-Выход\n";
        cout << "--------------------------------------------\n" << endl;
        cout << "Если нужная функция нажать ENTER\n";

        // для уведомление на каком пункте меню стоим
        switch (c) {
        case 1:
            cout << "1-Организация \n";
            break;
        case 2:
            cout << "2-Просмотр\n";
            break;
        case 3:
            cout << "3-Удаление всего списка\n";
            break;
        case 4:
            cout << "4-Редактирование списка\n";
            break;
        case 5:
            cout << "5-Удаление элемента из списка\n";
            break;
        case 6:
            cout << "6-Сортировка по возрастанию\n";
            break;
        case 7:
            cout << "7-Сортировка по убыванию\n";
            break;
        case 8:
            cout << "8-Поиск\n";
            break;
        case 9:
            cout << "9-Запись в бинарный файл\n";
            break;
        case 10:
            cout << "10-Чтение из бинарного файла\n";
            break;
        case 11:
            cout << "11-Запись в текстовый файл\n";
            break;
        case 12:
            cout << "12-Чтение из текстового файла\n";
            break;
        case 13:
            cout << "13-Отчетная ведомость\n";
            break;
        case 14:
            cout << "14-Выход\n";
            break;
        default:
            break;
        }
        //-----------------

        while ((symbol = _getch()) and (symbol != 13)) {
            switch (symbol) {
            case 72:
                c = c - 1;
                break;
            case 80:
                c = c + 1;
                break;
            default:
                break;
            }
            system("cls");
            switch (c) {
            case 1:
                cout << "1-Организация \n";
                break;
            case 2:
                cout << "2-Просмотр\n";
                break;
            case 3:
                cout << "3-Удаление всего списка\n";
                break;
            case 4:
                cout << "4-Редактирование списка\n";
                break;
            case 5:
                cout << "5-Удаление элемента из списка\n";
                break;
            case 6:
                cout << "6-Сортировка по возрастанию\n";
                break;
            case 7:
                cout << "7-Сортировка по убыванию\n";
                break;
            case 8:
                cout << "8-Поиск\n";
                break;
            case 9:
                cout << "9-Запись в бинарный файл\n";
                break;
            case 10:
                cout << "10-Чтение из бинарного файла\n";
                break;
            case 11:
                cout << "11-Запись в текстовый файл\n";
                break;
            case 12:
                cout << "12-Чтение из текстового файла\n";
                break;
            case 13:
                cout << "13-Отчетная ведомость\n";
                break;
            case 14:
                cout << "14-Выход\n";
                break;
            default:
                break;
            }
        }
        switch (c) {
        case 1: {
            if (beg) {
                system("cls");
                add(beg);
            }
            else {
                system("cls");
                first(beg);
            }
            break;
        }
        case 2:
            system("cls");
            watch(beg);
            cout << "Нажмите любую клавишу" << endl;
            cin.get();
            break;
        case 3:
            system("cls");
            del(beg);
            beg = 0;
            cout << "Нажмите любую клавишу" << endl;
            cin.get();
            break;
        case 4:
            system("cls");
            edit(beg);
            cin.get();
            break;
        case 5:
            system("cls");
            del_elem(beg);
            cin.get();
            break;
        case 6:
            system("cls");
            s_b_sort(beg);
            cin.get();
            break;
        case 7:
            system("cls");
            b_s_sort(beg);
            cin.get();
            break;
        case 8:
            system("cls");
            find(beg);
            cin.get();
            break;
        case 9:
            system("cls");
            cout << "Введите имя бинарного файла ";
            cin.get(filebin, 20);
            snprintf(filenamebin, 24, "%s%s", filebin, ".txt");
            write_binFile(filenamebin, beg);
            cin.get();
            break;
        case 10:
            system("cls");
            cout << "Введите имя бинарного файла из которого нужно прочитать ";
            cin.get(filebin, 20);
            snprintf(filenamebin, 24, "%s%s", filebin, ".txt");
            read_binFile(filenamebin, beg);
            break;
        case 11:
            system("cls");
            cout << "Введите имя файла ";
            cin.get(file, 20);
            snprintf(filename, 24, "%s%s", file, ".txt");
            write_txtFile(filename, beg);
            cin.get();
            break;
        case 12:
            system("cls");
            cout << "Введите имя файла из которого нужно прочитать ";
            cin.get(file, 20);
            cin.get();
            snprintf(filename, 24, "%s%s", file, ".txt");
            read_txtFile(filename, beg);
            break;
        case 13:
            system("cls");
            vedomost(data, beg);
            break;
        case 14:
            return 0;
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
