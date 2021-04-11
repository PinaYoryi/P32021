#pragma once

#include "Component.h"
#include "Entity.h"
#include "Vector2.h"
#include <list>

//TODO: Habría que conseguir esto llamando a un get que no hay todavía
const int WIN_HEIGHT = 1000;
const int WIN_WIDTH = 1000;

/// <summary>
/// Componente transform para lo elementos de la UI. Tiene un padre y una lista de hijos 
/// y las posiciones de cada UITransform son relativas a la de su padre.
/// 
/// Eliminar un UITransform elimina a todos sus hijos existentes y lo quita de la lista de 
/// hijos de su padre.
/// </summary>
class UITransform : public Component {
public:
	UITransform() : _width(0), _height(0), _parent(nullptr), _anchor(Vector2<float>(0, 0)) {
		_children = list<Entity*>();
	}

	~UITransform() {
		if (_parent != nullptr) _parent->getComponent<UITransform>()->removeChild(_myEntity);
		for (auto it = _children.begin(); it != _children.end(); ++it)
			if ((*it) != nullptr) delete (*it); //TODO: Esto no deberia ser un delete sino que deberia borrarlo en juego.
	}

	bool init(const map<std::string, std::string>& mapa) override {}

#pragma region Setters
	/// <summary>
	/// Fija el tamaño horizontal del objeto.
	/// </summary>
	void setWidth(int width);
	/// <summary>
	/// Fija el tamaño vertical del objeto.
	/// </summary>
	void setHeight(int height);
	/// <summary>
	/// Mueve el objeto en relación a la posicion actual
	/// </summary>
	void move(float xAxis, float yAxis);
	/// <summary>
	/// Rota el objeto en relación a la posicion actual
	/// </summary>
	void rotate(float rotation);
	/// <summary>
	/// Fija la posición del objeto en pantalla.
	/// </summary>
	void setAbsolutePos(Vector2<float> pos);
	/// <summary>
	/// Fija la posición del objeto respecto a su padre.
	/// </summary>
	void setRelativePos(Vector2<float> pos);
	/// <summary>
	/// Fija la posición a la que se ancla en objeto respecto a su padre.
	/// Valores del 0 al 1 siendo estos los extremos de cada eje.
	/// </summary>
	void setAnchor(Vector2<float> anchor) { _anchor = anchor; }
	/// <summary>
	/// Asigna el padre del objeto.
	/// </summary>
	void setParent(Entity* parent);
	/// <summary>
	/// Añade un hijo a la lista de hijos. Devuelve true si se ha añadido y false si ya estaba en la lista.
	/// </summary>
	bool addChild(Entity* child);
	/// <summary>
	/// Elimina a un hijo a la lista de hijos. Devuelve true si se ha eliminado y false si no estaba en la lista.
	/// </summary>
	bool removeChild(Entity* child);
#pragma endregion

#pragma region Getters
	/// <summary>
	/// Devuelve el tamaño horizontal del objeto.
	/// </summary>
	int getWidth() { return _width; };
	/// <summary>
	/// Devuelve el tamaño vertical del objeto.
	/// </summary>
	int getHeight() { return _width; };
	/// <summary>
	/// Devuelve la posicion en pantalla del objeto.
	/// </summary>
	Vector2<float> getAbsolutePos();
	/// <summary>
	/// Devuelve la posicion del objeto respecto a la de su padre.
	/// </summary>
	Vector2<float> getRelativePos() { return _pos; };
	/// <summary>
	/// Devuelve la posicion del ancla del objeto.
	/// Valores del 0 al 1 siendo estos los extremos de cada eje.
	/// </summary>
	Vector2<float> getAnchor() { return _anchor; };
	/// <summary>
	/// Devuelve un puntero al padre del objeto.
	/// </summary>
	Entity* getParent() { return _parent; };
	/// <summary>
	/// Devuelve una lista de punteros con los hijos del objeto.
	/// </summary>
	std::list<Entity*> getChildren() { return _children; };
#pragma endregion

#pragma region Anclas Predefinidos
	static const Vector2<float> up() { return Vector2<float>(0.5, 1.0); }
	static const Vector2<float> down() { return Vector2<float>(0.5, 0.0); }
	static const Vector2<float> left() { return Vector2<float>(0.0, 0.5); }
	static const Vector2<float> right() { return Vector2<float>(1.0, 0.5); }
	static const Vector2<float> zero() { return Vector2<float>(0.0, 0.0); }
#pragma endregion

protected:
	int _width;
	int _height;
	float _rotation;
	Vector2<float> _pos;
	Vector2<float> _anchor;
	Entity* _parent;
	list<Entity*> _children;
};