#include <gtest/gtest.h>
#include <SFML\System.hpp>
TEST(SFMLSystem, UseSFMLSystem)
{
	sf::Clock clock;
	auto test = clock.getElapsedTime();
	test;
}