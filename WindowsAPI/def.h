#pragma once

//#define SINGLE(type)	public:							\
//							static type* GetInst()		\
//							{							\
//								static type mgr;		\
//								return &mgr;			\
//							}							\
//						private:						\
//							type();						\
//							~type();					


#define KEY_PREESE(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED
#define KEY_DOWN(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::DOWN
#define KEY_UP(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::UP

enum class eSceneType
{
	Logo,
	Title,
	Play,
	End,
	Tool,
	Max,
};

enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent, //≈ı∏Ì
	Black,
	Gray, //167 0 67
	White,
	End,
};

enum class eComponentType
{
	Rigidbody,
	Collider,
	Aimator,
	Sound,
	End,
};

#define _COLLIDER_LAYER 32
enum class eColliderLayer
{
	Default,

	//GameObject
	BackGround,
	Tile,
	Rock,
	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,
	NPC,
	FlameBase,
	Ground,
	Wall,
	Effect,

	//UI
	BackPack,
	UI,
	Counter,
	
	//Transition
	Transition,

	End = _COLLIDER_LAYER,
};

enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
};

enum class eUIType
{
	TPANEL,
	STEP,
	ROUND,
	LEFTBG,
	RIGHTBG,
	COUNTER,

	END,
};

union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;
};
typedef ColliderID TileID;

enum class Direction
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum class eGameObjectType
{	
	BackGround,
	Player,
	Monster,
	Rock,
	Key,
	Box,
	NPC,
	Static_Spike,
	Dynamic_Spike,
	FlameBase,
	Tile,
	Wall,
	Effect,
	Counter,
	Transition,
	None,
};


#define TILE_SIZE 32
#define TILE_SCALE 2

#define TILE_LINE_X 8
#define TILE_LINE_Y 3


