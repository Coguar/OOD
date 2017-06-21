#pragma once
#include "IImage.h"
#include "IHistory.h"

class Image 
	: public IImage
	, public std::enable_shared_from_this<IImage>
{
public:
	Image(const std::string& path, int width, int height,  IHistory& history);
	~Image();

	std::string GetPath()const override;
	int GetWidth()const override;
	int GetHeight()const override;
	void Resize(int width, int height) override;

	void SetSize(int width, int height) override;
private:

	int m_width = 0;
	int m_height = 0;

	std::string m_path;

	IHistory& m_history;
};

