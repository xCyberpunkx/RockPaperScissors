// ProgrammingAdvices.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using namespace std;
#include <Windows.h>

enum enGameChoice{
	rock = 1,
	paper = 2,
	Scissors = 3};
enum enWinner {
	Player = 1,
	Computer = 2,
	Draw = 3
};
struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults {
	short GameNumber = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName;
};
void setWinnerScreenColor(enWinner winner) {
	switch (winner) {
	case(enWinner::Player):
		system("color 2F"); // screen to green
		break;

	case(enWinner::Computer):
		system("color 4F");// screen to red
	case(enWinner::Draw):
		system("color 6F");//screen to yellow
	}
}
string ChoiceName(enGameChoice choice) {
	string arrGameChoice[3] = { "Rock","Paper","Scissors" };
	return arrGameChoice[choice - 1];
}
void PrintRoundResult(stRoundInfo roundinfo) {
	cout << "\n---------------------Round[" << roundinfo.RoundNumber << "]---------------------\n\n";
	cout << "Player Choice: " << ChoiceName(roundinfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(roundinfo.ComputerChoice) << endl;
	cout << " round Winner: " << roundinfo.WinnerName << endl;
	cout << "-----------------------------------------------------------------------------\n" << endl;
	setWinnerScreenColor(roundinfo.Winner);
}
int RandomNumber(int From, int To) {
	int Randnum = rand() % (To - From + 1) + From;
	return Randnum;
}
enGameChoice GenerateComputerChoice() {
	return enGameChoice(RandomNumber(1, 3));
}
enGameChoice ReadPlayerChoice() {
	short choice = 1;
	do {
		cout << "Your Choice: [1]:Rock,[2]:Paper,[3]Scissors\n";
		cin >> choice;

	} while (choice < 1 || choice > 3);
	return enGameChoice(choice);
}
short ReadHowManyRounds() {
	short GameRounds = 1;
	do {
		cout << "How Many Rounds Do You want to play?\n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10 );
	return GameRounds;
}
enWinner WhoWinTheRound(stRoundInfo roundinfo) {
	if (roundinfo.PlayerChoice == roundinfo.ComputerChoice) {
		return Draw;
		
	}
	switch (roundinfo.PlayerChoice) {
	case enGameChoice::paper : 
		if (roundinfo.ComputerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;

		}
		break;
	case enGameChoice::rock:
		if (roundinfo.ComputerChoice == enGameChoice::paper) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (roundinfo.ComputerChoice == enGameChoice::rock) {
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}
enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes) {
	if (PlayerWinTimes > ComputerWinTimes) {
		return enWinner::Player;
	}
	else  if (PlayerWinTimes < ComputerWinTimes) {
		return enWinner::Computer;
	}
	else
		return enWinner::Draw;
}
string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}
stGameResults FillGameResults(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short Drawtimes) {
	stGameResults GameResults;
	GameResults.GameNumber = GameRounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = Drawtimes;
	GameResults.Winner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.Winner);
	return GameResults;
}
string tabs(short numberOfTabs) {
	string t = "";
	for (int i = 0; i < numberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}
void ShowGameOverScreen() {
	cout << tabs(1) << "-----------------------------------------------------------------------------\n\n";
	cout << tabs(1) << "                          +++G A M E   O V E R+++\n\n";
	cout << tabs(1) << "-----------------------------------------------------------------------------\n\n";
}
stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo roundInfo;

	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout << "\nRound [" << GameRound << "] begins:\n";
		roundInfo.RoundNumber = GameRound;
		roundInfo.PlayerChoice = ReadPlayerChoice();
		roundInfo.ComputerChoice = GenerateComputerChoice();
		roundInfo.Winner = WhoWinTheRound(roundInfo);
		roundInfo.WinnerName = WinnerName(roundInfo.Winner);
	
	if (roundInfo.Winner == enWinner::Player) {
		PlayerWinTimes++;
	}
	else if (roundInfo.Winner == enWinner::Computer) {
		ComputerWinTimes++;
	}
	else
		DrawTimes++;
	PrintRoundResult(roundInfo);
	}
	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}
void ShowFinalGameResults(stGameResults gameResults) {
	cout << tabs(1) << "----------------------------------[GAME RESULTS]-----------------------------\n\n" << endl;
	cout << tabs(1) <<"Game Rounds:     " << gameResults.GameNumber <<endl;
	cout << tabs(1) <<"Player Won Times:    " << gameResults.PlayerWinTimes << endl;
	cout << tabs(1) << "Computer Won Times:  " << gameResults.ComputerWinTimes << endl;
	cout << tabs(1) << "Draw Times:     " << gameResults.DrawTimes << endl;
	cout << tabs(1) << "Final Winner:    " << gameResults.WinnerName << endl;
	cout << tabs(1) << "-----------------------------------------------------------------------------\n\n" << endl;
	setWinnerScreenColor(gameResults.Winner);
}
void resetScreen() {
	system("cls");
	system("color 0F");
}
void startGame() {
	char PlayAgain = 'y';
	do{
		resetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout << "Do you want to play again? (y/n): ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	startGame();	
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
