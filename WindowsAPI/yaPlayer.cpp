#include "yaPlayer.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaMissile.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaBackPack.h"
#include "yaRigidbody.h"
#include "yaUIManager.h"

namespace ya
{
	Player::Player()
		: mSpeed(1.0f)
		, mHp(100)
	{
		SetName(L"Player");
		SetPos({ 950.0f, 220.0f });
		SetScale({ 1.0f, 1.0f });

		

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Hero.bmp");
		}
		
		mAnimator = new Animator();
		//mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Idle", L"HeroIdle");


		mAnimator->CreateAnimation(L"Idle", mImage
			, Vector2(0.0f, 0.0f), Vector2(100.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 12, 0.12f);

		mAnimator->CreateAnimation(L"Move", mImage
			, Vector2(0.0f, 440.0f), Vector2(100.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 6, 0.12f);

		mAnimator->CreateAnimation(L"Attack", mImage
			, Vector2(0.0f, 220.0f), Vector2(100.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 13, 0.12f);

		mAnimator->CreateAnimation(L"Win", mImage
			, Vector2(0.0f, 440.0f), Vector2(100.0f, 130.0f)
			, Vector2(5.0f, -20.0f), 25, 0.12f);


		mAnimator->Play(L"Idle", true);

		mAnimator->FindEvents(L"Move")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Move") = std::bind(&Player::WalkComplete, this);

		mAnimator->FindEvents(L"Attack")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&Player::WalkComplete, this);

		mAnimator->FindEvents(L"Win")->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		mAnimator->GetCompleteEvent(L"Win") = std::bind(&Player::WalkComplete, this);

		//mAnimator->Play(L"MoveRight", true);
		//mAnimator->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		AddComponent(mAnimator);

		Collider* coliider = new Collider();
		AddComponent(coliider);

		coliider->SetOffset(Vector2(0.0f, 50.0f));
		coliider->SetScale(Vector2(10.0f, 10.0f));

		//Collider* coliider2 = new Collider();
		//AddComponent(coliider2);

		//coliider2->SetOffset(Vector2(60.0f, 0.0f));
		//coliider2->SetScale(Vector2(10.0f, 10.0f));

		//Rigidbody* rigidBody = new Rigidbody();
		//AddComponent(rigidBody);

		//AddComponent<Rigidbody>();
		
		mCoff = 0.1f;
		mMisiileDir = Vector2::One;

		//float x = math::lerp(1.0f, 3.0f, 0.5f);
	}

	Player::~Player()
	{

	}

	void Player::Tick()
	{
		GameObject::Tick();
		
		top.Tick();
		bottom.Tick();

		if (KEY_DOWN(eKeyCode::W))
		{
			mAnimator->Play(L"Move", true);
		}
		if (KEY_DOWN(eKeyCode::S))
		{
			mAnimator->Play(L"Move", true);
		}
		if (KEY_DOWN(eKeyCode::A))
		{
			//Vector2 pos = GetPos();
			//dest = Vector2(pos.x + 200.0f, pos.y);

			mAnimator->Play(L"Move", true);
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"Move", true);
		}

		Vector2 pos = GetPos();

		if (KEY_PREESE(eKeyCode::W))
		{
			pos.y -= 120.0f * Time::DeltaTime();
			//missile->mDir.y = -1.0f;

			//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}
		if (KEY_PREESE(eKeyCode::S))
		{
			pos.y += 120.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (KEY_PREESE(eKeyCode::A))
		{
			pos.x -= 120.0f * Time::DeltaTime();
			//missile->mDir.x = 1.0f;
			//GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));

			//Vector2 pos = GetPos();
		
			//pos = math::lerp(pos, dest, 0.003f);
			//SetPos(pos);
			//pos = math::lerp(pos, )

		}
		if (KEY_PREESE(eKeyCode::D))
		{
			pos.x += 120.0f * Time::DeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}
		SetPos(pos);

		/*if (KEY_DOWN(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = -500.0f;
			rigidbody->SetVelocity(velocity);

			rigidbody->SetGround(false);

			UIManager::Pop(eUIType::OPTION);
		}*/

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			mAnimator->Play(L"Attack", true);
		}

		if (KEY_DOWN(eKeyCode::ENTER))
		{
			mAnimator->Play(L"Win", true);
		}


	}

	void Player::Render(HDC hdc)
	{
		//HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		//Brush brush(hdc, blueBrush);

		//HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//Pen pen(hdc, redPen);





		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}

	void Player::OnCollisionStay(Collider* other)
	{

	}

	void Player::OnCollisionExit(Collider* other)
	{

	}

	void Player::WalkComplete()
	{
		/*Missile* missile = new Missile();

		Scene* playScene = SceneManager::GetPlayScene();
		playScene->AddGameObject(missile, eColliderLayer::Player_Projecttile);

		Vector2 playerPos = GetPos();
		Vector2 playerScale = GetScale() / 2.0f;
		Vector2 missileScale = missile->GetScale();

		missile->SetPos((playerPos + playerScale) - (missileScale / 2.0f));*/

		mAnimator->Play(L"Idle", true);

	}
}
