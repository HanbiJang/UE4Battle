// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/PlayerHUD.h"
#include "MyGameGameModeBase.h"


AMyGameGameModeBase::AMyGameGameModeBase() {
	//캐릭터 블루프린트 클래스 가져오기
	ConstructorHelpers::FClassFinder<APawn>
		MainCharacterClass(TEXT("Blueprint'/Game/Blueprints/Player/MyKnight2.MyKnight2_C'"));

	if (MainCharacterClass.Succeeded())
	{
		DefaultPawnClass = MainCharacterClass.Class;
	}

	//게임 UI 블루프린트 클래스 가져오기
	ConstructorHelpers::FClassFinder<UUserWidget>
		MainHUD(TEXT("WidgetBlueprint'/Game/Blueprints/UI/MainUI.MainUI_C'"));

	if (MainHUD.Succeeded())
	{
		m_MainHUDClass = MainHUD.Class;
	}

	//타이틀 UI 블프 클 가져오기
	ConstructorHelpers::FClassFinder<UUserWidget>
		TitleHUD(TEXT("WidgetBlueprint'/Game/Blueprints/UI/TitleUI.TitleUI_C'"));

	if (TitleHUD.Succeeded())
	{
		m_TitleHUDClass = TitleHUD.Class;
	}
	

}

//UI갱신
void AMyGameGameModeBase::UpdatePlayerHUD(float _CurHPRatio,float _CurMPRatio){

	UPlayerHUD* pPlayerHUD = m_MainHUD->GetPlayerHUD();

	//pPlayerHUD->SetHP(_CurHPRatio);
	pPlayerHUD->SetMP(_CurMPRatio);
}

void AMyGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//현재 레벨이 GameScene 이면 아래를 수행
	FString levelName = GetWorld()->GetMapName();

	if (levelName == "UEDPIE_0_GameLevel") {
		m_MainHUD = Cast<UMainHUD> (CreateWidget(GetWorld(), m_MainHUDClass));
		m_MainHUD->AddToViewport();
	}

	//현재 레벨이 Title 이면 아래를 수행
	if (levelName == "UEDPIE_0_TitleLevel") {
		m_MainHUD =  Cast<UMainHUD> (CreateWidget(GetWorld(), m_TitleHUDClass));
		m_MainHUD->AddToViewport();
	}

}