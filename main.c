#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <curses.h>
#define HEIGHT 18
#define WIDTH 72
#define TABLE_SIZE 26
#define INFO 21
#define DEBUG 24
#define RED_PIECE R
#define WHITE_PIECE W
using namespace std;

const char whitePiece = 'W';
const char redPiece = 'R';

struct GameState {
    int red[TABLE_SIZE];
    int white[TABLE_SIZE];
    int rolls[4];
    int round;
    char who;
};

void printArrows(int verse, int column)
{
    move(verse, column);
    if (column <= WIDTH / 2 - 1 && verse <= HEIGHT / 2 - 2)
    {
        if ((column - 1) % 5 == 0)
            printw("/");
        else if (column % 5 == 0)
            printw("\\");

    }
    else if (column >= WIDTH / 2 + 2 && verse <= HEIGHT / 2 - 2)
    {
        if ((column - 1) % 5 == 0)
            printw("\\");
        else if ((column - 2) % 5 == 0)
            printw("/");

    }
    else if (column <= WIDTH / 2 - 1 && verse >= HEIGHT / 2 + 2)
    {
        if ((column - 1) % 5 == 0)
            printw("\\");
        else if (column % 5 == 0)
            printw("/");

    }
    else if (column >= WIDTH / 2 + 2 && verse >= HEIGHT / 2 + 2)
    {
        if ((column - 1) % 5 == 0)
            printw("/");
        else if ((column - 2) % 5 == 0)
            printw("\\");

    }
}

void printBoard()
{
    for (int verse = 0; verse <= HEIGHT; verse++)
    {
        for (int column = 0; column <= WIDTH; column++)
        {
            if (verse == 0 || verse == HEIGHT || column < 2 || column > WIDTH - 2) {
                move(verse, column);
                printw(":");

            }
            else if (column == WIDTH / 2 - 1) {
                move(verse, column);
                printw("|||");

            }
            else {
                printArrows(verse, column);

            }

        }

    }
    move(1, WIDTH + 3);
    printw("Tobiasz");
    move(2, WIDTH + 3);
    printw("Grzesik");
    move(3, WIDTH + 3);
    printw("198345");
    refresh();
}

void initiatePieces(GameState& gs)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        switch (i)
        {
        case 1:
            gs.red[i] = 0;
            gs.white[i] = 2;
            break;
        case 6:
            gs.red[i] = 5;
            gs.white[i] = 0;
            break;
        case 8:
            gs.red[i] = 3;
            gs.white[i] = 0;
            break;
        case 12:
            gs.red[i] = 0;
            gs.white[i] = 5;
            break;
        case 13:
            gs.red[i] = 5;
            gs.white[i] = 0;
            break;
        case 17:
            gs.red[i] = 0;
            gs.white[i] = 3;
            break;
        case 19:
            gs.red[i] = 0;
            gs.white[i] = 5;
            break;
        case 24:
            gs.red[i] = 2;
            gs.white[i] = 0;
            break;
        default:
            gs.red[i] = 0;
            gs.white[i] = 0;

        }

    }
}

void dev(GameState& gs)
{
    for (int i = 18; i < TABLE_SIZE; i++)
    {
        gs.red[i] = 0;
    }
    for (int i = 5; i > 0; i--)
    {
        gs.white[i] = 0;
    }
    gs.red[0] = 15;
}

int getX(int index)
{
    if (index > 0 && index < 7) {
        return (66 - ((index - 1) * 5));

    }
    else if (index > 6 && index < 13) {
        return (30 - ((index - 7) * 5));

    }
    else if (index > 12 && index < 19) {
        return (5 + ((index - 13) * 5));

    }
    else if (index > 18 && index < 25) {
        return (41 + ((index - 19) * 5));

    }
    else if (index == 0) {
        return WIDTH / 2;

    }
    return 0;
}

int getY(int index, int amount)
{
    amount--;
    if (index > 12 && index < 25) {
        return 1 + amount;

    }
    else if (index > 0 && index < 13) {
        return 17 - amount;

    }
    else if (index == 0)
        return HEIGHT / 2;
    return 0;
}

void printBar(GameState& gs, int tab[], char who)
{
    if (tab[0] > 0)
    {
        if (who == redPiece)
        {
            move(HEIGHT / 2 + 1, WIDTH / 2 - 1);
            attron(COLOR_PAIR(2));
            printw("%d", tab[0]);
            printw("RR");
            attron(COLOR_PAIR(1));

        }

    }
    if (tab[25] > 0)
    {
        if (who == whitePiece)
        {
            move(HEIGHT / 2 - 1, WIDTH / 2 - 1);
            attron(COLOR_PAIR(3));
            printw("%d", tab[25]);
            printw("WW");
            attron(COLOR_PAIR(1));

        }

    }
}

void printPieces(GameState& gs, int tab[], char piece)
{
    for (int i = 1; i < 25; i++)
    {
        if (tab[i] > 0) {
            for (int j = 1; j <= tab[i]; j++)
            {
                int x = getX(i);
                int y = getY(i, j);
                move(y, x);

                if (piece == redPiece)
                    attron(COLOR_PAIR(2));
                else if (piece == whitePiece)
                    attron(COLOR_PAIR(3));

                printw("%c%c", piece, piece);
                attron(COLOR_PAIR(1));
                refresh();

            }

        }

    }
    printBar(gs, tab, piece);
}

void printDices(GameState& gs)
{
    move(HEIGHT + 1, 0);
    printw("Wyrzucone kosci:");
    attron(COLOR_PAIR(4));
    for (int i = 0; i < 4; i++)
    {
        if (gs.rolls[i] != 0)
            printw(" %d", gs.rolls[i]);

    }
    attron(COLOR_PAIR(1));
    printw("\n");
}

void printNumbers()
{
    for (int i = 1; i < 25; i++)
    {
        int x = getX(i);
        int y = getY(i, 0);
        move(y, x);
        if (i < 10)
            printw("0%d", i);
        else
            printw("%d", i);

    }
}

void playerIndicator(char piece)
{
    if (piece == redPiece)
    {
        move(HEIGHT + 1, WIDTH - 14);
        printw("Gracz: ");
        attron(COLOR_PAIR(2));
        printw("CZERWONY");
        attron(COLOR_PAIR(1));

    }
    else if (piece == whitePiece)
    {
        move(HEIGHT + 1, WIDTH - 11);
        printw("Gracz: ");
        attron(COLOR_PAIR(3));
        printw("BIALY");
        attron(COLOR_PAIR(1));

    }
}

void rollDices(GameState& gs)
{
    int roll1 = rand() % 6;
    if (roll1 == 0)
        roll1 = 6;
    int roll2 = rand() % 6;
    if (roll2 == 0)
        roll2 = 6;

    if (roll1 == roll2) {
        for (int i = 0; i < 4; i++)
            gs.rolls[i] = roll1;

    }
    else {
        gs.rolls[0] = roll1;
        gs.rolls[1] = roll2;
        gs.rolls[2] = 0;
        gs.rolls[3] = 0;

    }
}

int checkIfLegal(GameState& gs, int field, int moves, int player[], int opponent[], char who)
{
    if ((player[0] > 0) && (field != 0))
        return 0;

    if (player[field] < 1)
        return 0;

    if (moves == 0)
        return 0;
    if (who == redPiece && moves + field > 24)
        return 0;
    if (who == whitePiece && field - moves < 1)
        return 0;

    int found = 0;
    for (int i = 0; i < 4; i++) {
        if (gs.rolls[i] == moves)
            found = 1;
    }
    if (!found)
        return 0;

    if (who == redPiece) {
        if (opponent[field + moves] > 1)
            return 0;
    }

    if (who == whitePiece) {
        if (opponent[field - moves] > 1)
            return 0;
    }

    return 1;
}

void refreshBoard(GameState& gs)
{
    clear();
    printBoard();
    printPieces(gs, gs.red, redPiece);
    printPieces(gs, gs.white, whitePiece);
    printNumbers();
    printDices(gs);
    playerIndicator(gs.who);
    refresh();
}

int getField()
{
    move(HEIGHT + 2, 0);
    printw("Podaj pole pionka: ");
    int field;
    scanw("%d", &field);
    return field;
}

int getMoves()
{
    move(HEIGHT + 3, 0);
    printw("Wybierz kosc: ");
    int moves;
    scanw("%d", &moves);
    return moves;
}

void colors()
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
}

int remainingMoves(GameState& gs, int moves)
{
    for (int i = 0; i < 4; i++)
    {
        if (gs.rolls[i] == moves) {
            gs.rolls[i] = 0;
            break;
        }
    }
    int left = 0;
    for (int i = 0; i < 4; i++)
    {
        if (gs.rolls[i] != 0)
            left++;
    }
    return left;
}

int checkCapture(int opponent[], char who, int field, int moves)
{
    if (who == redPiece) {
        if (opponent[field + moves] == 1)
            return 1;
    }

    if (who == whitePiece) {
        if (opponent[field - moves] == 1)
            return 1;
    }

    return 0;
}

void sortRolls(GameState& gs)
{
    for (int i = 0; i < 4 - 1; i++) {
        for (int j = 0; j < 4 - i - 1; j++) {
            if (gs.rolls[j] > gs.rolls[j + 1]) {
                int temp = gs.rolls[j];
                gs.rolls[j] = gs.rolls[j + 1];
                gs.rolls[j + 1] = temp;
            }
        }
    }
}

int possibleToMove(GameState& gs, int player[], int opponent[], char who)
{
    if (who == redPiece && player[0] > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (opponent[0 + gs.rolls[i]] < 2)
                return 1;
        }
    }
    else if (who == whitePiece && player[25] > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (opponent[25 - gs.rolls[i]] < 2)
                return 1;
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (who == redPiece)
            {
                for (int j = 1; j < 25; j++)
                {
                    if ((player[j] > 0) && (j + gs.rolls[i] < 25) && (opponent[j + gs.rolls[i]] < 2))
                        return 1;
                }
            }
            if (who == whitePiece)
            {
                for (int j = 24; j > 0; j--)
                {
                    if ((player[j] > 0) && (j - gs.rolls[i] > 0) && (opponent[j - gs.rolls[i]] < 2))
                        return 1;
                }
            }
        }
    }
    return 0;
}

void forceCapture(int player[], int opponent[], int start, int end)
{
    player[start]--;
    player[end]++;
    opponent[end]--;
    opponent[0]++;
    move(INFO + 1, 0);
    attron(COLOR_PAIR(4));
    if (abs(end - start) != 0)
        printw("Bicie koscia %d", abs(end - start));
    attron(COLOR_PAIR(1));
    refresh();
    getch();
}

void dev2(GameState& gs)
{
    gs.rolls[0] = 2;
    gs.rolls[1] = 6;
    gs.rolls[2] = 0;
    gs.rolls[3] = 0;
}

int capture(GameState& gs, int player[], int opponent[], int i, int j, int sum, char who)
{
    if (who == redPiece)
    {
        int add = j + gs.rolls[i];
        if ((add < 25) && (opponent[add] == 1))
        {
            forceCapture(player, opponent, j, add);
            gs.rolls[i] = 0;
            return 1;
        }
        if ((add + sum < 25) && (opponent[add + sum] == 1))
        {
            forceCapture(player, opponent, j, add + sum);
            for (int k = 0; k <= j; k++)
                gs.rolls[k] = 0;
            return 1;
        }
    }
    else if (who == whitePiece)
    {
        int sub = j - gs.rolls[i];
        if ((sub > 0) && (opponent[sub] == 1))
        {
            forceCapture(player, opponent, j, sub);
            gs.rolls[i] = 0;
            return 1;
        }
        if ((sub - sum > 0) && (opponent[sub - sum] == 1))
        {
            forceCapture(player, opponent, j, sub - sum);
            for (int k = 0; k <= j; k++)
                gs.rolls[k] = 0;
            return 1;
        }
    }
    return 0;
}

int checkBar(int player[], char who)
{
    if (who == redPiece)
    {
        if (player[0] > 0)
            return 1;
    }
    else if (who == whitePiece)
    {
        if (player[25] > 0)
            return 1;
    }
    return 0;
}

int findCapture(GameState& gs, int player[], int opponent[], char who)
{
    if (!checkBar(player, who))
    {
        sortRolls(gs);
        int sum = 0;
        int remaining = remainingMoves(gs, 0);
        for (int k = 1; k <= remaining; k++)
        {
            for (int i = 0; i < 4; i++)
            {
                if (who == redPiece)
                {
                    for (int j = 1; j < 25; j++)
                    {
                        if (player[j] > 0)
                        {
                            if (capture(gs, player, opponent, i, j, sum, who))
                            {
                                printDices(gs);
                                remaining = remainingMoves(gs, 0);
                            }
                        }
                    }
                }
                if (who == whitePiece)
                {
                    for (int j = 24; j > 0; j--)
                    {
                        if (player[j] > 0)
                        {
                            if (capture(gs, player, opponent, i, j, sum, who))
                            {
                                printDices(gs);
                                remaining = remainingMoves(gs, 0);
                            }
                        }
                    }
                }
                sum = sum + gs.rolls[i];
            }
        }
        return remainingMoves(gs, 0);
    }
    return remainingMoves(gs, 0);
}

void correctMove(GameState& gs, int player[], int opponent[], int field, int moves, int capture)
{
    player[field]--;
    if (gs.who == redPiece) {
        player[field + moves]++;
        refreshBoard(gs);
    }
    else if (gs.who == whitePiece) {
        player[field - moves]++;
        refreshBoard(gs);
    }
}

void wrongMove(GameState& gs, int player[], int opponent[])
{
    if (gs.who == redPiece)
        refreshBoard(gs);
    else if (gs.who == whitePiece)
        refreshBoard(gs);
    printDices(gs);
    move(INFO, 0);
    attron(COLOR_PAIR(2));
    printw("Ruch niedozwolony!");
    attron(COLOR_PAIR(1));
    refresh();
    napms(1000);
}

void playerMove(GameState& gs, int player[], int opponent[])
{
    int remaining = findCapture(gs, player, opponent, gs.who);

    while (remaining > 0)
    {
        int capture = 0;
        if (gs.who == redPiece)
            refreshBoard(gs);
        else if (gs.who == whitePiece)
            refreshBoard(gs);

        int field = getField();
        int moves = getMoves();
        if (checkIfLegal(gs, field, moves, player, opponent, gs.who))
        {
            capture = checkCapture(opponent, gs.who, field, moves);
            correctMove(gs, player, opponent, field, moves, capture);
            remaining = remainingMoves(gs, moves);
        }
        else
            wrongMove(gs, player, opponent);
    }
}

void endgame(GameState& gs)
{
    sortRolls(gs);
    if (gs.round % 2 == 1)
    {
        for (int i = 24; i > 18; i--)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i + gs.rolls[j] == 25)
                {
                    gs.red[i]--;
                    gs.red[25]++;
                    gs.rolls[i] = 0;
                    return;
                }
            }
        }
    }
    else if (gs.round % 2 == 0)
    {
        for (int i = 1; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i - gs.rolls[j] == 0)
                {
                    gs.white[i]--;
                    gs.white[0]++;
                    gs.rolls[i] = 0;
                    return;
                }
            }
        }
    }
}

int checkEndgame(GameState& gs)
{
    if (gs.round % 2 == 1)
    {
        for (int i = 0; i < 19; i++)
        {
            if (gs.red[i] > 0)
                return 0;
        }
    }
    else if (gs.round % 2 == 0)
    {
        for (int i = 25; i > 6; i--)
        {
            if (gs.white[i] > 0)
                return 0;
        }
    }
    return 1;
}

int isEnd(GameState& gs)
{
    if (gs.red[25] == 15)
        return 1;
    else if (gs.white[0] == 15)
        return 1;
    else
        return 0;
}

void fail()
{
    attron(COLOR_PAIR(2));
    move(INFO + 1, 0);
    printw("Brak mozliwych ruchow!");
    refresh();
    attron(COLOR_PAIR(1));
    napms(2000);
}

int play(GameState& gs)
{
    if (checkEndgame(gs))
        endgame(gs);
    else if (gs.round % 2 == 1 && possibleToMove(gs, gs.red, gs.white, redPiece))
        playerMove(gs, gs.red, gs.white);
    else if (gs.round % 2 == 0 && possibleToMove(gs, gs.white, gs.red, whitePiece))
        playerMove(gs, gs.white, gs.red);
    else
        fail();
    if (isEnd(gs))
        return 1;
    return 0;
}

int playRound(GameState& gs)
{
    rollDices(gs);
    if (play(gs))
        return -1;
    refreshBoard(gs);
    move(INFO, 0);
    gs.round++;
    return gs.round;
}

void saveFile(GameState& gs)
{
    FILE* file = fopen("save", "wb");
    if (file != NULL) {
        fwrite(gs.red, sizeof(int), TABLE_SIZE, file);
        fwrite(gs.white, sizeof(int), TABLE_SIZE, file);
        fwrite(&gs.round, sizeof(int), 1, file);
        fclose(file);
    }
    else
        printf("Nie można otworzyć pliku do zapisu.\n");
    fclose(file);
    clear();
}

int loadFile(GameState& gs)
{
    int read_red[TABLE_SIZE];
    int read_white[TABLE_SIZE];
    int round;
    FILE* file = fopen("save", "rb");

    if (file != NULL) {
        fread(read_red, sizeof(int), TABLE_SIZE, file);
        fread(read_white, sizeof(int), TABLE_SIZE, file);
        fread(&round, sizeof(int), 1, file);
        fclose(file);
    }
    else
        printf("Blad odczytu.\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        gs.red[i] = read_red[i];
        gs.white[i] = read_white[i];
    }

    printf("%d", round);
    clear();
    refresh();
    fclose(file);
    return round;
}

int menu(GameState& gs)
{
    printw("(P)lay, (S)ave, (L)oad or (Q)uit: ");
    char mode = getch();
    switch (mode)
    {
    case 'P':
    case 'p':
        gs.round = playRound(gs);
        if (gs.round == -1)
        {
            printw("KONIEC GRY!");
            napms(3000);
            return 1;
        }
        return 0;
    case 'S':
    case 's':
        saveFile(gs);
        return 0;
    case 'L':
    case 'l':
        gs.round = loadFile(gs);
        refreshBoard(gs);
        refreshBoard(gs);
        gs.round = playRound(gs);
        return 0;
    case 'Q':
    case 'q':
        return 1;
    default:
        clear();
        return menu(gs);
    }
}

int main()
{
    initscr();
    colors();
    srand(time(NULL));

    GameState gs;
    for (int i = 0; i < TABLE_SIZE; i++) {
        gs.red[i] = 0;
        gs.white[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        gs.rolls[i] = 0;
    }
    gs.round = 1;
    gs.who = redPiece;

    initiatePieces(gs);

    int quit = 0;

    while (!quit)
    {
        quit = menu(gs);
        gs.round++;
    }
}
