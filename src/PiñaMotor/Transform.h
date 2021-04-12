#pragma once
#include "Component.h"
#include "Vector3.h"
#include <list>

class Transform : public Component {
public:
	enum class Space {
		Self,
		World,
		Parent
	};

	Transform(Vector3 position, Vector3 rotation, Vector3 scale, Transform* parent = nullptr);

	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void translate(float x, float y, float z);
	void rotate(float xAngle, float yAngle, float zAngle, Space relativeTo = Space::Self);

	// Getter
	Transform* parent() { return _parent; }
	Transform* findChild(char* name);

	Vector3 position() { return _position; }
	Vector3 rotation() { return _rotation; }
	Vector3 scale() { return _scale; }

	Vector3 localPosition() { return _localPosition; }
	Vector3 localRotation() { return _localRotation; }
	Vector3 localScale() { return _localScale; }

	// Setter
	void setParent(Transform* parent);

	void setPosition(Vector3 v);
	void setPosition(float x, float y, float z);

	void setRotation(Vector3 v);
	void setRotation(float x, float y, float z);

	void setScale(Vector3 v);
	void setScale(float x, float y, float z);

	void setLocalPosition(Vector3 v);
	void setLocalPosition(float x, float y, float z);

	void setLocalRotation(Vector3 v);
	void setLocalRotation(float x, float y, float z);

	void setLocalScale(Vector3 v);
	void setLocalScale(float x, float y, float z);


	// Transforma el vector direction del espacio local al espacio global
	Vector3 transformDirection(Vector3 direction);
	// Transforma la posicion x, y, z del espacio local al espacio global
	Vector3 transformDirection(float x, float y, float z);

	// Transforma el vector direction del espacio global al espacio local
	Vector3 inverseTransformDirection(Vector3 direction);
	// Transforma la posicion x, y, z del espacio global al espacio local
	Vector3 inverseTransformDirection(float x, float y, float z);

private:
	// Añade a un hijo a la lista
	void setChild(Transform* child) { _vChild.push_back(child); }
	// Elimina a un hijo de la lista
	void removeChild(Transform* child) { if (child->parent() == this) _vChild.remove(child); };

	Transform* _parent = nullptr;
	list<Transform*> _vChild;

	// En funcion del mundo (global)
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;

	// En funcion del padre (local)
	Vector3 _localPosition;
	Vector3 _localRotation;
	Vector3 _localScale;
};