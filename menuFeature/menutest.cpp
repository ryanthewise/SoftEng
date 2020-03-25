#include <iostream>
int main () {



char option;
std::cout<< "Please select an option from the menu."<< std::endl;
std::cout<<"----------------------MAIN MENU----------------------"<<std::endl;
std::cout<< "(1) Search by City\n(2) Search by Zip Code\n(3) Search by State\n(4) Search by Price Range"<<std::endl;

std::cin>>option;
  std::string citysearch;
  std::string zipsearch;
  std::string statesearch;
  
switch (option) {
    case '1': 
    std::cout<<"Please type the name of the city you wish to search, followed by the 'enter' key: ";
    std::cin>>citysearch;
    break;

    case '2':
    std::cout<<"Please type the zip code you wish to search, followed by the 'enter' key: ";
    std::cin>>zipsearch;
    break;

    case '3':
    std::cout<<"Please type the name of the state you wish to search, followed by the 'enter' key: ";
    std::cin>>statesearch;
    break;

    case '4':
    char pricerange;
    std::cout<<"Please select from the price ranges below: "<<std::endl;
    std::cout<<"(a) under 3K\n(b) under 5K\n(c) under 1M"<<std::endl;
    std::cin>>pricerange;

    switch (pricerange){
        case 'a': 
        break;

        case 'b':
        break;

        case 'c':
        break;

        default: 
        std::cout<<"Not an option, try again."<<std::endl;
    }
    break;

    default :
    std:: cout << "Invalid option, please try again."<<std::endl;
    std::cin>>option;

}

return 0;
}