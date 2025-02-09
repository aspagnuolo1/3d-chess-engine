/**
 * @file		main.cpp
 * @brief	Client application (that uses the graphics engine) for a Chess 3D application
 *
 * @author	Alessandro Spagnuolo, Dominik Panzarella, Mattia Mancino
 */



//////////////
// #INCLUDE //ß
//////////////

   // Library header:
   #include "engine.h"
   #include "nodeList.h"
   #include "nodeMatrix.h"
   #include "elementList.h"
   #include <glm/glm.hpp>
   #include <glm/gtc/matrix_transform.hpp>
   #include <stack>
   #include <tuple>
    #include <algorithm>

   // C/C++:
   #include <iostream>
   #include <chrono>
   #include <limits.h>
   #include <cstring>
   #include <filesystem>


Node* root;
SpotLight* spotLight;
Mesh* cube1;

PerspectiveCamera* dynamic_camera;
PerspectiveCamera* positional_camera;
PerspectiveCamera* positional_camera2;
PerspectiveCamera* positional_camera3;
PerspectiveCamera* positional_camera4;
PerspectiveCamera* positional_camera5;

//Current Camera
PerspectiveCamera* current_camera;
ElementList<PerspectiveCamera*> camera_list;

NodeMatrix chessboardNodeMatrix;

Eng::Base& eng = Eng::Base::getInstance();
glm::mat4 perspective;

glm::mat4 chessboardMatrix;


bool moving = false;
int selectorRow = 0; // Riga iniziale
int selectorCol = 0; // Colonna iniziale
unsigned int width = 512;
unsigned int height = 512;
float near = 0.01f;
float far = 250.f;
float fov = 70.f;

// Camera 1: Vista frontale in alto (camera principale) OK
glm::mat4 camera1Coordinate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 13.0f, 25.0f));

// Camera 2: Vista obliqua a sinistra
glm::mat4 camera2Coordinate = glm::translate(glm::mat4(1.f), glm::vec3(-10.0f, 3.0f, 10.0f)) *
                              glm::rotate(glm::mat4(1.f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

// Camera 3: Vista obliqua a destra
glm::mat4 camera3Coordinate = glm::translate(glm::mat4(1.f), glm::vec3(10.0f, 3.0f, 10.0f)) *
                              glm::rotate(glm::mat4(1.f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

// Camera 4: Vista dall'alto inclinata verso il basso (retro)
glm::mat4 camera4Coordinate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 20.0f, 15.0f)) *
                              glm::rotate(glm::mat4(1.f), glm::radians(45.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

// Camera 5: Vista dall'alto inclinata verso il basso (fronte)
glm::mat4 camera5Coordinate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 20.0f, -15.0f)) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
                              glm::rotate(glm::mat4(1.f), glm::radians(45.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

// Camera 6: Vista dall'alto perfettamente verticale OK
glm::mat4 camera6Coordinate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 30.0f, 0.0f)) *
                              glm::rotate(glm::mat4(1.f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


Node* selector;

// Dynamic camera parameters
float camera_speed = 0.5f;
float camera_rotation = 1.0f;

float lightX = 10.0f;
float lightY = -2.5f;
float lightZ = -45.0f;
float angleY = 0.0f;

bool isWireframeEnable = false;
bool showFPS = false;


// Variabili globali per l'animazione
float timeCounter = 0.0f;    // Contatore del tempo
float translationSpeed = 1.0f; // Velocità del movimento
float translationAmplitude = 0.008f;

struct PieceState{
   Node* piece;
   int row;
   int col;
};

void initializeChessboard(const glm::mat4& chessboardMatrixWorld) ;

std::vector< PieceState> piece_states;


std::vector<PieceState> captured_pieces; // Keep track of captured pieces
std::vector<PieceState> initialPosition;
std::vector<PieceState> resetPosition;
std::stack<std::pair<std::vector<PieceState>, std::vector<PieceState>>> undo_stack;


void saveState() {
    std::vector<PieceState> currentPieceStates;
    std::vector<PieceState> currentCapturedPieces;

    for (const auto& initial_pos : initialPosition) {
        currentPieceStates.push_back({initial_pos.piece, initial_pos.row, initial_pos.col});
         std::cout << initial_pos.piece->get_object_name()
              << " at (" << initial_pos.row << ", " << initial_pos.col << ")" << std::endl;
    }

   // Salva i pezzi catturati
   for (auto& captured : captured_pieces) {
        currentCapturedPieces.push_back(captured);
   }

   // Aggiungi lo stato allo stack di undo
   undo_stack.push({currentPieceStates, currentCapturedPieces});

    // Pulisci le liste temporanee
   currentPieceStates.clear();
   currentCapturedPieces.clear();

   std::cout << "State saved. Current undo stack size: " << undo_stack.size() << std::endl;

}

std::stack<std::pair<std::vector<PieceState>, std::vector<PieceState>>> redo_stack;

void undo() {
    if (undo_stack.empty()) {
        std::cout << "No state to undo." << std::endl;
        return;
    }

    // Save the current state to the redo stack
    auto current_state = std::make_pair(initialPosition, captured_pieces);
    redo_stack.push(current_state);

    // Retrieve the previous state from the undo stack
    auto previous_state = undo_stack.top();
    undo_stack.pop();

    // Clear the chessboard
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNodeMatrix.removePiece(i, j);
        }
    }

    // Restore captured pieces
    captured_pieces = previous_state.second;

    // Restore the chessboard pieces
    for (const auto& piece_state : previous_state.first) {
        auto piece = piece_state.piece;

        // Check if the piece was captured
        bool is_captured = std::any_of(
            captured_pieces.begin(), captured_pieces.end(),
            [&piece](const PieceState& captured) {
                return captured.piece == piece;
            });

        if (is_captured) {
            continue; // Skip captured pieces
        }

        // Restore the piece on the chessboard
        //piece->set_matrix(glm::mat4(1.0f));
        chessboardNodeMatrix.getPiece(piece_state.row, piece_state.col)->add_child(piece);
        root->remove_child(piece);

        selectorRow = piece_state.row;
        selectorCol = piece_state.col;
        std::cout << "Restored piece: " << piece->get_object_name()
                  << " at (" << piece_state.row << ", " << piece_state.col << ")" << std::endl;

        // Update the initial position
        for (auto& initial_pos : initialPosition) {
            if (initial_pos.piece == piece) {
                initial_pos.row = piece_state.row;
                initial_pos.col = piece_state.col;
                break;
            }
        }
    }

    // Update selector position
    selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() *
                         glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));

    std::cout << "Undo completed. Captured pieces count: " << captured_pieces.size() << std::endl;
}

void redo() {
    if (redo_stack.empty()) {
        std::cout << "No state to redo." << std::endl;
        return;
    }

    // Save the current state to the undo stack
    auto current_state = std::make_pair(initialPosition, captured_pieces);
    undo_stack.push(current_state);

    // Retrieve the next state from the redo stack
    auto next_state = redo_stack.top();
    redo_stack.pop();

    // Clear the chessboard
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNodeMatrix.removePiece(i, j);
        }
    }

    // Restore captured pieces
    captured_pieces = next_state.second;

    // Restore the chessboard pieces
    for (const auto& piece_state : next_state.first) {
        auto piece = piece_state.piece;

        // Check if the piece was captured
        bool is_captured = std::any_of(
            captured_pieces.begin(), captured_pieces.end(),
            [&piece](const PieceState& captured) {
                return captured.piece == piece;
            });

        if (is_captured) {
            continue; // Skip captured pieces
        }

        // Restore the piece on the chessboard
        //piece->set_matrix(glm::mat4(1.0f));
        chessboardNodeMatrix.getPiece(piece_state.row, piece_state.col)->add_child(piece);
        root->remove_child(piece);

        selectorRow = piece_state.row;
        selectorCol = piece_state.col;
        std::cout << "Redone piece: " << piece->get_object_name()
                  << " to (" << piece_state.row << ", " << piece_state.col << ")" << std::endl;

        // Update the initial position
        for (auto& initial_pos : initialPosition) {
            if (initial_pos.piece == piece) {
                initial_pos.row = piece_state.row;
                initial_pos.col = piece_state.col;
                break;
            }
        }
    }

    // Update selector position
    selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() *
                         glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));

    std::cout << "Redo completed. Captured pieces count: " << captured_pieces.size() << std::endl;
}


void reset() {
    // Clear captured pieces
    captured_pieces.clear();

    // Remove all pieces from the chessboard
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboardNodeMatrix.removePiece(i, j);
        }
    }

    // Prepare the reset state
    std::vector<PieceState> resetState;
    for (const auto& initial_pos : resetPosition) {
        auto piece = initial_pos.piece;

        // Reset piece transformation
        //piece->set_matrix(glm::mat4(1.0f));

        // Place piece back on the chessboard
        chessboardNodeMatrix.getPiece(initial_pos.row, initial_pos.col)->add_child(piece);

        // Remove piece from the root node
        root->remove_child(piece);

        resetState.push_back({piece, initial_pos.row, initial_pos.col});
        selectorRow = initial_pos.row;
        selectorCol = initial_pos.col;

        std::cout << "Reset piece: " << piece->get_object_name()
                  << " to (" << initial_pos.row << ", " << initial_pos.col << ")" << std::endl;
    }

    // Clear undo stack and push the reset state
    while (!undo_stack.empty()) {
        undo_stack.pop();
    }
    undo_stack.push({resetState, {}}); // Push reset state with no captured pieces

    while (!redo_stack.empty())
       redo_stack.pop();

    // Update selector position
    selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() *
                         glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));

    std::cout << "Reset completed. Undo stack updated with reset state." << std::endl;
}




void displayCallback()
{
   // Calcola il delta time (tempo trascorso tra i frame)
   static auto lastTime = std::chrono::high_resolution_clock::now();
   auto currentTime = std::chrono::high_resolution_clock::now();
   float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
   lastTime = currentTime;

   // Incrementa il contatore del tempo
   timeCounter += deltaTime * translationSpeed;

   // Calcola la traslazione Y usando una sinusoide per oscillare su e giù
   float translationY = translationAmplitude * sin(timeCounter);

   // Matrice di rotazione
   glm::mat4 translationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0.0f, translationY, 0.0f));

   // Combina la matrice attuale del selector con la rotazione animata
   glm::mat4 updatedMatrix = selector->get_matrix(); // Prende la matrice attuale
   updatedMatrix = glm::rotate(updatedMatrix, glm::radians(5.0f), glm::vec3(0.0f, translationY, 0.0f));

   // Imposta la matrice aggiornata
   selector->set_matrix(updatedMatrix);

   // Renderizza la scena
   eng.renderScene();
}

void reshapeCallback(int width, int height)
{
   current_camera->update_window_size(width, height);
}


void specialCallback(int key, int mouseX, int mouseY)
{
   const float rotation_speed = 1.0f; // Velocità di rotazione in gradi
   glm::mat4 camera_matrix = dynamic_camera->get_final_matrix();

   // TODO: Work in progress rotazioni camera dinamica

   switch (key)
   {
   case GLUT_KEY_UP: // Ruota intorno all'asse X locale (Right)
   {
      if (current_camera->get_object_name() == "Main Camera") {
         glm::vec3 right = glm::normalize(glm::vec3(camera_matrix[0])); // Normalizza l'asse X
         camera_matrix = glm::rotate(camera_matrix, glm::radians(rotation_speed), right);
      } else{
         moving = true;
         if(selectorRow + 1 < 8){
            Node* piece;
            if(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_number_of_chilren()==1)
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[0];
            else
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[1];

            //piece->set_matrix(chessboardNodeMatrix.getPiece(selectorRow +1, selectorCol)->get_matrix());
            chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->remove_child(piece);
            chessboardNodeMatrix.getPiece(++selectorRow, selectorCol)->add_child(piece);
            selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));
         }
      }
      break;
   }

   case GLUT_KEY_DOWN: // Ruota intorno all'asse X locale inverso
   {
      if (current_camera->get_object_name() == "Main Camera") {
         glm::vec3 right = glm::normalize(glm::vec3(camera_matrix[0]));
         camera_matrix = glm::rotate(camera_matrix, glm::radians(-rotation_speed), right);
      } else{
         moving = true;
         if(selectorRow - 1 >= 0){
            Node* piece;
            if(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_number_of_chilren()==1)
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[0];
            else
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[1];

            //piece->set_matrix(chessboardNodeMatrix.getPiece(selectorRow-1, selectorCol)->get_matrix());
            chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->remove_child(piece);
            chessboardNodeMatrix.getPiece(--selectorRow, selectorCol)->add_child(piece);
            selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));
         }
      }
      break;
   }

   case GLUT_KEY_LEFT: // Ruota intorno all'asse Y locale (Up)
   {
      if (current_camera->get_object_name() == "Main Camera") {
         glm::vec3 up = glm::normalize(glm::vec3(camera_matrix[1])); // Normalizza l'asse Y
         camera_matrix = glm::rotate(camera_matrix, glm::radians(rotation_speed), up);
      } else{
         moving = true;
         if(selectorCol - 1 >= 0){
            Node* piece;
            if(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_number_of_chilren()==1)
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[0];
            else
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[1];

            //piece->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol-1)->get_matrix());
            chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->remove_child(piece);
            chessboardNodeMatrix.getPiece(selectorRow, --selectorCol)->add_child(piece);
            selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));
         }
      }
      break;
   }

   case GLUT_KEY_RIGHT: // Ruota intorno all'asse Y locale inverso
   {
      if (current_camera->get_object_name() == "Main Camera") {
         glm::vec3 up = glm::normalize(glm::vec3(camera_matrix[1]));
         camera_matrix = glm::rotate(camera_matrix, glm::radians(-rotation_speed), up);
      } else{
         moving = true;
         if(selectorCol + 1 < 8){
            Node* piece;
            if(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_number_of_chilren()==1)
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[0];
            else
               piece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[1];

            //piece->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol+1)->get_matrix());
            chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->remove_child(piece);
            chessboardNodeMatrix.getPiece(selectorRow, ++selectorCol)->add_child(piece);
            selector->set_matrix(chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_matrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));
         }
      }
      break;
   }

   case GLUT_CTRL_L: // Reset della matrice
      camera_matrix = camera1Coordinate;
      break;
   }
   dynamic_camera->set_matrix(camera_matrix);

}

void keyboardCallback(unsigned char key, int x, int y) {
   Node* currentPiece = nullptr;
   switch(key)
   {
      case '0':
         current_camera = *camera_list.getElementAt(0);
         current_camera->update_window_size(eng.getWindowWidth(), eng.getWindowHeight());
         eng.setCamera(current_camera);
       break;
      case '1':
         current_camera = *camera_list.getElementAt(1);
         current_camera->update_window_size(eng.getWindowWidth(), eng.getWindowHeight());
         eng.setCamera(current_camera);
      break;
      case '2':
         current_camera = *camera_list.getElementAt(2);
         current_camera->update_window_size(eng.getWindowWidth(), eng.getWindowHeight());
         eng.setCamera(current_camera);
      break;
      case '3':
         current_camera = *camera_list.getElementAt(3);
         current_camera->update_window_size(eng.getWindowWidth(), eng.getWindowHeight());
         eng.setCamera(current_camera);
      break;
      case '4':
         current_camera = *camera_list.getElementAt(4);
         current_camera->update_window_size(eng.getWindowWidth(), eng.getWindowHeight());
         eng.setCamera(current_camera);
      break;
      case '5':
         current_camera = *camera_list.getElementAt(5);
         current_camera->update_window_size(eng.getWindowWidth(), eng.getWindowHeight());
         eng.setCamera(current_camera);
      break;
      case TAB: {
         if(moving){
            break;
         }
         // Calcola la posizione corrente nella matrice
         int currentRow = selectorRow;
         int currentCol = selectorCol;

         // Ciclo per trovare la prossima cella non vuota
         do {
            // Sposta alla prossima cella (logica orizzontale, poi verticale)
            if (currentCol < 7) {
                  currentCol++; // Avanza di una colonna
            } else {
                  currentCol = 0; // Torna alla prima colonna
                  if (currentRow < 7) {
                     currentRow++; // Passa alla riga successiva
                  } else {
                     currentRow = 0; // Torna alla prima riga
                  }
            }

            // Ottieni il pezzo dalla nuova posizione
            auto nextPiece = chessboardNodeMatrix.getPiece(currentRow, currentCol);

            // Se il pezzo non è vuoto e non è una "cell", esci dal ciclo
            if (nextPiece && nextPiece->get_number_of_chilren()!=0) {
                  // Aggiorna la posizione del selettore in base alla matrice world coordinates del pezzo
                  selector->set_matrix(nextPiece->get_matrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.2f, 0.0f)));

                  // Aggiorna le coordinate del selettore
                  selectorRow = currentRow;
                  selectorCol = currentCol;

                  break;
            }
         } while (currentRow != selectorRow || currentCol != selectorCol); // Evita cicli infiniti se tutte le celle sono vuote

         // Resetta il contatore del tempo
         timeCounter = 0.0f;
      }
      break;

   // Modify the case where the piece is captured
   case '\r': //enter
{

      saveState();

      if (chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_number_of_chilren() > 1) {
         Node* pieceToRemove = chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->get_children()[0];

         // Salva lo stato del pezzo catturato
         captured_pieces.push_back({pieceToRemove, selectorRow, selectorCol});

         // Rimuovi il pezzo catturato dalla scacchiera
         //pieceToRemove->set_matrix(glm::mat4(1.0f));  // Reset delle trasformazioni
         chessboardNodeMatrix.getPiece(selectorRow, selectorCol)->remove_child(pieceToRemove);
      }

      //Retrieve the element just moved
      Node* selectedPiece = chessboardNodeMatrix.getPiece(selectorRow, selectorCol);
      std::cout << selectedPiece->get_children()[0]->get_object_name() << std::endl;
      for(auto& el : initialPosition)
      {
         if(el.piece == selectedPiece->get_children()[0])
         {
            el.row = selectorRow;
            el.col = selectorCol;
         }
      }

      while(!redo_stack.empty())
         redo_stack.pop();
      saveState();

      moving = false;
   }
   break;

      case 'x':
         if(isWireframeEnable){
            eng.disableWireFrame();
         }
         else{
            eng.enableWireFrame();
         }
         isWireframeEnable = !isWireframeEnable;
      break;
      case 'c':
         if(showFPS==false)      eng.enableFPS();
         else                    eng.disableFPS();
         showFPS = !showFPS;
      break;
      case 'z':
         undo();
      break;

      case 'y':
         redo();
      break;


      case 't':
         reset();
      break;

   }

   if (current_camera->get_object_name() == "Main Camera") {

      glm::mat4 camera_matrix = current_camera->get_matrix();
      switch (key)
      {
      case 'w': // Muovi avanti lungo Z locale (Forward)
         camera_matrix = glm::translate(camera_matrix, -camera_speed * glm::vec3(camera_matrix[2]));
         break;

      case 's': // Muovi indietro lungo Z locale
         camera_matrix = glm::translate(camera_matrix, camera_speed * glm::vec3(camera_matrix[2]));
         break;

      case 'a': // Muovi a sinistra lungo X locale (Right inverso)
         camera_matrix = glm::translate(camera_matrix, -camera_speed * glm::vec3(camera_matrix[0]));
         break;

      case 'd': // Muovi a destra lungo X locale
         camera_matrix = glm::translate(camera_matrix, camera_speed * glm::vec3(camera_matrix[0]));
         break;

      case 'e': // Muovi verso l'alto lungo Y locale (Up)
         camera_matrix = glm::translate(camera_matrix, camera_speed * glm::vec3(camera_matrix[1]));
         break;

      case 'q': // Muovi verso il basso lungo Y locale
         camera_matrix = glm::translate(camera_matrix, -camera_speed * glm::vec3(camera_matrix[1]));
         break;
      }
      current_camera->set_matrix(camera_matrix);
   }

}


std::vector<std::string> blackPieces = {
      "B_Rook_1", "B_Knight_1", "B_Bishop_1", "B_King", "B_Queen",
      "B_Bishop_2", "B_Knight_2", "B_Rook_2",
      "B_Pawn_1", "B_Pawn_2", "B_Pawn_3", "B_Pawn_4",
      "B_Pawn_5", "B_Pawn_6", "B_Pawn_7", "B_Pawn_8"
   };

 std::vector<std::string> whitePieces = {
      "W_Rook_1", "W_Knight_1", "W_Bishop_1", "W_Queen", "W_King",
      "W_Bishop_2", "W_Knight_2", "W_Rook_2",
      "W_Pawn_1", "W_Pawn_2", "W_Pawn_3", "W_Pawn_4",
      "W_Pawn_5", "W_Pawn_6", "W_Pawn_7", "W_Pawn_8"
   };

float cellWidth;


void initializeChessboard(const glm::mat4& chessboardMatrixWorld) {

   // Calcola le dimensioni delle celle
   float scaleX = glm::length(glm::vec3(chessboardMatrixWorld[0][0], chessboardMatrixWorld[1][0], chessboardMatrixWorld[2][0]));
   float scaleZ = glm::length(glm::vec3(chessboardMatrixWorld[0][2], chessboardMatrixWorld[1][2], chessboardMatrixWorld[2][2]));
   cellWidth = scaleX + 0.075f; // Aggiustamento per le dimensioni delle celle

   glm::mat4 diffLateral = glm::translate(glm::mat4(1.0f), glm::vec3(cellWidth, 0.0f, 0.0f)); // Traslazione laterale
   glm::mat4 diffVertical = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -cellWidth)); // Traslazione verticale

   glm::mat4 currentDiff = glm::mat4(1.0f);

   for (unsigned int row = 0; row < 8; row++) {
      for (unsigned int col = 0; col < 8; col++) {
         // Verifica se la cella è vuota
         if (chessboardNodeMatrix.getPiece(row, col) == nullptr) {
            // Calcola la posizione corrente in world coordinates
            glm::mat4 cellMatrix;
            if(col==0){
               if(row==0){
                  Node* cell1 = root->find_by_name("B_Rook_1")[0];
                  cellMatrix = cell1->get_matrix();
               } else{
                  cellMatrix = chessboardNodeMatrix.getPiece(row-1, col)->get_matrix();
               }
            }
            else
               cellMatrix = chessboardNodeMatrix.getPiece(row, col-1)->get_matrix();

            cellMatrix = (cellMatrix*currentDiff);
            currentDiff = diffLateral;
            // Crea un nuovo nodo per la cella vuota
            Node* emptyCell = new Node("cell_"+std::to_string(row)+"_"+std::to_string(col), cellMatrix);

            // Imposta il nodo nella matrice della scacchiera
            chessboardNodeMatrix.setPiece(row, col, emptyCell);
         }
      }
      currentDiff = diffVertical;
   }

   // Popola i pezzi neri
   for (int i = 0; i < 8; i++) {
      if(blackPieces[i] == "B_King")
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.4f,0.0f)));
      else if (blackPieces[i] == "B_Queen")
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
      else if (blackPieces[i] == "B_Bishop_1")
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
      else if (blackPieces[i] == "B_Bishop_2")
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
      else if (blackPieces[i] == "B_Knight_1")
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.2f, 0.0f)));
      else if (blackPieces[i] == "B_Knight_2")
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.2f, 0.0f)));
      else
         root->find_by_name(blackPieces[i])[0]->set_matrix(glm::mat4(1.0f));
      root->find_by_name(blackPieces[i+8])[0]->set_matrix(glm::mat4(1.0f));
      chessboardNodeMatrix.getPiece(0, i)->add_child(root->find_by_name(blackPieces[i])[0]);
      chessboardNodeMatrix.getPiece(1, i)->add_child(root->find_by_name(blackPieces[i + 8])[0]);
      root->remove_child(chessboardNodeMatrix.getPiece(0, i)->get_children()[0]);
      root->remove_child(chessboardNodeMatrix.getPiece(1, i)->get_children()[0]);


      initialPosition.push_back({chessboardNodeMatrix.getPiece(0, i)->get_children()[0], 0, i});
      initialPosition.push_back({chessboardNodeMatrix.getPiece(1, i)->get_children()[0], 1, i});

      resetPosition.push_back({chessboardNodeMatrix.getPiece(0, i)->get_children()[0], 0, i});
      resetPosition.push_back({chessboardNodeMatrix.getPiece(1, i)->get_children()[0], 1, i});
   }

   // Popola i pezzi bianchi
   for (int i = 0; i < 8; i++) {
      if (whitePieces[i] == "W_King")
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.4f, 0.0f)));
      else if (whitePieces[i] == "W_Queen")
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
      else if (whitePieces[i] == "W_Bishop_1")
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
      else if (whitePieces[i] == "W_Bishop_2")
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
      else if (whitePieces[i] == "W_Knight_1")
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.2f, 0.0f)));
      else if (whitePieces[i] == "W_Knight_2")
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.2f, 0.0f)));
      else
         root->find_by_name(whitePieces[i])[0]->set_matrix(glm::mat4(1.0f));

      root->find_by_name(whitePieces[i+8])[0]->set_matrix(glm::mat4(1.0f));

      chessboardNodeMatrix.getPiece(7, i)->add_child(root->find_by_name(whitePieces[i])[0]);
      chessboardNodeMatrix.getPiece(6, i)->add_child(root->find_by_name(whitePieces[i + 8])[0]);
      root->remove_child(chessboardNodeMatrix.getPiece(7, i)->get_children()[0]);
      root->remove_child(chessboardNodeMatrix.getPiece(6, i)->get_children()[0]);

      initialPosition.push_back({chessboardNodeMatrix.getPiece(7, i)->get_children()[0], 7, i});
      initialPosition.push_back({chessboardNodeMatrix.getPiece(6, i)->get_children()[0], 6, i});

      resetPosition.push_back({chessboardNodeMatrix.getPiece(7, i)->get_children()[0], 7, i});
      resetPosition.push_back({chessboardNodeMatrix.getPiece(6, i)->get_children()[0], 6, i});
   }
   // AGGIUNTE TUTTE LE CELLE COME FIGLIE DI ROOT, NON SOLO QUELLE OCCUPATE

   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8;j++){
         root->add_child(chessboardNodeMatrix.getPiece(i, j));
      }
   }
}

//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char *argv[])
{

    std::filesystem::path cwd = std::filesystem::current_path();

    const char* path_file = "../assets/n6/chessboard_final_scale_surrounding_room_new_selector.ovo";
    const char* textuers_dir_path = "../assets/n6/";
    const char* target = "client";

    if (strstr(cwd.string().c_str(), target) != nullptr) {
        std::cout << "The string \"client\" is found in cwd.\n";
        path_file = "../assets/n6/chessboard_final_scale_surrounding_room_new_selector.ovo";
        textuers_dir_path = "../assets/n6/";
    } else {
        std::cout << "The string \"client\" is not found in cwd.\n";
        path_file = "assets/n6/chessboard_final_scale_surrounding_room_new_selector.ovo";
        textuers_dir_path = "assets/n6/";
    }

   // Credits:
   std::cout << "Chess 3D (C) SUPSI" << std::endl;
   std::cout << std::endl;

   // Inizializzazione del motore grafico
   eng.init("Chess3D", 650, 650,argc, argv);


   // Registrazione delle callback
   eng.registerDisplayCallback(displayCallback);
   eng.registerReshapeCallback(reshapeCallback);
   eng.registerSpecialCallback(specialCallback);
   eng.registerKeyboardCallback(keyboardCallback);

   /*
      Codice per dire al motore grafico di renderizzare
      il seguente testo
   */
   eng.printText("=========== COMMANDS ===========");
   eng.printText("[wasdeq] move camera");
   eng.printText("[arrows] rotate camera / move piece");
   eng.printText("[LCTRL] dynamic camera default settings");
   eng.printText("[TAB] move piece selector");
   eng.printText("[x] enable/disable wireframe");
   eng.printText("[c] enable/disable fps");
   eng.printText("[z] undo");
   eng.printText("[y] redo");
   eng.printText("[t] reset");
   eng.printText("[012345] change camera");

   /*
      Creazione delle diverse camere (1 dinamica + 5 statiche)
      e la loro matrice più il setup della NodeList per ciclare
      tra le camere disponibili
   */

   dynamic_camera = new PerspectiveCamera("Main Camera", camera1Coordinate, width, height, near, far, fov);
   positional_camera = new PerspectiveCamera("First Camera", camera2Coordinate, width, height, near, far, fov);
   positional_camera2 = new PerspectiveCamera("Second Camera", camera3Coordinate, width, height, near, far, fov);
   positional_camera3 = new PerspectiveCamera("Third Camera", camera4Coordinate, width, height, near, far, fov);
   positional_camera4 = new PerspectiveCamera("Fourth Camera", camera5Coordinate, width, height, near, far, fov);
   positional_camera5 = new PerspectiveCamera("Fifth Camera", camera6Coordinate, width, height, near, far, fov);

   current_camera = dynamic_camera;
      camera_list.addElement(&dynamic_camera);
         camera_list.addElement(&positional_camera);
            camera_list.addElement(&positional_camera2);
               camera_list.addElement(&positional_camera3);
                  camera_list.addElement(&positional_camera4);
                     camera_list.addElement(&positional_camera5);



   // Caricamento della scena nell'engine
   eng.loadScene(path_file, textuers_dir_path);

   // Retrieve del nodo root dall'engine
   root = eng.getRoot();

   /*
      Codice per riposizionare le camere iniziali dinamicamente in base
      alla posizione della matrice della ChessBoard
   */

   Node* chessboardNode = root->find_by_name("Chess Board")[0];
   chessboardMatrix = chessboardNode->get_final_matrix();

   Mesh* chessboardNodeMesh = dynamic_cast<Mesh*>(chessboardNode);
   chessboardNodeMesh->get_material()->set_transparency(0.8f);

   // Funzione di riposizionamento della camera partendo dalla matrice della chessboard
   auto repositionCamera = [](PerspectiveCamera* camera, const glm::mat4& baseMatrix, const glm::mat4& relativeTransform) {
      camera->set_matrix(baseMatrix * relativeTransform);
   };

   // Riposiziona tutte le camere relative alla matrice della scacchiera
   repositionCamera(dynamic_camera, chessboardMatrix, camera1Coordinate);
   repositionCamera(positional_camera, chessboardMatrix, camera2Coordinate);
   repositionCamera(positional_camera2, chessboardMatrix, camera3Coordinate);
   repositionCamera(positional_camera3, chessboardMatrix, camera4Coordinate);
   repositionCamera(positional_camera4, chessboardMatrix, camera5Coordinate);
   repositionCamera(positional_camera5, chessboardMatrix, camera6Coordinate);

   // Configura nuovamente la camera corrente
   eng.setCamera(dynamic_camera);


   /*
      Codice per inizializzare e popolare la NodeMatrix delle celle
      in cui muovere il selettore
   */

   selector = root->find_by_name("Selector")[0];


   

   for (auto& i : root->get_children())
       std::cout << i->get_object_name() << std::endl;

   /*
      Codice per renderizzare mesh trasparente e sdoppiata per riflesso
   */

   // Definisci bottomY come la quantità di traslazione (ad esempio, -4.0f nel tuo caso)
   float bottomY = -2.0f; // Usa il valore appropriato per bottomY
   glm::mat4 scaleFlip = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f));

   glm::mat4 translateDown = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bottomY, 0.0f));

   glm::mat4 finalTransform = scaleFlip;

   initializeChessboard(chessboardMatrix);

   saveState();

   for(std::string& name: blackPieces){
      Node* element_node = root->find_by_name(name)[0];

      Mesh* element_mesh = static_cast<Mesh*>(element_node);

      if (name == "B_King")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)) * finalTransform;
      else if (name == "B_Queen")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.8f, 0.0f)) * finalTransform;
      else if (name == "B_Bishop_1")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.4f, 0.0f)) * finalTransform;
      else if (name == "B_Bishop_2")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.4f, 0.0f)) * finalTransform;
      else if (name == "B_Knight_1")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.2f, 0.0f)) * finalTransform;
      else if (name == "B_Knight_2")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.2f, 0.0f)) * finalTransform;
      else if (name == "B_Rook_1")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)) * finalTransform;
      else if (name == "B_Rook_2")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)) * finalTransform;
      else
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) * finalTransform;


      Mesh* copiedMesh = new Mesh(
         name+"_Flipped", // Nome del nodo
         finalTransform, // Applica la trasformazione finale
         element_mesh->get_face_vertices().size(), // Numero di facce
         element_mesh->get_all_vertices().size()// Numero di vertici

      );

      // Imposta i dati aggiuntivi
      copiedMesh->set_all_vertices(element_mesh->get_all_vertices());
      copiedMesh->set_all_normals(element_mesh->get_all_normals());
      copiedMesh->set_all_texture_coords(element_mesh->get_all_texture_coords());
      copiedMesh->set_face_vertices(element_mesh->get_face_vertices());
      copiedMesh->set_material(element_mesh->get_material());
      // Aggiungi la mesh alla scena
      element_mesh->add_child(copiedMesh);
      finalTransform = scaleFlip;
   }


   for(std::string& name: whitePieces){
      Node* element_node = root->find_by_name(name)[0];

      Mesh* element_mesh = static_cast<Mesh*>(element_node);

      if (name == "W_King")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)) * finalTransform;
      else if (name == "W_Queen")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.8f, 0.0f)) * finalTransform;
      else if (name == "W_Bishop_1")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.4f, 0.0f)) * finalTransform;
      else if (name == "W_Bishop_2")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.4f, 0.0f)) * finalTransform;
      else if (name == "W_Knight_1")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.2f, 0.0f)) * finalTransform;
      else if (name == "W_Knight_2")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.2f, 0.0f)) * finalTransform;
      else if (name == "W_Rook_1")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)) * finalTransform;
      else if (name == "W_Rook_2")
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)) * finalTransform;
      else
         finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) * finalTransform;


      Mesh* copiedMesh = new Mesh(
         name+"_Flipped", // Nome del nodo
         finalTransform, // Applica la trasformazione finale
         element_mesh->get_face_vertices().size(), // Numero di facce
         element_mesh->get_all_vertices().size()// Numero di vertici

      );

      // Imposta i dati aggiuntivi
      copiedMesh->set_all_vertices(element_mesh->get_all_vertices());
      copiedMesh->set_all_normals(element_mesh->get_all_normals());
      copiedMesh->set_all_texture_coords(element_mesh->get_all_texture_coords());
      copiedMesh->set_face_vertices(element_mesh->get_face_vertices());
      copiedMesh->set_material(element_mesh->get_material());
      // Aggiungi la mesh alla scena
      element_mesh->add_child(copiedMesh);

      finalTransform = scaleFlip;
   }



   // Loop principale dell'applicazione
   while (true) {
      eng.update();
   }

   // Release engine:
   eng.free();

   delete root;
   delete &camera_list;

   // Done:
   std::cout << "\n[application terminated]" << std::endl;
   return 0;
}
