#pragma once
#include "Canvas.h"
#include "Style.h"
#include <memory>
#include <numeric>

class IShapesCollection;
class IShape;

using IGroupPtr = std::shared_ptr<IShapesCollection>;
using IShapePtr = std::shared_ptr<IShape>;

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw(ICanvas & canvas) = 0;
};

class IShape : public IDrawable
{
public:
	virtual ~IShape() = default;

	virtual OptionalStyle GetLineStyle()const = 0;
	virtual void SetLineStyle(const CStyle& style) = 0;

	virtual OptionalStyle GetFillStyle()const = 0;
	virtual void SetFillStyle(const CStyle& style) = 0;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual IGroupPtr GetGroup() = 0;
};