// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoulProjectile.h"

AMySoulProjectile::AMySoulProjectile() 
	: m_fAccTime(0.f)
	, m_Sound(nullptr)
	, m_Attenuation(nullptr){

	m_IsHit = false;

	// 박스 생성
	SetBox(CreateDefaultSubobject<UBoxComponent>(TEXT("Box")));

	// 파티클 컴포넌트 생성 및 에셋 세팅
	SetParticle(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle")));

	ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("	ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stab.P_ky_stab'"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_stabShot_1Play.P_ky_stabShot_1Play'"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Archive/P_Posseser_Attach.P_Posseser_Attach'"));
	if (particleAsset.Succeeded())
	{
		GetParticle()->SetTemplate(particleAsset.Object);
	}

	// 박스 컴포넌트를 루트씬 컴포넌트로 지정
	SetRootComponent(GetBox());

	// 파티클 컴포넌트가 박스를 부모로 지정
	GetParticle()->SetupAttachment(GetBox());

	// 투사체 업데이트 대상을 박스로 지정
	GetProjectile()->SetUpdatedComponent(GetBox());

	newScale = GetActorScale3D();

	//// 재생할 사운드 참조
	//ConstructorHelpers::FObjectFinder<USoundBase> soundasset(TEXT("SoundWave'/Game/Interface_And_Item_Sounds/WAV/Bar_Filling_02.Bar_Filling_02'"));
	//if (soundasset.Succeeded())
	//{
	//	m_Sound = soundasset.Object;
	//}

	//ConstructorHelpers::FObjectFinder<USoundAttenuation> soundAtt(TEXT("SoundAttenuation'/Game/BlueprintClass/DefaulAttenuation.DefaulAttenuation'"));
	//if (soundAtt.Succeeded())
	//{
	//	m_Attenuation = soundAtt.Object;
	//}
}


// Called when the game starts or when spawned
void AMySoulProjectile::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void AMySoulProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	m_fAccTime += DeltaTime;
	if (3.f <= m_fAccTime)
	{
		Destroy();
	}
	//충돌
	if (m_IsHit) {
		if (newScale.X >= 0.f && newScale.X >= 0.f && newScale.X >= 0.f) {
			newScale.X -= 0.02f;
			newScale.Y -= 0.02f;
			newScale.Z -= 0.02f;
			//사이즈 줄기
			SetActorScale3D(newScale);
			//GetParticle()->SetWorldScale3D(newScale);
			//UE_LOG(LogTemp, Log, TEXT("%f"), newScale.X);
		}
	}


}

void AMySoulProjectile::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp
	, FVector _NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(_HitComponent, _OtherActor, _OtherComp, _NormalImpulse, Hit);
	//// 소리 재생, 2D
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_Sound, GetActorLocation(), 1.f, 1.f, 0.f, m_Attenuation);

	m_IsHit = true;
}

void AMySoulProjectile::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("overlap"));

}

void AMySoulProjectile::OnEndOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex)
{

}