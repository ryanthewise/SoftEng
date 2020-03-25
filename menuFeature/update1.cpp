#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "csvhead.h"
#include "tinyxml2.h"

using namespace tinyxml2;

void searchCity();
void searchState();
void searchZip();
void searchPrice();

int main(){

std::ifstream csvFile("test3bed.csv");

std::string state_name;
std::string city_name;
std::string zip_code;
std::string price;

XMLDocument xmlDoc;				// creates XML Doc to return
    
if(!csvFile.is_open())
     std::cout << "ERROR: File not open" << '\n';
while(csvFile.good()){
    XMLNode * pRoot = xmlDoc.NewElement("Root");	// creates  <root> element
        xmlDoc.InsertFirstChild(pRoot);			// inserts as first element
        std::string line;
        std::getline(csvFile, line);

        XMLElement * pState = xmlDoc.NewElement("state");
        pRoot -> InsertEndChild(pState);


}

//beginnig of user search menu
char option;
std::cout<< "Please select an option from the menu."<< std::endl;
std::cout<<"----------------------MAIN MENU----------------------"<<std::endl;
std::cout<< "(1) Search by City\n(2) Search by Zip Code\n(3) Search by State\n(4) Search by Price Range"<<std::endl;

std::cin>>option;
  std::string citysearch;
  std::string zipsearch;
  std::string statesearch;
  
switch (option) { //add in a loop to return to menu upon invalid
    case '1': //create a searching function outside of main
    std::cout<<"Please type the name of the city you wish to search, followed by the 'enter' key: ";
    std::cin>>citysearch;
    if (citysearch == city_name)
    searchCity(); //returns a list different zipcodes within a city
    //using an if statement, create a "pushback" feature to select from list
    break;

    case '2': //create function outside of main
    std::cout<<"Please type the zip code you wish to search, followed by the 'enter' key: ";
    std::cin>>zipsearch;
    if (zipsearch == zip_code)
    searchZip(); //returns average pricing within specified zipcode
    break;

    case '3': // create funcction outside of main
    std::cout<<"Please type the name of the state you wish to search, followed by the 'enter' key: ";
    std::cin>>statesearch;
    if (statesearch == state_name)
    searchState(); //returns a list of cities within a state
    //create a select option for city, then for zip, return price
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
    break;

    default :
    std:: cout << "Invalid option, please try again."<<std::endl;
}



    return 0;
}

void searchCity(){
//some code that returns list of zipcodes

}

void searchZip(){
//some code that returns prices
}

void searchState(){

}

void searchPrice(){

}