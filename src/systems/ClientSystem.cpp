/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ClientSystem
*/

#include "ClientSystem.hpp"

namespace R_TYPE {

ClientSystem::ClientSystem(std::string ip, size_t port) : _server_endpoint(asio::ip::make_address(ip), port)
{
    std::cout << "Client Network System created" << std::endl;
}

ClientSystem::~ClientSystem()
{
}

void ClientSystem::init(SceneManager &/*manager*/)
{
    std::cout << "Client Network System initiating" << std::endl;
    _socket.open(asio::ip::udp::v4());
    read_setup();
    _threadContext = std::thread([this]() { _context.run(); });
}

void ClientSystem::update(SceneManager &/*manager*/, uint64_t deltaTime)
{
    _ping_cooldown += deltaTime;
    if (_ping_cooldown >= NETWORK_PING_FREQUENCY) {
        _ping_cooldown = 0;
        broadcast();
    } else {
        std::cout << _ping_cooldown << " " << deltaTime << " " << NETWORK_PING_FREQUENCY << std::endl;
    }
}

void ClientSystem::destroy()
{
    std::cout << "Network System destroyed" << std::endl;
}

void ClientSystem::handle_incomming_message()
{
    // here, handle the recienved message stored in _buffer
}

void ClientSystem::broadcast()
{
    char buff[1024];

    for (int i = 0; i < 1024; buff[i] = '\0', i++);
    buff[0] = protocol::Header::PING;
    _socket.send_to(asio::buffer(buff), _server_endpoint);
}

}