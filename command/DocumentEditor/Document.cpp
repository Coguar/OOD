#include "stdafx.h"
#include "Document.h"
#include "Image.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"
#include "DeleteCommand.h"
#include "InsertImageCommand.h"
#include "InsertParagraphCommand.h"

namespace
{

std::string HtmlEscape(std::string const& text)
{
	using boost::algorithm::replace_all;
	std::string str(text);
	boost::algorithm::replace_all(str, "&", "&amp;");
	boost::algorithm::replace_all(str, "\"", "&quot;");
	boost::algorithm::replace_all(str, "\'", "&apos;");
	boost::algorithm::replace_all(str, "<", "&lt;");
	boost::algorithm::replace_all(str, ">", "&gt;");
	return str;
}

void CreateFolderIfNotExists(const boost::filesystem::path& path)
{
	if (!boost::filesystem::exists(boost::filesystem::path(path)))
	{
		boost::filesystem::create_directory(path);
	}
}
}

Document::Document()
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
	m_history.ExecuteCommand(std::make_unique<CChangeStringCommand>(m_title, title));
}

bool Document::CanUndo() const
{
	return m_history.CanUndo();
}

void Document::Undo()
{
	m_history.Undo();
}

bool Document::CanRedo() const
{
	return m_history.CanRedo();
}

void Document::Redo()
{
	m_history.Redo();
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
	if (index >= m_items.size())

	{
		throw std::logic_error("Index of item out of range");
	}
	m_history.ExecuteCommand(std::make_unique<DeleteCommand>(index, m_items));
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

	auto imgPtr = std::make_shared<Image>(pathToImg.string(), width, height, m_history);
	m_history.ExecuteCommand(std::make_unique<InsertImageCommand>(m_items, imgPtr, index));
	return ImagePtr();
}

ParagraphPtr Document::InsertParagraph(const std::string & text, optional<size_t> position)
{
	size_t index = position ? *position : m_items.size();
	if (index > m_items.size())
	{
		throw std::logic_error("Index of item out of range");
	}

	auto parPtr = std::make_shared<Paragraph>(text, m_history);
	m_history.ExecuteCommand(std::make_unique<InsertParagraphCommand>(m_items, parPtr, index));
	return ParagraphPtr();
}

void Document::Save(const std::string & path) const
{
	using namespace std;
	std::ofstream output(path);
	if (!output.is_open())
	{
		throw std::runtime_error("failed to open " + path + " to writing");
	}
	output << "<!DOCTYPE html>" << endl	<< "<html>" << endl	<< "\t<head>" << endl << "\t\t<title>" 
		<< HtmlEscape(GetTitle()) << "</title>" << endl	<< "\t</head>" << endl	<< "\t<body>" << endl;

	auto pathToImages = boost::filesystem::path(path).parent_path() / "images";
	CreateFolderIfNotExists(pathToImages);
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		auto item = m_items[i];
		if (auto paragraphPtr = item.GetParagraph())
		{
			output << "\t\t<p>" << HtmlEscape(paragraphPtr->GetText()) << "</p>" << endl;
		}
		else if (auto imagePtr = item.GetImage())
		{
			boost::format imageFormat(R"(		<img src="%1%" width="%2%" height="%3%"/>)");
			output << imageFormat % HtmlEscape(imagePtr->GetPath()) % imagePtr->GetWidth() % imagePtr->GetHeight() << endl;
			boost::filesystem::copy_file(
				boost::filesystem::path(m_workingFolder) / imagePtr->GetPath(),
				boost::filesystem::path(path).parent_path() / imagePtr->GetPath(),
				boost::filesystem::copy_option::overwrite_if_exists);
		}
	}
	output << "\t</body>" << endl<< "</html>";
	output.close();
}
