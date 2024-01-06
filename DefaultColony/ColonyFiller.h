#pragma once
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cBuilding.h>

class ColonyFiller
{
public:
	ColonyFiller();
	ColonyFiller(Vector3 const& position);
	~ColonyFiller();
	bool CheckCityStatus(const Vector3& position);
	virtual void FillColony();
	ResourceKey RetrieveHouseKey(Simulator::cCivilization* civilization);
	ResourceKey RetrieveIndustryKey(Simulator::cCivilization* civilization);
	ResourceKey RetrieveEntertainmentKey(Simulator::cCivilization* civilization);
	void ResolveBuildingKeys();
	bool FillSingleSlot(Simulator::cBuilding* building, ResourceKey buildingKey, int slotIndex);
	virtual void FillOptimalLayout();
	virtual void FillTurrets();

public:
	Simulator::cEmpire* mEmpire;
	Simulator::cCity* mCity;
	Simulator::cCivilization* mCivilization;
	ResourceKey mHouseKey;
	ResourceKey mIndustryKey;
	ResourceKey mEntertainmentKey;
	ResourceKey mDefaultHouseKey;
	ResourceKey mDefaultIndustryKey;
	ResourceKey mDefaultEntertainmentKey;
	ResourceKey mDefaultTurretKey;
	vector<int> mHouseSlotList;
	vector<int> mIndustrySlotList;
	vector<int> mEntertainSlotList;
	vector<int> mTurretSlotList;
	int mTScore;
	Vector3 const& mPosition;

};