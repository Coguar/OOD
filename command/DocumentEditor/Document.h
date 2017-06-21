#pragma once
#include "IDocument.h"

class Document : public IDocument
{
public:
	Document();
	~Document();

	std::string GetTitle()const override;
	void SetTitle(const std::string & title) override;

	bool CanUndo()const override;
	void Undo() override;

	bool CanRedo()const override;
	void Redo() override;

	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	size_t GetItemsCount()const override;

	void DeleteItem(size_t index) override;
	ImagePtr InsertImage(const std::string& path, int width, int height, optional<size_t> position = none) override;
	ParagraphPtr InsertParagraph(const std::string& text, optional<size_t> position = none) override;

private:
	std::unique_ptr<IHistory> m_history;

	std::string m_title;

	std::vector<CDocumentItem> m_items;
	boost::filesystem::path m_workingFolder;
};

