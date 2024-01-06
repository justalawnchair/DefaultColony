#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cPLaceObjectToolStrategy.h>

#define cPlaceFullColonyToolStrategyPtr intrusive_ptr<cPlaceFullColonyToolStrategy>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new cPlaceFullColonyToolStrategy(), cPlaceFullColonyToolStrategy::NOUN_ID);
///

class cPlaceFullColonyToolStrategy
	: public Simulator::cDefaultProjectileWeapon
{
public:

	~cPlaceFullColonyToolStrategy();
	static const uint32_t TYPE = id("Simulator::cPlaceFullColonyToolStrategy");
	static const uint32_t NOUN_ID = TYPE;
	//
	// You can add more methods here
	//
		
	virtual bool OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int) override;
	virtual bool CheckCityStatus(const Vector3& position);
	static Simulator::Attribute ATTRIBUTES[];

private:
	//
	// You can add members here
	//
};
