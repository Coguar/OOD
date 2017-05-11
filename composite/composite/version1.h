#pragma once
#include "CommonTypes.h"
#include "Canvas.h"
#include <memory>
#include <numeric>
#include <vector>

namespace version1
{

class CStyle
{
public:
	CStyle();

	bool IsEnabled()const;
	void Enable(bool enable);

	RGBAColor GetColor()const;
	void SetColor(RGBAColor color);

private:
	bool m_isEnable;
	RGBAColor m_color;
};

class CShape
{
public:
	RectD GetFrame();
	void SetFrame(const RectD & rect);

	CStyle GetLineStyle()const;
	void SetLineStyle(const CStyle& style);

	CStyle GetFillStyle()const;
	void SetFillStyle(const CStyle& style);

	virtual void Draw(ICanvas & canvas) = 0;

	virtual ~CShape() = default;

private:
	RectD m_frame;
	CStyle m_lineStyle;
	CStyle m_fillStyle;
};

class CRectangle : public CShape
{
public:
	CRectangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CEllipse : public CShape
{
public:
	CEllipse(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CTriangle : public CShape
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
	std::shared_ptr<CShape> GetShapeAtIndex(size_t index);
	void InsertShape(const std::shared_ptr<CShape> & shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);

	RGBAColor GetBackgroundColor()const;
	void SetBackgroundColor(RGBAColor color);

	void Draw(ICanvas & canvas);

private:
	void UpdateFrame();

	double m_width = 0;
	double m_height = 0;
	
	RGBAColor m_backgroundColor;

	std::vector<std::shared_ptr<CShape>> m_shapes;
	
};

class IGroup : public CShape
{
public:
	virtual ~IGroup() = default;
	virtual size_t GetShapesCount()const = 0;
	virtual std::shared_ptr<CShape> GetShapeAtIndex(size_t index) = 0;
	virtual void InsertShape(const std::shared_ptr<CShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
};

class CGroup : public IGroup
{
public: 
	size_t GetShapesCount()const override;
	std::shared_ptr<CShape> GetShapeAtIndex(size_t index) override;
	void InsertShape(const std::shared_ptr<CShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;
	void Draw(ICanvas & canvas) final;

private:
	void UpdateFrame();

	std::vector<std::shared_ptr<CShape>> m_shapes;
};

}