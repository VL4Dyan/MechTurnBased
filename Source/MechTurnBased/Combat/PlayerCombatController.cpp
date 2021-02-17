// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCombatController.h"

APlayerCombatController::APlayerCombatController()
{

}

void APlayerCombatController::SetSelectedTile(FMatrixIndex Index)
{
	if (CombatGridManagerRef->TryGetTileDataByIndex(Index, SelectedTile) && !SelectedTile.bIsVoid)
	{
		SelectedTileIndex = Index;
		bIsTileSelected = true;

		if (SelectedTile.TileHolder != nullptr && SelectedTile.TileHolder->GetGridObjectType() == EGridObjectType::GOType_CombatUnit)
		{
			bIsControllableUnitSelected = true;
			SelectedUnit = Cast<ACombatUnit>(SelectedTile.TileHolder);
		}
		else
		{
			bIsControllableUnitSelected = false;
		}
	}
	else
	{
		bIsTileSelected = false;
	}
}

bool APlayerCombatController::TryGetTempSelectedTile(FMatrixIndex Index, FTileData& TileOut)
{
	FTileData Result;
	if (CombatGridManagerRef->TryGetTileDataByIndex(Index, Result))
	{
		if (!Result.bIsVoid)
		{
			TileOut = Result;
			return true;
		}
	}

	return false;
}

TArray<UTileTargetingResult*> APlayerCombatController::GetActionResultBasedOnUISignal(int Signal)
{
	TArray<UTileTargetingResult*> Result;

	/*if (Signal == 0)
	{
		UMechComponent* MovementComponent = SelectedUnit->GetMechMovementComponent();
		if (MovementComponent != nullptr)
		{
			Result = MovementComponent->GetAvailableActions();
		}
	}
	else
	{
		TArray<UMechComponent*> MechComponents = SelectedUnit->GetMechComponentsRepresentingFunctionality();
		if ((Signal - 2) >= 0 && (Signal - 2) < MechComponents.Num())
		{
			Result = MechComponents[Signal - 2]->GetAvailableActions();
		}
	}

	if (Result.Num() == 0)
	{
		bActionState = false;
	}
	else
	{
		bActionState = true;
	}*/
	return Result;
}