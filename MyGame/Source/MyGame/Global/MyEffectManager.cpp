// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffectManager.h"
#include "MyEffect.h"

UMyEffectManager* UMyEffectManager::m_This = nullptr;
UWorld* UMyEffectManager::m_World = nullptr;

UMyEffectManager::UMyEffectManager()
{
}

UMyEffectManager::~UMyEffectManager()
{
}

UMyEffectManager* UMyEffectManager::GetInst(UWorld* _world)
{
	if (nullptr == m_This)
	{
		// ���� �ش�.
		m_This = NewObject<UMyEffectManager>();
		m_This->AddToRoot(); // G.C ���� ��꿡�� ��â �ֻ����� ��ġ�Ѵ�. ==> GC �� ���ؼ� ������ ����

		m_World = _world;
	}

	// ����� ���忡�� ��ü�� ��û�� ���
	if (m_World != _world)
	{
		m_World = _world;
	}

	/*UWorld* pWorld = nullptr;
	UGameInstance* pInst = UGameplayStatics::GetGameInstance(pWorld);
	pInst->GetEngine()->OnWorldDestroyed().AddStatic();*/

	return m_This;
}

void UMyEffectManager::Destroy()
{
	if (nullptr != m_This)
	{
		m_This->ConditionalBeginDestroy();
		m_This = nullptr;
		m_World = nullptr;
	}
}


void UMyEffectManager::CreateEffect(EEFFECT _type, FTransform _trans, ULevel* _Level)
{
	FActorSpawnParameters SpawnParam = {};

	SpawnParam.OverrideLevel = _Level;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;

	AMyEffect* pEffect = m_World->SpawnActor<AMyEffect>(AMyEffect::StaticClass(), _trans, SpawnParam);

	pEffect->SetEffectType(_type);

	pEffect->FinishSpawning(pEffect->GetTransform());
}

