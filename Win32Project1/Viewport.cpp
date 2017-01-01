#include "Viewport.h"

OpenGL::Viewport::Viewport() {
	this->_pos = new Vector2<int>();
	this->_size = new Vector2<int>();
}
OpenGL::Viewport::Viewport(int x, int y, int width, int height) {
	this->_pos = new Vector2<int>();
	this->_size = new Vector2<int>();
	this->_pos->x(x);
	this->_pos->y(y);
	this->_size->x(width);
	this->_size->y(height);
}
OpenGL::Viewport::~Viewport() {
	delete this->_pos;
	delete this->_size;
}
const Vector2<int>* OpenGL::Viewport::GetPosition() {
	return this->_pos;
}
const Vector2<int>* OpenGL::Viewport::GetSize() {
	return this->_size;
}
void OpenGL::Viewport::SetPosition(int x, int y) {
	this->_pos->x(x);
	this->_pos->y(y);
}
void OpenGL::Viewport::SetSize(int width, int height) {
	this->_size->x(width);
	this->_size->y(height);
}