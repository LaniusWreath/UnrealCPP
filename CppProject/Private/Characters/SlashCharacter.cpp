// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Items/Item.h"
#include "Weapons/Weapon.h"
#include "Animation/AnimMontage.h"


// Sets default values
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//카메라 세팅 - 폰 - 컨트롤러 회전 피치-요-롤 기본값 세팅 : 카메라 회전 제어 on/off : 컨트롤러 입력을 따라 카메라 회전 할것인지(true시 카메라 회전에 제약생김)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	//회전 방향에 맞게 폰 회전시키기
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	//머리카락 Groom 캐릭터 메시에 부착
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	//ACharacter::GetMesh() : 캐릭터 메시(Skeletal Mesh) Subobject 반환 
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	//눈썹 Groom 캐릭터 메시에 부착
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SlashContext, 0);
		}
	}
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//EnhancedInputComponent에 IA 입출력 함수 바인딩 함수
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//EnhancedInputComponent가 nullptr인지 확인
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//EnhancedInputComponent에 입력->출력(이동) 함수 바인딩
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);

		//EnhancedInputComponent에 입력->출력(회전) 함수 바인딩
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);

		//EnhancedInputComponent에 Default 점프 함수 바인딩
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Jump);
		
		//EnhancedInputComponent에 EKey 입력 함수 바인딩
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);

		//EnhancedInputComponent에 공격 입력 함수 바인딩
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);

		//EnhancedInputComponent에 회피 입력 함수 바인딩
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
	}
}

//IA 이벤트 출력 함수
void ASlashCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	//컨트롤러 회전 Get 함수 : Controller->GetControlRotation() : 현재 컨트롤러의 회전 Yaw Pitch Roll 가져옴. Pawn 조작 기반 카메라 회전 기능 구현.
	const FRotator Rotation = Controller->GetControlRotation();

	//Z축 회전만 가져온 회전 객체 생성, FRotator (Pitch, Yaw, Roll) !Vector가 아닌 Rotator
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//Rotator -> RotationMatrix -> Vector 변환과정 
	// 
	// < 3 Dimention Rotation Matrix in Unreal > 
	//  Xaxis : [CosP*CosY,  CosP*CosY,  SinP,  OriginX] : Front Vector 
	//  Yaxis :	[SinR*SinP*CosY - CosR*SinY,  SinR*SinP*SinY + CosR*CosY,  -SinR*CosP,  OriginY] : Right Vector 
	//  Zaxis : [-(CosR*SinP*CosY+SinR*SinY),  CosY*SinR - CosR*SinP*SinY,  CosR*CosP,  OriginZ] : Top Vector
	//  0     : [0,  0,  0,  1]
	// 
	//R[0, θ, 0] -> M[[CosPcosY, CosPSinY, ...]] -> V(M[0][0], M[0][1], M[0][2])
	const FVector ForwardDirrection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirrection, MovementVector.Y);  // W, S Key
	const FVector RightDirrection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirrection, MovementVector.X);  // A, D Key

}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ASlashCharacter::EKeyPressed(const FInputActionValue& Value)
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString("Current Overlapped : ") + OverlappingWeapon->GetName());
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void ASlashCharacter::Attack(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_UnOccupied)
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void ASlashCharacter::Dodge(const FInputActionValue& Value)
{
}

void ASlashCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		const int32 Selection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

