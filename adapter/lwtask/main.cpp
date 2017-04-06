#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <cstdint>
#include <iomanip>

using namespace std;

// Пространство имен графической библиотеки (недоступно для изменения)
namespace graphics_lib
{
// Холст для рисования
class ICanvas
{
public:
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
};
}

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point & p1, const Point & p2, const Point & p3)
		: m_vertex1(p1)
		, m_vertex2(p2)
		, m_vertex3(p3)
	{
	}

	void Draw(graphics_lib::ICanvas & canvas)const override
	{
		canvas.MoveTo(m_vertex1.x, m_vertex1.y);
		canvas.LineTo(m_vertex2.x, m_vertex2.y);
		canvas.LineTo(m_vertex3.x, m_vertex3.y);
		canvas.LineTo(m_vertex1.x, m_vertex1.y);
	}
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;

};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point & leftTop, int width, int height)
		: m_topLeft(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(graphics_lib::ICanvas & canvas)const override
	{
		canvas.MoveTo(m_topLeft.x, m_topLeft.y);
		canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y);
		canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y + m_height);
		canvas.LineTo(m_topLeft.x, m_topLeft.y + m_height);
		canvas.LineTo(m_topLeft.x, m_topLeft.y);
	}
private:
	Point m_topLeft;
	int m_width;
	int m_height;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas & canvas)
		: m_canvas(canvas)
	{
	}
	void Draw(const ICanvasDrawable & drawable)
	{
		drawable.Draw(m_canvas);
	}
private:
	graphics_lib::ICanvas & m_canvas;
};
}

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
class CPoint
{
public:
	CPoint(int x, int y) :x(x), y(y) {}

	int x;
	int y;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(ostream & strm) : m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint & start, const CPoint & end)
	{
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)") % start.x % start.y % end.x % end.y << endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}
private:
	ostream & m_out;
	bool m_drawing = false;
};
}

// Пространство имен приложения (доступно для модификации)
namespace app
{

class CanvasClassAdaptor
	: public graphics_lib::ICanvas
	, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CanvasClassAdaptor(ostream & strm)
		: modern_graphics_lib::CModernGraphicsRenderer(strm)
		, m_x(0)
		, m_y(0)
	{}

	void MoveTo(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	void LineTo(int x, int y)
	{
		BeginDraw();
		DrawLine({ m_x, m_y }, { x, y });
		EndDraw();
		MoveTo(x, y);
	}

private:
	int m_x;
	int m_y;
};

class CanvasAdaptor : public graphics_lib::ICanvas
{
public:
	CanvasAdaptor(modern_graphics_lib::CModernGraphicsRenderer & renderer)
		: m_renderer(renderer)
		, m_x(0)
		, m_y(0)
	{
	}
	virtual void MoveTo(int x, int y) override
	{
		m_x = x;
		m_y = y;
	}
	virtual void LineTo(int x, int y) override
	{
		m_renderer.BeginDraw();
		m_renderer.DrawLine({ m_x, m_y }, { x, y });
		m_renderer.EndDraw();
		MoveTo(x, y);
	}


private:
	modern_graphics_lib::CModernGraphicsRenderer & m_renderer;
	int m_x;
	int m_y;
};

void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
	CanvasAdaptor canvasAdaptor(renderer);

	CanvasClassAdaptor canvasClassAdapter(cout);
	shape_drawing_lib::CCanvasPainter painter(canvasClassAdapter);
	PaintPicture(painter);
}
}

namespace graphics_lib_pro
{
// Холст для рисования
class ICanvas
{
public:
	// Установка цвета в формате 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		cout << "#" << hex << setw(6) << setfill('0') << rgbColor << endl;
	}
	void MoveTo(int x, int y) override
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
};
}

// Пространство имен обновленной современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib_pro
{
class CPoint
{
public:
	CPoint(int x, int y) :x(x), y(y) {}

	int x;
	int y;
};

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a):r(r), g(g), b(b), a(a){}
	float r, g, b, a;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(ostream & strm) : m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
	{
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % start.x % start.y % end.x % end.y << endl;
		m_out << boost::format(R"(<color r="%1%" g="%2%" b="%3%" a="%4%" />)") % color.r % color.g % color.b % color.a << endl;
		m_out << "</line>" << endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}
private:
	ostream & m_out;
	bool m_drawing = false;
};

}

namespace app_pro
{

class CanvasAdaptor : public graphics_lib_pro::ICanvas
{
public:
	CanvasAdaptor(modern_graphics_lib_pro::CModernGraphicsRenderer & renderer)
		: m_renderer(renderer)
		, m_currentColor(0,0,0,1)
		, m_x(0)
		, m_y(0)
	{

	}

	void SetColor(uint32_t rgbColor) override
	{
		auto tempRgbColor = rgbColor;
		m_currentColor.b = ((tempRgbColor) * 0x0000FF) / 256.f;
		m_currentColor.g = ((tempRgbColor >>= 8) * 0x0000FF) / 256.f;
		m_currentColor.r = ((tempRgbColor >>= 8) * 0x0000FF) / 256.f;
	}

	void MoveTo(int x, int y) override
	{
		m_x = x;
		m_y = y;
	}
	void LineTo(int x, int y)override
	{
		m_renderer.BeginDraw();
		m_renderer.DrawLine({ m_x, m_y }, { x, y }, m_currentColor);
		m_renderer.EndDraw();
		MoveTo(x, y);
	}

private:
	modern_graphics_lib_pro::CModernGraphicsRenderer & m_renderer;
	modern_graphics_lib_pro::CRGBAColor m_currentColor;
	int m_x;
	int m_y;
};

}

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}
	return 0;
}
