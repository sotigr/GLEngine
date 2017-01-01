#pragma once
#include "Vector2.h";
namespace OpenGL {
	class Viewport
	{
	private:
		Vector2<int>* _pos; 
		Vector2<int>* _size;
	public:
		Viewport();
		Viewport(int x, int y, int width, int height);
		~Viewport();
		const Vector2<int>* GetPosition();
		const Vector2<int>* GetSize();
		void SetPosition(int x, int y);
		void SetSize(int width, int height);
	};
}

