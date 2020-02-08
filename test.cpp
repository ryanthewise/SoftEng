#include <iostream>
#include "tinyxml2.h"
using namespace tinyxml2;


int main(){

	XMLDocument xmlDoc;
	XMLNode * pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);
	XMLElement * pElement = xmlDoc.NewElement("IntValue");
	pElement->SetText(10);
	pRoot->InsertEndChild(pElement);
	pElement = xmlDoc.NewElement("FloatValue");
	pElement->SetText(0.5f);
	pRoot->InsertEndChild(pElement);

	xmlDoc.SaveFile("fuckit.xml");
	



	return 0;

}
