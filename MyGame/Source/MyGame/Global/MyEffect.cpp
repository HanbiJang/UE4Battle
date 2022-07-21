// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEffect.h"

// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComponent");
	SetRootComponent(m_Particle);

}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();

	UParticleSystem* ParticleAsset = nullptr;

	switch (m_eType)
	{

	case EEFFECT::ATTACK1:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_hit_slash.P_ky_hit_slash'"));
		//UE_LOG(LogTemp, Log, TEXT("effect attack1"));
		break;
	case EEFFECT::ATTACK2:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/P_My_Lava_Splashes.P_My_Lava_Splashes'"));
		break;
	case EEFFECT::ATTACK3:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_hit_slash.P_ky_hit_slash'"));
		break;
	case EEFFECT::ATTACKMOVABLE:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_hit_slash.P_ky_hit_slash'"));
		break;
	//case EEFFECT::JUMP1:
	//	ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit.P_ky_hit'"));
	//	break;
	//case EEFFECT::JUMP2:
	//	ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));
	//	break;
	case EEFFECT::RANGEATTACK:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));

		//ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stabShot_1Play.P_ky_stabShot_1Play'"));
		break;
	//case EEFFECT::DOWNATTACK:
	//	ParticleAsset = LoadObject<UParticleSystem>(GetWorld(), TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_water.P_ky_hit_water'"));
	//	break;
	}

	if (nullptr != ParticleAsset)
	{
		m_Particle->SetTemplate(ParticleAsset);
		m_Particle->OnSystemFinished.AddDynamic(this, &AMyEffect::OnFinish);
	}
	else UE_LOG(LogTemp, Log, TEXT("null effect rangeAttack"));
	
}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffect::OnFinish(UParticleSystemComponent* _Particle)
{
	Destroy();
}
