#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>
#include <ctype.h>

using namespace std;

const int MAX_WRONG = 7; // Maximum number of wrong answers for Hangman

// Main function
int main()
{
	vector<string> wordList = {"HELLO", "PROGRAM", "BATTLE", "TEXTBOOK", "CLASS", "STRING", "FINAL", "RANDOM", "VIDEO", "SOFTWARE"}; // List of words used in Hangman
	default_random_engine engine(static_cast<unsigned int>(time(0))); // Randomizer engine
	uniform_int_distribution<size_t> dist(0, wordList.size() - 1); // Indexes of word list
	char playing = 'y'; // Indicates if player is still playing

	// Hangman game logic
	while (tolower(playing) == 'y')
	{
		string word = wordList[dist(engine)]; // The word used for this round
		int wrongCount = 0; // Count of wrong guesses
		string guessedWord(word.size(), '?'); // The word guessed
		string input = ""; // Player's input
		string letter = ""; // Player's guess
		string guessedLetters = ""; // Letters guessed so far
		bool win = false; // Win status
		bool firstChar = true; // Indicates that this is the first character

		string::const_iterator it = word.begin(); // Iterator to iterate through the word

		cout << "Guess the word: ";

		// Print out the X to indicate number of characters in the word
		while (it != word.end())
		{
			cout << "X";
			it++;
		}

		cout << "\n\n" << endl;

		while (wrongCount < MAX_WRONG && !win)
		{
			cout << "Guess a letter: " << guessedWord << endl;
			cout << "?";

			getline(std::cin, input); // Get the input
			transform(input.begin(), input.end(), input.begin(), toupper); // Convert input to upper case letters
			
			string::const_iterator iter = input.begin(); // Iterator to iterate through the input
			firstChar = true;

			while(iter != input.end())
			{
				letter = *iter; // Get the letter

				// This is needed to match the formatting if more than one character is input at once
				if (!firstChar)
				{
					cout << "Guess a letter: " << guessedWord << endl;
					cout << "?";
				}

				if (!(isalpha(*iter)))
				{
					cout << "Letters only please\n" << endl;
				}
				else
				{	
					if (guessedLetters.find(letter) != string::npos)
					{
						cout << "'" << letter << "' was already guessed. Try another letter\n" << endl;
					}
					else
					{
						guessedLetters += (" " + letter); // Add letter to list of guessed letters
						size_t position = word.find(letter); // Find index of letter in the word

						if (position == string::npos)
						{
							wrongCount++;
						}
						else
						{
							// Find and replace ? with the letter for each position
							while (position != string::npos)
							{
								guessedWord.replace(position, 1, letter);
								position = word.find(letter, position + 1);
							}
						}

						// Print out the hang man
						switch (wrongCount)
						{
						case 1: cout << "\n o";
							break;
						case 2: cout << "\n o" << endl;
							cout << "/";
							break;
						case 3: cout << "\n o" << endl;
							cout << "/|";
							break;
						case 4: cout << "\n o" << endl;
							cout << "/|\\";
							break;
						case 5: cout << "\n o" << endl;
							cout << "/|\\" << endl;
							cout << " |";
							break;
						case 6: cout << "\n o" << endl;
							cout << "/|\\" << endl;
							cout << " |" << endl;
							cout << "/";
							break;
						case 7: cout << "\n o" << endl;
							cout << "/|\\" << endl;
							cout << " |" << endl;
							cout << "/ \\";
							break;
						}

						cout << "\n\nYour guesses: \n" << guessedLetters << "\n" << endl;
					}
				}

				firstChar = false;
				iter++;
			}

			// Output for when word is guessed correctly
			if (word == guessedWord)
			{
				cout << "Word: " << word << "\n\n\n" << "Congratulations!!! You guessed my word." << endl;
				win = true;
			}

			letter = ""; // Reset letter variable
		}

		// Output for when word is guessed incorrectly
		if (word != guessedWord)
		{
			cout << "\nSorry - you have run out of guesses ;-(" << endl;
			cout << "The correct answer was: " << word << endl;
			cout << "\n...GAME OVER..." << endl;
		}

		cout << "\n\n" << "Play again? (y/n) ";
		std::cin >> playing;
		std::cin.ignore(1, '\n'); // Ignore the remaining newline character
	}

	system("pause");
	return 0;
}