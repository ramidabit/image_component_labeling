#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "pixel.h"
using namespace std;

// Default constructor (values overritten)
Pixel::Pixel() {
	componentLabel = 0;
	orderOfDiscovery = 0;
}

// Constructor for pixels
Pixel::Pixel(double density) {
	int densityAsInt = (int)(density * 100);

	// Generate random number from 1 to 100 (inclusive)
	int num = 1 + (rand() % 100);

	// % chance will match the desired density
	if (num <= densityAsInt) {
		componentLabel = 1;
	}
	else {
		componentLabel = 0;
	}

	orderOfDiscovery = 0;
}

// Create a pixel in which the label is known, but is undiscovered
Pixel::Pixel(int inComponentLabel) {
	componentLabel = inComponentLabel;
	orderOfDiscovery = 0;
}

// Accessors for label and order
int Pixel::getLabel() const {
	return componentLabel;
}

int Pixel::getOrder() const {
	return orderOfDiscovery;
}

// Mutators for label and order
void Pixel::setLabel(int inComponentLabel) {
	componentLabel = inComponentLabel;
}

void Pixel::setOrder(int inOrderOfDiscovery) {
	orderOfDiscovery = inOrderOfDiscovery;
}

// Allows for the printing of label and order, separated by a comma
ostream& operator<<(ostream& out, const Pixel& right) {
	out << setw(3) << std::right << right.componentLabel << "," << setw(3) << std::left << right.orderOfDiscovery;
	return out;
}