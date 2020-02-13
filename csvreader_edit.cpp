#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "csvhead.h"
#include "tinyxml2.h"

using namespace tinyxml2;

int main(){
	std::string fileName = "test3bed.csv";
	int r, c;
	r = rows(fileName);
	c = cols(fileName);
	
	XMLDocument xmlDoc;
        XMLNode * pRoot = xmlDoc.NewElement("housing");
        xmlDoc.InsertFirstChild(pRoot);

        std::string temp;
        std::string y;
        std::ifstream file(fileName);

        std::getline(file, temp);

	XMLElement * root = xmlDoc.NewElement("states");
	pRoot -> InsertEndChild(root);
	
	XMLElement * state = xmlDoc.NewElement("state");
		xmlDoc.InsertFirstChild(state);
			for(int i = 0; i <= r; i++){

			std::getline(file, temp);
			std::stringstream sstream(temp);

			std::getline(sstream, temp, ',');
	   	 	state -> SetAttribute("state_name", temp.c_str());

		XMLElement * city = xmlDoc.NewElement("city");
			xmlDoc.InsertFirstChild(city);
				for (int p = 0; p <= r; p++){
			
				std::getline(sstream, temp, ',');
				city -> SetAttribute("city_name", temp.c_str());

				}

		XMLElement * zip = xmlDoc.NewElement("zip");
			xmlDoc.InsertFirstChild(zip);
				for (int l = 0; l <= r; l++){
				
				std::getline(sstream, temp, ',');
				zip -> SetAttribute("code", temp.c_str());
				}	

		for(int j = 0; j <= r - 4; j++){
			std::getline(sstream, temp, ',');
		}

		temp = temp.substr(0, temp.length() - 1);
		XMLElement * price = xmlDoc.NewElement("Price");
		price -> SetText(temp.c_str());
       	 	root  -> InsertEndChild(state);
		state -> InsertEndChild(city);
		city  -> InsertEndChild(zip);
		zip -> InsertEndChild(price);
		sstream.str(std::string());

	}
		
	
	
	



	xmlDoc.SaveFile("attribute_test.xml");

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
