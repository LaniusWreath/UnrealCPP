#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "EquippedOneHanddedWeapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "EquippedTwoHanddedWeapon"),
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_UnOccupied UMETA(DisplayName = "UnOccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
};