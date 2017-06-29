#include "stdafx.h"
#include "../composite/Style.h"
#include "../composite/Group.h"
#include "../composite/TypedShapes.h"

struct MyGroup
{
	Group group;
};

BOOST_FIXTURE_TEST_SUITE(Testing_group, MyGroup)

BOOST_AUTO_TEST_CASE(can_get_size_of_empty_group)
{
	auto rect = group.GetFrame();
	BOOST_CHECK_EQUAL(rect.left, 0);
	BOOST_CHECK_EQUAL(rect.width, 0);
	BOOST_CHECK_EQUAL(rect.top, 0);
	BOOST_CHECK_EQUAL(rect.height, 0);
}

BOOST_AUTO_TEST_CASE(can_get_shapes_count_of_empty_group)
{
	BOOST_CHECK_EQUAL(group.ShapesCount(), 0u);
}

BOOST_AUTO_TEST_CASE(can_try_to_resize_empty_group)
{
	group.SetFrame({ 0,0,10,10 });
	auto rect = group.GetFrame();
	BOOST_CHECK_EQUAL(rect.left, 0);
	BOOST_CHECK_EQUAL(rect.width, 0);
	BOOST_CHECK_EQUAL(rect.top, 0);
	BOOST_CHECK_EQUAL(rect.height, 0);
}

BOOST_AUTO_TEST_CASE(can_try_to_get_styles)
{
	BOOST_CHECK(!group.GetFillStyle());
	BOOST_CHECK(!group.GetLineStyle());
}

BOOST_AUTO_TEST_CASE(can_try_to_set_style)
{
	CStyle redStyle;
	redStyle.Enable(true);
	redStyle.SetColor(0xFF0000);
	group.SetFillStyle(redStyle);
	group.SetLineStyle(redStyle);
	BOOST_CHECK(!group.GetFillStyle());
	BOOST_CHECK(!group.GetLineStyle());
}

struct GroupWithShape
{
	GroupWithShape()
	{
		redStyle.Enable(true);
		redStyle.SetColor(0xFF0000);
		auto rectangleShape = std::make_shared<CRectangle>(RectD{ 10, 10, 10, 10 });
		rectangleShape->SetFillStyle(redStyle);
		rectangleShape->SetLineStyle(redStyle);

		group.AddShape(rectangleShape);
	}
	Group group;
	CStyle redStyle;
};

BOOST_FIXTURE_TEST_SUITE(Testing_group, GroupWithShape)

BOOST_AUTO_TEST_CASE(can_get_shape)
{
	BOOST_CHECK(group.GetShape(0));
}

BOOST_AUTO_TEST_CASE(can_get_style)
{
	BOOST_CHECK(group.GetFillStyle() == redStyle);
	BOOST_CHECK(group.GetLineStyle() == redStyle);
}

BOOST_AUTO_TEST_CASE(can_get_size)
{
	auto rect = group.GetFrame();
	BOOST_CHECK_EQUAL(rect.left, 10);
	BOOST_CHECK_EQUAL(rect.width, 10);
	BOOST_CHECK_EQUAL(rect.top, 10);
	BOOST_CHECK_EQUAL(rect.height, 10);
}

BOOST_AUTO_TEST_CASE(can_get_shapes_count)
{
	BOOST_CHECK_EQUAL(group.ShapesCount(), 1u);
}

BOOST_AUTO_TEST_CASE(can_resize_group)
{
	group.SetFrame({0,0,40,40});
	auto rect = group.GetFrame();
	BOOST_CHECK_EQUAL(rect.left, 0);
	BOOST_CHECK_EQUAL(rect.width, 40);
	BOOST_CHECK_EQUAL(rect.top, 0);
	BOOST_CHECK_EQUAL(rect.height, 40);

	auto shape = group.GetShape(0);
	auto shapeRect = shape->GetFrame();
	BOOST_CHECK_EQUAL(rect.left, 0);
	BOOST_CHECK_EQUAL(rect.width, 40);
	BOOST_CHECK_EQUAL(rect.top, 0);
	BOOST_CHECK_EQUAL(rect.height, 40);
}

BOOST_AUTO_TEST_CASE(can_set_style)
{
	CStyle newStyle;
	newStyle.Enable(true);
	newStyle.SetColor(0xAABBCC);

	group.SetFillStyle(newStyle);
	group.SetLineStyle(newStyle);

	BOOST_CHECK(group.GetFillStyle() == newStyle);
	BOOST_CHECK(group.GetLineStyle() == newStyle);

	auto shape = group.GetShape(0);

	BOOST_CHECK(shape->GetFillStyle() == newStyle);
	BOOST_CHECK(shape->GetLineStyle() == newStyle);
}

BOOST_AUTO_TEST_CASE(cant_get_style_if_they_are_different)
{
	CStyle newStyle;
	newStyle.Enable(true);
	newStyle.SetColor(0xAABBCC);

	auto rectangleShape = std::make_shared<CRectangle>(RectD{ 10, 10, 10, 10 });
	rectangleShape->SetFillStyle(newStyle);
	rectangleShape->SetLineStyle(newStyle);

	group.AddShape(rectangleShape);

	BOOST_CHECK(!group.GetFillStyle());
	BOOST_CHECK(!group.GetLineStyle());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()