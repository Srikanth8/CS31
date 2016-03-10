#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isTuneWellFormed(string tune);
char translateNote(int octave, char noteLetter, char accidentalSign);
int translateTune(string S, string& instructions, int& badBeat);

int main()
{
	for (;;)
	{
		string tune;
		string instructions;
		int badBeat = 0;

		cout << "Enter tune: ";
		getline(cin, tune);

		if (tune == "quit")
			break;

		int a = translateTune(tune, instructions, badBeat);

		cout << "translateTune returns " << a << endl;
		if (badBeat > 0)
			cout << "Bad beat is at " << badBeat << endl;
		cout << instructions << endl;
		cout << "The size is " << instructions.size() << endl;
	}
}

char translateNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** translateNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}

bool isTuneWellFormed(string tune)
{
	int Single = 0; // These variables will be used to test the validity of a note
	int Double = 0; // The 'Single', 'Double' and 'Triple' correspond to the no. of characters in the note
	int Triple = 0;

	int index = 0; // indicates position in string
	while (index < tune.size())
	{
		if (tune[index] == '/')
		{
			Single = 1; // A single '/' counts as a 'Single' character
			index += 1;
		}
		else if ('A' <= tune[index] && tune[index] <= 'G')
		{
			if (tune[index + 1] == '#' || tune[index + 1] == 'b')
			{
				if (isdigit(tune[index + 2]))
				{
					Triple = 1; // This point is reached in the code, only if a note has a letter, accidental and number. Hence 'Triple' is changed to 1
					index += 3;
				}
				else
				{
					Double = 1;  // A note without a number is also valid, as octave is 4 by default. 'Double' is changed to 1 as there is a letter and an accidental in this case
					index += 2;
				}
			}
			else if (isdigit(tune[index + 1]))
			{
				Double = 1; // This point is reached when a note only has a letter and a number
				index += 2;
			}
			else
			{
				Single = 1; // Finally if a letter is not followed by an accidental or a number, 'Single' is changed to 1
				index += 1;
			}
		}

		if (Single == 0 && Double == 0 && Triple == 0)
		{
			return false; // If none of the variables were changed to 1, this means invalid characters or an invalid sequence of characters were present in the input. So the function returns false
		}

		Single = Double = Triple = 0; // Resetting variables for next iteration
	}

	if (tune.size() == 0 || tune[tune.size() - 1] == '/')
		return true; // The tune is only confirmed to be well formed if the string is empty or if the last character of the string is a '/' (Note: if the string was empty, the above while loop would have never been executed)
	else
		return false;
}

int translateTune(string tune, string& instructions, int& badBeat)
{
	bool formed = isTuneWellFormed(tune);
	if (formed) // The function attempts to translate the tune only if the tune is well formed
	{
		int length = tune.size();

		char letter;
		int octave = 4; // octave is 4 by default
		char accidental = ' '; // there is no accidental by default

		string Temp = ""; // The 'Temp' string will hold a translated beat temporarily, while the 'Whole' string will hold the entire translated tune
		string Whole = "";

		int noteCounter = 0;
		int beatCounter = 0;

		int index = 0;
		for (; index < length; index++)
		{
			if (tune[index] == '/')
			{
				beatCounter += 1; // if a '/' is present, we know that a beat has ended, so 'beatCounter' is increased by 1
				switch (noteCounter) // Once a beat has ended, the 'Temp' string is added to the 'Whole' string, and then 'Temp' is reset as an empty string 
				{
				case 0:
					Whole += " "; // an empty beat just translates to a space character
					Temp = "";
					break;
				case 1:
					Whole += Temp; // if only one note is present in the beat square brackets are not needed
					Temp = "";
					break;
				default:
					Whole += "[" + Temp + "]"; // square brackets are needed when multiple notes are present in the beat
					Temp = "";
					break;
				}
				noteCounter = 0;
			}
			if ('A' <= tune[index] && tune[index] <= 'G')
			{
				letter = tune[index];
				noteCounter += 1; // once a note letter is encountered, the noteCounter increases by 1

				if (tune[index + 1] == 'b' || tune[index + 1] == '#')
				{
					accidental = tune[index + 1];
					if (isdigit(tune[index + 2]))
					{
						octave = tune[index + 2] - '0'; // This point is reached when there is a note letter, an accidental and a number
					}
					else
					{
						octave = 4; // This point is reached when there is only a note letter and an accidental
					}
				}
				if (isdigit(tune[index + 1]))
				{
					octave = tune[index + 1] - '0'; // This point is reached when there is only a note letter and number
					accidental = ' ';
				}

				if (translateNote(octave, letter, accidental) == ' ')
				{
					badBeat = beatCounter + 1;
					return 2; // The function returns 2 when the 'translateNote' function returns ' ' 
				}

				Temp += translateNote(octave, letter, accidental); // 'Temp' collects the translated notes in a beat
			}
			octave = 4; // Reseting variables for next iteration
			accidental = ' ';
		}
		instructions = Whole;
		return 0;
	}
	return 1;
}