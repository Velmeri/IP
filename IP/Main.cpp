#include <iostream>
#include "Socket.h"
#include <thread>

using namespace std;

enum comands
{
	InvalidСommand,
	GetPrice,
	HELP,
	END
};

struct product {
	string name;
	double price;

	product(string name, double price) {
		this->name = name;
		this->price = price;
	}
};
const short SIZE = 1;
const string ComandList[SIZE] = { "GetPrice" };
product Laptop("laptop", 1200);
product Phone("phone", 500);
product Tablet("tablet", 700);

const short PRODUCTCOUNT = 3;
product ProductList[PRODUCTCOUNT] = { Laptop, Phone, Tablet };

int GetComand(string comand) {
	if ("GetPrice" == comand) return GetPrice;
	if ("help" == comand) return HELP;
	if ("end" == comand) return END;
	return InvalidСommand;
}

void function1(ServerSocket server, char receiveMessage[]) {
	bool is_skip = 0;
	int price = 0;
	server.SendData("\nServer: please enter name of the product");
	server.ReceiveData(receiveMessage, MAXSTRLEN);
	for (unsigned short i = 0; receiveMessage[i] != '\0'; i++)
		if (receiveMessage[i] >= 'A' && receiveMessage[i] <= 'Z') receiveMessage[i] += 'a' - 'A';
	for (unsigned short i = 0; i < PRODUCTCOUNT; i++)
		if (ProductList[i].name == receiveMessage) price = ProductList[i].price;
	if (price == 0)
	{
		server.SendData("\nServer: product not found");
	} else {
		server.SendData("\nServer: please enter count");
		server.ReceiveData(receiveMessage, MAXSTRLEN);
		int res = 0;
		for (int i = 0; i < strlen(receiveMessage); i++) {
			if (receiveMessage[i] >= '0' && receiveMessage[i] <= '9' && i > 0 || receiveMessage[i] >= '1' && receiveMessage[i] <= '9' && i == 0)
				res = res * 10 + receiveMessage[i] - '0';
			else {
				server.SendData("\nServer: you entered unacceptable value");
				is_skip = 1;
			}
		}
		if (is_skip) {
		} else {
			string a = "\nServer: the price of the product is " + to_string(res * price) + "$";
			server.SendData(a);
		}
	}
}

void function2(ServerSocket server) {
	server.SendData("\nServer:\n\tGetPrice to find out the price of a product,\n\thelp to list all commands,\n\tend to finish work.");
}


int main()
{
	int nChoice;
	int port = 24242;  //âûáèðàåì ïîðò
	string ipAddress = "127.0.0.1"; //Àäðåñ ñåðâåðà
	//string ipAddress = "10.4.3.8";
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];

	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	switch (nChoice)
	{
	case 1:
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//Çàïóñêàåì ñåðâåð
		server.StartHosting(port);
		while (true)
		{
			cout << "\tWaiting..." << endl;
			//Ïîëó÷àåì äàííûå îò êëèåíòà
			//è ñîõðàíÿåì â ïåðåìåííîé receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			switch (GetComand(receiveMessage))
			{
			case GetPrice:
			{
				thread a(function1, server, receiveMessage);
				a.detach();
			}
			break;

			case HELP:
			{
				thread a(function2, server);
				a.detach();
			}
			break;

			case END:
			{
				server.SendData("end");
				return 0;
			}

			default:
				server.SendData("\nServer: you entered a non-existent command");
				break;
			}
		}
	}
	break;
	case 2:
	{
		//cout << "Enter an IP address: " << endl;
				//Çàïðàøèâàåì IP ñåðâåðà
				//cin >> ipAddress;
		ClientSocket client;
		//ïîäêëþ÷àåìñÿ ê ñåðâåðó
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			cout << "\nClient: ";
			//îòïðàâëÿåì ñîîáùåíèå
			client.SendDataMessage();
			//ïîëó÷àåì îòâåò
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << receiveMessage << endl;
			if (GetComand(receiveMessage) == END) {
				cout << "bye\n\n";
				system("pause");
				break;
			}
		}
		//Çàêðûâàåì ñîåäèíåíèå
		client.CloseConnection();
		return 0;
	}

	break;

	case 3:
	{
		return 0;
	}
	break;

	default:
		break;
	}
}