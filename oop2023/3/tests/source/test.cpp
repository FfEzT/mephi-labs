#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "coord/Direction.h"
#include "coord/Coords.h"

#include "Enviroment/Enviroment.h"
#include "Enviroment/Database.h"

#include "subject/BasicSubject.h"
#include "subject/Moveable.h"

#include "object/BasicPlatform.h"
#include "object/BasicCommandPlatform.h"
#include "object/IObject.h"

#include "module/allBasic.h"

using std::unique_ptr;
using std::unordered_set;
using std::queue;

using namespace GameLogic;
using namespace coord;
using namespace subject;
using namespace object;
using namespace module;

TEST_CASE("Coords") {
    SECTION("distance") {
        SECTION("normal") {
            Coords a(0, 0);
            Coords b(0, 4);

            CHECK(Coords::distance(a, b) == 4);
            CHECK(Coords::distanceSquared(a, b) == 16);
        }
        
        //SECTION
        
    }

    SECTION("operator==") {
        Coords a(0, 0);
        Coords b(0, 4);
        Coords c(0, 4);

        CHECK(a != b);
        CHECK(b == c);
    }

    SECTION("operator+") {
        Coords a = Coords(0, 0) + Coords(15, -7);
        Coords example(15, -7);

        CHECK(a == example);
    }
}

TEST_CASE("Direction") {
    SECTION("cnstr") {
        Direction test(3, 4);

        CHECK(test.getSpeed() == 5);
        CHECK(test.getX() == 1);
        CHECK(test.getY() == 1);
    }

    SECTION("setSpeed") {
        Direction test(3, 4);
        test.setSpeed(50);

        CHECK(test.getSpeed() == 50);
        CHECK(test.getX() == 1);
        CHECK(test.getY() == 1);
    }
}

TEST_CASE("Subject") {
    SECTION("BasicSubject") {
        SECTION("cnstrct") {
            std::unique_ptr<IObject> smartPtr(new IPointInterest);
            auto checkPtr = smartPtr.get();

            BasicSubject<> test(std::move(smartPtr));

            const auto& ok = test.getObject();

            CHECK(&test.getObject() == checkPtr);
            CHECK(&ok == checkPtr);
        }
        SECTION("Just getters") {
            std::unique_ptr<IObject> smartPtr(new IPointInterest);
            BasicSubject<> test(std::move(smartPtr));

            const auto& ref1 = test.getObject();
            auto& ref2 = test.getObject();
        }
    }

    SECTION("MoveAble") {
        SECTION("cnstrct") {
            ILet* ptr = new ILet;
            Direction direct(5, 7);

            Moveable subj(direct, unique_ptr<IObject>(ptr));
            CHECK(subj.getDirection() == direct);
            CHECK(ptr == &subj.getObject());
        }

        SECTION("set direct") {
            Direction newDirect(0, 1);
            Moveable subj(Direction(5, 7), unique_ptr<IObject>(new ILet));

            subj.setDirection(newDirect);
            CHECK(subj.getDirection() == newDirect);
        }

        SECTION("nextPositions") {
            SECTION("is empty") {
                Moveable subj(Direction(1, 0), unique_ptr<IObject>(new ILet));

                CHECK(!subj.getNextPosition());
                CHECK(!subj.popNextPosition());
            }

            SECTION("Set") {
                SECTION("Empty queue") {
                    Moveable subj(Direction(1, 0), unique_ptr<IObject>(new ILet));
    
                    queue<Coords> que;
                    Coords p1(1, 3);
                    Coords p2(2, 6);
                    Coords p3(2, 2);
                    que.push(p1);
                    que.push(p2);
                    que.push(p3);

                    subj.setNextPositions(que);

                    CHECK(subj.getNextPosition() == p1);
                    CHECK(subj.popNextPosition());
                    CHECK(subj.getNextPosition() == p2);
                    CHECK(subj.popNextPosition());
                    CHECK(subj.getNextPosition() == p3);
                    CHECK(subj.popNextPosition());
                    CHECK(!subj.popNextPosition());
                }

                SECTION("Non empty") {
                    Moveable subj(Direction(1, 0), unique_ptr<IObject>(new ILet));

                    queue<Coords> que;
                    Coords p_(10, 3);
                    que.push(p_);
                    subj.setNextPositions(que);

                    queue<Coords> newQue;
                    Coords p1(1, 3);
                    Coords p2(2, 6);
                    Coords p3(2, 2);
                    newQue.push(p1);
                    newQue.push(p2);
                    newQue.push(p3);
                    subj.setNextPositions(newQue);

                    CHECK(subj.getNextPosition() == p1);
                    CHECK(subj.popNextPosition());
                    CHECK(subj.getNextPosition() == p2);
                    CHECK(subj.popNextPosition());
                    CHECK(subj.getNextPosition() == p3);
                    CHECK(subj.popNextPosition());
                    CHECK(!subj.popNextPosition());
                }

            }

            SECTION("Add") {
                Moveable subj(Direction(1, 0), unique_ptr<IObject>(new ILet));

                queue<Coords> que;
                Coords p_(10, 3);
                que.push(p_);
                subj.setNextPositions(que);

                queue<Coords> newQue;
                Coords p1(1, 3);
                Coords p2(2, 6);
                Coords p3(2, 2);
                newQue.push(p1);
                newQue.push(p2);
                newQue.push(p3);
                subj.addNextPositions(newQue);

                CHECK(subj.getNextPosition() == p_);
                CHECK(subj.popNextPosition());
                CHECK(subj.getNextPosition() == p1);
                CHECK(subj.popNextPosition());
                CHECK(subj.getNextPosition() == p2);
                CHECK(subj.popNextPosition());
                CHECK(subj.getNextPosition() == p3);
                CHECK(subj.popNextPosition());
                CHECK(!subj.popNextPosition());
            }
        }
    }
}

TEST_CASE("Module") {
    SECTION("BasicModule") {
        int energy = 1;
        int priority = 10;
        int cost = 100;

        SECTION("cnstrctr") {
            BasicModule<> test(energy, priority, cost);

            CHECK(test.getCost() == cost);
            CHECK(test.getEnergy() == energy);
            CHECK(test.getPriority() == priority);
            CHECK(test.isOn());
        }

        SECTION("setIsOn") {
            BasicModule<> test(energy, priority, cost);

            test.setIsOn(false);
            CHECK(!test.isOn());

            test.setIsOn(true);
            CHECK(test.isOn());
        }
    }

    SECTION("BasicSensor") {
        int energy = 1;
        int priority = 10;
        int cost = 100;
        float angle = 1;
        Direction direct;
        
        SECTION("cnstrctr") {
            SECTION("normal") {
                BasicSensor test(energy, priority, cost, angle, direct);

                CHECK(test.getCost() == cost);
                CHECK(test.getEnergy() == energy);
                CHECK(test.getPriority() == priority);
                CHECK(test.isOn());
                CHECK(test.getAngle() == angle);
                CHECK(test.getDirection() == direct);
                CHECK(test.getRadius() == direct.getSpeed());
            }

            SECTION("except negative angle") {
                float negativeAngle = -1;
                
                CHECK_THROWS_AS(
                    BasicSensor(energy, priority, cost, negativeAngle, direct),
                    std::invalid_argument
                );
            }
        }

        SECTION("setIsOn") {
            BasicSensor test(energy, priority, cost, angle, direct);

            test.setIsOn(false);
            CHECK(!test.isOn());

            test.setIsOn(true);
            CHECK(test.isOn());
        }

        SECTION("Environment info") {
            BasicSensor test(energy, priority, cost, angle, direct);
            test.setIsOn(false);

            unordered_set<id_t> environment = { 0,7,8,9,5,6,4,1,2,3 };
            test.setEnvironmentInfo(environment);

            auto aga = test.getEnvironmentInfo();
            CHECK(aga == unordered_set<id_t>());
                
            test.setIsOn(true);
            CHECK(test.getEnvironmentInfo() == environment);
        }
    }

    SECTION("BasicGenerator") {
        int energy = 1;
        int priority = 10;
        int cost = 100;

        SECTION("cnstrctr") {
            BasicGenerator test(energy, priority, cost);

            CHECK(test.getCost() == cost);
            CHECK(test.getEnergy() == energy);
            CHECK(test.getPriority() == priority);
            CHECK(test.isOn());
        }

        SECTION("setIsOn") {
            BasicGenerator test(energy, priority, cost);

            test.setIsOn(false);
            CHECK(!test.isOn());

            test.setIsOn(true);
            CHECK(test.isOn());
        }

        SECTION("generate") {
            BasicGenerator test(energy, priority, cost);
            CHECK(test.generate() == energy);
        }
    }

    SECTION("BasicCommandModule") {
        int energy = 1;
        int priority = 10;
        int cost = 100;
        unsigned radius = 10;

        SECTION("cnstrctr") {
            SECTION("normal") {
                BasicCommandModule test(energy, priority, cost, radius);

                CHECK(test.getCost() == cost);
                CHECK(test.getEnergy() == energy);
                CHECK(test.getPriority() == priority);
                CHECK(test.isOn());
                CHECK(test.getRadius() == radius);
            }
        }

        SECTION("setIsOn") {
            BasicCommandModule test(energy, priority, cost, radius);

            test.setIsOn(false);
            CHECK(!test.isOn());

            test.setIsOn(true);
            CHECK(test.isOn());
        }

        SECTION("Controlled robot") {
            BasicCommandModule test(energy, priority, cost, radius);
            test.setIsOn(false);

            unordered_set<id_t> environment = { 0,7,8,9,5,6,4,1,2,3 };
            test.setControlledRobot(environment);

            CHECK(test.getControlledRobot() == unordered_set<id_t>());

            test.setIsOn(true);
            CHECK(test.getControlledRobot() == environment);
        }
    }
}

TEST_CASE("Platforms") {
    string name = "Platform";
    unsigned cost = 15;
    unsigned energy = 1;
    size_t maxModuleCount = 3;

    SECTION("Basic") {
        SECTION("constrct") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);

            CHECK(platform.getCost() == cost);
            CHECK(platform.getDescribe() == name);
            CHECK(platform.getEnergy() == energy);
            CHECK(platform.getMaxModuleCount() == maxModuleCount);
            CHECK(platform.getIdTexture() == PLATFORM);
        }

        SECTION("isActive") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);

            CHECK(!platform.isActive());
            platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)));
            CHECK(platform.isActive());
        }

        SECTION("setModule") {
            SECTION("normal") {
                unsigned energySen = 1;
                BasicPlatform<> platform(name, cost, energy, maxModuleCount);

                CHECK(platform.getGenerators().empty());
                CHECK(platform.getModuleCount() == 0);
                CHECK(platform.getSumEnergy() == energy);
                CHECK(platform.getSensors().empty());

                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)))
                    == nullptr
                );
                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicSensor(energySen, 5, 1, 2)))
                    == nullptr
                );
                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicModule<>(1, 5, 7)))
                    != nullptr
                );
                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicCommandModule(1, 5, 1, 2)))
                    != nullptr
                );

                CHECK(!platform.getGenerators().empty());
                CHECK(!platform.getSensors().empty());
                CHECK(platform.getModuleCount() == 2);
                CHECK(platform.getSumEnergy() == energy + energySen);
            }
            SECTION("Limit") {
                size_t maxModuleCount = 0;
                BasicPlatform<> platform(name, cost, energy, maxModuleCount);

                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)))
                    != nullptr
                );
                CHECK(platform.getGenerators().empty());
                CHECK(platform.getModuleCount() == 0);
            }

            SECTION("checkEnergy") {
                unsigned energySen = 1;
                BasicPlatform<> platform(name, cost, energy, maxModuleCount);

                BasicGenerator* ptr1 = new BasicGenerator(2, 10, 1);
                BasicSensor*    ptr2 = new BasicSensor(energySen, 1, 1, 2);
                BasicSensor*    ptr3 = new BasicSensor(energySen, 5, 1, 2);
                
                platform.setModule(unique_ptr<IModule>(ptr1));
                platform.setModule(unique_ptr<IModule>(ptr2));
                platform.setModule(unique_ptr<IModule>(ptr3));

                CHECK(ptr1->isOn());
                CHECK(!ptr2->isOn());
                CHECK(ptr3->isOn());
            }
        }

        SECTION("deleteModuleGen") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);

            platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)));
            platform.deleteModule(platform.getGenerators().begin());

            CHECK(platform.getGenerators().empty());
        }
        SECTION("deleteModuleSens") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);

            platform.setModule(unique_ptr<IModule>(new BasicSensor(1,1,1,5.0)));
            platform.deleteModule(platform.getSensors().begin());

            CHECK(platform.getSensors().empty());
        }

        SECTION("onModule") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);
            platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)));
            platform.setModule(unique_ptr<IModule>(new BasicSensor(1, 1, 1, 5.0)));
            
            platform.onModule(platform.getGenerators().begin());
            platform.onModule(platform.getSensors().begin());

            CHECK(platform.getGenerators().begin()->get()->isOn());
            CHECK(platform.getSensors().begin()->get()->isOn());
        }

        SECTION("offModule") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);
            platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)));
            platform.setModule(unique_ptr<IModule>(new BasicSensor(1, 1, 1, 5.0)));

            platform.offModule(platform.getGenerators().begin());
            platform.offModule(platform.getSensors().begin());

            CHECK(!platform.getGenerators().begin()->get()->isOn());
            CHECK(!platform.getSensors().begin()->get()->isOn());
        }

        SECTION("getEnvironmentInfo") {
                BasicPlatform<> platform(name, cost, energy, maxModuleCount);

                CHECK(platform.getEnvironmentInfo().empty());

                platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)));
                CHECK(platform.getEnvironmentInfo().empty());

                unordered_set<id_t> set = { 1, 7, 5, 3 };
                BasicSensor* ptrSen1 = new BasicSensor(1, 1, 1, 5.0);
                BasicSensor* ptrSen2 = new BasicSensor(1, 1, 1, 5.0);
                ptrSen1->setEnvironmentInfo(set);
                ptrSen2->setEnvironmentInfo(set);

                platform.setModule(unique_ptr<IModule>(ptrSen1));
                platform.setModule(unique_ptr<IModule>(ptrSen2));

                CHECK(set == platform.getEnvironmentInfo());
        }

        SECTION("isUnderConrol") {
            BasicPlatform<> platform(name, cost, energy, maxModuleCount);

            CHECK(!platform.isUnderControl());
            platform.setIsUnderControl(true);
            CHECK(platform.isUnderControl());
        }
    }

    SECTION("Command") {
        SECTION("setModule") {
            SECTION("normal") {
                unsigned energySen = 1;
                unsigned energyCom = 1;
                BasicCommandPlatform platform(name, cost, energy, maxModuleCount);

                CHECK(platform.getGenerators().empty());
                CHECK(platform.getModuleCount() == 0);
                CHECK(platform.getSumEnergy() == energy);
                CHECK(platform.getSensors().empty());

                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)))
                    == nullptr
                );
                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicSensor(energySen, 5, 1, 2)))
                    == nullptr
                );
                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicModule<>(1, 5, 7)))
                    != nullptr
                );
                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicCommandModule(energyCom, 5, 1, 2)))
                    == nullptr
                );

                CHECK(!platform.getGenerators().empty());
                CHECK(!platform.getSensors().empty());
                CHECK(!platform.getCommandModule().empty());
                CHECK(platform.getModuleCount() == 3);
                CHECK(platform.getSumEnergy() == (energy + energySen + energyCom));
            }

            SECTION("Limit") {
                size_t maxModuleCount = 0;
                BasicCommandPlatform platform(name, cost, energy, maxModuleCount);

                CHECK(
                    platform.setModule(unique_ptr<IModule>(new BasicGenerator(10, 5, 7)))
                    != nullptr
                );
                CHECK(platform.getGenerators().empty());
                CHECK(platform.getModuleCount() == 0);
            }
        }

        SECTION("deleteModuleSens") {
            BasicCommandPlatform platform(name, cost, energy, maxModuleCount);

            platform.setModule(unique_ptr<IModule>(new BasicCommandModule(1, 5, 1, 2)));
            platform.deleteModule(platform.getCommandModule().begin());

            CHECK(platform.getCommandModule().empty());
        }

        SECTION("onModule") {
            BasicCommandPlatform platform(name, cost, energy, maxModuleCount);
            platform.setModule(unique_ptr<IModule>(new BasicCommandModule(1, 5, 1, 2)));

            platform.onModule(platform.getCommandModule().begin());

            CHECK(platform.getCommandModule().begin()->get()->isOn());
        }

        SECTION("offModule") {
            BasicCommandPlatform platform(name, cost, energy, maxModuleCount);
            platform.setModule(unique_ptr<IModule>(new BasicCommandModule(1, 5, 1, 2)));

            platform.offModule(platform.getCommandModule().begin());

            CHECK(!platform.getCommandModule().begin()->get()->isOn());
        }

        SECTION("getControlledPlatform") {
            BasicCommandPlatform platform(name, cost, energy, maxModuleCount);
            BasicCommandModule* ptrComm = new BasicCommandModule(0, 5, 1, 2);

            unordered_set<id_t> inf = { 1,8,5 };
            ptrComm->setControlledRobot(inf);
            platform.setModule(unique_ptr<IModule>(ptrComm));

            CHECK(platform.getControlledPlatform() == inf);
        }
    }
}
