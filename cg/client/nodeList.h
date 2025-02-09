#pragma once

#include <iostream>
#include <memory>

template <typename T>
class NodeList {
public:
    // Costruttore
    NodeList(T* camera = nullptr, NodeList<T>* next = nullptr) 
        : m_camera{camera}, m_next{next} {}

    // Distruttore
    ~NodeList() {
        delete m_camera;
    }

    // Elimina il costruttore di copia
    NodeList(const NodeList& o) = delete;

    // Elimina il costruttore di spostamento
    NodeList(NodeList&& o) = delete;

    // Elimina l'operatore di assegnazione per copia
    NodeList& operator=(const NodeList& o) = delete;

    // Elimina l'operatore di assegnazione per spostamento
    NodeList& operator=(NodeList&& o) = delete;

    // Getter per il puntatore al prossimo nodo
    NodeList<T>* getNext() {
        return m_next;
    }

    // Getter per il puntatore alla camera
    T* getCamera() {
        return m_camera;
    }

    // Setter per il puntatore al prossimo nodo
    void setNext(NodeList<T>* next) {
        m_next = next;
    }


private:
    T* m_camera;           // Puntatore alla camera
    NodeList* m_next;      // Puntatore al prossimo nodo
};