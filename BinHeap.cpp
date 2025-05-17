/*
Вариант 14
Запрещено исп библиотеки, кроме ф-ий ввода/вывода (print, operator >> и тп) и математических функций (log, sqrt и тп)
Написать программу для работы с биномиальными кучами.
Реализовать операции 
- вставки, 
- объединения, у
- даления вершины с минимальным ключом, 
- удаления произвольной вершины 
- и уменьшение ключа.
*/

#include <iostream>
#include <fstream>
#include <string>


int main()
{
    std::ifstream file("data.txt");

    if (!file) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string word;
    while (file >> word) { // Чтение по словам (до пробела или перевода строки)
        std::cout << word << std::endl;
    }

    return 0;
}

/*
struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
};

class BinomialHeap {
private:
    Node* head;

    Node* createNode(int key) {
        Node* node = new Node;
        node->key = key;
        node->degree = 0;
        node->parent = nullptr;
        node->child = nullptr;
        node->sibling = nullptr;
        return node;
    }

    void linkTrees(Node* y, Node* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    Node* mergeHeaps(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head = nullptr;
        Node* tail = nullptr;
        Node* x = h1;
        Node* y = h2;

        if (x->degree <= y->degree) {
            head = x;
            x = x->sibling;
        } else {
            head = y;
            y = y->sibling;
        }
        tail = head;

        while (x && y) {
            if (x->degree <= y->degree) {
                tail->sibling = x;
                x = x->sibling;
            } else {
                tail->sibling = y;
                y = y->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = x ? x : y;
        return head;
    }

    Node* unionHeaps(Node* h1, Node* h2) {
        Node* newHead = mergeHeaps(h1, h2);
        if (!newHead) return nullptr;

        Node* prev = nullptr;
        Node* x = newHead;
        Node* next = x->sibling;

        while (next) {
            if (x->degree != next->degree ||
                (next->sibling && next->sibling->degree == x->degree)) {
                prev = x;
                x = next;
            } else if (x->key <= next->key) {
                x->sibling = next->sibling;
                linkTrees(next, x);
            } else {
                if (!prev) {
                    newHead = next;
                } else {
                    prev->sibling = next;
                }
                linkTrees(x, next);
                x = next;
            }
            next = x->sibling;
        }

        return newHead;
    }

    Node* reverseList(Node* node) {
        Node* prev = nullptr;
        Node* next = nullptr;
        while (node) {
            next = node->sibling;
            node->sibling = prev;
            prev = node;
            node = next;
        }
        return prev;
    }

    Node* findMinNode() {
        if (!head) return nullptr;

        Node* minNode = head;
        Node* current = head->sibling;
        while (current) {
            if (current->key < minNode->key) {
                minNode = current;
            }
            current = current->sibling;
        }
        return minNode;
    }

    Node* findNode(Node* node, int key) {
        if (!node) return nullptr;

        if (node->key == key) return node;

        Node* found = findNode(node->child, key);
        if (found) return found;

        return findNode(node->sibling, key);
    }

    void decreaseKeyInternal(Node* node, int newKey) {
        if (newKey > node->key) {
            std::cout << "New key is greater than current key\n";
            return;
        }

        node->key = newKey;
        Node* parent = node->parent;

        while (parent && node->key < parent->key) {
            std::swap(node->key, parent->key);
            node = parent;
            parent = parent->parent;
        }
    }

public:
    BinomialHeap() : head(nullptr) {}

    void insert(int key) {
        Node* newNode = createNode(key);
        head = unionHeaps(head, newNode);
    }

    int extractMin() {
        if (!head) {
            std::cout << "Heap is empty\n";
            return std::numeric_limits<int>::min();
        }

        Node* minNode = findMinNode();
        Node* prev = nullptr;
        Node* current = head;

        while (current != minNode) {
            prev = current;
            current = current->sibling;
        }

        if (prev) {
            prev->sibling = current->sibling;
        } else {
            head = current->sibling;
        }

        Node* newHead = reverseList(minNode->child);
        head = unionHeaps(head, newHead);

        int minKey = minNode->key;
        delete minNode;
        return minKey;
    }

    void unionWith(BinomialHeap& other) {
        head = unionHeaps(head, other.head);
        other.head = nullptr;
    }

    bool decreaseKey(int oldKey, int newKey) {
        Node* node = findNode(head, oldKey);
        if (!node) {
            std::cout << "Key not found\n";
            return false;
        }
        decreaseKeyInternal(node, newKey);
        return true;
    }

    bool deleteKey(int key) {
        if (!decreaseKey(key, std::numeric_limits<int>::min())) {
            return false;
        }
        extractMin();
        return true;
    }

    void printHeap(Node* node, int level = 0) {
        if (!node) return;

        std::cout << "Level " << level << ": ";
        Node* current = node;
        while (current) {
            std::cout << current->key << " (deg " << current->degree << ") ";
            if (current->child) {
                std::cout << " -> ";
                printHeap(current->child, level + 1);
            }
            current = current->sibling;
            if (current) std::cout << " | ";
        }
        std::cout << std::endl;
    }

    void print() {
        printHeap(head);
    }
};

int main() {
    BinomialHeap heap1, heap2;

    // Пример использования
    heap1.insert(10);
    heap1.insert(20);
    heap1.insert(5);
    heap1.insert(15);

    std::cout << "Heap 1:\n";
    heap1.print();

    std::cout << "Extracted min: " << heap1.extractMin() << "\n";
    heap1.print();

    heap2.insert(3);
    heap2.insert(7);
    heap2.insert(12);

    std::cout << "Heap 2:\n";
    heap2.print();

    heap1.unionWith(heap2);
    std::cout << "After union:\n";
    heap1.print();

    heap1.decreaseKey(12, 2);
    std::cout << "After decreasing 12 to 2:\n";
    heap1.print();

    heap1.deleteKey(7);
    std::cout << "After deleting 7:\n";
    heap1.print();

    return 0;
}
Эта реализация включает все требуемые операции:

Вставка (insert)

Объединение (unionWith)

Удаление вершины с минимальным ключом (extractMin)

Удаление произвольной вершины (deleteKey)

Уменьшение ключа (decreaseKey)

Программа использует только базовые функции ввода/вывода (cout, операторы) и не использует никаких дополнительных библиотек, кроме <iostream> и <limits> (для numeric_limits). Математические функции не требуются для этой реализации.

*/


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////
Вот модифицированная версия программы, которая создает биномиальные кучи, читая данные из файлов:

cpp
#include <iostream>
#include <limits>

struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
};

class BinomialHeap {
private:
    Node* head;

    Node* createNode(int key) {
        Node* node = new Node;
        node->key = key;
        node->degree = 0;
        node->parent = nullptr;
        node->child = nullptr;
        node->sibling = nullptr;
        return node;
    }

    void linkTrees(Node* y, Node* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    Node* mergeHeaps(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head = nullptr;
        Node* tail = nullptr;
        Node* x = h1;
        Node* y = h2;

        if (x->degree <= y->degree) {
            head = x;
            x = x->sibling;
        } else {
            head = y;
            y = y->sibling;
        }
        tail = head;

        while (x && y) {
            if (x->degree <= y->degree) {
                tail->sibling = x;
                x = x->sibling;
            } else {
                tail->sibling = y;
                y = y->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = x ? x : y;
        return head;
    }

    Node* unionHeaps(Node* h1, Node* h2) {
        Node* newHead = mergeHeaps(h1, h2);
        if (!newHead) return nullptr;

        Node* prev = nullptr;
        Node* x = newHead;
        Node* next = x->sibling;

        while (next) {
            if (x->degree != next->degree ||
                (next->sibling && next->sibling->degree == x->degree)) {
                prev = x;
                x = next;
            } else if (x->key <= next->key) {
                x->sibling = next->sibling;
                linkTrees(next, x);
            } else {
                if (!prev) {
                    newHead = next;
                } else {
                    prev->sibling = next;
                }
                linkTrees(x, next);
                x = next;
            }
            next = x->sibling;
        }

        return newHead;
    }

    Node* reverseList(Node* node) {
        Node* prev = nullptr;
        Node* next = nullptr;
        while (node) {
            next = node->sibling;
            node->sibling = prev;
            prev = node;
            node = next;
        }
        return prev;
    }

    Node* findMinNode() {
        if (!head) return nullptr;

        Node* minNode = head;
        Node* current = head->sibling;
        while (current) {
            if (current->key < minNode->key) {
                minNode = current;
            }
            current = current->sibling;
        }
        return minNode;
    }

    Node* findNode(Node* node, int key) {
        if (!node) return nullptr;

        if (node->key == key) return node;

        Node* found = findNode(node->child, key);
        if (found) return found;

        return findNode(node->sibling, key);
    }

    void decreaseKeyInternal(Node* node, int newKey) {
        if (newKey > node->key) {
            std::cout << "New key is greater than current key\n";
            return;
        }

        node->key = newKey;
        Node* parent = node->parent;

        while (parent && node->key < parent->key) {
            std::swap(node->key, parent->key);
            node = parent;
            parent = parent->parent;
        }
    }

public:
    BinomialHeap() : head(nullptr) {}

    void insert(int key) {
        Node* newNode = createNode(key);
        head = unionHeaps(head, newNode);
    }

    int extractMin() {
        if (!head) {
            std::cout << "Heap is empty\n";
            return std::numeric_limits<int>::min();
        }

        Node* minNode = findMinNode();
        Node* prev = nullptr;
        Node* current = head;

        while (current != minNode) {
            prev = current;
            current = current->sibling;
        }

        if (prev) {
            prev->sibling = current->sibling;
        } else {
            head = current->sibling;
        }

        Node* newHead = reverseList(minNode->child);
        head = unionHeaps(head, newHead);

        int minKey = minNode->key;
        delete minNode;
        return minKey;
    }

    void unionWith(BinomialHeap& other) {
        head = unionHeaps(head, other.head);
        other.head = nullptr;
    }

    bool decreaseKey(int oldKey, int newKey) {
        Node* node = findNode(head, oldKey);
        if (!node) {
            std::cout << "Key not found\n";
            return false;
        }
        decreaseKeyInternal(node, newKey);
        return true;
    }

    bool deleteKey(int key) {
        if (!decreaseKey(key, std::numeric_limits<int>::min())) {
            return false;
        }
        extractMin();
        return true;
    }

    void printHeap(Node* node, int level = 0) {
        if (!node) return;

        std::cout << "Level " << level << ": ";
        Node* current = node;
        while (current) {
            std::cout << current->key << " (deg " << current->degree << ") ";
            if (current->child) {
                std::cout << " -> ";
                printHeap(current->child, level + 1);
            }
            current = current->sibling;
            if (current) std::cout << " | ";
        }
        std::cout << std::endl;
    }

    void print() {
        printHeap(head);
    }

    // Метод для чтения данных из файла
    void readFromFile(const char* filename) {
        FILE* file = fopen(filename, "r");
        if (!file) {
            std::cout << "Cannot open file " << filename << "\n";
            return;
        }

        int key;
        while (fscanf(file, "%d", &key) {
            insert(key);
            // Пропускаем пробелы и переводы строк
            while (fgetc(file) == ' ') {}
            if (feof(file)) break;
        }

        fclose(file);
    }
};

int main() {
    BinomialHeap heap1, heap2;

    // Чтение данных из файлов
    heap1.readFromFile("heap1.txt");
    heap2.readFromFile("heap2.txt");

    std::cout << "Heap 1 after reading from file:\n";
    heap1.print();

    std::cout << "Heap 2 after reading from file:\n";
    heap2.print();

    // Пример операций с кучами
    std::cout << "Extracted min from heap1: " << heap1.extractMin() << "\n";
    heap1.print();

    heap1.unionWith(heap2);
    std::cout << "After union:\n";
    heap1.print();

    return 0;
}
Формат входных файлов:
Файлы heap1.txt и heap2.txt должны содержать целые числа, разделенные пробелами или переводами строк. Например:

heap1.txt:

10 20 5 15
heap2.txt:

3 7 12
Изменения в программе:
Добавлен метод readFromFile для чтения данных из файла

Используются функции стандартного ввода-вывода C (FILE*, fscanf, fgetc)

Удалены все операции с кучами из main, кроме чтения из файлов и демонстрационных операций

Как компилировать и запускать:
Создайте файлы heap1.txt и heap2.txt с данными

Скомпилируйте программу: g++ binomial_heap.cpp -o binomial_heap

Запустите: ./binomial_heap

Программа прочитает данные из файлов, построит биномиальные кучи и продемонстрирует основные операции с ними.

*/
