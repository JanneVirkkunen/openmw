#include "extensions0.hpp"

#include "opcodes.hpp"
#include "extensions.hpp"

namespace Compiler
{
    void registerExtensions (Extensions& extensions, bool consoleOnly)
    {
        Ai::registerExtensions (extensions);
        Animation::registerExtensions (extensions);
        Cell::registerExtensions (extensions);
        Container::registerExtensions (extensions);
        Control::registerExtensions (extensions);
        Dialogue::registerExtensions (extensions);
        Gui::registerExtensions (extensions);
        Misc::registerExtensions (extensions);
        Sky::registerExtensions (extensions);
        Sound::registerExtensions (extensions);
        Stats::registerExtensions (extensions);
        Transformation::registerExtensions (extensions);

        if (consoleOnly)
        {
            Console::registerExtensions (extensions);
            User::registerExtensions (extensions);
        }
    }

    namespace Ai
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("aiactivate", "c/l", opcodeAIActivate,
                opcodeAIActivateExplicit);
            extensions.registerInstruction ("aitravel", "fff/l", opcodeAiTravel,
                opcodeAiTravelExplicit);
            extensions.registerInstruction ("aiescort", "cffff/l", opcodeAiEscort,
                opcodeAiEscortExplicit);
            extensions.registerInstruction ("aiescortcell", "ccffff/l", opcodeAiEscortCell,
                opcodeAiEscortCellExplicit);
            extensions.registerInstruction ("aiwander", "fff/llllllllll", opcodeAiWander,
                opcodeAiWanderExplicit);
            extensions.registerInstruction ("aifollow", "cffff/l", opcodeAiFollow,
                opcodeAiFollowExplicit);
            extensions.registerInstruction ("aifollowcell", "ccffff/l", opcodeAiFollowCell,
                opcodeAiFollowCellExplicit);
            extensions.registerFunction ("getaipackagedone", 'l', "", opcodeGetAiPackageDone,
                opcodeGetAiPackageDoneExplicit);
            extensions.registerFunction ("getcurrentaipackage", 'l', "", opcodeGetCurrentAiPackage,
                opcodeGetAiPackageDoneExplicit);
            extensions.registerFunction ("getdetected", 'l', "c", opcodeGetDetected,
                opcodeGetDetectedExplicit);
            extensions.registerInstruction ("sethello", "l", opcodeSetHello, opcodeSetHelloExplicit);
            extensions.registerInstruction ("setfight", "l", opcodeSetFight, opcodeSetFightExplicit);
            extensions.registerInstruction ("setflee", "l", opcodeSetFlee, opcodeSetFleeExplicit);
            extensions.registerInstruction ("setalarm", "l", opcodeSetAlarm, opcodeSetAlarmExplicit);
            extensions.registerInstruction ("modhello", "l", opcodeModHello, opcodeModHelloExplicit);
            extensions.registerInstruction ("modfight", "l", opcodeModFight, opcodeModFightExplicit);
            extensions.registerInstruction ("modflee", "l", opcodeModFlee, opcodeModFleeExplicit);
            extensions.registerInstruction ("modalarm", "l", opcodeModAlarm, opcodeModAlarmExplicit);
            extensions.registerInstruction ("toggleai", "", opcodeToggleAI, opcodeToggleAI);
            extensions.registerInstruction ("tai", "", opcodeToggleAI, opcodeToggleAI);
            extensions.registerFunction ("gethello", 'l', "", opcodeGetHello, opcodeGetHelloExplicit);
            extensions.registerFunction ("getfight", 'l', "", opcodeGetFight, opcodeGetFightExplicit);
            extensions.registerFunction ("getflee", 'l', "", opcodeGetFlee, opcodeGetFleeExplicit);
            extensions.registerFunction ("getalarm", 'l', "", opcodeGetAlarm, opcodeGetAlarmExplicit);
            extensions.registerFunction ("getlineofsight", 'l', "c", opcodeGetLineOfSight, opcodeGetLineOfSightExplicit);
            extensions.registerFunction ("getlos", 'l', "c", opcodeGetLineOfSight, opcodeGetLineOfSightExplicit);
        }
    }

    namespace Animation
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("skipanim", "", opcodeSkipAnim, opcodeSkipAnimExplicit);
            extensions.registerInstruction ("playgroup", "c/l", opcodePlayAnim, opcodePlayAnimExplicit);
            extensions.registerInstruction ("loopgroup", "cl/l", opcodeLoopAnim, opcodeLoopAnimExplicit);
        }
    }

    namespace Cell
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerFunction ("cellchanged", 'l', "", opcodeCellChanged);
            extensions.registerInstruction ("coc", "S", opcodeCOC);
            extensions.registerInstruction ("centeroncell", "S", opcodeCOC);
            extensions.registerInstruction ("coe", "ll", opcodeCOE);
            extensions.registerInstruction ("centeronexterior", "ll", opcodeCOE);
            extensions.registerInstruction ("setwaterlevel", "f", opcodeSetWaterLevel);
            extensions.registerInstruction ("modwaterlevel", "f", opcodeModWaterLevel);
            extensions.registerFunction ("getinterior", 'l', "", opcodeGetInterior);
            extensions.registerFunction ("getpccell", 'l', "c", opcodeGetPCCell);
            extensions.registerFunction ("getwaterlevel", 'f', "", opcodeGetWaterLevel);
        }
    }

    namespace Console
    {
        void registerExtensions (Extensions& extensions)
        {

        }
    }

    namespace Container
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("additem", "cl", opcodeAddItem, opcodeAddItemExplicit);
            extensions.registerFunction ("getitemcount", 'l', "c", opcodeGetItemCount,
                opcodeGetItemCountExplicit);
            extensions.registerInstruction ("removeitem", "cl", opcodeRemoveItem,
                opcodeRemoveItemExplicit);
            extensions.registerInstruction ("equip", "c", opcodeEquip, opcodeEquipExplicit);
            extensions.registerFunction ("getarmortype", 'l', "l", opcodeGetArmorType, opcodeGetArmorTypeExplicit);
            extensions.registerFunction ("hasitemequipped", 'l', "c", opcodeHasItemEquipped, opcodeHasItemEquippedExplicit);
            extensions.registerFunction ("hassoulgem", 'l', "c", opcodeHasSoulGem, opcodeHasSoulGemExplicit);
            extensions.registerFunction ("getweapontype", 'l', "", opcodeGetWeaponType, opcodeGetWeaponTypeExplicit);
        }
    }

    namespace Control
    {
        void registerExtensions (Extensions& extensions)
        {
            std::string enable ("enable");
            std::string disable ("disable");

            for (int i=0; i<numberOfControls; ++i)
            {
                extensions.registerInstruction (enable + controls[i], "", opcodeEnable+i);
                extensions.registerInstruction (disable + controls[i], "", opcodeDisable+i);
                extensions.registerFunction (std::string("get") + controls[i] + std::string("disabled"), 'l', "", opcodeGetDisabled+i);
            }

            extensions.registerInstruction ("togglecollision", "", opcodeToggleCollision);
            extensions.registerInstruction ("tcl", "", opcodeToggleCollision);

            extensions.registerInstruction ("clearforcerun", "", opcodeClearForceRun,
                opcodeClearForceRunExplicit);
            extensions.registerInstruction ("forcerun", "", opcodeForceRun,
                opcodeForceRunExplicit);

            extensions.registerInstruction ("clearforcesneak", "", opcodeClearForceSneak,
                opcodeClearForceSneakExplicit);
            extensions.registerInstruction ("forcesneak", "", opcodeForceSneak,
                opcodeForceSneakExplicit);
            extensions.registerFunction ("getpcrunning", 'l', "", opcodeGetPcRunning);
            extensions.registerFunction ("getpcsneaking", 'l', "", opcodeGetPcSneaking);
            extensions.registerFunction ("getforcerun", 'l', "", opcodeGetForceRun, opcodeGetForceRunExplicit);
            extensions.registerFunction ("getforcesneak", 'l', "", opcodeGetForceSneak, opcodeGetForceSneakExplicit);
        }
    }

    namespace Dialogue
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("journal", "cl", opcodeJournal);
            extensions.registerInstruction ("setjournalindex", "cl", opcodeSetJournalIndex);
            extensions.registerFunction ("getjournalindex", 'l', "c", opcodeGetJournalIndex);
            extensions.registerInstruction ("addtopic", "S" , opcodeAddTopic);
            extensions.registerInstruction ("choice", "/SlSlSlSlSlSlSlSlSlSlSlSlSlSlSlSl", opcodeChoice);
            extensions.registerInstruction("forcegreeting","",opcodeForceGreeting);
            extensions.registerInstruction("forcegreeting","",opcodeForceGreeting,
                opcodeForceGreetingExplicit);
            extensions.registerInstruction("goodbye", "", opcodeGoodbye);
            extensions.registerInstruction("setreputation", "l", opcodeSetReputation,
                opcodeSetReputationExplicit);
            extensions.registerInstruction("modreputation", "l", opcodeModReputation,
                opcodeModReputationExplicit);
            extensions.registerFunction("getreputation", 'l', "", opcodeGetReputation,
                opcodeGetReputationExplicit);
            extensions.registerFunction("samefaction", 'l', "", opcodeSameFaction,
                opcodeSameFactionExplicit);
        }
    }

    namespace Gui
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("enablebirthmenu", "", opcodeEnableBirthMenu);
            extensions.registerInstruction ("enableclassmenu", "", opcodeEnableClassMenu);
            extensions.registerInstruction ("enablenamemenu", "", opcodeEnableNameMenu);
            extensions.registerInstruction ("enableracemenu", "", opcodeEnableRaceMenu);
            extensions.registerInstruction ("enablestatreviewmenu", "", 
                opcodeEnableStatsReviewMenu);

            extensions.registerInstruction ("enableinventorymenu", "", opcodeEnableInventoryMenu);
            extensions.registerInstruction ("enablemagicmenu", "", opcodeEnableMagicMenu);
            extensions.registerInstruction ("enablemapmenu", "", opcodeEnableMapMenu);
            extensions.registerInstruction ("enablestatsmenu", "", opcodeEnableStatsMenu);

            extensions.registerInstruction ("enablerest", "", opcodeEnableRest);
            extensions.registerInstruction ("enablelevelupmenu", "", opcodeEnableRest);

            extensions.registerInstruction ("showrestmenu", "", opcodeShowRestMenu);

            extensions.registerFunction ("getbuttonpressed", 'l', "", opcodeGetButtonPressed);

            extensions.registerInstruction ("togglefogofwar", "", opcodeToggleFogOfWar);
            extensions.registerInstruction ("tfow", "", opcodeToggleFogOfWar);

            extensions.registerInstruction ("togglefullhelp", "", opcodeToggleFullHelp);
            extensions.registerInstruction ("tfh", "", opcodeToggleFullHelp);

            extensions.registerInstruction ("showmap", "S", opcodeShowMap);
            extensions.registerInstruction ("fillmap", "", opcodeFillMap);
        }
    }

    namespace Misc
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerFunction ("xbox", 'l', "", opcodeXBox);
            extensions.registerFunction ("onactivate", 'l', "", opcodeOnActivate);
            extensions.registerInstruction ("activate", "", opcodeActivate);
            extensions.registerInstruction ("lock", "/l", opcodeLock, opcodeLockExplicit);
            extensions.registerInstruction ("unlock", "", opcodeUnlock, opcodeUnlockExplicit);
            extensions.registerInstruction ("togglecollisionboxes", "", opcodeToggleCollisionBoxes);
            extensions.registerInstruction ("togglecollisiongrid", "", opcodeToggleCollisionDebug);
            extensions.registerInstruction ("tcb", "", opcodeToggleCollisionBoxes);
            extensions.registerInstruction ("tcg", "", opcodeToggleCollisionDebug);
            extensions.registerInstruction ("twf", "", opcodeToggleWireframe);
            extensions.registerInstruction ("togglewireframe", "", opcodeToggleWireframe);
            extensions.registerInstruction ("fadein", "f", opcodeFadeIn);
            extensions.registerInstruction ("fadeout", "f", opcodeFadeOut);
            extensions.registerInstruction ("fadeto", "ff", opcodeFadeTo);
            extensions.registerInstruction ("togglewater", "", opcodeToggleWater);
            extensions.registerInstruction ("twa", "", opcodeToggleWater);
            extensions.registerInstruction ("togglepathgrid", "", opcodeTogglePathgrid);
            extensions.registerInstruction ("tpg", "", opcodeTogglePathgrid);
            extensions.registerInstruction ("dontsaveobject", "", opcodeDontSaveObject);
            extensions.registerInstruction ("togglevanitymode", "", opcodeToggleVanityMode);
            extensions.registerInstruction ("tvm", "", opcodeToggleVanityMode);
            extensions.registerFunction ("getpcsleep", 'l', "", opcodeGetPcSleep);
            extensions.registerInstruction ("wakeuppc", "", opcodeWakeUpPc);
            extensions.registerInstruction ("playbink", "Sl", opcodePlayBink);
            extensions.registerFunction ("getlocked", 'l', "", opcodeGetLocked, opcodeGetLockedExplicit);
            extensions.registerFunction ("geteffect", 'l', "S", opcodeGetEffect, opcodeGetEffectExplicit);
            extensions.registerInstruction ("addsoulgem", "cc", opcodeAddSoulGem, opcodeAddSoulGemExplicit);
            extensions.registerInstruction ("removesoulgem", "c", opcodeRemoveSoulGem, opcodeRemoveSoulGemExplicit);
            extensions.registerInstruction ("drop", "cl", opcodeDrop, opcodeDropExplicit);
            extensions.registerInstruction ("dropsoulgem", "c", opcodeDropSoulGem, opcodeDropSoulGemExplicit);
            extensions.registerFunction ("getattacked", 'l', "", opcodeGetAttacked, opcodeGetAttackedExplicit);
            extensions.registerFunction ("getweapondrawn", 'l', "", opcodeGetWeaponDrawn, opcodeGetWeaponDrawnExplicit);
            extensions.registerFunction ("getspelleffects", 'l', "c", opcodeGetSpellEffects, opcodeGetSpellEffectsExplicit);
            extensions.registerFunction ("getcurrenttime", 'f', "", opcodeGetCurrentTime);
            extensions.registerInstruction ("setdelete", "l", opcodeSetDelete, opcodeSetDeleteExplicit);
            extensions.registerFunction ("getsquareroot", 'f', "f", opcodeGetSquareRoot);
            extensions.registerInstruction ("fall", "", opcodeFall, opcodeFallExplicit);
            extensions.registerFunction ("getstandingpc", 'l', "", opcodeGetStandingPc, opcodeGetStandingPcExplicit);
            extensions.registerFunction ("getstandingactor", 'l', "", opcodeGetStandingActor, opcodeGetStandingActorExplicit);
            extensions.registerFunction ("getwindspeed", 'f', "", opcodeGetWindSpeed);
            extensions.registerFunction ("hitonme", 'l', "S", opcodeHitOnMe, opcodeHitOnMeExplicit);
            extensions.registerInstruction ("disableteleporting", "", opcodeDisableTeleporting);
            extensions.registerInstruction ("enableteleporting", "", opcodeEnableTeleporting);
            extensions.registerInstruction ("showvars", "", opcodeShowVars, opcodeShowVarsExplicit);
            extensions.registerInstruction ("sv", "", opcodeShowVars, opcodeShowVarsExplicit);
            extensions.registerInstruction("tgm", "", opcodeToggleGodMode);
            extensions.registerInstruction("togglegodmode", "", opcodeToggleGodMode);
            extensions.registerInstruction ("disablelevitation", "", opcodeDisableLevitation);
            extensions.registerInstruction ("enablelevitation", "", opcodeEnableLevitation);
        }
    }

    namespace Sky
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("togglesky", "", opcodeToggleSky);
            extensions.registerInstruction ("ts", "", opcodeToggleSky);
            extensions.registerInstruction ("turnmoonwhite", "", opcodeTurnMoonWhite);
            extensions.registerInstruction ("turnmoonred", "", opcodeTurnMoonRed);
            extensions.registerInstruction ("changeweather", "Sl", opcodeChangeWeather);
            extensions.registerFunction ("getmasserphase", 'l', "", opcodeGetMasserPhase);
            extensions.registerFunction ("getsecundaphase", 'l', "", opcodeGetSecundaPhase);
            extensions.registerFunction ("getcurrentweather", 'l', "", opcodeGetCurrentWeather);
            extensions.registerInstruction ("modregion", "S/llllllllll", opcodeModRegion);
        }
    }

    namespace Sound
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("say", "SS", opcodeSay, opcodeSayExplicit);
            extensions.registerFunction ("saydone", 'l', "", opcodeSayDone, opcodeSayDoneExplicit);
            extensions.registerInstruction ("streammusic", "S", opcodeStreamMusic);
            extensions.registerInstruction ("playsound", "c", opcodePlaySound);
            extensions.registerInstruction ("playsoundvp", "cff", opcodePlaySoundVP);
            extensions.registerInstruction ("playsound3d", "c", opcodePlaySound3D,
                opcodePlaySound3DExplicit);
            extensions.registerInstruction ("playsound3dvp", "cff", opcodePlaySound3DVP,
                opcodePlaySound3DVPExplicit);
            extensions.registerInstruction ("playloopsound3d", "c", opcodePlayLoopSound3D,
                opcodePlayLoopSound3DExplicit);
            extensions.registerInstruction ("playloopsound3dvp", "cff", opcodePlayLoopSound3DVP,
                opcodePlayLoopSound3DVPExplicit);
            extensions.registerInstruction ("stopsound", "c", opcodeStopSound,
                opcodeStopSoundExplicit);
            extensions.registerFunction ("getsoundplaying", 'l', "c", opcodeGetSoundPlaying,
                opcodeGetSoundPlayingExplicit);
        }
    }

    namespace Stats
    {
        void registerExtensions (Extensions& extensions)
        {
            static const char *attributes[numberOfAttributes] =
            {
                "strength", "intelligence", "willpower", "agility", "speed", "endurance",
                "personality", "luck"
            };

            static const char *dynamics[numberOfDynamics] =
            {
                "health", "magicka", "fatigue"
            };

            static const char *skills[numberOfSkills] =
            {
                "block", "armorer", "mediumarmor", "heavyarmor", "bluntweapon",
                "longblade", "axe", "spear", "athletics", "enchant", "destruction",
                "alteration", "illusion", "conjuration", "mysticism",
                "restoration", "alchemy", "unarmored", "security", "sneak",
                "acrobatics", "lightarmor", "shortblade", "marksman",
                "mercantile", "speechcraft", "handtohand"
            };

            std::string get ("get");
            std::string set ("set");
            std::string mod ("mod");
            std::string modCurrent ("modcurrent");
            std::string getRatio ("getratio");

            for (int i=0; i<numberOfAttributes; ++i)
            {
                extensions.registerFunction (get + attributes[i], 'l', "",
                    opcodeGetAttribute+i, opcodeGetAttributeExplicit+i);

                extensions.registerInstruction (set + attributes[i], "l",
                    opcodeSetAttribute+i, opcodeSetAttributeExplicit+i);

                extensions.registerInstruction (mod + attributes[i], "l",
                    opcodeModAttribute+i, opcodeModAttributeExplicit+i);
            }

            for (int i=0; i<numberOfDynamics; ++i)
            {
                extensions.registerFunction (get + dynamics[i], 'f', "",
                    opcodeGetDynamic+i, opcodeGetDynamicExplicit+i);

                extensions.registerInstruction (set + dynamics[i], "f",
                    opcodeSetDynamic+i, opcodeSetDynamicExplicit+i);

                extensions.registerInstruction (mod + dynamics[i], "f",
                    opcodeModDynamic+i, opcodeModDynamicExplicit+i);

                extensions.registerInstruction (modCurrent + dynamics[i], "f",
                    opcodeModCurrentDynamic+i, opcodeModCurrentDynamicExplicit+i);

                extensions.registerFunction (get + dynamics[i] + getRatio, 'f', "",
                    opcodeGetDynamicGetRatio+i, opcodeGetDynamicGetRatioExplicit+i);
            }

            for (int i=0; i<numberOfSkills; ++i)
            {
                extensions.registerFunction (get + skills[i], 'l', "",
                    opcodeGetSkill+i, opcodeGetSkillExplicit+i);

                extensions.registerInstruction (set + skills[i], "l",
                    opcodeSetSkill+i, opcodeSetSkillExplicit+i);

                extensions.registerInstruction (mod + skills[i], "l",
                    opcodeModSkill+i, opcodeModSkillExplicit+i);
            }

            extensions.registerFunction ("getpccrimelevel", 'f', "", opcodeGetPCCrimeLevel);
            extensions.registerInstruction ("setpccrimelevel", "f", opcodeSetPCCrimeLevel);
            extensions.registerInstruction ("modpccrimelevel", "f", opcodeModPCCrimeLevel);

            extensions.registerInstruction ("addspell", "c", opcodeAddSpell, opcodeAddSpellExplicit);
            extensions.registerInstruction ("removespell", "c", opcodeRemoveSpell,
                opcodeRemoveSpellExplicit);
            extensions.registerFunction ("getspell", 'l', "c", opcodeGetSpell, opcodeGetSpellExplicit);

            extensions.registerInstruction("pcraiserank","/S",opcodePCRaiseRank);
            extensions.registerInstruction("pclowerrank","/S",opcodePCLowerRank);
            extensions.registerInstruction("pcjoinfaction","/S",opcodePCJoinFaction);
            extensions.registerInstruction ("moddisposition","l",opcodeModDisposition,
                opcodeModDispositionExplicit);
            extensions.registerInstruction ("setdisposition","l",opcodeSetDisposition,
                opcodeSetDispositionExplicit);
            extensions.registerFunction ("getdisposition",'l', "",opcodeGetDisposition,
                opcodeGetDispositionExplicit);
            extensions.registerFunction("getpcrank",'l',"/S",opcodeGetPCRank,opcodeGetPCRankExplicit);

            extensions.registerInstruction("setlevel", "l", opcodeSetLevel, opcodeSetLevelExplicit);
            extensions.registerFunction("getlevel", 'l', "", opcodeGetLevel, opcodeGetLevelExplicit);

            extensions.registerFunction ("getdeadcount", 'l', "c", opcodeGetDeadCount);

            extensions.registerFunction ("getpcfacrep", 'l', "/c", opcodeGetPCFacRep, opcodeGetPCFacRepExplicit);
            extensions.registerInstruction ("setpcfacrep", "l/c", opcodeSetPCFacRep, opcodeSetPCFacRepExplicit);
            extensions.registerInstruction ("modpcfacrep", "l/c", opcodeModPCFacRep, opcodeModPCFacRepExplicit);

            extensions.registerFunction ("getcommondisease", 'l', "", opcodeGetCommonDisease,
                opcodeGetCommonDiseaseExplicit);
            extensions.registerFunction ("getblightdisease", 'l', "", opcodeGetBlightDisease,
                opcodeGetBlightDiseaseExplicit);

            extensions.registerFunction ("getrace", 'l', "c", opcodeGetRace,
                opcodeGetRaceExplicit);
            extensions.registerFunction ("getwerewolfkills", 'f', "", opcodeGetWerewolfKills);
            extensions.registerFunction ("pcexpelled", 'l', "/S", opcodePcExpelled, opcodePcExpelledExplicit);
            extensions.registerInstruction ("pcexpell", "/S", opcodePcExpell, opcodePcExpellExplicit);
            extensions.registerInstruction ("pcclearexpelled", "/S", opcodePcClearExpelled, opcodePcClearExpelledExplicit);
            extensions.registerInstruction ("raiserank", "", opcodeRaiseRank, opcodeRaiseRankExplicit);
            extensions.registerInstruction ("lowerrank", "", opcodeLowerRank, opcodeLowerRankExplicit);

            extensions.registerFunction ("ondeath", 'l', "", opcodeOnDeath, opcodeOnDeathExplicit);

            extensions.registerFunction ("iswerewolf", 'l', "", opcodeIsWerewolf, opcodeIsWerewolfExplicit);

            extensions.registerInstruction("becomewerewolf", "", opcodeBecomeWerewolf, opcodeBecomeWerewolfExplicit);
            extensions.registerInstruction("undowerewolf", "", opcodeUndoWerewolf, opcodeUndoWerewolfExplicit);
            extensions.registerInstruction("setwerewolfacrobatics", "", opcodeSetWerewolfAcrobatics, opcodeSetWerewolfAcrobaticsExplicit);
        }
    }

    namespace Transformation
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction("setscale","f",opcodeSetScale,opcodeSetScaleExplicit);
            extensions.registerFunction("getscale",'f',"",opcodeGetScale,opcodeGetScaleExplicit);
            extensions.registerInstruction("setangle","cf",opcodeSetAngle,opcodeSetAngleExplicit);
            extensions.registerFunction("getangle",'f',"c",opcodeGetAngle,opcodeGetAngleExplicit);
            extensions.registerInstruction("setpos","cf",opcodeSetPos,opcodeSetPosExplicit);
            extensions.registerFunction("getpos",'f',"c",opcodeGetPos,opcodeGetPosExplicit);
            extensions.registerFunction("getstartingpos",'f',"c",opcodeGetStartingPos,opcodeGetStartingPosExplicit);
            extensions.registerInstruction("position","ffff",opcodePosition,opcodePositionExplicit);
            extensions.registerInstruction("positioncell","ffffc",opcodePositionCell,opcodePositionCellExplicit);
            extensions.registerInstruction("placeitemcell","ccffff",opcodePlaceItemCell);
            extensions.registerInstruction("placeitem","cffff",opcodePlaceItem);
            extensions.registerInstruction("placeatpc","clfl",opcodePlaceAtPc);
            extensions.registerInstruction("placeatme","clfl",opcodePlaceAtMe,opcodePlaceAtMeExplicit);
            extensions.registerInstruction("modscale","f",opcodeModScale,opcodeModScaleExplicit);
            extensions.registerInstruction("rotate","cf",opcodeRotate,opcodeRotateExplicit);
            extensions.registerInstruction("rotateworld","cf",opcodeRotateWorld,opcodeRotateWorldExplicit);
            extensions.registerInstruction("setatstart","",opcodeSetAtStart,opcodeSetAtStartExplicit);
            extensions.registerInstruction("move","cf",opcodeMove,opcodeMoveExplicit);
            extensions.registerInstruction("moveworld","cf",opcodeMoveWorld,opcodeMoveWorldExplicit);
            extensions.registerFunction("getstartingangle",'f',"c",opcodeGetStartingAngle,opcodeGetStartingAngleExplicit);
        }
    }

    namespace User
    {
        void registerExtensions (Extensions& extensions)
        {
            extensions.registerInstruction ("user1", "", opcodeUser1);
            extensions.registerInstruction ("user2", "", opcodeUser2);
            extensions.registerInstruction ("user3", "", opcodeUser3, opcodeUser3);
            extensions.registerInstruction ("user4", "", opcodeUser4, opcodeUser4);
        }
    }
}
