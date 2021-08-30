#include "DamageCommand.h"

#include "../../Module/ModuleManager.h"

DamageCommand::DamageCommand() : IMCCommand("damage", "Damage yourself (relies on falldamage)", "<amount>") {
	registerAlias("dmg");
}

DamageCommand::~DamageCommand() {
}

bool DamageCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	float amount = assertFloat(args->at(1));
	if (amount < 1.f) {
		clientMessageF("%sIf you making it 0 why u using da cmd", GRAY);
		return true;
	}
	auto noFallMod = moduleMgr->getModule<NoFall>();

	if (noFallMod->isEnabled()) {
		noFallMod->setEnabled(false);
		g_Data.getLocalPlayer()->causeFallDamage(amount + 3.f);
		noFallMod->setEnabled(true);
	} else {
		g_Data.getLocalPlayer()->causeFallDamage(amount + 3.f);
	}
	return true;
}
