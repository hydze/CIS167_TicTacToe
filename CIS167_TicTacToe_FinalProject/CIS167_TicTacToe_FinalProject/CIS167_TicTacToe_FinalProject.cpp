///NAME : JESSE PERRY
// DATE : 26 APRIL 2023
// NOTES : CIS167 - MiniMax Algorithm - TicTacToe AI
// NOTES : This utilizes the minimax algorithm to create an AI
// NOTES : that is impossible to win against. Only able to draw or lose

#include <iostream>
#include <string>

#define PLAYER_SYMBOL 'X'
#define BOT_SYMBOL 'O'

using namespace std;

//use single array instead of double for memory reasons
static char table[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
bool isPlayersTurn;

//getting the table "input" into a format of a double array / 2d graph
inline char& table_at(char arr[], uint8_t x, uint8_t y) {return arr[x + y * 3];};

void displayBoard()
{
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
        "      |     |\n",
        table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7], table[8]
    );
}

void firstTurnQuestion()
{
    int choiceX = 999;
    string temp;

    cout << " ___________________" << endl;
    cout << "|                   |" << endl;
    cout << "|  WHO GOES FIRST?  |" << endl;
    cout << "|   1 = PLAYER      |" << endl;
    cout << "|   2 = GOD AI      |" << endl;
    cout << "|___________________|" << endl;
    cout << endl;

    while (choiceX != 1 && choiceX != 2)
    {
        cout << "Make your choice : ";
        cin >> temp;
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp.at(i) == ' ')
            {
                cin.ignore();
            }
        }
        if (temp.length()==1) 
        {
            choiceX = stoi(temp.c_str());
        };
    }
    isPlayersTurn = choiceX % 2;
}

//ternery operator guide/syntax
// (psuedo)   return 5 if condition else 6
// (cpp)      return (condition) ? 5 : 6;
char detectWins(char arr[])
{
    for (int i = 0; i < 3; i++)
    {
        //vert / horizontal check
        if ((table_at(arr, 0, i) == table_at(arr, 1, i) && table_at(arr, 1, i) == table_at(arr, 2, i)) ||
            (table_at(arr, i, 0) == table_at(arr, i, 1) && table_at(arr, i, 1) == table_at(arr, i, 2)))
        {
            if (table_at(arr, i, i) != '-')
            {
                return (table_at(arr, i, i)==PLAYER_SYMBOL)?PLAYER_SYMBOL:BOT_SYMBOL;
            }
        }
    }
    //diagonal check
    if ((table_at(arr, 0, 0) == table_at(arr, 1, 1) && table_at(arr, 1, 1) == table_at(arr, 2, 2)) ||
        (table_at(arr, 2, 0) == table_at(arr, 1, 1) && table_at(arr, 1, 1) == table_at(arr, 0, 2)))
    {
        if (table_at(arr, 1, 1) != '-')
        {
            return (table_at(arr, 1, 1)==PLAYER_SYMBOL)?PLAYER_SYMBOL:BOT_SYMBOL;
        }
    }
    return '-';
}

bool drawChecker(char arr[])
{
    int k = 0;
    for (int i = 0; i < 9; i++)
    {
        if (arr[i] == '-') k++;
    }
    return (k >= 1)?false:true;
}

//CALLED FROM PLAYER TURN : PLAYER WIN GOOD, BOT WIN BAD
//CALLED FROM BOT TURN    : PLAYER WIN BAD, BOT WIN GOOD

int miniMaxAlg(char arr[], int depth, bool maximizing)
{
    if (detectWins(arr) != '-')
    {
        if (detectWins(arr) == PLAYER_SYMBOL)
        {
            return -1;
        }
        else if (detectWins(arr) == BOT_SYMBOL)
        {
            return 1;
        }
    }
    if (drawChecker(arr))
    {
        return 0;
    }

    //ai turn
	if (maximizing)
	{
		int bestScore = INT_MIN;
		for (int i = 0; i < 9; i++)
		{
			if (arr[i] == '-')
			{
				arr[i] = BOT_SYMBOL;
				int score = miniMaxAlg(arr, depth + 1, false);
				arr[i] = '-';

				if (score > bestScore)
				{
					bestScore = score;
				}
			}
		}
		return bestScore;
	}
	//player turn
	else
	{
		int bestScore = INT_MAX;
		for (int i = 0; i < 9; i++)
		{
			if (arr[i] == '-')
			{
				arr[i] = PLAYER_SYMBOL;
				int score = miniMaxAlg(arr, depth + 1, true);
				arr[i] = '-';

				if (score < bestScore)
				{
					bestScore = score;
				}
			}
		}
		return bestScore;
	}
}

void resetArray(char arr[])
{
    for (int i = 0; i < 9; i++) {arr[i] = table[i];}
}

int miniMaxStart()
{
    int bestScore = INT_MIN;
    int bestMove = 999;
    char tempBoard[9];
    resetArray(tempBoard);

    for (int i = 0; i < 9; i++)
    {
        
        if (table[i] == '-')
        {
            tempBoard[i] = BOT_SYMBOL;
            int score = miniMaxAlg(tempBoard, 0, false);
            resetArray(tempBoard);
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
            cout << score << " : " << i << endl;
        }
    }
    return bestMove;
}

//FIRST MINI MAX ALG

//This is the minimax algorithm
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

//FIRST MINI MAX START

//Minimax start
//void botMove() 
//{
//    float bestScore = float(INT_MIN);
//    int bestPosition = 999;
//
//	for (int i = 0; i < 9; i++)
//	{
//		if (table[i] == '-')
//		{
//            table[i] = BOT_SYMBOL;
//            float score = getMoveScore(i,0,false);
//            table[i] = '-';
//            if (score > bestScore)
//            {
//                bestScore = score;
//                bestPosition = i;
//            }
//            printf("SCORE: %f , POS: %d\n",score,i);
//		}
//	}
//
//    cout << bestPosition;
//    table[bestPosition] = BOT_SYMBOL;
//};

inline void playerTurn(string& m)
{
    cout << "Where would you love to move? : ";
repeat:
    cin >> m;
    if (m.length() != 2)    
    {
        cout << "Wrong input parameters, type again : ";
        goto repeat;
    }
    if (m[0]<49||m[0]>51||m[1]<97||m[1]>99) {
        cout << "Wrong input range, type again : ";
        goto repeat;
    }
    if (table_at(table, m[1]-97,m[0]-49)!='-') {
        cout << "Wrong input, position already set; type again : ";
        goto repeat;
    };

    table_at(table, m[1]-97,m[0]-49) = PLAYER_SYMBOL;
}

int main()
{
	string input = "";

	firstTurnQuestion();
	displayBoard();

	if (isPlayersTurn)
	{
		for (int i = 0; i < 9; i += 2)
		{
			playerTurn(input);
			displayBoard();
			table[miniMaxStart()] = BOT_SYMBOL;

			if (detectWins(table) != '-')
			{
				displayBoard();
				cout << "Bot wins " << endl;
				return 0;
			}
			displayBoard();
		}
		printf("Draw!\n");
	}
	else
	{
		for (int i = 0; i < 9; i += 2)
		{
			table[miniMaxStart()] = BOT_SYMBOL;
			displayBoard();
			if (!drawChecker(table) && detectWins(table) == '-')
			{
				playerTurn(input);
			}

			if (detectWins(table) != '-')
			{
				displayBoard();
				cout << "Bot wins " << endl;
				return 0;
			};
			displayBoard();
		}
		printf("Draw!\n");
	}
}