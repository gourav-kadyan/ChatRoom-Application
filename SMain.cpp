#include "Server.hpp"
#include "ServerFunctionalities.hpp"

int main(int argc, char const *argv[])
{
    Server obj;
    Start(obj.serverSocket());
    return 0;
}
