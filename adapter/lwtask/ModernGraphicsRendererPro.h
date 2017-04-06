#pragma once

namespace modern_graphics_lib_pro
{
class CPoint
{
public:
	CPoint(int x, int y) :x(x), y(y) {}

	int x;
	int y;
};

class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a);
	float r;
	float g;
	float b;
	float a;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream & strm);

	~CModernGraphicsRenderer();

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw();

	// Выполняет рисование линии
	void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color);

	// Этот метод должен быть вызван в конце рисования
	void EndDraw();
private:
	std::ostream & m_out;
	bool m_drawing = false;
};

}