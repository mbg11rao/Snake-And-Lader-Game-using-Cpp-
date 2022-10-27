#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string>
#include<windows.h>
#include<tuple>
#include<vector>
#include <fstream>
using namespace std;


// Function Prototypes
void board();
int roll();
void check_location(int& p1, int& p2, int& p3, int& p4, int s1, int s2, int s3, int s4, int s5, int l1, int l2, int l3, int l4, int l5);

// Declaration of arrays for table
char player1[100];
char player2[100];
char player3[100];
char player4[100];

string snakes[2000];

tuple<int, int, int, char, char, char>// function for player same index value
CheckPosition(int p, int p1, int p2, int p3, char pl1, char pl2, char pl3) {
	if (p1 == p && p != 0 && p != 100) {
		p1 = 0;
		pl1 = ' ';
		cout << "It pushed the previous player at " << p << " on 0" << endl;
	}
	if (p2 == p && p != 0 && p != 100) {
		p2 = 0;
		pl2 = ' ';
		cout << "It pushed the previous player at " << p << " on 0" << endl;
	}
	if (p3 == p && p != 0 && p != 100) {
		p3 = 0;
		pl3 = ' ';
		cout << "It pushed the previous player at " << p << " on 0" << endl;
	}
	return make_tuple(p1, p2, p3, pl1, pl2, pl3);
}

tuple<int, int, int, int> winGift(string a, string b, string c, int p1, int p2, int p3) {// function choice  for the gift of six moves 
	int gift;
	char t = 0;
	cout << "You can give 6 points to any other player!\nTo award any of them your gift\nEnter 1 for " << a;
	cout << "\nEnter 2 for " << b << "\nEnter 3 for " << c << endl;
	cin >> gift;
	if (gift == 1) {
		t = p1;
		p1 += 6;
		cout << "Gift awarded to " << a << endl;
	}
	else if (gift == 2) {
		t = p2;
		p2 += 6;
		cout << "Gift awarded to " << b << endl;
	}
	else if (gift == 3) {
		t = p3;
		p3 += 6;
		cout << "Gift awarded to " << c << endl;
	}
	else {
		cout << "Incorrect input!!! The gift isn't awarded!!!" << endl;
	}
	return make_tuple(p1, p2, p3, t);
}

tuple<int, bool> move(int p, bool start, char pN) {// first we will return int 2nd we will return the bool
	if (start) {// function for rolling the dice 
		int r = roll();

		p = p + r;
		if (p > 100) {
			p = p - r;
		}
		cout << "Player " << pN << " got " << r << endl;
		if (r == 6) {

			r = roll();
			p = p + r;
			if (p > 100) {
				p = p - r;
			}
			cout << "Player " << pN << " got " << r << " at 2nd turn" << endl;
			if (r == 6) {

				r = roll();
				p = p + r;
				if (p > 100 && r != 6) {
					p = p - r;
				}
				if (r == 6) {
					p = 6 - 6 - 6;
					cout << "Three consecutive 6's which is 0" << endl;
				}
				else
					cout << "Player " << pN << " got " << r << "at 3rd turn" << endl;
			}
		}
	}
	else {
		int r = roll();
		if (r == 6) {
			char a;
			cout << "Player " << pN << " got 6 and now can move on the board!!!" << endl;
			start = true;
			cout << "Press " << pN << " to roll dice : ";
			cin >> a;
			if (a == pN) {
				tie(p, start) = move(p, start, pN);
			}
		}
		else {
			cout << "Player " << pN << " got " << r << " You need 6 to start!!!" << endl;
		}
	}
	return make_tuple(p, start);// to return the daTa type
}

int main() {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);// for color coding
	char n;
	int r;
	int t = 0, i = 1, toss[4] = { -1, -1, -1, -1 };
	int moves1 = 0, moves2 = 0, moves3 = 0, moves4 = 0;
	int  p1 = 0;
	int  p2 = 0;
	int  p3 = 0;
	int  p4 = 0;
	vector<string> names = { "", "", "", "" };// use string for player names 
	bool startp1 = false, startp2 = false, startp3 = false, startp4 = false;
	bool won1 = false, won2 = false, won3 = false, won4 = false, giftGiven = false;
	int choice = 0;// for menu driven
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 91);
	cout << "1 for PLAY GAME\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 92);
	cout << "2 for credits\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 93);
	cout << "3 for Instructions/Rules\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 94);
	cout << "4 for Records\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 95);
	cout << "5 for EXIT\n";
	cin >> choice;

	if (choice == 2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 69);
		cout << "NAME : MUHAMMAD BIN GULZAR\n roll no 20F-0346\t I created this game in c++ thanks for sir hanan farooq and mam rabia  for helping \n";
	}
	else if (choice == 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 59);
		cout << "INSTRUCTIONS/RULES\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 49);
		cout << "Any player can start playing by getting six on dice\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 29);
		cout << " If there’s six on dice the player gets another turn to roll dice.\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 88);
		cout << "If two or more players are at the same point index then all goes back to the initial state except the latest one.\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "The first winner can give six moves forward to any other player as a gift.\n";

	}
	else if (choice == 4) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		fstream new_file;
		new_file.open("new_file_write.txt", ios::out);
		if (!new_file)
		{
			cout << "File creation failed";
		}
		else
		{
			cout << "New file created";
			new_file << names[toss[0]] << " Has Won in " << moves1 << " moves!!!\n"
				<< names[toss[1]] << " Has Won in " << moves2 << " moves!!!\n"
				<< names[toss[3]] << " Has Won in " << moves4 << " moves!!!\n"
				<< names[toss[2]] << " Has Won in " << moves3 << " moves!!!\n" << endl;    //Writing to file
			new_file.close();
		}



	}

	else if (choice == 5) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "EXIT \n";
	}
	else if (choice == 1)
	{
		//		main game starts from here 

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,10 });
		std::cout << "                  _                               _   _           _     _              " << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,11 });
		std::cout << "  ___ _ __   __ _| | _____  ___    __ _ _ __   __| | | | __ _  __| | __| | ___ _ __ ___ " << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,12 });
		std::cout << " / __| '_ \\ / _` | |/ / _ \\/ __|  / _` | '_ \\ / _` | | |/ _` |/ _` |/ _` |/ _ \\ '__/ __|" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,13 });
		std::cout << " \\__ \\ | | | (_| |   <  __/\\__ \\ | (_| | | | | (_| | | | (_| | (_| | (_| |  __/ |  \\__ \\" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,14 });
		std::cout << " |___/_| |_|\\__,_|_|\\_\\___||___/  \\__,_|_| |_|\\__,_| |_|\\__,_|\\__,_|\\__,_|\\___|_|  |___/" << std::endl;
		std::cout << std::endl;

		cout << "" << endl;
		cout << "********* WELCOME TO SNAKES AND LADDERS GAME *************  " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "==========================================================" << endl;
		cout << "==========================================================" << endl;
		cout << "==========================================================" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "                      LETS START" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "==========================================================" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cout << "==========================================================" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "==========================================================" << endl;



		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 19);
		cout << "Enter player 1 name  " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cin >> names[0];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "Enter player 2 name  " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cin >> names[1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 36);
		cout << "Enter player 3 name  " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
		cin >> names[2];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 88);
		cout << "Enter player 4 name  " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 99);
		cin >> names[3];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 20);
		cout << "\nIts time for the toss";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 21);
		srand(time(0));
		for (int i = 0; i < 4; i++) {// a bool condition for the toss
			bool tossNotFound;
			do {
				tossNotFound = true;
				int temp = rand() % 4;
				for (int j = 0; j < 4; j++) {
					if (toss[j] == temp) {
						break;
					}
					if (j == 3) {
						toss[i] = temp;
						tossNotFound = false;
					}
				}
			} while (tossNotFound);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 22);
		cout << "\nFirst turn: " << names[toss[0]] << "\nSecond turn: " << names[toss[1]] << "\nThird turn: " << names[toss[2]] << "\nFourth turn: " << names[toss[3]] << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
		cout << "\nNote:\nOn board, " << names[toss[0]] << " will be shown as 'a'\n" << names[toss[1]] << " will be shown as 'b'\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 24);
		cout << names[toss[2]] << " will be shown as 'c'\n" << names[toss[3]] << " will be shown as 'd'\n" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		Sleep(3000);
		system("cls");
		for (int i = 1; i <= 100; i++) { // Initially giving all position of P and C empty i.e ' ' .
			player1[i] = ' ';
			player2[i] = ' ';
			player3[i] = ' ';
			player4[i] = ' ';

		}
		for (int i = 1; i <= 100; i++) { // Initially giving all snakes and ladders value double space i.e "  " .
			snakes[i] = "  ";
		}

		// Generating random snakes and ladders position for every new match
		int s1 = rand() % (98) + 12;
		int s2 = rand() % (88) + 6;
		int s3 = rand() % (77) + 4;
		int s4 = rand() % (66) + 3;
		int s5 = rand() % (55) + 1;
		int l1 = rand() % (89) + 6;
		int l2 = rand() % (79) + 5;
		int l3 = rand() % (66) + 4;
		int l4 = rand() % (59) + 3;
		int l5 = rand() % (49) + 2;


		// Checking if Snake and ladder do not come at same place
		while (s1 == l1 && s1 == l2 && s1 == l3 && s1 == l4 && s1 == l5
			&& s2 == l1 && s2 == l2 && s2 == l3 && s2 == l4 && s2 == l5
			&& s3 == l1 && s3 == l2 && s3 == l3 && s3 == l4 && s3 == l5
			&& s4 == l1 && s4 == l2 && s4 == l3 && s4 == l4 && s4 == l5
			&& s5 == l1 && s5 == l2 && s5 == l3 && s5 == l4 && s5 == l5)
		{
			int s1 = rand() % (98) + 12;
			int s2 = rand() % (88) + 6;
			int s3 = rand() % (77) + 4;
			int s4 = rand() % (66) + 3;
			int s5 = rand() % (55) + 2;

			int l1 = rand() % (89) + 6;
			int l2 = rand() % (79) + 5;
			int l3 = rand() % (66) + 4;
			int l4 = rand() % (59) + 3;
			int l5 = rand() % (49) + 2;

		}

		snakes[s1] = "S1";
		snakes[s2] = "S2";
		snakes[s3] = "S3";
		snakes[s4] = "S4";
		snakes[s5] = "S5";



		snakes[l1] = "L1";
		snakes[l2] = "L2";
		snakes[l3] = "L3";
		snakes[l4] = "L4";
		snakes[l5] = "L5";

		board();
		// dice roll for 4 player on the board 

		while (p1 != 100 || p2 != 100 || p3 != 100 || p4 != 100) {
			player1[p1] = ' ';
			player2[p2] = ' ';
			player3[p3] = ' ';
			player4[p4] = ' ';

			if (!won1) {
				system("Color 0B");
				cout << "Press 'a' to roll dice : ";

				cin >> n;
				if (n == 'a') {
					moves1++;
					tie(p1, startp1) = move(p1, startp1, 'a'); // making a tuple of returend tupple
					tie(p2, p3, p4, player2[p1], player3[p1], player4[p1]) = CheckPosition(p1, p2, p3, p4, player2[p1], player3[p1], player4[p1]);
				}
			}

			if (!won2) {
				system("Color 0D");
				cout << "Press 'b' to roll dice : ";

				cin >> n;
				if (n == 'b') {
					moves2++;
					tie(p2, startp2) = move(p2, startp2, 'b');
					tie(p1, p3, p4, player1[p2], player3[p2], player4[p2]) = CheckPosition(p2, p1, p3, p4, player1[p2], player3[p2], player4[p2]);
				}
			}

			if (!won3) {
				system("Color 0E");
				cout << "Press 'c' to roll dice : ";

				cin >> n;
				if (n == 'c') {
					moves3++;
					tie(p3, startp3) = move(p3, startp3, 'c');
					tie(p1, p2, p4, player1[p3], player2[p3], player4[p3]) = CheckPosition(p3, p1, p2, p4, player1[p3], player2[p3], player4[p3]);
				}
			}

			if (!won4) {
				system("Color 0F");
				cout << "Press 'd' to roll dice : ";

				cin >> n;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				if (n == 'd') {
					moves4++;
					tie(p4, startp4) = move(p4, startp4, 'd');
					tie(p1, p2, p3, player1[p4], player2[p4], player3[p4]) = CheckPosition(p4, p1, p2, p3, player1[p4], player2[p4], player3[p4]);
				}
			}

			player1[p1] = 'a';
			player2[p2] = 'b';
			player3[p3] = 'c';
			player4[p4] = 'd';

			board();// function condition for player draw and win if he gets 100
			// also player gift condition
			check_location(p1, p2, p3, p4, s1, s2, s3, s4, s5, l1, l2, l3, l4, l5);

			if (p1 == 100 && p2 == 100 && p3 == 100 && p4 == 100
				&& moves1 == moves2 && moves2 == moves3 && moves3 == moves4) {
				cout << "DRAW!!!";
			}
			else {
				if (p1 == 100) {
					if (!won1) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 33);
						cout << names[toss[0]] << " Has Won in " << moves1 << " moves!!!" << endl;
						won1 = true;
					}
					if (!giftGiven) {
						tie(p2, p3, p4, t) = winGift(names[toss[1]], names[toss[2]], names[toss[3]], p2, p3, p4);
						giftGiven = true;
						player1[t] = ' ';
						player2[t] = ' ';
						player3[t] = ' ';
						player4[t] = ' ';
					}
				}
				if (p2 == 100) {
					if (!won2) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
						cout << names[toss[1]] << " Has Won in " << moves2 << " moves!!!" << endl;
						won2 = true;
					}
					if (!giftGiven) {
						tie(p1, p3, p4, t) = winGift(names[toss[0]], names[toss[2]], names[toss[3]], p1, p3, p4);
						giftGiven = true;
						player1[t] = ' ';
						player2[t] = ' ';
						player3[t] = ' ';
						player4[t] = ' ';
					}
				}
				if (p3 == 100) {
					if (!won3) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 35);
						cout << names[toss[2]] << " Has Won in " << moves3 << " moves!!!" << endl;
						won3 = true;
					}
					if (!giftGiven) {
						tie(p1, p2, p4, t) = winGift(names[toss[0]], names[toss[1]], names[toss[3]], p1, p2, p4);
						giftGiven = true;
						player1[t] = ' ';
						player2[t] = ' ';
						player3[t] = ' ';
						player4[t] = ' ';
					}
				}
				if (p4 == 100) {
					if (!won4) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 36);
						cout << names[toss[3]] << " Has Won in " << moves4 << " moves!!!" << endl;
						won4 = true;
					}
					if (!giftGiven) {
						tie(p1, p2, p3, t) = winGift(names[toss[0]], names[toss[1]], names[toss[2]], p1, p2, p3);
						giftGiven = true;
						player1[t] = ' ';
						player2[t] = ' ';
						player3[t] = ' ';
						player4[t] = ' ';
					}
				}
			}
		}
	}

	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 38);
		cout << "Wrong input";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}

void board() {
	// a joint board for all 4 players 

	cout << " ______________________________________________________________________" << endl;
	cout << "|  " << "100  " << "|  " << "99  " << "|  " << "98  " << "|  " << "97  " << "|  " << "96  " << "|  " << "95  " << "|  " << "94  " << "|  " << "93  " << "|  " << "92  " << "|  " << "91  |" << endl;
	cout << "|" << snakes[100] << player1[100] << player2[100] << player3[100] << player4[100] << " |" << snakes[99] << player1[99] << player2[99] << player3[99] << player4[99] << "|" << snakes[98] << player1[98] << player2[98] << player3[98] << player4[98] << "|" << snakes[97] << player1[97] << player2[97] << player3[97] << player4[97] << "|" << snakes[96] << player1[96] << player2[96] << player3[96] << player4[96] << "|" << snakes[95] << player1[95] << player2[95] << player3[95] << player4[95] << "|" << snakes[94] << player1[94] << player2[94] << player3[94] << player4[94] << "|" << snakes[93] << player1[93] << player2[93] << player3[93] << player4[93] << "|" << snakes[92] << player1[92] << player2[92] << player3[92] << player4[92] << "|" << snakes[91] << player1[91] << player2[91] << player3[91] << player4[91] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "81   " << "|  " << "82  " << "|  " << "83  " << "|  " << "84  " << "|  " << "85  " << "|  " << "86  " << "|  " << "87  " << "|  " << "88  " << "|  " << "89  " << "|  " << "90  |" << endl;
	cout << "|" << snakes[81] << player1[81] << player2[81] << player3[81] << player4[81] << " |" << snakes[82] << player1[82] << player2[82] << player3[82] << player4[82] << "|" << snakes[83] << player1[83] << player2[83] << player3[83] << player4[83] << "|" << snakes[84] << player1[84] << player2[84] << player3[84] << player4[84] << "|" << snakes[85] << player1[85] << player2[85] << player3[85] << player4[85] << "|" << snakes[86] << player1[86] << player2[86] << player3[86] << player4[86] << "|" << snakes[87] << player1[87] << player2[87] << player3[87] << player4[87] << "|" << snakes[88] << player1[88] << player2[88] << player3[88] << player4[88] << "|" << snakes[89] << player1[89] << player2[89] << player3[89] << player4[89] << "|" << snakes[90] << player1[90] << player2[90] << player3[90] << player4[90] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "80   " << "|  " << "79  " << "|  " << "78  " << "|  " << "77  " << "|  " << "76  " << "|  " << "75  " << "|  " << "74  " << "|  " << "73  " << "|  " << "72  " << "|  " << "71  |" << endl;
	cout << "|" << snakes[80] << player1[80] << player2[80] << player3[80] << player4[80] << " |" << snakes[79] << player1[79] << player2[79] << player3[79] << player4[79] << "|" << snakes[78] << player1[78] << player2[78] << player3[78] << player4[78] << "|" << snakes[77] << player1[77] << player2[77] << player3[77] << player4[77] << "|" << snakes[76] << player1[76] << player2[76] << player3[76] << player4[76] << "|" << snakes[75] << player1[75] << player2[75] << player3[75] << player4[75] << "|" << snakes[74] << player1[74] << player2[74] << player3[74] << player4[74] << "|" << snakes[73] << player1[73] << player2[73] << player3[73] << player4[73] << "|" << snakes[72] << player1[72] << player2[72] << player3[72] << player4[72] << "|" << snakes[71] << player1[71] << player2[71] << player3[71] << player4[71] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "61   " << "|  " << "62  " << "|  " << "63  " << "|  " << "64  " << "|  " << "65  " << "|  " << "66  " << "|  " << "67  " << "|  " << "68  " << "|  " << "69  " << "|  " << "70  |" << endl;
	cout << "|" << snakes[61] << player1[61] << player2[61] << player3[61] << player4[61] << " |" << snakes[62] << player1[62] << player2[62] << player3[62] << player4[62] << "|" << snakes[63] << player1[63] << player2[63] << player3[63] << player4[63] << "|" << snakes[64] << player1[64] << player2[64] << player3[64] << player4[64] << "|" << snakes[65] << player1[65] << player2[65] << player3[65] << player4[65] << "|" << snakes[66] << player1[66] << player2[66] << player3[66] << player4[66] << "|" << snakes[67] << player1[67] << player2[67] << player3[67] << player4[67] << "|" << snakes[68] << player1[68] << player2[68] << player3[68] << player4[68] << "|" << snakes[69] << player1[69] << player2[69] << player3[69] << player4[69] << "|" << snakes[70] << player1[70] << player2[70] << player3[70] << player4[70] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "60   " << "|  " << "59  " << "|  " << "58  " << "|  " << "57  " << "|  " << "56  " << "|  " << "55  " << "|  " << "54  " << "|  " << "53  " << "|  " << "52  " << "|  " << "51  |" << endl;
	cout << "|" << snakes[60] << player1[60] << player2[60] << player3[60] << player4[60] << " |" << snakes[59] << player1[59] << player2[59] << player3[59] << player4[59] << "|" << snakes[58] << player1[58] << player2[58] << player3[58] << player4[58] << "|" << snakes[57] << player1[57] << player2[57] << player3[57] << player4[57] << "|" << snakes[56] << player1[56] << player2[56] << player3[56] << player4[56] << "|" << snakes[55] << player1[55] << player2[55] << player3[55] << player4[55] << "|" << snakes[54] << player1[54] << player2[54] << player3[54] << player4[54] << "|" << snakes[53] << player1[53] << player2[53] << player3[53] << player4[53] << "|" << snakes[52] << player1[52] << player2[52] << player3[52] << player4[52] << "|" << snakes[51] << player1[51] << player2[52] << player3[52] << player4[52] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "41   " << "|  " << "42  " << "|  " << "43  " << "|  " << "44  " << "|  " << "45  " << "|  " << "46  " << "|  " << "47  " << "|  " << "48  " << "|  " << "49  " << "|  " << "50  |" << endl;
	cout << "|" << snakes[41] << player1[41] << player2[41] << player3[41] << player4[41] << " |" << snakes[42] << player1[42] << player2[42] << player3[42] << player4[42] << "|" << snakes[43] << player1[43] << player2[43] << player3[43] << player4[43] << "|" << snakes[44] << player1[44] << player2[44] << player3[44] << player4[44] << "|" << snakes[45] << player1[45] << player2[45] << player3[45] << player4[45] << "|" << snakes[46] << player1[46] << player2[46] << player3[46] << player4[46] << "|" << snakes[47] << player1[47] << player2[47] << player3[47] << player4[47] << "|" << snakes[48] << player1[48] << player2[48] << player3[48] << player4[48] << "|" << snakes[49] << player1[49] << player2[49] << player3[49] << player4[49] << "|" << snakes[50] << player1[50] << player2[50] << player3[50] << player4[50] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "40   " << "|  " << "39  " << "|  " << "38  " << "|  " << "37  " << "|  " << "36  " << "|  " << "35  " << "|  " << "34  " << "|  " << "33  " << "|  " << "32  " << "|  " << "31  |" << endl;
	cout << "|" << snakes[40] << player1[40] << player2[40] << player3[40] << player4[40] << " |" << snakes[39] << player1[39] << player2[39] << player3[39] << player4[39] << "|" << snakes[38] << player1[38] << player2[38] << player3[38] << player4[38] << "|" << snakes[37] << player1[37] << player2[37] << player3[37] << player4[37] << "|" << snakes[36] << player1[36] << player2[36] << player3[36] << player4[36] << "|" << snakes[35] << player1[35] << player2[35] << player3[35] << player4[35] << "|" << snakes[34] << player1[34] << player2[34] << player3[34] << player4[34] << "|" << snakes[33] << player1[33] << player2[33] << player3[33] << player4[33] << "|" << snakes[32] << player1[32] << player2[32] << player3[32] << player4[32] << "|" << snakes[31] << player1[31] << player2[31] << player3[31] << player4[31] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "21   " << "|  " << "22  " << "|  " << "23  " << "|  " << "24  " << "|  " << "25  " << "|  " << "26  " << "|  " << "27  " << "|  " << "28  " << "|  " << "29  " << "|  " << "30  |" << endl;
	cout << "|" << snakes[21] << player1[21] << player2[21] << player3[21] << player4[21] << " |" << snakes[22] << player1[22] << player2[22] << player3[22] << player4[22] << "|" << snakes[23] << player1[23] << player2[23] << player3[23] << player4[23] << "|" << snakes[24] << player1[24] << player2[24] << player3[24] << player4[24] << "|" << snakes[25] << player1[25] << player2[25] << player3[25] << player4[25] << "|" << snakes[26] << player1[26] << player2[26] << player3[26] << player4[26] << "|" << snakes[27] << player1[27] << player2[27] << player3[27] << player4[27] << "|" << snakes[28] << player1[28] << player2[28] << player3[28] << player4[28] << "|" << snakes[29] << player1[29] << player2[29] << player3[29] << player4[29] << "|" << snakes[30] << player1[30] << player2[30] << player3[30] << player4[30] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "20   " << "|  " << "19  " << "|  " << "18  " << "|  " << "17  " << "|  " << "16  " << "|  " << "15  " << "|  " << "14  " << "|  " << "13  " << "|  " << "12  " << "|  " << "11  |" << endl;
	cout << "|" << snakes[20] << player1[20] << player2[20] << player3[20] << player4[20] << " |" << snakes[19] << player1[19] << player2[19] << player3[19] << player4[19] << "|" << snakes[18] << player1[18] << player2[18] << player3[18] << player4[18] << "|" << snakes[17] << player1[17] << player2[17] << player3[17] << player4[17] << "|" << snakes[16] << player1[16] << player2[16] << player3[16] << player4[16] << "|" << snakes[15] << player1[15] << player2[15] << player3[15] << player4[15] << "|" << snakes[14] << player1[14] << player2[14] << player3[14] << player4[14] << "|" << snakes[13] << player1[13] << player2[13] << player3[13] << player4[13] << "|" << snakes[12] << player1[12] << player2[12] << player3[12] << player4[12] << "|" << snakes[11] << player1[11] << player2[11] << player3[11] << player4[11] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;
	cout << "|  " << "1    " << "|  " << "2   " << "|  " << "3   " << "|  " << "4   " << "|  " << "5   " << "|  " << "6   " << "|  " << "7   " << "|  " << "8   " << "|  " << "9   " << "|  " << "10  |" << endl;
	cout << "|" << snakes[1] << player1[1] << player2[1] << player3[1] << player4[1] << " |" << snakes[2] << player1[2] << player2[2] << player3[2] << player4[2] << "|" << snakes[3] << player1[3] << player2[3] << player3[3] << player4[3] << "|" << snakes[4] << player1[4] << player2[4] << player3[4] << player4[4] << "|" << snakes[5] << player1[5] << player2[5] << player3[5] << player4[5] << "|" << snakes[6] << player1[6] << player2[6] << player3[6] << player4[6] << "|" << snakes[7] << player1[7] << player2[7] << player3[7] << player4[7] << "|" << snakes[8] << player1[8] << player2[8] << player3[8] << player4[8] << "|" << snakes[9] << player1[9] << player2[9] << player3[9] << player4[9] << "|" << snakes[10] << player1[10] << player2[10] << player3[10] << player4[10] << "|";
	cout << endl << "  ______________________________________________________________________" << endl;

}


int roll() {
	int p1 = 0;
	p1 = rand() % (6) + 1;
	return p1;
}

void check_location(int& p1, int& p2, int& p3, int& p4, int s1, int s2, int s3, int s4, int s5, int l1, int l2, int l3, int l4, int l5)
{// for snake condition 
	int flag = 0;
	int t = 0;
	if (p1 == s1) {
		t = p1;
		p1 = p1 - 5;
		if (p1 < 0) {
			p1 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;
	}
	else if (p1 == s2) {
		t = p1;
		p1 = p1 - 9;
		if (p1 < 0) {
			p1 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p1 << endl;

		flag = 1;
	}
	else if (p1 == s3) {
		t = p1;
		p1 = p1 - 13;
		if (p1 < 0) {
			p1 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p1 << endl;

		flag = 1;
	}
	else if (p1 == s4) {
		t = p1;
		p1 = p1 - 15;
		if (p1 < 0) {
			p1 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;

	}
	else if (p1 == s5) {
		t = p1;
		p1 = p1 - 17;
		if (p1 < 0) {
			p1 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;

	}


	if (p2 == s1) {
		t = p2;
		p2 = p2 - 5;
		if (p2 < 0) {
			p2 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == s2) {
		t = p2;
		p2 = p2 - 9;
		if (p2 < 0) {
			p2 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == s3) {
		t = p2;
		p2 = p2 - 13;
		if (p2 < 0) {
			p2 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == s4) {
		t = p2;
		p2 = p2 - 15;
		if (p2 < 0) {
			p2 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == s5) {
		t = p2;
		p2 = p2 - 17;
		if (p2 < 0) {
			p2 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}


	if (p3 == s1) {
		t = p3;
		p3 = p3 - 5;
		if (p3 < 0) {
			p3 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == s2) {
		t = p3;
		p3 = p3 - 9;
		if (p3 < 0) {
			p3 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == s3) {
		t = p3;
		p3 = p3 - 13;
		if (p3 < 0) {
			p3 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == s4) {
		t = p3;
		p3 = p3 - 15;
		if (p3 < 0) {
			p3 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == s5) {
		t = p3;
		p3 = p3 - 17;
		if (p3 < 0) {
			p3 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}

	if (p4 == s1) {
		t = p4;
		p4 = p4 - 5;
		if (p4 < 0) {
			p4 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == s2) {
		t = p4;
		p4 = p4 - 9;
		if (p4 < 0) {
			p4 = 0;
		}
		system("Color C4");
		Sleep(1000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == s3) {
		t = p4;
		p4 = p4 - 13;
		if (p4 < 0) {
			p4 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == s4) {
		t = p4;
		p4 = p4 - 15;
		if (p4 < 0) {
			p4 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == s5) {
		t = p4;
		p4 = p4 - 17;
		if (p4 < 0) {
			p4 = 0;
		}
		system("Color C4");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into Snake!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}


	// condition for the ladder 


	if (p1 == l1) {
		t = p1;
		p1 = p1 + 4;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;
	}
	else if (p1 == l2) {
		t = p1;
		p1 = p1 + 8;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;
	}
	else if (p1 == l3) {
		t = p1;
		p1 = p1 + 10;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;
	}
	else if (p1 == l4) {
		t = p1;
		p1 = p1 + 12;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;
	}
	else if (p1 == l5) {
		t = p1;
		p1 = p1 + 14;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p1 << endl;
		flag = 1;
	}





	if (p2 == l1) {
		t = p2;
		p2 = p2 + 4;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == l2) {
		t = p2;
		p2 = p2 + 8;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == l3) {
		t = p2;
		p2 = p2 + 10;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}

	else if (p2 == l4) {
		t = p2;
		p2 = p2 + 12;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}
	else if (p2 == l5) {
		t = p2;
		p2 = p2 + 14;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p2 << endl;
		flag = 1;
	}

	if (p3 == l1) {
		t = p3;
		p3 = p3 + 4;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == l2) {
		t = p3;
		p3 = p3 + 8;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == l3) {
		t = p3;
		p3 = p3 + 10;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == l4) {
		t = p3;
		p3 = p3 + 12;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}
	else if (p3 == l5) {
		t = p3;
		p3 = p3 + 14;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p3 << endl;
		flag = 1;
	}


	if (p4 == l1) {
		t = p4;
		p4 = p4 + 4;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == l2) {
		t = p4;
		p4 = p4 + 8;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == l3) {
		t = p4;
		p4 = p4 + 10;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == l4) {
		t = p4;
		p4 = p4 + 12;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}
	else if (p4 == l5) {
		t = p4;
		p4 = p4 + 14;
		system("Color A2");
		Sleep(2000);
		system("Color 7");
		cout << "Player got into LADDER!! at " << t << " you are moved to place" << p4 << endl;
		flag = 1;
	}



	if (flag == 1) {
		player1[p1] = 'a';
		player2[p2] = 'b';
		player3[p3] = 'c';
		player4[p4] = 'd';
		player1[t] = ' ';
		player2[t] = ' ';
		player3[t] = ' ';
		player4[t] = ' ';
		board();
	}

}
