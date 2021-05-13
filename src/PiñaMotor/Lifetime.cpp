#include "Lifetime.h"
#include "SceneManager.h"

bool Lifetime::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("life") == mapa.end() || mapa.find("year") == mapa.end()) return false;

	std::string s = mapa.at("year");
	dosmilveintiuno.tm_hour = 0;					dosmilveintiuno.tm_min = 0; dosmilveintiuno.tm_sec = 0;
	dosmilveintiuno.tm_year = std::stoi(s) - 1900;	dosmilveintiuno.tm_mon = 0; dosmilveintiuno.tm_mday = 1;

	_startTime = -1;
	_currentTime = 0;

	s = mapa.at("life");
	_endTime = std::stof(s);

	return true;
}

void Lifetime::update(){
	if (!_startedYet) {
		_startedYet = true;

		time(&timer);	// Tiempo actual

		_startTime = difftime(timer, mktime(&dosmilveintiuno));	//Segundos desde el 1-1-2021 (no funcionará bien si lo juegas en el pasado)
	}
	else {
		time(&timer);	// Tiempo actual

		_currentTime = difftime(timer, mktime(&dosmilveintiuno)) - _startTime;	// Diferencia entre _startTime y el actual

		if (_currentTime >= _endTime)	// Si debe morir
		{
			SceneManager::GetInstance()->addEntityToRemove(_myEntity);
		}
	}
}