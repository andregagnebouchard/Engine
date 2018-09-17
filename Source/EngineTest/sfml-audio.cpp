#include <gtest/gtest.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

void playSound()
{
}

TEST(SFMLAudio, UseSFMLAudio)
{
	// Load a sound buffer from a wav file
	sf::SoundBuffer buffer;
	std::string soundFilePath = "../../Support/Testing/sfmlAudioTest//WavTest.wav";
	if (!buffer.loadFromFile(soundFilePath))
		throw std::runtime_error("Could not open audio file:" + soundFilePath);

	// Create a sound instance and play it
	sf::Sound sound(buffer);
	sound.play();

	// Loop while the sound is playing
	while (sound.getStatus() == sf::Sound::Playing)
		sf::sleep(sf::milliseconds(10));
}
