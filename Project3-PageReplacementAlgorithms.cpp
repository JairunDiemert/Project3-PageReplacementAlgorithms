// aurthor Jairun Diemert

#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <algorithm> 


using namespace std;

int countDigit(vector<int>& v)
{
	int maxElement = *max_element(v.begin(), v.end());
	int count = 0;
	while (maxElement != 0) {
		maxElement = maxElement / 10;
		++count;
	}
	return count;
}

void print(vector<int>& v) {

	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
void printWithColumb(vector<int>& v, int columbs) {
	int padding = countDigit(v);
	cout << endl;
	int columbCounter = 1;
	for (int i = 0; i < v.size(); i++) {
		cout << setw(padding) << setfill('0') << v[i] << " ";
		if (columbs == columbCounter) {
			cout << endl;
			columbCounter = 0;
		}
		columbCounter++;
	}
	cout << endl;
}

void print(vector<int>& frames, int page) {

	cout << setfill(' ') << setw(2) << page << " : ";
	for (int i = frames.size() - 1; i >= 0; --i) {
		if (frames[i] == INT_MAX) {
			cout << "* ";
		}
		else {
			cout << frames[i] << " ";
		}
	}
	cout << endl;
}

void print(int pageFaults) {

	cout << endl << "Page Faults: " << pageFaults << endl;
}

int search(vector<int>& v, int index, int value) {

	for (int i = index; i < v.size(); i++) {
		if (v[i] == value) {
			return i;
		}
	}
	return INT_MAX;
}

void FIFO(vector<int>& addressSequence, int numberOfFrames) {

	int pageFaults = 0;

	vector<int> frames(numberOfFrames, INT_MAX);

	cout << endl;

	for (int i = 0; i < addressSequence.size(); i++) {
		int index = search(frames, 0, addressSequence[i]);

		if (index == INT_MAX) {
			frames.erase(frames.begin());
			frames.push_back(addressSequence[i]);
			pageFaults++;
		}
		print(frames, addressSequence[i]);
	}

	print(pageFaults);
	frames.clear();
}

void LRU(vector<int>& addressSequence, int numberOfFrames) {

	int pageFaults = 0;

	vector<int> frames(numberOfFrames, INT_MAX);

	cout << endl;

	for (int i = 0; i < addressSequence.size(); i++) {
		int index = search(frames, 0, addressSequence[i]);

		if (index == INT_MAX) {
			frames.erase(frames.begin());
			frames.push_back(addressSequence[i]);
			pageFaults++;
		}
		else {
			int temp = frames[index];
			frames.erase(frames.begin() + index);
			frames.push_back(temp);
		}
		print(frames, addressSequence[i]);
	}

	print(pageFaults);
	frames.clear();
}
int main(void) {


	int pageSize = 100;
	int numberOfFrames;
	int numberOfPages;
	int numberOfAddresses = 100;
	vector<int> addressSequence(0);
	vector<int> pageString(0);

	int temp;

	srand(time(NULL));
	for (int i = 0; i < numberOfAddresses; i++) {
		int temp = rand() % (10 * pageSize);
		addressSequence.push_back(temp);
	}

	cout << endl << "Please enter the number of pages: ";
	cin >> numberOfPages;
	cout << endl << "Please enter the number of frames: ";
	cin >> numberOfFrames;

	cout << endl << "This is the address sequence assumed inside the program." << endl;
	printWithColumb(addressSequence, 10);

	int previousTemp = -1;
	for (int i = 0; i < numberOfPages; i++) {
		int temp = addressSequence[i] / pageSize;
		if (temp != previousTemp) {
			pageString.push_back(temp);
		}
		previousTemp = temp;
	}
	cout << "This is the reference string. ";
	print(pageString);
	FIFO(pageString, numberOfFrames);
	LRU(pageString, numberOfFrames);
	addressSequence.clear();
	pageString.clear();
}

