#include "./includes/testVM.h"

#include "./includes/vm.h"
#include "./includes/world.h"
#include "./includes/utils.h"

void comTest_sun(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->energy += 10;
	setProp(bot, 1, true);
}

void comTest_move(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	world->moveToDir(x, y, args[0]);
}

void comTest_eatCompl(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 2) {
		bot->energy += tmp.proxyPointer;
	}
}

void comTest_eatBot(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 1) {
		Bot* tb = (Bot*) tmp.proxyPointer;
		bot->energy += tb->energy / 2;
		world->clear(sp.x, sp.y);
	}
}

void comTest_reproduce(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 0) {
		Bot* tb = vm->createChildBot(bot);
		world->setToDir(sp.x, sp.y, args[0], 1, (long) tb);
		bot->energy -= bot->energy / 2;
	}
}

void comTest_goto(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->pointer = args[0];
}

void comTest_gotoInc(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->pointer += args[0];
}

void comTest_moreEnergy(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	if (bot->pointer > args[0] % vm->getProgSize()) bot->pointer += args[1];
}

void comTest_lessEnergy(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	if (bot->pointer < args[0] % vm->getProgSize()) bot->pointer += args[1];
}

void comTest_ifBotToDir(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = pointFromXYD(x, y, args[0]);
	if (world->get(x, y).type == 1) bot->pointer += args[1];
}

VM* createTestVM() {
	VM* testVM = new VM(0, 10);
	testVM->setCommand(0, {comTest_sun       , 0, 0});
	double at1 = {4};
	testVM->setCommand(1, {comTest_move      , 1, initDoubleMass(at1) });
	double at2 = {4};
	testVM->setCommand(2, {comTest_eatCompl  , 1, initDoubleMass(at2) });
	double at3 = {4};
	testVM->setCommand(3, {comTest_eatBot    , 1, initDoubleMass(at3) });
	double at4 = {4};
	testVM->setCommand(4, {comTest_reproduce , 1, initDoubleMass(at4) });
	double at5 = {3};
	testVM->setCommand(5, {comTest_goto      , 1, initDoubleMass(at5) });
	double at6 = {3};
	testVM->setCommand(6, {comTest_gotoInc   , 1, initDoubleMass(at6) });
	double at7 = {1, 3};
	testVM->setCommand(7, {comTest_moreEnergy, 2, initDoubleMass(at7) });
	double at8 = {1, 3};
	testVM->setCommand(8, {comTest_lessEnergy, 2, initDoubleMass(at8) });
	double at9 = {4, 3};
	testVM->setCommand(9, {comTest_ifBotToDir, 2, initDoubleMass(at9) });
	return testVM;
};