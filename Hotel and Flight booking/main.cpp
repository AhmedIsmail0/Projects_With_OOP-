/***********************************************************************
Matr.-Nr:   3145242
Surname:  Ismail
firstname:  Ahmed
Uni-Email:   ahmed.abdelnaser-saad-ismail@stud.uni-due.de
Course of studis: Computer of Engineering ( software)
***********************************************************************/
#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;
class Date{
private:
	int DaysinMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int year,month,day;
public:
	Date operator +(int n)
	{
		Date result;
		int no=DaysinMonth[month-1];
		int m=day+n;
		if(m<=no)
		{
			result.day=m;
			result.month=month;
			result.year=year;
		}
		else
		{
			result.day=m-no;
			int kk=month+1;
			if(kk==13)
			{
				result.month=1;
				result.year=year+1;
			}
			else
			{
				result.month=kk;
				result.year=year;
			}
		}
		return result;
	}
    friend ostream &operator<<( ostream &output, const Date &D ) {

       output << D.year<<"-";
       if(D.month<10)
    	   output<<"0";
       output<<D.month<<"-";
       if(D.day<10)
    	   output<<"0";
       output<<D.day;
       return output;
    }

    friend istream &operator>>( istream  &input, Date &D ) {
    	char c;
       input>>D.year>>c>>D.month>>c>>D.day;
       return input;
    }

};
enum  Board{
	breakfast=10,no_meals=0,half_board=20,all_inclusive=50
};
double get_price(Board b)
{
	return b;
}
char boar()
{
	char c;
	cout<<"a all inclusive ("<<get_price(all_inclusive)<<" EUR/day)\n";
	cout<<"b breakfast     ("<<get_price(breakfast)<<" EUR/day)\n";
	cout<<"h half board    ("<<get_price(half_board)<<" EUR/day)\n";
	cout<<"n no meals\n";
	cout<<"your choice: ";
	cin>>c;
	return c;
}
void get(Board b)
{
	if(b==all_inclusive)
		cout<<"all inclusive ("<<get_price(all_inclusive)<<" EUR/day and person)\n";
	else if(b==breakfast)
		cout<<"breakfast     ("<<get_price(breakfast)<<" EUR/day and person)\n";
	else if(b==no_meals)
		cout<<"no meals\n";
	else
		cout<<"half board ("<<get_price(half_board)<<" EUR/day and person)\n";
}
class Accomodation{
private:
	double priceNightSingle,priceNightDouble,priceOneDayParking;
	string location;
	Date arrival;
	int nights,singles,doubles;
	Board board;
	bool parking;

public:
	Accomodation(double a,double b,double c)
	{
		priceNightSingle=a;
		priceNightDouble=b;
		priceOneDayParking=c;
		ask_data();
	}
	~Accomodation()
	{
		cout<<"destructor Accomodation "<<location<<" at "<<arrival<<" for "<<get_guests()<<" guests done\n";
	}
	Date get_arrival()
	{
		return arrival;
	}
	Date get_checkout()
	{
		return arrival+nights;
	}
	int get_guests()
	{
		return singles+2*doubles;
	}
	double get_price()
	{
		double k=(double)singles*priceNightSingle+(double)doubles*priceNightDouble;
		if(parking)
			k+=priceOneDayParking;
		double all=singles+2*doubles;
		k+=(double)all*board;
		return (double)nights*k;
	}
	void ask_data()
	{
		cout<<"location of accomodation: ";
		cin>>location;
		cout<<"arrival on (yyyy-mm-dd): ";
		cin>>arrival;
		cout<<"how many nights (maximum 4 weeks): ";
		cin>>nights;
		cout<<"how many single bed rooms ("<<priceNightSingle<<" EUR/night): ";
		cin>>singles;
		cout<<"how many double bed rooms ("<<priceNightDouble<<" EUR/night): ";
		cin>>doubles;
		char b=boar();
		if(b=='h')
			board=half_board;
		else if(b=='n')
			board=no_meals;
		else if(b=='b')
			board=breakfast;
		else
			board=all_inclusive;
		cout<<"with parking place ("<<priceOneDayParking<<" EUR/day; y(es) or n(o)): ";
		parking=0;
		char c;
		cin>>c;
		if(c=='y')
			parking=1;
		cout<<"price: "<<get_price()<<" EUR\n";
	}
	void print()
	{
		cout<<"accomodation at:    "<<location<<"\n";
		cout<<"number of guests:   "<<get_guests()<<"\n";
		cout<<"number of nights:   "<<nights<<"\n";
		cout<<"check-in date:      "<<arrival<<"\n";
		cout<<"check-out date:     "<<get_checkout()<<"\n";
		cout<<"single bed room(s): "<<singles<<" ("<<priceNightSingle<<" EUR/night)\n";
		cout<<"double bed room(s): "<<doubles<<" ("<<priceNightDouble<<" EUR/night)\n";
		cout<<"board:              ";
		get(board);
		cout<<"parking:            ";
		if(parking)
			cout<<"included ("<<priceOneDayParking<<" EUR/day)\n";
		else
			cout<<"no parking place booked\n";
		cout<<"price accomodation: "<<get_price()<<"\n";
	}

};
class  Transport{
public:
	virtual ~Transport()
	{
		cout<<"destructor Transport done\n";
	}
	virtual bool  includedTransfer()
	{
		return 0;
	}
	virtual double get_price()=0;
	virtual void print()=0;
};
class SelfTravel: public Transport{
public:
	SelfTravel(){}
	virtual ~SelfTravel()
	{
		cout<<"destructor SelfTravel done\n";
	}
	virtual double get_price(){return 0.00;}
	virtual void print(){cout<<"self travel ";}
};
class PublicTransport:public Transport{
protected:
	Date departure;
	string code,from,to;
	double priceOneSeat;
	bool firstClass;
public:
	PublicTransport(Date D,string c,string f,string t,double p,bool fi=0)
	{
		departure=D;
		code =c;
		from=f;
		to=t;
		priceOneSeat=p;
		firstClass=fi;
	}
	virtual ~PublicTransport()
	{
		cout<<"destructor PublicTransport ";
		cout<<code<<" at "<<departure<<" from "<<from<<" to "<<to<<" done\n";
	}
	virtual void print()
	{
		cout<<departure<<" "<<code<<" from "<<from<<" to "<<to<<" ";
		if(firstClass)
			cout<<"first class ";
		cout<<"("<<get_price()<<" EUR/person) ";
	}
};
Date need;
class Flight:public PublicTransport{
protected:
	bool transfer;
public:
	Flight(Date D,string c,string f,string t,double p,bool fi=0,bool tr=1) : PublicTransport(need,"","","",0.00,false)
	{
		departure=D;
		code =c;
		from=f;
		to=t;
		priceOneSeat=p;
		firstClass=fi;
		transfer=tr;
	}
	virtual ~Flight()
	{
		cout<<"destructor Flight done\n";
	}
	virtual bool includedTransfer(){return transfer;}
	virtual double get_price()
	{
		if(firstClass)return (double)2*priceOneSeat;
		return priceOneSeat;
	}
	virtual void print()
	{
		cout<<"flight ";
		PublicTransport::print();
	}
};
class Train:public PublicTransport{
protected:
	bool transfer;
public:
	Train(Date D,string c,string f,string t,double p,bool fi=0,bool tr=1) : PublicTransport(need,"","","",0.00,false)
	{
		departure=D;
		code =c;
		from=f;
		to=t;
		priceOneSeat=p;
		firstClass=fi;
		transfer=tr;
	}
	virtual ~Train()
	{
		cout<<"destructor Train done\n";
	}
	virtual bool includedTransfer(){return transfer;}
	virtual double get_price()
	{
		if(firstClass)return (double)1.5*priceOneSeat;
		return priceOneSeat;
	}
	virtual void print()
	{
		cout<<"train ";
		PublicTransport::print();
	}
};
class Request{
private:
	int no;
	static int lastNo;
	Request* next;
	Accomodation* accomodation;
	Transport* transportReturn;
	Transport* transportOutward;
public:
	Request(Accomodation* tmp,Request* tmp2=NULL,Transport* from=NULL,Transport* to=NULL)
	{
		lastNo++;
		no=lastNo;
		next=tmp2;
		accomodation=tmp;
		transportOutward=from;
		transportReturn=to;
	}
	~Request()
	{
		delete accomodation;
		delete transportOutward;
		delete transportReturn;
		cout<<"destructor Request "<<no<<" done\n";
	}
	int get_no()
	{
		return no;
	}
	double get_price()
	{
		double gues=accomodation->get_guests();
		double all_price=gues*(transportOutward->get_price());
		all_price+=gues*(transportReturn->get_price());
		all_price+=accomodation->get_price();
		return all_price;
	}
	void print()
	{
		cout<<"********REQUEST NO: "<<no<<"********\n";
		accomodation->print();
		cout<<"outward journey:    ";
		transportOutward->print();
		if(transportOutward->includedTransfer())
			cout<<"transfer included\n";
		else
			cout<<"no transfer\n";
		cout<<"journey back:       ";
		transportReturn->print();
		if(transportReturn->includedTransfer())
			cout<<"transfer included\n";
		else
			cout<<"no transfer\n";
		cout<<"price total:        "<<get_price()<<" EUR\n\n";
	}
	Request* get_next()
	{
		return next;
	}
	void set_next(Request* tmp)
	{
		next=tmp;
	}
};
class CallCenter{
private:
	Request* head;
public:
	CallCenter(){head=NULL;}
	void append(Request* tmp)
	{
		if(head==NULL)
		{
			head=tmp;
		}
		else
		{
			Request* now=head;
			while(now->get_next()!=NULL)
				now=now->get_next();
			now->set_next(tmp);
		}
	}
	void cancel(Request* tmp)
	{
		Request* now=head;
		Request* pre=NULL;
		if(now!=NULL&&now==tmp)
		{
			head=tmp->get_next();
			delete now;
		}
		else
		{
			while(now!=NULL&&now!=tmp)
			{
				pre=now;
				now=now->get_next();
			}
			if(now==NULL)
				return;
			pre->set_next(now->get_next());
			delete now;
		}
	}
	Request* get_request(int tmp)
	{
		Request* now=head;
		while(now!=NULL&&now->get_no()!=tmp)
			now=now->get_next();
		return now;
	}
	void print_all()
	{
		Request* now=head;
		while(now!=NULL)
		{
			now->print();
			now=now->get_next();
		}
	}
};
void menu()
{
	cout<<"CALL CENTER BOOKING REQUEST\n";
	cout<<"0 end\n";
	cout<<"1 new reservation request standard\n";
	cout<<"2 new reservation request superior\n";
	cout<<"3 show reservation request\n";
	cout<<"4 show all reservation requests\n";
	cout<<"your choice: ";
}
int trans_input(string trans)
{
	int choice;
	cout<<"please choose transport "<<trans<<"\n";
	cout<<"0 self travel\n";
	cout<<"1 by flight\n";
	cout<<"2 by train\n";
	cout<<"your choice: ";
	cin>>choice;
	return choice;
}
Transport* get(int tmp,Date d)
{
	Transport* tmps;
	string code,from,to;
	char first_c;
	bool h=false;
	double price;
	if(tmp==0)
		tmps= new SelfTravel();
	else if(tmp==1)
	{
		cout<<"code of flight: ";
		cin>>code;
		cout<<"airport of departure: ";
		cin>>from;
		cout<<"airport of arrival: ";
		cin>>to;
		cout<<"standard price for one passenger: ";
		cin>>price;
		cout<<"first class ((y)es or (n)o): ";
		cin>>first_c;
		if(first_c=='y')h=true;
		tmps=new Flight(d,code,from,to,price,h);
	}
	else
	{
		cout<<"code of train: ";
		cin>>code;
		cout<<"main train station of departure: ";
		cin>>from;
		cout<<"main train station of arrival: ";
		cin>>to;
		cout<<"first class ((y)es or (n)o): ";
		cin>>first_c;
		cout<<"price for one passenger: ";
		cin>>price;
		if(first_c=='y')h=true;
		tmps=new Train(d,code,from,to,price,h);
	}
	return tmps;
}
int Request::lastNo=0;
int main()
{
	CallCenter call;
	int tmp=1,choice;
	cout<<fixed<<setprecision(2);
	while(tmp)
	{
		menu();
		cin>>tmp;
		if(tmp==1)
		{
			Accomodation* acco=new Accomodation(80.00,150.00,10.00);
			choice=trans_input("outward");
			Transport* fr= get(choice,acco->get_arrival());
			choice=trans_input("return");
			Transport* t= get(choice,acco->get_checkout());
			Request* req=new Request(acco,NULL,fr,t);
			call.append(req);
			cout<<"\n";
		}
		else if(tmp==2)
		{
			Accomodation* acco=new Accomodation(110.00,210.00,10.00);
			choice=trans_input("outward");
			Transport* fr= get(choice,acco->get_arrival());
			choice=trans_input("return");
			Transport* t= get(choice,acco->get_checkout());
			Request* req=new Request(acco,NULL,fr,t);
			call.append(req);
			cout<<"\n";
		}
		else if(tmp==3)
		{
			int num;
			cout<<"number of reservation request: ";
			cin>>num;
			Request* ptr=call.get_request(num);
			if(ptr==NULL)
				cout<<"reservation request not found\n";
			else
			{
				char c;
				ptr->print();
				cout<<"(c)ancel this request or (n)ot: ";
				cin>>c;
				if(c=='c')
				{
					call.cancel(ptr);
				}
			}
			cout<<"\n";
		}
		else if(tmp==4)
		{
			call.print_all();
			cout<<"\n";
		}
	}
	return 0;
}


