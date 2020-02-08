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

        std::string temp;
	std::string y;
	std::ifstream file(fileName);

        std::getline(file, temp);

        std::stringstream sstream(temp);

        std::getline(sstream, temp, '\n');


	XMLElement * z = xmlDoc.NewElement(temp.c_str());
	//pElement -> SetText(temp.c_str());
        pRoot  -> InsertEndChild(z);

        std::getline(sstream, y, ',');


        XMLElement * x = xmlDoc.NewElement("Next");
        x -> SetText(y.c_str());
	z  -> InsertEndChild(x);



	xmlDoc.SaveFile("yolo.xml");



	return 0;
}
