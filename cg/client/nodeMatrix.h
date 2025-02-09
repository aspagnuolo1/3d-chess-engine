#include <iostream>
#include <memory>
#include "node.h"
#include <array>


class NodeMatrix {
public:
    // Costruttore
    NodeMatrix() {
        for (auto& row : matrix) {
            row.fill(nullptr); // Inizializza tutte le celle a nullptr
        }
    }

    // Distruttore
    ~NodeMatrix() = default;

    // Elimina il costruttore di copia
    NodeMatrix(const NodeMatrix& o) = delete;

    // Elimina il costruttore di spostamento
    NodeMatrix(NodeMatrix&& o) = delete;

    // Elimina l'operatore di assegnazione per copia
    NodeMatrix& operator=(const NodeMatrix& o) = delete;

    // Elimina l'operatore di assegnazione per spostamento
    NodeMatrix& operator=(NodeMatrix&& o) = delete;

    void setPiece(int row, int col, Node* piece) {
        if (isValidPosition(row, col)) {
            if (matrix[row][col] == nullptr) {
                matrix[row][col] = piece;
            }
            else {
                matrix[row][col] = piece;
            }
        }
        else {
            throw std::out_of_range("Posizione non valida nella matrice");
        }
    }

    // Rimuove tutti i pezzi (figli) da una cella specifica della matrice
    void clear(int row, int col) {
        if (isValidPosition(row, col)) {
            Node* cell = matrix[row][col];
            if (cell != nullptr) {
                // Rimuovi tutti i figli del nodo rappresentante la cella
                while (cell->get_number_of_chilren() > 0) {
                    Node* child = cell->get_children()[0]; // Ottieni il primo figlio
                    cell->remove_all_children(); // Rimuovi il figlio
                }
            }
        }
        else {
            throw std::out_of_range("Posizione non valida nella matrice");
        }
    }



    // Ottiene il pezzo in una cella specifica
    Node* getPiece(int row, int col) const {
        if (isValidPosition(row, col)) {
            return matrix[row][col];
        }
        else {
            throw std::out_of_range("Posizione non valida nella matrice");
        }
    }

    std::array<std::array<Node*, 8>, 8> getCurrentState() const {
        return matrix;
    }

    void clear_all() {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++)
            {
                clear(row, col);
            }
        }
    }

    void removePiece(int row, int col)
    {
        Node* piece = matrix[row][col];
        if (piece->get_number_of_chilren() > 0) {
            //piece->remove_child(piece->get_children()[0]);
            piece->remove_all_children();
        }
    }

    void setChildAt(int row, int col, Node* el) {
        if (isValidPosition(row, col) && matrix[row][col] != nullptr)
        {
            matrix[row][col]->add_child(el);
        }
    }



private:
    // Verifica se una posizione è valida
    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }



    // Matrice 8x8 di puntatori condivisi a T
    std::array<std::array<Node*, 8>, 8> matrix;

};
