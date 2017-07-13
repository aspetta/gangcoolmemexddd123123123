/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "GUI.h"
#include "Controls.h"

class CRageBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CSlider	  AimbotFov;
	CCheckBox AimbotSilentAim;
	CCheckBox AimbotPerfectSilentAim;
	CCheckBox AimbotAutoPistol;
	CCheckBox AimbotAimStep;
	CCheckBox AimbotKeyPress;
	CCheckBox AutoAwpBody;
	CComboBox AccuracyAngleFixY;
	CComboBox AccuracyAngleFix;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoRevolver;
	CKeyBind  AimbotStopKey;

	// Target Selection Settings
	CGroupBox TargetGroup;
	CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CComboBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CSlider   TargetPointscale;


	// Accuracy Settings
	CGroupBox AccuracyGroup;
	CComboBox AccuracyResolverPitch;
	CCheckBox AccuracyRecoil;
	CCheckBox AccuracyAutoWall;
	CSlider	  AccuracyMinimumDamage;
	CCheckBox AccuracyAutoStop;
	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CSlider   AccuracyHitchance;
	CComboBox AccuracyResolver; 
	CComboBox AccuracyXReslver;
	CComboBox AccuracyAaCorrection;
	CComboBox AccuracyYResolver;
	CComboBox AccuracyResolverType;
	CComboBox AccuracyResolverYaw;
	CCheckBox AccuracyAutoResolver;
	CComboBox PreferBodyAim;

	CCheckBox AccuracyPositionAdjustment;
	CSlider   AccuracySmart;

	// Anti-Aim Settings
	CGroupBox AntiAimGroup;
	CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CComboBox AntiAimYaw;
	CComboBox Fakeyaw;
	CCheckBox AntiAimEdge;
	CCheckBox EdgeAntiAim;
	CSlider	  AntiAimOffset;
	CSlider AntiAimPitchoffset;
	CCheckBox AntiAimKnife;
	CCheckBox AntiAimNoSpread;
	CSlider   AntiAimSpeed;
	CCheckBox AntiAimTarget;

};

class CLegitBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;
	CSlider   AimbotInaccuracy;
	CKeyBind  AimbotDisableVis;

	// Main
	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CSlider   TriggerDelay;

	// Main
	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CCheckBox WeaponMainRecoil;
	CCheckBox WeaponMainPSilent;
	CSlider   WeaponMainInacc;
	CComboBox WeaponMainHitbox;

	// Pistol
	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CCheckBox WeaponPistRecoil;
	CCheckBox WeaponPistPSilent;
	CSlider   WeaponPistInacc;
	CComboBox WeaponPistHitbox;

	// Sniper
	CCheckBox WeaponSnipEnable;
	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CCheckBox WeaponSnipRecoil;
	CCheckBox WeaponSnipPSilent;
	CSlider   WeaponSnipInacc;
	CComboBox WeaponSnipHitbox;

	//More
	CGroupBox AimMoreGroup;
	CCheckBox FoVRadius;
	CCheckBox WeaponConfig;
	CComboBox WeaponConf;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Options Settings
	CGroupBox OptionsGroup;
	CCheckBox OptionsBox;
	CCheckBox OptionsName;
	CCheckBox  OptionsGlow;
	CComboBox OptionsHealth;
	CCheckBox OptionsArmor;
	CCheckBox OptionsWeapon;
	CCheckBox OptionsInfo;
	CCheckBox OptionsHelmet;
	CCheckBox OptionsKit;
	CCheckBox OptionsDefuse;
	//CCheckBox OptionsGlow;
	CComboBox OptionsChams;
	CCheckBox OptionsSkeleton;
	CCheckBox OptionsVisibleOnly;
	CCheckBox OptionsAimSpot;
	CCheckBox OptionsCompRank;

	

	// Filters Settings
	CGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox FiltersPlayers;
	CCheckBox FiltersEnemiesOnly;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersChickens;
	CCheckBox FiltersC4;

	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherCrosshair;
	CComboBox OtherRecoilCrosshair;
	CCheckBox OtherHitmarker;
	CCheckBox OtherRadar;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherNoSky; 
	CCheckBox OtherNoFlash; 
	CSlider   OtherNoFlashVal;
	CCheckBox NightMode;
	CComboBox AmbientSkybox;
	CComboBox OtherStrafeDir;;
	CSlider AmbientExposure;
	CSlider AmbientRed;
	CSlider AmbientGreen;
	CSlider AmbientBlue;
	CCheckBox OtherNoSmoke;
	CCheckBox OtherAutoAccept;
	CCheckBox OtherAsusWalls;
	CComboBox OtherNoHands;
	CSlider OtherViewmodelFOV;
	CSlider OtherFOV;
	

};

class CMiscTab : public CTab
{
public:
	void Setup();

	// Knife Changer
	CGroupBox KnifeGroup;
	CCheckBox KnifeEnable;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;
	CButton   KnifeApply;

	CComboBox FakeLagTypes;
	// Other Settings
	CGroupBox OtherGroup;
	CCheckBox OtherAutoJump;
	CCheckBox OtherEdgeJump;
	CComboBox OtherAutoStrafe;
	CCheckBox OtherSafeMode;
	CComboBox OtherChatSpam;
	CCheckBox OtherTeamChat;
	CCheckBox OtherCircleStrafe;
	CComboBox OtherStrafeDir;;
	CKeyBind OtherCircleStrafeKey;
	CSlider	  OtherChatDelay;
	CCheckBox othercirclestrafe;
	CCheckBox OtherAutoAccept;
	CKeyBind  OtherAirStuck;
	CKeyBind  OtherLagSwitch;
	CCheckBox OtherSpectators;
	CCheckBox OtherThirdperson;
	CCheckBox OtherSkinChanger;
	CCheckBox OtherWatermark;
	CCheckBox OtherAutoCounterStafe;
	CKeyBind  OtherAutoCounterStafeKey;
	CCheckBox OtherNoScopeBorder;
	//CCheckBox OtherAutoAccept;
	CCheckBox OtherWalkbot;
	CComboBox OtherClantag;
	CCheckBox DisableAll;

	// Fake Lag Settings
	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable;
	CSlider   FakeLagChoke;
	CSlider	  FakeLagSend;
	CCheckBox ChokeRandomize;
	CCheckBox SendRandomize;
	//CCheckBox FakeLagWhileShooting;

	// Teleport shit cause we're cool
	CGroupBox TeleportGroup;
	CCheckBox TeleportEnable;
	CKeyBind  TeleportKey;
};

class CColorTab : public CTab
{
public:
	void Setup();

	//Groups
	CGroupBox ColorsGroup;
	CGroupBox Wiregroup;
	CSlider CTColorVisR;
	CSlider CTColorVisG;
	CSlider CTColorVisB;

	CSlider CTColorNoVisR;
	CSlider CTColorNoVisG;
	CSlider CTColorNoVisB;

	//CLabel ColorSpacer;

	CSlider TColorVisR;
	CSlider TColorVisG;
	CSlider TColorVisB;

	CSlider TColorNoVisR;
	CSlider TColorNoVisG;
	CSlider TColorNoVisB;

	// Wireframe colors
	CSlider WireframeColorR;
	CSlider WireframeColorG;
	CSlider WireframeColorB;


	//Menu Colors

	
	CSlider  MenuBar1R;
	CSlider  MenuBar1G;
	CSlider  MenuBar1B;
	CSlider  MenuBar2R;
	CSlider  MenuBar2G;
	CSlider  MenuBar2B;
	//Inner
	CSlider  MenuInnerR;
	CSlider  MenuInnerG;
	CSlider  MenuInnerB;
	CSlider  MenuOpacity;

};

class CSettingsTab : public CTab
{
public:
	void Setup();
	CGroupBox ButtonGroup;
	CButton SaveButton;
	CButton LoadButton;
	CLabel Cfgtext;
	//Options
	CComboBox SetNr;
	CButton Unload;
	

	
};
class ApocalypseWindow : public CWindow
{
public:
	void Setup();

	CRageBotTab RageBotTab;
	CLegitBotTab LegitBotTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;
	CColorTab ColorTab;
	CSettingsTab SettingsTab;
	




	CButton SaveButton;
	CButton LoadButton;
	CButton SaveButton1;
	CButton LoadButton1;
	CButton SaveButton2;
	CButton LoadButton2;
	CButton SaveButton3;
	CButton LoadButton3;
	CButton UnloadButton;
};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();

	extern ApocalypseWindow Window;
};