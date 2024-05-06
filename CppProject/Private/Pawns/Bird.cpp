// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ABird::BeginPlay()
{
	Super::BeginPlay();
	
	//if�� ������ ����� ���ǹ� �� �� ����. �� ���, �����ʹ� if�� �ȿ����� ��ȿ. ����ȭ ���ؼ�, null üũ�뵵�� ��ٰ� �޸𸮿��� ����. 
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
	
}

void ABird::MoveForward(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Value : %f"), value);
}

void ABird::Move(const FInputActionValue& value)
{
	const bool CurrentValue = value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Triggered"));
	}
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//
// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
	}

	//"�̵��� ��ǲ �Լ�"�� "�ƿ�ǲ �Լ�" ���ε� : ������Ʈ->�� ���ε� �Լ�("�� �̸�(������Ʈ ����)", ��� �ּ�, �Լ� �ּ�)
	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);

}