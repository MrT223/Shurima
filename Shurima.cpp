#include <bits/stdc++.h>
using namespace std;

//--------------------Khai báo các class của chương trình-------------------//

//Bảng game//
class Board {
    char board [4][4];
    public:
    Board();
    bool checkDraw();
    bool checkMove(int r, int c);
    bool checkGame();
    void getMove(int r, int c, char symbol);
    char getLoca(int, int);
    void display();
    void refresh();
    ~Board();
};

//Lớp player//
class Player {
    char symbol;
    public:
    Player();
    Player(char);
    Player(const Player&);
    char getSymbol();
    void setSymbol(char);
    virtual void move(Board &board) = 0;
    virtual string getName() = 0;
    virtual void vicAnnou() = 0;
    ~Player();
};

//Lớp người chơi//
class Human : public Player {
    string name;
    int score;
    public:
    Human();
    Human(char, string);
    Human(const Human&);
    string getName();
    void setName(string);
    int getScore();
    void setScore(int);
    void move(Board &board) override;
    void incScore();
    void display();
    void vicAnnou() override;
    ~Human();
};

//Lớp máy//
class Computer : public Player {
    int lv;
    public:
    Computer();
    Computer(int);
    int getLv();
    void setLv(int);
    void movelv1(Board &board);
    void movelv2(Board &board);
    string getName() override;
    void move(Board &board) override;
    void vicAnnou() override;
    ~Computer();
};

//Lớp game, quản lý trò chơi//
class Game {
    int mode;
    Player* p1;
    Player* p2;
    Board board;
    public:
    Game();
    void setMode();
    int getMode();
    void setPlayer(Human *p1, Human *p2, Computer *p3);
    void start();
    ~Game();
};
//----------------------------------------------------------------------------//



//------------------------------------MAIN------------------------------------//
int main() {
    Human p1, p2;
    Computer a;
    Game game;
    char cont = 'Y';
    game.setMode();
    game.setPlayer(&p1, &p2, &a);
    while(cont == 'Y') {
        game.start();
        cout << "   Ban co muon tiep tuc?" << endl;
        cout << "[Y] Tiep tuc     [N] Ket thuc" << endl;
        cout << "Xac nhan: ";
        cin >> cont;
    }
    cout << "----------------------\n";
    if (game.getMode() == 2) {
        p1.display();
    }
    else if (game.getMode() == 1) {
        p1.display();  
        p2.display();
    }
}
//-----------------------------------------------------------------------------//



//----------Các constructor, destructor, getter, setter của lớp Player---------//
Player::Player() {}

Player::Player(char symbol) {
    this -> symbol = symbol;
}

Player::Player(const Player& other) {
    this -> symbol = other.symbol;
}

char Player::getSymbol() {
    return symbol;
}

void Player::setSymbol(char symbol) {
    this -> symbol = symbol;
}

Player::~Player() {}
//----------------------------------------------------------------------------//


//-------------------Human-------------------//

//Các constructor, destructor, getter, setter của Human//
Human::Human() {
    score = 0;
}
Human::Human(char symbol, string Name) {
    this -> name = name;
}

Human::Human(const Human& other){
    this -> name = other.name;
}

string Human::getName() {
    return name;
}

int Human::getScore() {
    return score;
}

void Human::setScore(int score) {
    this -> score = score;
}

void Human::setName(string name) {
    this-> name = name;
}
Human::~Human() {}
//------------------------------------------//

//Thực hiện nước đi của người chơi
void Human::move(Board& board) {
    int row, col;
    bool validMove = false;
    do {
        cout<<"Nhap vi tri muon di: ";
        cin >> row >> col;
        if(board.checkMove(row, col)) validMove=true;
        else cout << "Nuoc di khong hop le!" << endl;
    }
    while (!validMove);
    board.getMove(row, col, getSymbol());
}

//Tăng điểm của người chơi (1đ mỗi lần)
void Human::incScore() {
    score++;
}

//Xuất thông tin của người chơi
void Human::display(){
    cout << "[" << getName() << "]" << endl;
    cout << "Diem: " << getScore();
}

//Thông báo chiến thắng của người chơi và thực hiện nâng điểm cho người chơi đó
void Human::vicAnnou() {
    cout << getName() << " thang" << endl;
    incScore();
}

//------------------------------------------//


//-----------------Computer----------------//
//Các hàm constructor, destructor, getter, setter của máy//
Computer::Computer() {
    int lv = 1;
}

Computer::Computer(int lv) {
    this -> lv = lv;
}

int Computer::getLv() {
    return lv;
}

void Computer::setLv(int lv) {
    this -> lv = lv;
} 

Computer::~Computer() {}
//--------------------------------------------------------//

//Thuật toán cho máy chế độ dễ
void Computer::movelv1(Board &board) {
    srand(time(NULL));
    int row = rand() % 3 + 1;
    int col = rand() % 3 + 1;
    bool validMove = false;
    do {
        srand(time(NULL));
        row = rand() % 3 + 1;
        col = rand() % 3 + 1;
        if(board.checkMove(row, col)) validMove=true;
    }
    while (!validMove);
    board.getMove(row, col, getSymbol());
}

//Thuật toán cho máy chế độ khó
void Computer::movelv2(Board &board) {
    if (board.getLoca(2, 2) == ' ') board.getMove(2, 2, getSymbol());
    else if (board.getLoca(2, 2) != ' ' && board.getLoca(1, 1) == ' ' && board.getLoca(1, 3) == ' ' && board.getLoca(3, 1) == ' ' && board.getLoca(3, 3) == ' ') {
        srand(time(NULL));
        int temp[2] = {1, 3};
        int row = temp[rand() % 2];
        int col = temp[rand() % 2];
        board.getMove(row, col, getSymbol());
    }
    else if ((board.getLoca(1, 1) == board.getLoca(1, 2) && board.getLoca(1, 1) != ' ' || board.getLoca(1, 2) == board.getLoca(1, 3) && board.getLoca(1, 2) != ' ' || board.getLoca(1, 1) == board.getLoca(1, 3) && board.getLoca(1, 1) != ' ') && (board.getLoca(1, 1) == ' ' || board.getLoca(1, 2) == ' ' || board.getLoca(1, 3) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(1, i) == ' ') {
                board.getMove(1, i, getSymbol());
            }
        }
    }
    else if ((board.getLoca(2, 1) == board.getLoca(2, 2) && board.getLoca(2, 1) != ' ' || board.getLoca(2, 2) == board.getLoca(2, 3) && board.getLoca(2, 2) != ' ' || board.getLoca(2, 1) == board.getLoca(2, 3) && board.getLoca(2, 1) != ' ') && (board.getLoca(2, 1) == ' ' || board.getLoca(2, 2) == ' ' || board.getLoca(2, 3) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(2, i) == ' ') {
                board.getMove(2, i, getSymbol());
            }
        }
    }
    else if ((board.getLoca(3, 1) == board.getLoca(3, 2) && board.getLoca(3, 1) != ' ' || board.getLoca(3, 2) == board.getLoca(3, 3) && board.getLoca(3, 2) != ' ' || board.getLoca(3, 1) == board.getLoca(3, 3) && board.getLoca(3, 1) != ' ') && (board.getLoca(3, 1) == ' ' || board.getLoca(3, 2) == ' ' || board.getLoca(3, 3) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(3, i) == ' ') {
                board.getMove(3, i, getSymbol());
            }
        }
    }
    else if ((board.getLoca(1, 1) == board.getLoca(2, 1) && board.getLoca(1, 1) != ' ' || board.getLoca(2, 1) == board.getLoca(3, 1) && board.getLoca(2, 1) != ' ' || board.getLoca(1, 1) == board.getLoca(3, 1) && board.getLoca(1, 1) != ' ') && (board.getLoca(1, 1) == ' ' || board.getLoca(2, 1) == ' ' || board.getLoca(3, 1) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(i, 1) == ' ') {
                board.getMove(i, 1, getSymbol());
            }
        }
    }
    else if ((board.getLoca(1, 2) == board.getLoca(2, 2) && board.getLoca(1, 2) != ' ' || board.getLoca(2, 2) == board.getLoca(3, 2) && board.getLoca(2, 2) != ' ' || board.getLoca(1, 2) == board.getLoca(3, 2) && board.getLoca(1, 2) != ' ') && (board.getLoca(1, 2) == ' ' || board.getLoca(2, 2) == ' ' || board.getLoca(3, 2) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(i, 2) == ' ') {
                board.getMove(i, 2, getSymbol());
            }
        }
    }
    else if ((board.getLoca(1, 3) == board.getLoca(2, 3) && board.getLoca(1, 3) != ' ' || board.getLoca(2, 3) == board.getLoca(3, 3) && board.getLoca(2, 3) != ' ' || board.getLoca(1, 3) == board.getLoca(3, 3) && board.getLoca(1, 3) != ' ') && (board.getLoca(1, 3) == ' ' || board.getLoca(2, 3) == ' ' || board.getLoca(3, 3) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(i, 3) == ' ') {
                board.getMove(i, 3, getSymbol());
            }
        }
    }
    else if ((board.getLoca(1, 1) == board.getLoca(2, 2) && board.getLoca(1, 1) != ' ' || board.getLoca(2, 2) == board.getLoca(3, 3) && board.getLoca(2, 2) != ' ' || board.getLoca(1, 1) == board.getLoca(3, 3) && board.getLoca(1, 1) != ' ') && (board.getLoca(1, 1) == ' ' || board.getLoca(2, 2) == ' ' || board.getLoca(3, 3) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(i, i) == ' ') {
                board.getMove(i, i, getSymbol());
            }
        }
    }
    else if ((board.getLoca(1, 3) == board.getLoca(2, 2) && board.getLoca(1, 3) != ' ' || board.getLoca(2, 2) == board.getLoca(3, 1) && board.getLoca(2, 2) != ' ' || board.getLoca(1, 3) == board.getLoca(3, 1) && board.getLoca(1, 3) != ' ') && (board.getLoca(1, 3) == ' ' || board.getLoca(2, 2) == ' ' || board.getLoca(3, 1) == ' ' )) {
        for (int i = 1; i < 4; i++) {
            if (board.getLoca(i, 4 - i) == ' ') {
                board.getMove(i, 4 - i, getSymbol());
            }
        }
    }
    else {
        srand(time(NULL));
        int row = rand() % 3 + 1;
        int col = rand() % 3 + 1;
        bool validMove = false;
        do {
            srand(time(NULL));
            row = rand() % 3 + 1;
            col = rand() % 3 + 1;
            if(board.checkMove(row, col)) validMove=true;
        }
        while (!validMove);
            board.getMove(row, col, getSymbol());
    }
}

//Thực hiện nước đi của máy tùy theo độ khó đã được gán
void Computer::move(Board &board) {
    if (lv == 1) movelv1(board);
    else if (lv == 2) movelv2(board);
}

//Hàm thông báo thất bại của người chơi
void Computer::vicAnnou() {
    cout << "BAN DA THUA!" << endl;
}

//-----------------------------------------------------------------------------------------------------//


//-----------------------------Board------------------------------//
//Hàm khởi tạo mặc định
Board::Board() {
  for(int i = 1; i < 4; i++) {
    for(int j = 1; j < 4; j++) {
      board[i][j] = ' ';
    }
  }    
}

//Kiểm tra trạng thái bảng đã được lấp đầy hay chưa
bool Board::checkDraw(){
  if (board[1][3] != ' ' && board[2][3] != ' ' && board[3][3] != ' ' &&
	    board[1][2] != ' ' && board[2][2] != ' ' && board[3][2] != ' ' &&
	    board[1][1] != ' ' && board[2][1] != ' ' && board[3][1] != ' ') {
	  return true;
  }
  else return false;
}

//Kiểm tra tính hợp lệ của nước đi
bool Board::checkMove(int r, int c) {
    if (board[r][c] != ' ' || r <= 0 || c <= 0 || r > 3 || c > 3) return false;
    else return true;
}


//Kiểm tra chiến thắng của game
bool Board::checkGame() {
    //dòng đầu
if (board[1][3] != ' ' && board[1][3] == board[2][3] && board[2][3] == board[3][3])
		return true;
    //dòng 2
	else if (board[1][2] != ' ' && board[1][2] == board[2][2] && board[2][2] == board[3][2])
		return true;
    //dòng 3
	else if (board[1][1] != ' ' && board[1][1] == board[2][1] && board[2][1] == board[3][1])
		return true;
    //cột 1
	else if (board[1][3] != ' ' && board[1][3] == board[1][2] && board[1][2] == board[1][1])
		return true;
    //cột 2
	else if (board[2][3] != ' ' && board[2][3] == board[2][2] && board[2][2] == board[2][1])
		return true;
    //cột 3
	else if (board[3][3] != ' ' && board[3][3] == board[3][2] && board[3][2] == board[3][1])
		return true;
    //chéo chính
	else if (board[1][3] != ' ' && board[1][3] == board[2][2] && board[2][2] == board[3][1])
		return true;
    //chéo phụ
	else if (board[1][1] != ' ' && board[1][1] == board[2][2] && board[2][2] == board[3][3])
		return true;
	return false;
}

//Lấy tên của máy (luôn là Computer) 
string Computer::getName() {
    return "Computer"; 
}

//Nhận nước đi và lưu vào bảng
void Board::getMove(int r, int c, char symbol) {
    board[r][c] = symbol;
}

//Lấy kí tự của một điểm trên bảng
char Board::getLoca(int r, int c) {
    return board[r][c];
}

//Xuất bảng game
void Board::display() {
    system("clear");
  cout << "| " << board[1][3] << " | " << board[2][3] << " | " << board[3][3] << " |"<< endl;
  cout << "|---|---|---|" << endl;
  cout << "| " << board[1][2] << " | " << board[2][2] << " | " << board[3][2] << " |"<< endl;
  cout << "|---|---|---|" << endl;
  cout << "| " << board[1][1] << " | " << board[2][1] << " | " << board[3][1] << " |" << endl;
}

//Làm mới bảng sau mỗi vòng chơi
void Board::refresh() {
    for(int i = 1; i < 4; i++) {
    for(int j = 1; j < 4; j++) {
      board[i][j] = ' ';
    }
  }
}

Board::~Board() {}

//-----------------------------------------------------------------//


//-----------------------------Game-------------------------------//
Game::Game() {
    mode = 1;
}

//Chọn chế độ chơi (đấu với người hoặc đấu với máy)
void Game::setMode() {
    cout << "   [1] Nguoi vs nguoi      [2] Nguoi vs may" << endl;
    cout << "Chon che do choi: ";
    bool valid = false;
    while(!valid) {
        cin >> mode;
        if (mode == 1 || mode == 2) break;
        else {
            cout << "Che do khong hop le, vui long nhap lai: ";
        }
    }
}

int Game::getMode() {
    return mode;
}

//Chọn người chơi thông qua chế độ được chọn
void Game::setPlayer(Human *p1, Human *p2, Computer *p3) {
    char symbol(' '), symbol1(' '), symbol2(' '), symbol3(' ');
  if (mode == 1) {
    this->p1 = p1;
    cout << "Nhap ten nguoi choi 1: ";
    string name1;
    cin.ignore();
    getline(cin, name1);
    p1->setName(name1);

    cout << "Chon ky tu muon danh " << p1->getName() << ": ";
    while (!(cin >> symbol) || (symbol != 'X' && symbol != 'x' && symbol != 'O' && symbol != 'o')) {
      cout << "Ky tu khong hop le!" << endl;
      cout << "Hay nhap lai ky tu (X hoac O): ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (symbol == 'x' || symbol == 'o')
      symbol1 = symbol - 32;
    if (symbol == 'X' || symbol == 'O')
      symbol1 = symbol;

    if (symbol1 == 'X') {
      symbol2 = 'O';
    }
    if (symbol1 == 'O') {
      symbol2 = 'X';
    }

    p1->setSymbol(symbol1);
    p2->setSymbol(symbol2);
    this->p2 = p2;

    cout << "Nhap ten nguoi choi 2: ";
    string name2;
    cin.ignore();
    getline(cin, name2);
    p2->setName(name2);
  } else {
    this->p1 = p1;
    cout << "Nhap ten nguoi choi: ";
    string name;
    cin.ignore();
    getline(cin, name);
    p1->setName(name);

    cout << "Chon ky tu muon danh " << p1->getName() << ": ";
    while (!(cin >> symbol) || (symbol != 'X' && symbol != 'x' && symbol != 'O' && symbol != 'o')) {
      cout << "Ky tu khong hop le!" << endl;
      cout << "Hay nhap lai ky tu (X hoac O): ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (symbol == 'x' || symbol == 'o')
      symbol1 = symbol - 32;
    if (symbol == 'X' || symbol == 'O')
      symbol1 = symbol;

    p1->setSymbol(symbol1);

    if (symbol1 == 'X') {
      symbol3 = 'O';
    }
    if (symbol1 == 'O') {
      symbol3 = 'X';
    }

    cout << "[1] De [2] Kho" << endl;
    int lv;
    cout << "Chon cap do cua may: ";
    while (!(cin >> lv) || (lv != 1 && lv != 2)) {
      cout << "Chon sai cap do xin hay chon lai: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    p3->setLv(lv);
    this->p2 = p3;
    p3->setSymbol(symbol3);
  }
}

//Quản lý chính của game
void Game::start() {
    Player* turnPlayer = p1;
    Player* winner;
    bool draw = false;
    while(true) {
        board.display();
        cout << "Luot cua [" << turnPlayer->getName() << "]" << endl;
        turnPlayer->move(board);
        if (board.checkGame()) {
            winner = turnPlayer;
            board.display();
            break;
        }
        if (board.checkDraw()) {
            draw = true;
            board.display();
            cout << "HOA" << endl;
            break;
        }
        turnPlayer = (turnPlayer == p1) ? p2 : p1;
    }
    if (!draw && winner->getName() != " ") {
        winner->vicAnnou();
    }
    board.refresh();
}

Game::~Game() {}
//----------------------------------------------------------------//