/*
Rest In Peace ApocalypseCheats
*/

#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "nosmoke.h"
#include "GlowManager.h"
void CEsp::Init()
{
	BombCarrier = nullptr;
}

// Yeah dude we're defo gunna do some sick moves for the esp yeah
void CEsp::Move(CUserCmd *pCmd, bool &bSendPacket)
{

}

// Main ESP Drawing loop
void CEsp::Draw()
{
	IClientEntity *pLocal = hackManager.pLocal();


	if (Menu::Window.MiscTab.OtherSpectators.GetState())
	{
		SpecList();
	}
	if (Menu::Window.VisualsTab.OtherNoSky.GetState())
		NoSky();
	if (Menu::Window.LegitBotTab.FoVRadius.GetState())
		DoFOV();
	// Loop through all active entitys
	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		// Get the entity
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		player_info_t pinfo;

		// The entity isn't some laggy peice of shit or something
		if (pEntity &&  pEntity != pLocal && !pEntity->IsDormant())
		{
			// Radar
			if (Menu::Window.VisualsTab.OtherRadar.GetState())
			{
				DWORD m_bSpotted = NetVar.GetNetVar(0x839EB159);
				*(char*)((DWORD)(pEntity)+m_bSpotted) = 1;
			}

			// Is it a player?!
			if (Menu::Window.VisualsTab.FiltersPlayers.GetState() && Interfaces::Engine->GetPlayerInfo(i, &pinfo) && pEntity->IsAlive())
			{
				DrawPlayer(pEntity, pinfo);
			}


			// ~ Other ESP's here (items and shit) ~ //
			ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

			// Dropped weapons
			if (Menu::Window.VisualsTab.FiltersWeapons.GetState() && cClass->m_ClassID != (int)CSGOClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)CSGOClassID::CDEagle || cClass->m_ClassID == (int)CSGOClassID::CAK47)))
			{
				DrawDrop(cClass, pEntity);
			}

			// If entity is the bomb
			if (Menu::Window.VisualsTab.FiltersC4.GetState())
			{
				if (cClass->m_ClassID == (int)CSGOClassID::CPlantedC4)
					DrawBombPlanted(cClass, pEntity);

				if (cClass->m_ClassID == (int)CSGOClassID::CC4)
					DrawBomb(cClass, pEntity);
			}

			// If entity is a chicken
			if (Menu::Window.VisualsTab.FiltersChickens.GetState())
			{
				if (cClass->m_ClassID == (int)CSGOClassID::CChicken)
					DrawChicken(cClass, pEntity);
			}
		}
	}

	// Anti Flash
	if (Menu::Window.VisualsTab.OtherNoFlash.GetState())
	{
		DWORD m_flFlashMaxAlpha = NetVar.GetNetVar(0xFE79FB98);
		*(float*)((DWORD)pLocal + m_flFlashMaxAlpha) = Menu::Window.VisualsTab.OtherNoFlashVal.GetValue();
	}
}

void CEsp::NoSky()
{

}
void CEsp::DoFOV()
{
	float FoV;
	std::vector<int> HitBoxesToScan;
	IClientEntity* pLocal = hackManager.pLocal();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (!pWeapon)
		return;

	if (GameUtils::IsPistol(pWeapon))
	{
		FoV = Menu::Window.LegitBotTab.WeaponPistFoV.GetValue();

	}
	else if (GameUtils::IsSniper(pWeapon))
	{
		FoV = Menu::Window.LegitBotTab.WeaponSnipFoV.GetValue();

	}
	else
	{
		FoV = Menu::Window.LegitBotTab.WeaponMainFoV.GetValue();
	}



	int w, h;
	Interfaces::Engine->GetScreenSize(w, h);
	float CenterX = (float)w / 2;
	float CenterY = (float)h / 2;


	Offsets::VMT::Surface_DrawOutlinedCircle;//(CenterX, CenterY, FoV, 360, 0, 255, 0, 255); //(int x, int y, int radius, int segments, int r, int g, int b, int a)
}
void CEsp::SpecList()
{
	IClientEntity *pLocal = hackManager.pLocal();

	RECT scrn = Render::GetViewport();
	int AC = 0;

	// Loop through all active entitys
	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		// Get the entity
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		player_info_t pinfo;

		// The entity isn't some laggy peice of shit or something
		if (pEntity &&  pEntity != pLocal)
		{
			if (Interfaces::Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
			{
				HANDLE obs = pEntity->GetObserverTargetHandle();

				if (obs)
				{
					IClientEntity *pTarget = Interfaces::EntList->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;
					if (pTarget)
					{
						if (Interfaces::Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
						{
							char buf[255]; sprintf_s(buf, "%s => %s", pinfo.name, pinfo2.name);
							RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, buf);
							Render::Clear(scrn.right - 260, (scrn.bottom / 2) + (16 * AC), 260, 16, Color(0, 0, 0, 120));
							Render::Text(scrn.right - TextSize.right - 4, (scrn.bottom / 2) + (16 * AC), pTarget->GetIndex() == pLocal->GetIndex() ? Color(240, 70, 80, 255) : Color(255, 255, 255, 255), Render::Fonts::ESP, buf);
							AC++;
						}
					}
				}
			}
		}
	}

	Render::Outline(scrn.right - 261, (scrn.bottom / 2) - 1, 262, (16 * AC) + 2, Color(23, 23, 23, 255));
	Render::Outline(scrn.right - 260, (scrn.bottom / 2), 260, (16 * AC), Color(90, 90, 90, 255));
}

//  Yeah m8
void CEsp::DrawPlayer(IClientEntity* pEntity, player_info_t pinfo)
{
	ESPBox Box;
	Color Color;

	// Show own team false? well gtfo teammate lol
	if (Menu::Window.VisualsTab.FiltersEnemiesOnly.GetState() && (pEntity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()))
		return;

	if (GetBox(pEntity, Box))
	{
		Color = GetPlayerColor(pEntity);

		/*if (Menu::Window.VisualsTab.OptionsGlow.GetState())
		{
		int TeamNum = pEntity->GetTeamNum();

		if (TeamNum == TEAM_CS_T)
		{
		DrawGlow(pEntity, 255, 0, 0, 160);
		}
		else if (TeamNum == TEAM_CS_CT)
		{
		DrawGlow(pEntity, 0, 0, 255, 160);
		}
		}*/

		if (Menu::Window.VisualsTab.OptionsBox.GetState())
			DrawBox(Color, Box);

		if (Menu::Window.VisualsTab.OptionsName.GetState())
			DrawName(pinfo, Box);

		if (Menu::Window.VisualsTab.OptionsHealth.GetIndex() == 0)
		{

		}
		if (Menu::Window.VisualsTab.OptionsHealth.GetIndex() == 1)
		{
			DrawHealth(Box, pEntity);
		}
		if (Menu::Window.VisualsTab.OptionsHealth.GetIndex() == 2)
		{
			DrawHealth2(Box, pEntity);
		}
		if (Menu::Window.VisualsTab.OptionsArmor.GetState())
		{
			DrawArmor(Box, pEntity);
		}


		if (Menu::Window.VisualsTab.OptionsInfo.GetState() || Menu::Window.VisualsTab.OptionsWeapon.GetState())
			DrawInfo(Box, pEntity);

		if (Menu::Window.VisualsTab.OptionsAimSpot.GetState())
			DrawCross(pEntity);

		if (Menu::Window.VisualsTab.OptionsSkeleton.GetState())
			DrawSkeleton(pEntity);
	}
}


// Gets the 2D bounding box for the entity
// Returns false on failure nigga don't fail me
bool CEsp::GetBox(IClientEntity* pEntity, CEsp::ESPBox &result)
{
	// Variables
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	// Get the locations
	vOrigin = pEntity->GetOrigin();
	min = pEntity->collisionProperty()->GetMins() + vOrigin;
	max = pEntity->collisionProperty()->GetMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	// Get screen positions
	if (!Render::WorldToScreen(points[3], flb) || !Render::WorldToScreen(points[5], brt)
		|| !Render::WorldToScreen(points[0], blb) || !Render::WorldToScreen(points[4], frt)
		|| !Render::WorldToScreen(points[2], frb) || !Render::WorldToScreen(points[1], brb)
		|| !Render::WorldToScreen(points[6], blt) || !Render::WorldToScreen(points[7], flt))
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	// Width / height
	result.x = left;
	result.y = top;
	result.w = right - left;
	result.h = bottom - top;

	return true;
}

void CEsp::Main(IClientEntity * pLocalEntity)
{
	IClientEntity* pLocal = (IClientEntity*)(Interfaces::Engine->GetLocalPlayer());

	if (pLocal && Menu::Window.VisualsTab.Active.GetState())
	{
		CEsp::Main(pLocal);
	}

}

// Get an entities color depending on team and vis ect
Color CEsp::GetPlayerColor(IClientEntity* pEntity)
{
	int TeamNum = pEntity->GetTeamNum();
	bool IsVis = GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Head);

	Color color;

	if (TeamNum == TEAM_CS_T)
	{
		if (IsVis)
			color = Color(Menu::Window.ColorTab.TColorVisR.GetValue(), Menu::Window.ColorTab.TColorVisG.GetValue(), Menu::Window.ColorTab.TColorVisB.GetValue(), 255);
		else
			color = Color(Menu::Window.ColorTab.TColorNoVisR.GetValue(), Menu::Window.ColorTab.TColorNoVisG.GetValue(), Menu::Window.ColorTab.TColorNoVisB.GetValue(), 255);
	}
	else
	{
		if (IsVis)
			color = Color(Menu::Window.ColorTab.CTColorVisR.GetValue(), Menu::Window.ColorTab.CTColorVisG.GetValue(), Menu::Window.ColorTab.CTColorVisB.GetValue(), 255);
		else
			color = Color(Menu::Window.ColorTab.CTColorNoVisR.GetValue(), Menu::Window.ColorTab.CTColorNoVisG.GetValue(), Menu::Window.ColorTab.CTColorNoVisB.GetValue(), 255);
	}


	return color;
}
// 2D  Esp box
void CEsp::DrawBox(Color color, CEsp::ESPBox size)
{
	Render::Outline(size.x, size.y, size.w, size.h, color);
	Render::Outline(size.x - 1, size.y - 1, size.w + 2, size.h + 2, Color(140, 1320, 10, 210));
	Render::Outline(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(10, 10, 10, 210));
}



// Unicode Conversions
static wchar_t* CharToWideChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(NULL, wa, size / 4, text, size);
	return wa;
}

// Player name
void CEsp::DrawName(player_info_t pinfo, CEsp::ESPBox size)
{

	RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
	Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 14,
		Color(255, 255, 255, 255), Render::Fonts::ESP, pinfo.name);
}

// Draw a health bar. For Tf2 when a bar is bigger than max health a second bar is displayed
void CEsp::DrawHealth(CEsp::ESPBox size, IClientEntity* pEntity)
{
	int health = pEntity->GetHealth();

	if (health > 100)
		health = 100;

	int r = 255 - health * 2.55;
	int g = health * 2.55;

	int healthBar = size.h / 100 * health;
	int healthBarDelta = size.h - healthBar;

	int iClampedHealth = pEntity->GetHealth();
	if (iClampedHealth >= 100)
		iClampedHealth = 100;

	Render::Outline(size.x - 4, size.y + 1, 2, size.h * 0.01 * iClampedHealth, Color(r, g, 0, 255));
	Render::Outline(size.x - 4, size.y + 1, 2, size.h * 0.01 * iClampedHealth, Color(r, g, 0, 255));
	Render::Outline(size.x - 5, size.y - 1, 4, size.h + 2, Color(0, 0, 0, 100));
}
void CEsp::DrawHealth2(CEsp::ESPBox size, IClientEntity* pEntity)
{
	ESPBox HealthBar = size;
	HealthBar.y += (HealthBar.h + 6);
	HealthBar.h = 4;

	float HealthValue = pEntity->GetHealth();
	float HealthPerc = HealthValue / 100.f;
	float Width = (size.w * HealthPerc);
	HealthBar.w = Width;

	int health = pEntity->GetHealth();

	if (health > 100)
		health = 100;

	int r = 255 - health * 2.55;
	int g = health * 2.55;

	int healthBar = size.h / 100 * health;
	int healthBarDelta = size.h - healthBar;

	//int iClampedHealth = pEntity->GetHealth();
	//  if (iClampedHealth >= 100)
	//  iClampedHealth = 100;

	Render::Outline(size.x - 4, size.y + 1, 1, size.h * 0.01 * health, Color(r, g, 0, 205));
	Render::Outline(size.x - 5, size.y - 1, 3, size.h + 2, Color(0, 0, 0, 205));
}
void CEsp::DrawArmor(CEsp::ESPBox size, IClientEntity* pEntity)
{
	ESPBox ArmorBar = size;
	if (Menu::Window.VisualsTab.OptionsHealth.GetIndex())
		ArmorBar.y += (ArmorBar.h + 3);
	else
		ArmorBar.y += (ArmorBar.h + 3);

	ArmorBar.h = 2;

	float ArmorValue = pEntity->ArmorValue();
	float ArmorPerc = ArmorValue / 100.f;
	float Width = (size.w * ArmorPerc);
	ArmorBar.w = Width;

	// � Main Bar � //
	Vertex_t Verts[4];
	Verts[0].Init(Vector2D(ArmorBar.x, ArmorBar.y));
	Verts[1].Init(Vector2D(ArmorBar.x + size.w, ArmorBar.y));
	Verts[2].Init(Vector2D(ArmorBar.x + size.w, ArmorBar.y + 4));
	Verts[3].Init(Vector2D(ArmorBar.x, ArmorBar.y + 4));

	Render::PolygonOutline(4, Verts, Color(0, 0, 0, 255), Color(0, 0, 0, 255));

	Vertex_t Verts2[4];
	Verts2[0].Init(Vector2D(ArmorBar.x + 1, ArmorBar.y + 1));
	Verts2[1].Init(Vector2D(ArmorBar.x + ArmorBar.w, ArmorBar.y + 1));
	Verts2[2].Init(Vector2D(ArmorBar.x + ArmorBar.w, ArmorBar.y + 4));
	Verts2[3].Init(Vector2D(ArmorBar.x, ArmorBar.y + 4));

	Color c = Color(80, 135, 190, 255);
	Render::Polygon(4, Verts2, c);

	Verts2[0].Init(Vector2D(ArmorBar.x + 1, ArmorBar.y + 1));
	Verts2[1].Init(Vector2D(ArmorBar.x + ArmorBar.w, ArmorBar.y + 1));
	Verts2[2].Init(Vector2D(ArmorBar.x + ArmorBar.w, ArmorBar.y + 2));
	Verts2[3].Init(Vector2D(ArmorBar.x, ArmorBar.y + 2));

	Render::Polygon(4, Verts2, Color(80, 135, 190, 255));
}
/*
void NoScope(IClientEntity *pLocal, unsigned int vguiPanel)
{
if (Menu::Window.VisualsTab.NoZoom.GetState() && pLocal->IsScoped() && Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && pLocal->IsAlive())
{
int width, height;
Interfaces::Engine->GetScreenSize(width, height);
Render::Line(0, height * 0.5, width, height * 0.5, Color(0, 0, 0, 255));
Render::Line(width * 0.5, 0, width * 0.5, height, Color(0, 0, 0, 255));
}

if (!strcmp("HudZoom", Interfaces::Panels->GetName(vguiPanel)) && Menu::Window.VisualsTab.NoZoom.GetState() && pLocal->IsScoped() && Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame() && pLocal->IsAlive())
{ //KURVA BUILDNI SA TY KOKOT JEBNUTY
return;
}
}
*/
//ide po armor bar i zaraz ci esp zrobie
// Cleans the internal class name up to something human readable and nice
std::string CleanItemName(std::string name)
{
	std::string Name = name;
	// Tidy up the weapon Name
	if (Name[0] == 'C')
		Name.erase(Name.begin());

	// Remove the word Weapon
	auto startOfWeap = Name.find("Weapon");
	if (startOfWeap != std::string::npos)
		Name.erase(Name.begin() + startOfWeap, Name.begin() + startOfWeap + 6);

	return Name;
}



// Anything else: weapons, class state? idk
void CEsp::DrawInfo(CEsp::ESPBox size, IClientEntity* pEntity)
{
	int xd = 5;

	if (Menu::Window.VisualsTab.OptionsArmor.GetState())
		xd += (0 + 3);
	else
		xd += (0 + 0);

	std::vector<std::string> Info;

	// Player Weapon ESP
	IClientEntity* pWeapon = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)pEntity->GetActiveWeaponHandle());
	if (Menu::Window.VisualsTab.OptionsWeapon.GetState() && pWeapon)
	{
		ClientClass* cClass = (ClientClass*)pWeapon->GetClientClass();
		if (cClass)
		{
			// Draw it
			std::string meme = CleanItemName(cClass->m_pNetworkName);
			RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, meme.c_str());
			Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y + size.h + xd,
				Color(255, 255, 255, 255), Render::Fonts::ESP, meme.c_str());
		}
	}


	// Bomb Carrier
	if (Menu::Window.VisualsTab.OptionsInfo.GetState() && pEntity == BombCarrier)
	{
		Info.push_back("Bomb Carrier");
	}

	static RECT Size = Render::GetTextSize(Render::Fonts::Default, "Hi");
	int i = 0;
	for (auto Text : Info)
	{
		Render::Text(size.x + size.w + 3, size.y + (i*(Size.bottom + 2)), Color(255, 255, 255, 255), Render::Fonts::ESP, Text.c_str());
		i++;
	}
}

// Little cross on their heads
void CEsp::DrawCross(IClientEntity* pEntity)
{
	Vector cross = pEntity->GetHeadPos(), screen;
	static int Scale = 2;
	if (Render::WorldToScreen(cross, screen))
	{
		Render::Clear(screen.x - Scale, screen.y - (Scale * 2), (Scale * 2), (Scale * 4), Color(20, 20, 20, 160));
		Render::Clear(screen.x - (Scale * 2), screen.y - Scale, (Scale * 4), (Scale * 2), Color(20, 20, 20, 160));
		Render::Clear(screen.x - Scale - 1, screen.y - (Scale * 2) - 1, (Scale * 2) - 2, (Scale * 4) - 2, Color(250, 250, 250, 160));
		Render::Clear(screen.x - (Scale * 2) - 1, screen.y - Scale - 1, (Scale * 4) - 2, (Scale * 2) - 2, Color(250, 250, 250, 160));
	}
}

// Draws a dropped CS:GO Item
void CEsp::DrawDrop(ClientClass* cClass, IClientEntity* pEntity)
{
	Vector Box;
	CBaseCombatWeapon* Weapon = (CBaseCombatWeapon*)pEntity;
	IClientEntity* plr = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)Weapon->GetOwnerHandle());
	if (!plr && Render::WorldToScreen(Weapon->GetOrigin(), Box))
	{
		if (Menu::Window.VisualsTab.OptionsBox.GetState())
		{
			Render::Outline(Box.x - 2, Box.y - 2, 4, 4, Color(255, 255, 255, 255));
			Render::Outline(Box.x - 3, Box.y - 3, 6, 6, Color(10, 10, 10, 150));
		}

		if (Menu::Window.VisualsTab.OptionsInfo.GetState())
		{
			std::string ItemName = CleanItemName(cClass->m_pNetworkName);
			RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, ItemName.c_str());
			Render::Text(Box.x - (TextSize.right / 2), Box.y - 16, Color(255, 255, 255, 255), Render::Fonts::ESP, ItemName.c_str());
		}
	}
}

// Draws a chicken
void CEsp::DrawChicken(ClientClass* cClass, IClientEntity* pEntity)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "Chicken");
		if (Menu::Window.VisualsTab.OptionsBox.GetState())
			DrawBox(Color(255, 255, 255, 255), Box);

		if (Menu::Window.VisualsTab.OptionsName.GetState())
			DrawName(pinfo, Box);
	}
}

// Draw the planted bomb and timer
void CEsp::DrawBombPlanted(ClientClass* cClass, IClientEntity* pEntity)
{
	// Null it out incase bomb has been dropped or planted
	BombCarrier = nullptr;

	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	CCSBomb* Bomb = (CCSBomb*)pEntity;

	if (Render::WorldToScreen(vOrig, vScreen))
	{
		float flBlow = Bomb->GetC4BlowTime();
		float TimeRemaining = flBlow - (Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase());
		char buffer[64];
		sprintf_s(buffer, "Bomb Planted", TimeRemaining);
		Render::Text(vScreen.x, vScreen.y, Color(250, 42, 42, 255), Render::Fonts::ESP, buffer);
	}
}

// Draw the bomb if it's dropped, or store the player who's carrying 
void CEsp::DrawBomb(ClientClass* cClass, IClientEntity* pEntity)
{
	// Null it out incase bomb has been dropped or planted
	BombCarrier = nullptr;
	CBaseCombatWeapon *BombWeapon = (CBaseCombatWeapon *)pEntity;
	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	bool adopted = true;
	HANDLE parent = BombWeapon->GetOwnerHandle();
	if (parent || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
	{
		IClientEntity* pParentEnt = (Interfaces::EntList->GetClientEntityFromHandle(parent));
		if (pParentEnt && pParentEnt->IsAlive())
		{
			BombCarrier = pParentEnt;
			adopted = false;
		}
	}

	if (adopted)
	{
		if (Render::WorldToScreen(vOrig, vScreen))
		{
			Render::Text(vScreen.x, vScreen.y, Color(112, 230, 20, 255), Render::Fonts::ESP, "Bomb");
		}
	}
}

void DrawBoneArray(int amount, IClientEntity* pEntity, Color color, int* boneNumbers)
{
	Vector LastBoneScreen;
	for (int i = 0; i < amount; i++)
	{
		Vector Bone = pEntity->GetBonePos(boneNumbers[i]);
		Vector BoneScreen;

		if (Render::WorldToScreen(Bone, BoneScreen))
		{
			if (i>0)
			{
				Render::Line(LastBoneScreen.x, LastBoneScreen.y, BoneScreen.x, BoneScreen.y, color);
			}
		}
		LastBoneScreen = BoneScreen;
	}
}

void DrawBoneTest(IClientEntity *pEntity)
{
	for (int i = 0; i < 127; i++)
	{
		Vector BoneLoc = pEntity->GetBonePos(i);
		Vector BoneScreen;
		if (Render::WorldToScreen(BoneLoc, BoneScreen))
		{
			char buf[10];
			_itoa_s(i, buf, 10);
			Render::Text(BoneScreen.x, BoneScreen.y, Color(255, 255, 255, 180), Render::Fonts::ESP, buf);
		}
	}
}
/*
void CEsp::Main(IClientEntity* pLocalEntity)
{
IClientEntity* pLocal = (IClientEntity*)(Interfaces::Engine->GetLocalPlayer());

if (pLocal && Menu::Window.VisualsTab.Active.GetState())
{
CEsp::Main(pLocal);
}


}
*/
// UDALO SIE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void CEsp::DrawSkeleton(IClientEntity* pEntity)
{
	studiohdr_t* pStudioHdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			if (Render::WorldToScreen(vParent, sParent) && Render::WorldToScreen(vChild, sChild))
			{
				Render::Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255, 255, 255, 255));
			}
		}
	}
}