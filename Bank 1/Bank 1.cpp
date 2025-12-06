
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

short ReadChooseNumber()
{
    short Number;

    cout << "Choose What do you want to do ? [1 To 6] : ";
    cin >> Number;

    return Number;

}


struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

sClient ConvertLineToRecord(string line, string Seperator = "#//#");

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}



sClient ReadNewClint()
{
    sClient client;

    cout << "Please enter Account Number : ";
    getline(cin >> ws, client.AccountNumber);

    while (ClientExistsByAccountNumber(client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, client.AccountNumber);
    }

    cout << "Please enter Pincode : ";
    getline(cin, client.PinCode);

    cout << "Please enter Name : ";
    getline(cin, client.Name);

    cout << "Please enter Phone : ";
    getline(cin, client.Phone);

    cout << "Please enter Accounte Balance : ";
    cin >> client.AccountBalance;

    return client;

}


string ConvertRecordToLine(sClient Client, string Seperetor = "#//#")
{
    string ClientRecord = "";

    ClientRecord += Client.AccountNumber + Seperetor;
    ClientRecord += Client.PinCode + Seperetor;
    ClientRecord += Client.Name + Seperetor;
    ClientRecord += Client.Phone + Seperetor;
    ClientRecord += to_string(Client.AccountBalance);

    return ClientRecord;
}


void DataLineToFile(string FileName, string DataLine)
{
   
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);
    {
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;

            MyFile.close();
        }
    }
}


void AddNewClints()
{

    char AddMore = 'Y';

    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";

        sClient Client;

        Client = ReadNewClint();

        DataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";

        cin >> AddMore;


    } while (toupper(AddMore) == 'Y');

}

void PrintAddNewClients()
{
    cout << "\n-----------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n_____________________________\n";

    AddNewClints();
}


string ReadAccountNumber()
{
    string AccountNumber;

    cout << "Please enter Account Number : ";
    cin >> AccountNumber;

    return AccountNumber;
}


void PrintClientCard(sClient Client)
{
    cout << "\nThe Follwing are The Client datails : " << endl;
    cout << "\nAccount Number   : " << Client.AccountNumber << endl;
    cout << "Pin Code         : " << Client.PinCode << endl;
    cout << "Name             : " << Client.Name << endl;
    cout << "Phone            : " << Client.Phone << endl;
    cout << "Number Balance   : " << Client.AccountBalance << endl;
}


vector<string> SplitString(string st, string Delim)
{
    vector<string> vClients;

    string sWord = "";
    size_t Pos;

    while((Pos = st.find(Delim)) != std::string::npos)
    {
        sWord = st.substr(0, Pos);

        if (sWord != "")
        {
            vClients.push_back(sWord);
        }

        st.erase(0, Pos + Delim.length());

    }

    if (st != "")
    {
        vClients.push_back(st);

    }

    return vClients;
}


sClient ConvertLineToRecord(string line, string Seperator)
{
    sClient Client;

    vector <string> vClientData = SplitString(line, Seperator);


    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;

}


bool FindAccountByAccountNumber(string AccountNumber, vector<sClient> &vClients, sClient& Client)
{
    for (sClient &s : vClients)
    {
        if (s.AccountNumber == AccountNumber)
        {
            Client = s;
            return true;
        }
    }

    return false;
}


bool MarkClientForDelete(string AccountNumber, vector<sClient> &vClients)
{
    for (sClient & s : vClients)
    {
        if (s.AccountNumber == AccountNumber)
        {
            s.MarkForDelete = true;
            
            return true;
        }
    }

    return false;
}


void SaveDataLineToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);  // Over Write

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);

                MyFile << DataLine << endl;

            }
        }
        MyFile.close();
    }

}


vector<sClient> LoadClientsDataFromFile(string FileName)
{
    vector<sClient> vClients;

    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);

        }
        MyFile.close();
    }

    return vClients;
}


bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindAccountByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDelete(AccountNumber, vClients);
            SaveDataLineToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully." << endl;

            return true;

        }

        
    }

    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }

    return false;
}


void PrintClientsAfterDelete()
{
    cout << "\n-----------------------------\n";
    cout << "\tDelete Clients Screen";
    cout << "\n_____________________________\n";

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);
}




sClient changeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Please enter Pin Code : ";
    getline(cin >> ws, Client.PinCode);

    cout << "Please enter Name : ";
    getline(cin, Client.Name);

    cout << "Please enter Phone : ";
    getline(cin, Client.Phone);

    cout << "Please enter Accounte Balance : ";
    cin >> Client.AccountBalance;

    return Client;

}


bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindAccountByAccountNumber(AccountNumber, vClients , Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want Update this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient &s : vClients)
            {
                if (s.AccountNumber == AccountNumber)
                {
                    s = changeClientRecord(AccountNumber);
                    break;
                }
            }
        }

        SaveDataLineToFile(ClientsFileName, vClients);

        cout << "\n\nClient Updated Successfully.";

        return true;


    }

    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }

    return false;

}


void PrintClientAfterUpdate()
{
    cout << "\n-----------------------------\n";
    cout << "\tUpdate Clients Screen";
    cout << "\n_____________________________\n";

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}


bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
   
    for (sClient& s : vClients)
    {
        if (s.AccountNumber == AccountNumber)
        {
            PrintClientCard(s);
            

            return true;
        }
    }
    
    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
    return false;
}


void PrintFindClient()
{
    cout << "\n-----------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n_____________________________\n";

    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    FindClientByAccountNumber(AccountNumber, vClients);
}



void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}


void AllClientsData(vector<sClient> vClients)
{
    cout << "\n\t\t\t\t\tClinrt List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;

    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void PrintAllClientsData()
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    AllClientsData(vClients);
}


void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}



enum enMainMenueOptions
{
    eShowClientList = 1,
    eAddNewClient = 2 ,
    eDeleteClient = 3 ,
    eUpdateClint = 4 ,
    eFindClient = 5,
    eExit = 6
};


void PrintMainMenueScreen();

void GoBackToMainMenue()
{
    cout << "\n\nPress Any Key To Go Back To Main Menue ....";
    system("pause>0");

    PrintMainMenueScreen();
}


void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eShowClientList:
    {
        system("cls");
        PrintAllClientsData();
        GoBackToMainMenue();
        break;
    }

    case enMainMenueOptions::eAddNewClient:
    {
        system("cls");
        PrintAddNewClients();
        GoBackToMainMenue();
        break;
    }

    case enMainMenueOptions::eDeleteClient:
    {
        system("cls");
        PrintClientsAfterDelete();
        GoBackToMainMenue();
        break;
    }

    case enMainMenueOptions::eUpdateClint:
    {
        system("cls");
        PrintClientAfterUpdate();
        GoBackToMainMenue();
        break;
    }

    case enMainMenueOptions::eFindClient:
    {
        system("cls");
        PrintFindClient();
        GoBackToMainMenue();
        break;
    }

    case enMainMenueOptions::eExit:
    {
        system("cls");
        ShowEndScreen();
        break;
    }

    }
}


void PrintMainMenueScreen()
{
    system("cls");
    cout << "________________________________________________________" << endl;
    cout << "________________________________________________________" << endl;
    cout << "\t\t Main Menue Screen " << endl;
    cout << "________________________________________________________" << endl;
    cout << "________________________________________________________" << endl;

    cout << "\t [1] Show Client List" << endl;
    cout << "\t [2] Add New Client" << endl;
    cout << "\t [3] Delete Client" << endl;
    cout << "\t [4] Update Client Info" << endl;
    cout << "\t [5] Find Client" << endl;
    cout << "\t [6] Exit" << endl;
    cout << "________________________________________________________" << endl;
    cout << "________________________________________________________" << endl;

    PerformMainMenueOption((enMainMenueOptions)ReadChooseNumber());
}



int main()
{
    PrintMainMenueScreen();
    system("pause>0");
}