#include "gtest/gtest.h"

#include "player.h"
#include "healer.h"
#include "tank.h"
#include "fighter.h"
#include "inventory.h"

#include <iostream>
#include <sstream>

class RPGTest : public testing::Test {
protected:
	RPGTest() {
	}

	virtual ~RPGTest() {
	}

	virtual void SetUp() {
		tank = new Tank("Rachel");
		healer = new Healer("Aaron");
		fighter = new Fighter("Cynthia");
	}

	virtual void TearDown() {
		delete tank;
		delete healer;
		delete fighter;
	}

	Player* tank;
	Player* healer;
	Player* fighter;
};

TEST_F(RPGTest, FighterTest) {
	tank->setHP(500);
	fighter->doAction(tank);
	EXPECT_EQ(tank->getHP(), 425);

	tank->setHP(75);
	fighter->doAction(tank);
	EXPECT_TRUE(tank->isDead());
}

TEST_F(RPGTest, HealerTest) {
	tank->setHP(400);
	healer->doAction(tank);
	EXPECT_EQ(tank->getHP(), 475);

	tank->setHP(450);
	healer->doAction(tank);
	EXPECT_EQ(tank->getHP(), 500);
}

TEST_F(RPGTest, InventoryTest) {

	// redirect cout statements to our stringstream
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	Inventory* inv = tank->getInv();

	inv->addItem("HP Potion", 4);
	inv->addItem("Sword", 1);
	inv->addItem("Tunic", 1);
	inv->addItem("Boots", 2);
	inv->addItem("Flower", 5);
	inv->removeItem("Flower");
	inv->addItem("Tunic", 2);
	EXPECT_EQ(inv->getNumItems("Tunic"), 3);

	inv->printAllItems();

	std::string compare = "Boots 2\nHP Potion 4\nSword 1\nTunic 3\n";

	EXPECT_EQ(buffer.str(), compare);

	std::cout.rdbuf(sbuf);
}