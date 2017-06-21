#pragma once

class IParagraph;
class IImage;

using ParagraphPtr = std::shared_ptr<IParagraph>;
using ImagePtr = std::shared_ptr<IImage>;

/*
������������ ������� ���������
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(const ParagraphPtr& paragraph);
	CConstDocumentItem(const ImagePtr& image);


	// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;

private:
	ParagraphPtr m_paragraph = nullptr;
	ImagePtr m_image = nullptr;
};

/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(const ParagraphPtr& paragraph);
	CDocumentItem(const ImagePtr& image);

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();

private:
	ParagraphPtr m_paragraph = nullptr;
	ImagePtr m_image = nullptr;
};
