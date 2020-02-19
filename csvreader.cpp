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
        XMLNode * pRoot = xmlDoc.NewElement("housing");	// creates  <root> element
        xmlDoc.InsertFirstChild(pRoot);			// inserts as first element

        std::string temp;				// holds the string when parsing
        std::string y;					// not sure yet
        std::ifstream file(fileName);			// Brings in CSV as fileBuffer object (in the stream)

        std::getline(file, temp, '\n');	
	//	while(std::getline(file,temp,','))
	//	{
	//		std::cout << temp <<"\n";
	//	}
				// Stores chars into 'temp' until the first '\n' is found

	XMLElement * root = xmlDoc.NewElement("states"); // creates element <state>
	pRoot -> InsertEndChild(root);			// inserts <state> into end

	XMLElement * state;				// undeclared XMLElements meant to house the future ones
	XMLElement * zip;
	XMLElement * city;


	//const char * zip_id, city_id, state_id;
	
	for(int i = 0; i < r + 1; i++){			// for the total number of r Rows in this CSV file

		
		std::getline(file, temp, '\n');		// Obtain the first row of CSV into a String
		std::stringstream sstream(temp);	// puts into stringstream for manipulation


        std::getline(sstream, temp, ',');	// puts RegionID into temp 
		std::getline(sstream, temp, ',');	// puts RegionName (The actual zip code) into temp
		
		std::string zip_id = temp;
		zip = xmlDoc.NewElement("zip");
		zip -> SetAttribute("code", zip_id.c_str());	// assigns the XMLElement 'zip' with the char* (or string) value of temp 
		
		std::getline(sstream, temp, ',');	// save city value into the temp string
		std::string city_id = temp;
		city = xmlDoc.NewElement("city");
		city ->SetAttribute("city_name", city_id.c_str()); // assign XMLElement

        std::getline(sstream, temp, ',');	// then the state
		std::string state_id =temp;
		state = xmlDoc.NewElement("state");
		state -> SetAttribute("state_name", state_id.c_str());
	        

		for(int j = 0; j < 4; j++){
			std::getline(sstream, temp, ',');
		}

		temp = temp.substr(0, temp.length() - 1);
		
		XMLElement * price = xmlDoc.NewElement("Price");	
		
       	root  -> InsertEndChild(state);		// If SetText in any upper elements, it fucks up the format
		state -> InsertEndChild(city);
		city  -> InsertEndChild(zip);
		zip -> InsertEndChild(price);
		price -> SetText(temp.c_str());		// close them up by inserting them in layers
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
