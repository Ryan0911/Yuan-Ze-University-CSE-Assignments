#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger( int begin, int end );

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : idNumber(),
     reservationNumber(),
     reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
	cout << "Enter ID Number:";
	cin >> idNumber;
	cout << endl << "Enter Reservation Number:";
	cin >> reservationNumber;
	cout << endl;
	cin.ignore();
	if (reservationDatabase.exist(idNumber, reservationNumber))
	{
		reservationDatabase.displayReservation(idNumber, reservationNumber);
		cout << endl << "Enter Your Choice" << endl;
		cout << "1. Cancellation" << endl;
		cout << "2. Reduce" << endl;
		cout << "3. End" << endl;
		cout << "?";
		int choice = 0;
		cin >> choice;
		cin.ignore();
			switch (choice)
			{
			case 1:
				reservationDatabase.cancelReservation(idNumber, reservationNumber);
				break;
			case 2:
				reservationDatabase.reduceSeats(idNumber,reservationNumber);
				break;
			case 3:
				system("pause");
				return;
				break;
			default:
				break;
			}
	}
	else
		cout<<"Reservation record not found.\n";
	
}