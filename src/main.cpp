#include <iostream>
#include <SFML/Audio.hpp>

int main()
{
	
	sf::SoundBuffer buffer;

	// Cannot find default sound.
	if (!buffer.loadFromFile("Sounds/note_do.wav"))
	{
		std::cout << "Cannot find default sound." << std::endl;
		return -1;
	}

	sf::Sound sound(buffer);
	sound.play();

	while (sound.getStatus() == sf::Sound::Status::Playing) 
	{
		sf::sleep(sf::milliseconds(100));
	}

	return 0;
}