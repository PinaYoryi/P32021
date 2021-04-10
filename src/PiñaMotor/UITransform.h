#pragma once

#include "Component.h"
#include "Vector2.h"
#include <list>

class UITransform : public Component {
public:
	UITransform() : _width(0), _height(0), _parent(nullptr) {
		_children = std::list<UITransform*>();
	}

	void setWidth(float width);
	void setHeight(float height);
	void setAbsolutePos(Vector2<float> pos);
	void setRelativePos(Vector2<float> pos);
	void setParent(UITransform parent);
	bool addChild(UITransform child);
	bool removeChild(UITransform child);

	float getWidth() { return _width; };
	float getHeight() { return _width; };
	Vector2<float> getAbsolutePos() {
		if (_parent == nullptr) return _pos;
		return _pos + _parent->getAbsolutePos();
	};
	Vector2<float> getRelativePos() { return _pos; };
	UITransform* getParent() { return _parent; };
	std::list<UITransform*> getChildren() { return _children; };

protected:
	float _width;
	float _height;
	Vector2<float> _pos;
	UITransform* _parent;
	std::list<UITransform*> _children;
};