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
	
	//if에 포인터 선언과 조건문 둘 다 가능. 이 경우, 포인터는 if문 안에서만 유효. 최적화 위해서, null 체크용도로 썼다가 메모리에서 지움. 
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

	//"이동축 인풋 함수"에 "아웃풋 함수" 바인딩 : 컴포넌트->축 바인딩 함수("축 이름(프로젝트 설정)", 대상 주소, 함수 주소)
	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);

}