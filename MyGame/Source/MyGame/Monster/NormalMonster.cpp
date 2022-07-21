// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonster.h"

ANormalMonster::ANormalMonster() {
	
	//메시 가져오기
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		WarriorMesh(TEXT("SkeletalMesh'/Game/CityofBrass_Enemies/Meshes/Enemy/Corpse/Corpse_Sword.Corpse_Sword'"));

	if (WarriorMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WarriorMesh.Object);
	}

	//애니메이션 가져오기
	ConstructorHelpers::FClassFinder<UAnimInstance> animblueprint(TEXT("AnimBlueprint'/Game/Blueprints/Monster/AMyNormalMonsterAnimBlueprint.AMyNormalMonsterAnimBlueprint_C'"));
	if (animblueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animblueprint.Class);
	}


	// 사용 할 행동트리
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/Blueprints/Monster/MonsterAI/BTNormalMonster.BTNormalMonster'"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}

	// 사용 할 블랙보드	
	ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/Blueprints/Monster/MonsterAI/BBNormalMonster.BBNormalMonster'"));
	if (BB.Succeeded())
	{
		SetBlackboard(BB.Object);
	}


}


void ANormalMonster::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Monster");

	// 테이블에서 NormalMonster 정보를 가져와서 세팅한다.
	UMyGameInstance* pGameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != pGameInst)
	{
		const FMonInfo* pTableRow = pGameInst->GetMonInfo(TEXT("NormalMonster"));
		if (nullptr != pTableRow)
		{
			SetMonInfo(*pTableRow);
		}
	}
}

void ANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//체력이 0이면 죽어버리기
	FMonInfo info = GetInfo();
	if (info.fCurHP <= 0.f) {
		ChangeState(EMON_STATE::DEAD);
	}

}

bool ANormalMonster::ChangeState(EMON_STATE _eNextState)
{
	if (EMON_STATE::HIT == _eNextState)
	{
		SetUnStopable(false); //false면 경직 푼다
	}


	EMON_STATE eCurState = GetState();
	if (IsUnStopable() || eCurState == _eNextState) //true면 경직 준다
		return false;

	SetState(_eNextState);


	// 상태 변경 성공 시 후처리
	switch (GetState())
	{
	case EMON_STATE::IDLE:
		GetMovementComponent()->StopMovementImmediately();
		break;
	case EMON_STATE::MOVE:
		break;
	case EMON_STATE::ATTACK:
		SetUnStopable(true);
		break;
	case EMON_STATE::ATTACK_MOVABLE:
		break;
	case EMON_STATE::JUMP:
		break;
	case EMON_STATE::HIT:
		SetUnStopable(true);
		break;
	case EMON_STATE::DEAD:
		SetUnStopable(true);
		break;
	default:
		break;
	}

	return true;
}


void ANormalMonster::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor
	, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(_HitComponent, _OtherActor, _OtherComp, _NormalImpulse, Hit);

	if (ECC_GameTraceChannel2 == _OtherComp->GetCollisionObjectType()) //플레이어 소울공격
	{
		ChangeState(EMON_STATE::HIT);
		//UE_LOG(LogTemp, Log, TEXT("OnHit"));
	}

	//UE_LOG(LogTemp, Log, TEXT("OnHit"));
}
void ANormalMonster::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	Super::OnBeginOverlap(_PrimitiveComponent, _OtherActor, _OtherComp, _OtherBodyIndex, _bFromSweep, _SweepResult);

	if (ECC_GameTraceChannel2 == _OtherComp->GetCollisionObjectType()) //플레이어 소울공격
	{
		ANormalMonster::HitFunc();

		//ChangeState(EMON_STATE::HIT);
		//GetMovementComponent()->StopMovementImmediately();
		//FMonInfo info = GetInfo();
		//info.fCurHP -= 35.f;
		//SetMonInfo(info);
		////UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

		//FString text =  "monster  HP: " + FString::SanitizeFloat(info.fCurHP);

		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, text);
	}
	//UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

}

//맞았을 시 
void ANormalMonster::HitFunc() {
	ChangeState(EMON_STATE::HIT);
	GetMovementComponent()->StopMovementImmediately();
	FMonInfo info = GetInfo();
	info.fCurHP -= 20.f;
	SetMonInfo(info);
	//UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));

	FString text = "monster  HP: " + FString::SanitizeFloat(info.fCurHP);

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, text);
}
