#include "HideCommand.h"

HideCommand::HideCommand() : IMCCommand("hide", "hide the mod", "") {
}

HideCommand::~HideCommand() {
}

bool HideCommand::execute(std::vector<std::string>* args) {
	GameData::hide();
	if (GameData::shouldHide()) {
		clientMessageF("[%sNatsuki%s] %sHidden.", GOLD, WHITE, GREEN);
	} else {
		clientMessageF("[%sNatsuki%s] %sMod is now visible.", GOLD, WHITE, GREEN);
	}
	return true;
}
