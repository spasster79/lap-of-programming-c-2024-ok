#include <iostream>

// LinkedList class
class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* head;

public:
    // Default constructor
    LinkedList() : head(nullptr) {}

    // Copy constructor for deep copy
    LinkedList(const LinkedList& other) : head(nullptr) {
        Node* current = other.head;
        Node* tail = nullptr;
        while (current) {
            Node* newNode = new Node(current->data);
            if (!head) head = newNode;
            else tail->next = newNode;
            tail = newNode;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert an element into the list
    void insert(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Remove the first element with the given value
    void remove(int value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Check if the list contains a given value
    bool contains(int value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    // Overload the << operator to print the list
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& s) {
        Node* current = s.head;
        while (current) {
            out << current->data << " ";
            current = current->next;
        }
        return out;
    }

    // Friend class declaration to allow Set to access private members
    friend class Set;
};

// Set class
class Set {
private:
    LinkedList elements;

public:
    // Default constructor
    Set() {}

    // Constructor initializing from an array
    Set(const int arr[], size_t size) {
        for (size_t i = 0; i < size; ++i) {
            if (!elements.contains(arr[i])) {
                elements.insert(arr[i]);
            }
        }
    }

    // Copy constructor
    Set(const Set& other) : elements(other.elements) {}

    // Overload the >> operator to read data into the set
    friend std::istream& operator>>(std::istream& in, Set& s) {
        int value;
        while (in >> value) {
            if (!s.elements.contains(value)) {
                s.elements.insert(value);
            }
        }
        return in;
    }

    // Overload the << operator to print the set
    friend std::ostream& operator<<(std::ostream& out, const Set& s) {
        out << s.elements;
        return out;
    }

    // + operator to perform the union of two sets
    Set operator+(const Set& other) const {
        Set result = *this;
        LinkedList::Node* current = other.elements.head;
        while (current) {
            if (!result.elements.contains(current->data)) {
                result.elements.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // * operator to perform the intersection of two sets
    Set operator*(const Set& other) const {
        Set result;
        LinkedList::Node* current = elements.head;
        while (current) {
            if (other.elements.contains(current->data)) {
                result.elements.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // += operator to add an element to the set
    Set& operator+=(int value) {
        if (!elements.contains(value)) {
            elements.insert(value);
        }
        return *this;
    }

    // -= operator to remove an element from the set
    Set& operator-=(int value) {
        elements.remove(value);
        return *this;
    }

    // = operator to assign one set to another
    Set& operator=(const Set& other) {
        if (this != &other) {
            elements = other.elements; // Uses LinkedList's copy constructor
        }
        return *this;
    }
};

// Main function for testing
int main() {
    Set s1;
    int arr[] = {1, 2, 3, 2};
    Set s2(arr, 4);
    std::cout << "s2: " << s2 << std::endl; // Prints: 3 2 1

    s1 += 1;
    s1 += 2;
    std::cout << "s1: " << s1 << std::endl; // Prints: 2 1

    Set s3 = s1 + s2;
    std::cout << "s1 + s2: " << s3 << std::endl; // Prints: 3 2 1

    Set s4 = s1 * s2;
    std::cout << "s1 * s2: " << s4 << std::endl; // Prints: 2 1

    s3 -= 2;
    std::cout << "s3 after removing 2: " << s3 << std::endl; // Prints: 3 1

    return 0;
}
