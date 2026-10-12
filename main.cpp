#include <iostream> 
#include <locale> 
#include <windows.h> 
#include "keeper.h" 
#include "Fishes.h" 
#include "Birds.h" 
#include "Cats.h" 

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    Keeper keeper;
    int choice;

    while (true) {
        cout << "\nМЕНЮ" << endl;
        cout << "1. Добавить животное" << endl;
        cout << "2. Удалить животное" << endl;
        cout << "3. Показать всех животных" << endl;
        cout << "4. Сохранить в файл" << endl;
        cout << "5. Загрузить из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт: ";
        cin >> choice;

        try {
            if (choice == 0) break;

            else if (choice == 1) {
                int subChoice;
                cout << "1. Рыба" << endl;
                cout << "2. Птица" << endl;
                cout << "3. Кошка" << endl;
                cout << "Выберите тип животного: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    Fish* f = new Fish();
                    f->input();
                    keeper.add(f);
                }
                else if (subChoice == 2) {
                    Bird* b = new Bird();
                    b->input();
                    keeper.add(b);
                }
                else if (subChoice == 3) {
                    Cat* c = new Cat();
                    c->input();
                    keeper.add(c);
                }
                else {
                    cout << "Неверный выбор!" << endl;
                }
            }

            else if (choice == 2) {
                if (keeper.getSize() == 0) {
                    cout << "Данных нет" << endl;
                }
                else {
                    cout << "\nСписок животных:" << endl;
                    keeper.printAll();

                    int idx;
                    cout << "\nВведите номер животного для удаления: ";
                    cin >> idx;

                    if (idx < 1 || idx > keeper.getSize()) {
                        cout << "Неверный номер!" << endl;
                    }
                    else {
                        keeper.remove(idx - 1);
                        cout << "Животное удалено" << endl;
                    }
                }
            }

            else if (choice == 3) {
                if (keeper.getSize() == 0) {
                    cout << "Данных о животных нет" << endl;
                }
                else {
                    keeper.printAll();
                }
            }

            else if (choice == 4) {
                keeper.saveAll("animals.txt");
                cout << "Данные сохранены в файл animals.txt" << endl;
            }

            else if (choice == 5) {
                keeper.loadAll("animals.txt");
                cout << "Данные загружены из файла animals.txt" << endl;
            }

            else {
                cout << "Неверный пункт меню!" << endl;;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }

    cout << "Программа завершена.";
    return 0;
}