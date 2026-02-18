// DoublyList.tpp
template <typename T>
DoublyList<T>::DoublyList()
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
    this->length  = 0;
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    this->length   = copyObj.length;
    Node* myCurr   = header;
    Node* copyCurr = copyObj.header->next;

    while (copyCurr != copyObj.trailer) {
        Node* n      = new Node(copyCurr->value);
        myCurr->next = n;
        n->prev      = myCurr;
        myCurr       = n;
        copyCurr     = copyCurr->next;
    }

    myCurr->next  = trailer;
    trailer->prev = myCurr;
}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }
    trailer->prev = header;
    this->length  = 0;
}

// helper: get pointer to node at position
template <typename T>
typename DoublyList<T>::Node* DoublyList<T>::getNode(int position) const {
    if (position < 0 || position >= this->length) {
        throw out_of_range("getNode: position out of bounds");
    }

    if (position <= this->length / 2) {
        Node* curr = header->next;
        for (int i = 0; i < position; i++) curr = curr->next;
        return curr;
    } else {
        Node* curr = trailer->prev;
        for (int i = this->length - 1; i > position; i--) curr = curr->prev;
        return curr;
    }
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    Node* last = trailer->prev;              // header if empty
    Node* n = new Node(elem, trailer, last); // next=trailer, prev=last
    last->next = n;
    trailer->prev = n;
    this->length++;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    return getNode(position)->value;
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}

template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) {
        throw out_of_range("insert: position out of bounds");
    }

    if (position == this->length) { // insert at end
        append(elem);
        return;
    }

    Node* after  = getNode(position); // node currently at position
    Node* before = after->prev;

    Node* n = new Node(elem, after, before);
    before->next = n;
    after->prev  = n;
    this->length++;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0
        && header->next  == trailer
        && trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    Node* victim = getNode(position);
    Node* before = victim->prev;
    Node* after  = victim->next;

    before->next = after;
    after->prev  = before;

    delete victim;
    this->length--;
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    Node* curr = header->next;
    while (curr != trailer) {
        if (curr->value == elem) return true;
        curr = curr->next;
    }
    return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    getNode(position)->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const DoublyList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    } else {
        typename DoublyList<T>::Node* curr = myObj.header->next;
        while (curr != myObj.trailer) {
            outStream << curr->value;
            if (curr->next != myObj.trailer) outStream << " <--> ";
            curr = curr->next;
        }
        outStream << endl;
    }
    return outStream;
}
