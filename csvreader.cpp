#include <iostream>
#include <fstream>
#include <sstream>
#include "csvhead.h"
#include "tinyxml2.h"

using namespace tinyxml2;

int main(){
	std::string fileName = "3bed.csv";
	int r, c;
	r = rows(fileName);
	c = cols(fileName);
	
	XMLDocument xmlDoc;
        XMLNode * pRoot = xmlDoc.NewElement("Root");
        xmlDoc.InsertFirstChild(pRoot);

        std::string temp;
        std::string y;
        std::ifstream file(fileName);

        std::getline(file, temp);

	XMLElement * ryan = xmlDoc.NewElement("state");
	pRoot -> InsertEndChild(ryan);

	XMLElement * state;
	XMLElement * zip;
	XMLElement * city;
	XMLElement * price;
	for(int i = 0; i <= r; i++){

		
		std::getline(file, temp);
		std::stringstream sstream(temp);

        	std::getline(sstream, temp, ',');
		std::getline(sstream, temp, ',');
		zip = xmlDoc.NewElement(temp.c_str());

		std::getline(sstream, temp, ',');
		city = xmlDoc.NewElement(temp.c_str());

                std::getline(sstream, temp, ',');
	        state = xmlDoc.NewElement(temp.c_str());


		for(int j = 0; j <= r - 4; j++){
			std::getline(sstream, temp, ',');
		}

		price = xmlDoc.NewElement("Price");
		price -> SetText(temp.c_str());
       	 	ryan  -> InsertEndChild(state);
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
