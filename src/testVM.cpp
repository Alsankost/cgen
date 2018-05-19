#include "./includes/testVM.h"

#include "./includes/vm.h"
#include "./includes/world.h"

void comTest_sun(int x, int y, Bot* bot, World* world, double* args) {
	bot->energy += 10;
	setProp(bot, 1, true);
}

void comTest_move(int x, int y, Bot* bot, World* world, double* args) {
	world->moveToDir(x, y, args[0]);
}

void comTest_eatCompl(int x, int y, Bot* bot, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 2) {
		bot->energy += tmp.proxyPointer;
	}
}

void comTest_eatBot(int x, int y, Bot* bot, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 1) {
		Bot* tb = (Bot*) tmp.proxyPointer;
		bot->energy += tb->energy / 2;
		world->clear(sp.x, sp.y);
	}
}

void comTest_reproduce(int x, int y, Bot* bot, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 0) {
		Bot* tb = createChildBot(bot);
		world->setToDir(sp.x, sp.y, args[0], 1, (long) tb);
		bot->energy -= bot->energy / 2;
	}
}

void comTest_goto(int x, int y, Bot* bot, World* world, double* args) {
	bot->pointer = args[0];
}

void comTest_gotoInc(int x, int y, Bot* bot, World* world, double* args) {
	bot->pointer += args[0];
}

void comTest_moreEnergy(int x, int y, Bot* bot, World* world, double* args) {
	if (bot->pointer > args[0]) bot->pointer += args[1];
}

void comTest_lessEnergy(int x, int y, Bot* bot, World* world, double* args) {
	if (bot->pointer < args[0]) bot->pointer += args[1];
}

void comTest_ifBotToDir(int x, int y, Bot* bot, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	if (world->get(x, y).type == 1) bot->pointer += args[1];
}

VM* createTestVM() {
	VM* testVM = new VM(0, 10);
	vm.setCommand(0, {comTest_sun       , 0, {}});
	vm.setCommand(1, {comTest_move      , 1, {4}});
	vm.setCommand(2, {comTest_eatCompl  , 1, {4}});
	vm.setCommand(3, {comTest_eatBot    , 1, {4}});
	vm.setCommand(4, {comTest_reproduce , 1, {4}});
	vm.setCommand(5, {comTest_goto      , 1, {3}});
	vm.setCommand(6, {comTest_gotoInc   , 1, {3}});
	vm.setCommand(7, {comTest_moreEnergy, 2, {1, 3}});
	vm.setCommand(8, {comTest_lessEnergy, 2, {1, 3}});
	vm.setCommand(9, {comTest_lessEnergy, 2, {4, 3}});
	return testVM;
};