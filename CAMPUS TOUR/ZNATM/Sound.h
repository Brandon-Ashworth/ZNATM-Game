#pragma once

#include <string>
#include "SFML\Audio.hpp"

#include <iostream>

/**
 *  \brief This class handles sound
 *  
 *  This class handles the sound through sfml, which sits ontop of openal.
 *  sounds can be of two varieties, it can be streamed or loaded fully into memory.
 *  on creationg you will be able to choose the sound type, the default is sound.
 *  
 *  \author Umar Badat 31852179, assistance from Annopan
 *  
 *  \bug doesn't work, crashes run time with memory violation
 *  \bug fixed Too many dll's
 *  
 *  \note I'd like to thank Annopan for telling me which of the dll's should be included.
 *  
 *  
 */
class Sound
{
public:
	
	/**
	 *  \brief This is the default constructor and assumes the user wants to load the whole sound into memory.
	 *  
	 *  As Mentioned you can stream the music and load it all into memory and play it, 
	 *  the default of this is set to 1 so load the whole thing.
	 *  
	 *  \note this would be easier if i set it to use enums and not try to remember a code like 0 to stream
	 */
	Sound(void); //default is 1 so sound, sound loads the whole thing while music streams
	
	/**
	 *  \breif sets the audio type
	 *  
	 *  put 1 for loading the whole music clip into memory
	 *  put 0 for streaming the audio clip
	 *  
	 *  \bug does not check if the input is incorrect
	 *  
	 *  \param integer
	 *  
	 *  
	 */
	Sound(int input);//setting the type 1 is sound 2 is music
	/**
	*	\brief loading the sound on create
	*
	*	\param string fileLocation
	*
	*	\author Umar Badat
	*
	*/
	Sound(std::string input);
	~Sound(void);
	/**
	 *  \brief location of the sound file
	 *  
	 *  using a string input the file location of the file you want to load
	 *  
	 *  \param string
	 *  
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date 
	 *  
	 */
	void Load(std::string input);

	/**
	 *  \brief Sets the repeat to true or false 
	 *  
	 *  This class sets the audio to repeat after it finishes if not then it will stop until the play function is called again
	 *  
	 *  \param bool
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void setRep(bool input);//1 is repeate 
	
	/**
	 *  \brief plays the audio
	 *  
	 *  This function calls the correct play depengin on if it is 
	 *  streaming or loading it all into memory
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void play();
	/**
	 *  \brief pause the audio
	 *  
	 *  Depending on audio type pauses the audio
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Umar Badat
	 *  \date
	 */
	void pause();

	/**
	*	\brief sets the volume of the audio clip
	*
	*	\param float
	*	\return void
	*
	*	\author Umar Badat
	*	\date
	*/
	void setVolume(float volume);

	/**
	*	\brief gets the volume 
	*
	*	\param void
	*	\return the current volume
	*
	*	\author Umar Badat
	*	\date
	*/
	float getVolume();

	int isPlaying();

	

private:
	
	//stores the audio type, could be better if it's an enum
	int type;
	//if true needs to be repeated until the the pause command is called
	bool rep;
	
	//these next 3 are just for storing the sounds, sometimes they don't need to store the data might be an idea to use pointers
	sf::SoundBuffer m_soundBuff;
	sf::Sound m_sound;
	sf::Music m_music;

	//these are the two load functions that could be called
	void loadSound(std::string input);
	void loadMusic(std::string input);

	//thses are the two play functions that could be called
	void playSound();
	void playMusic();

	//these are the two pause functions 
	void pauseSound();
	void pauseMusic();

	//set the volume for both sounds
	void setVolSound(float volume);
	void setVolMusic(float volume);

	//get the volume for the two audio's
	float getVolSound();
	float getVolMusic();

	//hcek if the sound is playing
	int Sound::isPlaySound();
	int Sound::isPlayMusic();
};

