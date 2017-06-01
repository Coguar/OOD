#pragma once
#include "Canvas.h"
#include <SFML\Graphics.hpp>

class SFMLCanvas :
	public ICanvas
{
public:
	SFMLCanvas(sf::RenderTarget & window);
	~SFMLCanvas();

	static sf::Color ConvertUintToRGB(RGBAColor color);

	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;

private:
	void DrawFillingShape();

	sf::Color m_currentLineColor;
	sf::Color m_currentfillColor;

	sf::Vector2f m_currentPenPosition;

	bool m_isFilling;

	sf::RenderTarget & m_window;

	std::vector<sf::Vector2f> m_points;
};

