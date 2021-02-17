// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionResult.h"

UActionResult::UActionResult()
{

}

void UActionResult::AddTileTarget(FMatrixIndex TileIndex)
{
	UTileTargetingResult* TileTarget = NewObject<UTileTargetingResult>();
	TileTarget->Initialize(TileIndex);

	TileTargets.Add(TileTarget);
}

void UActionResult::AddComponentTarget(FMatrixIndex TileIndexOfExistingTileTarget, UGridObjectComponent* MechComponent)
{
	for (UTileTargetingResult* TileTarget : TileTargets)
	{
		if (TileTarget->TileIndex == TileIndexOfExistingTileTarget)
		{
			UComponentTargetingResult* ComponentTarget = NewObject<UComponentTargetingResult>();
			ComponentTarget->Initialize(MechComponent);

			TileTarget->ComponentTargetResults.Add(ComponentTarget);
		}
	}
}

bool UActionResult::TryCreateCompUpdate(UGridObjectComponent* GridObjectComponentToAdd, FMatrixIndex TargetTileIndex, UGridObjectComponent* TargetMechComponent)
{
	UTileTargetingResult* CurrTileTarget = nullptr;

	for (UTileTargetingResult* TileTarget : TileTargets)
	{
		if (TileTarget->TileIndex == TargetTileIndex)
		{
			CurrTileTarget = TileTarget;
			break;
		}
	}

	if (CurrTileTarget != nullptr)
	{
		if (TargetMechComponent != nullptr)
		{
			UComponentTargetingResult* CurrCompTarget = nullptr;

			for (UComponentTargetingResult* CompTarget : CurrTileTarget->ComponentTargetResults)
			{
				if (CompTarget->GridObjectComponent == TargetMechComponent)
				{
					CurrCompTarget = CompTarget;
					break;
				}
			}

			if (CurrCompTarget != nullptr)
			{
				bool ResultAlreadyExists = false;

				for (UGridObjectComponentStateUpdate* CompUpdate : CurrCompTarget->MechComponentUpdates)
				{
					if (CompUpdate->GridObjectComponent == GridObjectComponentToAdd)
					{
						ResultAlreadyExists = true;
						break;
					}
				}

				if (!ResultAlreadyExists)
				{
					UGridObjectComponentStateUpdate* CompUpdate = NewObject<UGridObjectComponentStateUpdate>();
					CompUpdate->GridObjectComponent = GridObjectComponentToAdd;

					CurrCompTarget->MechComponentUpdates.Add(CompUpdate);

					return true;
				}
			}
		}
		else
		{
			bool ResultAlreadyExists = false;

			for (UGridObjectComponentStateUpdate* CompUpdate : CurrTileTarget->MechComponentUpdates)
			{
				if (CompUpdate->GridObjectComponent == GridObjectComponentToAdd)
				{
					ResultAlreadyExists = true;
					break;
				}
			}

			if (!ResultAlreadyExists)
			{
				UGridObjectComponentStateUpdate* CompUpdate = NewObject<UGridObjectComponentStateUpdate>();
				CompUpdate->GridObjectComponent = GridObjectComponentToAdd;

				CurrTileTarget->MechComponentUpdates.Add(CompUpdate);

				return true;
			}
		}
	}

	return false;
}

bool UActionResult::TryCreateTileUpdate(FMatrixIndex TileIndexToAdd, FMatrixIndex TargetTileIndex, UGridObjectComponent* TargetMechComponent)
{
	UTileTargetingResult* CurrTileTarget = nullptr;

	for (UTileTargetingResult* TileTarget : TileTargets)
	{
		if (TileTarget->TileIndex == TargetTileIndex)
		{
			CurrTileTarget = TileTarget;
			break;
		}
	}

	if (CurrTileTarget != nullptr)
	{
		if (TargetMechComponent != nullptr)
		{
			UComponentTargetingResult* CurrCompTarget = nullptr;

			for (UComponentTargetingResult* CompTarget : CurrTileTarget->ComponentTargetResults)
			{
				if (CompTarget->GridObjectComponent == TargetMechComponent)
				{
					CurrCompTarget = CompTarget;
					break;
				}
			}

			if (CurrCompTarget != nullptr)
			{
				bool ResultAlreadyExists = false;

				for (UTileDataUpdate* TileUpdate : CurrCompTarget->TileUpdates)
				{
					if (TileUpdate->TileIndex == TileIndexToAdd)
					{
						ResultAlreadyExists = true;
						break;
					}
				}

				if (!ResultAlreadyExists)
				{
					UTileDataUpdate* TileUpdate = NewObject<UTileDataUpdate>();
					TileUpdate->TileIndex = TileIndexToAdd;

					CurrCompTarget->TileUpdates.Add(TileUpdate);

					return true;
				}
			}
		}
		else
		{
			bool ResultAlreadyExists = false;

			for (UTileDataUpdate* TileUpdate : CurrTileTarget->TileUpdates)
			{
				if (TileUpdate->TileIndex == TileIndexToAdd)
				{
					ResultAlreadyExists = true;
					break;
				}
			}

			if (!ResultAlreadyExists)
			{
				UTileDataUpdate* TileUpdate = NewObject<UTileDataUpdate>();
				TileUpdate->TileIndex = TileIndexToAdd;

				CurrTileTarget->TileUpdates.Add(TileUpdate);

				return true;
			}
		}
	}

	return false;
}

TArray<UGridObjectComponentStateUpdate*> UActionResult::GetComponentStateUpdates()
{
	TArray<UGridObjectComponentStateUpdate*> Result;

	for (UTileTargetingResult* TileTarget : TileTargets)
	{
		Result.Append(TileTarget->MechComponentUpdates);

		for (UComponentTargetingResult* CompTarget : TileTarget->ComponentTargetResults)
		{
			Result.Append(CompTarget->MechComponentUpdates);
		}
	}

	return Result;
}
