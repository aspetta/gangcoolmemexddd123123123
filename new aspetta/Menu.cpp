/*
Rest In Peace ApocalypseCheats
*/

#include "Menu.h"
#include "Controls.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "CRC32.h"
#include <string>
#include "ItemDefinitions.hpp"
#include "Hooks.h"
#include "Hacks.h"
#include "Chams.h"
#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "MiscHacks.h"
#include "CRC32.h"
#include "Resolver.h"


#define WINDOW_WIDTH 930
#define WINDOW_HEIGHT 590

ApocalypseWindow Menu::Window;
void Unloadbk()
{
	DoUnload = true;
}

void SaveCallbk()
{
	switch (Menu::Window.SettingsTab.SetNr.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "legit.xml");
		break;
	case 1:
		GUI.SaveWindowState(&Menu::Window, "semirage.xml");
		break;
	case 2:
		GUI.SaveWindowState(&Menu::Window, "rage.xml");
		break;
	case 3:
		GUI.SaveWindowState(&Menu::Window, "custom.xml");
		break;
	case 4:
		GUI.SaveWindowState(&Menu::Window, "custom1.xml");
		break;
	}

}

void LoadCallbk()
{
	switch (Menu::Window.SettingsTab.SetNr.GetIndex())
	{
	case 0:
		GUI.LoadWindowState("legit.xml", &Menu::Window);
		break;
	case 1:
		GUI.LoadWindowState("semirage.xml", &Menu::Window);
		break;
	case 2:
		GUI.LoadWindowState("rage.xml", &Menu::Window);
		break;
	case 3:
		GUI.LoadWindowState("custom.xml", &Menu::Window);
		break;
	case 4:
		GUI.LoadWindowState("custom2.xml", &Menu::Window);
		break;
	}
}

void UnLoadCallbk()
{
	DoUnload = true;
}


void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");

}/*void SetAKCB()
{
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	IClientEntity* WeaponEnt = Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	CBaseCombatWeapon* Weapon = (CBaseCombatWeapon*)WeaponEnt;
	*Weapon->FallbackPaintKit() = 524;

}*/
RECT dab;
void ApocalypseWindow::Setup()
{
	SetPosition(50, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("Aspetta | Dev build");

	RegisterTab(&RageBotTab);
	RegisterTab(&LegitBotTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);
	RegisterTab(&ColorTab);
	RegisterTab(&SettingsTab);


	dab = GetClientArea();
	RECT Client = GetClientArea();
	Client.bottom -= 29;

	RageBotTab.Setup();
	LegitBotTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();
	ColorTab.Setup();
	SettingsTab.Setup();

	
}

void CRageBotTab::Setup()
{
	
	SetTitle("a");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Aimbot

	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(376, 262);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl(this, &AimbotEnable, "Enable");

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl(this, &AimbotAutoFire, "Automatic Shoot");

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(180.f); //
	AimbotGroup.PlaceLabledControl(this, &AimbotFov, "Maximum Fov");

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup.PlaceLabledControl(this, &AimbotSilentAim, "Silent Aim");

	//AimbotPerfectSilentAim.SetFileId("aim_psilent");
	//AimbotGroup.PlaceLabledControl(this, &AimbotPerfectSilentAim, "Perfect Silent");

	AimbotAutoPistol.SetFileId("aim_autopistol");
	AimbotGroup.PlaceLabledControl(this, &AimbotAutoPistol, "Automatic Pistol");

	//AimbotAimStep.SetFileId("aim_aimstep");
	//AimbotGroup.PlaceLabledControl(this, &AimbotAimStep, "Aim Step");

	AimbotAutoRevolver.SetFileId("aim_autorevo");
	AimbotGroup.PlaceLabledControl(this, &AimbotAutoRevolver, "Auto Revolver");

	AutoAwpBody.SetFileId("aim_awpbody");
	AimbotGroup.PlaceLabledControl(this, &AutoAwpBody, "Auto Awp Body");

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl(this, &AimbotKeyPress, "On Key Press");

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl(this, &AimbotKeyBind, "Key");

//	AimbotStopKey.SetFileId("aim_stop");
//	AimbotGroup.PlaceLabledControl(this, &AimbotStopKey, "Stop Aim");

#pragma endregion Aimbot Controls Get Setup in here


#pragma region AntiAim
	AntiAimGroup.SetPosition(408, 48); //408, 307
	AntiAimGroup.SetText("Anti Aim");
	AntiAimGroup.SetSize(360, 240);
	RegisterControl(&AntiAimGroup);

	AntiAimEnable.SetFileId("aa_enable");
	AntiAimGroup.PlaceLabledControl(this, &AntiAimEnable, "Enable");

	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("None");
	AntiAimPitch.AddItem("Emotion");
	AntiAimPitch.AddItem("Half Down");
	AntiAimPitch.AddItem("Jitter");
	AntiAimPitch.AddItem("Static");
	AntiAimPitch.AddItem("Fake Down");
	AntiAimPitch.AddItem("Lisp Down"); //lispy w 2017 bez lisp fixa kurwa najlepsze polecam Kamilek 
	AntiAimPitch.AddItem("Lisp Up");
	AntiAimGroup.PlaceLabledControl(this, &AntiAimPitch, "Pitch");

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("None");
	AntiAimYaw.AddItem("Fake Edge");//1
	AntiAimYaw.AddItem("Fake Sideways");//2
	AntiAimYaw.AddItem("Fake Static");//3
	AntiAimYaw.AddItem("T Fake");//4
	AntiAimYaw.AddItem("Fake Jitter");//5
	AntiAimYaw.AddItem("Jitter");//6
	AntiAimYaw.AddItem("L Jitter");//7
	AntiAimYaw.AddItem("Back Jitter");//8
	AntiAimYaw.AddItem("Backwards");// 16
	AntiAimYaw.AddItem("Fake Fast Spin"); // 17
	AntiAimYaw.AddItem("Fake Random"); // 18
	AntiAimGroup.PlaceLabledControl(this, &AntiAimYaw, "Yaw");

	Fakeyaw.SetFileId("aafake_yaw");
	Fakeyaw.AddItem("None");
	Fakeyaw.AddItem("T Fake");
	Fakeyaw.AddItem("Fake Back");
	Fakeyaw.AddItem("Fake LBY");
	Fakeyaw.AddItem("Fake Jitter");
	Fakeyaw.AddItem("LBY Jitter");
	Fakeyaw.AddItem("Fake Spin");
	Fakeyaw.AddItem("LBY Backward");
	Fakeyaw.AddItem("LBY");
	Fakeyaw.AddItem("Fake Edge");
	AntiAimGroup.PlaceLabledControl(this, &Fakeyaw, "Fake Yaw");

	AntiAimPitchoffset.SetFileId("aa_offset");
	AntiAimPitchoffset.SetBoundaries(0, 180);
	AntiAimPitchoffset.SetValue(0);
	AntiAimGroup.PlaceLabledControl(this, &AntiAimPitchoffset, "Custom Pitch");

	AntiAimOffset.SetFileId("aa_offset");
	AntiAimOffset.SetBoundaries(0, 360);
	AntiAimOffset.SetValue(0);
	AntiAimGroup.PlaceLabledControl(this, &AntiAimOffset, "Custom Yaw");

	AntiAimKnife.SetFileId("aa_knife");
	AntiAimGroup.PlaceLabledControl(this, &AntiAimKnife, "AntiAim with Knife");

	AntiAimTarget.SetFileId("aa_target");
	AntiAimGroup.PlaceLabledControl(this, &AntiAimTarget, "At target");

#pragma endregion  AntiAim controls get setup in here

#pragma region Target
	TargetGroup.SetPosition(16, 334);
	TargetGroup.SetText("Target");
	TargetGroup.SetSize(376, 191);
	RegisterControl(&TargetGroup);

	TargetSelection.SetFileId("tgt_selection");
	TargetSelection.AddItem("Cycle");
	TargetSelection.AddItem("Distance");
	TargetSelection.AddItem("Health");
	TargetGroup.PlaceLabledControl(this, &TargetSelection, "Target Selection");

	TargetFriendlyFire.SetFileId("tgt_friendlyfire");
	TargetGroup.PlaceLabledControl(this, &TargetFriendlyFire, "Friendly Fire");

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("Head");
	TargetHitbox.AddItem("Neck");
	TargetHitbox.AddItem("Chest");
	TargetHitbox.AddItem("Stomach");
	TargetHitbox.AddItem("Pelvis");
	TargetHitbox.AddItem("Shins");
	TargetGroup.PlaceLabledControl(this, &TargetHitbox, "Target Hitbox");

	TargetHitscan.SetFileId("tgt_hitscan");
	TargetHitscan.AddItem("Off"); //0
	TargetHitscan.AddItem("Fast"); // 1
	TargetHitscan.AddItem("Medium"); // 2
	TargetHitscan.AddItem("Baim"); // 3
	TargetHitscan.AddItem("All");
	TargetGroup.PlaceLabledControl(this, &TargetHitscan, "Hitscan");

	PreferBodyAim.SetFileId("acc_bodyaim");
	PreferBodyAim.AddItem("Off");
	PreferBodyAim.AddItem("Unresolved");//baims only when resolver off (not done at all)
	PreferBodyAim.AddItem("Always");//Baims everytime even with fast hitscan or hitbox head only
	TargetGroup.PlaceLabledControl(this, &PreferBodyAim, "Prefer Body Aim");

	//TargetMultipoint.SetFileId("tgt_multipoint");
//	TargetGroup.PlaceLabledControl(this, &TargetMultipoint, "Multipoint");

	TargetPointscale.SetFileId("tgt_pointscale");
	TargetPointscale.SetBoundaries(0.f, 10.f);
	TargetPointscale.SetValue(5.f);
	TargetGroup.PlaceLabledControl(this, &TargetPointscale, "Aim Height");
#pragma endregion Targetting controls 

#pragma region Accuracy
	AccuracyGroup.SetPosition(408, 310);
	AccuracyGroup.SetText("Accuracy");
	AccuracyGroup.SetSize(360, 216); //280
	RegisterControl(&AccuracyGroup);

	AccuracyRecoil.SetFileId("acc_norecoil"); 
	AccuracyGroup.PlaceLabledControl(this, &AccuracyRecoil, "Remove recoil");

	AccuracyAutoWall.SetFileId("acc_awall");
	AccuracyGroup.PlaceLabledControl(this, &AccuracyAutoWall, "Automatic penetration"); 

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(1.f, 100.f);
	AccuracyMinimumDamage.SetValue(1.f);
	AccuracyGroup.PlaceLabledControl(this, &AccuracyMinimumDamage, "Automatic penetration Damage");

	AccuracyAutoStop.SetFileId("acc_stop");
	AccuracyGroup.PlaceLabledControl(this, &AccuracyAutoStop, "Automatic Stop");

	AccuracyAutoCrouch.SetFileId("acc_crouch");
	AccuracyGroup.PlaceLabledControl(this, &AccuracyAutoCrouch, "Automatic Duck");

	AccuracyAutoScope.SetFileId("acc_scope");
	AccuracyGroup.PlaceLabledControl(this, &AccuracyAutoScope, "Automatic scope");

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(10);
	AccuracyGroup.PlaceLabledControl(this, &AccuracyHitchance, "Hit Chance");

	
	//AntiAimTarget.SetFileId("aa_nospread");
	//AccuracyGroup.PlaceLabledControl(this, &AntiAimNoSpread, "No Spread");

	AccuracyResolver.SetFileId("accuracy_reso");
	AccuracyResolver.AddItem("Off");
	AccuracyResolver.AddItem("Advanced");
	//AccuracyResolver.AddItem("Yaw Resolver");
	AccuracyResolver.AddItem("Brute Force");
	AccuracyResolver.AddItem("pYawResolver");
	AccuracyResolver.AddItem("Pitch");
	AccuracyGroup.PlaceLabledControl(this, &AccuracyResolver, "Resolver");


	#pragma endregion  Accuracy controls get Setup in here
}

void CLegitBotTab::Setup()
{
	SetTitle("b");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Aimbot
	AimbotGroup.SetPosition(16, 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(240, 210);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl(this, &AimbotEnable, "Enable");

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl(this, &AimbotAutoFire, "Auto Shoot");

	AimbotFriendlyFire.SetFileId("aim_friendfire");
	AimbotGroup.PlaceLabledControl(this, &AimbotFriendlyFire, "Friendly Shoot");

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl(this, &AimbotKeyPress, "On Key");

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl(this, &AimbotKeyBind, "Key Bind");
	
	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl(this, &AimbotAutoPistol, "Auto Pistol");

#pragma endregion Aimbot shit

#pragma region Triggerbot
	TriggerGroup.SetPosition(272, 48);
	TriggerGroup.SetText("Triggerbot");
	TriggerGroup.SetSize(240, 210);
	RegisterControl(&TriggerGroup);

	TriggerEnable.SetFileId("trig_enable");
	TriggerGroup.PlaceLabledControl(this, &TriggerEnable, "Enable");

	TriggerKeyPress.SetFileId("trig_onkey");
	TriggerGroup.PlaceLabledControl(this, &TriggerKeyPress, "On Key Press");

	TriggerKeyBind.SetFileId("trig_key");
	TriggerGroup.PlaceLabledControl(this, &TriggerKeyBind, "Key Bind");

	TriggerDelay.SetFileId("trig_time");
	TriggerDelay.SetBoundaries(1.f, 1000.f);
	TriggerDelay.SetValue(1.f);
	TriggerGroup.PlaceLabledControl(this, &TriggerDelay, "Delay (ms)");
#pragma endregion Triggerbot stuff

#pragma region Main Weapon
	WeaponMainGroup.SetPosition(16, 274);
	WeaponMainGroup.SetText("Rifles");
	WeaponMainGroup.SetSize(240, 210);
	RegisterControl(&WeaponMainGroup);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.1f, 100.f); 
	WeaponMainSpeed.SetValue(1.0f);
	WeaponMainGroup.PlaceLabledControl(this, &WeaponMainSpeed, "Smooth");

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.f, 30.f);
	WeaponMainFoV.SetValue(5.f);
	WeaponMainGroup.PlaceLabledControl(this, &WeaponMainFoV, "Fov");

	WeaponMainRecoil.SetFileId("main_recoil");
	WeaponMainGroup.PlaceLabledControl(this, &WeaponMainRecoil, "Recoil");

	WeaponMainPSilent.SetFileId("main_psilent");
	WeaponMainGroup.PlaceLabledControl(this, &WeaponMainPSilent, "Silent");

	WeaponMainInacc.SetFileId("main_inacc");
	WeaponMainInacc.SetBoundaries(0.f, 15.f);
	WeaponMainGroup.PlaceLabledControl(this, &WeaponMainInacc, "Inaccuracy");

	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("Head");
	WeaponMainHitbox.AddItem("Neck");
	WeaponMainHitbox.AddItem("Chest");
	WeaponMainHitbox.AddItem("Stomach");
	WeaponMainGroup.PlaceLabledControl(this, &WeaponMainHitbox, "Hitbox");
#pragma endregion

#pragma region Pistols
	WeaponPistGroup.SetPosition(272, 274);
	WeaponPistGroup.SetText("Pistols");
	WeaponPistGroup.SetSize(240, 210);
	RegisterControl(&WeaponPistGroup);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 100.f);
	WeaponPistSpeed.SetValue(1.0f);
	WeaponPistGroup.PlaceLabledControl(this, &WeaponPistSpeed, "Smooth");

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 30.f);
	WeaponPistFoV.SetValue(0.78f);
	WeaponPistGroup.PlaceLabledControl(this, &WeaponPistFoV, "Fov");

	WeaponPistRecoil.SetFileId("pist_recoil");
	WeaponPistGroup.PlaceLabledControl(this, &WeaponPistRecoil, "Recoil");

	WeaponPistPSilent.SetFileId("pist_psilent");
	WeaponPistGroup.PlaceLabledControl(this, &WeaponPistPSilent, "Silent");

	WeaponPistInacc.SetFileId("pist_inacc");
	WeaponPistInacc.SetBoundaries(0.f, 15.f);
	WeaponPistInacc.SetValue(0.f);
	WeaponPistGroup.PlaceLabledControl(this, &WeaponPistInacc, "Inaccuracy");

	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	WeaponPistGroup.PlaceLabledControl(this, &WeaponPistHitbox, "Hitbox");
#pragma endregion

#pragma region Snipers
	WeaponSnipGroup.SetPosition(528, 274);
	WeaponSnipGroup.SetText("Snipers");
	WeaponSnipGroup.SetSize(240, 210);
	RegisterControl(&WeaponSnipGroup);

	

	WeaponSnipSpeed.SetFileId("wconf_speed_ak");
	WeaponSnipSpeed.SetBoundaries(0.1f, 100.f);
	WeaponSnipSpeed.SetValue(1.0f);
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipSpeed, "Smooth");

	WeaponSnipFoV.SetFileId("wconf_fov_ak");
	WeaponSnipFoV.SetBoundaries(0.1f, 30.f);
	WeaponSnipFoV.SetValue(5.f);
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipFoV, "Fov");

	WeaponSnipRecoil.SetFileId("wconf_recoil_ak");
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipRecoil, "Recoil");

	WeaponSnipPSilent.SetFileId("wconf_psilent_ak");
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipPSilent, "Silent");

	WeaponSnipInacc.SetFileId("wconf_inacc_ak");
	WeaponSnipInacc.SetBoundaries(0.f, 15.f);
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipInacc, "Inaccuracy");

	WeaponSnipHitbox.SetFileId("wconf_hitbox_ak");
	WeaponSnipHitbox.AddItem("Head");
	WeaponSnipHitbox.AddItem("Neck");
	WeaponSnipHitbox.AddItem("Chest");
	WeaponSnipHitbox.AddItem("Stomach");
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipHitbox, "Hitbox");

	WeaponSnipEnable.SetFileId("wconf_enable_ak");
	WeaponSnipGroup.PlaceLabledControl(this, &WeaponSnipEnable, "Aimbot Unscoped");
#pragma endregion

#pragma More
	AimMoreGroup.SetPosition(528, 48);
	AimMoreGroup.SetText("More");
	AimMoreGroup.SetSize(240, 210);
	RegisterControl(&AimMoreGroup);

	FoVRadius.SetFileId("fov_aim");
	AimMoreGroup.PlaceLabledControl(this, &FoVRadius, "Fov Radius");

	WeaponConfig.SetFileId("wconf_toggle");
	AimMoreGroup.PlaceLabledControl(this, &WeaponConfig, "Weapon Configs"); //tutaj niby sa skiny tsa? nie wyjebalem bo sie wkurwilem, mozesz dodac masz dingo pobrane?
	WeaponConf.SetFileId("wconf_weapon");
	WeaponConf.AddItem("AK-47");
	WeaponConf.AddItem("AUG");
	WeaponConf.AddItem("AWP");
	WeaponConf.AddItem("CZ75-Auto");
	WeaponConf.AddItem("Desert Eagle");
	WeaponConf.AddItem("Dual Beretas");
	WeaponConf.AddItem("Famas");
	WeaponConf.AddItem("Five-SeveN");
	WeaponConf.AddItem("Galil AR");
	WeaponConf.AddItem("G3SG1");
	WeaponConf.AddItem("Glock-18");
	WeaponConf.AddItem("M249");
	WeaponConf.AddItem("M4A1-S");
	WeaponConf.AddItem("M4A4");
	WeaponConf.AddItem("MAC-10");
	WeaponConf.AddItem("MAG-7");
	WeaponConf.AddItem("MP7");
	WeaponConf.AddItem("MP9");
	WeaponConf.AddItem("Negev");
	WeaponConf.AddItem("Nova");
	WeaponConf.AddItem("P2000");
	WeaponConf.AddItem("P250");
	WeaponConf.AddItem("P90");
	WeaponConf.AddItem("PP-Bizon");
	WeaponConf.AddItem("R8 Revolver");
	WeaponConf.AddItem("Sawed-Off");
	WeaponConf.AddItem("SCAR-20");
	WeaponConf.AddItem("SSG 08");
	WeaponConf.AddItem("SG 553");
	WeaponConf.AddItem("TEC-9");
	WeaponConf.AddItem("UMP-45");
	WeaponConf.AddItem("USP-S");
	WeaponConf.AddItem("XM-1014");
	AimMoreGroup.PlaceLabledControl(this, &WeaponConf, "Weapon");


#pragma endregion
}

void CVisualTab::Setup()
{
	SetTitle("c");

	ActiveLabel.SetPosition(16, 16);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetPosition(66, 16);
	RegisterControl(&Active);

#pragma region Options
	OptionsGroup.SetText("Options");
	OptionsGroup.SetPosition(16, 48);
	OptionsGroup.SetSize(193, 430);
	RegisterControl(&OptionsGroup);

	OptionsBox.SetFileId("opt_box");
	OptionsGroup.PlaceLabledControl(this, &OptionsBox, "Box");

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl(this, &OptionsName, "Name");

	OptionsHealth.SetFileId("opt_hp");
	OptionsHealth.AddItem("Off");
	OptionsHealth.AddItem("Health1");
	OptionsHealth.AddItem("Health2");
	OptionsGroup.PlaceLabledControl(this, &OptionsHealth, "Health");

	OptionsArmor.SetFileId("opt_armor");
	OptionsGroup.PlaceLabledControl(this, &OptionsArmor, "Armor");

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl(this, &OptionsWeapon, "Weapon");
	
	
	OptionsChams.SetFileId("opt_chams");
	OptionsChams.AddItem("Off");
	OptionsChams.AddItem("Normal");
	OptionsChams.AddItem("Flat");
	OptionsGroup.PlaceLabledControl(this, &OptionsChams, "Chams");

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl(this, &OptionsSkeleton, "Skeleton");

	OptionsVisibleOnly.SetFileId("opt_vonly");
	OptionsGroup.PlaceLabledControl(this, &OptionsVisibleOnly, "Visible Only");

	OptionsAimSpot.SetFileId("opt_aimspot");
	OptionsGroup.PlaceLabledControl(this, &OptionsAimSpot, "Head Cross");
	
	OptionsCompRank.SetFileId("opt_comprank");
	OptionsGroup.PlaceLabledControl(this, &OptionsCompRank, "Player Ranks");
	
	OtherAutoAccept.SetFileId("ort_OtherAutoAccept");
	OtherAutoAccept.SetState(true);
	OptionsGroup.PlaceLabledControl(this, &OtherAutoAccept, "Auto Accept");


	
#pragma endregion Setting up the Options controls

#pragma region Filters
	FiltersGroup.SetText("Filters");
	FiltersGroup.SetPosition(225, 48);
	FiltersGroup.SetSize(193, 430);
	RegisterControl(&FiltersGroup);

	FiltersAll.SetFileId("ftr_all");
	FiltersGroup.PlaceLabledControl(this, &FiltersAll, "All");

	FiltersPlayers.SetFileId("ftr_players");
	FiltersGroup.PlaceLabledControl(this, &FiltersPlayers, "Players");

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	FiltersGroup.PlaceLabledControl(this, &FiltersEnemiesOnly, "Enemies Only");

	FiltersWeapons.SetFileId("ftr_weaps");
	FiltersGroup.PlaceLabledControl(this, &FiltersWeapons, "Weapons");

	//FiltersChickens.SetFileId("ftr_chickens");
	//FiltersGroup.PlaceLabledControl("Chickens", this, &FiltersChickens);

	FiltersC4.SetFileId("ftr_c4");
	FiltersGroup.PlaceLabledControl(this, &FiltersC4, "C4");
#pragma endregion Setting up the Filters controls

#pragma region Other
	OtherGroup.SetText("Other");
	OtherGroup.SetPosition(434, 48);
	OtherGroup.SetSize(334, 430);
	RegisterControl(&OtherGroup);

	OtherCrosshair.SetFileId("otr_xhair");
	OtherGroup.PlaceLabledControl(this, &OtherCrosshair, "Crosshair");

	OtherRecoilCrosshair.SetFileId("otr_recoilhair");
	OtherRecoilCrosshair.AddItem("Off");
	OtherRecoilCrosshair.AddItem("Recoil Position");
	OtherRecoilCrosshair.AddItem("Radius");
	OtherGroup.PlaceLabledControl(this, &OtherRecoilCrosshair, "Recoil Crosshair");

	OtherRadar.SetFileId("otr_radar");
	OtherGroup.PlaceLabledControl(this, &OtherRadar, "Radar");

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl(this, &OtherNoVisualRecoil, "No Visual Recoil");

	OtherNoFlash.SetFileId("otr_noflash");
	//OtherNoFlas.SetBoundaries(0.f, 90.f);
	//OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl(this, &OtherNoFlash, "No Flash Enable");

	OtherNoFlashVal.SetFileId("otr_noflashval");
	OtherNoFlashVal.SetBoundaries(0,255);
	OtherViewmodelFOV.SetValue(200);
	OtherGroup.PlaceLabledControl(this, &OtherNoFlashVal, "Max Flash");

	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("Off");
	OtherNoHands.AddItem("None");
	OtherNoHands.AddItem("Transparent");
	OtherNoHands.AddItem("Wireframe");
	OtherNoHands.AddItem("Chams");
	//OtherNoHands.AddItem("Rainbow");
	OtherGroup.PlaceLabledControl(this, &OtherNoHands, "Hands");

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 90.f);
	OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl(this, &OtherViewmodelFOV, "Viewmodel Fov Changer");

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	OtherGroup.PlaceLabledControl(this, &OtherFOV, "Field of View Changer");


	
#pragma endregion Setting up the Other controls
}

void CMiscTab::Setup()
{
	SetTitle("d");

#pragma region Knife
	KnifeGroup.SetPosition(16, 16);
	KnifeGroup.SetSize(360, 126);
	KnifeGroup.SetText("Knife Changer");
	RegisterControl(&KnifeGroup);

	KnifeEnable.SetFileId("knife_enable");
	KnifeGroup.PlaceLabledControl(this, &KnifeEnable, "Enable");

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Falchion Knife");
    KnifeModel.AddItem("Bowie Knife");
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Shadow Daggers");
	KnifeGroup.PlaceLabledControl(this, &KnifeModel, "Knife");

	KnifeSkin.SetFileId("knife_skin");
	KnifeSkin.AddItem("Doppler Sapphire");
	KnifeSkin.AddItem("Doppler Ruby");
	KnifeSkin.AddItem("Tiger Tooth");
	KnifeSkin.AddItem("Lore");
	KnifeSkin.AddItem("Forest DDPAT");
	KnifeSkin.AddItem("Crimson Web");
	KnifeSkin.AddItem("Slaughter");
	KnifeSkin.AddItem("Vanilla");
	KnifeSkin.AddItem("Fade");
	KnifeSkin.AddItem("Night");
	KnifeSkin.AddItem("Blue Steel");
	KnifeSkin.AddItem("Stained");
	KnifeSkin.AddItem("Case Hardended");
	KnifeSkin.AddItem("Safari Mesh");
	KnifeSkin.AddItem("Boreal Forest");
	KnifeSkin.AddItem("Ultaviolet");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Romania's Flag");
	

	KnifeGroup.PlaceLabledControl(this, &KnifeSkin, "Skin");

	KnifeApply.SetText("Apply Knife");
	KnifeApply.SetCallback(KnifeApplyCallbk);
	KnifeGroup.PlaceLabledControl(this, &KnifeApply, "");

#pragma endregion

#pragma region Other
	OtherGroup.SetPosition(408, 16);
	OtherGroup.SetSize(360, 440);
	OtherGroup.SetText("Other");
	RegisterControl(&OtherGroup);

	OtherAutoJump.SetFileId("otr_autojump");
	OtherGroup.PlaceLabledControl(this, &OtherAutoJump, "Bhop");

	OtherEdgeJump.SetFileId("otr_edgejump");
	OtherGroup.PlaceLabledControl(this, &OtherEdgeJump, "Edge Jump");


	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherAutoStrafe.AddItem("Off");
	OtherAutoStrafe.AddItem("Legit");
	OtherAutoStrafe.AddItem("Rage");
	OtherGroup.PlaceLabledControl(this, &OtherAutoStrafe, "Auto Strafer");

	//OtherAutoCounterStafe.SetFileId("otr_autocs");
	//OtherGroup.PlaceLabledControl(this, &OtherAutoCounterStafe, "Auto Counter-Stafer Enable");

	//OtherAutoCounterStafeKey.SetFileId("otr_autocs_key");
	//OtherGroup.PlaceLabledControl(this, &OtherAutoCounterStafeKey, "Auto Counter-Stafer Key");

	//OtherCircleStrafe.SetFileId("otr_circlestrafe");
	//OtherGroup.PlaceLabledControl(this, &OtherCircleStrafe, "Circle Strafe");

	//OtherCircleStrafeKey.SetFileId("otr_circlekey");
	//OtherGroup.PlaceLabledControl(this, &OtherCircleStrafeKey, "Circle Strafe Key");

	//othercirclestrafe.SetFileId("circlestraferkurwa");
	//OtherGroup.PlaceLabledControl(this, &othercirclestrafe, "Cricle Strafer Mouse2");

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	OtherGroup.PlaceLabledControl(this, &OtherSafeMode, "Safe Mode");

	OtherChatSpam.SetFileId("otr_spam");
	OtherChatSpam.AddItem("Off");
	OtherChatSpam.AddItem("Namestealer");
	OtherChatSpam.AddItem("Jihad.win - CS");
	OtherChatSpam.AddItem("Jihad.win - NS");
	//OtherChatSpam.AddItem("Rekt");
	//OtherChatSpam.AddItem("Aimware - CS");
	//OtherChatSpam.AddItem("Aimware - NS");
	OtherGroup.PlaceLabledControl(this, &OtherChatSpam, "Chat Spam");

	//OtherAutoAccept.SetFileId("ort_OtherAutoAccept");
	//OtherAutoAccept.SetState(true);
	//OtherGroup.PlaceLabledControl(this, &OtherAutoAccept, "AutoAccept");

	OtherClantag.SetFileId("otr_spam");
	OtherClantag.AddItem("Off");
	OtherClantag.AddItem("Jihad.win");
	OtherClantag.AddItem("'SlideShow'");
	OtherClantag.AddItem("None");
	OtherClantag.AddItem("Valve");
	OtherGroup.PlaceLabledControl(this, &OtherClantag, "Custom Clantag");

	OtherTeamChat.SetFileId("otr_teamchat");
	OtherGroup.PlaceLabledControl(this, &OtherTeamChat, "Team Chat Only");

	OtherChatDelay.SetFileId("otr_chatdelay");
	OtherChatDelay.SetBoundaries(0.1, 3.0);
	OtherChatDelay.SetValue(0.5);
	OtherGroup.PlaceLabledControl(this, &OtherChatDelay, "Spam Delay");

	OtherAirStuck.SetFileId("otr_astuck");
	OtherGroup.PlaceLabledControl(this, &OtherAirStuck, "Air Stuck");

	OtherSpectators.SetFileId("otr_speclist");
	OtherGroup.PlaceLabledControl(this, &OtherSpectators, "Spectators List");

	OtherThirdperson.SetFileId("aa_thirdpsr");
	OtherGroup.PlaceLabledControl(this, &OtherThirdperson, "Thirdperson");

	OtherNoScopeBorder.SetFileId("otr_noscopebrd");
	OtherGroup.PlaceLabledControl(this, &OtherNoScopeBorder, "No Scope");

	//OtherSpectators.SetFileId("otr_skin");
	//OtherGroup.PlaceLabledControl(this, &OtherSkinChanger, "SkinChanger");

	bool wmon;

	
  //  OtherWatermark.SetFileId("otr_watermark");
	
//	OtherGroup.PlaceLabledControl(this, &OtherWatermark, "Watermark");

	//DisableAll.SetFileId("otr_disableall");
	//OtherGroup.PlaceLabledControl("Disable All", this, &DisableAll);

#pragma endregion other random options

#pragma region FakeLag
	FakeLagGroup.SetPosition(16, 160);
	FakeLagGroup.SetSize(360, 170);
	FakeLagGroup.SetText("Fake Lag");
	RegisterControl(&FakeLagGroup);

	FakeLagEnable.SetFileId("fakelag_enable");
	FakeLagGroup.PlaceLabledControl(this, &FakeLagEnable, "Fake Lag");

	FakeLagChoke.SetFileId("fakelag_choke");
	FakeLagChoke.SetBoundaries(0, 16);
	FakeLagChoke.SetValue(0);
	FakeLagGroup.PlaceLabledControl(this, &FakeLagChoke, "Choke Factor");

	FakeLagSend.SetFileId("fakelag_send");
	FakeLagSend.SetBoundaries(0, 16);
	FakeLagSend.SetValue(0);
	FakeLagGroup.PlaceLabledControl(this, &FakeLagSend, "Send Factor");

	//ChokeRandomize.SetFileId("choke_random");
	//FakeLagGroup.PlaceLabledControl(this, &ChokeRandomize, "Randomize Choke");

	//SendRandomize.SetFileId("send_random");
	//FakeLagGroup.PlaceLabledControl(this, &SendRandomize, "Randomize Send");

	//FakeLagTypes.SetFileId("fakelag_type");
	//FakeLagTypes.AddItem("Normal");
	//FakeLagTypes.AddItem("Adaptive");
	//FakeLagTypes.AddItem("Switch");
	//FakeLagTypes.AddItem("Random");
	//FakeLagTypes.AddItem("Cycle");
	//FakeLagTypes.AddItem("Revolve");
	//FakeLagGroup.PlaceLabledControl(this, &FakeLagTypes, "FakeLag Mode");

#pragma endregion fakelag shit
/*
#pragma region Teleport
	TeleportGroup.SetPosition(16, 316);
	TeleportGroup.SetSize(360, 75);
	TeleportGroup.SetText("Teleport");
	RegisterControl(&TeleportGroup);

	TeleportEnable.SetFileId("teleport_enable");
	TeleportGroup.PlaceLabledControl(this, &TeleportEnable, "Enable");

	TeleportKey.SetFileId("teleport_key");
	TeleportGroup.PlaceLabledControl(this, &TeleportKey, "Key");

#pragma endregion
	*/
/*#pragma region OverideFov
	FOVGroup.SetPosition(16, 365);
	FOVGroup.SetSize(360, 75);
	FOVGroup.SetText("FOV Changer");
	RegisterControl(&FOVGroup);

	FOVEnable.SetFileId("fov_enable");
	FOVGroup.PlaceLabledControl("Enable", this, &FOVEnable);

	FOVSlider.SetFileId("fov_slider");
	FOVSlider.SetBoundaries(0, 200);
	FOVSlider.SetValue(0);
	FOVGroup.PlaceLabledControl("FOV Amount", this, &FOVSlider);

#pragma endregion*/
}

/*void CPlayersTab::Setup()
{
	SetTitle("PlayerList");

#pragma region PList

	pListGroup.SetPosition(16, 16);
	pListGroup.SetSize(680, 200);
	pListGroup.SetText("Player List");
	pListGroup.SetColumns(2);
	RegisterControl(&pListGroup);

	pListPlayers.SetPosition(26, 46);
	pListPlayers.SetSize(640, 50);
	pListPlayers.SetHeightInItems(20);
	RegisterControl(&pListPlayers);

#pragma endregion

#pragma region Options
	
	OptionsGroup.SetPosition(16, 257);
	OptionsGroup.SetSize(450, 120);
	OptionsGroup.SetText("Player Options");
	RegisterControl(&OptionsGroup);

	OptionsFriendly.SetFileId("pl_friendly");
	OptionsGroup.PlaceLabledControl("Friendly", this, &OptionsFriendly);

	OptionsAimPrio.SetFileId("pl_priority");
	OptionsGroup.PlaceLabledControl("Priority", this, &OptionsAimPrio);

	OptionsCalloutSpam.SetFileId("pl_callout");
	OptionsGroup.PlaceLabledControl("Callout Spam", this, &OptionsCalloutSpam);

#pragma endregion
}

DWORD GetPlayerListIndex(int EntId)
{
	player_info_t pinfo;
	Interfaces::Engine->GetPlayerInfo(EntId, &pinfo);

	// Bot
	if (pinfo.guid[0] == 'B' && pinfo.guid[1] == 'O')
	{
		char buf[64]; sprintf_s(buf, "BOT_420%sAY", pinfo.name);
		return CRC32(buf, 64);
	}
	else
	{
		return CRC32(pinfo.guid, 32);
	}
}

bool IsFriendly(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].Friendly;
	}

	return false;
}

bool IsAimPrio(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].AimPrio;
	}

	return false;
}

bool IsCalloutTarget(int EntId)
{
	DWORD plistId = GetPlayerListIndex(EntId);
	if (PlayerList.find(plistId) != PlayerList.end())
	{
		return PlayerList[plistId].Callout;
	}

	return false;
}

void UpdatePlayerList()
{
	IClientEntity* pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && pLocal && pLocal->IsAlive())
	{
		Menu::Window.Playerlist.pListPlayers.ClearItems();

		// Loop through all active entitys
		for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
		{
			// Get the entity

			player_info_t pinfo;
			if (i != Interfaces::Engine->GetLocalPlayer() && Interfaces::Engine->GetPlayerInfo(i, &pinfo))
			{
				IClientEntity* pEntity = Interfaces::EntList->GetClientEntity(i);
				int HP = 100; char* Location = "Unknown";
				char *Friendly = " ", *AimPrio = " ";

				DWORD plistId = GetPlayerListIndex(Menu::Window.Playerlist.pListPlayers.GetValue());
				if (PlayerList.find(plistId) != PlayerList.end())
				{
					Friendly = PlayerList[plistId].Friendly ? "Friendly" : "";
					AimPrio = PlayerList[plistId].AimPrio ? "AimPrio" : "";
				}

				if (pEntity && !pEntity->IsDormant())
				{
					HP = pEntity->GetHealth();
					Location = pEntity->GetLastPlaceName();
				}

				char nameBuffer[512];
				sprintf_s(nameBuffer, "%-24s %-10s %-10s [%d HP] [Last Seen At %s]", pinfo.name, IsFriendly(i) ? "Friend" : " ", IsAimPrio(i) ? "AimPrio" : " ", HP, Location);
				Menu::Window.Playerlist.pListPlayers.AddItem(nameBuffer, i);

			}

		}

		DWORD meme = GetPlayerListIndex(Menu::Window.Playerlist.pListPlayers.GetValue());

		// Have we switched to a different player?
		static int PrevSelectedPlayer = 0;
		if (PrevSelectedPlayer != Menu::Window.Playerlist.pListPlayers.GetValue())
		{
			if (PlayerList.find(meme) != PlayerList.end())
			{
				Menu::Window.Playerlist.OptionsFriendly.SetState(PlayerList[meme].Friendly);
				Menu::Window.Playerlist.OptionsAimPrio.SetState(PlayerList[meme].AimPrio);
				Menu::Window.Playerlist.OptionsCalloutSpam.SetState(PlayerList[meme].Callout);

			}
			else
			{
				Menu::Window.Playerlist.OptionsFriendly.SetState(false);
				Menu::Window.Playerlist.OptionsAimPrio.SetState(false);
				Menu::Window.Playerlist.OptionsCalloutSpam.SetState(false);

			}
		}
		PrevSelectedPlayer = Menu::Window.Playerlist.pListPlayers.GetValue();

		PlayerList[meme].Friendly = Menu::Window.Playerlist.OptionsFriendly.GetState();
		PlayerList[meme].AimPrio = Menu::Window.Playerlist.OptionsAimPrio.GetState();
		PlayerList[meme].Callout = Menu::Window.Playerlist.OptionsCalloutSpam.GetState();
	}
}*/



void CColorTab::Setup()
{
	SetTitle("f");
#pragma region Colors
	ColorsGroup.SetText("Colors");
	ColorsGroup.SetPosition(16, 48);
	ColorsGroup.SetSize(360, 400);
	RegisterControl(&ColorsGroup);

	CTColorVisR.SetFileId("ct_color_vis_r");
	CTColorVisR.SetBoundaries(0.f, 255.f);
	CTColorVisR.SetValue(120.f);
	ColorsGroup.PlaceLabledControl(this, &CTColorVisR, "CTColorVisR");

	CTColorVisG.SetFileId("ct_color_vis_g");
	CTColorVisG.SetBoundaries(0.f, 255.f);
	CTColorVisG.SetValue(210.f);
	ColorsGroup.PlaceLabledControl(this, &CTColorVisG, "CTColorVisG");

	CTColorVisB.SetFileId("ct_color_vis_b");
	CTColorVisB.SetBoundaries(0.f, 255.f);
	CTColorVisB.SetValue(26.f);
	ColorsGroup.PlaceLabledControl(this, &CTColorVisB, "CTColorVisB");


	CTColorNoVisR.SetFileId("ct_color_no_vis_r");
	CTColorNoVisR.SetBoundaries(0.f, 255.f);
	CTColorNoVisR.SetValue(15.f);
	ColorsGroup.PlaceLabledControl(this, &CTColorNoVisR, "CTColorNoVisR");

	CTColorNoVisG.SetFileId("ct_color_no_vis_g");
	CTColorNoVisG.SetBoundaries(0.f, 255.f);
	CTColorNoVisG.SetValue(110.f);
	ColorsGroup.PlaceLabledControl(this, &CTColorNoVisG, "CTColorNoVisG");

	CTColorNoVisB.SetFileId("ct_color_no_vis_b");
	CTColorNoVisB.SetBoundaries(0.f, 255.f);
	CTColorNoVisB.SetValue(220.f);
	ColorsGroup.PlaceLabledControl(this, &CTColorNoVisB, "CTColorNoVisB");

	

	TColorVisR.SetFileId("t_color_vis_r");
	TColorVisR.SetBoundaries(0.f, 255.f);
	TColorVisR.SetValue(235.f);
	ColorsGroup.PlaceLabledControl(this, &TColorVisR, "TColorVisR");

	TColorVisG.SetFileId("t_color_vis_g");
	TColorVisG.SetBoundaries(0.f, 255.f);
	TColorVisG.SetValue(200.f);
	ColorsGroup.PlaceLabledControl(this, &TColorVisG, "TColorVisG");

	TColorVisB.SetFileId("t_color_vis_b");
	TColorVisB.SetBoundaries(0.f, 255.f);
	TColorVisB.SetValue(0.f);
	ColorsGroup.PlaceLabledControl(this, &TColorVisB, "TColorVisB");


	TColorNoVisR.SetFileId("t_color_no_vis_r");
	TColorNoVisR.SetBoundaries(0.f, 255.f);
	TColorNoVisR.SetValue(235.f);
	ColorsGroup.PlaceLabledControl(this, &TColorNoVisR, "TColorNoVisR");

	TColorNoVisG.SetFileId("t_color_no_vis_g");
	TColorNoVisG.SetBoundaries(0.f, 255.f);
	TColorNoVisG.SetValue(50.f);
	ColorsGroup.PlaceLabledControl(this, &TColorNoVisG, "TColorNoVisG");

	TColorNoVisB.SetFileId("t_color_no_vis_b");
	TColorNoVisB.SetBoundaries(0.f, 255.f);
	TColorNoVisB.SetValue(0.f);
	ColorsGroup.PlaceLabledControl(this, &TColorNoVisB, "TColorNoVisB");
	
	//CT VISIBLE
	Wiregroup.SetPosition(408, 16);
	Wiregroup.SetSize(360, 100);
	Wiregroup.SetText("Wireframe Colors");
	RegisterControl(&Wiregroup);

	WireframeColorR.SetFileId("wire_r");
	WireframeColorR.SetBoundaries(0, 255);
	WireframeColorR.SetValue(0);
	Wiregroup.PlaceLabledControl(this, &WireframeColorR, "Red");

	WireframeColorG.SetFileId("wire_r");
	WireframeColorG.SetBoundaries(0, 255);
	WireframeColorG.SetValue(0);
	Wiregroup.PlaceLabledControl(this, &WireframeColorG, "Green");

	WireframeColorB.SetFileId("wire_r");
	WireframeColorB.SetBoundaries(0, 255);
	WireframeColorB.SetValue(0);
	Wiregroup.PlaceLabledControl(this, &WireframeColorB, "Blue");

	//T Not Visible
	//TNVisGroup.SetPosition(16, 137);
	//TNVisGroup.SetSize(360, 100);
	//TNVisGroup.SetText("T Not Visible");
	//RegisterControl(&TNVisGroup);

	

	// T Vis Color

	//TVisGroup.SetPosition(408, 137);
	//TVisGroup.SetSize(360, 100);
	//TVisGroup.SetText("T Visible");
	//RegisterControl(&TVisGroup);



#pragma endregion
	
#pragma MenuGroup
	/*
	MenuGroup.SetPosition(16, 258);
	MenuGroup.SetSize(360, 100);
	MenuGroup.SetText("Bar Color 1");
	RegisterControl(&MenuGroup);

	//Menu Gradient Color 1
	MenuBar1R.SetFileId("bar_grad_1R");
	MenuBar1R.SetBoundaries(0, 255);
	MenuBar1R.SetValue(255);
	MenuGroup.PlaceLabledControl(this, &MenuBar1R, "Red");

	MenuBar1G.SetFileId("bar_grad_1G");
	MenuBar1G.SetBoundaries(0, 255);
	MenuBar1G.SetValue(144);
	MenuGroup.PlaceLabledControl(this, &MenuBar1G, "Green");

	MenuBar1B.SetFileId("bar_grad_1B");
	MenuBar1B.SetBoundaries(0, 255);
	MenuBar1B.SetValue(0);
	MenuGroup.PlaceLabledControl(this, &MenuBar1B, "Blue");


	//Menu Gradient Color 2
	MenuBar2.SetPosition(408, 258);
	MenuBar2.SetSize(360, 100);
	MenuBar2.SetText("Bar Color 2");
	RegisterControl(&MenuBar2);

	MenuBar2R.SetFileId("bar_grad_2R");
	MenuBar2R.SetBoundaries(0, 255);
	MenuBar2R.SetValue(255);
	MenuBar2.PlaceLabledControl(this, &MenuBar2R, "Red");

	MenuBar2G.SetFileId("bar_grad_2G");
	MenuBar2G.SetBoundaries(0, 255);
	MenuBar2G.SetValue(93);
	MenuBar2.PlaceLabledControl(this, &MenuBar2G, "Green");

	MenuBar2B.SetFileId("bar_grad_2B");
	MenuBar2B.SetBoundaries(0, 255);
	MenuBar2B.SetValue(0);
	MenuBar2.PlaceLabledControl(this, &MenuBar2B, "Blue");


	//MenuOpacity.SetFileId("men_oapacity");
	//MenuOpacity.SetBoundaries(0, 255);
	//MenuOpacity.SetValue(0);
	//MenuGroup.PlaceLabledControl("Menu Opacity", this, &MenuOpacity);

	//Inner
	MenuInside.SetPosition(16, 379);
	MenuInside.SetSize(360, 100);
	MenuInside.SetText("Menu Inner Color");
	RegisterControl(&MenuInside);

	MenuInnerR.SetFileId("in_R");
	MenuInnerR.SetBoundaries(0, 255);
	MenuInnerR.SetValue(255);
	MenuInside.PlaceLabledControl(this, &MenuInnerR, "Red");

	MenuInnerG.SetFileId("in_G");
	MenuInnerG.SetBoundaries(0, 255);
	MenuInnerG.SetValue(93);
	MenuInside.PlaceLabledControl(this, &MenuInnerG, "Green");

	MenuInnerB.SetFileId("in_B");
	MenuInnerB.SetBoundaries(0, 255);
	MenuInnerB.SetValue(0);
	MenuInside.PlaceLabledControl(this, &MenuInnerB, "Blue");
	*/
#pragma endregion

}

void CSettingsTab::Setup()
{

	SetTitle("d");// jestem pro XDDD
#pragma ButtonGroup
	ButtonGroup.SetPosition(16, 16);
	ButtonGroup.SetSize(360, 460);
	ButtonGroup.SetText("Buttons");
	RegisterControl(&ButtonGroup);

	ButtonGroup.SetPosition(16, 16);
	ButtonGroup.SetSize(360, 460);
	ButtonGroup.SetText("Buttons");
	RegisterControl(&ButtonGroup);
	
	
	SaveButton.SetText("Save Configuration");
	SaveButton.SetCallback(SaveCallbk);
	ButtonGroup.PlaceLabledControl(this, &SaveButton, "Save");

	LoadButton.SetText("Load Configuration");
	LoadButton.SetCallback(LoadCallbk);
	ButtonGroup.PlaceLabledControl(this, &LoadButton, "Load");

	//Cfgtext.SetFileId("cfgtext");
	//ButtonGroup.PlaceLabledControl(this, &Cfgtext, "");

	SetNr.AddItem("Legit");
	SetNr.AddItem("Semi Rage");
	SetNr.AddItem("Rage");
	SetNr.AddItem("Custom");
	//SetNr.AddItem("Custom 2");
	//SetNr.AddItem("Disable All");
	ButtonGroup.PlaceLabledControl(this, &SetNr, "CFG");
	
	//Unload.SetText("Force Crash(time out)");
	//Unload.SetCallback(Unloadbk);
	//ButtonGroup.PlaceLabledControl(this, &Unload, "Unload");
};








void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(&Window, VK_INSERT);
}

void Menu::DoUIFrame()
{
	// General Processing

	// If the "all filter is selected tick all the others
	if (Window.VisualsTab.FiltersAll.GetState())
	{
		Window.VisualsTab.FiltersC4.SetState(true);
		Window.VisualsTab.FiltersChickens.SetState(true);
		Window.VisualsTab.FiltersPlayers.SetState(true);
		Window.VisualsTab.FiltersWeapons.SetState(true);
	}
	

	GUI.Update();
	GUI.Draw();

	
}


