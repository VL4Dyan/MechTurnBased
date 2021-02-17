#pragma once

UENUM(BlueprintType)
enum class EGridObjectType : uint8
{
	GOType_CombatUnit UMETA(DisplayName = "CombatUnit"),
	GOType_Structure UMETA(DisplayName = "Structure")
};