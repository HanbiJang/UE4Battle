// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

/// <summary>
/// 행 이름에 맞는 몬스터 데이터 테이블의 값 반환
/// </summary>
/// <param name="_RowName"></param>
/// <returns></returns>
const FMonInfo* UMyGameInstance::GetMonInfo(const FString& _RowName)
{
	FMonInfo* pMonInfo = m_MonTable->FindRow<FMonInfo>(FName(_RowName), TEXT(""));
	return pMonInfo;
}

UMyGameInstance::UMyGameInstance()
	: m_MonTable(nullptr)
{
	ConstructorHelpers::FObjectFinder<UDataTable> montable(TEXT("DataTable'/Game/Blueprints/Monster/MonsterAI/DTNormalMonster.DTNormalMonster'"));
	if (montable.Succeeded())
	{
		m_MonTable = montable.Object;
	}

	//카메라 쉐이크 블루프린트 클래스를 가져옴
	ConstructorHelpers::FClassFinder<UCameraShakeBase> CamShake(TEXT("Blueprint'/Game/Blueprints/MyCameraShakeKnightAttack.MyCameraShakeKnightAttack_C'"));
	if (CamShake.Succeeded())
	{
		m_CamShake = CamShake.Class;
	}
}

//UMyGameInstance::~UMyGameInstance()
//{
//	UEffectMgr::Destroy();
//}


//const FMonInfo* UMyGameInstance::GetMonInfo(const FString& _RowName)
//{
//	FMonInfo* pMonInfo = m_MonTable->FindRow<FMonInfo>(FName(_RowName), TEXT(""));
//	return pMonInfo;
//}