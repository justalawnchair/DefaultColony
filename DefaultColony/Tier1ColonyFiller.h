#pragma once
#include "ColonyFiller.h"
class Tier1ColonyFiller :
    public ColonyFiller

{
public:
    using ColonyFiller::ColonyFiller;
    void FillOptimalLayout() override;
    void FillTurrets() override;
};

