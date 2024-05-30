#include "ServerFunctionalities.hpp"



struct terminal
{
	int id;
	std::string name;
	int socket;
	std::thread th;
};

std::vector<terminal> clients;
std::string def_col = "\033[0m";
std::string colors[] = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"};
int seed = 0;
std::mutex cout_mtx, clients_mtx;




std::string color(int code)
{
	return colors[code % NUM_COLORS];
}

// Set name of client
void set_name(int id, char name[])
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].id == id)
		{
			clients[i].name = std::string(name);
		}
	}
}

// For synchronisation of cout statements
void shared_print(std::string str, bool endLine = true)
{
	std::lock_guard<std::mutex> guard(cout_mtx);
	std::cout << str;
	if (endLine)
		std::cout << std::endl;
}

// Broadcast message to all clients except the sender
void broadcast_message(std::string message, int sender_id)
{
	char temp[MAX_LEN];
	strcpy(temp, message.c_str());
	// std::cout << "Printing ---- " <<  temp << std::endl;
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].id != sender_id)
		{
			send(clients[i].socket, temp, sizeof(temp), 0);
		}
	}
}

// Broadcast a number to all clients except the sender
void broadcast_message(int num, int sender_id)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].id != sender_id)
		{
			send(clients[i].socket, &num, sizeof(num), 0);
		}
	}
}

void end_connection(int id)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].id == id)
		{
			std::lock_guard<std::mutex> guard(clients_mtx);
			clients[i].th.detach();
			clients.erase(clients.begin() + i);
			close(clients[i].socket);
			break;
		}
	}
}

void handle_client(int client_socket, int id)
{
	char name[MAX_LEN], str[MAX_LEN];
	recv(client_socket, name, sizeof(name), 0);
	set_name(id, name);

	// Display welcome message
	std::string welcome_message = std::string(name) + std::string(" has joined");
	broadcast_message("#NULL", id);
	broadcast_message(id, id);
	broadcast_message(welcome_message, id);
	shared_print(color(id) + welcome_message + def_col);

	while (1)
	{
		int bytes_received = recv(client_socket, str, sizeof(str), 0);
		if (bytes_received <= 0)
			return;
		if (strcmp(str, "#exit") == 0)
		{
			// Display leaving message
			std::string message = std::string(name) + std::string(" has left");
			broadcast_message("#NULL", id);
			broadcast_message(id, id);
			broadcast_message(message, id);
			shared_print(color(id) + message + def_col);
			end_connection(id);
			return;
		}
		broadcast_message(std::string(name), id);
		broadcast_message(id, id);
		broadcast_message(std::string(str), id);
		shared_print(color(id) + name + " : " + def_col + str);
	}
}

void Start(int server_socket)
{
	
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(10001);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 0);

	if ((bind(server_socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in))) == -1)
	{
		perror("bind error: ");
		exit(-1);
	}

	if ((listen(server_socket, 8)) == -1)
	{
		perror("listen error: ");
		exit(-1);
	}

	struct sockaddr_in client;
	int client_socket;
	unsigned int len = sizeof(sockaddr_in);

	std::cout << colors[NUM_COLORS - 1] << "\n\t  ====== Welcome to the chat-room ======   " << std::endl
		 << def_col;

	while (1)
	{
		if ((client_socket = accept(server_socket, (struct sockaddr *)&client, &len)) == -1)
		{
			perror("accept error: ");
			exit(-1);
		}
		seed++;
		std::thread t(handle_client, client_socket, seed);
		std::lock_guard<std::mutex> guard(clients_mtx);
		clients.push_back({seed, std::string("Anonymous"), client_socket, (move(t))});
	}

	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i].th.joinable())
			clients[i].th.join();
	}

	
}