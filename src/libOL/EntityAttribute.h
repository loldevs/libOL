// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__EntityAttribute__
#define __libol__EntityAttribute__

#include "Block.h"
#include "Value.h"

#include <cstdint>
#include <map>
#include <string>
#include <functional>

namespace libol {
    class EntityAttribute {
        typedef std::pair<uint8_t, uint8_t> AttrId;

        std::map<AttrId, std::function< void (Object&, Block::Stream&) >> attributes;

        template<typename T>
        void defineAttribute(uint8_t groupBit, uint8_t attrBit, std::string name) {
            AttrId id {groupBit, attrBit};

            attributes[id] = [name] (Object& obj, Block::Stream& stream) {
                obj.setv(name, stream.read<T>());
            };
        }

        EntityAttribute() {
            // Group 1
            defineAttribute<float>(1, 1, "CurrentGold");
            defineAttribute<float>(1, 2, "TotalGold");

            // Group 2
            defineAttribute<float>(2, 6, "BaseAttackDamage");
            defineAttribute<float>(2, 7, "BaseAbilityPower");
            defineAttribute<float>(2, 9, "CritChance");
            defineAttribute<float>(2, 10, "Amor");
            defineAttribute<float>(2, 11, "MagicResistance");
            defineAttribute<float>(2, 12, "Hp5");
            defineAttribute<float>(2, 13, "Mp5");
            defineAttribute<float>(2, 14, "Range");
            defineAttribute<float>(2, 15, "BonusAttackDamage");
            defineAttribute<float>(2, 16, "PctBonusAttackDamage");
            defineAttribute<float>(2, 17, "BonusAbilityPower");
            defineAttribute<float>(2, 20, "PctAttackSpeed");
            defineAttribute<float>(2, 23, "CooldownReduction");
            defineAttribute<float>(2, 26, "AmorPenetration");
            defineAttribute<float>(2, 27, "PctAmorPenetration");
            defineAttribute<float>(2, 28, "MagicPenetration");
            defineAttribute<float>(2, 29, "PctMagicPenetration");
            defineAttribute<float>(2, 30, "PctLifeSteal");
            defineAttribute<float>(2, 31, "PctSpellVamp");
            defineAttribute<float>(2, 32, "Tenacity");

            // Group 3

            // Group 4
            defineAttribute<float>(4, 1, "CurrentHealth");
            defineAttribute<float>(4, 2, "CurrentMana");
            defineAttribute<uint8_t>(4, 15, "Level");
        }
    public:
        static bool read(Object* obj, Block::Stream& stream, uint8_t groupBit, uint8_t attrBit) {
            static EntityAttribute reader;
            AttrId id {groupBit + 1, attrBit + 1};

            if(!reader.attributes.count(id)) return false;
            reader.attributes[id](*obj, stream);
            return true;
        }
    };
}

#endif /* defined(__libol__EntityAttribute__) */
