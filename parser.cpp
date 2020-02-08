#include <iostream>
#include <fstream>
#include <sstream>
#include "csvhead.h"
#include "tinyxml2.h"

using namespace tinyxml2;

int main(){

	XMLDocument xmlDoc;
	XMLNode * pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);

	std::string fileName = "3bed.csv";
	std::ifstream csvFile(fileName);
	int r, c;
	r = rows(fileName);
	c = cols(fileName);
	std::cout << "Rows: " << r << "\nCols: " << c << "\n";
	std::string test;
	std::ifstream file(fileName);
	std::getline(file, test, ',');
	std::cout << test << "\n";


	XMLElement * pElement = xmlDoc.NewElement("Title");
	pElement -> SetText(test.c_str());
	pRoot  -> InsertEndChild(pElement);
	
	xmlDoc.SaveFile("yolo.xml");


/*	std::ifstream csvFile;
	csvFile.open("test.csv");

	while(csvFile.good()){
		std::string line;
		getline(csvFile, line, ',');
		std::cout << line << "\n";
	}*/

	return 0;
}

unsigned int rows(std::string s){
	std::ifstream file(s);
	std::string temp;
	unsigned int count = 0;

	while(std::getline(file, temp)){
		count++;
	}

	return count;
}

unsigned int cols(std::string s){
	std::ifstream file(s);
	std::string temp;
	unsigned int count = 0;
	std::getline(file, temp);
	std::stringstream sstream(temp);

	while(!sstream.eof()){
		std::getline(sstream, temp, ',');
		count++;
	}
	return count;
}
