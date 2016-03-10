#include <iostream>
#include <string>
using namespace std;

int main()
{
	int minutes;
	int texts;
	string name;
	int month;

	int a = 0;
	int b = 0;
	int c = 0;

	double costA = 0;
	double costB = 0;
	double total = 0;

	cout << "Minutes used: ";
	cin >> minutes;

	cout << "Text messages: ";
	cin >> texts;

	cin.ignore(10000, '\n');

	cout << "Customer name: ";
	getline(cin, name);

	cout << "Month number (1=Jan, 2=Feb, etc.): ";
	cin >> month;

	cout << "---" << endl;

	if (minutes < 0)
	{
		cout << "The number of minutes used must be nonnegative." << endl;
	}
	else
	{
		if (texts < 0)
		{
			cout << "The number of text messages must be nonnegative." << endl;
		}
		else
		{
			if (name == "")
			{
				cout << "You must enter a customer name." << endl;
			}
			else
			{
				if (month < 1 || month > 12)
				{
					cout << "The month number must be in the range 1 through 12." << endl;
				}
				else
				{
					if (minutes > 500)
					{
						a = minutes - 500;
					}
					if (texts > 200)
					{
						b = texts - 200;
						if (texts > 400)
						{
							b = 200;
							c = texts - 400;
						}
					}
					costA = 0.45*a;
					if (month < 6 || month > 9)
					{
						costB = 0.03*b + 0.11*c;
					}
					else
					{
						costB = 0.02*b + 0.11*c;
					}
					total = 40 + costA + costB;

					cout.setf(ios::fixed);
					cout.precision(2);

					cout << "The bill for " << name << " is $" << total << endl;
				}
			}
		}
	}
}