// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
	Train temp;
	ifstream infile("Northbound timetable.dat", ios::binary);
	while (infile.read(reinterpret_cast<char *>(&temp), sizeof(Train)))
	{
		northboundTimetable.push_back(temp);
	}
	infile.close();
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{

	originStation = 13 - originStation;
	destinationStation = 13 - destinationStation;
    //找給的departureTime的時間後有沒有車子可以搭
	string departure =departureTimes[departureTime];//自己選的時間
	for (int i = 0; i < northboundTimetable.size(); i++)
	{
		if (getDepartureTimes(northboundTimetable[i].getTrainNumber(),originStation) ==""|| 
			getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation) == "-"||
			getDepartureTimes(northboundTimetable[i].getTrainNumber(), destinationStation) == ""||
			getDepartureTimes(northboundTimetable[i].getTrainNumber(), destinationStation) == "-"
			)//如果起點站沒車或是終點站沒車
		{
			continue;
		}
		for (int j = 0; j < 5; j++)//時間比較
		{
			if (j == 2)//冒號
				continue;
			if (getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation)[j] - '0' > departure[j] -'0')//發車時間大於我選的時間 有車 true
			{
				return true;
			}
			else if (getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation)[j] - '0' == departure[j] - '0')//時間一樣 true
			{
				if(j==4)
				return true;
			}
			else
				break;
		}
	}
	return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
	originStation = 13 - originStation;
	destinationStation = 13 - destinationStation;
	string time = departureTimes[departureTime];
	//亮出前十個車車 先找能用的車有哪些
	vector<Train> departureTrain;
	for (int i = 0; i < northboundTimetable.size(); i++)
	{
		if (getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation) == "" ||
			getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation) == "-" ||
			getDepartureTimes(northboundTimetable[i].getTrainNumber(), destinationStation) == "" ||
			getDepartureTimes(northboundTimetable[i].getTrainNumber(), destinationStation) == "-"
			)//如果起點站沒車或是終點站沒車
		{
			continue;
		}
		for (int j = 0; j < 5; j++)//時間比較
		{
			if (j == 2)//冒號
				continue;
			if (getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation)[j] - '0' > time[j] - '0')//發車時間大於我選的時間 有車 true
			{
				departureTrain.push_back(northboundTimetable[i]);
				break;
			}
			else if (getDepartureTimes(northboundTimetable[i].getTrainNumber(), originStation)[j] - '0' == time[j] - '0')//時間一樣 true
			{
				if (j == 4)
					departureTrain.push_back(northboundTimetable[i]);
			}
			else
				break;
		}
	}
	//車子找完了 排序小到大
	Train temp;
	for (int i = 0; i < departureTrain.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			for (int z = 0; z < 5; z++)
			{
				if (z == 2)
					continue;
				if (getDepartureTimes(departureTrain[j].getTrainNumber(), originStation)[z] - '0' >
					getDepartureTimes(departureTrain[j + 1].getTrainNumber(), originStation)[z] - '0')
				{
					//swap j j+1
					temp = departureTrain[j];
					departureTrain[j] = departureTrain[j + 1];
					departureTrain[j + 1] = temp;
					break;

				}
				else if (getDepartureTimes(departureTrain[j].getTrainNumber(), originStation)[z] - '0' ==
					getDepartureTimes(departureTrain[j + 1].getTrainNumber(), originStation)[z] - '0')
				{
					continue;
				}
				else
				{
					break;
				}

			}
		}
	}
	cout << setw(10) << "Train No." << setw(10) << "Departure" << setw(10) << "Arrival" << endl;
	//排序完 列前面十輛車
	for (int i = 0; i < departureTrain.size(); i++)
	{
		if (i == 10)
			break;
		cout << setw(10) << departureTrain[i].getTrainNumber() << setw(10) << departureTrain[i].getDepartureTimes(originStation)
			<< setw(10) << departureTrain[i].getDepartureTimes(destinationStation) << endl;
	}

}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}