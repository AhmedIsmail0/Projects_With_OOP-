/***********************************************************************
Matr.-Nr:   3145242
Surname:  Ismail
firstname:  Ahmed
Uni-Email:   ahmed.abdelnaser-saad-ismail@stud.uni-due.de
Course of studis: Computer of Engineering ( software)
***********************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Station
{
    string stationName;
    int minutes;
    Station* next;
    Station* previous;
    Station* connection;
};
struct Train
{
    string trainname;
    int leftminutes;
    bool diriction;
    Station* next;
};

Station* generate_metro_line(int lineNumber, int totalStations);
void output(Station *station);
void output_line (Station *firstStation);
void init (Train &train,string name,Station *currentStation );
void output (Train &train);
void output_all_trains (int minutes,Train arr_trains[],int size);
float get_km_of_line(Station* fStation, float averagespeed);
int main()
{
    int firstline,secondline,line_choice,line,line_1,line_2,st_1,st_2,value;
    char choice;
    float avgeragespeed;
    cout<<"seed value of initialisation of random generator ( try 3, 5, 7, ....)?";
    cin>>value;
    srand(value);
    cout<<"input number of stations in line 1:" ;
    cin>>firstline;
    cout<<"input number of stations in line 2:" ;
    cin>>secondline;
    Station* arr_line[2];
    Train arr_trains[2];
    int simtime=0;
    arr_line[0]=generate_metro_line(1,firstline);
    arr_line[1]=generate_metro_line(2,secondline);
    for(int i=0; i<2; i++)
    {
        init(arr_trains[i],("train"+to_string(i+1)),arr_line[i]);
    }
    while(1)
    {
        cout<<"\npress e to end"<<"\n";
        cout<<"press l to line output"<<"\n";
        cout<<"press t to train output"<<"\n";
        cout<<"press 1 to simulate 1 minute"<<"\n";
        cout<<"press k to total km complete outward and return ride of line"<<"\n";
        cout<<"press c to connect option of lines"<<"\n";
        cin>>choice;
        if(choice=='l')
        {
            cout<<"which line? ";
            cin>>line_choice;
            if(line_choice == 1)
            {
                output_line(arr_line[0]);
            }
            else if(line_choice == 2)
            {
                output_line(arr_line[1]);
            }
        }
        else if(choice=='t')
        {
            output_all_trains(simtime,arr_trains,2);
        }
        else if (choice=='1')
        {
            simtime++;
            for(int i=0; i<2; i++)
            {
jump2:
                if(arr_trains[i].diriction == true)
                {
                    if(arr_trains[i].leftminutes == 0)
                    {
                        if(arr_trains[i].next->next == nullptr)
                        {
                            arr_trains[i].diriction = false;
                            goto jump1;
                        }
                        arr_trains[i].leftminutes = arr_trains[i].next->minutes;
                        arr_trains[i].next = arr_trains[i].next->next;
                    }
                }
jump1:
                if(arr_trains[i].diriction == false)
                {
                    if(arr_trains[i].leftminutes == 0)
                    {
                        if(arr_trains[i].next->previous == nullptr)
                        {
                            arr_trains[i].diriction = true;
                            goto jump2;
                        }
                        arr_trains[i].next = arr_trains[i].next->previous;
                        arr_trains[i].leftminutes = arr_trains[i].next->minutes;
                    }
                }
                arr_trains[i].leftminutes--;
            }
            output_all_trains(simtime,arr_trains, 2);

        }
        else if (choice == 'k')
        {
            cout << "which line? ";
            cin >> line;
            cout << "please enter average speed in km/h? ";
            cin >> avgeragespeed;
            if (line == 1)
            {
                cout <<"length of line: "<<get_km_of_line(arr_line[0], avgeragespeed);
            }
            else if (line == 2)
            {
                cout <<"length of line: "<<get_km_of_line(arr_line[1], avgeragespeed);
            }
        }
        else if (choice == 'c')
        {
            cout<<"connection of which two line numbers? \n";
            cin>>line_1>>line_2;
            cout<<"connection at which station number of line1? ";
            cin>>st_1;
            cout<<"connection at which station number of line2? ";
            cin>>st_2;
            if((line_1 ==1 && line_2 == 2) || (line_1 ==2 && line_2== 1))
            {
                Station *station1 = arr_line[0];
                Station *station2 = arr_line[1];
                for(int i=1; i<st_1; i++)
                {
                    station1 = station1->next;
                }
                for(int j=1; j<st_2; j++)
                {
                    station2 = station2->next;
                }
                station1->connection = station2;
                station2->connection = station1;
            }
        }
        else if (choice=='e')
        {
            break;
        }
        else
        {
            cout<<"your choic is wrong:"<<"("<<"choose only one of these characters "<<"\n";
        }
    }
}

Station* generate_metro_line(int lineNumber, int totalStations)
{
    Station *fStation = new Station();

    Station *prev ;

    for (int i = 1; i <= totalStations; i++)
    {
        Station *station = new Station();

        station->stationName = "line " + to_string(lineNumber) + " station " + to_string(i);

        if (i == 1)
        {
            if (totalStations == 1)
            {
                station->minutes = 0;
            }
            else
                station->minutes = rand() % 5 + 1;
            station->previous = NULL;
            station->next = NULL;
            fStation  = station;
        }
        else if (i == totalStations)
        {
            station->minutes = 0;
            station->previous = prev;
            station->next = NULL;
            station->previous->next = station;
        }
        else
        {
            station->minutes = rand() % 5 + 1;
            station->previous = prev;
            station->previous ->next = station;
            station->next = NULL;
        }
        prev = station;
    }
    return fStation;
}
void output(Station *station)
{
    if(station->minutes == 0)
    {
        cout<<station->stationName<<": end station"<<"\n";
    }
    else if (station->connection==nullptr)
    {
        cout<<station->stationName<<": time to next: "<<station->minutes<<" minutes"<<"\n";
    }
    else if(station->connection!=nullptr)
    {
        cout<<station->stationName<<": time to next: "<<station->minutes<<" minutes"<<" (here connection to "<<station->connection->stationName<<")"<<endl;
    }
}

void output_line (Station *fStation)
{
    Station *ptr = fStation;

    while (ptr != NULL)
    {
        output(ptr);
        ptr = ptr->next;
    }

}


void init (Train &train,string name,Station *currentStation )
{
    train.trainname=name;
    train.leftminutes=0;
    train.next=currentStation;
    train.diriction = true;
}
void output (Train &train)
{
    if(train.leftminutes == 0)
    {
        cout<<train.trainname<<" : stop at "<<train.next->stationName<<"\n";
    }
    else
    {
        if(train.diriction == false)
        {

            cout<<train.trainname<<" : "<<train.leftminutes<<" minute(s) to "<<train.next->stationName<<" (on way back)"<<"\n";
        }
        else
        {
            cout<<train.trainname<<" : "<<train.leftminutes<<" minute(s) to "<<train.next->stationName<<"\n";
        }
    }
}
void output_all_trains (int minutes,Train arr_trains[],int size)
{
    cout<<"time simulation: "<<minutes<<"min"<<"\n";
    for(int i=0; i<size; i++)
    {
        output(arr_trains[i]);
    }
}
float get_km_of_line(Station* fStation, float averagespeed)
{
    float time=0;
    float distance=0;
    while (fStation->next != nullptr)
    {
        time = fStation->minutes +time;
        fStation = fStation->next;
    }

    distance = (2*time)*averagespeed /60 ;

    return distance;
}
