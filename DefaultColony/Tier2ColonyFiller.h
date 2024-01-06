#pragma once

#include "ColonyFiller.h"
class Tier2ColonyFiller
	: public ColonyFiller
{
public:
	using ColonyFiller::ColonyFiller;
	~Tier2ColonyFiller();
	void FillTurrets() override;
};

