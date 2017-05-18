#pragma once
#include "CommonTypes.h"
#include "Canvas.h"
#include <memory>
#include <numeric>
#include <vector>
#include <boost/variant.hpp>

namespace version1
{
enum StyleType {
	UnacceptableStyle = 0,
};

class CStyle
{
public:
	CStyle();

	bool IsEnabled()const;
	void Enable(bool enable);

	RGBAColor GetColor()const;
	void SetColor(RGBAColor color);

	friend bool operator==(const CStyle& left, const CStyle& right);
private:
	bool m_isEnable;
	RGBAColor m_color;
};

using StyleVariant = boost::variant<CStyle, StyleType>;

class Composite;

class IDrawable
{
public:
	virtual void Draw(ICanvas & canvas) = 0;

	virtual StyleVariant GetLineStyle()const = 0;
	virtual void SetLineStyle(const CStyle& style) = 0;

	virtual StyleVariant GetFillStyle()const = 0;
	virtual void SetFillStyle(const CStyle& style) = 0;

	virtual ~IDrawable() = default;
};

class IComponent : public IDrawable
{
public:
	virtual IComponent* GetComponent(size_t index)const = 0;
	virtual void AddComponent(IComponent* component, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual void RemoveComponent(IComponent* component) = 0;

	virtual Composite* GetComposite() = 0;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual ~IComponent() = default;
};

class Component : public IComponent
{
public:
	IComponent* GetComponent(size_t index)const override;
	void AddComponent(IComponent* component, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveComponent(IComponent* component) override;

	Composite* GetComposite() override;

	RectD GetFrame() const override;
	void SetFrame(const RectD & rect) override;

	StyleVariant GetLineStyle()const override;
	void SetLineStyle(const CStyle& style) override;

	StyleVariant GetFillStyle()const  override;
	void SetFillStyle(const CStyle& style) override;

private:
	RectD m_frame;

	CStyle m_lineStyle;
	CStyle m_fillStyle;
};


class CRectangle : public Component
{
public:
	CRectangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CEllipse : public Component
{
public:
	CEllipse(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CTriangle : public Component
{
public:
	CTriangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CSlide
{
public:
	double GetWidth()const;
	double GetHeight()const;

	size_t GetShapesCount()const;
	IComponent* GetShapeAtIndex(size_t index);
	void InsertShape(IComponent* shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);

	RGBAColor GetBackgroundColor()const;
	void SetBackgroundColor(RGBAColor color);

	void Draw(ICanvas & canvas);

private:
	void UpdateFrame();

	double m_width = 0;
	double m_height = 0;
	
	RGBAColor m_backgroundColor;

	std::vector<IComponent*> m_components;
	
};

class Composite : public Component
{
public: 
	IComponent* GetComponent(size_t index)const final;
	void AddComponent(IComponent* component, size_t position = std::numeric_limits<size_t>::max()) final;
	void RemoveComponent(IComponent* component) final;

	Composite* GetComposite() final;

	void Draw(ICanvas & canvas) final;

	StyleVariant GetLineStyle()const final;
	void SetLineStyle(const CStyle& style) final;

	StyleVariant GetFillStyle()const  final;
	void SetFillStyle(const CStyle& style) final;
private:
	void UpdateFrame();

	std::vector<IComponent*> m_components;
};

}