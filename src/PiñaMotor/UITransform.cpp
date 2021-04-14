#include "UITransform.h"

UITransform::UITransform() : _width(0), _height(0), _parent(nullptr), _anchor(Vector2<float>(0, 0)) {
	_children = list<UITransform*>();
}

UITransform::~UITransform() {
	if (_parent != nullptr) _parent->removeChild(this);
	UITransform* temp;
	while (_children.size() > 0) {
		temp = _children.front();
		_children.pop_front();
		delete temp->_myEntity;
	}
	/*for (auto it = _children.begin(); it != _children.end(); ++it)
		if ((*it) != nullptr) delete (*it)->_myEntity; //TODO: Esto no deberia ser un delete sino que deberia borrarlo en juego.*/
}

void UITransform::setWidth(int width) {
	_width = width;
}

void UITransform::setHeight(int height) {
	_height = height;
}

void UITransform::move(float xAxis, float yAxis) {
	_pos += Vector2<float>(xAxis, yAxis);
	for (auto it = _children.begin(); it != _children.end(); ++it)
		if ((*it) != nullptr) (*it)->move(xAxis, yAxis);
}

void UITransform::rotate(float rotation) {
	_rotation += rotation; if (_rotation > 360) _rotation -= 360;
	for (auto it = _children.begin(); it != _children.end(); ++it)
		if ((*it) != nullptr) (*it)->rotate(rotation);
}

void UITransform::setAbsolutePos(Vector2<float> pos) {
	Vector2<float> absPos = getAbsolutePos();
	move(pos.getX() - absPos.getX(), pos.getY() - absPos.getY());
}

void UITransform::setRelativePos(Vector2<float> pos) {
	move(pos.getX() - _pos.getX(), pos.getY() - _pos.getY());
}

void UITransform::setParent(UITransform* parent) {
	_parent = parent;
	parent->addChild(this);
}

bool UITransform::addChild(UITransform* child) {
	if (find(_children.begin(), _children.end(), child) == _children.end()) {
		_children.push_back(child);
		return true;
	}
	return false;
}

bool UITransform::removeChild(UITransform* child) {
	auto it = find(_children.begin(), _children.end(), child);
	if (it != _children.end()) {
		_children.erase(it);
		return true;
	}
	return false;
}

Vector2<float> UITransform::getAbsolutePos() {
	Vector2<float> panel = Vector2<float>(WIN_WIDTH, WIN_HEIGHT);
	Vector2<float> absPos = Vector2<float>::zero();
	if (_parent != nullptr) {
		absPos = _parent->getAbsolutePos();
		panel.setX(_parent->getWidth()); panel.setY(_parent->getHeight());
	};
	return absPos + Vector2<float>(_anchor.getX() * panel.getX() + _pos.getX(), _anchor.getY() * panel.getY() + _pos.getY());
};