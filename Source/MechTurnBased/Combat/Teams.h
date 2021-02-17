#pragma once

//#include "CoreMinimal.h"
//#include "Teams.generated.h"

UENUM(BlueprintType)
enum class ETeams : uint8
{
	Team_Player UMETA(DisplayName = "Player"),
	Team_One UMETA(DisplayName = "TeamOne")
};