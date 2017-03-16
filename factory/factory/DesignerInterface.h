#pragma once
#include <iostream>

class CPictureDraft;

struct IDesigner
{
	virtual ~IDesigner() = default;
	virtual CPictureDraft CreateDraft(std::istream & strm) = 0;
};