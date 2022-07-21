// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonsterSpawnPoint.h"
#include "GameFramework/Actor.h"


// Sets default values
ANormalMonsterSpawnPoint::ANormalMonsterSpawnPoint()
	: m_AccTime(0.f)
	, bIsSpawnUse(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�±��߰��ϱ�
	Tags.Add("SpawnPoint");

	// �÷��̾�� �浹�� ���� ����
	m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(m_StaticMeshComponent);

	m_StaticMeshComponent->SetCollisionProfileName(TEXT("SpawnArea"));


	// �⺻ �浹 �޽��� Sphere �� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMesh.Succeeded())
	{
		m_StaticMeshComponent->SetStaticMesh(SphereMesh.Object);
	}
}

// Called when the game starts or when spawned
void ANormalMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// ������ ���� �̺�Ʈ�Լ� ��������Ʈ �߰�
	m_StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ANormalMonsterSpawnPoint::OnBeginOverlap);
	
}

// Called every frame
void ANormalMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


#ifdef ENABLE_DRAW_DEBUG
	m_AccTime += DeltaTime;

	if (m_AccTime > 2.f)
	{
		m_AccTime = 0.f;

		FVector vPos = GetActorLocation();
		float fRadius = GetActorTransform().GetScale3D().X * (50.f);

		FColor color = FColor::Yellow;
		DrawDebugSphere(GetWorld(), vPos, fRadius, 20, color, false, 2.f);
	}
#else
#endif
}

/// <summary>
/// �÷��̾�� ������ ���� ����
/// </summary>
void ANormalMonsterSpawnPoint::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	if (nullptr == m_SpawnType || bIsSpawnUse)
	{
		return;
	}

	FActorSpawnParameters SpawnParam = {};
	SpawnParam.OverrideLevel = GetLevel();
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;

	float fMaxDist = GetActorTransform().GetScale3D().X * (100.f / 2.f);
	FVector vSpawnPointLocation = GetActorLocation();

	for (uint8 i = 0; i < m_SpawnNum; ++i)
	{
		// ������ġ �����
		float fDist = FMath::RandRange(0.f, fMaxDist);
		float fAngle = FMath::RandRange(0.f, 2 * PI);
		FVector vRandPos = FVector(FMath::Sin(fAngle) * fDist, FMath::Cos(fAngle) * fDist, vSpawnPointLocation.Z + 100.f);
		vRandPos.X += vSpawnPointLocation.X;
		vRandPos.Y += vSpawnPointLocation.Y;


		FVector vDir = vRandPos - vSpawnPointLocation;
		vDir.Z = 0.f; // �ٶ󺸴� ������ �������� �����ϱ� ���ؼ�
		vDir.Normalize();

		// ���� �������� ������ġ�� ���� ����
		AMyMonster* pMonster = GetWorld()->SpawnActor<AMyMonster>(m_SpawnType, FTransform(vDir.Rotation(), vRandPos), SpawnParam);

		// �ʱ�ȭ ���� ȣ��
		// ���Ͱ� �����ؾ� �ϴ� ����Ʈ���� �˷� ��	
		for (int j = 0; j < m_PatrolPoints.Num(); ++j)
		{
			int idx = (i + j) % m_PatrolPoints.Num();
			pMonster->AddPatrolPoint(m_PatrolPoints[idx]->GetActorLocation());
		}

		// BeginPlay ȣ��
		pMonster->FinishSpawning(pMonster->GetTransform());
	}

	bIsSpawnUse = true;
}

