#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <vector>
#include "tinyxml2.h"
using namespace tinyxml2;

/*

This main.cpp acts as a a parser for a CVS file and returns an XML

*/

unsigned int rows(std::string);	// returns the number of rows in file

unsigned int cols(std::string);	// returns the number of columns in file

int main()
{
	std::string fileName = "SmallSample.csv";
	int r, c;
	r = rows(fileName);								// Needed for 'for loop' to iterate over whole file.
	// r returns one too many rows or that the first line is completely ignored					

	//c = cols(fileName);								// What will this be for? !!!
	
	std::string STATE[50] = {"AL","AK","AZ","AR","CA","CO","CT","DE","FL","GA","HI","ID","IL","IN","IA","KS",
	"KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA",
	"RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};

	XMLDocument xmlDoc;								// creates XML Doc to return
	XMLNode * pRoot = xmlDoc.NewElement("Root");	// creates  <root> element
	xmlDoc.InsertFirstChild(pRoot);					// inserts as first element

	std::string stringHolder;								// holds the string when parsing
	std::string y;									// not sure yet
	std::ifstream file(fileName);					// Brings in CSV as fileBuffer object (in the stream)

	std::getline(file, stringHolder);						// Stores chars into 'stringHolder' until the first '\n' is found

	XMLElement * root = xmlDoc.NewElement("state"); // creates element <state>
	pRoot -> InsertEndChild(root);					// inserts <state> into end

	XMLElement * state;								// undeclared XMLElements meant to house the future ones
	XMLElement * zip;
	XMLElement * city;
	XMLElement * price;
	std::string stateName;
	int stateCount{-1};
    std::map<std::string, int> theMap;

	//create 50 xml objects belonging to root and add them into root
	for(int z = 0; z < 50; z++){
		state = xmlDoc.NewElement(STATE[z].c_str());
		root->InsertEndChild(state); 
	}

	for(int i = 0; i < r-1; i++){					// for the total number of r Rows in this CSV file (fixd with (r-1))
		
		std::getline(file, stringHolder);				// Obtain the first row of CSV into a String
		std::stringstream sstream(stringHolder);		// puts into stringstream for manipulation


		// let's assume that every zip will be unique

		std::getline(sstream, stringHolder, ',');		// puts RegionID into stringHolder 
		std::getline(sstream, stringHolder, ',');		// puts RegionName (The actual zip code) into stringHolder
		zip = xmlDoc.NewElement(stringHolder.c_str());	// assigns the XMLElement 'zip' with the char* (or string) value of stringHolder 

		std::getline(sstream, stringHolder, ',');		// save city value into the stringHolder string
		city = xmlDoc.NewElement(stringHolder.c_str()); // assign XMLElement

		std::getline(sstream, stringHolder, ',');		// then the state
		//state = xmlDoc.NewElement(stringHolder.c_str());
		stateName = stringHolder;
		for(int j = 0; j < 5; j++)
		{
			std::getline(sstream, stringHolder, ','); // wasteful but gets the 4th item
		}		

		
		stringHolder = stringHolder.substr(0, stringHolder.length()); // gets the whole string (for some reason, length()-1 did not work)

		price = xmlDoc.NewElement("Price");	
		price -> SetText(stringHolder.c_str());		// close them up by inserting them in layers

		state = root->FirstChildElement(stateName.c_str()); // state pointer directed to the <state> children with this Name
		state ->InsertEndChild(city);
		city->InsertEndChild(zip);
		zip->InsertEndChild(price);
		sstream.flush();


		/* Original Pattern 
		// root ->InsertEndChild(state); 
		// state->InsertEndChild(city);
		// city ->InsertEndChild(zip);
		// zip  ->InsertEndChild(price);
		// sstream.str(std::string());
		*/
	}


	xmlDoc.SaveFile("test.xml");

	
	return 0;
}

unsigned int rows(std::string s){
	std::ifstream file(s);
	std::string stringHolder;
	unsigned int count = 0;

	while(std::getline(file, stringHolder)){
		count++;
	}

	return count;
}

unsigned int cols(std::string s){
	std::ifstream file(s);
	std::string stringHolder;
	unsigned int count = 0;
	std::getline(file, stringHolder);
	std::stringstream sstream(stringHolder);

	while(!sstream.eof()){
		std::getline(sstream, stringHolder, ',');
		count++;
	}
	return count;
}
