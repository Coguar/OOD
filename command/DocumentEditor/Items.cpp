#include "stdafx.h"
#include "Items.h"

CConstDocumentItem::CConstDocumentItem(const ParagraphPtr & paragraph)
	: m_paragraph(paragraph)
{
}

CConstDocumentItem::CConstDocumentItem(const ImagePtr & image)
	: m_image(image)
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}

CDocumentItem::CDocumentItem(const ParagraphPtr & paragraph)
	: CConstDocumentItem(paragraph)
	, m_paragraph(paragraph)
{
}

CDocumentItem::CDocumentItem(const ImagePtr & image)
	: CConstDocumentItem(image)
	, m_image(image)
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
