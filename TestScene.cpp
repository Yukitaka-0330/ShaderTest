#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Stage.h"
#include "ColorBall.h"
#include "ColorDice.h"
#include "WaterSurface.h"

TestScene::TestScene(GameObject* parent) :GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<ColorBall>(this);
	Instantiate<ColorDice>(this);
	Instantiate<WaterSurface>(this);
}

void TestScene::Update()
{
	
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
