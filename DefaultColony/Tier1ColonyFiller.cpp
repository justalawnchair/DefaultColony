#include "stdafx.h"
#include "Tier1ColonyFiller.h"

void Tier1ColonyFiller::FillOptimalLayout() {
	vector<int> mHouseSlotList = { 6, 11 };
	vector<int> mEntertainSlotList = { 2 };
	vector<int> mIndustrySlotList = { 1, 5};
	Simulator::cCommunityLayout buildingLayout = mCity->mBuildingsLayout;

	// fill entertainment building slots
	for (int i = 0; i < static_cast<int>(mEntertainSlotList.size()); i++) {
		int slotIndex = mEntertainSlotList[i];
		if (buildingLayout.mSlots[slotIndex].mpObject == NULL) {
			Simulator::cBuildingEntertainment* building = simulator_new<Simulator::cBuildingEntertainment>();
			FillSingleSlot(building, mEntertainmentKey, slotIndex);
		}

	}

	// fill industry building slots
	for (int i = 0; i < static_cast<int>(mIndustrySlotList.size()); i++) {
		int slotIndex = mIndustrySlotList[i];
		if (buildingLayout.mSlots[slotIndex].mpObject == NULL) {
			Simulator::cBuildingIndustry* building = simulator_new<Simulator::cBuildingIndustry>();
			FillSingleSlot(building, mIndustryKey, slotIndex);
		}
	}

	// fill house building slots
	for (int i = 0; i < static_cast<int>(mHouseSlotList.size()); i++) {
		int slotIndex = mHouseSlotList[i];
		if (buildingLayout.mSlots[slotIndex].mpObject == NULL) {
			Simulator::cBuildingHouse* building = simulator_new<Simulator::cBuildingHouse>();
			FillSingleSlot(building, mHouseKey, slotIndex);
		}
	}

}


void Tier1ColonyFiller::FillTurrets() {
	vector<int> mTurretSlotList = { 0, 1, 2, 3, 4, 5, 6, 7 };
	return;
}