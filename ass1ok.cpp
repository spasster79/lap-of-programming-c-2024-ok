#include <iostream>

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();
    void insert(int value);
    void remove(int value);
    bool contains(int value) const;
    LinkedList& operator=(const LinkedList& other);
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list);
};

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::insert(int value) {
    if (contains(value)) return;
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void LinkedList::remove(int value) {
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data == value) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool LinkedList::contains(int value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this != &other) {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;

        current = other.head;
        Node* tail = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(current->data);
            if (tail == nullptr) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            current = current->next;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
    LinkedList::Node* current = list.head;
    while (current != nullptr) {
        out << current->data << " ";
        current = current->next;
    }
    return out;
}

class Set {
private:
    LinkedList elements;

public:
    Set() {}
    Set(const int arr[], size_t size);
    friend std::istream& operator>>(std::istream& in, Set& s);
    friend std::ostream& operator<<(std::ostream& out, const Set& s);
    Set operator+(const Set& other) const;
    Set operator*(const Set& other) const;
    Set& operator+=(int value);
    Set& operator=(const Set& other);
};

Set::Set(const int arr[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        elements.insert(arr[i]);
    }
}

std::istream& operator>>(std::istream& in, Set& s) {
    int value;
    while (in >> value) {
        s.elements.insert(value);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Set& s) {
    out << s.elements;
    return out;
}

Set Set::operator+(const Set& other) const {
    Set result = *this;
    LinkedList::Node* current = other.elements.head;
    while (current != nullptr) {
        result.elements.insert(current->data);
        current = current->next;
    }
    return result;
}

Set Set::operator*(const Set& other) const {
    Set result;
    LinkedList::Node* current = elements.head;
    while (current != nullptr) {
        if (other.elements.contains(current->data)) {
            result.elements.insert(current->data);
        }
        current = current->next;
    }
    return result;
}

Set& Set::operator+=(int value) {
    elements.insert(value);
    return *this;
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        elements = other.elements;
    }
    return *this;
}
