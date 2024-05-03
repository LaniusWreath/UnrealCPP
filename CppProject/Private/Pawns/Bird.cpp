// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

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
	
}

void ABird::MoveForward(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Value : %f"), value);
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

	//"이동축 인풋 함수"에 "아웃풋 함수" 바인딩 : 컴포넌트->축 바인딩 함수("축 이름(프로젝트 설정)", 대상 주소, 함수 주소)
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);
}

