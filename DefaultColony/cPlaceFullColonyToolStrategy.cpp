#include "stdafx.h"
#include "cPlaceFullColonyToolStrategy.h"
#include <Spore\Simulator\cPlaceObjectToolStrategy.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cCommunityLayout.h>
#include <Spore\Simulator\SubSystem\GameNounManager.h>
#include <Spore\Simulator\SubSystem\TerraformingManager.h>
#include "ColonyFiller.h"
#include "Tier1ColonyFiller.h"
#include "Tier2ColonyFiller.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <future>

cPlaceFullColonyToolStrategy::~cPlaceFullColonyToolStrategy() {

}

bool cPlaceFullColonyToolStrategy::CheckCityStatus(const Vector3& position) {
	Simulator::cCity* city = PlanetModel.GetNearestCity(position);
	if (city->IsAboveCity(position)) {
		return true;
	}
	return false;
}

bool cPlaceFullColonyToolStrategy::OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int) {
	bool cPlaceColonyToolStrategyResult = cDefaultProjectileWeapon::OnHit(pTool, position, hitType, 0);

	Simulator::cTerraformingManager* terraformingManager = Simulator::cTerraformingManager::Get();
	int tScore = terraformingManager->GetTScore();

	ColonyFiller* colonyFiller;

	if (tScore < 1) {
		return false;
	} else if (tScore < 2) { 
		colonyFiller = new Tier1ColonyFiller(position);
	}
	else if (tScore < 3) {
		colonyFiller = new Tier2ColonyFiller(position);
	}
	else {
		colonyFiller = new ColonyFiller(position);
	}

	
	if (!colonyFiller->CheckCityStatus(position)) {
		return false;
	}

	colonyFiller->FillColony();
	return true;
};
/// AUTOGENERATED METHODS ///

/// END OF AUTOGENERATED METHODS ///
////////////////////////////////////
