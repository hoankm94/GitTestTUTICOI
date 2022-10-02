#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;

class card
{
    int suite, rank;

public:
    card()
    {
        suite = 1;
        rank = 1;
    }
    card(int r, int s)
    {
        rank = r;
        suite = s;
    }
    void set(int r, int s)
    {
        rank = r;
        suite = s;
    }
    void print()
    {
        switch (rank)
        {
        case 1:
            cout << "Ace";
            break;
        case 11:
            cout << "Jack";
            break;
        case 12:
            cout << "Queen";
            break;
        case 13:
            cout << "King";
            break;
        case 2:
            cout << 2;
            break;
        case 3:
            cout << 3;
            break;
        case 4:
            cout << 4;
            break;
        case 5:
            cout << 5;
            break;
        case 6:
            cout << 6;
            break;
        case 7:
            cout << 7;
            break;
        case 8:
            cout << 8;
            break;
        case 9:
            cout << 9;
            break;
        case 10:
            cout << 10;
            break;
        default:
            cout << "Rank ERROR";
            break;
        }
        cout << " of ";
        switch (suite)
        {
        case 1:
            cout << "Heart";
            break;
        case 2:
            cout << "Diamond";
            break;
        case 3:
            cout << "Club";
            break;
        case 4:
            cout << "Spade";
            break;
        default:
            cout << "Suite ERROR" << endl;
            break;
        }
    }

    // Set gia tri diem cho la bai
    int getPoint()
    {
        // if (rank == 1)
        // getPointAce();
        if (rank <= 10)
            return rank;
        else
            return 10;
    }
};

class deck
{
    card cards[52];
    int count;

public:
    deck()
    {
        srand(time(NULL));
        int i = 0;
        for (int rank = 1; rank <= 13; rank++)
        {
            for (int suite = 1; suite <= 4; suite++)
            {
                cards[i].set(rank, suite);
                i++;
            }
        }
        count = 52;
    }
    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cards[i].print();
            cout << endl;
        }
    }

    card drawRandom()
    {
        if (count == 0)
        {
            cout << "ERROR: Deck is empty" << endl;
            card c;
            return c;
        }
        int i = rand() % count;
        card card = cards[i];
        // Delete card i from deck
        for (int j = i; j < count - 1; j++)
        {
            cards[j] = cards[j + 1];
        }
        count--;
        return card;
    }
};

class player
{
    card cards[5];
    int count;
    bool stop;
    string name;
    friend class card;

public:
    player()
    {
        stop = count = 0;
    }
    void setName()
    {
        getline(cin, name);
    }
    string getName()
    {
        return name;
    }
    // Initial hand
    void drawInitialHand(deck &d)
    {
        cards[0] = d.drawRandom();
        cards[1] = d.drawRandom();
        count = 2;
    }

    // drawing more cards
    void draw(deck &d)
    {
        cards[count] = d.drawRandom();
        count++;
        if (count == 5)
            stop = 1;
    }

    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cards[i].print();
            cout << endl;
        }
    }

    void stopDraw()
    {
        stop = 1;
    }

    int isStopped()
    {
        return stop;
    }

    int getPoint()
    {
        int p = 0;
        for (int i = 0; i < count; i++)
            p += cards[i].getPoint();
        return p;
    }

    int getCount()
    {
        return count;
    }
};

int main()
{
    deck d;
    short unsigned int num;
    cout << "Xilat game by TUTICOI" << endl;
    cout << "Input number of players: ";
    cin >> num;
    player players[num];
    for (int i = 0; i < num; i++)
    {
        cout << "Input player " << i + 1 << "'s name: ";
        if (i == 0)
            cin.ignore();
        players[i].setName();
        players[i].drawInitialHand(d);
    }
    for (int i = 0; i < num; i++)
    {
        cout << "Player ";
        cout << players[i].getName();
        cout << ": " << endl;
        players[i].print();
        cout << "Score: " << players[i].getPoint() << endl;
        short unsigned int cont = 1;
        while (cont)
        {
            cout << "Continue drawing? (1 = Yes, 0 = No): ";
            try
            {
                cin >> cont;
                if (cont != 1 && cont != 0)
                {
                    throw(cont);
                }
            }
            catch (...)
            {
                cout << "Invalid input! Default option: No" << endl;
                cont = 0;
            }
            if (cont)
            {
                players[i].draw(d);
                players[i].print();
                int score = players[i].getPoint();
                cout << "Score: " << score << endl;

                if (score > 21)
                {
                    cout << "BUSTED" << endl;
                    cont = 0;
                }

                if (score == 21)
                    cont = 0;

                if (score <= 21 && players[i].getCount() == 5)
                    cont = 0;
            }
            else
            {
                players[i].stopDraw();
                cont = 0;
            }
        }
        cout << endl;
    }
    return 0;
}