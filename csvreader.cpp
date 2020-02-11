#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "csvhead.h"
#include "tinyxml2.h"

using namespace tinyxml2;
	
int main(){
	std::string fileName = "3bed.csv";
	int r, c;
	r = rows(fileName);				// Needed for 'for loop' to iterate over whole file.
						

	c = cols(fileName);				// What will this be for? 
	
	XMLDocument xmlDoc;				// creates XML Doc to return
        XMLNode * pRoot = xmlDoc.NewElement("Root");	// creates  <root> element
        xmlDoc.InsertFirstChild(pRoot);			// inserts as first element

        std::string temp;				// holds the string when parsing
        std::string y;					// not sure yet
        std::ifstream file(fileName);			// Brings in CSV as fileBuffer object (in the stream)

        std::getline(file, temp);			// Stores chars into 'temp' until the first '\n' is found

	XMLElement * root = xmlDoc.NewElement("state"); // creates element <state>
	pRoot -> InsertEndChild(root);			// inserts <state> into end

	XMLElement * state;				// undeclared XMLElements meant to house the future ones
	XMLElement * zip;
	XMLElement * city;
	XMLElement * price;

	for(int i = 0; i <= r; i++){			// for the total number of r Rows in this CSV file

		
		std::getline(file, temp);		// Obtain the first row of CSV into a String
		std::stringstream sstream(temp);	// puts into stringstream for manipulation

        	std::getline(sstream, temp, ',');	// puts RegionID into temp 
		std::getline(sstream, temp, ',');	// puts RegionName (The actual zip code) into temp
		zip = xmlDoc.NewElement(temp.c_str());	// assigns the XMLElement 'zip' with the char* (or string) value of temp 

		std::getline(sstream, temp, ',');	// save city value into the temp string
		city = xmlDoc.NewElement(temp.c_str()); // assign XMLElement

                std::getline(sstream, temp, ',');	// then the state
	        state = xmlDoc.NewElement(temp.c_str());

		for(int j = 0; j <= r - 4; j++){
			std::getline(sstream, temp, ',');
		}

		temp = temp.substr(0, temp.length() - 1);

		price = xmlDoc.NewElement("Price");	
		price -> SetText(temp.c_str());		// close them up by inserting them in layers
       	 	root  -> InsertEndChild(state);		// If SetText in any upper elements, it fucks up the format
		state -> InsertEndChild(city);
		city  -> InsertEndChild(zip);
		zip -> InsertEndChild(price);
		sstream.str(std::string());

	}



	xmlDoc.SaveFile("yolo.xml");

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
