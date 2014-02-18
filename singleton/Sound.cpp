#include "Sound.h"

CSound* CSound::instance_=0;

CSound::CSound()
{
	muteBGM = false;
	muteSound = false;
	muteHit = false;
	muteJump = false;
	initSound();
}

CSound::~CSound()
{
}

void CSound::initSound()
{
	//start the sound engine with default parameters
	theSoundEngine = createIrrKlangDevice();
	BGM = theSoundEngine->play2D("sounds/bgm.ogg", true, true);
	BGM->setVolume(0.5);
}

void CSound::setMuteBGM(bool muteBGM)
{
	this->muteBGM = muteBGM;
}

void CSound::setMuteSound(bool muteSound)
{
	this->muteSound = muteSound;
}

void CSound::setMuteHit(bool muteHit)
{
	this->muteHit = muteHit;
}

void CSound::setMuteJump(bool muteJump)
{
	this->muteJump = muteJump;
}

bool CSound::getMuteBGM()
{
	return muteBGM;
}

bool CSound::getMuteSound()
{
	return muteSound;
}

bool CSound::getMuteHit()
{
	return muteHit;
}

bool CSound::getMuteJump()
{
	 return muteJump;
}

void CSound::playSound(SNUM state)
{
	switch(state)
	{
	case SNUM::CHOOSE:
		theSoundEngine->play2D("sounds/choose.wav");
		break;
	case SNUM::SELECT:
		theSoundEngine->play2D("sounds/select.wav");
		break;
	case SNUM::HIT:
		theSoundEngine->play2D("sounds/hit.wav");
		break;
	case SNUM::JUMP:
		theSoundEngine->play2D("sounds/jump.mp3");
		break;
	case SNUM::SHOOT:
		theSoundEngine->play2D("sounds/bow.wav");
	}
}
CSound* CSound::instance(void)
{
	if(instance_==0)
		instance_=new CSound;
	return instance_;
}

void CSound::playBGM()
{
	//Checks if is it muted
	if(muteBGM == false)
	{
		BGM->setIsPaused(false);
	}
	else
	{
		BGM->setIsPaused(true);
	}
}