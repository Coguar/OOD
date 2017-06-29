#include "stdafx.h"
#include "../DocumentEditor/ChangeStringCommand.h"
#include "../DocumentEditor/Items.h"
#include "../DocumentEditor/DeleteCommand.h"
#include "../DocumentEditor/InsertParagraphCommand.h"
#include "../DocumentEditor/InsertImageCommand.h"
#include "../DocumentEditor/History.h"
#include "../DocumentEditor/Paragraph.h"
#include "../DocumentEditor/Image.h"
#include "../DocumentEditor/ResizeImageCommand.h"

#include <vector>
#include <memory>

BOOST_AUTO_TEST_SUITE(testing_commands)

BOOST_AUTO_TEST_CASE(can_swap_two_strings_with_command)
{
	std::string source("Hello");
	CChangeStringCommand command(source, "bye");
	command.Execute();
	BOOST_CHECK_EQUAL(source, "bye");
}

BOOST_AUTO_TEST_CASE(can_swap_two_strings_with_command_and_turn_back)
{
	std::string source("Hello");
	CChangeStringCommand command(source, "bye");
	command.Execute();
	BOOST_CHECK_EQUAL(source, "bye");
	command.Unexecute();
	BOOST_CHECK_EQUAL(source, "Hello");
}

struct Document
{
	std::vector<CDocumentItem> items;
	History history;
};

BOOST_FIXTURE_TEST_SUITE(testing_document_commands, Document)

BOOST_AUTO_TEST_CASE(can_add_paragraph)
{
	auto parPtr = std::make_shared<Paragraph>("Text", history);
	history.ExecuteCommand(std::make_unique<InsertParagraphCommand>(items, parPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK_EQUAL(items.at(0).GetParagraph()->GetText(), "Text");
}

BOOST_AUTO_TEST_CASE(can_add_paragraph_and_undo)
{
	auto parPtr = std::make_shared<Paragraph>("Text", history);
	history.ExecuteCommand(std::make_unique<InsertParagraphCommand>(items, parPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK_EQUAL(items.at(0).GetParagraph()->GetText(), "Text");
	history.Undo();
	BOOST_CHECK_EQUAL(items.size(), 0u);
	BOOST_CHECK(history.CanRedo());
	BOOST_CHECK(!history.CanUndo());
}

BOOST_AUTO_TEST_CASE(can_add_paragraph_and_delete_it)
{
	auto parPtr = std::make_shared<Paragraph>("Text", history);
	history.ExecuteCommand(std::make_unique<InsertParagraphCommand>(items, parPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK_EQUAL(items.at(0).GetParagraph()->GetText(), "Text");
	history.ExecuteCommand(std::make_unique<DeleteCommand>(0, items));
	BOOST_CHECK_EQUAL(items.size(), 0u);
	BOOST_CHECK(!history.CanRedo());
	BOOST_CHECK(history.CanUndo());
}

BOOST_AUTO_TEST_CASE(can_add_image)
{
	auto imgPtr = std::make_shared<Image>("cat.jpg", 10, 10, history);
	history.ExecuteCommand(std::make_unique<InsertImageCommand>(items, imgPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK(!items.at(0).GetParagraph());
}

BOOST_AUTO_TEST_CASE(can_add_image_2_times)
{
	auto imgPtr = std::make_shared<Image>("cat.jpg", 10, 10, history);
	history.ExecuteCommand(std::make_unique<InsertImageCommand>(items, imgPtr, 0));
	history.ExecuteCommand(std::make_unique<InsertImageCommand>(items, imgPtr, 1));
	BOOST_CHECK_EQUAL(items.size(), 2u);
	BOOST_CHECK(!items.at(0).GetParagraph());
	BOOST_CHECK(!items.at(1).GetParagraph());
	BOOST_CHECK(items.at(0).GetImage()->GetPath() == items.at(1).GetImage()->GetPath());
}

BOOST_AUTO_TEST_CASE(can_add_image_and_undo)
{
	auto imgPtr = std::make_shared<Image>("cat.jpg", 10, 10, history);
	history.ExecuteCommand(std::make_unique<InsertImageCommand>(items, imgPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK(!items.at(0).GetParagraph());
	history.Undo();
	BOOST_CHECK_EQUAL(items.size(), 0u);
}

BOOST_AUTO_TEST_CASE(can_add_image_and_resize)
{
	auto imgPtr = std::make_shared<Image>("cat.jpg", 10, 10, history);
	history.ExecuteCommand(std::make_unique<InsertImageCommand>(items, imgPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK(!items.at(0).GetParagraph());
	history.ExecuteCommand(std::make_unique<ResizeImageCommand>(imgPtr, imgPtr->GetWidth(), imgPtr->GetHeight(), 20, 20));
	BOOST_CHECK_EQUAL(imgPtr->GetHeight(), 20);
	BOOST_CHECK_EQUAL(imgPtr->GetWidth(), 20);
}

BOOST_AUTO_TEST_CASE(can_add_image_and_resize_and_undo_and_resize_again)
{
	auto imgPtr = std::make_shared<Image>("cat.jpg", 10, 10, history);
	history.ExecuteCommand(std::make_unique<InsertImageCommand>(items, imgPtr, 0));
	BOOST_CHECK_EQUAL(items.size(), 1u);
	BOOST_CHECK(!items.at(0).GetParagraph());
	history.ExecuteCommand(std::make_unique<ResizeImageCommand>(imgPtr, imgPtr->GetWidth(), imgPtr->GetHeight(), 20, 20));
	BOOST_CHECK_EQUAL(imgPtr->GetHeight(), 20);
	BOOST_CHECK_EQUAL(imgPtr->GetWidth(), 20);
	history.Undo();
	history.ExecuteCommand(std::make_unique<ResizeImageCommand>(imgPtr, imgPtr->GetWidth(), imgPtr->GetHeight(), 30, 30));
	BOOST_CHECK_EQUAL(imgPtr->GetHeight(), 30);
	BOOST_CHECK_EQUAL(imgPtr->GetWidth(), 30);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()