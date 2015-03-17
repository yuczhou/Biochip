/*
 * NetTest.cpp
 *
 *  Created on: Mar 3, 2014
 *      Author: yuczhou
 */
#ifndef NET_TEST
#define NET_TEST

#include "Net.h"
#include "Utility.h"
#include "gtest/gtest.h"

namespace BioChip {

    class NetTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            module = Utility::getPointer(new RectangularModuleFactory("module"));
            module->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
            module->addShape(Utility::getPointer(new RectangularShape("1", Coord(2, 2, 5))));
        }

        ModuleNodePointer module;
    };

    TEST_F(NetTest, sourcePinTest) {
        Coord origin(5, 6, 7);
        auto pin = Utility::getPointer(new SourcePin(module->createModule(0, origin)));
        EXPECT_TRUE(pin->getPins().find(Coord(5, 6, 7)) != pin->getPins().end());
        EXPECT_EQ(1, pin->getPins().size());

        pin = Utility::getPointer(new SourcePin(module->createModule(1, origin)));
        EXPECT_TRUE(pin->getPins().find(Coord(5, 6, 7)) != pin->getPins().end());
        EXPECT_TRUE(pin->getPins().find(Coord(6, 6, 7)) != pin->getPins().end());
        EXPECT_TRUE(pin->getPins().find(Coord(5, 7, 7)) != pin->getPins().end());
        EXPECT_TRUE(pin->getPins().find(Coord(6, 7, 7)) != pin->getPins().end());
        EXPECT_EQ(4, pin->getPins().size());
    }

    TEST_F(NetTest, targetPinTest) {
        Coord origin(5, 6, 7);
        auto pin = Utility::getPointer(new TargetPin(module->createModule(0, origin)));
        EXPECT_TRUE(pin->getPins().find(Coord(5, 6, 7)) != pin->getPins().end());
        EXPECT_EQ(1, pin->getPins().size());

        pin = Utility::getPointer(new TargetPin(module->createModule(1, origin)));
        EXPECT_TRUE(pin->getPins().find(Coord(5, 6, 11)) != pin->getPins().end());
        EXPECT_TRUE(pin->getPins().find(Coord(6, 6, 11)) != pin->getPins().end());
        EXPECT_TRUE(pin->getPins().find(Coord(5, 7, 11)) != pin->getPins().end());
        EXPECT_TRUE(pin->getPins().find(Coord(6, 7, 11)) != pin->getPins().end());
        EXPECT_EQ(4, pin->getPins().size());
    }
}

#endif