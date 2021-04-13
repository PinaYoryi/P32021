#pragma once
#include "Component.h"
#include "Vector3.h"
#include <list>
#include "btBulletCollisionCommon.h"

class BoxCollider : public Component {
public:
	// Constructora
	BoxCollider(Vector3<float> position, Vector3<float> size, bool isTrigger = false);

	// TODO
	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	// Getters
	inline bool getIsTrigger() const { return _isTrigger; }
	inline Vector3<float> getCenter() const { return _center; }
	inline Vector3<float> getSize() const { return _size; }

	// Setters
	inline void setIsTrigger(bool b) { _isTrigger = b; }

	inline void setCenter(Vector3<float> v) { _center = v; };
	inline void setCenter(float x, float y, float z) { _center = { x, y, z }; };

	inline void setSize(Vector3<float> v) { _size = v; };
	inline void setSize(float x, float y, float z) { _size = { x, y, z }; };
	
private:
	// Si está habilitada, este Collider será usado para eventos de triggering, y será ignorado por el motor de física.
	bool _isTrigger;

	// El centro del BoxCollider
	Vector3<float> _center;

	// El tamaño de cada eje (la mitad para cada lado del centro)
	Vector3<float> _size;

	btCollisionObject* _btCollisionObject = nullptr;
	btCollisionShape* _btCollisionShape = nullptr;
	btBoxShape* _btBoxShape = nullptr;
};