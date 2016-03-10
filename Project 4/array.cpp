#include <iostream>
#include <string>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

/* int main()
{
string cast[6] = { "glenn", "carl", "carol", "rick", "maggie", "daryl" };
int j = appendToAll(cast, 2, "!!!");
for (int x = 0; x < 6; x++)
cout << cast[x] << endl;
} */

/* int main()
{
string cast[7] = { "rick", "rick", "rick", "maggie", "rick", "maggie", "daryl" };
string best[3] = { "rick", "maggie", "daryl" };
int j = subsequence(cast, 7, best, 3);
cout << j << endl;
} */

/* int main()
{
string cast[15] = { "xavier", "carl", "daryl", "rick", "michonne", "carol", "maggie", "glenn", "glenn", "abby", "xavier", "daryl", "john", "glen", "brock" };
int j = separator(cast, 13, "fisher");
cout << j << endl;
for (int x = 0; x < 15; x++)
cerr << cast[x] << endl;
} */

int main()
{
	const int arraySize = 12;
	string abc[arraySize] = { "a", "b", "c", "d", "e", "1", "2", "3", "A", "B", "C", "D" };
	string abc1[arraySize] = {"b"};
	string abc2[arraySize] = {};
	int y = separate(abc, 12, "4");
	for (int x = 0; x < arraySize; x++)
		cerr << abc[x];
	cerr << endl;
	cerr << y << endl;
}

int appendToAll(string a[], int n, string value)
{
	if (n < 0)
		return -1;

	for (int index = 0; index < n; index++) // the loop appends the value to the elements
		a[index] = a[index] + value;
	return n;
}

int lookup(const string a[], int n, string target)
{
	for (int index = 0; index < n; index++)
	{
		if (a[index] == target) 
			return index;  // returns a non-positive value only if the target is found
	}
	return -1;
}

int positionOfMax(const string a[], int n)
{
	if (n <= 0)
		return -1;

	int maxPos = 0; // this variable will hold the position of the maximum value

	for (int index = 1; index < n; index++)
		if (a[index] > a[maxPos])
			maxPos = index;
	return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos < 0 || pos >= n)
		return -1;

	string lastString = a[pos]; // holds the eliminated element
	for (int index = pos; index < n - 1; index++)
		a[index] = a[index + 1];
	a[n - 1] = lastString;
	return pos;
}

int rotateRight(string a[], int n, int pos)
{
	if (n < 0 || pos < 0 || pos >= n)
		return -1;

	string firstString = a[pos]; // holds the eliminated element
	for (int index = pos; index > 0; index--)
		a[index] = a[index - 1];
	a[0] = firstString;
	return pos;
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;

	for (int index = 0; index < n / 2; index++) 
	{
		string temporary = a[index];
		a[index] = a[n - 1 - index];
		a[n - 1 - index] = temporary;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	for (int index = 0; index < n1 && index < n2; index++)
		if (a1[index] != a2[index]) // the position is returned only when the corresponding elements dont match
			return index;

	if (n1 < n2)
		return n1;
	else
		return n2;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	int index2 = 0;
	bool firstEncounter = true; // checks if a potential subsequence has been encountered
	int pos;

	if (n2 == 0) // as a sequence of zero elements is a subsequence of any sequence
		return 0;

	for (int index1 = 0; index1 < n1; index1++)
	{
		if (a1[index1] == a2[index2])
		{
			if (firstEncounter)
			{
				pos = index1;
				firstEncounter = false;
			}
			if (index2 == n2 - 1)
				return pos;
			index2++;
		}
		else if (!firstEncounter) 
		{
			index2 = 0; // these statements reset the variables, when an incomplete subsequence is found
			firstEncounter = true;
			index1 = pos;
		}
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	for (int index1 = 0; index1 < n1; index1++)
		for (int index2 = 0; index2 < n2; index2++)
			if (a1[index1] == a2[index2])
				return index1;
	return -1;
}

int separate(string a[], int n, string separator)
{
	if (n < 0)
		return -1;

	string storage;
	int start = 0;

	for (int index = 0; index < n; index++)
	{
		if (a[index] < separator) // places all elements < separator before all other elements
		{
			storage = a[start];
			a[start] = a[index];
			a[index] = storage;
			start++;
		}
	}

	int returnValue = start; // records the position of element that is not < separator

	for (int index = 0; index < n; index++)
	{
		if (a[index] == separator) // places all elements == seperator after the elements < separator
		{
			storage = a[start];
			a[start] = a[index];
			a[index] = storage;
			start++;
		}
	}
	return returnValue;
}