//
//  List.h
//  Projecto
//
//  Created by Miguel Enrique Guerra Topete on 01/04/17.
//  Copyright © 2017 Miguel Enrique Guerra Topete. All rights reserved.
//

#ifndef List_h
#define List_h

#include <stdio.h>
#include <iostream>

template <class T>
class Node
{
public:
    T value;
    Node* sig;
    Node* ant;
    
    Node();
};

template <class T>
class List
{
public:
    Node<T>* head;
    Node<T>* tail;
    
    List();
    
    int Length();
    
    void Add(T value);
    
    void AddAfter(T value, int index);
    
    T Get(int index);
    
    void RemoveAt(int index);
    
    void PrintAll(bool reverse = false);
};

using namespace std;

template <class T>
Node<T>::Node()
{
    sig = NULL;
    ant = NULL;
}

template <class T>
List<T>::List()
{
    head = NULL;
    tail = NULL;
}

template <class T>
int List<T>::Length()
{
    Node<T>* node = head;
    int cont = 0;
    while(node)
    {
        cont++;
        node = node->sig;
    }
    
    return cont;
}

template <class T>
void List<T>::Add(T value)
{
    Node<T>* node = new Node<T>();
    node->value = value;
    
    
    if(!tail)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->sig = node;
        node->ant = tail;
        tail = node;
    }
}

template <class T>
void List<T>::AddAfter(T value, int index)
{
    int length = Length();
    
    if(length <= index)
        return;
    
    if(length == index -1)
        Add(value);
    
    Node<T>* node = head;
    int cont = 0;
    
    while(cont < index)
    {
        cont++;
        node = node->sig;
    }
    
    Node<T>* n = new Node<T>();
    n->value = value;
    node->sig->ant = n;
    n->sig = node->sig;
    node->sig = n;
    n->ant = node;
}

template <class T>
T List<T>::Get(int index)
{
    int length = Length();
    
    if(length <= index)
        return NULL;
    
    Node<T>* node = head;
    int cont = 0;
    
    while(cont < index)
    {
        cont++;
        node = node->sig;
    }
    
    return node->value;
}

template <class T>
void List<T>::RemoveAt(int index)
{
    int length = Length();
    
    if(length <= index)
        return;
    
    if(index == 0)
    {
        Node<T>* node = head;
        head = head->sig;
        delete node;
        return;
    }
    
    Node<T>* node = head;
    for(int i = 0; i < index; node = node->sig, i++);
    
    if(index == length - 1)
    {
        node->ant->sig;
        delete node;
    }
    else
    {
        node->sig->ant = node->ant;
        node->ant->sig = node->sig;
        delete node;
    }
}

template <class T>
void List<T>::PrintAll(bool reverse)
{
    if(!reverse)
    {
        Node<T>* node = head;
        int i = 0;
        
        while(node)
        {
            cout << "[" << i++ << "]" << node->value << endl;
            node = node->sig;
        }
    }
    else
    {
        Node<T>* node = tail;
        int i = Length() - 1;
        
        while(node)
        {
            cout << "[" << i-- << "] = " << node->value << endl;
            node = node->ant;
        }
    }
}


#endif /* List_h */
