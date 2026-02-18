template <typename T>
typename DoublyList<T>::Node* DoublyList<T>::getNode(int position) const {
    // assumes caller already validated bounds: 0 <= position < length
    if (position < this->length / 2) {
        Node* curr = header->next;
        for (int i = 0; i < position; ++i) {
            curr = curr->next;
        }
        return curr;
    } else {
        Node* curr = trailer->prev;
        for (int i = this->length - 1; i > position; --i) {
            curr = curr->prev;
        }
        return curr;
    }
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    Node* last = trailer->prev;                 // could be header if empty
    Node* n    = new Node(elem, trailer, last); // next=trailer, prev=last

    last->next    = n;
    trailer->prev = n;
    this->length++;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        cerr << "getElement: error, position out of bounds\n";
        return T();
    }
    Node* curr = getNode(position);
    return curr->value;
}

template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) {
        cerr << "insert: error, position out of bounds\n";
        return;
    }

    if (position == this->length) { // insert at end
        append(elem);
        return;
    }

    Node* curr = getNode(position);   // node currently at 'position'
    Node* prev = curr->prev;

    Node* n = new Node(elem, curr, prev);
    prev->next = n;
    curr->prev = n;
    this->length++;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    if (position < 0 || position >= this->length) {
        cerr << "remove: error, position out of bounds\n";
        return;
    }

    Node* curr = getNode(position);
    Node* prev = curr->prev;
    Node* next = curr->next;

    prev->next = next;
    next->prev = prev;

    delete curr;
    this->length--;
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    Node* curr = header->next;
    while (curr != trailer) {
        if (curr->value == elem) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        cerr << "replace: error, position out of bounds\n";
        return;
    }

    Node* curr = getNode(position);
    curr->value = elem;
}
