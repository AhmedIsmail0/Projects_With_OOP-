/***********************************************************************
Matr.-Nr:   3145242
Surname:  Ismail
firstname:  Ahmed
Uni-Email:   ahmed.abdelnaser-saad-ismail@stud.uni-due.de
Course of studis: Computer of Engineering ( software)
***********************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

void from_file(string fileName, struct city* cities[], int legnth);
void create_html_file(string fileName, city* cities[], int legnth, int from, int to);
int getNumberFromArray(int myNumbers[5]);
void print(city* cities[], int l, int from, int to);


struct city {
    string name;
    string addition_to_city;
    struct city* next = nullptr;
};


int main()
{

    string postcode;


    string fromString = "";
    string toString = "";

    int fromArray[5] = { 0,0,0,0,0 };
    int toArray[5] = { 9,9,9,9,9 };

    char choice;

    bool quit = false;
    const int legnth = 100000;
    struct city* cities[legnth];

    for (int i = 0; i < legnth; i++)
    {
        cities[i] = nullptr;
    }

    struct city* test = new city();

    string Name_of_file;
    cout << "please input file name: ";
    cin>>Name_of_file;

    from_file(Name_of_file, cities, legnth);
    cout << "read file " << Name_of_file << " ...... done" << endl;

    while (quit != true) {

        cout << "q quit" << "\n"
        << "c city" << "\n"
        << "f from to" << "\n"
        << "w write HTML file" << endl;

        cin >> choice;

        switch (choice) {

        case 'q':

            quit = true;
            break;

        case 'c':

            cout << "please input zip code: ";
            cin >> postcode;

            for (int i = 0; i < postcode.length() && i < 5; i++)
            {
                fromArray[i] = (int)postcode.at(i) - '0';
                toArray[i] = (int)postcode.at(i) - '0';
            }

            print(cities, legnth, getNumberFromArray(fromArray), getNumberFromArray(toArray));
            break;

        case 'f':

            cout << "from which zip code: ";
            cin >> fromString;

            cout << "up to which zip code: ";
            cin >> toString;

            print(cities, legnth, stoi(fromString), stoi(toString));
            break;

        case 'w':

            cout << "please input file name: ";
            cin >> Name_of_file;

            cout << "from which zip code: ";
            cin >> fromString;

            cout << "up to which zip code: ";
            cin >> toString;

            create_html_file(Name_of_file, cities, legnth, stoi(fromString), stoi(toString));

            cout << "start writing HTML file \"" << Name_of_file << "\" ...done" << endl;
            break;

        default:

            cout << "Error!try again!" << endl;
        }
    }

    return 0;
}

ostream& operator << (ostream& output, city* cityname) {

    while (true)
        {
        string name = cityname->name;

        string addition_to_city = cityname->addition_to_city;
        output << name;

        if (addition_to_city != "")
        {
            if (addition_to_city.at(0) != ',')
            output << ' ';
            output << addition_to_city;
        }

        cityname = cityname->next;

        if (cityname == nullptr)
            break;

        output << "| ";
    }

    return output;
}



void from_file(string Name_of_file, struct city* cities[], int length ) {



    string t;
    string x;
    ifstream File;

    File.open(Name_of_file);

    if (File.is_open())
    {
        getline(File, t);

        while (getline(File, x))
        {
            if (x == "")
                continue;
            string pnum="";

            struct city* readCity = new city();
            int i = 0;

            for (i = 0; i < x.length(); i++)

            {
                if (x.at(i) == ';')
                    break;

                readCity->name += x.at(i);
            }
            i++;
            for (i; i < x.length(); i++)

            {
                if (x.at(i) == ';')
                    break;

                readCity->addition_to_city += x.at(i);
            }

            i++;

            for (i; i < x.length(); i++)

            {
                pnum += x.at(i);
                if (x.at(i) == ';')
                    break;
            }
            int postalcode;
            if(pnum!="")
                postalcode = stoi(pnum);

            if (cities[postalcode] == nullptr)

                cities[postalcode] = readCity;

            else

            {

                readCity->next = cities[postalcode];
                cities[postalcode] = readCity;
            }


        }
        File.close();
    }
    else {
        cout << "can't open the file!!";
    }
}

void create_html_file(string Name_of_file, city* cities[], int legnth, int from, int to) {

    ofstream file;

    file.open(Name_of_file);

    file<< "<!DOCTYPE html>" << "\n"<< "<html>" << "\n"<< "<head>" << "\n"
        <<"<title>PLZ in Germany from " << from << " to " << to << "</title>" << "\n"<< "</head>" << "\n"
        << "<body>" << "\n"<< "<h1>PLZ in Germany from " << from << " to " << to << "</h1>" << "\n"
        << "<table border=\"1\">" << "\n"<< "<tr><th>PLZ</th><th>Area</th></tr>" << endl;

    for (int i = from; (i <= to && i < legnth); i++)

    {
        if (cities[i] != nullptr)

        {
            file << "<tr><td>" << i << "</td><td>" << cities[i] << "</td></tr>" << endl;
        }

    }

    file <<endl;
}

void print(city* cities[], int l, int from, int to) {


    for (int i = from; (i <= to && i < l); i++)
    {
        if (cities[i] != nullptr)

        {
            cout << i << " ";
            cout << cities[i] << endl;
        }

    }

}


int getNumberFromArray(int myNumbers[5]) {

    int result = 0;

    for (int i = 0; i < 5; i++)

    {

        result *= 10;
        result += myNumbers[i];

    }

    return result;
}
