#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<cstdlib>

#if defined(__linux__)
	#define clrr cout << "\033[2J\033[1;1H"
#elif defined(__WIN32)||defined(WIN32)||defined(__WIN32__)
	#define clrr system("cls")
#else
	#endif

using namespace std;

static float total=0;
int counter=0;
bool keepon=true;

class custom
{
  public:
          vector<pair<string,float>> menuu={{"Americano" ,10},{"Caffe Latte", 15},{"Cafe Mocha" ,15},{"Cafe Au Laut",20},{"Cappucino" ,15},{"Brew Coffee" ,10},{"Double Espresso", 20},{"Espresso",15},{"Espresso Con Panna",20},{"Espresso Macchiato",20},{"Flat White",15},{"Frappe",15},{"Freak Shake",15},{"Irish Latte",20},{"Mocha",15},{"Irish Coffee",15},{"Latte Machiato",20},{"Lungo" ,20},{"Ristretto",20}};
          
          vector<pair<string,float>> typech={{"hot brew",2},{"cold brew",3},{"iced",0}};
          
          vector<pair<string,float>> originch{{"Ethopian",2},{"Sumatra",2},{"Columbian",0}};

          vector<pair<string,float>> beansch{{"Dark roasted",20},{"Medium roasted",10},{"Light roasted",0}};
          
           struct choice
          {
            float price;
            string name;
          };
          int op_typ,op_bea,op_ori,coffe;
          void type();
          void beans();
          void origin();
          void customise();
          choice getcho(vector<pair<string,float>>,int);
};


class menu:public custom
{
public:
void displaymenu();
};

class bill:public menu
{
  public:
  float tot,grandtot;
  void finmes();
  void disbill();
  void calctot();
  void reintialise();
};

bill arr[100];

void bill::reintialise()
{
  tot=0;
  grandtot=0;
  op_typ=3;
  op_ori=3;
  op_bea=3;
}

void bill::calctot()
{
      tot+=getcho(menuu,coffe).price;
      tot+=getcho(typech,op_typ).price;
      tot+=getcho(originch,op_ori).price;
      tot+=getcho(beansch,op_bea).price;
      total+=tot;
}

void bill::disbill()
{
  clrr;
  choice a;
  float tax;
  int ch,dec;
  cout<<"\n-------------------------------------------------------------------------------";
  cout<<"\nOrder summary:";
  for(int i=0;i<=counter;i++)
  {
    a=getcho(menuu,arr[i].coffe);
    cout<<"\nSerial no: "<<i+1<<endl<<left<<setw(20)<<setfill(' ')<<a.name<<"\t$"<<a.price;
    a=getcho(typech,arr[i].op_typ);
    cout<<endl<<left<<setw(20)<<setfill(' ')<<a.name<<"\t$"<<a.price;
    a=getcho(beansch,arr[i].op_bea);
    cout<<endl<<left<<setw(20)<<setfill(' ')<<a.name<<"\t$"<<a.price;
    a=getcho(originch,arr[i].op_ori);
    cout<<endl<<left<<setw(20)<<setfill(' ')<<a.name<<"\t$"<<a.price;
    cout<<"\n-------------------------------------------------------------------------------";
    cout<<left<<setw(20)<<setfill(' ')<<"\nSubtotal"<<"= $"<<arr[i].tot<<endl;
    cout<<"-------------------------------------------------------------------------------";
  }
  cout<<"\n===============================================================================\n";
  cout<<left<<setw(20)<<setfill(' ')<<"Total"<<"= $"<<total<<endl;
  tax=total*0.18;
  cout<<left<<setw(20)<<setfill(' ')<<"Tax @18%"<<"= $"<<tax<<endl;
  grandtot=total+tax;
  cout<<left<<setw(20)<<setfill(' ')<<"GrandTotal"<<"= $"<<grandtot;
  cout<<"\n===============================================================================";
  cout<<"\n1) Add\t2) Remove\t3)CHECKOUT\t0) Cancel";
  cout<<"\nPlease enter your choice: ";
  cin>>ch;
  switch(ch)
  {
    case 1: break;
    case 2:cout<<"From previous list please enter the serial no. of the order to delete: ";
           cin>>dec;
           if(dec>=1&&dec<=counter+1)
            {
              total-=arr[dec-1].tot;
              for(int i=dec-1;i<=counter;i++)
                arr[i]=arr[i+1];
              counter--;
            }
           else
           {
            cout<<"Error in input.";
            cout<<"\n[Press Enter to Re-enter]";
            cin.get();
            disbill();
           }
           if(counter>=0)
            disbill();
           else
           {
            keepon=false;
           }
    break;
    case 3:finmes();
    break;
    case 0:keepon=false;
           finmes();
    break;
    default: cout<<"\nInvalid input."; 
     cout<<"\n[Press Enter to Re-enter]";
     cin.get();
    disbill();
    break;
  }
  }
void bill::finmes()
{
  clrr;
  cout<<"\t\t\tThank You for Visiting us.\n";
  if (keepon)
  {
    cout<<"\t\tPlease pay $"<<grandtot<<" at the counter.\n";
    keepon=false;
  }
  cout<<"\n[Press Enter to Logout]";
  cin.get();
  cin.get();
}

void menu::displaymenu()
{
  clrr;
  cout<<"\n===============================================================================";
  cout<<"\n\n\t\t\t\tWELCOME TO GOLDIE'S CAFE";
  cout<<"\n\n===============================================================================\n";
 for(int i=0;i<menuu.size();i++)
    cout<<i+1<<"\t"<<left<<setw(20)<<setfill(' ')<<menuu[i].first<<" $"<<menuu[i].second<<endl;
  cout<<"Please enter your choice: ";
  cin>>coffe;
  if(coffe>=1&&coffe<=19)
    customise();
  else 
  {
    cout<<"\nInvalid input";
     cout<<"\n[Press Enter to Re-enter]";
     cin.get();
     displaymenu();
  }   
}

custom::choice custom::getcho(vector<pair<string,float>> vec,int ch)
{
  choice a;
  for(int i=0;i<vec.size();i++)
  {
    if(i+1==ch)
    {
      a.name=vec[i].first;
      a.price=vec[i].second;
    }
  }
  return a;
}
void custom::customise()
{
  clrr;
  int ch;
  cout<<"\nCustomise your brew: "<<getcho(menuu,coffe).name;
  cout<<"\n1)Type ("<<getcho(typech,op_typ).name<<")\t2)Beans ("<<getcho(beansch,op_bea).name<<")\t3)Origin ("<<getcho(originch,op_ori).name<<")\n4)Happy with my choices PROCEED.";
  cout<<"\nPlease enter your choice: ";
  cin>>ch;
  switch(ch)
  {
    case 1:type();
    break;
    case 2:beans();
    break;
    case 3:origin();
    break;
    case 4:
    arr[counter].calctot();
    arr[counter].disbill();
    break;
    default: cout<<"\nInvalid input";
     cout<<"\n[Press Enter to Re-enter]";
     cin.get();
     customise();
    break;
  }
}                         

void custom::type()
{
  clrr;
  for(int i=0;i<typech.size();i++)
    cout<<i+1<<"\t"<<left<<setw(20)<<setfill(' ')<<typech[i].first<<"\t$"<<typech[i].second<<endl;
  cout<<"\nPlease enter your choice: ";
  cin>>op_typ;

  if(op_typ>=1&&op_typ<=3)
    customise();
  else
  {
    cout<<"\nInvalid input";
     cout<<"\n[Press Enter to Re-enter]";
     cin.get();
     type();    
  }
}

   
void custom::beans()
{
  clrr;
  for(int i=0;i<beansch.size();i++)
    cout<<i+1<<"\t"<<left<<setw(20)<<setfill(' ')<<beansch[i].first<<"\t$"<<beansch[i].second<<endl;
  cout<<"\nPlease enter your choice: ";
  cin>>op_bea;
 
  if(op_bea>=1&&op_bea<=3)
    customise();
  else
  {
    cout<<"\nInvalid input";
     cout<<"\n[Press Enter to Re-enter]";
     cin.get();
     beans();    
  }
}
   
   
void custom::origin()
{
  clrr;
  for(int i=0;i<originch.size();i++)
    cout<<i+1<<"\t"<<left<<setw(20)<<setfill(' ')<<originch[i].first<<"\t$"<<originch[i].second<<endl;
  cout<<"\nPlease enter your choice: ";
  cin>>op_ori;

  if(op_ori>=1&&op_ori<=3)
    customise();
  else
  {
    cout<<"\nInvalid input";
     cout<<"\n[Press Enter to Re-enter]";
     cin.get();
     origin();    
  }
}

int main()
{
  bool running=true;
  do
  {
    do
    {
      arr[counter].reintialise();
      arr[counter].displaymenu();
      if(!keepon)
        break;
      counter++;
    }while(counter<100);
    if(counter==100)
      cout<<"\n You have exceeded the limit of items in cart. Please start again and make sure number of items<100";
    counter=0;
    total=0;
    keepon=true;
  }while(running);
  return 0;
}