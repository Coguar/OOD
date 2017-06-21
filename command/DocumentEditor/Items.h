#pragma once

class IParagraph;
class IImage;

using ParagraphPtr = std::shared_ptr<IParagraph>;
using ImagePtr = std::shared_ptr<IImage>;

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(const ParagraphPtr& paragraph);
	CConstDocumentItem(const ImagePtr& image);


	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<const IImage> GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;

private:
	ParagraphPtr m_paragraph = nullptr;
	ImagePtr m_image = nullptr;
};

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(const ParagraphPtr& paragraph);
	CDocumentItem(const ImagePtr& image);

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();

private:
	ParagraphPtr m_paragraph = nullptr;
	ImagePtr m_image = nullptr;
};
