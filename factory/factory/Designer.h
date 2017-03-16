#pragma once
#include "ShapeFactoryInterface.h"
#include "DesignerInterface.h"

class CDesigner :
	public IDesigner
{
public:
	CDesigner();
	~CDesigner();
	CPictureDraft CreateDraft(std::istream & strm) override;

private:
	std::unique_ptr<IShapeFactory> m_shapeFactory;
};

