#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <chrono>
#include <thread>
#include <regex>
#include "Socket.h"

using namespace std;

// Время приготовления для различных блюд
unordered_map<string, int> cooking_times = {
     {"hamburger", 5},
     {"sprite", 1},
     {"french fries", 3}
};

// Очередь заказов
queue<pair<string, chrono::time_point<chrono::system_clock>>> order_queue;

// Обработка заказа
int process_order(const string& order_string) {

    // Используем регулярное выражение для поиска блюд в строке
    regex pattern("\\b(hamburger|sprite|french fries)\\b");
    sregex_iterator it(order_string.begin(), order_string.end(), pattern);
    sregex_iterator end;
    int total_time = 0;

    // Добавляем время приготовления для каждого найденного блюда
    for (; it != end; ++it) {
        total_time += cooking_times[it->str()];
    }
    // Возвращаем общее время приготовления
    return total_time;
}

// Расчет времени отображения заказа
chrono::time_point<chrono::system_clock> get_display_time(const string& order) {

    // Рассчитываем время приготовления заказа
    int cooking_time = process_order(order);
    cout << endl <<process_order(order) << endl;
    // Рассчитываем время отображения заказа
    auto display_time = chrono::system_clock::now() + chrono::seconds(cooking_time);

    // Добавляем заказ в очередь
    order_queue.push({ order, display_time });

    // Возвращаем время отображения
    return display_time;
}

int main() {
    ServerSocket server;
    int port = 24242;
    string ipAddress = "127.0.0.1";
    char receiveMessage[MAXSTRLEN];
    char sendMessage[MAXSTRLEN];
    Sleep(300);
    server.StartHosting(port);
	while (true)
	{
        cout << "\tWaiting..." << endl;
        //Ïîëó÷àåì äàííûå îò êëèåíòà
        //è ñîõðàíÿåì â ïåðåìåííîé receiveMessage
        server.ReceiveData(receiveMessage, MAXSTRLEN);
        cout << "Received: " << receiveMessage << endl;

        string order = "i would like a hamburger, sprite, and french fries";
        auto display_time = process_order(order);
        string res;
        res = "Order placed: " + order + '\n'
            + "Display time: " + to_string(display_time).c_str() + '\n';
        cout << res;
        server.SendData(res);

        get_display_time(receiveMessage);
        
	}
    return 0;
}