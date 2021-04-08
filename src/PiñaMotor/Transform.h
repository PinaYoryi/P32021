#pragma once
#include "Component.h"
#include "Vector3.h"

class Transform : public Component {
public:
	enum Space {
		Self,
		World
	};

	Transform(Vector3 position, Vector3 rotation, Vector3 scale, Transform* parent = nullptr) :
	_parent(parent), _position(position), _rotation(rotation), _scale(scale) {
		if (parent == nullptr) {
			_localPosition = _position;
			_localRotation = _rotation;
			_localScale = _scale;
		}
		else {
			_localPosition = InverseTransformDirection(parent->position());
			_localRotation = InverseTransformDirection(parent->rotation());
			_localScale = InverseTransformDirection(parent->scale());
		}
	}
	
	bool init(const std::map<std::string, std::string>& mapa) override {
		return true;
	}

	void translate(float x, float y, float z) {
		//Cambiamos la posicion sumando x, y, z
	}
	void rotate(float xAngle, float yAngle, float zAngle, Space relativeTo = Space::Self) {
		if (relativeTo == Space::Self) {
			//Cambiamos la rotacion x, y, z angulo
		}
		else {
			//Transladamos el obj al centro (guardamos la direccion)
			//Rotamos x, y, z angulo
			//Volvemos a transladar el obj habiendo rotado tb la direccion
		}
	}
	
	//Getter
	Transform* parent() { return _parent; }
	Transform* getChild(char* name) {
		for (auto c : _vChild) {
			if (c->getEntity()->getName() == name)
				return c;
		}
	}
	
	Vector3 localPosition() { return _localPosition; }
	Vector3 localRotation() { return _localRotation; }
	Vector3 localScale() { return _localScale; }
	
	Vector3 position() { return _position; }
	Vector3 rotation() { return _rotation; }
	Vector3 scale() { return _scale; }
	
	//Setter
	void parent(Transform* parent) { _parent = parent; }
	void child(Transform* child) { _vChild.push_back(child); }

	void localPosition(Vector3 v) { _localPosition = v; }
	void localPosition(float x, float y, float z) { _localPosition = { x, y, z }; }
	
	void localRotation(Vector3 v) { _localRotation = v; }
	void localRotation(float x, float y, float z) { _localRotation = { x, y, z }; }
	
	void localScale(Vector3 v) { _localScale = v; }
	void localScale(float x, float y, float z) { _localScale = { x, y, z }; }
	
	void position(Vector3 v) { _position = v; }
	void position(float x, float y, float z) { _position = { x, y, z }; }
	
	void rotation(Vector3 v) { _rotation = v; }
	void rotation(float x, float y, float z) { _rotation = { x, y, z }; }
	
	void scale(Vector3 v) { _scale = v; }
	void scale(float x, float y, float z) { _scale = { x, y, z }; }
	
	//Transforma el vector direction del espacio local al espacio global
	Vector3 TransformDirection(Vector3 direction) {
		return { abs(direction.getX() + _parent->localPosition().getX()),
				 abs(direction.getY() + _parent->localPosition().getY()),
				 abs(direction.getZ() + _parent->localPosition().getZ()) };
	}
	//Transforma la posicion x, y, z del espacio local al espacio global
	Vector3 TransformDirection(float x, float y, float z) {
		return { abs(x + _parent->localPosition().getX()),
				 abs(y + _parent->localPosition().getY()),
				 abs(z + _parent->localPosition().getZ()) };
	}
	
	//Transforma el vector direction del espacio global al espacio local
	Vector3 InverseTransformDirection(Vector3 direction) {
		return { abs(direction.getX() - _parent->localPosition().getX()),
				 abs(direction.getY() - _parent->localPosition().getY()),
				 abs(direction.getZ() - _parent->localPosition().getZ()) };
	}
	//Transforma la posicion x, y, z del espacio global al espacio local
	Vector3 InverseTransformDirection(float x, float y, float z) {
		return { abs(x - _parent->localPosition().getX()),
				 abs(y - _parent->localPosition().getY()),
				 abs(z - _parent->localPosition().getZ()) };
	}

private:
	Transform* _parent = nullptr;
	list<Transform*> _vChild;

	//En funcion del padre (local)
	Vector3 _localPosition;
	Vector3 _localRotation;
	Vector3 _localScale;
	
	//En funcion del mundo (global)
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _scale;
};