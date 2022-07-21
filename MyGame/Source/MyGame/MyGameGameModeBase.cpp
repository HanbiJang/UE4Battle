// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/PlayerHUD.h"
#include "MyGameGameModeBase.h"


AMyGameGameModeBase::AMyGameGameModeBase() {
	//ĳ���� �������Ʈ Ŭ���� ��������
	ConstructorHelpers::FClassFinder<APawn>
		MainCharacterClass(TEXT("Blueprint'/Game/Blueprints/Player/MyKnight2.MyKnight2_C'"));

	if (MainCharacterClass.Succeeded())
	{
		DefaultPawnClass = MainCharacterClass.Class;
	}

	//���� UI �������Ʈ Ŭ���� ��������
	ConstructorHelpers::FClassFinder<UUserWidget>
		MainHUD(TEXT("WidgetBlueprint'/Game/Blueprints/UI/MainUI.MainUI_C'"));

	if (MainHUD.Succeeded())
	{
		m_MainHUDClass = MainHUD.Class;
	}

	//Ÿ��Ʋ UI ���� Ŭ ��������
	ConstructorHelpers::FClassFinder<UUserWidget>
		TitleHUD(TEXT("WidgetBlueprint'/Game/Blueprints/UI/TitleUI.TitleUI_C'"));

	if (TitleHUD.Succeeded())
	{
		m_TitleHUDClass = TitleHUD.Class;
	}
	

}

//UI����
void AMyGameGameModeBase::UpdatePlayerHUD(float _CurHPRatio,float _CurMPRatio){

	UPlayerHUD* pPlayerHUD = m_MainHUD->GetPlayerHUD();

	//pPlayerHUD->SetHP(_CurHPRatio);
	pPlayerHUD->SetMP(_CurMPRatio);
}

void AMyGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//���� ������ GameScene �̸� �Ʒ��� ����
	FString levelName = GetWorld()->GetMapName();

	if (levelName == "UEDPIE_0_GameLevel") {
		m_MainHUD = Cast<UMainHUD> (CreateWidget(GetWorld(), m_MainHUDClass));
		m_MainHUD->AddToViewport();
	}

	//���� ������ Title �̸� �Ʒ��� ����
	if (levelName == "UEDPIE_0_TitleLevel") {
		m_MainHUD =  Cast<UMainHUD> (CreateWidget(GetWorld(), m_TitleHUDClass));
		m_MainHUD->AddToViewport();
	}

}