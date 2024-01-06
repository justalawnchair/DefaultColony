#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore ModAPI/Spore/Simulator/cPlaceColonyToolStrategy.h>

#define PlaceColonyWithTurretsPtr intrusive_ptr<PlaceColonyWithTurrets>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new PlaceColonyWithTurrets(), PlaceColonyWithTurrets::NOUN_ID);
///

class PlaceColonyWithTurrets
	: public Simulator::cPlaceColonyToolStrategy
{
public:
	static const uint32_t TYPE = id("DefaultColony::PlaceColonyWithTurrets");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;

	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];

private:
	//
	// You can add members here
	//
};