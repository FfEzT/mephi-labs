#pragma once

#include "IPlatform.h"

#include <algorithm>
#include <iterator>
#include <unordered_set>

namespace GameLogic {
    namespace object {
        template <typename Parent = Platform>
        class BasicPlatform : public Parent
        {
        public:
            BasicPlatform(std::string describe, unsigned coast,
                unsigned energy, size_t maxModuleCount);

            bool isActive() const override
            {
                return sumGenerator() >= getSumEnergy();
            }

            bool isUnderControl() const override
            {
                return isUnderControl_;
            }

            void setIsUnderControl(bool status) override
            {
                isUnderControl_ = status;
            }

            size_t getIdTexture() const override
            {
                return PLATFORM;
            }

            unsigned getEnergy() const override;

            unsigned getSumEnergy() const override;

            unsigned getCost() const override;

            size_t getMaxModuleCount() const override;

            size_t getModuleCount() const override;

            const std::string& getDescribe() const override;

            std::unordered_set<id_t> getEnvironmentInfo() const override;

            void deleteModule(std::vector<std::shared_ptr<module::ISensor   >>::const_iterator element) override;
            void deleteModule(std::vector<std::shared_ptr<module::IGenerator>>::const_iterator element) override;

            void onModule(std::vector<std::shared_ptr<module::ISensor   >>::const_iterator element) override;
            void onModule(std::vector<std::shared_ptr<module::IGenerator>>::const_iterator element) override;

            void offModule(std::vector<std::shared_ptr<module::ISensor   >>::const_iterator element) override;
            void offModule(std::vector<std::shared_ptr<module::IGenerator>>::const_iterator element) override;

            const std::vector< std::shared_ptr<module::ISensor   >>& getSensors()    const override;
            const std::vector< std::shared_ptr<module::IGenerator>>& getGenerators() const override;

        protected:
            virtual std::vector<std::weak_ptr<module::IModule>> getAllModules() const;

            template <typename Type>
            static bool inVector(const std::vector<Type>& vec, std::vector<Type>::const_iterator it)
            {
                return it >= vec.cbegin() && it < vec.cend();
            }

        private:
            bool isUnderControl_ = false;

            void checkEnergy() override;

            unsigned sumGenerator() const;

            void setModule_(std::shared_ptr<module::ISensor> ptr) override;
            void setModule_(std::shared_ptr<module::IGenerator> ptr) override;

            std::vector< std::shared_ptr<module::ISensor   > > sensors;
            std::vector< std::shared_ptr<module::IGenerator> > generators;

            std::string describe_;
            size_t maxModuleCount_;
            unsigned energy_;
            unsigned coast_;
        };

        template <typename Parent>
        BasicPlatform<Parent>::BasicPlatform(std::string describe, unsigned coast, unsigned energy, size_t maxModuleCount)
            : describe_(std::move(describe)), coast_(coast),
            energy_(energy), maxModuleCount_(maxModuleCount)
        {}

        template <typename Parent>
        unsigned BasicPlatform<Parent>::getEnergy() const
        {
            return energy_;
        }

        template <typename Parent>
        unsigned BasicPlatform<Parent>::getSumEnergy() const
        {
            unsigned sum = getEnergy();
            for (const auto& ptr : sensors) {
                sum += ptr->getEnergy();
            }

            return sum;
        }

        template <typename Parent>
        unsigned BasicPlatform<Parent>::getCost() const
        {
            return coast_;
        }

        template <typename Parent>
        size_t BasicPlatform<Parent>::getMaxModuleCount() const
        {
            return maxModuleCount_;
        }

        template <typename Parent>
        size_t BasicPlatform<Parent>::getModuleCount() const
        {
            return sensors.size() + generators.size();
        }

        template <typename Parent>
        const std::string& BasicPlatform<Parent>::getDescribe() const
        {
            return describe_;
        }

        template <typename Parent>
        const std::vector< std::shared_ptr<module::ISensor> >& BasicPlatform<Parent>::getSensors() const
        {
            return sensors;
        }

        template <typename Parent>
        const std::vector< std::shared_ptr<module::IGenerator>>& BasicPlatform<Parent>::getGenerators() const
        {
            return generators;
        }

        template <typename Parent>
        std::unordered_set<id_t> BasicPlatform<Parent>::getEnvironmentInfo() const
        {
            if (!isActive())
                return {};

            using std::unordered_set;
            using std::vector;
            using std::shared_ptr;
            using std::back_inserter;
            using std::move;
            using std::unique;
            using module::ISensor;

            const vector<shared_ptr<ISensor>>& sensors = getSensors();
            unordered_set<id_t> res;

            for (const auto& sensor : sensors) {
                auto infoFromeOneSensor = sensor->getEnvironmentInfo();

                for (auto id : infoFromeOneSensor)
                    res.emplace(id);
            }

            return res;
        }

        template <typename Parent>
        void BasicPlatform<Parent>::checkEnergy()
        {
            unsigned sumGenerated = sumGenerator();
            unsigned consumed = getSumEnergy();
            if (sumGenerated >= consumed)
                return;

            using std::vector;
            using std::weak_ptr;
            using std::shared_ptr;
            using std::sort;

            using namespace module;

            vector<weak_ptr<IModule>> all_modules = getAllModules();

            sort(
                all_modules.begin(),
                all_modules.end(),
                [](weak_ptr<IModule>& left, weak_ptr<IModule>& right) {
                    return left.lock()->getPriority() < right.lock()->getPriority();
                }
            );

            for (auto& mod_ : all_modules) {
                shared_ptr<IModule> mod = mod_.lock();
                if (mod->isOn() && !dynamic_cast<IGenerator*>( mod.get() ) ) {
                    mod->setIsOn(false);
                    consumed -= mod->getEnergy();
                    if (sumGenerated >= consumed) {
                        return;
                    }
                }
            }
        }

        template <typename Parent>
        void BasicPlatform<Parent>::setModule_(std::shared_ptr<module::ISensor> ptr)
        {
            sensors.emplace_back(std::move(ptr));
        }

        template <typename Parent>
        void BasicPlatform<Parent>::setModule_(std::shared_ptr<module::IGenerator> ptr)
        {
            generators.emplace_back(std::move(ptr));
        }

        template <typename Parent>
        unsigned BasicPlatform<Parent>::sumGenerator() const
        {
            unsigned sum = 0;
            for (const auto& ptr : generators)
                sum += ptr->getEnergy();

            return sum;
        }

        template <typename Parent>
        void BasicPlatform<Parent>::deleteModule(std::vector<std::shared_ptr<module::ISensor>>::const_iterator element)
        {
            sensors.erase(element);
        }

        template <typename Parent>
        void BasicPlatform<Parent>::deleteModule(std::vector<std::shared_ptr<module::IGenerator>>::const_iterator element)
        {
            generators.erase(element);
        }

        template <typename Parent>
        void BasicPlatform<Parent>::onModule(std::vector<std::shared_ptr<module::ISensor>>::const_iterator element)
        {
            if (inVector(sensors, element))
                (*element)->setIsOn(true);
        }

        template <typename Parent>
        void BasicPlatform<Parent>::onModule(std::vector<std::shared_ptr<module::IGenerator>>::const_iterator element)
        {
            if (inVector(generators, element))
                (*element)->setIsOn(true);
        }

        template <typename Parent>
        void BasicPlatform<Parent>::offModule(std::vector<std::shared_ptr<module::ISensor>>::const_iterator element)
        {
            if (inVector(sensors, element))
                (*element)->setIsOn(false);
        }

        template <typename Parent>
        void BasicPlatform<Parent>::offModule(std::vector<std::shared_ptr<module::IGenerator>>::const_iterator element)
        {
            if (inVector(generators, element))
                (*element)->setIsOn(false);
        }

        template <typename Parent>
        std::vector<std::weak_ptr<module::IModule>>
            BasicPlatform<Parent>::getAllModules() const
        {
            using namespace std;
            using namespace module;

            vector<weak_ptr<IModule>> res;

            copy(
                sensors.begin(),
                sensors.end(),
                back_inserter(res)
            );

            copy(
                generators.begin(),
                generators.end(),
                back_inserter(res)
            );

            return res;
        }
    }
}
