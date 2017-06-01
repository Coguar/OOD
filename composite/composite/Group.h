#pragma once
#include "IShapesCollection.h"
#include <vector>

class Group : public IShapesCollection,
			public IShape,
			public std::enable_shared_from_this<Group>
{
public:

	IShapePtr GetShape(size_t index)const override;
	void AddShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(const IShapePtr &component) override;
	size_t ShapesCount() const override;

	OptionalStyle GetLineStyle()const override;
	void SetLineStyle(const CStyle& style) override;

	OptionalStyle GetFillStyle()const override;
	void SetFillStyle(const CStyle& style) override;

	RectD GetFrame() const override;
	void SetFrame(const RectD & rect) override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas & canvas) override;

private:
	std::vector<IShapePtr> m_shapes;
};

