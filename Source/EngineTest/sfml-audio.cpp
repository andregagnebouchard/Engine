#include <gtest/gtest.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

void playSound()
{
	// Load a sound buffer from a wav file
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("../../Support/Testing/sfmlAudioTest//canary.wav"))
		return;

	// Display sound informations
	std::cout << "WavTest.wav:" << std::endl;
	std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
	std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;
	std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;

	// Create a sound instance and play it
	sf::Sound sound(buffer);
	sound.play();

	// Loop while the sound is playing
	while (sound.getStatus() == sf::Sound::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));

		// Display the playing position
		std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
		std::cout << std::flush;
	}
	std::cout << std::endl << std::endl;
}

TEST(SFMLAudio, UseSFMLAudio)
{
	// Play a sound
	playSound();
}
