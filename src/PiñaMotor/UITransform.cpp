#include "UITransform.h"

void UITransform::setWidth(int width) {
	_width = width;
}

void UITransform::setHeight(int height) {
	_height = height;
}

void UITransform::move(float xAxis, float yAxis) {
	_pos += Vector2<float>(xAxis, yAxis);
	for (auto it = _children.begin(); it != _children.end(); ++it)
		if ((*it) != nullptr) (*it)->getComponent<UITransform>()->move(xAxis, yAxis);
}

void UITransform::rotate(float rotation) {
	_rotation += rotation; if (_rotation > 360) _rotation -= 360;
	for (auto it = _children.begin(); it != _children.end(); ++it)
		if ((*it) != nullptr) (*it)->getComponent<UITransform>()->rotate(rotation);
}

void UITransform::setAbsolutePos(Vector2<float> pos) {
	Vector2<float> absPos = getAbsolutePos();
	move(pos.getX() - absPos.getX(), pos.getY() - absPos.getY());
}

void UITransform::setRelativePos(Vector2<float> pos) {
	move(pos.getX() - _pos.getX(), pos.getY() - _pos.getY());
}

void UITransform::setParent(Entity* parent) {
	_parent = parent;
	parent->getComponent<UITransform>()->addChild(_myEntity);
}

bool UITransform::addChild(Entity* child) {
	child->getComponent<UITransform>()->setParent(_myEntity);
	if (find(_children.begin(), _children.end(), child) == _children.end()) {
		_children.push_back(child);
		return true;
	}
	return false;
}

bool UITransform::removeChild(Entity* child) {
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
		UITransform* parent = _parent->getComponent<UITransform>();
		absPos = parent->getAbsolutePos();
		panel.setX(parent->getWidth()); panel.setY(parent->getHeight());
	};
	return absPos + Vector2<float>(_anchor.getX() * panel.getX() + _pos.getX(), _anchor.getY() * panel.getY() + _pos.getY());
};