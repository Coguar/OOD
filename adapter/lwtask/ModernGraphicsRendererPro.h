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

// ����� ��� ������������ ��������� �������
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream & strm);

	~CModernGraphicsRenderer();

	// ���� ����� ������ ���� ������ � ������ ���������
	void BeginDraw();

	// ��������� ��������� �����
	void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color);

	// ���� ����� ������ ���� ������ � ����� ���������
	void EndDraw();
private:
	std::ostream & m_out;
	bool m_drawing = false;
};

}