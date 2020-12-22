#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#define STANDARD_RANGE_EXCEPTION "Index out of range"

using namespace std;

template<class T>
class InternalListNode
{
public:
    InternalListNode(T o)
    {
        obj = o;
    }
    T *getObj()
    {
        return &obj;
    }

private:
    InternalListNode *prev() const
    {
        return _prev;
    }
    void setPrev(InternalListNode *prev)
    {
        _prev = prev;
    }
    InternalListNode *next() const
    {
        return _next;
    }
    void setNext(InternalListNode *next)
    {
        _next = next;
    }

    T obj;
    InternalListNode *_prev = nullptr, *_next = nullptr;

    template<class A>
    friend class LinkedList;
};

template<class T>
class LinkedList
{
public:
    /*
     * Appends data to the end of the list
     *
     * Equivalent to std::list::push_back
     */
    void append(const T &o)
    {
        auto node = new InternalListNode<T>(o);
        if(_firstNode == nullptr)
            _firstNode = node;
        if(_lastNode != nullptr)
        {
            node->setPrev(_lastNode);
            _lastNode->setNext(node);
        }
        _lastNode = node;
        _size++;
    }
    void append(const LinkedList &l)
    {
        auto firstListNode = l.firstNode();
        auto lastListNode = l.lastNode();
        if(_firstNode == nullptr)
            _firstNode = firstListNode;
        if(_lastNode != nullptr)
        {
            _lastNode->setNext(firstListNode);
            firstListNode->setPrev(_lastNode);
        }
        _lastNode = lastListNode;
        auto listCount = l.count();
        _size += listCount;
    }
    void insert(const int &i, const T o)
    {
        auto newNode = new InternalListNode<T>(o);
        InternalListNode<T> *nodeAtIndex;
        try {
            nodeAtIndex = findAt(i);
        }  catch (const std::out_of_range *e) {
            append(o);
            return;
        }
        auto previousNode = nodeAtIndex->prev();
        auto nextNode = nodeAtIndex->next();

        if(previousNode == nullptr)
        {
            _firstNode = newNode;
        }
        else
        {
            previousNode->setNext(newNode);
            newNode->setPrev(previousNode);
        }
        newNode->setNext(nodeAtIndex);
        nodeAtIndex->setPrev(newNode);
        if(nextNode == nullptr)
            _lastNode = nodeAtIndex;
        _size++;
    }

    void insert(const int &i, const LinkedList &list)
    {
        InternalListNode<T> *nodeAtIndex = nullptr;
        try {
            nodeAtIndex = findAt(i);
        }  catch (const std::out_of_range *e) {
            append(list);
            return;
        }
        auto firstListNode = list.firstNode();
        auto lastListNode = list.lastNode();
        auto previousNote = nodeAtIndex->prev();
        auto nextNode = nodeAtIndex->next();

        if(previousNote == nullptr)
        {
            _firstNode = firstListNode;
        }
        else
        {
            previousNote->setNext(firstListNode);
            firstListNode->setPrev(previousNote);
        }

        lastListNode->setNext(nodeAtIndex);
        nodeAtIndex->setPrev(lastListNode);

        if(nextNode == nullptr)
            _lastNode = nodeAtIndex;

        _size += list.count();
    }
    void removeAt(const int &i)
    {
        InternalListNode<T>* nodeAtIndex = nullptr;
        try {
            nodeAtIndex = findAt(i);
        }  catch (const std::out_of_range *e) {
            throw e;
        }
        // The previous and next nodes
        auto previousNoteAtIndex = nodeAtIndex->prev();
        auto nextNoteAtIndex = nodeAtIndex->next();
        if(previousNoteAtIndex != nullptr)
            previousNoteAtIndex->setNext(nextNoteAtIndex);
        else
            _firstNode = nextNoteAtIndex;
        if(nextNoteAtIndex != nullptr)
            nextNoteAtIndex->setPrev(previousNoteAtIndex);
        else
            _lastNode = previousNoteAtIndex;
        _size--;
        delete nodeAtIndex;
    }

    T& at(const int &i)
    {
        InternalListNode<T> *nodeAtIndex = nullptr;
        try {
            nodeAtIndex = findAt(i);
        }  catch (const std::out_of_range *e) {
            cout << e->what()  << " Index: " << i << " Size: " << _size << endl;
            throw e;
        }
        auto o = nodeAtIndex->getObj();
        return *o;
    }
    T value(const int i)
    {
        InternalListNode<T> *nodeAtIndex = nullptr;
        try {
            nodeAtIndex = findAt(i);
        }  catch (std::out_of_range *e) {
            cout << e->what()  << " Index: " << i << " Size: " << _size << endl;
            throw e;
        }
        auto o = nodeAtIndex->getObj();
        return o;
    }

    void replace(const int &i, T o)
    {
        auto node = new InternalListNode<T>(o);
        InternalListNode<T> *nodeAtIndex;
        try {
            nodeAtIndex = findAt(i);
        }  catch (const std::out_of_range e) {
            throw e;
        }
        auto previousNoteAtIndex = nodeAtIndex->prev();
        auto nextNoteAtIndex = nodeAtIndex->next();
        if(previousNoteAtIndex != nullptr)
        {
            previousNoteAtIndex->setNext(node);
            node->setPrev(previousNoteAtIndex);
        }
        else
        {
            _firstNode = node;
        }
        if(nextNoteAtIndex == nullptr)
        {
            _lastNode = node;
        }
        else
        {
            node->setNext(nextNoteAtIndex);
            nextNoteAtIndex->setPrev(node);
        }
        delete nodeAtIndex;
    }

    InternalListNode<T> *firstNode() const
    {
        return _firstNode;
    }
    void setFirstNode(InternalListNode<T> *firstNode)
    {
        _firstNode = firstNode;
    }

    int count() const
    {
        return (int) _size;
    }

    LinkedList<T> &operator<<(const T &o)
    {
        auto node = new InternalListNode<T>(o);
        if(_firstNode == nullptr)
            _firstNode = node;
        if(_lastNode != nullptr)
        {
            node->setPrev(_lastNode);
            _lastNode->setNext(node);        }
        _lastNode = node;
        _size++;

        return *this;
    }

    LinkedList<T> &operator<<(const LinkedList<T> &other)
    {
        auto listFirstNode = other.firstNode();
        auto listLastNode = other.lastNode();
        _lastNode->setNext(listFirstNode);
        listFirstNode->setPrev(_lastNode);
        _lastNode = other.lastNode();
        _size += other.count();

        if(_firstNode == nullptr)
            _firstNode = listFirstNode;
        if(_lastNode != nullptr)
        {
            listFirstNode->setPrev(_lastNode);
            _lastNode->setNext(listFirstNode);        }
        _lastNode = listLastNode;
        _size++;

        return *this;
    }

private:
    InternalListNode<T> *findAt(const int &i)
    {
        auto index = 0;
        auto nodeAtIndex = _firstNode;
        while (index != i)
        {
            nodeAtIndex = nodeAtIndex->next();
            index++;
        }
        if(nodeAtIndex == nullptr)
            throw new std::out_of_range(STANDARD_RANGE_EXCEPTION);
        return nodeAtIndex;
    }
    InternalListNode<T> *lastNode() const
    {
        return _lastNode;
    }
    void setLastNode(InternalListNode<T> *lastNode)
    {
        _lastNode = lastNode;
    }

    __SIZE_TYPE__ _size = 0;
    InternalListNode<T> *_firstNode = nullptr, *_lastNode = nullptr;

};

#endif // LINKEDLIST_H
