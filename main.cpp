#include <iostream>
using namespace std;

// Класс, представляющий узел списка
class Node {
public:
    int data;        // Данные, хранящиеся в узле
    Node* prev;     // Указатель на предыдущий узел
    Node* next;     // Указатель на следующий узел

    // Конструктор узла
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Класс, представляющий двусвязный список
class DoublyLinkedList {
private:
    Node* head;     // Указатель на первый узел списка
    Node* tail;     // Указатель на последний узел списка

public:
    // Конструктор списка
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Добавление элемента в конец списка
    void push_back(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        if (!head) {
            head = tail = newNode; // Если список пуст, новый узел становится головой и хвостом
        } else {
            tail->next = newNode; // Устанавливаем следующий узел для хвоста
            newNode->prev = tail; // Устанавливаем предыдущий узел для нового узла
            tail = newNode;       // Обновляем хвост
        }
    }

    // Добавление элемента в начало списка
    void push_front(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        if (!head) {
            head = tail = newNode; // Если список пуст, новый узел становится головой и хвостом
        } else {
            newNode->next = head;  // Устанавливаем следующий узел для нового узла
            head->prev = newNode;   // Устанавливаем предыдущий узел для головы
            head = newNode;         // Обновляем голову
        }
    }

    // Удаление последнего элемента
    void pop_back() {
        if (!tail) return; // Если список пуст, ничего не делаем
        Node* temp = tail; // Сохраняем указатель на хвост
        if (head == tail) {
            head = tail = nullptr; // Если в списке один элемент, удаляем его
        } else {
            tail = tail->prev;     // Обновляем хвост
            tail->next = nullptr;  // Убираем указатель на следующий узел
        }
        delete temp; // Освобождаем память
    }

    // Удаление первого элемента
    void pop_front() {
        if (!head) return; // Если список пуст, ничего не делаем
        Node* temp = head; // Сохраняем указатель на голову
        if (head == tail) {
            head = tail = nullptr; // Если в списке один элемент, удаляем его
        } else {
            head = head->next;     // Обновляем голову
            head->prev = nullptr;  // Убираем указатель на предыдущий узел
        }
        delete temp; // Освобождаем память
    }

    // Вставка элемента по значению на указанную позицию
    void insert(int value, int position) {
        Node* newNode = new Node(value); // Создаем новый узел
        if (position == 0) {
            push_front(value); // Если позиция 0, добавляем в начало
            return;
        }

        Node* current = head; // Начинаем с головы
        for (int i = 0; current != nullptr && i < position; i++) {
            current = current->next; // Перемещаемся к нужной позиции
        }

        if (current == nullptr) {
            push_back(value); // Если достигли конца списка, добавляем в конец
        } else {
            newNode->prev = current->prev; // Устанавливаем указатели для нового узла
            newNode->next = current;
            if (current->prev) {
                current->prev->next = newNode; // Обновляем указатель предыдущего узла
            }
            current->prev = newNode; // Устанавливаем новый узел как предыдущий для текущего
            if (current == head) {
                head = newNode; // Если вставляем в начало, обновляем голову
            }
        }
    }

    // Удаление элемента по значению
    void remove(int value) {
        Node* current = head; // Начинаем с головы
        while (current != nullptr) {
            if (current->data == value) { // Если нашли элемент
                if (current->prev) {
                    current->prev->next = current->next; // Обновляем указатель предыдущего узла
                } else {
                    head = current->next; // Удаляем голову
                }
                if (current->next) {
                    current->next->prev = current->prev; // Обновляем указатель следующего узла
                } else {
                    tail = current->prev; // Удаляем хвост
                }
                delete current; // Освобождаем память
                return;
            }
            current = current->next; // Перемещаемся к следующему узлу
        }
    }

    // Поиск элемента по значению
    bool search(int value) {
        Node* current = head; // Начинаем с головы
        while (current != nullptr) {
            if (current->data == value) { // Если нашли элемент
                return true; // Возвращаем true
            }
            current = current->next; // Перемещаемся к следующему узлу
        }
        return false; // Если не нашли, возвращаем false
    }

    // Функция для отображения списка
    void display() {
        Node* current = head; // Начинаем с головы
        while (current != nullptr) {
            cout << current->data << " "; // Выводим данные узла
            current = current->next; // Перемещаемся к следующему узлу
        }
        cout << endl; // Переход на новую строку
    }

    // Деструктор для освобождения памяти
    ~DoublyLinkedList() {
        while (head) {
            pop_front(); // Освобождаем память, удаляя все узлы
        }
    }
};

int main() {
    DoublyLinkedList list; // Создаем экземпляр двусвязного списка

    list.push_back(1); // Добавляем 1 в конец
    list.push_back(2); // Добавляем 2 в конец
    list.push_front(0); // Добавляем 0 в начало
    list.insert(1, 1); // Вставка 1 на позицию 1
    list.display(); // Ожидается: 0 1 1 2

    list.pop_back(); // Удаление последнего элемента
    list.display(); // Ожидается: 0 1 1

    list.pop_front(); // Удаление первого элемента
    list.display(); // Ожидается: 1 1

    list.remove(1); // Удаление элемента со значением 1
    list.display(); // Ожидается: (пусто)

    return 0; // Завершение программы
}
