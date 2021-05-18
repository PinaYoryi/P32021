#pragma once
#include "Component.h"
#include "Vector3.h"
#include <list>
#include "Quaternion.h"

class Transform : public Component {
public:
	enum class Space {
		Self,
		World,
		Parent
	};

	Transform() : _scale ( 1, 1, 1 ) {}

	bool init(const std::map<std::string, std::string>& mapa) override;
	void translate(float x, float y, float z);
	void rotate(float xAngle, float yAngle, float zAngle, Space relativeTo = Space::Self);

	// Getter
	Transform* parent() { return _parent; }
	Transform* findChild(char* name);

	Vector3<float> position() { getParentData(); return _position; }
	Quaternion rotation() { getParentData(); return _rotation; }
	Vector3<float> scale() { getParentData(); return _scale; }

	Vector3<float> localPosition() {  return _localPosition; }
	Quaternion localRotation() {  return _localRotation; }
	Vector3<float> localScale() {  return _localScale; }

	// Setter
	void setParent(Transform* parent);

	void setPosition(Vector3<float> v);
	void setPosition(float x, float y, float z);

	void setRotation(Quaternion q);
	Quaternion inverseTransformRotation(Quaternion q);
	void setRotation(float x, float y, float z);

	void setScale(Vector3<float> v);
	void setScale(float x, float y, float z);

	void setLocalPosition(Vector3<float> v);
	void setLocalPosition(float x, float y, float z);

	void setLocalRotation(Quaternion q);
	Quaternion transformRotation(Quaternion q);
	void setLocalRotation(float x, float y, float z);

	void setLocalScale(Vector3<float> v);
	void setLocalScale(float x, float y, float z);


	// Transforma el vector direction del espacio local al espacio global
	Vector3<float> transformDirection(Vector3<float> direction);
	// Transforma la posicion x, y, z del espacio local al espacio global
	Vector3<float> transformDirection(float x, float y, float z);

	// Transforma el vector direction del espacio global al espacio local
	Vector3<float> inverseTransformDirection(Vector3<float> direction);
	// Transforma la posicion x, y, z del espacio global al espacio local
	Vector3<float> inverseTransformDirection(float x, float y, float z);


private:
	// A�ade a un hijo a la lista
	void setChild(Transform* child) { _vChild.push_back(child); }
	// Elimina a un hijo de la lista
	void removeChild(Transform* child) { if (child->parent() == this) _vChild.remove(child); };

	void getParentData();

	Transform* _parent = nullptr;
	std::list<Transform*> _vChild;

	// En funcion del mundo (global)
	Vector3<float> _position;
	Quaternion _rotation;
	Vector3<float> _scale;

	// En funcion del padre (local)
	Vector3<float> _localPosition;
	Quaternion _localRotation;
	Vector3<float> _localScale;

};