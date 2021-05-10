#include "Lifetime.h"
#include "SceneManager.h"

bool Lifetime::init(const std::map<std::string, std::string>& mapa) {
	//if... comprobación de lua

	dosmilveintiuno.tm_hour = 0;   dosmilveintiuno.tm_min = 0; dosmilveintiuno.tm_sec = 0;
	dosmilveintiuno.tm_year = 121; dosmilveintiuno.tm_mon = 0; dosmilveintiuno.tm_mday = 1;

	_startTime = -1;
	_currentTime = 0;
	_endTime /* = key del mapa de lua */ = 10;

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
			SceneManager::GetInstance()->removeEntity(getEntity());
		}
	}
}