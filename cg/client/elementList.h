#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class ElementList {
public:
    // Costruttore di default
    ElementList() = default;

    // Distruttore di default
    ~ElementList() {
        for (auto element : m_elements) {
            delete element;
        }
    }

    // Elimina il costruttore di copia
    ElementList(const ElementList& other) = delete;

    // Elimina il costruttore di spostamento
    ElementList(ElementList&& other) = delete;

    // Elimina l'operatore di assegnazione per copia
    ElementList& operator=(const ElementList& other) = delete;

    // Elimina l'operatore di assegnazione per spostamento
    ElementList& operator=(ElementList&& other) = delete;

    // Aggiunge un elemento alla lista
    void addElement(T* element) {
        m_elements.push_back(element);
    }

    // Ottiene un elemento alla posizione specificata
    T* getElementAt(size_t index) {
        if (index < m_elements.size()) {
            return m_elements[index];
        }
        return nullptr; // Ritorna nullptr se l'indice non è valido
    }

    // Ottiene la dimensione della lista
    size_t size() const {
        return m_elements.size();
    }

private:
    std::vector<T*> m_elements; // Vettore di elementi
};