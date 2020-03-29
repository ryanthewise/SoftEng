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

void searchCity(std::string, std::string);	//currently being used for both state and city search
void searchState();				//might be deleted
void searchZip();				//needs some love
void searchPrice();				//also needs some love

int main(int argc, char *argv[])
{
	std::string fileName = argv[1];
	int r, c;
	r = rows(fileName);							// Needed for 'for loop' to iterate over whole file.
	// r returns one too many rows or that the first line is completely ignored					

	//c = cols(fileName);								// What will this be for? !!!
	
	std::string STATE[51] = {"AL","AK","AZ","AR","CA","CO","CT","DC","DE","FL","GA","HI","ID","IL","IN","IA","KS",
	"KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA",
	"RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};

	std::string state_name;
	std::string city_name;
	std::string zip_code;
	std::string price1;

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
	std::string stateName,cityName;
	int stateCount{-1};
	std::map<std::string, int> theMap;

	//create 51 xml objects belonging to root and add them into root
	for(int z = 0; z < 51; z++){
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
		cityName = stringHolder;
		std::getline(sstream, stringHolder, ',');		// then the state
		//state = xmlDoc.NewElement(stringHolder.c_str());
		stateName = stringHolder;
		for(int j = 0; j < 4; j++)
		{
			std::getline(sstream, stringHolder, ','); // wasteful but gets the 4th column item
		}		

		
		stringHolder = stringHolder.substr(0, stringHolder.length()); // gets the whole string (for some reason, length()-1 did not work)

		price = xmlDoc.NewElement("Price");	
		price -> SetText(stringHolder.c_str());		// close them up by inserting them in layers

		state = root->FirstChildElement(stateName.c_str()); // state pointer directed to the <state> children with this Name
		
		// This method checks if a state has the city or not
		if((state->FirstChildElement( cityName.c_str() )) == NULL){
			state->InsertEndChild(city);
		}
		else{
			city = state->FirstChildElement(cityName.c_str());
		}
		//state ->InsertEndChild(city);
		city->InsertEndChild(zip);
		zip->InsertEndChild(price);
		sstream.flush();
		
	}
	
	state = nullptr;
	zip = nullptr;
	city = nullptr;
	price = nullptr;
	
	xmlDoc.SaveFile("Results.xml");

	// Currently the Search Functionality. Very Simple ##Jacob Search##
/*
	std::cout<<"State Abberviation: ";
	std::string searchState,searchCity,searchZip; std::getline(std::cin,searchState);
	if(root->FirstChildElement(searchState.c_str())->FirstChildElement() == NULL){
		std::cout <<"No Results\n";
	}
	else{
		std::cout<<"\nCity Name: "; std::getline(std::cin,searchCity);
		if(root->FirstChildElement(searchState.c_str())->FirstChildElement(searchCity.c_str()) == NULL){
			std::cout <<"No Results\n";
		}
		else{
			std::cout<<"\nZip Code: "; std::cin >>searchZip;
			if(root->FirstChildElement(searchState.c_str())->FirstChildElement(searchCity.c_str())->FirstChildElement(searchZip.c_str()) == NULL){
				std::cout <<"No Results\n";
			}
			else{
				XMLText* textNode = root->FirstChildElement(searchState.c_str())->FirstChildElement(searchCity.c_str())->FirstChildElement(searchZip.c_str())->FirstChildElement()->FirstChild()->ToText();
				std::string title;
				title = textNode->Value();
				std::cout<<"Median Price is: " << title;
			}
		}
	}*/
	root = nullptr;


//beginnig of user search menu
	char option;
	char repeat;

	std::string citysearch;
	std::string zipsearch;
	std::string statesearch;

	do {
		std::cout<< "Please select an option from the menu."<< std::endl;
		std::cout<<"----------------------MAIN MENU----------------------"<<std::endl;
		std::cout<< "(1) Search by City\n(2) Search by Zip Code\n(3) Search by State\n(4) Search by Price Range"<<std::endl;

		std::cin>>option;
		switch (option) { //add in a loop to return to menu upon invalid
			case '1': //create a searching function outside of main
		    		std::cout<<"\nPlease type the name of the city you wish to search, followed by the 'enter' key: ";
				std::cin.ignore();
			    	std::getline(std::cin,citysearch);
				if (citysearch.size() > 2)
			    		searchCity(fileName, citysearch); //returns a list different zipcodes within a city
				else
					std::cout << "\nInvalid Entry - Too few characters indicates you are attempting to search by state. Try again with option 3.\n";
			    	//using an if statement, create a "pushback" feature to select from list
			    	std:: cout << "Would you like to search again: enter Y or N.\t";
				std::cin >> repeat;
			    	std::cout << "\n\n";
				break;

			case '2': //create function outside of main
			    	std::cout<<"Please type the zip code you wish to search, followed by the 'enter' key: ";
			    	std::cin>>zipsearch;
			    	if (zipsearch == zip_code)
			    		searchZip(); //returns average pricing within specified zipcode
			    	std:: cout << "Would you like to search again: enter Y or N.\t";
				std::cin >> repeat;
				std::cout << "\n\n";
			    	break;

			case '3': // create funcction outside of main
			    	std::cout<<"Please type the state abbreviation you wish to search, followed by the 'enter' key: ";
                                std::cin.ignore();
                                std::getline(std::cin,citysearch);
                                if (citysearch.size() == 2)
                                        searchCity(fileName, citysearch); //returns a list different zipcodes within a city
                                else
                                        std::cout << "\nInvalid Entry - State abbreviations are 2 characters long.\n";


			    	//create a select option for city, then for zip, return price
			    	std:: cout << "Would you like to search again: enter Y or N.\t";
				std::cin >> repeat;
				std::cout << "\n\n";
			    	break;

			case '4':
			    	char pricerange;
			   	std::cout<<"Please select from the price ranges below: "<<std::endl;
			    	std::cout<<"(a) under 3K\n(b) under 5K\n(c) under 1M"<<std::endl;
			    	std::cin>>pricerange;

			    	switch (pricerange){
				        case 'a': 
					        searchPrice();
				        	break;

				        case 'b':
				        	searchPrice();
				        	break;

				        case 'c':
					        searchPrice();
					        break;

					default: 
					        std::cout<<"Not an option, try again."<<std::endl;
				}
				std:: cout << "Would you like to search again: enter Y or N.\t";
				std::cin >> repeat;
				std::cout << "\n\n";
				break;

			default :
				std:: cout << "Invalid option, please try again: enter Y or N.\t";
				std::cin >> repeat;
				std::cout << "\n\n";
				break;
		}

	}while (repeat == 'Y' || repeat == 'y');

	return 0;
}

void searchCity(std::string f, std::string query){
//some code that returns list of zipcodes
        std::ifstream file(f);
        std::string stringHolder, cityTemp, stateTemp, zipTemp, priceTemp;
	std::vector<std::string> zips, cities, states, prices;
	unsigned int count = 0, input;
	unsigned int columns = cols(f);

        while(std::getline(file, stringHolder)){			//gets contents of file
		std::stringstream sstream(stringHolder);		//puts contents into string stream

                while(!sstream.eof()){
                        std::getline(sstream, stringHolder, ',');	//steps through row one element at a time

			switch(count){
				case 1: //grab zip
					zipTemp = stringHolder;
					break;
				case 2: //grab city
					cityTemp = stringHolder;
					break;
				case 3: //grab state
					stateTemp = stringHolder;
					break;
				default:
					break;
			}

			if(count == columns - 1)
				priceTemp = stringHolder;

			if(query == stringHolder){			//pushes good zips to vector
				input = 1;
			}

			count++;
			if(count == columns){				//resets counter for next row
				if(input == 1){
	                                zips.push_back(zipTemp);
        	                        cities.push_back(cityTemp);
					states.push_back(stateTemp);
                	                prices.push_back(priceTemp);
					input = 0;
				}
				count = 0;
			}
                }
        }
	if (zips.size() == 0){
		std::cout << "No results found for search query: " << query << "\n\n";
	}
	else{
		std::cout << "\nSelect a zipcode from the choices below\n\n";
	}
        for (unsigned int i = 0; i < zips.size(); i++){
                std::cout << "(" << i << ") " << zips[i] << "\n";
		count = i;
	}
	std::cout << "\n";
	if (zips.size() > 0){
		std::cin >> input;
		while(input < 0 || input > count){
			std::cout << "Invalid input: Must be a value listed above. Try again.\n";
			std::cin >> input;
		}
		std::cout << cities[input] << "\t" << states[input] << "\t" << zips[input] << "\t$" << prices[input] << "\n\n";
	}

}

void searchZip(){
//some code that returns prices
}

void searchState(){

}

void searchPrice(){

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
