// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatUnit.h"
#include "MechComponent.h"

ACombatUnit::ACombatUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	GridObjectType = EGridObjectType::GOType_CombatUnit;
}

void ACombatUnit::BeginPlay()
{
	Super::BeginPlay();

}

void ACombatUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACombatUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACombatUnit::AddMechComponent(UMechComponent* MechComponent)
{

}

TArray<UMechComponent*> ACombatUnit::GetMechComponentsHavingCollisionBoxes()
{
	TArray<UMechComponent*> Result;

	for (int i = 0; i < UnitMechComponents.Num(); i++)
	{
		TArray<UMechComponent*> SubComponents;

		if (UnitMechComponents[i]->TryGetSubComponents(SubComponents))
		{
			Result.Append(SubComponents);
		}
		else
		{
			Result.Add(UnitMechComponents[i]);
		}
	}

	return Result;
}

TArray<UMechComponent*> ACombatUnit::GetMechComponentsRepresentingFunctionality()
{
	return UnitMechComponents;
}

UMechComponent* ACombatUnit::GetMechMovementComponent()
{
	return MovementComponent;
}

bool ACombatUnit::TryToFall()
{
	UCombatGridManager* CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();

	FTileData TileData;
	if (CombatGridManagerRef->TryGetTileDataByIndex(UnitTileIndex, TileData) && TileData.bIsVoid)
	{
		FMatrixIndex CurrTileIndex = UnitTileIndex;
		CurrTileIndex.IndexZ--;
		bool InBounds = true;

		while (TileData.bIsVoid && InBounds)
		{
			InBounds = CombatGridManagerRef->TryGetTileDataByIndex(UnitTileIndex, TileData);
			if (InBounds && !TileData.bIsVoid)
			{
				if (TileData.TileHolder != nullptr)
				{
					CurrTileIndex.IndexX--;
				}
				else
				{
					FTileData TempTileData;
					CombatGridManagerRef->TryGetTileDataByIndex(UnitTileIndex, TempTileData);
					TempTileData.TileHolder = nullptr;
					CombatGridManagerRef->TryUpdateTileData(UnitTileIndex, TempTileData);

					CombatGridManagerRef->TryGetTileDataByIndex(UnitTileIndex, TempTileData);
					TempTileData.TileHolder = this;
					CombatGridManagerRef->TryUpdateTileData(UnitTileIndex, TempTileData);
				}
			}
			else
			{
				FTileData TempTileData;
				CombatGridManagerRef->TryGetTileDataByIndex(UnitTileIndex, TempTileData);
				TempTileData.TileHolder = nullptr;
				CombatGridManagerRef->TryUpdateTileData(UnitTileIndex, TempTileData);

				this->Destroy();
				
				return true;
			}
		}
	}
	return false;
}

void ACombatUnit::UpdateUnitPosition(FMatrixIndex TileIndexReplacement)
{
	UnitTileIndex = TileIndexReplacement;

	for (UMechComponent* MechComp : UnitMechComponents)
	{
		MechComp->UpdateComponentPosition(TileIndexReplacement);
	}
}

TArray<UGridObjectComponent*> ACombatUnit::GetGridObjectComponents()
{
	TArray<UGridObjectComponent*> Result;

	for (UMechComponent* MechComp : UnitMechComponents)
	{
		Result.Add(MechComp);
	}

	return Result;
}

TArray<UActionResult*> ACombatUnit::GetActionResultArray()
{
	TArray<UActionResult*> Result;

	for (UMechComponent* MechComp : UnitMechComponents)
	{
		Result.Add(MechComp->GetActionResult());
	}

	return Result;
}

 TArray<UGridObjectComponent*> ACombatUnit::GetGridObjectComponentsOccupyingTileIndex(FMatrixIndex TileIndex)
{
	 TArray<UGridObjectComponent*> Result;

	 Result.Append(UnitMechComponents);

	 return Result;
}

