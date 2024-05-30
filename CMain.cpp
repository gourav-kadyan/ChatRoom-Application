#include "Client.hpp"
#include "ClientFunctionalities.hpp"
int main(int argc, char const *argv[])
{
    Client obj;
    Start(obj.clientSocket());
    return 0;
}
