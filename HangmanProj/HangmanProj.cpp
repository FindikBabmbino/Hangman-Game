#include <iostream>
#include <cmath>
using namespace std;

void PlayGame();
void UpdateDrawing(int life);
void UpdateTextScreen(string text,char checkChar,string wordsToDisplay[]);
bool ExitPlaying();
bool GameEnd(int life,int winCount, int guessedString);
string ReturnRandomWord(string Words[],int size);
char GetInput();
void CheckGuess(int &life,int &guessedString,char guessChar,string currentWord);

const int IGNORE_CHARS(256);

int main()
{
	srand((unsigned int)time(NULL));

	do
	{
		PlayGame();
	} while (!ExitPlaying());

}

void PlayGame()
{	
	int life = 6;
	int guessedString = 0;

	string GuessWords[]{ "red","blue","green","yellow","pink"};
	string currentWord = ReturnRandomWord(GuessWords, 5);
	string textToShow[sizeof(currentWord)];

	char playerInput = NULL;


	do
	{
		cout << endl;
		UpdateDrawing(life);
		UpdateTextScreen(currentWord, playerInput, textToShow);

		playerInput = GetInput();
		CheckGuess(life,guessedString,playerInput,currentWord);
	} while (!GameEnd(life,currentWord.length(),guessedString));
}

string ReturnRandomWord(string Words[],int size)
{
	string newChar = Words[rand() % size].c_str();
	return newChar;
}

void UpdateDrawing(int life)
{
	//For the rope 
	for (int i = 0; i < 4; i++)
	{
		cout << "| ";

		if (life <= 5 && i == 0)
		{
			cout << "  O";
		}

		else if (life <= 4 && i == 1)
		{
			cout<< " /";
		}
		if(life <= 3 && i == 1)
		{
			cout<<"|";
		}
		if(life <= 2 && i == 1)
		{
			cout << "/";
		}

		else if(life <=1 && i == 2)
		{
			cout << " /";
		}
		if (life <=0 && i == 2)
		{
			cout << "/";
		}
		cout << endl;
	}
	
}
void UpdateTextScreen(string text,char checkChar,string wordsToDisplay[])
{
	for (int i = 0; i < text.length(); i++)
	{
		if (checkChar == text[i]) 
		{
			wordsToDisplay[i] = text[i];
			cout << wordsToDisplay[i];
			
		} 
		else if (wordsToDisplay[i] == "")
		{
			wordsToDisplay[i] = " _ ";
		} 
	}
}

char GetInput()
{
	bool failure;
	char input;
	do
	{
		failure = false;
		cout << "Please type in your guess: ";
		cin >> input;
		if(isdigit(input))
		{
			cin.clear();

			cout << "Please enter a valid char" << endl;
			failure = true;
		}

	} while (failure);
	return input;
}

bool GameEnd(int life,int winCount ,int guessedString)
{
	if(life<= 0)
	{
		cout << endl;
		cout << "You lost :(" << endl;
		return true;
	}
	else if (guessedString>=winCount)
	{
		cout << endl;
		cout << "You got it :)" << endl;
		return true;
	}
	return false;
}

void CheckGuess(int& life, int& guessedString, char guessChar, string currentWord)
{

	if(currentWord.find(guessChar) != string::npos )
	{
		cout << "You guessed Correctly :)" << endl;
		guessedString++;
		cout << guessedString;
	}
	else
	{
		cout << "You didn't get it right :(" << endl;
		life--;
	}
}




bool ExitPlaying()
{
	char input;
	bool failure;
	do
	{
		failure = false;
		cout << "Do you wish to play again? (y/n) ";
		cin >> input;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "Enter a valid character" << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');
			input = tolower(input);
		}
	} while (failure);
	if (input == 'y') return false;
	else if (input == 'n') return true;
}