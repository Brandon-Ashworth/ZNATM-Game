#include "Sound.h"


Sound::Sound(void)
{
	type = 1;
	rep = false;

}

Sound::Sound(int input)
{
	type = input;
	type = 1;
	rep = false;
}

Sound::Sound(std::string input)
{
	type = 1;
	Load(input);
}

Sound::~Sound(void)
{
}

void Sound::setRep(bool input)
{
	rep = input;
}

void Sound::Load(std::string input)
{
	if(type == 1)
	{
		loadSound(input);
	}
	else if (type == 2)
	{
		loadMusic(input);
	}
	else
		std::cout <<"Failed to Load thing" << std::endl;



	//error 0 = no error
	//error 1 = did not load

}

void Sound::play()
{
	if(type == 1)
	{
		playSound();
	}
	else if (type == 2)
	{
		playMusic();
	}
	else
		std::cout <<"Failed to Play" << std::endl;

}

void Sound::pause()
{
	if(type == 1)
	{
		pauseSound();
	}
	else if (type == 2)
	{
		pauseMusic();
	}
	else
		std::cout <<"Failed to Pause " << std::endl;

}

void Sound::loadSound(std::string input)
{
	m_soundBuff.loadFromFile(input);
	m_sound.setBuffer(m_soundBuff);

}

void  Sound::loadMusic(std::string input)
{
	m_music.openFromFile(input);
}

void Sound::playSound()
{
	//test to see if this can be called before
	//m_sound.setLoop(rep);
	//std::cout << "Playing Music" << std::endl;
	m_sound.play();
	m_sound.setLoop(rep);
}

void Sound::playMusic()
{
	m_music.play();
	m_music.setLoop(rep);
}

void Sound::pauseSound()
{
	m_sound.pause();
}

void Sound::pauseMusic()
{
	m_music.pause();
}

void Sound::setVolume(float volume)
{
	if(type == 1)
	{
		setVolSound(volume);
	}
	else if (type == 2)
	{
		setVolMusic(volume);
	}
	else
		std::cout <<"Failed to change volume " << std::endl;
}


float Sound::getVolume()
{
		if(type == 1)
	{
		return(getVolSound());
	}
	else if (type == 2)
	{
		return(getVolMusic());
	}
	else
		std::cout <<"Failed to change volume " << std::endl;
}

void Sound::setVolSound(float volume)
{
	m_sound.setVolume(volume);
}

void Sound::setVolMusic(float volume)
{
	m_music.setVolume(volume);
}

float Sound::getVolSound()
{
	return(m_sound.getVolume());
}

float Sound::getVolMusic()
{
	return(m_music.getVolume());
}
int Sound::isPlaySound()
{
	return(m_sound.getStatus());
}
int Sound::isPlayMusic()
{
	return(m_music.getStatus());
}

int Sound::isPlaying()
{
	if(type == 1)
	{
		return(isPlaySound());
	}
	else if (type == 2)
	{
		return(isPlayMusic());
	}
	else
		std::cout <<"Failed to Check if playing " << std::endl;
}