// Fill out your copyright notice in the Description page of Project Settings.

#include "../MyGameGameModeBase.h"

#include "MyCharacter.h"
#include "MyAnimInstance.h" //헤더 중복 문제 해결

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//카메라
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	m_Arm->SetupAttachment(GetMesh()); //메시에 카메라 붙이기
	m_Cam->SetupAttachment(m_Arm); //카메라암에 카메라 붙이기

	m_Arm->TargetArmLength = 200.f;

	//점프 주기
	jumpTime = 0.f;

	//칼 콜리전
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Capsule_Sword"));
	m_Cam->SetupAttachment(GetMesh()); //메시에 카메라 붙이기




	//체력,마나
	m_Info.fMaxHP = 100.f;
	m_Info.fCurHP = 100.f;
	m_Info.fMaxMP = 100.f;
	m_Info.fCurMP = 0.f;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//애니메이션 관련 생성
	m_AnimInst = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); //캐릭터의 매시에서 설정된 AnimInstance 클래스 가져오기

	//충돌 관련
	//충돌 델리게이트 추가
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnEndOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMyCharacter::OnHit);

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		if (m_PrevHP != m_Info.fCurHP || m_PrevMP != m_Info.fCurMP)
	{
		// 이전 MP과 현제 MP가 다르다.
		// HUD 갱신
		AMyGameGameModeBase* GM = Cast<AMyGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		float HPRatio = m_Info.fCurHP / m_Info.fMaxHP;
		float MPRatio = m_Info.fCurMP / m_Info.fMaxMP;
		GM->UpdatePlayerHUD(HPRatio, MPRatio);
	}

	m_PrevHP = m_Info.fCurHP;

	//점프 횟수 조절하기
	if (m_AnimInst->Getm_JumpEnd()) { //jumpend 변수가 true일때만 1초 뒤에 전환함
		if (0.5f <= jumpTime)
		{
			m_AnimInst->Setm_JumpEnd(false);
			jumpTime = 0.f; //초기화
			UE_LOG(LogTemp, Log, TEXT("Tick _ jumpTime = 0"));
		}
		else {
			jumpTime += DeltaTime;
			UE_LOG(LogTemp, Log, TEXT("Tick _ jumpTime = %f"), jumpTime);
		}
	}

	////속력체크 -> 상태 변화
	//if (GetCharacterMovement()->Velocity.Size() <= 0.f) {
	//	ChangeState(EPLAYER_STATE::IDLE);
	//}

}

#pragma region ----------------------------Camera-----------------------------------
//카메라
void AMyCharacter::RotationZ(float fscale)
{
	float speed = 1.f;

	//캐릭터 상태에 따라 카메라 회전 제한
	if (GetState() == EPLAYER_STATE::IDLE || GetState() == EPLAYER_STATE::MOVE || GetState() == EPLAYER_STATE::DEAD) {
		speed = 1.f;
	}
	else {
		speed = 0.4f;
	}


	
	AddControllerYawInput(fscale* speed);
}

void AMyCharacter::RotationY(float fscale)
{
	
	float fDT = GetWorld()->GetDeltaSeconds();
	float speed = 180.f;

	//캐릭터 상태에 따라 카메라 회전 제한
	if (GetState() == EPLAYER_STATE::IDLE || GetState() == EPLAYER_STATE::MOVE || GetState() == EPLAYER_STATE::DEAD) {
		speed = 180.f;
	}
	else {
		speed = 50.f;
	}

	FRotator rot = m_Arm->GetRelativeRotation();

	rot.Pitch += fDT * fscale * speed;

	if (rot.Pitch > 40.f)
	{
		rot.Pitch = 40.f;
	}
	else if (rot.Pitch < -45.f)
	{
		rot.Pitch = -45.f;
	}

	m_Arm->SetRelativeRotation(rot);
}

void AMyCharacter::Zoom(float fscale)
{
	float fDT = GetWorld()->GetDeltaSeconds();
	m_Arm->TargetArmLength -= fscale * 20.f;

	if (m_Arm->TargetArmLength > 500.f)
	{
		m_Arm->TargetArmLength = 500.f;
	}
	else if (m_Arm->TargetArmLength < 200.f)
	{
		m_Arm->TargetArmLength = 200.f;
	}
}
#pragma endregion


#pragma region ----------------------------States-----------------------------------
//상태 관리
//상태 값 가져오기
EPLAYER_STATE AMyCharacter::GetState() {
	return myState;
}

void AMyCharacter::SetState(EPLAYER_STATE newState) {
	myState = newState;
}

//상태 값 변화하기
void AMyCharacter::ChangeState(EPLAYER_STATE newState) {

	if (newState != myState) {
		SetState(newState);

		//애니메이션 상태 안의 모든 값 리셋하기
		ResetAnimState();

		//UE_LOG(LogTemp, Log, TEXT("%i"), newState);
	}


	//if (newState == EPLAYER_STATE::JUMP) {
	//	Jump();
	//	//UE_LOG(LogTemp, Log, TEXT("jump!"));
	//}
}

//애니메이션이 중간에 끊겼을 때 (스테이트)수치값을 원래대로 하기 위함
void AMyCharacter::ResetAnimState() {
	m_AnimInst->Setm_Attack01(false);
	m_AnimInst->Setm_Attack02(false);
	m_AnimInst->Setm_Attack01ComboEnable(false);
	m_AnimInst->Setm_Attack02ComboEnable(false);
	m_AnimInst->Setm_JumpComboEnable(false);
	m_AnimInst->Setm_Jump2(false);
	//m_AnimInst->Setm_JumpEnd(false);
}
#pragma endregion


#pragma region ----------------------------Move-----------------------------------
// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//키와 바인딩
	PlayerInputComponent->BindAxis("Side", this, &AMyCharacter::MoveSide);
	PlayerInputComponent->BindAxis("Front", this, &AMyCharacter::MoveFront);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMyCharacter::JumpAction);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAction("RangeAttack", EInputEvent::IE_Pressed, this, &AMyCharacter::RangeAttack);
	//PlayerInputComponent->BindAction("DownAttack", EInputEvent::IE_Pressed, this, &AMyCharacter::DownAttack);

	//카메라
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &AMyCharacter::RotationZ);
	PlayerInputComponent->BindAxis(TEXT("RotationY"), this, &AMyCharacter::RotationY);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AMyCharacter::Zoom);
}

void AMyCharacter::MoveFront(float fscale) {

	if (GetState() != EPLAYER_STATE::ATTACK 
		&& GetState() != EPLAYER_STATE::JUMP 
		&& GetState() != EPLAYER_STATE::RANGEATTACK
		//&& GetState() != EPLAYER_STATE::CHARGE
		&& GetState() != EPLAYER_STATE::DOWNATTACK) {
		AddMovementInput(GetActorForwardVector(), fscale);

		//속력체크 -> 상태 변화
		if (myState == EPLAYER_STATE::IDLE || myState == EPLAYER_STATE::MOVE)
		{
			if (GetCharacterMovement()->Velocity.Size() > 100.f) ChangeState(EPLAYER_STATE::MOVE);

			else 
			{
				ChangeState(EPLAYER_STATE::IDLE);
			}
		}

		else if (myState != EPLAYER_STATE::ATTACK_MOVABLE)
			return;

		//애니메이션
		float fDir = m_AnimInst->GetDirection();

		// 앞
		if (1.f == fscale)
		{
			if (90.f == fDir) //+오른쪽 눌림
			{
				m_AnimInst->SetDirection(45.f);
			}
			else if (0.f == fDir)
			{
				m_AnimInst->SetDirection(0.f);
			}
			else if (-90.f == fDir) // +왼쪽눌림
			{
				m_AnimInst->SetDirection(-45.f);
			}
		}

		// 뒤
		else if (-1.f == fscale)
		{
			if (90.f == fDir) //+오른쪽 눌림
			{
				m_AnimInst->SetDirection(135.f);
			}
			else if (0.f == fDir)
			{
				m_AnimInst->SetDirection(-180.f);
			}
			else if (-90.f == fDir) // +왼쪽눌림
			{
				m_AnimInst->SetDirection(-135.f);
			}
		}
	}

}
void AMyCharacter::MoveSide(float fscale) {
	if (GetState() != EPLAYER_STATE::ATTACK 
		&& GetState() != EPLAYER_STATE::JUMP
		//&& GetState() != EPLAYER_STATE::CHARGE
		&& GetState() != EPLAYER_STATE::RANGEATTACK && GetState() != EPLAYER_STATE::DOWNATTACK) {
		AddMovementInput(GetActorRightVector(), fscale);

		////속력체크 -> 상태 변화
		//if (myState == EPLAYER_STATE::IDLE || myState == EPLAYER_STATE::MOVE)
		//{
		//	if (0.f == fscale)
		//	{
		//		ChangeState(EPLAYER_STATE::IDLE);
		//	}
		//	else
		//	{
		//		ChangeState(EPLAYER_STATE::MOVE);
		//	}
		//}

		//else if (myState != EPLAYER_STATE::ATTACK_MOVABLE)
		//	return;

		//애니메이션
		// 왼쪽 눌림
		if (-1.f == fscale)
		{
			m_AnimInst->SetDirection(-90.f);
		}

		// 오른쪽 눌림
		else if (1.f == fscale)
		{
			m_AnimInst->SetDirection(90.f);
		}

		else
		{
			m_AnimInst->SetDirection(0.f);
		}
	}


}

void AMyCharacter::JumpAction() {
	
	if (!m_AnimInst->Getm_JumpEnd() && GetMovementComponent()->IsMovingOnGround()) 
	{
		Jump();
		AMyCharacter::ChangeState(EPLAYER_STATE::JUMP); //점프로 상태 변화
	}
		

	//if (!m_AnimInst->Getm_JumpEnd()) {
	//	//if (JumpCurrentCount >= 1 && m_AnimInst->Getm_JumpComboEnable()) { //2단점프
	//	//	m_AnimInst->Setm_Jump2(true);
	//	//}

	//	AMyCharacter::ChangeState(EPLAYER_STATE::JUMP); //점프로 상태 변화
	//}
}
#pragma endregion

void AMyCharacter::RangeAttack() {
	ChangeState(EPLAYER_STATE::RANGEATTACK);
}
void AMyCharacter::DownAttack() {
	ChangeState(EPLAYER_STATE::DOWNATTACK);
}



void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
}

void AMyCharacter::OnEndOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex)
{
}

void AMyCharacter::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
}


float AMyCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	float damageApplied = GetInfo().fCurHP - DamageTaken;
	//체력 설정
	GetInfo().fCurHP = damageApplied;

	return damageApplied;

}





