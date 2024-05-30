// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

UCLASS()
class CPPPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Amplitude: get, set
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin Parameters")
	float Amplitude = 1.f;

	//Frequency: get, set
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sin Parameters")
	float TimeConstant = 1.f;

	//Rotation Variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rotation Value")
	float RotationValue = 1.f;

	//-------------------------Function---------------------------//

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	UFUNCTION(BlueprintPure)
	float RotatedRational();

	template<typename T>
	T avg(T first, T second);

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private : 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;
};

template<typename T>
inline T AItem::avg(T first, T second)
{
	return T(first + second)/2;
}
