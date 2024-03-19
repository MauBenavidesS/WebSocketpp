#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <functional>

typedef websocketpp::server<websocketpp::config::asio> server;

int port = 4005;

class utility_server {
public:
    utility_server() {
        // Set logging settings
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        m_endpoint.init_asio();

        // Set message handler
        m_endpoint.set_message_handler(std::bind(&utility_server::on_message, this, std::placeholders::_1, std::placeholders::_2));
    }

    void run() {
        // Listen on port
        m_endpoint.listen(port);

        // Queues a connection accept operation
        m_endpoint.start_accept();

        // Start the Asio io_service run loop
        m_endpoint.run();
    }
private:
    server m_endpoint;

    // Message handler for incoming messages
    void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        printf("DEBUG. Received Message:... \n");
        // Here you can add any processing logic for the received message
        // For example, you can store it, forward it, or perform any other action
    }
};

int WebSocketServer() {
    printf("DEBUG. WebSocketServer Starting in port: %d... \n", port);
    utility_server s;
    s.run();
    return 0;
}