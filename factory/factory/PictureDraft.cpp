#include "stdafx.h"
#include "PictureDraft.h"
#include "Shape.h"

CPictureDraft::CPictureDraft()
{
}


CPictureDraft::~CPictureDraft() = default;

size_t CPictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

std::shared_ptr<CAbstractShape> CPictureDraft::GetShape(size_t position) const
{
	if (position < m_shapes.size())
	{
		return m_shapes[position];
	}
	else
	{
		return std::shared_ptr<CAbstractShape>();
	}
}

const std::vector<std::shared_ptr<CAbstractShape>>& CPictureDraft::GetShapesList() const
{
	return m_shapes;
}

void CPictureDraft::AddShape(std::shared_ptr<CAbstractShape> const & shape)
{
	m_shapes.push_back(shape);
}
