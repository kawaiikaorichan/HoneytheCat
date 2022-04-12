#include "pch.h"
#include "OverKnux.h"
#include "OverAmy.h"

//Macros
#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

player_parameter OrKnucklesPhysicsData = { 60, 2, 16, 16, 2.5f, 0.6f, 1.66f, 3, 0.23f, 0.46f, 1.39f, 3.1f, 3.7f, 5.09f, 0.076f, 0.05f, 0.031f, -0.06f, -0.18f, -0.17f, -0.028f, -0.008f, -0.01f, -0.4f, -0.1f, -0.6f, -0.3375f, 0.3f, 4, 10, 0.08f, 7, 5 };
player_parameter CustKnucklesPhysicsData = { 60, 1.5f, 16, 16, 2.5f, 0.5f, 1.66f, 3, 0.23f, 0.46f, 1.39f, 2.7f, 3.7f, 5.09f, 0.076f, 0.05f, 0.031f, -0.06f, -0.18f, -0.17f, -0.028f, -0.008f, -0.01f, -0.4f, -0.1f, -0.6f, -0.3375f, 0.3f, 3.5f, 10, 0.04f, 7, 5 };
player_parameter CustAmyPhysicsData = { 60, 1.5f, 16, 16, 2.5f, 0.5f, 1.66f, 3, 0.23f, 0.46f, 1.39f, 2.7f, 3.7f, 5.09f, 0.076f, 0.05f, 0.031f, -0.06f, -0.18f, -0.17f, -0.028f, -0.008f, -0.01f, -0.4f, -0.1f, -0.6f, -0.3375f, 0.3f, 3.5f, 10, 0.04f, 7, 5 };

//Options
enum OverKnuxTexture { RedK, BlueK };
enum OverAmyTexture { RedA, BlueA };

static bool EnableOverKnux = true;
static bool EnableOverAmy = true;
static bool CustomKnuxPhys = true;
static bool CustomAmyPhys = true;
static int OverKnux = RedK;
static int OverAmy = RedA;

Trampoline* LoadRegObjTextures_b = nullptr;
Trampoline* FreeRegObjTexlists_b = nullptr;

static NJS_TEXNAME HoneyOKGUI_TEXNAME[9] = {};
static NJS_TEXLIST HoneyOKGUI_TEXLIST = { arrayptrandlengthT(HoneyOKGUI_TEXNAME, int) };
static NJS_TEXNAME HoneyOKBlueGUI_TEXNAME[9] = {};
static NJS_TEXLIST HoneyOKBlueGUI_TEXLIST = { arrayptrandlengthT(HoneyOKBlueGUI_TEXNAME, int) };
static NJS_TEXNAME HoneyOAGUI_TEXNAME[9] = {};
static NJS_TEXLIST HoneyOAGUI_TEXLIST = { arrayptrandlengthT(HoneyOAGUI_TEXNAME, int) };
static NJS_TEXNAME HoneyOABlueGUI_TEXNAME[9] = {};
static NJS_TEXLIST HoneyOABlueGUI_TEXLIST = { arrayptrandlengthT(HoneyOABlueGUI_TEXNAME, int) };

static void __cdecl EV_SetFace_r(task* tp, const char* str);
Trampoline EV_SetFace_t(0x4310D0, 0x4310D6, EV_SetFace_r);
static void __cdecl EV_SetFace_r(task* tp, const char* str)
{
	if (EnableOverKnux)
	{
		if (tp && tp->twp->counter.b[1] == Characters_Knuckles)
		{
			return;
		}
	}

	if (EnableOverAmy)
	{
		if (tp && tp->twp->counter.b[1] == Characters_Amy)
		{
			return;
		}
	}
	

	((decltype(EV_SetFace_r)*)EV_SetFace_t.Target())(tp, str);
}

static void __cdecl LoadRegObjTextures_r(int a1)
{
	if (EnableOverKnux)
	{
		if (OverKnux == RedK)
		{
			LoadPVM("HoneyOKGUI", &HoneyOKGUI_TEXLIST);
		}

		if (OverKnux == BlueK)
		{
			LoadPVM("HoneyOKBlueGUI", &HoneyOKBlueGUI_TEXLIST);
		}
	}

	if (EnableOverAmy)
	{
		if (OverAmy == RedA)
		{
			LoadPVM("HoneyOAGUI", &HoneyOAGUI_TEXLIST);
		}

		if (OverAmy == BlueA)
		{
			LoadPVM("HoneyOABlueGUI", &HoneyOABlueGUI_TEXLIST);
		}
	}
	((decltype(LoadRegObjTextures_r)*)LoadRegObjTextures_b->Target())(a1);
}

static void __cdecl FreeRegObjTexlists_r()
{
	njReleaseTexture(&HoneyOKGUI_TEXLIST);
	njReleaseTexture(&HoneyOKBlueGUI_TEXLIST);
	njReleaseTexture(&HoneyOAGUI_TEXLIST);
	njReleaseTexture(&HoneyOABlueGUI_TEXLIST);
	((decltype(FreeRegObjTexlists_r)*)FreeRegObjTexlists_b->Target())();
}

void HoneyGUI_Init()
{
	LoadRegObjTextures_b = new Trampoline(0x4212E0, 0x4212E5, LoadRegObjTextures_r, false);
	FreeRegObjTexlists_b = new Trampoline(0x420F40, 0x420F45, FreeRegObjTexlists_r, false);
}

uint16_t Honey_UpperArmIndices_DC[] = {
	0, 2,
	4, 6,
	5, 7,
	1, 3,
};

uint16_t Honey_LowerArmIndices_DC[] = {
	4, 14,
	5, 15,
	1, 11,
	0, 10,
};

uint16_t Honey_KneeIndices_DC[] = {
	0, 2,
	4, 6,
	5, 7,
	1, 3,
};

uint16_t Honey_LegIndices_DC[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

uint16_t Honey_ShoeIndices_DC[] = {
	2, 3,
	3, 2,
	0, 1,
	1, 0,
};

uint16_t Honey_HandIndices_DC[] = {
	0, 13,
	1, 1,
	5, 3,
	4, 12,
};

uint16_t HoneyK_HandIndices_DC[] = {
	0, 0,
	1, 1,
	5, 3,
	4, 2,
};

uint16_t Honey_ShovelClawIndices_DC[] = {
	0, 10,
	1, 3,
	5, 1,
	4, 11,
};

void __cdecl InitKnucklesWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // edx@1
	NJS_OBJECT* v4; // edx@1
	NJS_OBJECT* v5; // eax@1

	KnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
	KnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[0].anonymous_5 = 0;
	KnucklesWeldInfo[0].VertexBuffer = 0;
	KnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[0].WeldType = 2;
	KnucklesWeldInfo[0].VertIndexes = Honey_UpperArmIndices_DC;
	KnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	KnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	KnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[1].WeldType = 2;
	KnucklesWeldInfo[1].anonymous_5 = 0;
	KnucklesWeldInfo[1].VertexBuffer = 0;
	KnucklesWeldInfo[1].VertIndexes = Honey_LowerArmIndices_DC;
	KnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[2].VertIndexes = Honey_UpperArmIndices_DC;
	KnucklesWeldInfo[2].ModelB = v0;
	KnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[2].WeldType = 2;
	KnucklesWeldInfo[2].anonymous_5 = 0;
	KnucklesWeldInfo[2].VertexBuffer = 0;
	KnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	KnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	KnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[3].WeldType = 2;
	KnucklesWeldInfo[3].anonymous_5 = 0;
	KnucklesWeldInfo[3].VertexBuffer = 0;
	KnucklesWeldInfo[3].VertIndexes = Honey_LowerArmIndices_DC;
	KnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	KnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[4].WeldType = 2;
	KnucklesWeldInfo[4].anonymous_5 = 0;
	KnucklesWeldInfo[4].VertexBuffer = 0;
	KnucklesWeldInfo[4].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	KnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	KnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[5].WeldType = 2;
	KnucklesWeldInfo[5].anonymous_5 = 0;
	KnucklesWeldInfo[5].VertexBuffer = 0;
	KnucklesWeldInfo[5].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	KnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[6].WeldType = 2;
	KnucklesWeldInfo[6].anonymous_5 = 0;
	KnucklesWeldInfo[6].VertexBuffer = 0;
	KnucklesWeldInfo[6].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	KnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	KnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[7].WeldType = 2;
	KnucklesWeldInfo[7].anonymous_5 = 0;
	KnucklesWeldInfo[7].VertexBuffer = 0;
	KnucklesWeldInfo[7].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	KnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[8].WeldType = 2;
	KnucklesWeldInfo[8].anonymous_5 = 0;
	KnucklesWeldInfo[8].VertexBuffer = 0;
	KnucklesWeldInfo[8].VertIndexes = Honey_ShoeIndices_DC;
	KnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[9].VertIndexes = Honey_ShoeIndices_DC;
	KnucklesWeldInfo[9].ModelB = v1;
	KnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[9].WeldType = 2;
	KnucklesWeldInfo[9].anonymous_5 = 0;
	KnucklesWeldInfo[9].VertexBuffer = 0;
	KnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	KnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	KnucklesWeldInfo[10].WeldType = 2;
	KnucklesWeldInfo[10].anonymous_5 = 0;
	KnucklesWeldInfo[10].VertexBuffer = 0;
	KnucklesWeldInfo[10].VertIndexes = HoneyK_HandIndices_DC;
	KnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	KnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	KnucklesWeldInfo[11].WeldType = 2;
	KnucklesWeldInfo[11].anonymous_5 = 0;
	KnucklesWeldInfo[11].VertexBuffer = 0;
	KnucklesWeldInfo[11].VertIndexes = HoneyK_HandIndices_DC;
	KnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	KnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[12].WeldType = 2;
	KnucklesWeldInfo[12].anonymous_5 = 0;
	KnucklesWeldInfo[12].VertexBuffer = 0;
	KnucklesWeldInfo[12].VertIndexes = Honey_UpperArmIndices_DC;
	KnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	KnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	KnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[13].WeldType = 2;
	KnucklesWeldInfo[13].anonymous_5 = 0;
	KnucklesWeldInfo[13].VertexBuffer = 0;
	KnucklesWeldInfo[13].VertIndexes = Honey_LowerArmIndices_DC;
	KnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	KnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	KnucklesWeldInfo[14].WeldType = 2;
	KnucklesWeldInfo[14].anonymous_5 = 0;
	KnucklesWeldInfo[14].VertexBuffer = 0;
	KnucklesWeldInfo[14].VertIndexes = Honey_UpperArmIndices_DC;
	KnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	KnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	KnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	KnucklesWeldInfo[15].WeldType = 2;
	KnucklesWeldInfo[15].anonymous_5 = 0;
	KnucklesWeldInfo[15].VertexBuffer = 0;
	KnucklesWeldInfo[15].VertIndexes = Honey_LowerArmIndices_DC;
	KnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	KnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[16].WeldType = 2;
	KnucklesWeldInfo[16].anonymous_5 = 0;
	KnucklesWeldInfo[16].VertexBuffer = 0;
	KnucklesWeldInfo[16].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	KnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	KnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[17].WeldType = 2;
	KnucklesWeldInfo[17].anonymous_5 = 0;
	KnucklesWeldInfo[17].VertexBuffer = 0;
	KnucklesWeldInfo[17].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	KnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	KnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[18].WeldType = 2;
	KnucklesWeldInfo[18].anonymous_5 = 0;
	KnucklesWeldInfo[18].VertexBuffer = 0;
	KnucklesWeldInfo[18].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	KnucklesWeldInfo[19].VertIndexes = Honey_LegIndices_DC;
	KnucklesWeldInfo[19].ModelB = v2;
	KnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	KnucklesWeldInfo[19].WeldType = 2;
	KnucklesWeldInfo[19].anonymous_5 = 0;
	KnucklesWeldInfo[19].VertexBuffer = 0;
	KnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	KnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	KnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[20].WeldType = 2;
	KnucklesWeldInfo[20].anonymous_5 = 0;
	KnucklesWeldInfo[20].VertexBuffer = 0;
	KnucklesWeldInfo[20].VertIndexes = Honey_ShoeIndices_DC;
	KnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	KnucklesWeldInfo[21].ModelB = KNUCKLES_OBJECTS[41];
	KnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	KnucklesWeldInfo[21].WeldType = 2;
	KnucklesWeldInfo[21].anonymous_5 = 0;
	KnucklesWeldInfo[21].VertexBuffer = 0;
	KnucklesWeldInfo[21].VertIndexes = Honey_ShoeIndices_DC;
	KnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	KnucklesWeldInfo[22].ModelB = KNUCKLES_OBJECTS[27];
	KnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	KnucklesWeldInfo[22].WeldType = 2;
	KnucklesWeldInfo[22].anonymous_5 = 0;
	KnucklesWeldInfo[22].VertexBuffer = 0;
	KnucklesWeldInfo[22].VertIndexes = HoneyK_HandIndices_DC;
	KnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	KnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	KnucklesWeldInfo[23].ModelB = KNUCKLES_OBJECTS[31];
	KnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	KnucklesWeldInfo[23].WeldType = 2;
	KnucklesWeldInfo[23].anonymous_5 = 0;
	KnucklesWeldInfo[23].VertexBuffer = 0;
	KnucklesWeldInfo[23].VertIndexes = HoneyK_HandIndices_DC;
	KnucklesWeldInfo[24].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[24].ModelA = KNUCKLES_OBJECTS[5];
	KnucklesWeldInfo[24].ModelB = 0;
	KnucklesWeldInfo[24].VertexPairCount = 2;
	KnucklesWeldInfo[24].WeldType = 4;
	KnucklesWeldInfo[24].anonymous_5 = 0;
	KnucklesWeldInfo[24].VertexBuffer = 0;
	KnucklesWeldInfo[24].VertIndexes = 0;
	KnucklesWeldInfo[25].BaseModel = *KNUCKLES_OBJECTS;
	KnucklesWeldInfo[25].ModelA = KNUCKLES_OBJECTS[9];
	KnucklesWeldInfo[25].ModelB = 0;
	KnucklesWeldInfo[25].VertexPairCount = 2;
	KnucklesWeldInfo[25].WeldType = 5;
	KnucklesWeldInfo[25].anonymous_5 = 0;
	KnucklesWeldInfo[25].VertexBuffer = 0;
	KnucklesWeldInfo[25].VertIndexes = 0;
	KnucklesWeldInfo[26].BaseModel = *KNUCKLES_OBJECTS;
	v3 = KNUCKLES_OBJECTS[17];
	KnucklesWeldInfo[26].ModelB = 0;
	KnucklesWeldInfo[26].VertexPairCount = 0;
	KnucklesWeldInfo[26].anonymous_5 = 0;
	KnucklesWeldInfo[26].VertexBuffer = 0;
	KnucklesWeldInfo[26].VertIndexes = 0;
	KnucklesWeldInfo[26].ModelA = v3;
	KnucklesWeldInfo[26].WeldType = 6;
	KnucklesWeldInfo[27].BaseModel = *KNUCKLES_OBJECTS;
	v4 = KNUCKLES_OBJECTS[19];
	KnucklesWeldInfo[27].ModelB = 0;
	KnucklesWeldInfo[27].VertexPairCount = 0;
	KnucklesWeldInfo[27].anonymous_5 = 0;
	KnucklesWeldInfo[27].VertexBuffer = 0;
	KnucklesWeldInfo[27].VertIndexes = 0;
	KnucklesWeldInfo[27].ModelA = v4;
	KnucklesWeldInfo[27].WeldType = 7;
	KnucklesWeldInfo[28].BaseModel = *KNUCKLES_OBJECTS;
	v5 = KNUCKLES_OBJECTS[54];
	KnucklesWeldInfo[28].ModelB = 0;
	KnucklesWeldInfo[28].VertexPairCount = 0;
	KnucklesWeldInfo[28].anonymous_5 = 0;
	KnucklesWeldInfo[28].VertexBuffer = 0;
	KnucklesWeldInfo[28].VertIndexes = 0;
	KnucklesWeldInfo[29].BaseModel = 0;
	KnucklesWeldInfo[29].ModelA = 0;
	KnucklesWeldInfo[29].ModelB = 0;
	KnucklesWeldInfo[29].VertexPairCount = 0;
	KnucklesWeldInfo[29].VertexBuffer = 0;
	KnucklesWeldInfo[28].ModelA = v5;
	KnucklesWeldInfo[28].WeldType = 8;
	KnucklesWeldInfo[29].VertIndexes = 0;
}

void __cdecl InitNPCKnucklesWeldInfo_mod()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebx@1
	NJS_OBJECT* v4; // esi@1
	NJS_OBJECT* v5; // eax@1

	NPCKnucklesWeldInfo[0].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[0].ModelA = KNUCKLES_OBJECTS[2];
	NPCKnucklesWeldInfo[0].ModelB = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[0].anonymous_5 = 0;
	NPCKnucklesWeldInfo[0].VertexBuffer = 0;
	NPCKnucklesWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[0].WeldType = 2;
	NPCKnucklesWeldInfo[0].VertIndexes = Honey_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[1].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[1].ModelA = KNUCKLES_OBJECTS[3];
	NPCKnucklesWeldInfo[1].ModelB = KNUCKLES_OBJECTS[4];
	NPCKnucklesWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[1].WeldType = 2;
	NPCKnucklesWeldInfo[1].anonymous_5 = 0;
	NPCKnucklesWeldInfo[1].VertexBuffer = 0;
	NPCKnucklesWeldInfo[1].VertIndexes = Honey_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[2].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[2].ModelA = KNUCKLES_OBJECTS[6];
	v0 = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[2].VertIndexes = Honey_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[2].ModelB = v0;
	NPCKnucklesWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[2].WeldType = 2;
	NPCKnucklesWeldInfo[2].anonymous_5 = 0;
	NPCKnucklesWeldInfo[2].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[3].ModelA = KNUCKLES_OBJECTS[7];
	NPCKnucklesWeldInfo[3].ModelB = KNUCKLES_OBJECTS[8];
	NPCKnucklesWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[3].WeldType = 2;
	NPCKnucklesWeldInfo[3].anonymous_5 = 0;
	NPCKnucklesWeldInfo[3].VertexBuffer = 0;
	NPCKnucklesWeldInfo[3].VertIndexes = Honey_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[4].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[4].ModelA = KNUCKLES_OBJECTS[10];
	NPCKnucklesWeldInfo[4].ModelB = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[4].WeldType = 2;
	NPCKnucklesWeldInfo[4].anonymous_5 = 0;
	NPCKnucklesWeldInfo[4].VertexBuffer = 0;
	NPCKnucklesWeldInfo[4].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[5].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[5].ModelA = KNUCKLES_OBJECTS[11];
	NPCKnucklesWeldInfo[5].ModelB = KNUCKLES_OBJECTS[12];
	NPCKnucklesWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[5].WeldType = 2;
	NPCKnucklesWeldInfo[5].anonymous_5 = 0;
	NPCKnucklesWeldInfo[5].VertexBuffer = 0;
	NPCKnucklesWeldInfo[5].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[6].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[6].ModelA = KNUCKLES_OBJECTS[13];
	NPCKnucklesWeldInfo[6].ModelB = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[6].WeldType = 2;
	NPCKnucklesWeldInfo[6].anonymous_5 = 0;
	NPCKnucklesWeldInfo[6].VertexBuffer = 0;
	NPCKnucklesWeldInfo[6].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[7].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[7].ModelA = KNUCKLES_OBJECTS[14];
	NPCKnucklesWeldInfo[7].ModelB = KNUCKLES_OBJECTS[15];
	NPCKnucklesWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[7].WeldType = 2;
	NPCKnucklesWeldInfo[7].anonymous_5 = 0;
	NPCKnucklesWeldInfo[7].VertexBuffer = 0;
	NPCKnucklesWeldInfo[7].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[8].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[8].ModelA = KNUCKLES_OBJECTS[16];
	NPCKnucklesWeldInfo[8].ModelB = KNUCKLES_OBJECTS[17];
	NPCKnucklesWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[8].WeldType = 2;
	NPCKnucklesWeldInfo[8].anonymous_5 = 0;
	NPCKnucklesWeldInfo[8].VertexBuffer = 0;
	NPCKnucklesWeldInfo[8].VertIndexes = Honey_ShoeIndices_DC;
	NPCKnucklesWeldInfo[9].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[9].ModelA = KNUCKLES_OBJECTS[18];
	v1 = KNUCKLES_OBJECTS[19];
	NPCKnucklesWeldInfo[9].VertIndexes = Honey_ShoeIndices_DC;
	NPCKnucklesWeldInfo[9].ModelB = v1;
	NPCKnucklesWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[9].WeldType = 2;
	NPCKnucklesWeldInfo[9].anonymous_5 = 0;
	NPCKnucklesWeldInfo[9].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[10].ModelA = KNUCKLES_OBJECTS[20];
	NPCKnucklesWeldInfo[10].ModelB = KNUCKLES_OBJECTS[5];
	NPCKnucklesWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[10].WeldType = 2;
	NPCKnucklesWeldInfo[10].anonymous_5 = 0;
	NPCKnucklesWeldInfo[10].VertexBuffer = 0;
	NPCKnucklesWeldInfo[10].VertIndexes = HoneyK_HandIndices_DC;
	NPCKnucklesWeldInfo[11].BaseModel = *KNUCKLES_OBJECTS;
	NPCKnucklesWeldInfo[11].ModelA = KNUCKLES_OBJECTS[22];
	NPCKnucklesWeldInfo[11].ModelB = KNUCKLES_OBJECTS[9];
	NPCKnucklesWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[11].WeldType = 2;
	NPCKnucklesWeldInfo[11].anonymous_5 = 0;
	NPCKnucklesWeldInfo[11].VertexBuffer = 0;
	NPCKnucklesWeldInfo[11].VertIndexes = HoneyK_HandIndices_DC;
	NPCKnucklesWeldInfo[12].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[12].ModelA = KNUCKLES_OBJECTS[24];
	NPCKnucklesWeldInfo[12].ModelB = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[12].WeldType = 2;
	NPCKnucklesWeldInfo[12].anonymous_5 = 0;
	NPCKnucklesWeldInfo[12].VertexBuffer = 0;
	NPCKnucklesWeldInfo[12].VertIndexes = Honey_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[13].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[13].ModelA = KNUCKLES_OBJECTS[25];
	NPCKnucklesWeldInfo[13].ModelB = KNUCKLES_OBJECTS[26];
	NPCKnucklesWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[13].WeldType = 2;
	NPCKnucklesWeldInfo[13].anonymous_5 = 0;
	NPCKnucklesWeldInfo[13].VertexBuffer = 0;
	NPCKnucklesWeldInfo[13].VertIndexes = Honey_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[14].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[14].ModelA = KNUCKLES_OBJECTS[28];
	NPCKnucklesWeldInfo[14].ModelB = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[14].WeldType = 2;
	NPCKnucklesWeldInfo[14].anonymous_5 = 0;
	NPCKnucklesWeldInfo[14].VertexBuffer = 0;
	NPCKnucklesWeldInfo[14].VertIndexes = Honey_UpperArmIndices_DC;
	NPCKnucklesWeldInfo[15].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[15].ModelA = KNUCKLES_OBJECTS[29];
	NPCKnucklesWeldInfo[15].ModelB = KNUCKLES_OBJECTS[30];
	NPCKnucklesWeldInfo[15].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	NPCKnucklesWeldInfo[15].WeldType = 2;
	NPCKnucklesWeldInfo[15].anonymous_5 = 0;
	NPCKnucklesWeldInfo[15].VertexBuffer = 0;
	NPCKnucklesWeldInfo[15].VertIndexes = Honey_LowerArmIndices_DC;
	NPCKnucklesWeldInfo[16].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[16].ModelA = KNUCKLES_OBJECTS[32];
	NPCKnucklesWeldInfo[16].ModelB = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[16].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[16].WeldType = 2;
	NPCKnucklesWeldInfo[16].anonymous_5 = 0;
	NPCKnucklesWeldInfo[16].VertexBuffer = 0;
	NPCKnucklesWeldInfo[16].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[17].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[17].ModelA = KNUCKLES_OBJECTS[33];
	NPCKnucklesWeldInfo[17].ModelB = KNUCKLES_OBJECTS[34];
	NPCKnucklesWeldInfo[17].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[17].WeldType = 2;
	NPCKnucklesWeldInfo[17].anonymous_5 = 0;
	NPCKnucklesWeldInfo[17].VertexBuffer = 0;
	NPCKnucklesWeldInfo[17].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[18].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[18].ModelA = KNUCKLES_OBJECTS[35];
	NPCKnucklesWeldInfo[18].ModelB = KNUCKLES_OBJECTS[36];
	NPCKnucklesWeldInfo[18].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[18].WeldType = 2;
	NPCKnucklesWeldInfo[18].anonymous_5 = 0;
	NPCKnucklesWeldInfo[18].VertexBuffer = 0;
	NPCKnucklesWeldInfo[18].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[19].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[19].ModelA = KNUCKLES_OBJECTS[36];
	v2 = KNUCKLES_OBJECTS[37];
	NPCKnucklesWeldInfo[19].anonymous_5 = 0;
	NPCKnucklesWeldInfo[19].VertexBuffer = 0;
	NPCKnucklesWeldInfo[19].VertIndexes = Honey_LegIndices_DC;
	NPCKnucklesWeldInfo[19].ModelB = v2;
	NPCKnucklesWeldInfo[19].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCKnucklesWeldInfo[19].WeldType = 2;
	NPCKnucklesWeldInfo[20].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[20].ModelA = KNUCKLES_OBJECTS[38];
	NPCKnucklesWeldInfo[20].ModelB = KNUCKLES_OBJECTS[39];
	NPCKnucklesWeldInfo[20].anonymous_5 = 0;
	NPCKnucklesWeldInfo[20].VertexBuffer = 0;
	NPCKnucklesWeldInfo[20].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[20].WeldType = 2;
	NPCKnucklesWeldInfo[20].VertIndexes = Honey_ShoeIndices_DC;
	NPCKnucklesWeldInfo[21].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[21].ModelA = KNUCKLES_OBJECTS[40];
	v3 = KNUCKLES_OBJECTS[41];
	NPCKnucklesWeldInfo[21].anonymous_5 = 0;
	NPCKnucklesWeldInfo[21].VertexBuffer = 0;
	NPCKnucklesWeldInfo[21].ModelB = v3;
	NPCKnucklesWeldInfo[21].VertIndexes = Honey_ShoeIndices_DC;
	NPCKnucklesWeldInfo[21].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	NPCKnucklesWeldInfo[21].WeldType = 2;
	NPCKnucklesWeldInfo[22].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[22].ModelA = KNUCKLES_OBJECTS[42];
	v4 = KNUCKLES_OBJECTS[27];
	NPCKnucklesWeldInfo[22].anonymous_5 = 0;
	NPCKnucklesWeldInfo[22].VertexBuffer = 0;
	NPCKnucklesWeldInfo[22].ModelB = v4;
	NPCKnucklesWeldInfo[22].VertIndexes = HoneyK_HandIndices_DC;
	NPCKnucklesWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[22].WeldType = 2;
	NPCKnucklesWeldInfo[23].BaseModel = KNUCKLES_OBJECTS[1];
	NPCKnucklesWeldInfo[23].ModelA = KNUCKLES_OBJECTS[44];
	v5 = KNUCKLES_OBJECTS[31];
	NPCKnucklesWeldInfo[23].anonymous_5 = 0;
	NPCKnucklesWeldInfo[23].VertexBuffer = 0;
	NPCKnucklesWeldInfo[24].BaseModel = 0;
	NPCKnucklesWeldInfo[24].ModelA = 0;
	NPCKnucklesWeldInfo[23].VertIndexes = HoneyK_HandIndices_DC;
	NPCKnucklesWeldInfo[24].ModelB = 0;
	NPCKnucklesWeldInfo[24].VertexPairCount = 0;
	NPCKnucklesWeldInfo[24].VertexBuffer = 0;
	NPCKnucklesWeldInfo[23].ModelB = v5;
	NPCKnucklesWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(HoneyK_HandIndices_DC) / 2);
	NPCKnucklesWeldInfo[23].WeldType = 2;
	NPCKnucklesWeldInfo[24].VertIndexes = 0;
}

void __cdecl InitAmyWeldInfo_mod()
{
	NJS_OBJECT* v0; // edi@1
	NJS_OBJECT* v1; // edi@1
	NJS_OBJECT* v2; // edi@1
	NJS_OBJECT* v3; // edi@1
	NJS_OBJECT* v4; // esi@1
	NJS_OBJECT* v5; // edx@1
	NJS_OBJECT* v6; // edx@1
	NJS_OBJECT* v7; // eax@1

	AmyWeldInfo[0].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[0].ModelA = AMY_OBJECTS[6];
	AmyWeldInfo[0].ModelB = AMY_OBJECTS[7];
	AmyWeldInfo[0].anonymous_5 = 0;
	AmyWeldInfo[0].VertexBuffer = 0;
	AmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	AmyWeldInfo[0].WeldType = 2;
	AmyWeldInfo[0].VertIndexes = Honey_UpperArmIndices_DC;
	AmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
	AmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
	AmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	AmyWeldInfo[1].WeldType = 2;
	AmyWeldInfo[1].anonymous_5 = 0;
	AmyWeldInfo[1].VertexBuffer = 0;
	AmyWeldInfo[1].VertIndexes = Honey_LowerArmIndices_DC;
	AmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
	AmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
	AmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	AmyWeldInfo[2].WeldType = 2;
	AmyWeldInfo[2].anonymous_5 = 0;
	AmyWeldInfo[2].VertexBuffer = 0;
	AmyWeldInfo[2].VertIndexes = Honey_UpperArmIndices_DC;
	AmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
	v0 = AMY_OBJECTS[11];
	AmyWeldInfo[3].VertIndexes = Honey_LowerArmIndices_DC;
	AmyWeldInfo[3].ModelB = v0;
	AmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	AmyWeldInfo[3].WeldType = 2;
	AmyWeldInfo[3].anonymous_5 = 0;
	AmyWeldInfo[3].VertexBuffer = 0;
	AmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
	AmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
	AmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	AmyWeldInfo[4].WeldType = 2;
	AmyWeldInfo[4].anonymous_5 = 0;
	AmyWeldInfo[4].VertexBuffer = 0;
	AmyWeldInfo[4].VertIndexes = Honey_LegIndices_DC;
	AmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
	AmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
	AmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	AmyWeldInfo[5].WeldType = 2;
	AmyWeldInfo[5].anonymous_5 = 0;
	AmyWeldInfo[5].VertIndexes = Honey_LegIndices_DC;
	AmyWeldInfo[5].VertexBuffer = 0;
	AmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
	v1 = AMY_OBJECTS[16];
	AmyWeldInfo[6].VertIndexes = Honey_LegIndices_DC;
	AmyWeldInfo[6].ModelB = v1;
	AmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	AmyWeldInfo[6].WeldType = 2;
	AmyWeldInfo[6].anonymous_5 = 0;
	AmyWeldInfo[6].VertexBuffer = 0;
	AmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
	v2 = AMY_OBJECTS[17];
	AmyWeldInfo[7].VertIndexes = Honey_LegIndices_DC;
	AmyWeldInfo[7].ModelB = v2;
	AmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	AmyWeldInfo[7].WeldType = 2;
	AmyWeldInfo[7].anonymous_5 = 0;
	AmyWeldInfo[7].VertexBuffer = 0;
	AmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
	AmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
	AmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	AmyWeldInfo[8].WeldType = 2;
	AmyWeldInfo[8].anonymous_5 = 0;
	AmyWeldInfo[8].VertexBuffer = 0;
	AmyWeldInfo[8].VertIndexes = Honey_ShoeIndices_DC;
	AmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
	v3 = AMY_OBJECTS[21];
	AmyWeldInfo[9].VertIndexes = Honey_ShoeIndices_DC;
	AmyWeldInfo[9].ModelB = v3;
	AmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	AmyWeldInfo[9].WeldType = 2;
	AmyWeldInfo[9].anonymous_5 = 0;
	AmyWeldInfo[9].VertexBuffer = 0;
	AmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
	AmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
	AmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Honey_HandIndices_DC) / 2);
	AmyWeldInfo[10].WeldType = 2;
	AmyWeldInfo[10].anonymous_5 = 0;
	AmyWeldInfo[10].VertexBuffer = 0;
	AmyWeldInfo[10].VertIndexes = Honey_HandIndices_DC;
	AmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
	AmyWeldInfo[11].ModelB = AMY_OBJECTS[25];
	AmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Honey_HandIndices_DC) / 2);
	AmyWeldInfo[11].WeldType = 2;
	AmyWeldInfo[11].anonymous_5 = 0;
	AmyWeldInfo[11].VertexBuffer = 0;
	AmyWeldInfo[11].VertIndexes = Honey_HandIndices_DC;
	AmyWeldInfo[12].BaseModel = *AMY_OBJECTS;
	AmyWeldInfo[12].ModelA = AMY_OBJECTS[23];
	AmyWeldInfo[12].ModelB = 0;
	AmyWeldInfo[12].anonymous_5 = 0;
	AmyWeldInfo[12].VertexBuffer = 0;
	AmyWeldInfo[12].VertIndexes = 0;
	AmyWeldInfo[12].WeldType = 4;
	AmyWeldInfo[12].VertexPairCount = 2;
	AmyWeldInfo[13].BaseModel = *AMY_OBJECTS;
	v4 = AMY_OBJECTS[25];
	AmyWeldInfo[13].ModelB = 0;
	AmyWeldInfo[13].anonymous_5 = 0;
	AmyWeldInfo[13].VertexBuffer = 0;
	AmyWeldInfo[13].VertIndexes = 0;
	AmyWeldInfo[13].ModelA = v4;
	AmyWeldInfo[13].VertexPairCount = 2;
	AmyWeldInfo[13].WeldType = 5;
	AmyWeldInfo[14].BaseModel = *AMY_OBJECTS;
	v5 = AMY_OBJECTS[19];
	AmyWeldInfo[14].ModelB = 0;
	AmyWeldInfo[14].VertexPairCount = 0;
	AmyWeldInfo[14].anonymous_5 = 0;
	AmyWeldInfo[14].VertexBuffer = 0;
	AmyWeldInfo[14].VertIndexes = 0;
	AmyWeldInfo[14].ModelA = v5;
	AmyWeldInfo[14].WeldType = 6;
	AmyWeldInfo[15].BaseModel = *AMY_OBJECTS;
	v6 = AMY_OBJECTS[21];
	AmyWeldInfo[15].ModelB = 0;
	AmyWeldInfo[15].VertexPairCount = 0;
	AmyWeldInfo[15].anonymous_5 = 0;
	AmyWeldInfo[15].VertexBuffer = 0;
	AmyWeldInfo[15].VertIndexes = 0;
	AmyWeldInfo[15].ModelA = v6;
	AmyWeldInfo[15].WeldType = 7;
	AmyWeldInfo[16].BaseModel = *AMY_OBJECTS;
	v7 = AMY_OBJECTS[30];
	AmyWeldInfo[16].ModelB = 0;
	AmyWeldInfo[16].VertexPairCount = 0;
	AmyWeldInfo[16].anonymous_5 = 0;
	AmyWeldInfo[16].VertexBuffer = 0;
	AmyWeldInfo[16].VertIndexes = 0;
	AmyWeldInfo[17].BaseModel = 0;
	AmyWeldInfo[17].ModelA = 0;
	AmyWeldInfo[17].ModelB = 0;
	AmyWeldInfo[17].VertexPairCount = 0;
	AmyWeldInfo[17].VertexBuffer = 0;
	AmyWeldInfo[16].ModelA = v7;
	AmyWeldInfo[16].WeldType = 8;
	AmyWeldInfo[17].VertIndexes = 0;
}

void __cdecl InitNPCAmyWeldInfo_mod()
{
	NJS_OBJECT* v0; // edi@1
	NJS_OBJECT* v1; // edi@1
	NJS_OBJECT* v2; // edi@1
	NJS_OBJECT* v3; // edi@1
	NJS_OBJECT* v4; // eax@1

	NPCAmyWeldInfo[0].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[0].ModelA = AMY_OBJECTS[6];
	NPCAmyWeldInfo[0].ModelB = AMY_OBJECTS[7];
	NPCAmyWeldInfo[0].anonymous_5 = 0;
	NPCAmyWeldInfo[0].VertexBuffer = 0;
	NPCAmyWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	NPCAmyWeldInfo[0].WeldType = 2;
	NPCAmyWeldInfo[0].VertIndexes = Honey_UpperArmIndices_DC;
	NPCAmyWeldInfo[1].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[1].ModelA = AMY_OBJECTS[7];
	NPCAmyWeldInfo[1].ModelB = AMY_OBJECTS[8];
	NPCAmyWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	NPCAmyWeldInfo[1].WeldType = 2;
	NPCAmyWeldInfo[1].anonymous_5 = 0;
	NPCAmyWeldInfo[1].VertexBuffer = 0;
	NPCAmyWeldInfo[1].VertIndexes = Honey_LowerArmIndices_DC;
	NPCAmyWeldInfo[2].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[2].ModelA = AMY_OBJECTS[9];
	NPCAmyWeldInfo[2].ModelB = AMY_OBJECTS[10];
	NPCAmyWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Honey_UpperArmIndices_DC) / 2);
	NPCAmyWeldInfo[2].WeldType = 2;
	NPCAmyWeldInfo[2].anonymous_5 = 0;
	NPCAmyWeldInfo[2].VertexBuffer = 0;
	NPCAmyWeldInfo[2].VertIndexes = Honey_UpperArmIndices_DC;
	NPCAmyWeldInfo[3].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[3].ModelA = AMY_OBJECTS[10];
	v0 = AMY_OBJECTS[11];
	NPCAmyWeldInfo[3].VertIndexes = Honey_LowerArmIndices_DC;
	NPCAmyWeldInfo[3].ModelB = v0;
	NPCAmyWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LowerArmIndices_DC) / 2);
	NPCAmyWeldInfo[3].WeldType = 2;
	NPCAmyWeldInfo[3].anonymous_5 = 0;
	NPCAmyWeldInfo[3].VertexBuffer = 0;
	NPCAmyWeldInfo[4].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[4].ModelA = AMY_OBJECTS[12];
	NPCAmyWeldInfo[4].ModelB = AMY_OBJECTS[13];
	NPCAmyWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCAmyWeldInfo[4].WeldType = 2;
	NPCAmyWeldInfo[4].anonymous_5 = 0;
	NPCAmyWeldInfo[4].VertexBuffer = 0;
	NPCAmyWeldInfo[4].VertIndexes = Honey_LegIndices_DC;
	NPCAmyWeldInfo[5].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[5].ModelA = AMY_OBJECTS[13];
	NPCAmyWeldInfo[5].ModelB = AMY_OBJECTS[14];
	NPCAmyWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCAmyWeldInfo[5].WeldType = 2;
	NPCAmyWeldInfo[5].anonymous_5 = 0;
	NPCAmyWeldInfo[5].VertexBuffer = 0;
	NPCAmyWeldInfo[5].VertIndexes = Honey_LegIndices_DC;
	NPCAmyWeldInfo[6].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[6].ModelA = AMY_OBJECTS[15];
	v1 = AMY_OBJECTS[16];
	NPCAmyWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCAmyWeldInfo[6].anonymous_5 = 0;
	NPCAmyWeldInfo[6].VertexBuffer = 0;
	NPCAmyWeldInfo[6].VertIndexes = Honey_LegIndices_DC;
	NPCAmyWeldInfo[6].ModelB = v1;
	NPCAmyWeldInfo[6].WeldType = 2;
	NPCAmyWeldInfo[7].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[7].ModelA = AMY_OBJECTS[16];
	v2 = AMY_OBJECTS[17];
	NPCAmyWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Honey_LegIndices_DC) / 2);
	NPCAmyWeldInfo[7].anonymous_5 = 0;
	NPCAmyWeldInfo[7].VertexBuffer = 0;
	NPCAmyWeldInfo[7].VertIndexes = Honey_LegIndices_DC;
	NPCAmyWeldInfo[7].ModelB = v2;
	NPCAmyWeldInfo[7].WeldType = 2;
	NPCAmyWeldInfo[8].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[8].ModelA = AMY_OBJECTS[18];
	NPCAmyWeldInfo[8].ModelB = AMY_OBJECTS[19];
	NPCAmyWeldInfo[8].anonymous_5 = 0;
	NPCAmyWeldInfo[8].VertexBuffer = 0;
	NPCAmyWeldInfo[8].WeldType = 2;
	NPCAmyWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	NPCAmyWeldInfo[8].VertIndexes = Honey_ShoeIndices_DC;
	NPCAmyWeldInfo[9].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[9].ModelA = AMY_OBJECTS[20];
	v3 = AMY_OBJECTS[21];
	NPCAmyWeldInfo[9].anonymous_5 = 0;
	NPCAmyWeldInfo[9].VertexBuffer = 0;
	NPCAmyWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Honey_ShoeIndices_DC) / 2);
	NPCAmyWeldInfo[9].VertIndexes = Honey_ShoeIndices_DC;
	NPCAmyWeldInfo[9].ModelB = v3;
	NPCAmyWeldInfo[9].WeldType = 2;
	NPCAmyWeldInfo[10].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[10].ModelA = AMY_OBJECTS[22];
	NPCAmyWeldInfo[10].ModelB = AMY_OBJECTS[23];
	NPCAmyWeldInfo[10].anonymous_5 = 0;
	NPCAmyWeldInfo[10].VertexBuffer = 0;
	NPCAmyWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Honey_HandIndices_DC) / 2);
	NPCAmyWeldInfo[10].WeldType = 2;
	NPCAmyWeldInfo[10].VertIndexes = Honey_HandIndices_DC;
	NPCAmyWeldInfo[11].BaseModel = *AMY_OBJECTS;
	NPCAmyWeldInfo[11].ModelA = AMY_OBJECTS[24];
	v4 = AMY_OBJECTS[25];
	NPCAmyWeldInfo[11].anonymous_5 = 0;
	NPCAmyWeldInfo[11].VertexBuffer = 0;
	NPCAmyWeldInfo[12].BaseModel = 0;
	NPCAmyWeldInfo[12].ModelA = 0;
	NPCAmyWeldInfo[11].ModelB = v4;
	NPCAmyWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Honey_HandIndices_DC) / 2);
	NPCAmyWeldInfo[11].WeldType = 2;
	NPCAmyWeldInfo[11].VertIndexes = Honey_HandIndices_DC;
	NPCAmyWeldInfo[12].ModelB = 0;
	NPCAmyWeldInfo[12].VertexPairCount = 0;
	NPCAmyWeldInfo[12].VertexBuffer = 0;
	NPCAmyWeldInfo[12].VertIndexes = 0;
}

void Init_OverKnux()
{
	KNUCKLES_OBJECTS[0] = &object_002E23B0;
	KNUCKLES_OBJECTS[1] = &object_002EEE50;
	KNUCKLES_OBJECTS[2] = &object_002DB8A4;
	KNUCKLES_OBJECTS[3] = &object_002DBA34;
	KNUCKLES_OBJECTS[4] = &object_002DD0AC;
	KNUCKLES_OBJECTS[5] = &object_002DC244;
	KNUCKLES_OBJECTS[6] = &object_002D9E5C;
	KNUCKLES_OBJECTS[7] = &object_002D9FEC;
	KNUCKLES_OBJECTS[8] = &object_002DB5F4;
	KNUCKLES_OBJECTS[9] = &object_002DAB34;
	KNUCKLES_OBJECTS[10] = &object_002D876C;
	KNUCKLES_OBJECTS[11] = &object_002D88FC;
	KNUCKLES_OBJECTS[12] = &object_002D9BB0;
	KNUCKLES_OBJECTS[13] = &object_002D6FE4;
	KNUCKLES_OBJECTS[14] = &object_002D7174;
	KNUCKLES_OBJECTS[15] = &object_002D8438;
	KNUCKLES_OBJECTS[16] = &object_002D9754;
	KNUCKLES_OBJECTS[17] = &object_002D9088;
	KNUCKLES_OBJECTS[18] = &object_002D7FDC;
	KNUCKLES_OBJECTS[19] = &object_002D7900;
	KNUCKLES_OBJECTS[20] = &object_002DC94C;
	KNUCKLES_OBJECTS[21] = &object_002DC244;
	KNUCKLES_OBJECTS[22] = &object_002DAEE4;
	KNUCKLES_OBJECTS[23] = &object_002DAB34;
	KNUCKLES_OBJECTS[24] = &object_002E8324;
	KNUCKLES_OBJECTS[25] = &object_002E84B4;
	KNUCKLES_OBJECTS[26] = &object_002E9B2C;
	KNUCKLES_OBJECTS[27] = &object_002E8CC4;
	KNUCKLES_OBJECTS[28] = &object_002E68DC;
	KNUCKLES_OBJECTS[29] = &object_002E6A6C;
	KNUCKLES_OBJECTS[30] = &object_002E8074;
	KNUCKLES_OBJECTS[31] = &object_002E75B4;
	KNUCKLES_OBJECTS[32] = &object_002E51EC;
	KNUCKLES_OBJECTS[33] = &object_002E537C;
	KNUCKLES_OBJECTS[34] = &object_002E6630;
	KNUCKLES_OBJECTS[35] = &object_002E3A64;
	KNUCKLES_OBJECTS[36] = &object_002E3BF4;
	KNUCKLES_OBJECTS[37] = &object_002E4EB8;
	KNUCKLES_OBJECTS[38] = &object_002E61D4;
	KNUCKLES_OBJECTS[39] = &object_002E5B08;
	KNUCKLES_OBJECTS[40] = &object_002E4A5C;
	KNUCKLES_OBJECTS[41] = &object_002E4380;
	KNUCKLES_OBJECTS[42] = &object_002E93CC;
	KNUCKLES_OBJECTS[43] = &object_002E8CC4;
	KNUCKLES_OBJECTS[44] = &object_002E7964;
	KNUCKLES_OBJECTS[45] = &object_002E75B4;
	KNUCKLES_OBJECTS[49] = &object_002E191C;
	KNUCKLES_OBJECTS[50] = &object_002EE3BC;
	KNUCKLES_OBJECTS[51] = &object_002E21A8;
	KNUCKLES_OBJECTS[52] = &object_002E2070;
	KNUCKLES_OBJECTS[53] = &object_002E1C78;
	KNUCKLES_OBJECTS[54] = &object_002E1D14;
	KNUCKLES_OBJECTS[55] = &object_002E191C;
	KNUCKLES_OBJECTS[58] = &object_002DB5F4;
	KNUCKLES_OBJECTS[59] = &object_002DAEE4;
	KNUCKLES_OBJECTS[60] = &object_002DAB34;
	KNUCKLES_OBJECTS[61] = &object_002DA324;
	KNUCKLES_OBJECTS[62] = &object_002DD0AC;
	KNUCKLES_OBJECTS[63] = &object_002DC94C;
	KNUCKLES_OBJECTS[64] = &object_002DC244;
	KNUCKLES_OBJECTS[65] = &object_002DC59C;
	KNUCKLES_OBJECTS[66] = &object_002E8074;
	KNUCKLES_OBJECTS[67] = &object_002E7964;
	KNUCKLES_OBJECTS[68] = &object_002E75B4;
	KNUCKLES_OBJECTS[69] = &object_002E6DA4;
	KNUCKLES_OBJECTS[70] = &object_002E9B2C;
	KNUCKLES_OBJECTS[71] = &object_002E93CC;
	KNUCKLES_OBJECTS[72] = &object_002E8CC4;
	KNUCKLES_OBJECTS[73] = &object_002E901C;
	KNUCKLES_ACTIONS[0]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[1]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[2]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[3]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[4]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[5]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[6]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[7]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[9]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[10]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[11]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[12]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[13]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[14]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[15]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[16]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[17]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[18]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[19]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[20]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[21]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[22]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[23]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[24]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[25]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[26]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[27]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[28]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[29]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[30]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[31]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[32]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[33]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[34]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[35]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[36]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[37]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[38]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[39]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[40]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[41]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[42]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[43]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[44]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[45]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[46]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[47]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[48]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[49]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[50]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[51]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[52]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[53]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[54]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[55]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[56]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[57]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[58]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[59]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[60]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[61]->object = &object_002F8530;
	KNUCKLES_ACTIONS[62]->object = &object_002F0E24;
	KNUCKLES_ACTIONS[63]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[64]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[65]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[66]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[67]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[68]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[69]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[70]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[71]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[72]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[73]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[74]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[75]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[76]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[77]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[78]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[79]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[80]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[81]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[82]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[83]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[84]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[85]->object = &object_002EEE50;
	KNUCKLES_ACTIONS[86]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[87]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[88]->object = &object_002E23B0;
	KNUCKLES_ACTIONS[89]->object = &object_002E23B0;
	KNUCKLES_MODELS[0] = &attach_003298C8;
	KNUCKLES_MODELS[1] = &attach_00329FF8;
	KNUCKLES_MODELS[2] = &attach_0032A6F0;
	KNUCKLES_MODELS[3] = &attach_0032ADF8;
	KNUCKLES_MODELS[4] = &attach_002E18F0;
	KNUCKLES_MODELS[5] = &attach_002EE390;
	KNUCKLES_MODELS[6] = &attach_002FC558;
	KNUCKLES_MODELS[7] = &attach_002DB5C8;
	KNUCKLES_MODELS[8] = &attach_002DAEB8;
	KNUCKLES_MODELS[9] = &attach_002DAB08;
	KNUCKLES_MODELS[10] = &attach_002DA2F8;
	KNUCKLES_MODELS[11] = &attach_002DD080;
	KNUCKLES_MODELS[12] = &attach_002DC920;
	KNUCKLES_MODELS[13] = &attach_002DC218;
	KNUCKLES_MODELS[14] = &attach_002DC570;
	KNUCKLES_MODELS[15] = &attach_0032B488;
	KNUCKLES_MODELS[16] = &attach_0032C2F8;
	KNUCKLES_MODELS[17] = &attach_0032BF48;
	KNUCKLES_MODELS[18] = &attach_0032B7C0;
	KNUCKLES_MODELS[19] = &attach_0032C950;
	KNUCKLES_MODELS[20] = &attach_0032D7E0;
	KNUCKLES_MODELS[21] = &attach_0032D430;
	KNUCKLES_MODELS[22] = &attach_0032CCA8;
	WriteJump((void*)0x007C94D0, InitKnucklesWeldInfo_mod);
	WriteJump((void*)0x007C9C80, InitNPCKnucklesWeldInfo_mod);
	WriteData((uint16_t**)0x0472CAC, (uint16_t*)&Honey_ShovelClawIndices_DC);
	WriteData((uint16_t**)0x0472B2C, (uint16_t*)&Honey_HandIndices_DC);
	WriteData((uint16_t**)0x0472835, (uint16_t*)&Honey_HandIndices_DC);
}

void Init_OverAmy()
{
	AMY_OBJECTS[0] = &object_00016460;
	AMY_OBJECTS[2] = &object_0000FB34;
	AMY_OBJECTS[3] = &object_0000F974;
	AMY_OBJECTS[4] = &object_000159CC;
	AMY_OBJECTS[5] = &object_00009C54;
	AMY_OBJECTS[6] = &object_0000EA74;
	AMY_OBJECTS[7] = &object_0000EC04;
	AMY_OBJECTS[8] = &object_000112C4;
	AMY_OBJECTS[9] = &object_0000CE6C;
	AMY_OBJECTS[10] = &object_0000CFFC;
	AMY_OBJECTS[11] = &object_0000D7B4;
	AMY_OBJECTS[12] = &object_0000B7D4;
	AMY_OBJECTS[13] = &object_0000B994;
	AMY_OBJECTS[14] = &object_0000CBC0;
	AMY_OBJECTS[15] = &object_0000A114;
	AMY_OBJECTS[16] = &object_0000A2D4;
	AMY_OBJECTS[17] = &object_0000B510;
	AMY_OBJECTS[18] = &object_0000C508;
	AMY_OBJECTS[19] = &object_0000BE90;
	AMY_OBJECTS[20] = &object_0000AE48;
	AMY_OBJECTS[21] = &object_0000A7D0;
	AMY_OBJECTS[22] = &object_00010AF8;
	AMY_OBJECTS[23] = &object_000108A0;
	AMY_OBJECTS[24] = &object_0000E7C8;
	AMY_OBJECTS[25] = &object_0000E570;
	AMY_OBJECTS[26] = &object_00016258;
	AMY_OBJECTS[27] = &object_00016120;
	AMY_OBJECTS[28] = &object_00015D28;
	AMY_OBJECTS[30] = &object_00015DC4;
	AMY_OBJECTS[31] = &object_000159CC;
	AMY_OBJECTS[33] = &object_000159CC;
	AMY_OBJECTS[34] = &object_00012324;
	AMY_OBJECTS[35] = &object_0001D858;
	AMY_OBJECTS[36] = &object_0000FDF8;
	AMY_OBJECTS[37] = &object_0000FB34;
	AMY_OBJECTS[38] = &object_0001D204;
	AMY_ACTIONS[0]->object = &object_00016460;
	AMY_ACTIONS[1]->object = &object_00016460;
	AMY_ACTIONS[2]->object = &object_00016460;
	AMY_ACTIONS[3]->object = &object_00016460;
	AMY_ACTIONS[4]->object = &object_00016460;
	AMY_ACTIONS[5]->object = &object_00016460;
	AMY_ACTIONS[6]->object = &object_00016460;
	AMY_ACTIONS[7]->object = &object_00016460;
	AMY_ACTIONS[8]->object = &object_00016460;
	AMY_ACTIONS[9]->object = &object_00016460;
	AMY_ACTIONS[10]->object = &object_00016460;
	AMY_ACTIONS[11]->object = &object_00016460;
	AMY_ACTIONS[12]->object = &object_00016460;
	AMY_ACTIONS[13]->object = &object_00016460;
	AMY_ACTIONS[14]->object = &object_00016460;
	AMY_ACTIONS[15]->object = &object_00016460;
	AMY_ACTIONS[16]->object = &object_00016460;
	AMY_ACTIONS[17]->object = &object_00016460;
	AMY_ACTIONS[18]->object = &object_00016460;
	AMY_ACTIONS[19]->object = &object_00016460;
	AMY_ACTIONS[20]->object = &object_00016460;
	AMY_ACTIONS[21]->object = &object_00016460;
	AMY_ACTIONS[22]->object = &object_00016460;
	AMY_ACTIONS[23]->object = &object_00016460;
	AMY_ACTIONS[24]->object = &object_00016460;
	AMY_ACTIONS[25]->object = &object_00016460;
	AMY_ACTIONS[26]->object = &object_00016460;
	AMY_ACTIONS[27]->object = &object_00016460;
	AMY_ACTIONS[28]->object = &object_00016460;
	AMY_ACTIONS[29]->object = &object_00016460;
	AMY_ACTIONS[30]->object = &object_00016460;
	AMY_ACTIONS[31]->object = &object_00016460;
	AMY_ACTIONS[32]->object = &object_00016460;
	AMY_ACTIONS[33]->object = &object_00016460;
	AMY_ACTIONS[34]->object = &object_00016460;
	AMY_ACTIONS[35]->object = &object_00016460;
	AMY_ACTIONS[36]->object = &object_00016460;
	AMY_ACTIONS[37]->object = &object_00016460;
	AMY_ACTIONS[38]->object = &object_00016460;
	AMY_ACTIONS[39]->object = &object_00016460;
	AMY_ACTIONS[40]->object = &object_00016460;
	AMY_ACTIONS[41]->object = &object_00016460;
	AMY_ACTIONS[42]->object = &object_00016460;
	AMY_ACTIONS[43]->object = &object_00016460;
	AMY_ACTIONS[44]->object = &object_00016460;
	AMY_ACTIONS[45]->object = &object_00016460;
	AMY_ACTIONS[46]->object = &object_00016460;
	AMY_ACTIONS[47]->object = &object_00016460;
	AMY_ACTIONS[48]->object = &object_00016460;
	AMY_ACTIONS[49]->object = &object_00016460;
	AMY_ACTIONS[50]->object = &object_00016460;
	AMY_ACTIONS[51]->object = &object_00016460;
	AMY_ACTIONS[52]->object = &object_00016460;
	AMY_ACTIONS[53]->object = &object_00016460;
	AMY_ACTIONS[54]->object = &object_00016460;
	AMY_ACTIONS[55]->object = &object_00016460;
	AMY_ACTIONS[56]->object = &object_00016460;
	AMY_ACTIONS[57]->object = &object_00016460;
	AMY_ACTIONS[58]->object = &object_00016460;
	AMY_ACTIONS[59]->object = &object_00016460;
	AMY_ACTIONS[60]->object = &object_00016460;
	AMY_ACTIONS[61]->object = &object_00016460;
	AMY_ACTIONS[62]->object = &object_00016460;
	AMY_ACTIONS[63]->object = &object_00016460;
	AMY_ACTIONS[64]->object = &object_00016460;
	AMY_ACTIONS[65]->object = &object_00016460;
	AMY_ACTIONS[66]->object = &object_00016460;
	AMY_ACTIONS[67]->object = &object_00016460;
	AMY_ACTIONS[68]->object = &object_00016460;
	AMY_ACTIONS[69]->object = &object_00016460;
	AMY_ACTIONS[70]->object = &object_00016460;
	AMY_ACTIONS[71]->object = &object_00016460;
	AMY_ACTIONS[72]->object = &object_00016460;
	AMY_ACTIONS[73]->object = &object_00016460;
	AMY_ACTIONS[76]->object = &object_00016460;
	AMY_ACTIONS[77]->object = &object_00016460;
	AMY_ACTIONS[78]->object = &object_00016460;
	AMY_ACTIONS[79]->object = &object_00016460;
	AMY_MODELS[1] = &attach_000159A0;
	AMY_MODELS[2] = &attach_0001C100;
	AMY_MODELS[3] = &attach_00009C28;
	AMY_MODELS[4] = &attach_00018A90;
	WriteJump((void*)0x007CCB90, InitAmyWeldInfo_mod);
	WriteJump((void*)0x007CD000, InitNPCAmyWeldInfo_mod);
}

extern "C" __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions & helperFunctions)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	EnableOverKnux = config->getBool("Characters", "EnableOverKnux", true);
	EnableOverAmy = config->getBool("Characters", "EnableOverAmy", true);
	CustomKnuxPhys = config->getBool("Physics", "CustomKnuxPhys", true);
	CustomAmyPhys = config->getBool("Physics", "CustomAmyPhys", true);

	std::string OverKnux_String = "RedK";
	OverKnux_String = config->getString("Textures", "Knux", "RedK");
	std::string OverAmy_String = "RedA";
	OverAmy_String = config->getString("Textures", "Amy", "RedA");

	if (OverKnux_String == "RedK") OverKnux = RedK;
	if (OverKnux_String == "BlueK") OverKnux = BlueK;
	if (OverAmy_String == "RedA") OverAmy = RedA;
	if (OverAmy_String == "BlueA") OverAmy = BlueA;

	HMODULE handle = GetModuleHandle(L"CHRMODELS_orig");
	NJS_OBJECT** ___KNUCKLES_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___KNUCKLES_OBJECTS");
	NJS_ACTION** ___KNUCKLES_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___KNUCKLES_ACTIONS");
	NJS_MODEL_SADX** ___KNUCKLES_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___KNUCKLES_MODELS");
	NJS_OBJECT** ___AMY_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___AMY_OBJECTS");
	NJS_ACTION** ___AMY_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___AMY_ACTIONS");
	NJS_MODEL_SADX** ___AMY_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___AMY_MODELS");

	HoneyGUI_Init();

	if (EnableOverKnux)
	{
		Init_OverKnux();
		if (CustomKnuxPhys)
		{
			*(player_parameter*)0x915674 = CustKnucklesPhysicsData;
		}
		else
		{
			*(player_parameter*)0x915674 = OrKnucklesPhysicsData;
		}

		if (OverKnux == RedK)
		{
			ReplacePVM("knuckles", "HoneyOK");
		}

		if (OverKnux == BlueK)
		{
			ReplacePVM("knuckles", "HoneyOKalt");
		}
	}

	if (EnableOverAmy)
	{
		Init_OverAmy();
		if (CustomAmyPhys)
		{
			*(player_parameter*)0x91577C = CustAmyPhysicsData;
		}

		if (OverAmy == RedA)
		{
			ReplacePVM("amy", "HoneyOA");
		}

		if (OverAmy == BlueA)
		{
			ReplacePVM("amy", "HoneyOAalt");
		}
	}
}

extern "C" __declspec(dllexport) const ModInfo SADXModInfo = { ModLoaderVer };