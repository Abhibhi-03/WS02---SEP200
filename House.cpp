//I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments.
//House.cpp
//Abhi Nileshkumar Patel
//apatel477@myseneca.ca
//150046217
//SEP 200 WS02
//Date: 06/03/2022
//=======================

#include "House.h"
#include <iostream>
#include <atomic>
#include <iomanip>

House::House() {//defualt constructor
	this->owner = nullptr;
	this->address = nullptr;
	this->rooms = 0.0;
	this->bathrooms = 0.0;
	this->price = 0.0;
}

House::House(const char* _owner, const char* _address, const double _rooms, const double _bathrooms, const double _price) {
	int length = std::strlen(_owner);
	owner = new char[length + 1];
	std::strcpy(owner, _owner);

	int length2 = std::strlen(_address);
	address = new char[length2 + 1];
	std::strcpy(address, _address);

	rooms = _rooms;
	bathrooms = _bathrooms;
	price = _price;
}

House::House(const House& house) {
	owner = nullptr;
	address = nullptr;
	*this = house; //will invoke copy assignment
}

House::House(House&& house) noexcept { //Move constructor
	*this = std::move(house);//will invoke the move assignment
}

House& House::operator=(const House& house) { //copy assignment
	if (this != &house) {//to prevent copying to yourself
		//shallow copies
		rooms = house.rooms;
		bathrooms = house.bathrooms;
		price = house.price;
		delete[] owner;
		delete[] address;
		//deep copy any resources
		if (house.owner != nullptr) {
			owner = house.owner;
		}
		else owner = nullptr;
		if (house.address != nullptr) {
			address = house.address;
		}
		else address = nullptr;
		return *this;
	}
}

House& House::operator=(House&& house) noexcept { //Move assignment
	if (this != &house) {//to prevent moving to yourself
		//shallow copies
		rooms = house.rooms;
		bathrooms = house.bathrooms;
		price = house.price;
		//remove existing resource
		owner = nullptr;
		address = nullptr;
		//take control of the resource on the rhs
		owner = house.owner;
		address = house.address;
		//Put the rhs into an empty state
		house.owner = nullptr;
		house.address = nullptr;
		house.rooms = 0.0;
		house.bathrooms = 0.0;
		house.price = 0.0;
	}
	return *this;
}

char* House::GetOwner() const {
	return owner;
}

bool House::ChangeOwner(char* owner2) {//Change the owner of house
	bool retVal = false;
	if (owner == nullptr) {
		int len1 = std::strlen(owner2);
		owner = new char[len1 + 1];
		std::strcpy(owner, owner2);
		retVal = true;
	}
	return retVal;
}

bool House::ChangePrice(double price2) {//Change the price of house
	bool retVal = false;
	if (price > 0) {
		price = price2;
		retVal = true;
	}
	return retVal;
}

const House& House::operator+=(double amount) {//increment/decrement the price of the house
	price += amount;
	return *this;
}

void House::DisplayInfo() const {//Display the owner, address, rooms, bathrooms, and price
	std::cout << std::endl;
	if (owner == nullptr) std::cout << "Owner:" << std::setw(6) << "None" << std::endl;
	else std::cout << "Owner: " << std::setw(6) << owner << std::endl;
	if (address == nullptr) std::cout << "Address:" << std::setw(6) << "None" << std::endl;
	else std::cout << "Address: " << std::setw(6) << address << std::endl;
	std::cout << "Rooms:" << std::setw(6) << rooms << std::endl;
	std::cout << "Bathrooms:" << std::setw(6)  << bathrooms << std::endl;
	std::cout << std::fixed << "Price: " << std::setw(6) << std::setprecision(2) << price << std::endl;;
	std::cout << std::endl;
}

House::~House() {//Destructor
	if (owner != nullptr) {
		delete[] owner;
		owner = nullptr;
	}
	if (address != nullptr) {
		delete[] address;
		address = nullptr;
	}
}

bool operator==(const House& house1, const House& house2) {//Confirm if the two houses have the same owner?
	bool prevOwner = false;
	if (strcmp(house1.GetOwner(), house2.GetOwner()) == 0) prevOwner = true;
	return prevOwner;
}

void operator>>(House& house1, House& house2) {//Move contents from the house1 object to the house2 object
	if (&house1 != &house2) (House&&)house2 = (House&&)house1;
}
