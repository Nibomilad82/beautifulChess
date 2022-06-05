#include <iostream>
#include <vector>

#include "Piece.h"
#include "Cell.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Empty.h"


Board::Board(){
    cellSize = 200;
    getBoard();
    WHITES_TURN = true;
    windowSizeHeight = 1600;
    windowSizeWidth = 1800;
}

bool Board::returnTurn() {
    return WHITES_TURN;
}

void Board::getBoard(){ // For inputting the chess board!
    boardSFML.resize(8);
    for (int i = 0; i < 8; i++) {
        boardSFML[i].resize(8);
    }
    string temp;
    for (int i = 0; i < 8; i++) {
        std::vector<Piece*> v;
        for (int j = 0; j < 8; j++) {
            cin >> temp;
            if (temp[0] == 'K') {
                Piece *a = new King(temp, i, j);
                v.push_back(a);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
            if (temp[0] == 'Q') {
                Piece *b = new Queen(temp, i, j);
                v.push_back(b);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
            if (temp[0] == 'R') {
                Piece *c = new Rook(temp, i, j);
                v.push_back(c);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
            if (temp[0] == 'B') {
                Piece *d = new Bishop(temp, i, j);
                v.push_back(d);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
            if (temp[0] == 'N') {
                Piece *e = new Knight(temp, i, j);
                v.push_back(e);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
            if (temp[0] == 'P') {
                Piece *f = new Pawn(temp, i, j);
                v.push_back(f);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
            if (temp[0] == '-'){
                Piece *g = new Empty(temp, i, j);
                v.push_back(g);
                boardSFML[i][j] = new Cell(temp, i, j, cellSize);
            }
        }
        board.push_back(v);
    }
}

void Board::printBoard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            cout << board[i][j]->returnPiece() << ' ';
        }
        cout << endl;
    }
}

bool Board::check(bool sig){
    int rowIndex_king, colIndex_king;
    int boolInt1 = (sig) ? 1: -1;
    int boolInt2 = (WHITES_TURN) ? 1: -1;
    bool checkBool = (boolInt1 * boolInt2 * -1 > 0) ? true: false;
    char kingColor = (checkBool) ? 'W': 'B';
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]->returnPiece() != "--") {
                if (board[i][j]->returnPiece()[1] == kingColor) {
                    if (board[i][j]->returnPiece()[0] == 'K') {
                        rowIndex_king = i;
                        colIndex_king = j;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]->returnPiece() != "--") {
                if (board[i][j]->returnPiece()[1] != kingColor) {
                    if (board[i][j]->legalMove(i, j, rowIndex_king, colIndex_king, board)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool Board::checkmate(char checkedColor){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            if (i == 0 && j == 4)
                int x;
            if (board[i][j]->returnPiece() != "--" && board[i][j]->returnPiece()[1] == checkedColor){
                for (int n = 0; n < 8; n++){
                    for (int m = 0; m < 8; m++){
                        if (!(m == j && n == i) && board[i][j]->legalMove(i, j, n, m, board)){
                            vector<vector<Piece*>> board_Copy = board;
                            board[n][m] = board[i][j];
                            board[i][j] = new Empty("--", i, j);
                            if (i == 1 && j == 4 && n == 3 && m == 4)
                                int y;
                            if (check(true)){
                                board = board_Copy;
                            }
                            else{
                                board = board_Copy;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::makeMove(int srcRow, int srcCol, int destRow, int destCol){
    char color = board[srcRow][srcCol]->returnPiece()[1];
    if ((color == 'W' && WHITES_TURN) || color == 'B' && !WHITES_TURN){
    }
    else{
        cout << "not your turn\n";
        return true;
    }
    vector<vector<Piece*>> board_Copy = board;
    if (board[srcRow][srcCol]->move(srcRow, srcCol, destRow, destCol, board)){
        if (!check(false)){
            char color_checked = (WHITES_TURN) ? 'B': 'W';
            if (check(true)){
                if(checkmate(color_checked)){
                    if (color_checked == 'W'){
                        cout << "done\n";
                        cout << "black win";
                        return false;
                    }
                    cout << "done\n";
                    cout << "white win";
                    return false;
                }
                else{
                    WHITES_TURN = !WHITES_TURN;
                    cout << "done\n";
                    return true;
                }
            }
            else{
                WHITES_TURN = !WHITES_TURN;
                cout << "done\n";
                return true;
            }
        }
        else{
            cout << "try again\n";
            board = board_Copy;
            return true;
        }
    }
    else{
        cout << "try again\n";
        return true;
    }
    return true;
}

//void Board::drawCell(Cell *cell, RenderWindow &window) {
//    window.draw(cell->rect);
//    if (cell->cellPiece != "--")
//        window.draw(cell->sprite);
//}
vector<float> Board::clickedWhere(Vector2f a) {
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            if (a.y < i * cellSize && a.x < j * cellSize) {
                return vector<float> {float(i - 1), float(j - 1)};
            }
        }
    }
    return vector<float> {-1, -1};
}

void Board::drawSelect(float x, float y, int sig = 0) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == x && j == y)
                continue;
            if (makeMove(x, y, i, j)) {
                boardSFML[i][j]->cellSelector = true;
            }
        }
    }
}

void Board::run() {
    RenderWindow window(VideoMode(1800, 1600), "BeautifulChess", Style::Close | Style::Titlebar);
    while (window.isOpen()) {
        Event evnt;
        while(window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {
                window.close();
            }
            if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i temp = Mouse::getPosition(window);
                Vector2f mousePositionFloat;
                mousePositionFloat.x = float(temp.x);
                mousePositionFloat.y = float(temp.y);
                clickedCell = clickedWhere(mousePositionFloat);
                if (clickedCell != vector<float> {-1, -1}) {
                    boardSFML[clickedCell[0]][clickedCell[1]]->cellSelected =
                            !(boardSFML[clickedCell[0]][clickedCell[1]]->cellSelected);
                }
//                cout << clickedCell[0] << clickedCell[1];
            }
            window.clear();

            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    window.draw(boardSFML[i][j]->rect);
//                    if (boardSFML[i][j]->cellSelected == true) {
//                        drawSelect(i, j);
//                    }
//                    if (boardSFML[i][j]->cellSelector) {
//                        window.draw(boardSFML[i][j]->shape_circle);
//                    }
                    if (boardSFML[i][j]->cellPiece != "--")
                        window.draw(boardSFML[i][j]->sprite);
                }
            }

            window.display();
        }

    }
}
