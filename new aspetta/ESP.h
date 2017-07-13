/*
Rest In Peace ApocalypseCheats
*/

#pragma once

#include "Hacks.h"

class CEsp : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
	std::vector<IMaterial*> SkyTextures;
	std::vector<IMaterial*> WorldTextures;
private:

	// Other shit
	IClientEntity *BombCarrier;

	struct ESPBox
	{
		int x, y, w, h;
	};

	// Draw a player
	void NoSky();
	void DoFOV();
	void DrawPlayer(IClientEntity* pEntity, player_info_t pinfo);

	// Get player info
	Color GetPlayerColor(IClientEntity* pEntity);
	void DrawBox(CEsp::ESPBox size, Color color);
	void Fill(CEsp::ESPBox size, Color color);
	void DrawAr(IClientEntity * pEntity, CEsp::ESPBox size);
	bool GetBox(IClientEntity* pEntity, ESPBox &result);
	void Main(IClientEntity* pLocalEntity);
	// Draw shit about player
	void SpecList();
	void DrawBox(Color color, ESPBox size);
	void DrawName(player_info_t pinfo, ESPBox size);
	void DrawHealth(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawHealth(ESPBox size, IClientEntity* pEntity);
	void DrawHealth2(CEsp::ESPBox size, IClientEntity* pEntity);
	void DrawArmor(CEsp::ESPBox size, IClientEntity* pEntity);
	void DrawInfo(ESPBox size, IClientEntity* pEntity);
	void DrawInfo(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawCross(IClientEntity* pEntity);
	void DrawDrop(IClientEntity * pEntity, ClientClass * cClass);
	void DrawChicken(IClientEntity * pEntity, ClientClass * cClass);
	void DrawBombPlanted(IClientEntity * pEntity, ClientClass * cClass);
	void DrawBomb(IClientEntity * pEntity, ClientClass * cClass);
	void DrawSkeleton(IClientEntity* pEntity);

	void DrawChicken(ClientClass* cClass, IClientEntity* pEntity);
	void DrawDrop(ClientClass* cClass, IClientEntity* pEntity);
	void DrawBombPlanted(ClientClass* cClass, IClientEntity* pEntity);
	void DrawBomb(ClientClass* cClass, IClientEntity* pEntity);
	void DrawGlow();
};

