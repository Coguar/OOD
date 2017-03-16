#pragma once

class CAbstractShape;

class CPictureDraft
{
public:
	CPictureDraft();
	~CPictureDraft();

	size_t GetShapeCount() const;
	std::shared_ptr<CAbstractShape> GetShape(size_t position) const;

	const std::vector<std::shared_ptr<CAbstractShape>>& GetShapesList() const;

	void AddShape(std::shared_ptr<CAbstractShape> const& shape);

private:
	std::vector<std::shared_ptr<CAbstractShape>> m_shapes;
};

