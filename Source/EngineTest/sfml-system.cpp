#include <gtest/gtest.h>
#include <SFML\System.hpp>
TEST(DISABLED_SFMLSystem, UseSFMLSystem)
{
	sf::Clock clock;
	auto test = clock.getElapsedTime();
	test;
}