#include "Socket.h"

using namespace std;

int main() {
    int port = 24242;
    string ipAddress = "127.0.0.1";
    char receiveMessage[MAXSTRLEN];
    char sendMessage[MAXSTRLEN];
    ClientSocket client;
    //подключаемся к серверу
    client.ConnectToServer(ipAddress.c_str(), port);
    Sleep(600);
	while (true)
	{
		cout << "\nClient: ";
		//отправляем сообщение
		client.SendDataMessage();
		//получаем ответ
		client.ReceiveData(receiveMessage, MAXSTRLEN);
		cout << receiveMessage << endl;
	}
    return 0;
}