#include "stdafx.h"
#include "Document.h"
#include "History.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "Image.h"
#include "Paragraph.h"

Document::Document()
	: m_history(std::make_unique<History>())
{
	m_workingFolder = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path("%%%%%%%").string();
	boost::filesystem::create_directory(m_workingFolder);
	boost::filesystem::create_directory(m_workingFolder / "images");
}


Document::~Document()
{
}

std::string Document::GetTitle() const
{
	return m_title;
}

void Document::SetTitle(const std::string & title)
{
	m_title = title;
}

bool Document::CanUndo() const
{
	return m_history->CanUndo();
}

void Document::Undo()
{
	m_history->Undo();
}

bool Document::CanRedo() const
{
	return m_history->CanRedo();
}

void Document::Redo()
{
	m_history->Redo();
}

CConstDocumentItem Document::GetItem(size_t index) const
{
	if (index > m_items.size())
	{
		throw std::logic_error("Index of item out of range");
	}
	return m_items.at(index);
}

CDocumentItem Document::GetItem(size_t index)
{
	if (index > m_items.size())
	{
		throw std::logic_error("Index of item out of range");
	}
	return m_items.at(index);
}

size_t Document::GetItemsCount() const
{
	return m_items.size();
}

void Document::DeleteItem(size_t index)
{
	//command to delete item
}

ImagePtr Document::InsertImage(const std::string & path, int width, int height, optional<size_t> position)
{
	size_t index = position ? *position : m_items.size();
	if (index > m_items.size())
	{
		throw std::logic_error("Index of item out of range");
	}
	if (!boost::filesystem::exists(path))
	{
		throw std::invalid_argument("Image not found");
	}
	if (width > 1000)
	{
		throw std::invalid_argument("Image width is Unacceptable");
	}
	if (height > 1000)
	{
		throw std::invalid_argument("Image width is Unacceptable");
	}
	auto ext = boost::filesystem::path(path).extension();
	std::string imgName = boost::filesystem::unique_path("img%%%%%%%" + ext.string()).string();
	auto pathToImg = m_workingFolder / "images" / imgName;

	boost::filesystem::copy_file(path, pathToImg, boost::filesystem::copy_option::overwrite_if_exists);

	auto imgPtr = std::make_shared<Image>(pathToImg, width, height, *m_history);
	//add command
	return ImagePtr();
}

ParagraphPtr Document::InsertParagraph(const std::string & text, optional<size_t> position)
{
	size_t index = position ? *position : m_items.size();
	if (index > m_items.size())
	{
		throw std::logic_error("Index of item out of range");
	}

	auto parPtr = std::make_shared<Paragraph>(text, *m_history);
	//add command
	return ParagraphPtr();
}
