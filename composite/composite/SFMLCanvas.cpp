#include "stdafx.h"
#include "SFMLCanvas.h"


namespace
{
const float OUTLINE_THICKNESS = 2.f;
}

class EllipseShape : public sf::Shape
{
public:

	explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0)) :
		m_radius(radius)
	{
		update();
	}

	void setRadius(const sf::Vector2f& radius)
	{
		m_radius = radius;
		update();
	}

	const sf::Vector2f& getRadius() const
	{
		return m_radius;
	}

	unsigned int getPointCount() const override
	{
		return m_pointCount;
	}

	virtual sf::Vector2f getPoint(unsigned int index) const
	{
		float angle = float(index * 2.f * M_PI / m_pointCount - M_PI / 2.f);
		float x = std::cos(angle) * m_radius.x;
		float y = std::sin(angle) * m_radius.y;

		return sf::Vector2f(m_radius.x + x, m_radius.y + y);
	}

private:
	size_t m_pointCount = 40;
	sf::Vector2f m_radius;
};


SFMLCanvas::SFMLCanvas(sf::RenderTarget & window)
	: m_window(window)
	, m_isFilling(false)
{
}

SFMLCanvas::~SFMLCanvas()
{
}

void SFMLCanvas::SetLineColor(RGBAColor color)
{
	m_currentLineColor = ConvertUintToRGB(color);
}

void SFMLCanvas::BeginFill(RGBAColor color)
{
	m_currentfillColor = ConvertUintToRGB(color);
	m_isFilling = true;
}

void SFMLCanvas::EndFill()
{
	DrawFillingShape();
	m_isFilling = false;
}

void SFMLCanvas::MoveTo(double x, double y)
{
	m_currentPenPosition = { float(x), float(y) };
	if (m_isFilling)
	{
		m_points.push_back(m_currentPenPosition);
	}
}

void SFMLCanvas::LineTo(double x, double y)
{
	sf::Vertex line[] = 
	{
		sf::Vertex(m_currentPenPosition),
		sf::Vertex({ float(x), float(y) })
	};
	line[0].color = m_currentLineColor;
	line[1].color = m_currentLineColor;
	m_window.draw(line, OUTLINE_THICKNESS, sf::Lines);

	if (m_isFilling)
	{
		m_points.push_back(m_currentPenPosition);
	}
	MoveTo(x, y);
}

void SFMLCanvas::DrawEllipse(double left, double top, double width, double height)
{
	EllipseShape ellipse({ float(width / 2.f), float(height / 2.f) });
	ellipse.setPosition(float(left), float(top));
	ellipse.setOutlineColor(m_currentLineColor);
	ellipse.setOutlineThickness(OUTLINE_THICKNESS);
	ellipse.setFillColor({ 0,0,0,0 });
	if (m_isFilling)
	{
		ellipse.setFillColor(m_currentfillColor);
	}
	m_window.draw(ellipse);
}

void SFMLCanvas::DrawFillingShape()
{
	if (m_isFilling)
	{
		sf::ConvexShape convex;
		auto pointCount = m_points.size();
		convex.setPointCount(pointCount);
		convex.setFillColor(m_currentfillColor);
		convex.setOutlineColor(m_currentLineColor);
		convex.setOutlineThickness(OUTLINE_THICKNESS);
		for (size_t i = 0; i < pointCount; ++i)
		{
			convex.setPoint(i, m_points.at(i));
		}
		m_window.draw(convex);
		m_points.clear();
	}
}

sf::Color SFMLCanvas::ConvertUintToRGB(RGBAColor color)
{
	auto tempRgbColor = color;
	sf::Color rgbColor;
	rgbColor.b = int(((tempRgbColor) & 0x0000FF));
	rgbColor.g = int(((tempRgbColor >>= 8) & 0x0000FF));
	rgbColor.r = int(((tempRgbColor >>= 8) & 0x0000FF));
	return rgbColor;
}
