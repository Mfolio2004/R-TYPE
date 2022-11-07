/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** ClientSystem
*/

#ifndef CLIENTSYSTEM_HPP_
    #define CLIENTSYSTEM_HPP_

    #include "NetworkSystem.hpp"

    #define NETWORK_PING_FREQUENCY  100

namespace R_TYPE {

    class GraphicSystem;

    class ClientSystem : public NetworkSystem {
        public:
            ClientSystem(std::string ip, size_t port);
            ~ClientSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;
            void sendEvent(int button, NetworkSystem::ButtonState state, bool isKey);

        protected:
        private:
            void handle_incomming_message() final;
            void broadcast(SceneManager &) final;

            int _ping_cooldown;
            asio::ip::udp::endpoint _server_endpoint;
            std::unique_ptr<GraphicSystem> graphicSystem;
    };

}

#endif /* !CLIENTSYSTEM_HPP_ */
