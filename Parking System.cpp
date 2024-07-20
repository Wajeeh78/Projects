#include<iostream>
#include<string>
using namespace std;
const int Parking_Space = 15;
struct Vehicle
{
    int parking_space;
    string Vehicle_Name;
    int Model;
    string License_Plate;
};
void Parkvehicle(Vehicle veh[], int Parking_Space[15])
{
    int i;
    cout<<"---------------------------------------- Car Parking System ----------------------------------------"<<endl<<endl;
    for(i=1;i<=15;i++)
    {
        if(Parking_Space[i]==0)
        {
            cout<<"Enter your Vehicle Name: ";
            cin.ignore();
            getline(cin, veh[i].Vehicle_Name);
            cout<<"Enter your Vehicle Model: ";
            cin>>veh[i].Model;
            cout<<"Enter your License Plate: ";
            cin.ignore();
            getline(cin, veh[i].License_Plate);
            veh[i].parking_space=i;
            Parking_Space[i]=1;  
            cout<<endl<<endl<<"Car parked in space "<<veh[i].parking_space<<endl<<endl;
            cout<<"\t\t\t\t _________"<<endl;
            cout<<"\t\t\t\t        Parking Ticket "<<endl<<endl;
            cout<<"\t\t\t\t Ticket No:       "<<veh[i].parking_space<<endl;
            cout<<"\t\t\t\t Vehicle Name:    "<<veh[i].Vehicle_Name<<endl;
            cout<<"\t\t\t\t License Plate:   "<<veh[i].License_Plate<<endl;
            cout<<"\t\t\t\t Vehicle Model:   "<<veh[i].Model<<endl;
            cout<<"\t\t\t\t _________"<<endl<<endl;
            break;
        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl<<endl;
}
void curr_available_spaces(const int Parking_Space[15])
{
    int j;
    cout<<"----------------------------------------- Current Available Space -----------------------------------"<<endl<<endl;
    for(j=1;j<=15;j++)
    {
        if(Parking_Space[j]==0)
        {
            cout<<"Parking Space "<<j<<" is available\n";
            break;
        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl<<endl;
}
void all_available_spaces(const int Parking_Space[15])
{
    int j;
    cout<<"------------------------------------------- All Available Space -------------------------------------"<<endl<<endl;
    for(j=1;j<=15;j++)
    {
        if(Parking_Space[j]==0)
        {
            cout<<"Parking Space "<<j<<" is available\n";
        }
    }
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl<<endl;
}
int main()
{
    int p[15] = {0}; 
    Vehicle veh[15];
    int choice;
    char ch;
    do
    {
        cout<<endl<<endl<<"------------------------------------Parking Lot Management System------------------------------------"<<endl<<endl;
        cout<<"1. Find an available parking space"<<endl;
        cout<<"2. Park a car"<<endl;
        cout<<"3. Display available parking spaces"<<endl;
        cout<<endl<<"Enter your choice: ";
        cin>>choice;
        if(choice==1)
            curr_available_spaces(p);
        else if(choice == 2)
            Parkvehicle(veh, p);
        else if(choice == 3)
            all_available_spaces(p);
        else
            cout<<"Invalid Entry.";
        cout<<"Do you want to Repeat the Process? (Y/N): ";
        cin>>ch;
    } 
	while((ch=='Y')||(ch=='y'));

    return 0;
}