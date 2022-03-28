#include "Sounds.h"

Sounds::Sounds()
{
	m_sounds[WALK      ].loadFromFile("walk.wav");
	m_sounds[JUMP      ].loadFromFile("jump.wav");
	m_sounds[EAT       ].loadFromFile("eat.wav" );
	m_sounds[JET_ACTIVE].loadFromFile("jet.wav" );
    m_sounds[BOOM      ].loadFromFile("boom.wav");

    m_playingSound = sf::Sound();
}//end constructor 

Sounds& Sounds::instance()
{//create static Sound object and return it
	static Sounds sound;
	return sound;
}//end instance 

void Sounds::PlaySound(SoundsType soundName)
{
    if (m_mute)
    {
        this->stopPlaying(true);
        return;
    }
    if (soundName == WALK)//so it wont start walk sound in the wrong time
        if((m_plyingNow == WALK || m_plyingNow == JUMP || m_plyingNow == BOOM) && m_playingSound.getStatus() == sf::Sound::Playing)
            return;

    if (m_plyingNow != soundName || m_playingSound.getStatus() != sf::Sound::Playing)
    {
        m_playingSound.setBuffer(m_sounds[soundName]);
        m_playingSound.play();
        m_plyingNow = soundName;
    }

}//end PlaySound 

void Sounds::stopPlaying(bool all)
{
    if ((m_plyingNow != JUMP && m_plyingNow != BOOM) || (all && m_plyingNow != BOOM))//if all = false, don't stop jump & boom sounds
        m_playingSound.stop();
}//end stopPlaying 

void Sounds::setMute(bool status)
{
    m_mute = status;
}//end setMute 

