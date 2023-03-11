// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n\n";
   }
   else
      cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
	char station[13][12] = { "","Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung"
	,"Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
	int number = 0;
	cout << "Origin Station" << endl;
	for (int i = 1; i < 13; i++)
	{
		cout << i << ". " << station[i] << endl;
	}
	cout << "?";
	cin >> number;
	reservation.setOriginStation(number);
	cout << "Destination Station" << endl;
	for (int i = 1; i < 13; i++)
	{
		cout << i << ". " << station[i] << endl;
	}
	cout << "?"; 
	cin >> number;
	for (; ; )
	{
		if (number == reservation.getOriginStation())
		{
			cout << "Destination can't same of the origin station." << endl;
			cin >> number;
		}
		else
			break;
	}
	reservation.setDestinationStation(number);
	
	cout << "Departure Time" << endl;
	for (int i = 1; i < 37; i++)
	{
		cout << i << ". " << departureTimes[i] << endl;
	}
	cout << "?";
	cin >> number;
	cin.ignore();
	if(reservation.getOriginStation() > reservation.getDestinationStation())//北上
	{
		
		reservation.setOriginStation(reservation.getOriginStation());
		reservation.setDestinationStation(reservation.getDestinationStation());
		if(northboundTimetable.trainsAvailable(number, reservation.getOriginStation(), reservation.getDestinationStation())==true)
		northboundTimetable.displayComingTrains(number, reservation.getOriginStation(), reservation.getDestinationStation());
		else
		{
			return false;
		}
	}
	else //南下
	{
		if (southboundTimetable.trainsAvailable(number, reservation.getOriginStation(), reservation.getDestinationStation()) == true)
		southboundTimetable.displayComingTrains(number, reservation.getOriginStation(), reservation.getDestinationStation());
		else
		{
			return false;
		}
	}
	cout << "Enter Train Number：";
	char trainNumber[8];
	cin >> trainNumber;
	reservation.setTrainNumber(trainNumber);
	cin.ignore(1024, '\n');
	return true;
}

void MakingReservation::inputReservationDetails()
{
   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";

   int carClass;
   do cout << "\n? ";
   while( ( carClass = inputAnInteger( 1, 2 ) ) == -1 );
   reservation.setCarClass( carClass );

	cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}