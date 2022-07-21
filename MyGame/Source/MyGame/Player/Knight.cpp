// Fill out your copyright notice in the Description page of Project Settings.

#include "Knight.h"
#include "../Monster/MyMonster.h"
#include "../Global/MyEffectEnum.h"
#include "../Global/MyEffectManager.h"
#include "../Global/MyGameInstance.h"

#define RangeAttackMp 35.f

AKnight::AKnight() {
	//매시 연결
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		WarriorMesh(TEXT("SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Meshes/Kallari.Kallari'"));

	if (WarriorMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(WarriorMesh.Object);
	}

	//애니메이션
	ConstructorHelpers::FClassFinder<UAnimInstance> animblueprint(TEXT("AnimBlueprint'/Game/Blueprints/Player/MyKnightAnimBlueprint.MyKnightAnimBlueprint_C'"));
	if (animblueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animblueprint.Class);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Down(TEXT("AnimMontage'/Game/Blueprints/Player/MMyKnightDownAttack.MMyKnightDownAttack'"));
	if (Down.Succeeded())
		m_arrMontage.Add(Down.Object);

	//칼
	m_CapsuleSword = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleSword"));
	m_CapsuleSword->SetupAttachment(GetMesh()); //메시에 sword컴포넌트 붙이기
	//부모 소켓 설정
	//m_CapsuleSword->AttachTo(GetMesh(), TEXT("Mesh"), EAttachLocation::SnapToTargetIncludingScale, true);

	//데미지
	m_Demage = 10.f;

	//무기 사운드
	// 재생할 사운드 참조
	ConstructorHelpers::FObjectFinder<USoundBase> soundasset1(TEXT("SoundWave'/Game/MyBGM/hit_sound.hit_sound'"));
	if (soundasset1.Succeeded())
	{
		hitSound = soundasset1.Object;
	}

	//레인지 어택 사운드
	//
	ConstructorHelpers::FObjectFinder<USoundBase> soundasset2(TEXT("SoundWave'/Game/MyBGM/RangeAttack.RangeAttack'"));
	if (soundasset2.Succeeded())
	{
		rangeAttackSound = soundasset2.Object;
	}
};


//키 바인딩
void AKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//회복
	PlayerInputComponent->BindAction("Charge", EInputEvent::IE_Pressed, this, &AKnight::Charging);
}

void AKnight::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//공격 주기 조절하기
	if (m_AnimInst->Getm_AttackEnd()) { //jumpend 변수가 true일때만 1초 뒤에 전환함
		if (0.5f <= AttackTime)
		{
			m_AnimInst->Setm_AttackEnd(false);
			AttackTime = 0.f; //초기화
			//UE_LOG(LogTemp, Log, TEXT("Tick _ jumpTime = 0"));
		}
		else {
			AttackTime += DeltaTime;
			//UE_LOG(LogTemp, Log, TEXT("Tick _ jumpTime = %f"), jumpTime);
		}
	}

}

void AKnight::BeginPlay() {
	Super::BeginPlay();

	//캐릭터의 매시에서 설정된 AnimInstance 클래스 가져오기
	m_AnimInst = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); 
}

void AKnight::Attack() {
	if (!m_AnimInst->Getm_AttackEnd()) {
		if (myState == EPLAYER_STATE::MOVE || myState == EPLAYER_STATE::JUMP) { //움직임 가능 공격
			AMyCharacter::ChangeState(EPLAYER_STATE::ATTACK_MOVABLE);
			// 소리 재생, 2D
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetActorLocation(), 1.f, 1.f, 0.f);
		}

		//일반공격
		else if (myState == EPLAYER_STATE::IDLE || myState == EPLAYER_STATE::ATTACK) 
		{

			if (m_AnimInst->Getm_Attack02()) { //3단계 공격 진행중일시
				return;
			}

			if( myState != EPLAYER_STATE::ATTACK){
				AMyCharacter::ChangeState(EPLAYER_STATE::ATTACK); //공격으로 상태 변화
			}
			

			if (m_AnimInst->Getm_Attack01ComboEnable()) {
				m_AnimInst->Setm_Attack01(true);
			}

			if (m_AnimInst->Getm_Attack02ComboEnable()) {
				m_AnimInst->Setm_Attack02(true);
			}

		}
	}
}

void AKnight::AttackSoundPlay() {

	// 소리 재생, 2D
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetActorLocation(), 1.f, 1.f, 0.f);
	
}


void AKnight::RangeAttack() { 

	if( myState != EPLAYER_STATE::RANGEATTACK && GetInfo().fCurMP >= RangeAttackMp){
	//이펙트 만들기
	FVector vPos = GetActorLocation();
	FVector vFoward = GetActorForwardVector();
	FTransform trans(GetActorRotation(), vPos+ vFoward *50.f);

	UMyEffectManager::GetInst(GetWorld())->CreateEffect(EEFFECT::RANGEATTACK, trans, GetLevel());

	// 소리 재생, 2D
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), rangeAttackSound, GetActorLocation(), 1.f, 1.f, 0.f);

	ChangeState(EPLAYER_STATE::RANGEATTACK);
	}
}

void AKnight::DownAttack() { //다운 어택
	Super::DownAttack();

	GetAnimInst()->Montage_Play(m_arrMontage[0]);
}

void AKnight::Charging() { //체력 회복

	ChangeState(EPLAYER_STATE::CHARGE);

	//체력회복 코드
	//...
}


void AKnight::AttackTrigger() 
{
	if (!m_AnimInst->Getm_AttackEnd()) {
		//camera shake
		UMyGameInstance* pGI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (nullptr != pGI)
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(pGI->GetCameraShake());
		}

		//휘두르는 이펙트 재생
		FVector vPos = GetActorLocation();
		FVector vFoward = GetActorForwardVector();
		FTransform trans(GetActorRotation(), vPos + vFoward * 50.f);
		UMyEffectManager::GetInst(GetWorld())->CreateEffect(EEFFECT::ATTACK1, trans, GetLevel());

		//공격 (충돌) 범위 체크
		//Trace 채널을 이용한 범위 체크		
		float fRadius = 200.f; //구의 크기

		TArray<FHitResult> arrHit; //충돌 결과
		FCollisionQueryParams param(NAME_None, false, this);

		GetWorld()->SweepMultiByChannel(arrHit, vPos + FVector(0, 0, 50.f), vPos + FVector(0, 0, 50.f), FQuat::Identity
			, ECC_GameTraceChannel3/*PlayerAttack Trace Channel*/
			, FCollisionShape::MakeSphere(fRadius), param);

		bool isCheckMonster = false;
		if (arrHit.Num())
		{

			for (size_t i = 0; i < arrHit.Num(); ++i) {
				if (arrHit[i].GetActor()->Tags.Num() != 0) {
					if ((arrHit[i].GetActor()->Tags)[0] == "Monster") {
						isCheckMonster = true;
						break;
					}
				}
			}

			if (isCheckMonster) {
				//이펙트 재생
				UMyEffectManager::GetInst(GetWorld())->CreateEffect(EEFFECT::ATTACK2, trans, GetLevel());

				//몬스터가 맞게하기...
				for (size_t i = 0; i < arrHit.Num(); ++i) {
					AMyMonster* m_mon = Cast<AMyMonster>(arrHit[i].GetActor());
					if (nullptr != m_mon)
						m_mon->HitFunc();
						
						//MP 회복하기

						GetInfo().fCurMP += 10.f;

						if(GetInfo().fMaxMP <= GetInfo().fCurMP){
							GetInfo().fCurMP = GetInfo().fMaxMP;
						}
				}
			}

			for (size_t i = 0; i < arrHit.Num(); ++i)
			{
				UE_LOG(LogTemp, Log, TEXT("collision : %i"), arrHit.Num());
				FString namemon = arrHit[i].GetActor()->GetName();
				UE_LOG(LogTemp, Log, TEXT("%s"), *namemon);
				//FTransform trans(arrHit[i].ImpactNormal.Rotation(), arrHit[i].ImpactPoint);
			}
		}
	

#ifdef ENABLE_DRAW_DEBUG //범위를 눈으로 확인
	FColor color;
	arrHit.Num() ? color = FColor::Red : color = FColor::Green;
	DrawDebugSphere(GetWorld(), vPos + FVector(0, 0, 50.f), fRadius, 12, color, false, 2.5f);
#endif
	}
}

void AKnight::RangeAttackTrigger() //레인지공격에 노티파이로 사용
{

	if(GetInfo().fCurMP >= RangeAttackMp){

		// 투사체 생성
		FVector vPos = GetActorLocation();
		FVector vFoward = GetActorForwardVector();

		FActorSpawnParameters SpawnParam = {};

		SpawnParam.OverrideLevel = GetLevel();
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParam.bDeferConstruction = true;

		AMySoulProjectile* pSoul = GetWorld()->SpawnActor<AMySoulProjectile>(m_Projectile
			, vPos + vFoward * 100.f
			, vFoward.Rotation()
			, SpawnParam);

		if (pSoul != nullptr) {
			pSoul->GetProjectile()->Velocity = vFoward;
			// begin play 호출
			pSoul->FinishSpawning(pSoul->GetTransform());
		}

		else UE_LOG(LogTemp, Log, TEXT("?"));	

		//mp쓰기
		GetInfo().fCurMP -= RangeAttackMp;
	}

}

void AKnight::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{

}
