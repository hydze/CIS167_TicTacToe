//#include <iostream>
//#include <string>
//
//#define PLAYER_SYMBOL 'X'
//#define BOT_SYMBOL 'O'
//
//using namespace std;
//
////instead of copying boards which takes a lot of memory, we are going to preform the move on the actual board, then undo it
//static char table[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
//
//bool playersTurn;
//
////getting the table into a format of a double array
//inline char& table_at(uint8_t x, uint8_t y) {
//    return table[x + y * 3];
//};
//
//void displayBoard()
//{
//    // system("cls");
//    printf(
//        "   a     b     c\n"
//        "      |     |\n"
//        "1  %c  |  %c  |  %c\n"
//        " _____|_____|_____\n"
//        "      |     |     \n"
//        "2  %c  |  %c  |  %c\n"
//        " _____|_____|_____\n"
//        "      |     |     \n"
//        "3  %c  |  %c  |  %c\n"
//        "      |     |\n",
//        table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7], table[8]
//    );
//}
//
//void firstTurnQuestion()
//{
//    int choiceX = 999;
//    string temp;
//
//    cout << " ___________________" << endl;
//    cout << "|                   |" << endl;
//    cout << "|  WHO GOES FIRST?  |" << endl;
//    cout << "|   1 = PLAYER      |" << endl;
//    cout << "|   2 = GOD AI      |" << endl;
//    cout << "|___________________|" << endl;
//    cout << endl;
//
//    while (choiceX != 1 && choiceX != 2)
//    {
//        cout << "Make your choice : ";
//        cin >> temp;
//        if (temp.length()==1) {
//            choiceX = stoi(temp.c_str());
//        };
//    }
//    playersTurn = choiceX % 2;
//}
//
////ternery operator guide/syntax
//// (psuedo)   return 5 if condition else 6
//// (cpp)      return (condition) ? 5 : 6;
//uint8_t detectWins()
//{
//    for (int i = 0; i < 3; i++)
//    {
//        //vert / horizontal check
//        if ((table_at(0, i) == table_at(1, i) && table_at(1, i) == table_at(2, i)) ||
//            (table_at(i, 0) == table_at(i, 1) && table_at(i, 1) == table_at(i, 2)))
//        {
//            if (table_at(i, i) != '-')
//            {
//                return (table_at(i, i)==PLAYER_SYMBOL)?PLAYER_SYMBOL:BOT_SYMBOL;
//            }
//
//        }
//    }
//    //diagonal check
//    if ((table_at(0, 0) == table_at(1, 1) && table_at(1, 1) == table_at(2, 2)) ||
//        (table_at(2, 0) == table_at(1, 1) && table_at(1, 1) == table_at(0, 2)))
//    {
//        if (table_at(1, 1) != '-')
//        {
//            return (table_at(1, 1)==PLAYER_SYMBOL)?PLAYER_SYMBOL:BOT_SYMBOL;
//        }
//    }
//    return '-';
//}
//
///*

#include <iostream>
#include <string>
#include <limits>

#define PLAYER_SYMBOL 'X'
#define BOT_SYMBOL 'O'
#define EMPTY_SYMBOL ' '

static uint8_t table[] = "         ";
static bool playersTurn;

inline uint8_t& table_at(uint8_t x, uint8_t y) { return table[x + y * 3]; };
static bool started = false;

void display_board() {
    system("cls");
    printf(
        "   a     b     c\n"
        "      |     |\n"
        "1  %c  |  %c  |  %c\n"
        " _____|_____|_____\n"
        "      |     |     \n"
        "2  %c  |  %c  |  %c\n"
        " _____|_____|_____\n"
        "      |     |     \n"
        "3  %c  |  %c  |  %c\n"
        "      |     |\n\n",
        table[0], table[1], table[2],
        table[3], table[4], table[5],
        table[6], table[7], table[8]
    );
};

void first_turn_question() {

    int choice = -1;
    std::string temp;

    printf(" ___________________ \n"
        "|                   |\n"
        "|  WHO GOES FIRST?  |\n"
        "|   1 = PLAYER      |\n"
        "|   2 = GOD AI      |\n"
        "|___________________|\n\n");

    while (choice != 1 && choice != 2)
    {
        printf("Make your choice: ");
        std::cin >> temp;
        if (temp.length() == 1) {
            choice = std::stoi(temp.c_str());
        };
    }

    playersTurn = choice % 2;
};

uint8_t detect_wins() {

    if (((table[0] == table[4] && table[4] == table[8]) || (table[2] == table[4] && table[4] == table[6]))
        && table[4] != EMPTY_SYMBOL)
        return table[4] == PLAYER_SYMBOL ? PLAYER_SYMBOL : BOT_SYMBOL;

    for (int i = 0; i < 3; i++)
        if (((table_at(0, i) == table_at(1, i) && table_at(1, i) == table_at(2, i)) ||
            (table_at(i, 0) == table_at(i, 1) && table_at(i, 1) == table_at(i, 2)))
            && table_at(i, i) != EMPTY_SYMBOL)
            return table_at(i, i) == PLAYER_SYMBOL ? PLAYER_SYMBOL : BOT_SYMBOL;

    return EMPTY_SYMBOL;
};

void player_turn(std::string& s) {

    printf("Where would you love to move?: ");

repeat:
    std::cin >> s;
    if (s.length() != 2) {
        printf("Wrong input parameters, type again: ");
        goto repeat;
    };
    if (s[0] < 49 || s[0]>51 || s[1] < 97 || s[1]>99) {
        printf("Wrong input range, type again: ");
        goto repeat;
    };
    if (table_at(s[1] - 97, s[0] - 49) != EMPTY_SYMBOL) {
        printf("Wrong input, position already set; type again: ");
        goto repeat;
    };

    table_at(s[1] - 97, s[0] - 49) = PLAYER_SYMBOL;
};

int get_move_score(uint8_t depth, bool is_player_turn) {

    const uint8_t winner = detect_wins();
    int best_score;
    uint8_t best_position = 0;

    if (winner == PLAYER_SYMBOL) {
        return depth;
    }
    else if (winner == BOT_SYMBOL) {
        return -depth;
    }
    else if (depth == 0) return 0;

    if (is_player_turn) {
        best_score = std::numeric_limits<int>::min();
        for (int i = 0; i < 9; i++)
            if (table[i] == EMPTY_SYMBOL) {
                table[i] = PLAYER_SYMBOL;
                int score = get_move_score(depth - 1, false);
                table[i] = EMPTY_SYMBOL;
                if (score > best_score) {
                    best_score = score;
                    best_position = i;
                };
            };
    }
    else {
        best_score = std::numeric_limits<int>::max();
        for (int i = 0; i < 9; i++)
            if (table[i] == EMPTY_SYMBOL) {
                table[i] = BOT_SYMBOL;
                int score = get_move_score(depth - 1, true);
                table[i] = EMPTY_SYMBOL;
                if (score < best_score) {
                    best_score = score;
                    best_position = i;
                };
            };
    };

    return best_score;
};

void bot_move() {

    if (started) {

        int best_score = std::numeric_limits<int>::max();
        uint8_t best_position = 0;

        for (int i = 0; i < 9; i++) {
            if (table[i] == EMPTY_SYMBOL) {
                table[i] = BOT_SYMBOL;
                int score = get_move_score(9, true);
                table[i] = EMPTY_SYMBOL;
                if (score < best_score) {
                    best_score = score;
                    best_position = i;
                };
            };
        };

        table[best_position] = BOT_SYMBOL;

    }
    else {

        if (table[4] == EMPTY_SYMBOL) table[4] = BOT_SYMBOL;
        else table[0] = BOT_SYMBOL;

        started = true;
    };
};

int main() {
    std::string input = "";

    first_turn_question();
    display_board();

    for (int i = 0; i < 9; i += 2) {
        player_turn(input);
        bot_move();
        display_board();
        if (detect_wins() == BOT_SYMBOL) {
            printf("Bot wins!\n");
            return 0;
        };
    };
    printf("Draw!\n");
};













//CALLED FROM PLAYER TURN : PLAYER WIN GOOD, BOT WIN BAD
//CALLED FROM BOT TURN :    PLAYER WIN BAD, BOT WIN GOOD
//*/
//
//
////This is the minimax algorithm
//float getMoveScore(uint8_t pos, uint8_t depth , bool maximizing)
//{
//    const uint8_t winner = detectWins();
//
//    if (winner == PLAYER_SYMBOL)
//    {
//        return -10.0f / depth;
//    }
//    else if (winner == BOT_SYMBOL)
//    {
//        return 10.0f / depth;
//    }
//    if (winner == '-' && depth == 9)
//    {
//        return 0;
//    }
//
//    // if (winner != '-' || depth == 9) // IF ENDGAME
//    //     return ((winner == PLAYER_SYMBOL) ? 10 : -10) //-1 if PLAYER , 1 if BOT
//    //     * (depth < (9-!isPlayerTurn)) // 0 IF DRAW , 1 IF NOT DRAW
//    //     * (1.0f/float(depth));
//
//    float bestScore;
//
//    //AI TURN
//	if (maximizing) 
//    {
//		bestScore = float(INT_MIN);
//		for (int i = 0; i < 9; i++)
//		{
//			if (table[i] == '-')
//			{
//				//make move on table
//				table[i] = BOT_SYMBOL;
//				//use recursion to call it again
//				float score = (getMoveScore(i, depth + 1, false));
//				//undo move on table
//				table[i] = '-';
//
//				if (score > bestScore)
//				{
//					bestScore = score;
//				}
//			}
//		}
//        return bestScore;
//	}
//    //PLAYER TURN
//	else 
//    {
//		bestScore = float(INT_MAX);
//		for (int i = 0; i < 9; i++)
//		{
//			if (table[i] == '-')
//			{
//				//make move on table
//				table[i] = PLAYER_SYMBOL;
//				//use recursion to call it again
//				float score = (getMoveScore(i, depth + 1, true));
//				//undo move on table
//				table[i] = '-';
//
//				if (score < bestScore)
//				{
//					bestScore = score;
//				}
//			}
//		}
//        return bestScore;
//	}
//}
//
//
//
//
//
//
//
//
//
//
//////Minimax start
////void botMove() 
////{
////    float bestScore = float(INT_MIN);
////    int bestPosition = 999;
////
////	for (int i = 0; i < 9; i++)
////	{
////		if (table[i] == '-')
////		{
////            table[i] = BOT_SYMBOL;
////            float score = getMoveScore(i,0,false);
////            table[i] = '-';
////            if (score > bestScore)
////            {
////                bestScore = score;
////                bestPosition = i;
////            }
////            printf("SCORE: %f , POS: %d\n",score,i);
////		}
////	}
////
////    cout << bestPosition;
////    table[bestPosition] = BOT_SYMBOL;
////};
//
//inline void playerTurn(string& m)
//{
//    cout << "Where would you love to move? : ";
//repeat:
//    cin >> m;
//    if (m.length() != 2)    
//    {
//        cout << "Wrong input parameters, type again : ";
//        goto repeat;
//    }
//    if (m[0]<49||m[0]>51||m[1]<97||m[1]>99) {
//        cout << "Wrong input range, type again : ";
//        goto repeat;
//    }
//    if (table_at(m[1]-97,m[0]-49)!='-') {
//        cout << "Wrong input, position already set; type again : ";
//        goto repeat;
//    };
//
//    table_at(m[1]-97,m[0]-49) = PLAYER_SYMBOL;
//}
//
//int main()
//{  
//    string input = "";
//
//    firstTurnQuestion();
//    displayBoard();
//
//    for (int i = 0 ; i < 9 ; i+=2)
//    {
//        playerTurn(input);
//        botMove();
//        if (detectWins()!='-') 
//        {
//            printf("Bot wins!\n");
//            displayBoard();
//            return 0;
//        };
//        displayBoard();
//    }
//    printf("Draw!\n");
//}