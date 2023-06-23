/***********************************************************************
Matr.-Nr:   3145242
Surname:  Ismail
firstname:  Ahmed
Uni-Email:   ahmed.abdelnaser-saad-ismail@stud.uni-due.de
Course of studis: Computer of Engineering ( software)
***********************************************************************/

#include <iostream>

using namespace std;

const unsigned int row = 13;                                           //step1
const unsigned int col = 26;

char Arr [row][col];                                                   //step2
void fill_with_blank(char x);                                           //step3
void show (string name , string mtr);                                  //step4
void store_array(char selection,int x,char y);

int main()                                                             //step5
{
    string name ="Ahmed Ismail";
    string mtr;
    cout <<"Please enter your matriculation number: "<<"\n";
    cin>> mtr;
    show(name,mtr);
    while(1)
    {

        char selection;
        int storerow;
        char storecolumn;
    cout<<"\n";
    cout<<"press e to end"<<"\n";
    cout<<"press f to fill with blank"<<"\n";
    cout<<"press s to show"<<"\n";
    cout<<"press - to minus"<<"\n";
    cout<<"press + to plus"<<"\n";
    cout<<"press | to vertical line "<<"\n";
    cout<<"press . to blank"<<"\n";
    cout<<"choose what you want: ";
    cin>>selection;

    if(selection=='f')
    {
        char x;
        cout<<"please enter fill character: ";
        //cin>>x;
        fill_with_blank(x);
    }
    else if (selection=='s')
    {
        show (name,mtr);
    }
    else if (selection =='e')
    {
        break;
    }
    else if ((selection =='-')||(selection =='+')||(selection =='|'))
    {
       cout<<"Enter row number: "<<"\n";  //62
       cin>>storerow;
       cout<<"Enter column number: "<<"\n";  //64
       cin>>storecolumn;

       store_array(selection,storerow,storecolumn);
    }
    else if (selection == '.')
    {
       cout<<"Enter row number: "<<"\n";  //71
       cin>>storerow;
       cout<<"Enter column number: "<<"\n";  //73
       cin>>storecolumn;

       store_array(' ',storerow,storecolumn);
    }
    else
    {
        cout<<"your choice is wrong:"<<"("<<"please choose from selected characters"<<")"<<"\n";
    }

    }


    return 0;
}
void fill_with_blank(char x)                                          //step3
{
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            Arr[i][j]=' ';
}
void show (string name, string mtr)                                  //step4
{
    cout<<" MAZE OF \""<<name<<"\""<<"  ("<<mtr<<")"<<"\n";
    cout<<"\t"<<" "<<"abcdefghijklmnopqrstuvwxyz"<<"\n";
    for(int i=0; i<row; i++)
    {
        cout<<i+1<<"\t"<<' ';

        for(int j=0; j<col; j++)
        {
            cout<<Arr[i][j];
        }
        cout<<"\n";
    }
}
void store_array(char selection,int x,char y)
{
    int storerow = x-1;
    char storecolumn= char(y)-97;
    Arr[storerow][storecolumn]=selection;
}
