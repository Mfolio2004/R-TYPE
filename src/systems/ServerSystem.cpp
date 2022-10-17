/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ServerSystem
*/

#include "ServerSystem.hpp"
#include "network/protocol.h"

namespace R_TYPE {

ServerSystem::ServerSystem(size_t port) : NetworkSystem(port)
{
    std::cout << "Server Network System created" << std::endl;
    _broadcast_cooldown = 0;
}

ServerSystem::~ServerSystem()
{
}

void ServerSystem::init(SceneManager &/*manager*/)
{
    std::cout << "Server Network System initiating" << std::endl;
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); });
}

void ServerSystem::update(SceneManager &/*manager*/, uint64_t deltaTime)
{
    _broadcast_cooldown += deltaTime;
    if (_broadcast_cooldown >= NETWORK_BROADCAST_FREQUENCY) {
        _broadcast_cooldown = 0;
        broadcast();
    }
}

void ServerSystem::destroy()
{
    std::cout << "Network System destroyed" << std::endl;
}

void ServerSystem::handle_incomming_message()
{
    bool new_client = true;

    for (size_t i = 0; i < _connections.size(); i++)
        if (_connections[i]->get_endpoint() == _edp_buff)
            new_client = false;
    if (new_client)
        _connections.push_back(std::make_unique<Connection> (_edp_buff, _connections.size() + 1));
    // here, handle the recienved message stored in _buffer
}

void ServerSystem::broadcast()
{
    char buff[1024];

    for (std::unique_ptr<Connection> &con : _connections) {
        create_start_game_msg(buff, con);
        _socket.send_to(asio::buffer(buff), con->get_endpoint());
    }
}

void ServerSystem::create_start_game_msg(char *buff, std::unique_ptr<Connection> &connection)
{
    buff[0] = protocol::Header::START_GAME;
    buff[sizeof(protocol::Header)] = (size_t)connection->get_id();
    buff[sizeof(protocol::Header) + sizeof(size_t)] = (size_t)_connections.size();
    buff[sizeof(protocol::Header) + 2 * sizeof(size_t)] = '\0';
}

}
