#include "stdafx.h"
#include <Spore\BasicIncludes.h>
#include "ColonyFiller.h"
#include <Spore\Simulator\SubSystem\GameNounManager.h>
#include <Spore\Simulator\cBuilding.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <future>

ColonyFiller::ColonyFiller(Vector3 const& position) : mPosition(position) {
	mEmpire = Simulator::GetPlayerEmpire();
	mCivilization = GameNounManager.GetPlayerCivilization();
	mCity = PlanetModel.GetNearestCity(mPosition);
	
	mDefaultHouseKey = ResourceKey(108551100, 597278293, 1080254976);
	mDefaultIndustryKey = ResourceKey(108551102, 597278293, 1080254976);
	mDefaultEntertainmentKey = ResourceKey(108551106, 597278293, 1080254976);
	mDefaultTurretKey = ResourceKey(3746749813, 0, 1082294528);
	ResolveBuildingKeys();
}

ColonyFiller::ColonyFiller() : mPosition(Math::Vector3(0,0,0)) {

}

ColonyFiller::~ColonyFiller() {

}
bool ColonyFiller::CheckCityStatus(const Vector3& position) {
	Simulator::cCity* city = PlanetModel.GetNearestCity(position);
	if (city->IsAboveCity(position)) {
		return true;
	}
	return false;
}

void ColonyFiller::FillColony() {
	FillOptimalLayout();
	FillTurrets();
	Simulator::cCity::ProcessBuildingUpdate(mCity);
}

ResourceKey ColonyFiller::RetrieveHouseKey(Simulator::cCivilization* civilization) {
	return civilization->mCultureSet.PickCreation(ModelTypes::kBuildingHouse);
};
ResourceKey ColonyFiller::RetrieveIndustryKey(Simulator::cCivilization* civilization) {
	return civilization->mCultureSet.PickCreation(ModelTypes::kBuildingIndustry);
};
ResourceKey ColonyFiller::RetrieveEntertainmentKey(Simulator::cCivilization* civilization) {
	return civilization->mCultureSet.PickCreation(ModelTypes::kBuildingEntertainment);
};

void ColonyFiller::ResolveBuildingKeys() {
	ResourceKey EMPTY_KEY = ResourceKey(0x00000000, 0x00000000, 0x00000000);
	ResourceKey mHouseKey = ColonyFiller::RetrieveHouseKey(mCivilization);
	if (mHouseKey == EMPTY_KEY) {
		mHouseKey = mDefaultHouseKey;
		mCivilization->mCultureSet.SetCreation(ModelTypes::kBuildingHouse, mHouseKey);
	}
	ResourceKey mIndustryKey = ColonyFiller::RetrieveIndustryKey(mCivilization);
	if (mIndustryKey == EMPTY_KEY) {
		mIndustryKey = mDefaultIndustryKey;
		mCivilization->mCultureSet.SetCreation(ModelTypes::kBuildingIndustry, mIndustryKey);
	}
	ResourceKey mEntertainmentKey = ColonyFiller::RetrieveEntertainmentKey(mCivilization);
	if (mEntertainmentKey == EMPTY_KEY) {
		mEntertainmentKey = mDefaultEntertainmentKey;
		mCivilization->mCultureSet.SetCreation(ModelTypes::kBuildingEntertainment, mEntertainmentKey);
	}

}
bool ColonyFiller::FillSingleSlot(Simulator::cBuilding* building, ResourceKey buildingKey, int slotIndex) {

	Simulator::cCommunityLayout& buildingLayout = mCity->mBuildingsLayout;
	if (buildingLayout.mSlots[slotIndex].mpObject != NULL) {
		return false;
	}

	building->mpOwnerCity = mCity;
	building->SetPosition(buildingLayout.mSlots[slotIndex].mPosition);
	building->SetOrientation(mCity->GetOrientation());

	building->SetModelKey(buildingKey);

	mCity->AddBuilding(building);
	mCity->mBuildingsLayout.mSlots[slotIndex].SetObject(building);
	//buildingLayout.mSlots[slotIndex].mIsOccupied = true;
	Simulator::cCity::ProcessBuildingUpdate(mCity);
	return true;
}

void ColonyFiller::FillOptimalLayout() {
	vector<int> mHouseSlotList = {6, 7, 8, 9, 10, 11};
	vector<int> mEntertainSlotList = {2};
	vector<int> mIndustrySlotList = {1, 3, 4, 5};
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

void ColonyFiller::FillTurrets() {
	vector<int> mTurretSlotList = {0, 1, 2, 3, 4, 5, 6, 7 };
	Simulator::cCommunityLayout& turretLayout = mCity->mTurretsLayout;
	for (int i = 0; i < static_cast<int>(mTurretSlotList.size()); i++) {
		int slotIndex = mTurretSlotList[i];
		if (turretLayout.mSlots[slotIndex].mpObject == NULL) {
			Simulator::cTurret* turret = simulator_new<Simulator::cTurret>();
			mCity->mTurrets.push_back(turret);
			turretLayout.mSlots[slotIndex].SetObject(turret);
			turret->mPoliticalID = mCivilization->GetPoliticalID();
			turret->mpCity = mCity;
			turret->SetPosition(turretLayout.mSlots[slotIndex].mPosition);
			turret->SetOrientation(mCity->GetOrientation());
			turret->SetModelKey(mDefaultTurretKey);
		}
		else {
			auto turretObject = turretLayout.mSlots[slotIndex].mpObject;
			

		};
	}
}

;