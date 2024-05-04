#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class contact
{
private:
    char firstName[50], lastName[50], email[50], address[50];
    long long phoneNumber;

public:
    void createContact()
    {
        cout << "\nEnter First Name : ";
        cin >> firstName;

        cout << "Enter Last Name : ";
        cin >> lastName;

        cout << "Enter Eamil : ";
        cin >> email;

        cout << "Enter Address : ";
        cin >> address;

        cout << "Enter Phone Number : ";
        cin >> phoneNumber;
    }

    void showContact()
    {
        cout << "\nName : " << firstName << " " << lastName << endl;
        cout << "Email : " << email << endl;
        cout << "Address : " << address << endl;
        cout << "Phone Number : " << phoneNumber;
    }

    void writeToFile()
    {
        char statement;
        ofstream myFile;
        myFile.open("cms.dat", ios::binary | ios::app);

        do
        {
            createContact();
            myFile.write(reinterpret_cast<char*>(this), sizeof(*this));

            cout << "\nDo you have next data...(y/n) : ";
            cin >> statement;
        }while(statement == 'y');

        cout << "Contact has been successfully save.";
        myFile.close();
    }

    void readOnFile()
    {
        ifstream myFile;
        myFile.open("cms.dat", ios::binary);

        cout << "\nList of Contact\n";
        cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = =";

        while(!myFile.eof())
        {
            if(myFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                showContact();
                cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = =";
            }
        }
        myFile.close();
    }

    void searchOnFile()
    {
        ifstream myFile;
        long long phone;
        cout << "\nEnter phone number : ";
        cin >> phone;
        myFile.open("cms.dat", ios::binary);

        while(!myFile.eof())
        {
            if(myFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(phone == phoneNumber)
                {
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - ";
                    cout << "\nSearch Results\n";
                    showContact();
                return;
                }
            }
        }
        cout << "\nNo record founds.";
        myFile.close();
    }

    void deleteFromFile()
    {
        long long phone;
        int flag = 0;
        ifstream myFile;
        ofstream tempFile;

        myFile.open("cms.dat", ios::binary);
        tempFile.open("tempt.dat", ios::binary);

        cout << "\nEnter a phone number to delete : ";
        cin >> phone;

        while(!myFile.eof())
        {
            if(myFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(phoneNumber != phone)
                {
                    tempFile.write(reinterpret_cast<char*>(this), sizeof(*this));

                }
                else flag = 1;
            }
        }

        myFile.close();
        tempFile.close();
        remove("cms.dat");
        rename("tempt.dat", "cms.dat");

        flag == 1 ?
        cout << "\nContact delete is successful." :
        cout << "\nNo contact founds.";

    }

    void editOnFile()
    {
        long long phone;
        fstream myFile;

        cout << "\nEdit Contact";
        cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = =\n";
        cout << "\nEnter Phone number to edit : ";
        cin >> phone;
        myFile.open("cms.dat", ios::binary | ios::out | ios::in);

        while(!myFile.eof())
        {
            if(myFile.read(reinterpret_cast<char*>(this), sizeof(*this)))
            {
                if(phone == phoneNumber)
                {
                    cout << "\nCreating new contact" << endl;
                    createContact();

                    int pos = -1*sizeof(*this);
                    myFile.seekp(pos, ios::cur);
                    myFile.write(reinterpret_cast<char*>(this), sizeof(*this));
                    cout << "\nContact Successfully Updated.\n";
                    return;

                }
            }
        }

        cout << "\nNo records found...";
        myFile.close();

    }

};


int main()
{
    system("cls");
    system("Color 5F");

    cout << "\n\n\n\n\t\t\t* * * Welcome to Contact Management System* * *\n\n\n";
    //getch();
    system("pause");

    while(1)
    {
        contact myContact;
        int choice;
        system("cls");
        system("Color 03");
        cout << "\nContact Management System";
        cout << "\n- - - - - - - - - - - - -\n";
        cout << "\nMain Menu";
        cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
        cout << "[1] Add new contact" << endl;
        cout << "[2] Show All Contact" << endl;
        cout << "[3] Search Contact" << endl;
        cout << "[4] Delete Contact" << endl;
        cout << "[5] Edit Contact" << endl;
        cout << "[0] Exit" << endl;
        cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;

        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            system("cls");
            myContact.writeToFile();
            break;
        case 2:
            system("cls");
            myContact.readOnFile();
            break;
        case 3:
            system("cls");
            myContact.searchOnFile();
            break;
        case 4:
            system("cls");
            myContact.deleteFromFile();
            break;
        case 5:
            system("cls");
            myContact.editOnFile();
            break;
        case 0:
            system("cls");
            cout << "\nThanks for using Small Contact Management System...";
            exit(0);
            break;
        default:
            continue;
        }

        int opt;
        cout << "\n\n\n\n=> Enter the choice \n\n[1] Main Menu \t\t[0] Exit\n";
        cout << "\nEnter a number : ";
        cin >> opt;

        switch(opt)
        {
        case 0:
            system("cls");
            cout << "\n\nThanks for using Small Contact Management System....\n\n\n";
            exit(0);
            break;
        default:
            continue;
        }
    }

    return 0;
}
