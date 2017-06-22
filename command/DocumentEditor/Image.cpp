#include "stdafx.h"
#include "Image.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "ResizeImageCommand.h"

Image::Image(const std::string & path, int width, int height, IHistory & history)
	: m_history(history)
	, m_width(width)
	, m_height(height)
	, m_path(path)
{
}

Image::~Image()
{
	if (boost::filesystem::exists(m_path))
	{
		boost::filesystem::remove(m_path);
	}
}

std::string Image::GetPath() const
{
	boost::filesystem::path fileName = boost::filesystem::path(m_path).filename();
	boost::filesystem::path folderName = boost::filesystem::path(m_path).parent_path().filename();
	return  (folderName / fileName).generic_string();
}

int Image::GetWidth() const
{
	return m_width;
}

int Image::GetHeight() const
{
	return m_height;
}

void Image::Resize(int width, int height)
{
	m_history.ExecuteCommand(std::make_unique<ResizeImageCommand>(shared_from_this(), m_width, m_height, width, height));
}

void Image::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}
