// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMonster.h"
#include "AI/MyAIController.h"


// Sets default values
AMyMonster::AMyMonster()
	: m_state(EMON_STATE::IDLE)
	, m_NextPatrolIdx(-1)
	, bIsUnStopable(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Tags.Add("Monster");

	// ��� �� AIController Ŭ���� ����
	AIControllerClass = AMyAIController::StaticClass();

	// AIController ���� ��� ����
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//// �浹 �������� ����
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnermyType"));
}

// Called when the game starts or when spawned
void AMyMonster::BeginPlay()
{
	Super::BeginPlay();

	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster::OnHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyMonster::OnBeginOverlap);
}

// Called every frame
void AMyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyMonster::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	//Super::OnHit(_HitComponent, _OtherActor, _OtherComp, _NormalImpulse, Hit);

}

FVector AMyMonster::GetNextPatrolPos()
{
	if (m_PatrolPoints.Num() == 0)
	{
		return GetActorLocation();
	}

	++m_NextPatrolIdx;
	if (m_PatrolPoints.Num() <= m_NextPatrolIdx)
	{
		m_NextPatrolIdx = 0;
	}

	return m_PatrolPoints[m_NextPatrolIdx];
}


void AMyMonster::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{

}

void AMyMonster::OnAttTrigger()
{
	// �÷��̾ �˾� ����.
	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr == Player)
		return;

	// ������ ��ġ, ���� ����, �÷��̾ ���ϴ� ����
	FVector vMonPos = GetActorLocation();

	FVector vMonFoward = GetActorForwardVector();
	vMonFoward.Z = 0.f;
	vMonFoward.Normalize(); //ũ��1

	FVector vTargetDir = Player->GetActorLocation() - vMonPos;
	vTargetDir.Normalize(); //ũ��1

	// ���� ������ �ݰ�
	float fRadius = 200.f;

	// ������ ���� ���� ����
	float fDegree = 90.f;


	TArray<FHitResult> arrHit;
	FCollisionQueryParams param(NAME_None, false, this);

	GetWorld()->SweepMultiByChannel(arrHit, vMonPos, vMonPos, FQuat::Identity
		, ECC_GameTraceChannel6/*MonsterAttack Trace Channel*/
		, FCollisionShape::MakeSphere(fRadius), param);

	if (arrHit.Num())
	{
		for (size_t i = 0; i < arrHit.Num(); ++i)
		{
			// ���� üũ
			float fDot = FVector::DotProduct(vTargetDir, vMonFoward);
			float fRadian = FMath::Acos(fDot);
			float fAngle = FMath::Abs(FMath::RadiansToDegrees(fRadian));

			if (fAngle <= fDegree / 2.f)
			{
				FTransform trans(arrHit[i].ImpactNormal.Rotation(), arrHit[i].ImpactPoint);
				//UEffectMgr::GetInst(GetWorld())->CreateEffect(EEFFECT_TYPE::ICE, trans, GetLevel());
			}
		}
	}
}


