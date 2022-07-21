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

	//태그추가하기
	Tags.Add("SpawnPoint");

	// 플레이어와 충돌할 스폰 영역
	m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(m_StaticMeshComponent);

	m_StaticMeshComponent->SetCollisionProfileName(TEXT("SpawnArea"));


	// 기본 충돌 메쉬를 Sphere 로 지정
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

	// 오버랩 진입 이벤트함수 델리게이트 추가
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
/// 플레이어와 겹쳐질 시의 반응
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
		// 랜덤위치 만들기
		float fDist = FMath::RandRange(0.f, fMaxDist);
		float fAngle = FMath::RandRange(0.f, 2 * PI);
		FVector vRandPos = FVector(FMath::Sin(fAngle) * fDist, FMath::Cos(fAngle) * fDist, vSpawnPointLocation.Z + 100.f);
		vRandPos.X += vSpawnPointLocation.X;
		vRandPos.Y += vSpawnPointLocation.Y;


		FVector vDir = vRandPos - vSpawnPointLocation;
		vDir.Z = 0.f; // 바라보는 방향을 수평으로 유지하기 위해서
		vDir.Normalize();

		// 스폰 범위내에 랜덤위치에 몬스터 생성
		AMyMonster* pMonster = GetWorld()->SpawnActor<AMyMonster>(m_SpawnType, FTransform(vDir.Rotation(), vRandPos), SpawnParam);

		// 초기화 관련 호출
		// 몬스터가 순찰해야 하는 포인트들을 알려 줌	
		for (int j = 0; j < m_PatrolPoints.Num(); ++j)
		{
			int idx = (i + j) % m_PatrolPoints.Num();
			pMonster->AddPatrolPoint(m_PatrolPoints[idx]->GetActorLocation());
		}

		// BeginPlay 호출
		pMonster->FinishSpawning(pMonster->GetTransform());
	}

	bIsSpawnUse = true;
}

