/*
Rest In Peace ApocalypseCheats
*/
#define M_PI 3.14159265358979323846
#pragma once

#include "Hacks.h"

class CRageBot : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	// Targetting
	int GetTargetCrosshair();
	int GetTargetDistance();
	int GetTargetHealth();
	bool TargetMeetsRequirements(IClientEntity* pEntity);
	float FovToPlayer(Vector View, IClientEntity* pEntity, int HitBox, Vector ViewOffSet);
	int HitScan(IClientEntity* pEntity);
	bool AimAtPoint(Vector point, CUserCmd *pCmd, bool &bSendPacket, IClientEntity* pLocal);

	// Functionality
	void DoAimbot(bool &bSendPacket, CUserCmd *pCmd);
	void DoNoRecoil(CUserCmd *pCmd);
	void DoNoSpread(CUserCmd * pCmd);
	void PositionAdjustment(CUserCmd* pCmd);

	// AntiAim
	void DoAntiAim(CUserCmd *pCmd, bool&bSendPacket);
	//bool EdgeAntiAim(IClientEntity* pLocalBaseEntity, CUserCmd* cmd, float flWall, float flCornor);
	//bool bEdge;	
	


	// AimStep
	bool IsAimStepping;
	Vector LastAimstepAngle;
	Vector LastAngle;

	// Aimbot
	bool IsLocked;
	int TargetID;
	int HitBox;
	Vector AimPoint;
};