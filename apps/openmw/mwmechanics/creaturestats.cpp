#include "creaturestats.hpp"

#include <algorithm>

#include "../mwworld/esmstore.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

namespace MWMechanics
{
    CreatureStats::CreatureStats()
        : mLevel (0), mLevelHealthBonus(0.f), mDead (false), mDied (false), mFriendlyHits (0),
          mTalkedTo (false), mAlarmed (false),
          mAttacked (false), mHostile (false),
          mAttackingOrSpell(false), mAttackType(AT_Chop),
          mIsWerewolf(false)
    {
        for (int i=0; i<4; ++i)
            mAiSettings[i] = 0;
    }

    float CreatureStats::getLevelHealthBonus () const
    {
        return mLevelHealthBonus;
    }

    void CreatureStats::levelUp()
    {
        const MWWorld::Store<ESM::GameSetting> &gmst =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();

        const int endurance = getAttribute(ESM::Attribute::Endurance).getBase();

        // "When you gain a level, in addition to increasing three primary attributes, your Health
        // will automatically increase by 10% of your Endurance attribute. If you increased Endurance this level,
        // the Health increase is calculated from the increased Endurance"
        mLevelHealthBonus += endurance * gmst.find("fLevelUpHealthEndMult")->getFloat();
        updateHealth();

        mLevel++;
    }

    void CreatureStats::updateHealth()
    {
        const int endurance = getAttribute(ESM::Attribute::Endurance).getBase();
        const int strength = getAttribute(ESM::Attribute::Strength).getBase();

        setHealth(static_cast<int> (0.5 * (strength + endurance)) + mLevelHealthBonus);
    }

    const AiSequence& CreatureStats::getAiSequence() const
    {
        return mAiSequence;
    }

    AiSequence& CreatureStats::getAiSequence()
    {
        return mAiSequence;
    }

    float CreatureStats::getFatigueTerm() const
    {
        int max = getFatigue().getModified();
        int current = getFatigue().getCurrent();

        float normalised = max==0 ? 1 : std::max (0.0f, static_cast<float> (current)/max);

        const MWWorld::Store<ESM::GameSetting> &gmst =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();

        return gmst.find ("fFatigueBase")->getFloat()
            - gmst.find ("fFatigueMult")->getFloat() * (1-normalised);
    }

    const Stat<int> &CreatureStats::getAttribute(int index) const
    {
        if (index < 0 || index > 7) {
            throw std::runtime_error("attribute index is out of range");
        }
        return (!mIsWerewolf ? mAttributes[index] : mWerewolfAttributes[index]);
    }

    const DynamicStat<float> &CreatureStats::getHealth() const
    {
        return mDynamic[0];
    }

    const DynamicStat<float> &CreatureStats::getMagicka() const
    {
        return mDynamic[1];
    }

    const DynamicStat<float> &CreatureStats::getFatigue() const
    {
        return mDynamic[2];
    }

    const Spells &CreatureStats::getSpells() const
    {
        return mSpells;
    }

    const ActiveSpells &CreatureStats::getActiveSpells() const
    {
        return mActiveSpells;
    }

    const MagicEffects &CreatureStats::getMagicEffects() const
    {
        return mMagicEffects;
    }

    bool CreatureStats::getAttackingOrSpell() const
    {
        return mAttackingOrSpell;
    }

    int CreatureStats::getLevel() const
    {
        return mLevel;
    }

    int CreatureStats::getAiSetting (int index) const
    {
        assert (index>=0 && index<4);
        return mAiSettings[index];
    }

    Stat<int> &CreatureStats::getAttribute(int index)
    {
        if (index < 0 || index > 7) {
            throw std::runtime_error("attribute index is out of range");
        }
        return (!mIsWerewolf ? mAttributes[index] : mWerewolfAttributes[index]);
    }

    const DynamicStat<float> &CreatureStats::getDynamic(int index) const
    {
        if (index < 0 || index > 2) {
            throw std::runtime_error("dynamic stat index is out of range");
        }
        return mDynamic[index];
    }

    Spells &CreatureStats::getSpells()
    {
        return mSpells;
    }

    void CreatureStats::setSpells(const Spells &spells)
    {
        mSpells = spells;
    }

    ActiveSpells &CreatureStats::getActiveSpells()
    {
        return mActiveSpells;
    }

    MagicEffects &CreatureStats::getMagicEffects()
    {
        return mMagicEffects;
    }

    void CreatureStats::setAttribute(int index, const Stat<int> &value)
    {
        if (index < 0 || index > 7) {
            throw std::runtime_error("attribute index is out of range");
        }
        if(!mIsWerewolf)
            mAttributes[index] = value;
        else
            mWerewolfAttributes[index] = value;
    }

    void CreatureStats::setHealth(const DynamicStat<float> &value)
    {
        setDynamic (0, value);
    }

    void CreatureStats::setMagicka(const DynamicStat<float> &value)
    {
        setDynamic (1, value);
    }

    void CreatureStats::setFatigue(const DynamicStat<float> &value)
    {
        setDynamic (2, value);
    }

    void CreatureStats::setDynamic (int index, const DynamicStat<float> &value)
    {
        if (index < 0 || index > 2)
            throw std::runtime_error("dynamic stat index is out of range");

        mDynamic[index] = value;

        if (index==0 && mDynamic[index].getCurrent()<1)
        {
            if (!mDead)
                mDied = true;

            mDead = true;
        }
    }

    void CreatureStats::setLevel(int level)
    {
        mLevel = level;
    }

    void CreatureStats::setActiveSpells(const ActiveSpells &active)
    {
        mActiveSpells = active;
    }

    void CreatureStats::setMagicEffects(const MagicEffects &effects)
    {
        mMagicEffects = effects;
    }

    void CreatureStats::setAttackingOrSpell(bool attackingOrSpell)
    {
        mAttackingOrSpell = attackingOrSpell;
    }

    void CreatureStats::setAiSetting (int index, int value)
    {
        assert (index>=0 && index<4);
        mAiSettings[index] = value;
    }

    bool CreatureStats::isDead() const
    {
        return mDead;
    }

    bool CreatureStats::hasDied() const
    {
        return mDied;
    }

    void CreatureStats::clearHasDied()
    {
        mDied = false;
    }

    void CreatureStats::resurrect()
    {
        if (mDead)
        {
            if (mDynamic[0].getCurrent()<1)
                mDynamic[0].setCurrent (1);

            if (mDynamic[0].getCurrent()>=1)
                mDead = false;
        }
    }

    bool CreatureStats::hasCommonDisease() const
    {
        return mSpells.hasCommonDisease();
    }

    bool CreatureStats::hasBlightDisease() const
    {
        return mSpells.hasBlightDisease();
    }

    int CreatureStats::getFriendlyHits() const
    {
        return mFriendlyHits;
    }

    void CreatureStats::friendlyHit()
    {
        ++mFriendlyHits;
    }

    bool CreatureStats::hasTalkedToPlayer() const
    {
        return mTalkedTo;
    }

    void CreatureStats::talkedToPlayer()
    {
        mTalkedTo = true;
    }

    bool CreatureStats::isAlarmed() const
    {
        return mAlarmed;
    }

    void CreatureStats::setAlarmed (bool alarmed)
    {
        mAlarmed = alarmed;
    }

    bool CreatureStats::getAttacked() const
    {
        return mAttacked;
    }

    void CreatureStats::setAttacked (bool attacked)
    {
        mAttacked = attacked;
    }

    bool CreatureStats::isHostile() const
    {
        return mHostile;
    }

    void CreatureStats::setHostile (bool hostile)
    {
        mHostile = hostile;
    }

    bool CreatureStats::getCreatureTargetted() const
    {
        return false;
    }

    float CreatureStats::getEvasion() const
    {
        float evasion = (getAttribute(ESM::Attribute::Agility).getModified() / 5.0f) +
                        (getAttribute(ESM::Attribute::Luck).getModified() / 10.0f);
        evasion *= getFatigueTerm();
        evasion += mMagicEffects.get(EffectKey(ESM::MagicEffect::Sanctuary)).mMagnitude;

        return evasion;
    }

    void CreatureStats::setLastHitObject(const std::string& objectid)
    {
        mLastHitObject = objectid;
    }

    const std::string &CreatureStats::getLastHitObject() const
    {
        return mLastHitObject;
    }

    bool CreatureStats::canUsePower(const std::string &power) const
    {
        std::map<std::string, MWWorld::TimeStamp>::const_iterator it = mUsedPowers.find(power);
        if (it == mUsedPowers.end() || it->second + 24 <= MWBase::Environment::get().getWorld()->getTimeStamp())
            return true;
        else
            return false;
    }

    void CreatureStats::usePower(const std::string &power)
    {
        mUsedPowers[power] = MWBase::Environment::get().getWorld()->getTimeStamp();
    }
}
