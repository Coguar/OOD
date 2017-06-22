#include "stdafx.h"
#include "Menu.h"
#include "Document.h"
#include "IParagraph.h"
#include "IImage.h"

using namespace std;
using namespace std::placeholders;

namespace
{

class CEditor
{
public:
	CEditor()  //-V730
		:m_document(make_unique<Document>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
		m_menu.AddItem("list", "Show document listing", bind(&CEditor::List, this, _1));
		AddMenuItem("undo", "Undo command", &CEditor::Undo);
		AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
		AddMenuItem("insertParagraph", "Inserts paragraph. USAGE: insertParagraph <position>|end <paragraph text>", &CEditor::AddParagraph);
		AddMenuItem("insertImage", "Inserts image. USAGE: insertImage <position>|end <width> <height> <path_to_file>", &CEditor::AddImage);
		AddMenuItem("replaceText", "Replace paragraph text. USAGE: replaceText <position> <paragraph text>", &CEditor::ReplaceText);
		AddMenuItem("resizeImage", "Resize image. USAGE: resizeImage <position> <width> <height>", &CEditor::ResizeImage);
		AddMenuItem("deleteItem", "Delete item. USAGE: deleteItem <position>", &CEditor::DeleteItem);
		AddMenuItem("save", "Save document. USAGE: save <path>", &CEditor::Save);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	// ”казатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(istream & in);

	void AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, _1));
	}

	boost::optional<size_t> GetPosition(istream & in)
	{
		boost::optional<size_t> position;
		string positionStr;
		in >> positionStr;
		if (positionStr != "end")
		{
			position = stoul(positionStr);
		}
		return position;
	}

	// TODO: скипнуть первый пробел элегантнее
	void SetTitle(istream & in)
	{
		string head;
		string tail;

		if (in >> head)
		{
			getline(in, tail);
		}
		string title = head + tail;

		m_document->SetTitle(title);
	}

	void AddParagraph(istream & in)
	{

		boost::optional<size_t> position = GetPosition(in);
		string text;
		getline(in, text);

		m_document->InsertParagraph(text, position);
	}

	void AddImage(istream & in)
	{
		string positionStr;
		in >> positionStr;

		boost::optional<size_t> position;
		if (positionStr == "end")
		{
			position = boost::none;
		}
		else
		{
			position = stoul(positionStr);
		}

		int width;
		int height;
		in >> width >> height;

		string head;
		string path;
		if (in >> head)
		{
			getline(in, path);
		}
		path = head + path;

		m_document->InsertImage(path, width, height, position);

	}

	void List(istream & /*in*/)
	{
		cout << "-------------" << endl;
		cout << "Title: " << m_document->GetTitle() << endl;
		for (size_t i = 0; i < m_document->GetItemsCount(); ++i)
		{
			auto item = m_document->GetItem(i);
			if (auto paragraphPtr = item.GetParagraph())
			{
				cout << i << ".Paragraph: " << paragraphPtr->GetText() << endl;
			}
			else if (auto imagePtr = item.GetImage())
			{
				cout << i << ".Image: " << imagePtr->GetWidth() << " "<< imagePtr->GetHeight() << " "<< imagePtr->GetPath() << endl;
			}

		}
		cout << "-------------" << endl;

	}
	void ReplaceText(istream & in)
	{
		size_t position;
		in >> position;

		string text;
		getline(in, text);

		auto item = m_document->GetItem(position);
		if (auto paragraphPtr = item.GetParagraph())
		{
			paragraphPtr->SetText(text);
			return;
		}
		throw std::runtime_error("this is not parargaph");
	}

	void Save(istream & in)
	{
		string path;
		in.get();
		getline(in, path);
		if (path.empty())
		{
			cout << "path is empty" << endl;
			return;
		}
		m_document->Save(path);
	}

	void ResizeImage(istream & in)
	{
		size_t position;
		int width, height;
		in >> position >> width >> height;


		if (width < 1 || width > 10000)
		{
			throw std::invalid_argument("invalid image width");
		}
		if (height < 1 || height > 10000)
		{
			throw std::invalid_argument("invalid image height");
		}
		auto item = m_document->GetItem(position);
		if (auto imagePtr = item.GetImage())
		{
			imagePtr->Resize(width, height);
			return;
		}
		throw std::runtime_error("item isn't shape");
	}

	void DeleteItem(istream & in)
	{
		size_t position;
		in >> position;

		m_document->DeleteItem(position);
	}


	void Undo(istream &)
	{
		if (m_document->CanUndo())
		{
			m_document->Undo();
			return;
		}
			cout << "Can't undo" << endl;
	}

	void Redo(istream &)
	{
		if (m_document->CanRedo())
		{
			m_document->Redo();
			return;
		}
		cout << "Can't redo" << endl;
	}

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};

}

int main()
{
	CEditor editor;
	editor.Start();
	return 0;
}
