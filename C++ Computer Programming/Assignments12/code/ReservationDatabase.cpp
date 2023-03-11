// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
	ifstream infile("Reservation details.dat", ios::binary | ios::in);
	Reservation Train;
	while (infile.read(reinterpret_cast<char*>(&Train), sizeof(Reservation)))
	{
		reservations.push_back(Train);
	}
	infile.close();
}

void ReservationDatabase::storeReservations()
{
	ofstream outfile("Reservation details.dat", ios::binary | ios::out);
	for (int i = 0; i < reservations.size(); i++)
		outfile.write(reinterpret_cast<char*>(&reservations[i]),sizeof(Reservation));
	outfile.close();
}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "Reservation Cancelled.\n\n";
   storeReservations();
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
   storeReservations();
}

void ReservationDatabase::reduceSeats(string idNumber, string reservationNumber)
{
	int adultNum, concessionNum = 0;
	int adult, concession;
	cout << "How many adult tickets to cancel?";
	cin >> adultNum;
	cout << "How many concession tickets to cancel?";
	cin >> concessionNum;
	adult = searchReservation(idNumber, reservationNumber)->getAdultTickets();
	concession = searchReservation(idNumber, reservationNumber)->getConcessionTickets();
	searchReservation(idNumber, reservationNumber)->setAdultTickets(adult - adultNum);
	searchReservation(idNumber, reservationNumber)->setConcessionTickets(concession - concessionNum);
	displayReservation(idNumber,reservationNumber);
	cout << "\nYou have successfully reduced the number of tickets!\n";
	cin.ignore();
	storeReservations();
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}