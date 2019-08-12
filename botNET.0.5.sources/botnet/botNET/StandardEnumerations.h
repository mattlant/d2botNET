#ifndef STANDARDENUMERATIONS_H
#define STANDARDENUMERATIONS_H

/////////////////////////////////////////////////////////////////////
//
// Section:	Enumerations
//
////////////////////////////////////////////////////////////////////

namespace botNET
{

	__value public enum CursorMode
	{
		Normal = 0,
		Item = 1,
		Identify = 2,
		Repair = 3,
		Buy = 4,
		Sell = 5,
		Unkown = 6
	};

    namespace Diagnostics
    {
		__value public enum LogLevelType : int
        {
            Trace       = 1000,
            Event       = 2000,
            Warning     = 3000,
            Error       = 4000,
            Critical    = 5000
        };
    };

    namespace Units
	{

		__value	public enum	UnitBaseMode
		{
		};

		__value	public enum	PlayerMode
		{
			Death,
			Neutral,
			Walk,
			Run,
			GetHit,
			TownNeutral,
			TownWalk,
			Attack1,
			Attack2,
			Block,
			Cast,
			Throw,
			Kick,
			Skill1,
			Skill2,
			Skill3,
			Skill4,
			Dead,
			Sequence,
			KnockBack
		};

		__value	public enum	NPCMode
		{
			Death,
			Neutral,
			Walk,
			GetHit,
			Attack1,
			Attack2,
			Block,
			Cast,
			Skill1,
			Skill2,
			Skill3,
			Skill4,
			Dead,
			KnockBack,
			Sequence,
			Run
		};

		__value	public enum	ItemMode
		{
			InvStaCuSto,
			Equipped,
			InBelt,
			OnGround,
			OnCursor,
			Dropping,
			Socketed
		};

		__value	public enum	GameObjectMode
		{
			Neutral,
			Operating,
			Opened,
			Special1,
			Special2,
			Special3,
			Special4,
			Special5,
			Invalid = 99
		};

	}


	/////////////////////////////////////////////////////////////////////
	//List:	GetSkillLevelMode
	/////////////////////////////////////////////////////////////////////
	__value	public enum	GetSkillLevelMode
	{
		Base,
		Bonus,
		Total
	};

	/////////////////////////////////////////////////////////////////////
	//List:	MouseClickTypes
	/////////////////////////////////////////////////////////////////////
	__value	public enum	MouseClickType
	{
		LeftDown = WM_LBUTTONDOWN,
		LeftUp = WM_LBUTTONUP,
		MiddleDown = WM_MBUTTONDOWN,
		MiddleUp = WM_MBUTTONUP,
		RightDown = WM_RBUTTONDOWN,
		RightUp = WM_RBUTTONUP
	};

	__value	public enum	MouseEventType
	{
		LeftDown = WM_LBUTTONDOWN,
		LeftUp = WM_LBUTTONUP,
		MiddleDown = WM_MBUTTONDOWN,
		MiddleUp = WM_MBUTTONUP,
		RightDown = WM_RBUTTONDOWN,
		RightUp = WM_RBUTTONUP,
		MouseOver = 4,
		MouseOut = 5
	};

	__value	public enum	KeyPressEventType
	{
		KeyDown = WM_KEYDOWN,
		KeyUp = WM_KEYUP,
		SystemKeyDown = WM_SYSKEYDOWN,
		SystemKeyUp = WM_SYSKEYUP
	};

	/////////////////////////////////////////////////////////////////////
	//List:	UnitTypes
	/////////////////////////////////////////////////////////////////////
	__value	public enum	UnitType
	{
		Player = 0,
		NPC	= 1,
		GameObject = 2,
		Object = 2,
		Missile	= 3,
		Item = 4,
		Warp = 5,
		Invalid	= 6
	};

	/////////////////////////////////////////////////////////////////////
	//List:	PriceCheckType
	/////////////////////////////////////////////////////////////////////
	__value	public enum	PriceType
	{
		Buy	= 0,
		Sell = 1,
		Gamble = 2,
		Repair = 3
	};

	/////////////////////////////////////////////////////////////////////
	//List:	Color
	/////////////////////////////////////////////////////////////////////
	__value	public enum	Color
	{
		White =	0,
		Red	= 1,
		Green =	2,
		Blue = 3,
		Gold = 4,
		Gray = 5,
		Black =	6,
		Gold2 =	7,
		Orange = 8,
		Yellow = 9
	};

	/////////////////////////////////////////////////////////////////////
	//List:	ItemLocation
	/////////////////////////////////////////////////////////////////////
	__value	public enum	ItemLocation
	{

		Ground = 0,
		Equipped = 1,
		Belt = 2,
		Inventory =	3,
		Store =	4,
		Trade =	5,
		Cube = 6,
		Stash =	7,
		Unk8 = 8,
		Unk9 = 9,
		Cursor = 128,
		Dropping = 129,
		Socket = 130
	};

	/////////////////////////////////////////////////////////////////////
	//List:	MonsterType
	/////////////////////////////////////////////////////////////////////
	__value	public enum	MonsterType
	{

		Regular = 0,
		Boss = 1,
		SuperUnique = 2,
		Unique =	3,
		Champion =	4,
		Unknown = 99
	};

	namespace OutOfGame
	{
		/////////////////////////////////////////////////////////////////////
		// List: ControlType
		//
		// * TextBox = 1,
		// * Image,
		// * Image2,
		// * LabelBox,
		// * ScrollBar,
		// * Button,
		// * List,
		// * Timer,
		// * Smack,
		// * ProgressBar,
		// * Popup,
		// * AccountList
		//
		/////////////////////////////////////////////////////////////////////
		__value	public enum	ControlType
		{
			TextBox	= 1,
			Image,
			Image2,
			LabelBox,
			ScrollBar,
			Button,
			List,
			Timer,
			Smack,
			ProgressBar,
			Popup,
			AccountList
		};

	}

	namespace Drawing
	{

		/////////////////////////////////////////////////////////////////////
		// List: TextHookAlignment
		//
		// * Left
		// * Right
		// * Center
		//
		/////////////////////////////////////////////////////////////////////
		__value	public enum	TextHookAlignment
		{
			Left = 0,
			Right =	1,
			Center = 2
		};

		/////////////////////////////////////////////////////////////////////
		// List: TextHookColors
		//
		// * White
		// * Red
		// * Green
		// * Blue
		// * Gold
		// * Grey
		// * Black
		// * Brown
		// * Orange
		// * Yellow
		// * Purple
		//
		/////////////////////////////////////////////////////////////////////
		__value	public enum	TextHookColors
		{
			White =	0,
			Red	= 1,
			Green =	2,
			Blue = 3,
			Gold,
			Grey,
			Black,
			Brown,
			Orange,
			Yellow,
			Purple
		};

		/////////////////////////////////////////////////////////////////////
		// List: ScreenHookTransparency
		//
		// * High
		// * Mid
		// * Low
		// * Full
		// * NoLight
		// * None
		// * NoLightTransparent
		//
		/////////////////////////////////////////////////////////////////////
		__value	public enum	ScreenHookTransparency
		{
			High = 0,
			Mid	= 1,
			Low	= 2,
			Full = 3,
			NoLight	= 4,
			None = 5,
			NoLightTransparent = 6,
		};
	}

	///<summary>
	///	Defines	the	hand on	which skills can be	used.
	///</summary>
	[System::FlagsAttribute]
	__value	public enum	SkillHand
	{
		///<summary>
		///	Right hand.
		///</summary>
		Right =	0,
		///<summary>
		///	Left hand
		///</summary>
		Left = 0x80000000
	};

	/////////////////////////////////////////////////////////////////////
	// List: ClickTypes
	/////////////////////////////////////////////////////////////////////
	__value	public enum	ClickType
	{
		LeftDown = 0,
		LeftHold = 1,
		LeftUp = 2,
		RightDown =	3,
		RightHold =	4,
		RightUp	= 5
	};

	/////////////////////////////////////////////////////////////////////
	// List: PotionTypes
	/////////////////////////////////////////////////////////////////////
	__value	public enum	PotionType
	{
		AnyHealing = 1,
		AnyMana	= 2,
		AnyRejuvenation	= 3,
		Stamina	= 513,
		Antidote = 514,
		Rejuvenation = 515,
		LargeRejuvenation =	516,	//TODO: Rename this at some point?
		Thawing	= 517,
		MinorHealing = 587,
		LightHealing = 588,
		Healing	= 589,
		GreaterHealing = 590,
		SuperHealing = 591,
		MinorMana =	592,
		LightMana =	593,
		Mana = 594,
		GreaterMana	= 595,
		SuperMana =	596
	};

	/////////////////////////////////////////////////////////////////////
	// List: EquippedLocations
	/////////////////////////////////////////////////////////////////////
	__value	public enum	EquipmentLocation
	{
		NotEquipped	= 0,
		Helmet = 1,
		Amulet = 2,
		Armor =	3,
		RightHandSlot1 = 4,
		LeftHandSlot1 =	5,
		RightRing =	6,
		LeftRing = 7,
		Belt = 8,
		Boots =	9,
		Gloves = 10,
		RightHandSlot2 = 11,
		LeftHandSlot2 =	12
	};

	/////////////////////////////////////////////////////////////////////
	// List: QualityType
	/////////////////////////////////////////////////////////////////////
	__value	public enum	QualityType
	{
		NotApplicable =	0,
		LowQuality = 1,
		Normal = 2,
		Superior = 3,
		Magic =	4,
		Set	= 5,
		Rare = 6,
		Unique = 7,
		Crafted	= 8
	};

	/////////////////////////////////////////////////////////////////////
	// List: ItemClass
	/////////////////////////////////////////////////////////////////////
	__value	public enum	ItemClass
	{
		None = 0,
		Normal = 1,
		Exceptional	= 2,
		Elite =	3
	};

	/////////////////////////////////////////////////////////////////////
	// List: DifficultyType
	/////////////////////////////////////////////////////////////////////
	__value	public enum	DifficultyType
	{
		Normal = 1,
		Nightmare =	2,
		Hell = 3
	};

	/////////////////////////////////////////////////////////////////////
	// List: GameType
	/////////////////////////////////////////////////////////////////////
	__value	public enum	GameType
	{
		Classic	= 0,
		LoD	= 1
	};

	/////////////////////////////////////////////////////////////////////
	// List: CharClass
	/////////////////////////////////////////////////////////////////////
	__value	public enum	CharacterClass
	{
		Amazon = 0,
		Sorceress,
		Necromancer,
		Paladin,
		Barbarian,
		Druid,
		Assassin
	};


	__value	public enum	SkillType
	{
		Attack = 0,
		Kick = 1,
		Throw =	2,
		Unsummon = 3,
		LeftHandThrow =	4,
		LeftHandSwing =	5,
		MagicArrow = 6,
		FireArrow =	7,
		InnerSight = 8,
		CriticalStrike = 9,
		Jab	= 10,
		ColdArrow =	11,
		MultipleShot = 12,
		Dodge =	13,
		PowerStrike	= 14,
		PoisonJavelin =	15,
		ExplodingArrow = 16,
		SlowMissiles = 17,
		Avoid =	18,
		Impale = 19,
		LightningBolt =	20,
		IceArrow = 21,
		GuidedArrow	= 22,
		Penetrate =	23,
		ChargedStrike =	24,
		PlagueJavelin =	25,
		Strafe = 26,
		ImmolationArrow	= 27,
		Dopplezon =	28,
		Evade =	29,
		Fend = 30,
		FreezingArrow =	31,
		Valkyrie = 32,
		Pierce = 33,
		LightningStrike	= 34,
		LightningFury =	35,
		FireBolt = 36,
		Warmth = 37,
		ChargedBolt	= 38,
		IceBolt	= 39,
		FrozenArmor	= 40,
		Inferno	= 41,
		StaticField	= 42,
		Telekinesis	= 43,
		FrostNova =	44,
		IceBlast = 45,
		Blaze =	46,
		FireBall = 47,
		Nova = 48,
		Lightning =	49,
		ShiverArmor	= 50,
		FireWall = 51,
		Enchant	= 52,
		ChainLightning = 53,
		Teleport = 54,
		GlacialSpike = 55,
		Meteor = 56,
		ThunderStorm = 57,
		EnergyShield = 58,
		Blizzard = 59,
		ChillingArmor =	60,
		FireMastery	= 61,
		Hydra =	62,
		LightningMastery = 63,
		FrozenOrb =	64,
		ColdMastery	= 65,
		AmplifyDamage =	66,
		Teeth =	67,
		BoneArmor =	68,
		SkeletonMastery	= 69,
		RaiseSkeleton =	70,
		DimVision =	71,
		Weaken = 72,
		PoisonDagger = 73,
		CorpseExplosion	= 74,
		ClayGolem =	75,
		IronMaiden = 76,
		Terror = 77,
		BoneWall = 78,
		GolemMastery = 79,
		RaiseSkeletalMage =	80,
		Confuse	= 81,
		LifeTap	= 82,
		PoisonExplosion	= 83,
		BoneSpear =	84,
		Bloodgolem = 85,
		Attract	= 86,
		Decrepify =	87,
		BonePrison = 88,
		SummonResist = 89,
		Irongolem =	90,
		LowerResist	= 91,
		PoisonNova = 92,
		BoneSpirit = 93,
		Firegolem =	94,
		Revive = 95,
		Sacrifice =	96,
		Smite =	97,
		Might =	98,
		Prayer = 99,
		ResistFire = 100,
		HolyBolt = 101,
		HolyFire = 102,
		Thorns = 103,
		Defiance = 104,
		ResistCold = 105,
		Zeal = 106,
		Charge = 107,
		BlessedAim = 108,
		Cleansing =	109,
		ResistLightning	= 110,
		Vengeance =	111,
		BlessedHammer =	112,
		Concentration =	113,
		HolyFreeze = 114,
		Vigor =	115,
		Conversion = 116,
		HolyShield = 117,
		HolyShock =	118,
		Sanctuary =	119,
		Meditation = 120,
		FistOfTheHeavens = 121,
		Fanaticism = 122,
		Conviction = 123,
		Redemption = 124,
		Salvation =	125,
		Bash = 126,
		SwordMastery = 127,
		AxeMastery = 128,
		MaceMastery	= 129,
		Howl = 130,
		FindPotion = 131,
		Leap = 132,
		DoubleSwing	= 133,
		PolearmMastery = 134,
		ThrowingMastery	= 135,
		SpearMastery = 136,
		Taunt =	137,
		Shout =	138,
		Stun = 139,
		DoubleThrow	= 140,
		IncreasedStamina = 141,
		FindItem = 142,
		LeapAttack = 143,
		Concentrate	= 144,
		IronSkin = 145,
		BattleCry =	146,
		Frenzy = 147,
		IncreasedSpeed = 148,
		BattleOrders = 149,
		GrimWard = 150,
		Whirlwind =	151,
		Berserk	= 152,
		NaturalResistance =	153,
		WarCry = 154,
		BattleCommand =	155,
		FireHit	= 156,
		Unholybolt = 157,
		Skeletonraise =	158,
		Maggotegg =	159,
		Shamanfire = 160,
		Magottup = 161,
		Magottdown = 162,
		Magottlay =	163,
		Andrialspray = 164,
		Jump = 165,
		SwarmMove =	166,
		Nest = 167,
		QuickStrike	= 168,
		Vampirefireball	= 169,
		Vampirefirewall	= 170,
		Vampiremeteor =	171,
		Gargoyletrap = 172,
		Spiderlay =	173,
		Vampireheal	= 174,
		Vampireraise = 175,
		Submerge = 176,
		Fetishaura = 177,
		Fetishinferno =	178,
		Zakarumheal	= 179,
		Emerge = 180,
		Resurrect =	181,
		Bestow = 182,
		Missileskill1 =	183,
		Monteleport	= 184,
		Primelightning = 185,
		Primebolt =	186,
		Primeblaze = 187,
		Primefirewall =	188,
		Primespike = 189,
		Primeicenova = 190,
		Primepoisonball	= 191,
		Primepoisonnova	= 192,
		Diablight =	193,
		Diabcold = 194,
		Diabfire = 195,
		Fingermagespider = 196,
		Diabwall = 197,
		Diabrun	= 198,
		Diabprison = 199,
		Poisonballtrap = 200,
		Andypoisonbolt = 201,
		Hireablemissile	= 202,
		Desertturret = 203,
		Arcanetower	= 204,
		Monblizzard	= 205,
		Mosquito = 206,
		Cursedballtrapright	= 207,
		Cursedballtrapleft = 208,
		Monfrozenarmor = 209,
		Monbonearmor = 210,
		Monbonespirit =	211,
		Moncursecast = 212,
		Hellmeteor = 213,
		Regurgitatoreat	= 214,
		Monfrenzy =	215,
		Queendeath = 216,
		ScrollOfIdentify = 217,
		BookOfIdentify = 218,
		ScrollOfTownportal = 219,
		BookOfTownportal = 220,
		Raven =	221,
		PoisonCreeper = 222,
		Werewolf = 223,
		ShapeShifting =	224,
		Firestorm =	225,
		OakSage	= 226,
		SummonSpiritWolf = 227,
		Wearbear = 228,
		MoltenBoulder =	229,
		ArcticBlast	= 230,
		CycleOfLife	= 231,
		FeralRage =	232,
		Maul = 233,
		Fissure = 234,
		CycloneArmor = 235,
		HeartOfWolverine = 236,
		SummonDireWolf = 237,
		Rabies = 238,
		FireClaws =	239,
		Twister	= 240,
		Vines =	241,
		Hunger = 242,
		ShockWave =	243,
		Volcano	= 244,
		Tornado	= 245,
		SpiritOfBarbs =	246,
		SummonGrizzly =	247,
		Fury = 248,
		Armageddon = 249,
		Hurricane =	250,
		FireBlast = 251,
		ClawMastery	= 252,
		PsychicHammer =	253,
		TigerStrike	= 254,
		DragonTalon	= 255,
		ShockWeb = 256,
		BladeSentinel =	257,
		BurstOfSpeed = 258,
		FistsOfFire	= 259,
		DragonClaw = 260,
		ChargedBoltSentry =	261,
		WakeOfFireSentry = 262,
		WeaponBlock	= 263,
		CloakOfShadows = 264,
		CobraStrike	= 265,
		BladeFury =	266,
		Fade = 267,
		ShadowWarrior =	268,
		ClawsOfThunder = 269,
		DragonTail = 270,
		LightningSentry	= 271,
		WakeOfInferno = 272,
		MindBlast =	273,
		BladesOfIce	= 274,
		DragonFlight = 275,
		DeathSentry	= 276,
		BladeShield	= 277,
		Venom =	278,
		ShadowMaster = 279,
		PhoenixStrike =	280,
		WakeOfDestructionSentry	= 281,
		ImpInferno = 282,
		ImpFireball	= 283,
		BaalTaunt =	284,
		BaalCorpseExplode =	285,
		BaalMonsterSpawn = 286,
		CatapultChargedBall	= 287,
		CatapultSpikeBall =	288,
		SuckBlood =	289,
		CryHelp	= 290,
		HealingVortex =	291,
		Teleport2 =	292,
		Selfresurrect =	293,
		VineAttack = 294,
		OverseerWhip = 295,
		BarbsAura =	296,
		WolverineAura =	297,
		OakSageAura	= 298,
		ImpFireMissile = 299,
		Impregnate = 300,
		SiegeBeastStomp	= 301,
		Minionspawner =	302,
		Catapultblizzard = 303,
		Catapultplague = 304,
		Catapultmeteor = 305,
		Boltsentry = 306,
		Corpsecycler = 307,
		Deathmaul =	308,
		DefenseCurse = 309,
		BloodMana =	310,
		InfernoSentry2 = 311,
		DeathSentry2 = 312,
		SentryLightning	= 313,
		FenrisRage = 314,
		BaalTentacle = 315,
		BaalNova = 316,
		BaalInferno	= 317,
		BaalColdMissiles = 318,
		MegaDemonInferno = 319,
		EvilHutSpawner = 320,
		CountessFirewall = 321,
		ImpBolt	= 322,
		HorrorArcticBlast =	323,
		DeathSentryLightning = 324,
		VineCycler = 325,
		BearSmite =	326,
		Resurrect2 = 327,
		BloodLordFrenzy	= 328,
		BaalTeleport = 329,
		ImpTeleport	= 330,
		BaalCloneTeleport =	331,
		ZakarumLightning = 332,
		VampireMissile = 333,
		MephistoMissile	= 334,
		DoomKnightMissile =	335,
		RogueMissile = 336,
		HydraMissile = 337,
		NecromageMissile = 338,
		MonsterBow = 339,
		MonsterFireArrow = 340,
		MonsterColdArrow = 341,
		MonsterExplodingArrow =	342,
		MonsterFreezingArrow = 343,
		MonsterPowerStrike = 344,
		SuccubusBolt = 345,
		MephistoFrostNova =	346,
		MonsterIceSpear	= 347,
		ShamanIce =	348,
		Diablogeddon = 349,
		DeleriumChange = 350,
		NihlathakCorpseExplosion = 351,
		SerpentCharge =	352,
		TrapNova = 353,
		UnHolyBoltEx = 354,
		ShamanFireEx = 355,
		ImpFireMissileEx = 356
	};

	__value	public enum	AreaLevel
	{
		None                        = 0,
		RogueEncampment	            = 1,
		BloodMoor                   = 2,
		ColdPlains                  = 3,
		StonyField                  = 4,
		DarkWood                    = 5,
		BlackMarsh                  = 6,
		TamoeHighland               = 7,
		DenOfEvil                   = 8,
		CaveLevel1                  = 9,
		UndergroundPassageLevel1    = 10,
		HoleLevel1                  = 11,
		PitLevel1                   = 12,
		CaveLevel2                  = 13,
		UndergroundPassageLevel2    = 14,
		HoleLevel2                  = 15,
		PitLevel2                   = 16,
		BurialGrounds               = 17,
		Crypt                       = 18,
		Mausoleum                   = 19,
		ForgottenTower              = 20,
		TowerCellarLevel1           = 21,
		TowerCellarLevel2           = 22,
		TowerCellarLevel3           = 23,
		TowerCellarLevel4           = 24,
		TowerCellarLevel5           = 25,
		MonasteryGate               = 26,
		OuterCloister               = 27,
		Barracks                    = 28,
		JailLevel1                  = 29,
		JailLevel2                  = 30,
		JailLevel3                  = 31,
		InnerCloister               = 32,
		Cathedral                   = 33,
		CatacombsLevel1	            = 34,
		CatacombsLevel2	            = 35,
		CatacombsLevel3	            = 36,
		CatacombsLevel4	            = 37,
		Tristram                    = 38,
		MooMooFarm                  = 39,
		LutGholein                  = 40,
		RockyWaste                  = 41,
		DryHills                    = 42,
		FarOasis                    = 43,
		LostCity                    = 44,
		ValleyOfSnakes              = 45,
		CanyonOfTheMagi	            = 46,
		SewersLevel1Act2            = 47,
		SewersLevel2Act2            = 48,
		SewersLevel3Act2            = 49,
		HaremLevel1	                = 50,
		HaremLevel2	                = 51,
		PalaceCellarLevel1          = 52,
		PalaceCellarLevel2          = 53,
		PalaceCellarLevel3          = 54,
		StonyTombLevel1	            = 55,
		HallsOfTheDeadLevel1        = 56,
		HallsOfTheDeadLevel2        = 57,
		ClawViperTempleLevel1       = 58,
		StonyTombLevel2	            = 59,
		HallsOfTheDeadLevel3        = 60,
		ClawViperTempleLevel2       = 61,
		MaggotLairLevel1            = 62,
		MaggotLairLevel2            = 63,
		MaggotLairLevel3            = 64,
		AncientTunnels              = 65,
		TalRashasTomb1              = 66,
		TalRashasTomb2              = 67,
		TalRashasTomb3              = 68,
		TalRashasTomb4              = 69,
		TalRashasTomb5              = 70,
		TalRashasTomb6              = 71,
		TalRashasTomb7              = 72,
		DurielsLair                 = 73,
		ArcaneSanctuary	            = 74,
		KurastDocks                 = 75,
		SpiderForest                = 76,
		GreatMarsh                  = 77,
		FlayerJungle                = 78,
		LowerKurast	                = 79,
		KurastBazaar                = 80,
		UpperKurast	                = 81,
		KurastCauseway              = 82,
		Travincal                   = 83,
		SpiderCave                  = 84,
		SpiderCavern                = 85,
		SwampyPitLevel1	            = 86,
		SwampyPitLevel2	            = 87,
		FlayerDungeonLevel1	        = 88,
		FlayerDungeonLevel2	        = 89,
		SwampyPitLevel3	            = 90,
		FlayerDungeonLevel3	        = 91,
		SewersLevel1Act3            = 92,
		SewersLevel2Act3            = 93,
		RuinedTemple                = 94,
		DisusedFane	                = 95,
		ForgottenReliquary          = 96,
		ForgottenTemple	            = 97,
		RuinedFane                  = 98,
		DisusedReliquary            = 99,
		DuranceOfHateLevel1	        = 100,
		DuranceOfHateLevel2	        = 101,
		DuranceOfHateLevel3	        = 102,
		ThePandemoniumFortress      = 103,
		OuterSteppes                = 104,
		PlainsOfDespair	            = 105,
		CityOfTheDamned	            = 106,
		RiverOfFlame                = 107,
		ChaosSanctuary              = 108,
		Harrogath                   = 109,
		BloodyFoothills	            = 110,
		FrigidHighlands	            = 111,
		ArreatPlateau               = 112,
		CrystallinePassage	        = 113,
		FrozenRiver                 = 114,
		GlacialTrail	            = 115,
		DrifterCavern               = 116,
		FrozenTundra                = 117,
		TheAncientsWay              = 118,
		IcyCellar                   = 119,
		ArreatSummit                = 120,
		NihlathaksTemple            = 121,
		HallsOfAnguish              = 122,
		HallsOfPain                 = 123,
		HallsOfVaught               = 124,
		Abaddon                     = 125,
		PitOfAcheron                = 126,
		InfernalPit                 = 127,
		TheWorldStoneKeepLevel1	    = 128,
		TheWorldStoneKeepLevel2	    = 129,
		TheWorldStoneKeepLevel3	    = 130,
		ThroneOfDestruction	        = 131,
		TheWorldstoneChamber        = 132
	};

	__value public enum WaypointArea 
        { 
            RogueEncampment = 0, 
            ColdPlains, //1 
            StonyField, //2 
            DarkWood, //3 
            BlackMarsh, //4 
            OuterCloister, //5 
            JailLevel1, //6 
            InnerCloister, //7 
            CatacombsLevel2, //8 
            LutGholein, //9 
            SewersLevel2Act2, //10 
            DryHills, //11 
            HallsOfTheDeadLevel2, //12 
            FarOasis, //13 
            LostCity, //14 
            PalaceCellarLevel1, //15 
            ArcaneSanctuary, //16 
            CanyonOfTheMagi, //17 
            KurastDocks, //18 
            SpiderForest, //19 
            GreatMarsh, //20 
            FlayerJungle, //21 
            LowerKurast, //22 
            KurastBazaar, //23 
            UpperKurast, //24 
            Travincal, //25 
            DuranceOfHateLevel2, //26 
            ThePandemoniumFortress, //27 
            CityOfTheDamned, //28 
            RiverOfFlame, //29 
            Harrogath, //30 
            FrigidHighlands, //31 
            ArreatPlateau, //32 
            CrystallinePassage, //33 
            GlacialTrail, //34 
            HallsOfPain, //35 
            FrozenTundra, //36 
            TheAncientsWay, //37 
            TheWorldStoneKeepLevel2, //38 
        }; 

	__value	public enum	ItemType
	{
		None0 =	0x00,
		None1 =	0x01,
		Orb	= 0x44,
		StavesAndRods =	0x37,
		Axe	= 0x1C,
		HandToHand = 0x43,
		Gem	= 0x14,
		Bow	= 0x1B,
		Key	= 0x29,
		ChippedGem = 0x5B,
		FlawedGem =	0x5C,
		HandToHand2	= 0x58,
		StandardGem	= 0x5D,
		FlawlessGem	= 0x5E,
		PerfectGem = 0x5F,
		Spear =	0x21,
		LargeCharm = 0x54,
		MediumCharm	= 0x53,
		SmallCharm = 0x52,
		PaladinItem	= 0x3F,
		Amethyst = 0x60,
		Cloak =	0x49,
		ComboWeapon	= 0x31,
		BarbarianItem =	0x3D,
		Herb = 0x08,
		Club = 0x1D,
		Circlet	= 0x4B,
		SorceressItem =	0x40,
		Torch =	0x15,
		Miscellaneous =	0x34,
		VoodooHeads	= 0x45,
		AuricShields = 0x46,
		AnyShield =	0x33,
		Gold = 0x04,
		Diamond	= 0x61,
		Wand = 0x19,
		Mace = 0x24,
		Shield = 0x02,
		MeleeWeapon	= 0x2E,
		Polearm	= 0x22,
		Emerald	= 0x62,
		Rune = 0x4A,
		AmazonSpear	= 0x56,
		Javelin	= 0x2C,
		ThrowingAxe	= 0x2B,
		Staff =	0x1A,
		Knife =	0X20,
		Ring = 0x0A,
		ThrowingKnife =	0x2A,
		Potion = 0x09,
		DruidItem =	0x42,
		SocketFiller = 0x35,
		Book = 0x12,
		Missle = 0x38,
		Amulet = 0x0C,
		Jewel =	0x3A,
		Helm = 0x25,
		PrimalHelm = 0x47,
		Hammer = 0x1F,
		AssassinItem = 0x41,
		Blunt =	0x39,
		SecondHand = 0x36,
		AnyArmour =	0x32,
		Scroll = 0x16,
		ThrowingWeapon = 0x30,
		Weapon = 0x2D,
		Scepter	= 0x18,
		MagicCrossBowQuiver	= 0x5A,
		MagicBowQuiver = 0x59,
		CrossBowQuiver = 0x06,
		BowQuiver =	0x05,
		Charm =	0x0D,
		NecromancerItem	= 0x3E,
		Ruby = 0x63,
		Sword =	0x1E,
		ClassSpecific =	0x3B,
		QuestItem =	0x27,
		Sapphire = 0x64,
		Armor =	0x03,
		MissileWeapon =	0x2F,
		Belt = 0x13,
		Pelt = 0x48,
		Topaz =	0x65,
		Boots =	0x0F,
		AntidotePotion = 0x50,
		HealingPotion =	0x4C,
		ManaPotion = 0x4D,
		RejuvenationPotion = 0x4E,
		StaminaPotion =	0x4F,
		MissilePotion =	0x26,
		ThawingPotion =	0x51,
		AmazonJavelin =	0x57,
		Gloves = 0x10,
		AmazonBow =	0x55,
		CrossBow = 0x23,
		Elixir = 0x0B,
		PlayerBodyPart = 0x07,
		BodyPart = 0x28,
		AmazonItem = 0x3C,
		Skull =	0x66
	};

	__value	public enum	EnchantmentType
	{
		Unknown_00 = 0,
		Unknown_01 = 1,
		Unknown_02 = 2,
		Unknown_03 = 3,
		Unknown_04 = 4,
		ExtraStrong	= 5,
		ExtraFast =	6,
		Cursed = 7,
		MagicResistant = 8,
		FireEnchanted =	9,
		Unknown_10 = 10,
		Unknown_11 = 11,
		Unknown_12 = 12,
		Unknown_13 = 13,
		Unknown_14 = 14,
		Unknown_15 = 15,
		Champion = 16,
		LightningEnchanted = 17,
		ColdEnchanted =	18,
		Unknown_19 = 19,
		Unknown_20 = 20,
		Unknown_21 = 21,
		PresetBoss = 22,
		Unknown_23 = 23,
		Thief =	24,
		ManaBurn = 25,
		Teleportation =	26,
		SpectralHit	= 27,
		StoneSkin =	28,
		MultipleShots =	29,
		AuraEnchanted =	30,
		Unknown_31 = 31,
		Unknown_32 = 32,
		Unknown_33 = 33,
		Unknown_34 = 34,
		Unknown_35 = 35,
		Ghostly	= 36,
		Fanatic	= 37,
		Possessed =	38,
		Berserker =	39
		//MIN_VALID_VALUE =	5,
		//MAX_VALID_VALUE =	39
	};

	__value	public enum	StateType{
		None = 0,
		Freeze = 1,
		Poison = 2,
		ResistFire = 3,
		ResistCold = 4,
		ResistLight	= 5,
		ResistMagic	= 6,
		PlayerBody = 7,
		ResistAll =	8,
		AmplifyDamage =	9,
		FrozenArmor	= 10,
		Cold = 11,
		Inferno	= 12,
		Blaze =	13,
		BoneArmor =	14,
		Concentrate	= 15,
		Enchant	= 16,
		InnerSight = 17,
		SkillMove =	18,
		Weaken = 19,
		ChillingArmor =	20,
		Stunned	= 21,
		SpiderLay =	22,
		DimVision = 23,
		Slowed = 24,
		FetishAura = 25,
		Shout =	26,
		Taunt =	27,
		Conviction = 28,
		Convicted =	29,
		EnergyShield = 30,
		VenomClaws = 31,
		BattleOrders = 32,
		Might =	33,
		Prayer = 34,
		HolyFire = 35,
		Thorns = 36,
		Defiance = 37,
		Thunderstorm = 38,
		LightningBolt =	39,
		BlessedAim = 40,
		Stamina	= 41,
		Concentration =	42,
		HolyWind = 43,
		HolyWindCold = 44,
		Cleansing =	45,
		HolyShock =	46,
		Sanctuary =	47,
		Meditation = 48,
		Fanaticism = 49,
		Redemption = 50,
		BattleCommand =	51,
		PreventHeal	= 52,
		Conversion = 53,
		Uninterruptable	= 54,
		IronMaiden = 55,
		Terror = 56,
		Attract	= 57,
		LifeTap	= 58,
		Confuse	= 59,
		Decrepify =	60,
		LowerResist	= 61,
		OpenWounds = 62,
		Dopplezon =	63,
		CriticalStrike = 64,
		Dodge =	65,
		Avoid =	66,
		Penetrate =	67,
		Evade =	68,
		Pierce = 69,
		Warmth = 70,
		FireMastery	= 71,
		LightningMastery = 72,
		ColdMastery	= 73,
		SwordMastery = 74,
		AxeMastery = 75,
		MaceMastery	= 76,
		PolearmMastery = 77,
		ThrowingMastery	= 78,
		SpearMastery = 79,
		IncreasedStamina = 80,
		IronSkin = 81,
		IncreasedSpeed = 82,
		NaturalResistance =	83,
		FingerMageCurse	= 84,
		NoManaRegen	= 85,
		JustHit	= 86,
		SlowMissiles = 87,
		ShiverArmor	= 88,
		BattleCry =	89,
		Blue = 90,
		Red	= 91,
		DeathDelay = 92,
		Valkyrie = 93,
		Frenzy = 94,
		Berserk	= 95,
		Revive = 96,
		ItemFullSet	= 97,
		SourceUnit = 98,
		Redeemed = 99,
		HealthPot =	100,
		HolyShield = 101,
		JustPortaled = 102,
		MonFrenzy =	103,
		CorpseNoDraw = 104,
		Alignment =	105,
		ManaPot	= 106,
		Shatter	= 107,
		SyncWarped = 108,
		ConversionSave = 109,
		Pregnant = 110,
		Unknown_111	= 111, // Unknown
		Rabies = 112,
		DefenseCurse = 113,
		BloodMana =	114,
		Burning	= 115,
		DragonFlight = 116,
		Maul = 117,
		CorpseNoSelect = 118,
		ShadowWarrior =	119,
		FeralRage =	120,
		SkillDelay = 121,
		ProgressiveDamage =	122,
		ProgressiveSteal = 123,
		ProgressiveOther = 124,
		ProgressiveFire	= 125,
		ProgressiveCold	= 126,
		ProgressiveLightning = 127,
		ShrineArmor	= 128,
		ShrineCombat = 129,
		ShrineResistLightning =	130,
		ShrineResistFire = 131,
		ShrineResistCold = 132,
		ShrineResistPoison = 133,
		ShrineSkill	= 134,
		ShrineManaRegen	= 135,
		ShrineStamina =	136,
		ShrineExperience = 137,
		FenrisRage = 138,
		Wolf = 139,
		Bear = 140,
		Bloodlust =	141,
		ChangeClass	= 142,
		Attached = 143,
		Hurricane =	144,
		Armageddon = 145,
		Invis =	146,
		Barbs =	147,
		Wolverine =	148,
		OakSage	= 149,
		VineBeast =	150,
		CycloneArmor = 151,
		ClawMastery	= 152,
		CloakOfShadows = 153,
		Recycled = 154,
		WeaponBlock	= 155,
		Cloaked	= 156,
		QuicknessState =	157,
		BladeShield	= 158,
		FadeState = 159
	};

	__value	public enum	StatType
	{
		Strength = 0,
		Energy = 1,
		Dexterity =	2,
		Vitality = 3,
		StatPoints = 4,
		NewSkills =	5,
		HitPoints =	6,
		MaxHitPoints = 7,
		Mana = 8,
		MaxMana	= 9,
		Stamina	= 10,
		MaxStamina = 11,
		Level =	12,
		Experience = 13,
		Gold = 14,
		GoldBank = 15,
		ItemArmorPercent = 16,
		ItemMaxDamagePercent = 17,
		ItemMinDamagePercent = 18,
		ToHit =	19,
		ToBlock	= 20,
		MinDamage =	21,
		MaxDamage =	22,
		SecondaryMinDamage = 23,
		SecondaryMaxDamage = 24,
		DamagePercent =	25,
		ManaRecovery = 26,
		ManaRecoveryBonus =	27,
		StaminaRecoveryBonus = 28,
		LastExp	= 29,
		NextExp	= 30,
		ArmorClass = 31,
		ArmorClassVsMissile	= 32,
		ArmorClassVsHth	= 33,
		NormalDamageReduction =	34,
		MagicDamageReduction = 35,
		DamageResist = 36,
		MagicResist	= 37,
		MaxMagicResist = 38,
		FireResist = 39,
		MaxFireResist =	40,
		LightResist	= 41,
		MaxLightResist = 42,
		ColdResist = 43,
		MaxColdResist =	44,
		PoisonResist = 45,
		MaxPoisonResist	= 46,
		DamageAura = 47,
		FireMinDam = 48,
		FireMaxDam = 49,
		LightMinDam	= 50,
		LightMaxDam	= 51,
		MagicMinDam	= 52,
		MagicMaxDam	= 53,
		ColdMinDam = 54,
		ColdMaxDam = 55,
		ColdLength = 56,
		PoisonMinDam = 57,
		PoisonMaxDam = 58,
		PoisonLength = 59,
		LifeDrainMinDam	= 60,
		LifeDrainMaxDam	= 61,
		ManaDrainMinDam	= 62,
		ManaDrainMaxDam	= 63,
		StaminaDrainMinDam = 64,
		StaminaDrainMaxDam = 65,
		StunLength = 66,
		VelocityPercent	= 67,
		AttackRate = 68,
		OtherAnimRate =	69,
		Quantity = 70,
		Value =	71,
		Durability = 72,
		MaxDurability =	73,
		HpRegen	= 74,
		ItemMaxDurabilityPercent = 75,
		ItemMaxHpPercent = 76,
		ItemMaxManaPercent = 77,
		ItemAttackerTakesDamage	= 78,
		ItemGoldBonus =	79,
		ItemMagicBonus = 80,
		ItemKnockBack =	81,
		ItemTimeDuration = 82,
		ItemAddAmazonSkillPoints = 83,
		ItemAddPaladinSkillPoints =	84,
		ItemAddNecromancerSkillPoints =	85,
		ItemAddSorceressSkillPoints	= 86,
		ItemAddBarbarianSkillPoints	= 87,
		ItemDoubleHerbDuration = 88,
		ItemLightRadius	= 89,
		ItemLightColor = 90,
		ItemReqPercent = 91,
		ItemFastAttackRate = 92,
		ItemFasterAttackRate = 93,
		ItemFastestAttackRate =	94,
		ItemFastMoveVelocity = 95,
		ItemFasterMoveVelocity = 96,
		ItemFastestMoveVelocity	= 97,
		ItemFastGetHitRate = 98,
		ItemFasterGetHitRate = 99,
		ItemFastestGetHitRate =	100,
		ItemFastBlockRate =	101,
		ItemFasterBlockRate	= 102,
		ItemFastestBlockRate = 103,
		ItemFastCastRate = 104,
		ItemFasterCastRate = 105,
		ItemFastestCastRate	= 106,
		ItemSingleSkill1 = 107,
		ItemSingleSkill2 = 108,
		ItemSingleSkill3 = 109,
		ItemPoisonLengthResist = 110,
		ItemNormalDamage = 111,
		ItemHowl = 112,
		ItemStupidity =	113,
		ItemDamageToMana = 114,
		ItemIgnoreTargetAc = 115,
		ItemFractionalTargetAc = 116,
		ItemPreventHeal	= 117,
		ItemHalfFreezeDuration = 118,
		ItemToHitPercent = 119,
		ItemDamageTargetAc = 120,
		ItemDemonDamagePercent = 121,
		ItemUndeadDamagePercent	= 122,
		ItemDemonToHit = 123,
		ItemUndeadToHit	= 124,
		ItemThrowable =	125,
		ItemFireSkill =	126,
		ItemAllSkills =	127,
		ItemAttackerTakesLightDamage = 128,
		IronMaidenLevel	= 129,
		LifeTapLevel = 130,
		ThornsLevel	= 131,
		BoneArmor =	132,
		BoneArmorMax = 133,
		ItemFreeze = 134,
		ItemOpenWounds = 135,
		ItemCrushingBlow = 136,
		ItemKickDamage = 137,
		ItemManaAfterKill =	138,
		ItemHealAfterDemonKill = 139,
		ItemExtraBlood = 140,
		ItemDeadlyStrike = 141,
		ItemAbsorbFirePercent =	142,
		ItemAbsorbFire = 143,
		ItemAbsorbLightPercent = 144,
		ItemAbsorbLight	= 145,
		ItemAbsorbMagicPercent = 146,
		ItemAbsorbMagic	= 147,
		ItemAbsorbColdPercent =	148,
		ItemAbsorbCold = 149,
		ItemSlow = 150,
		ItemBlessedAim = 151,
		ItemIndestructible = 152,
		ItemCannotBeFrozen = 153,
		ItemStaminaDrainPct	= 154,
		ItemReanimate =	155,
		ItemPierce = 156,
		ItemMagicArrow = 157,
		ItemExplosiveArrow = 158,
		ItemThrowMinDamage = 159,
		ItemThrowMaxDamage = 160,
		SkillHandOfAthena =	161,
		SkillStaminaPercent	= 162,
		SkillPassiveStaminaPercent = 163,
		SkillConcentration = 164,
		SkillEnchant = 165,
		SkillPierce	= 166,
		SkillConviction	= 167,
		SkillChillingArmor = 168,
		SkillFrenzy	= 169,
		SkillDecertify = 170,
		SkillArmorPercent =	171,
		Alignment =	172,
		Target0	= 173,
		Target1	= 174,
		GoldLost = 175,
		ConversionLevel	= 176,
		ConversionMaxHitPoints = 177,
		UnitDoOverlay =	178,
		ItemAddDruidSkillPoints	= 179,
		ItemAddAssassinSkillPoints = 180,
		ItemAddSkillSingle4	= 181,
		ItemAddSkillSingle5	= 182,
		ItemAddSkillSingle6	= 183,
		ItemAddSkillSingle7	= 184,
		ItemAddSkillSingle8	= 185,
		ItemAddSkillSingle9	= 186,
		ItemAddSkillSingle10 = 187,
		ItemAddSkillTab1 = 188,
		ItemAddSkillTab2 = 189,
		ItemAddSkillTab3 = 190,
		ItemAddSkillTab4 = 191,
		ItemAddSkillTab5 = 192,
		ItemAddSkillTab6 = 193,
		ItemNumSockets = 194,
		ItemSkillOnAttack1 = 195,
		ItemSkillOnAttack2 = 196,
		ItemSkillOnAttack3 = 197,
		ItemSkillOnHit1	= 198,
		ItemSkillOnHit2	= 199,
		ItemSkillOnHit3	= 200,
		ItemSkillOnGetHit1 = 201,
		ItemSkillOnGetHit2 = 202,
		ItemSkillOnGetHit3 = 203,
		ItemChargedSkill0 =	204,
		ItemChargedSkill1 =	205,
		ItemChargedSkill2 =	206,
		ItemChargedSkill3 =	207,
		ItemChargedSkill4 =	208,
		ItemChargedSkill5 =	209,
		ItemChargedSkill6 =	210,
		ItemChargedSkill7 =	211,
		ItemChargedSkill8 =	212,
		ItemChargedSkill9 =	213,
		ItemArmorPerLevel =	214,
		ItemArmorPercentPerLevel = 215,
		ItemHpPerLevel = 216,
		ItemManaPerLevel = 217,
		ItemMaxDamagePerLevel =	218,
		ItemMaxDamagePercentPerLevel = 219,
		ItemStrengthPerLevel = 220,
		ItemDexterityPerLevel =	221,
		ItemEnergyPerLevel = 222,
		ItemVitalityPerLevel = 223,
		ItemToHitPerLevel =	224,
		ItemToHitPercentPerLevel = 225,
		ItemColdDamageMaxPerLevel =	226,
		ItemFireDamageMaxPerLevel =	227,
		ItemLightDamageMaxPerLevel = 228,
		ItemPoisonDamageMaxPerLevel	= 229,
		ItemResistColdPerLevel = 230,
		ItemResistFirePerLevel = 231,
		ItemResistLightPerLevel	= 232,
		ItemResistPoisonPerLevel = 233,
		ItemAbsorbColdPerLevel = 234,
		ItemAbsorbFirePerLevel = 235,
		ItemAbsorbLightPerLevel	= 236,
		ItemAbsorbPoisonPerLevel = 237,
		ItemThornsPerLevel = 238,
		ItemFindGoldPerLevel = 239,
		ItemFindMagicPerLevel =	240,
		ItemRegenStaminaPerLevel = 241,
		ItemStaminaPerLevel	= 242,
		ItemDamageDemonPerLevel	= 243,
		ItemDamageUndeadPerLevel = 244,
		ItemToHitDemonPerLevel = 245,
		ItemToHitUndeadPerLevel	= 246,
		ItemCrushingBlowPerLevel = 247,
		ItemOpenWoundsPerLevel = 248,
		ItemKickDamagePerLevel = 249,
		ItemDeadlyStrikePerLevel = 250,
		ItemFindGemsPerLevel = 251,
		ItemReplenishDurability	= 252,
		ItemReplenishQuantity =	253,
		ItemExtraStack = 254,
		ItemFindItem = 255,
		ItemSlashDamage	= 256,
		ItemSlashDamagePercent = 257,
		ItemCrushDamage	= 258,
		ItemCrushDamagePercent = 259,
		ItemThrustDamage = 260,
		ItemThrustDamagePercent	= 261,
		ItemAbsorbSlash	= 262,
		ItemAbsorbCrush	= 263,
		ItemAbsorbThrust = 264,
		ItemAbsorbSlashPercent = 265,
		ItemAbsorbCrushPercent = 266,
		ItemAbsorbThrustPercent	= 267,
		ItemArmorByTime	= 268,
		ItemArmorPercentByTime = 269,
		ItemHpByTime = 270,
		ItemManaByTime = 271,
		ItemMaxDamageByTime	= 272,
		ItemMaxDamagePercentByTime = 273,
		ItemStrengthByTime = 274,
		ItemDexterityByTime	= 275,
		ItemEnergyByTime = 276,
		ItemVitalityByTime = 277,
		ItemToHitByTime	= 278,
		ItemToHitPercentByTime = 279,
		ItemColdDamageMaxByTime	= 280,
		ItemFireDamageMaxByTime	= 281,
		ItemLightDamageMaxByTime = 282,
		ItemPoisonDamageMaxByTime =	283,
		ItemResistColdByTime = 284,
		ItemResistFireByTime = 285,
		ItemResistLightByTime =	286,
		ItemResistPoisonByTime = 287,
		ItemAbsorbColdByTime = 288,
		ItemAbsorbFireByTime = 289,
		ItemAbsorbLightByTime =	290,
		ItemAbsorbPoisonByTime = 291,
		ItemFindGoldByTime = 292,
		ItemFindMagicByTime	= 293,
		ItemRegenStaminaByTime = 294,
		ItemStaminaByTime =	295,
		ItemDamageDemonByTime =	296,
		ItemDamageUndeadByTime = 297,
		ItemToHitDemonByTime = 298,
		ItemToHitUndeadByTime =	299,
		ItemCrushingBlowByTime = 300,
		ItemOpenWoundsByTime = 301,
		ItemKickDamageByTime = 302,
		ItemDeadlyStrikeByTime = 303,
		ItemFindGemsByTime = 304,
		ItemPierceCold = 305,
		ItemPierceFire = 306,
		ItemPierceLight	= 307,
		ItemPiercePoison = 308,
		ItemDamageVsMonster	= 309,
		ItemDamagePercentVsMonster = 310,
		ItemToHitVsMonster = 311,
		ItemToHitPercentVsMonster =	312,
		ItemAcVsMonster	= 313,
		ItemAcPercentVsMonster = 314,
		FireLength = 315,
		BurningMin = 316,
		BurningMax = 317,
		ProgressiveDamage =	318,
		ProgressiveSteal = 319,
		ProgressiveOther = 320,
		ProgressiveFire	= 321,
		ProgressiveCold	= 322,
		ProgressiveLightning = 323,
		ItemExtraCharges = 324,
		ProgressiveToHit = 325,
		PoisonCount	= 326,
		DamageFramerate	= 327,
		PierceIdx =	328,
		PassiveFireMastery = 329,
		PassiveLightningMastery	= 330,
		PassiveColdMastery = 331,
		PassivePoisonMastery = 332,
		PassiveFirePierce =	333,
		PassiveLightningPierce = 334,
		PassiveColdPierce =	335,
		PassivePoisonPierce	= 336,
		PassiveCriticalStrike =	337,
		PassiveDodge = 338,
		PassiveAvoid = 339,
		PassiveEvade = 340,
		PassiveWarmth =	341,
		PassiveMasteryMeleeTh =	342,
		PassiveMasteryMeleeDmg = 343,
		PassiveMasteryMeleeCrit	= 344,
		PassiveMasteryThrowTh =	345,
		PassiveMasteryThrowDmg = 346,
		PassiveMasteryThrowCrit	= 347,
		PassiveWeaponblock = 348,
		PassiveSummonResist	= 349,
		ModifierlistSkill =	350,
		ModifierlistLevel =	351,
		LastSentHpPct =	352,
		SourceUnitType = 353,
		SourceUnitId = 354,
		Shortparam1	= 355,
		QuestItemDifficulty	= 356,
		QassiveMagMastery =	357,
		PassiveMagPierce = 358
	};

	//[Flags]
	__value	public enum	ItemFlag
	{
		IsRuneword = 0x4000000,	// set if it is	a runeword (note that 'ith'	qualifies ;)
		IsNamed	= 0x1000000, //	has	a custom name "Player's	item"
		IsAny =	0x0800000, // was set for all items	tested (tested in inv, stash, store)
		IsEthereal = 0x0400000,	// 0 if	not	ethereal
		IsRuneOrPot	= 0x0200000, //	rune or	potion,	also set for mephisto's	soulstone
		IsStartItem	= 0x0020000, //	an item	that a new character starts	with (like javelin and buckler,	and	the	minor healings at the start)
		IsEar =	0x0010000, // a	player ear
		IsNotInSocket =	0x0004000, // 0	if in socket, 0	if in belt,	0 if equipped or equipped by merc, 0 for gems/charms/..
		IsInStore =	0x0002000, // in trade or gamble screen
		IsSocketed = 0x0000800,	// the item	has	sockets	(they can be full or empty)
		IsRejuvenation = 0x0000400,	// only	seen set for full rejuvs for now
		IsBroken = 0x0000100, // just a	bet, but i'm pretty	sure it's correct
		IsSwitchedOut =	0x0000080, // a	weapon switch command was performed, and this item is no longer	being used
		IsSwitchedIn = 0x0000040, // a weapon switch command was performed,	and	this item is now being used
		IsIdentified = 0x0000010, // 0 if unid
		IsInSocket = 0x0000008,	// 8 if	in socket, valid for rune and jewels, not gems
		IsEquipped = 0x0000001,	// player or merc is wearing the item (don't trust too much, especially	when bit 9 is set)
		None = 0x0000000, // player	or merc	is wearing the item	(don't trust too much, especially when bit 9 is	set)
		BIT_MASK = IsRuneword |
		IsNamed	|
		IsAny |
		IsEthereal |
		IsRuneOrPot	|
		IsStartItem	|
		IsEar |
		IsNotInSocket |
		IsInStore |
		IsSocketed |
		IsRejuvenation|
		IsBroken |
		IsSwitchedOut |
		IsSwitchedIn |
		IsIdentified |
		IsInSocket |
		IsEquipped
	};

	namespace Mapping
	{
		[System::FlagsAttribute]
		__value	public enum	Collision
		{
			None = 0x00,
			Walk = 0x01,
			LineOfSight	= 0x02,
			Jump = 0x04, //	Seems to also block	attack.
			PlayerWalk = 0x08,
			Bit_04 = 0x10, // This doesn't block Walk or LineOfSight.
			Light =	0x20,
			Bit_06 = 0x40,
			Bit_07 = 0x80, // Players (any).
			Default	= Walk |
			LineOfSight	|
			PlayerWalk,
			BIT_MASK = Walk	|
			LineOfSight	|
			Jump |
			PlayerWalk |
			Bit_04 |
			Light |
			Bit_06 |
			Bit_07
		};
	}

	__value public enum MainMenu
	{
		Cancel = 0x0000,
		Talk = 0x0D35,
		Trade = 0x0D44,
		TradeOrRepair = 0x0D06,
		Imbue = 0x0FB1,
		Gamble = 0x0D46,
		Hire = 0x0D45,
		GoEast = 0x0D36,
		GoWest = 0x0D37,
		IdentifyItems = 0x0FB4,
		SailEast = 0x0D38,
		SailWest = 0x0D39,
		RessurectMerc = 0x1507,
		AddSockets = 0x58DC,
		Personalize = 0x58DD,
		TravelToHarrogath = 0x58D2
	};

	// #define NUM_UI 0x26
	// D2Client\UI\ui.cpp, line #3097
	// (nUIId < NUM_UI)
	__value public enum UIState
	{
		MainUIBar = 0x00,
		InventoryPanel = 0x01,
		CharacterPanel = 0x02,
		QuickSkillPanel = 0x03,
		SkillPanel = 0x04,
		ChatBox = 0x05,
		NewStatsAvailable = 0x06,
		NewSkillsAvailable = 0x07, //SkillBook_A2Q1 = 0x07, //This was so wrong
		NPCMenuPanel = 0x08,
		GameMenuActive = 0x09,
		AutoMapActive = 0x0A,
		ConfigureControlsPanel = 0x0B,
		StorePanel = 0x0C,
		ShowItemsAltKey = 0x0D,
		SpecialPanel = 0x0E,
		GoldPanel = 0x0E, // Forgot what I meant by this... // UIManip Enable -> D2Client\UI\useitems.cpp Expression: 0
		AddSocketsPanel = 0x0E,
		ImbuePanel = 0x0E,
		PersonalizePanel = 0x0E,
		HoradricOrificePanel = 0x0E,
		QuestPanel = 0x0F,
		ScrollOfInifussActive = 0x10,
		QuestLog = 0x11,
		StatusArea = 0x12,
		Unknown_0X13 = 0x13, // Drawing something?		Turn off merc/minion/player portraits and hit escape twice to turn off.
		WaypointPanel = 0x14,
		MiniPanel = 0x15,
		PartyPanel = 0x16,
		PlayerTradeRequest = 0x17,
		MessagePanel = 0x18,
		StashPanel = 0x19,
		CubePanel = 0x1A,
		Unknown_0X1B = 0x1B, // Uses trade screen boarder with black
		Unknown_0X1C = 0x1C, // Uses left trade boarder, fake inventory
		Unknown_0X1D = 0x1D, // Uses trade screen boarder with black
		Unknown_0X1E = 0x1E, // No change?		can't interact
		BeltOpened = 0x1F, // Using tilde key only, NOT mouse-over.
		Unknown_0X20 = 0x20, // Uses trade screen boarder with black
		HelpPanel = 0x21,
		Unknown_0X22 = 0x22, // Auto turns off
		PortraitsActive = 0x23, // Merc, minion(s), or other player portraits showing.
		MercenaryPanel = 0x24,
		ScrollOfUnimplemented = 0x25, // Also forgot what this was... // Probably the frame for those runeword scrolls that never were implemented
	};

}

#endif