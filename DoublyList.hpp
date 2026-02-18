#ifndef DOUBLY_LIST_HPP
#define DOUBLY_LIST_HPP

#include "List.hpp"
#include <iostream>
using namespace std;

template <typename T>
class DoublyList : public List<T> {
    protected:
        struct Node {
            T value;
            Node* next;
            Node* prev;

            Node(T v = T(), Node* n = nullptr, Node* p = nullptr)
            : value(v), next(n), prev(p) { }
        };

        Node *header, *trailer;

    private:
        void copy(const DoublyList<T>&);

        // return the node at the given position (0-based)
        Node* getNode(int) const;

    public:
        DoublyList();
        DoublyList(const DoublyList<T>&);
        DoublyList<T>& operator=(const DoublyList<T>&);
        virtual ~DoublyList();

        virtual void append(const T&) override;
        virtual void clear() override;
        virtual T getElement(int) const override;
        virtual int getLength() const override;
        virtual void insert(int, const T&) override;
        virtual bool isEmpty() const override;
        virtual void remove(int) override;
        virtual void replace(int, const T&) override;

        virtual bool search(const T&) const;

        template <typename U>
        friend ostream& operator<<(ostream&, const DoublyList<U>&);
};

#include "DoublyList.tpp"
#endif
