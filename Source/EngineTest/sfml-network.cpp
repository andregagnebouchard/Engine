#include <gtest/gtest.h>
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>

std::ostream& operator <<(std::ostream& stream, const sf::Ftp::Response& response)
{
	return stream << response.getStatus() << response.getMessage();
}

TEST(SFMLNetwork, UseSFMLNetwork)
{
	// Choose the server address
	sf::IpAddress address("127.0.0.1");

	// Connect to the server
	sf::Ftp server;
	sf::Ftp::Response connectResponse = server.connect(address);
	std::cout << connectResponse << std::endl;
}
