/* This class represents a pixel in a two-dimensional grid */

#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
using namespace std;

class Pixel {
	private:
		int componentLabel;      // Which component is this pixel part of?
		int orderOfDiscovery;    // When was this pixel discovered?
	public:
		Pixel();
		Pixel(double density);
		Pixel(int inComponentLabel);
		int getLabel() const;
		int getOrder() const;
		void setLabel(int inComponentLabel);
		void setOrder(int inOrderOfDiscovery);
		friend ostream& operator<<(ostream& out, const Pixel& right);
};

#endif