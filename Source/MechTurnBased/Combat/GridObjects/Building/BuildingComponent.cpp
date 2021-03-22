// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingComponent.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBuildingComponent::IsComponentABase()
{
	return bIsABase;
}

TArray<UBuildingComponent*> UBuildingComponent::RemoveConnectionToComponent(UBuildingComponent* ComponentRefToRemove)
{
	TArray<UBuildingComponent*> Result;

	for (int i = 0; i < NextComponents.Num(); i++)
	{
		if (NextComponents[i] == ComponentRefToRemove)
		{
			NextComponents.RemoveAt(i);
			break;
		}
	}

	for (int i = 0; i < PreviousComponents.Num(); i++)
	{
		if (PreviousComponents[i] == ComponentRefToRemove)
		{
			PreviousComponents.RemoveAt(i);
			break;
		}
	}

	if (PreviousComponents.Num() == 0 && !bIsABase)
	{
		Result.Add(this);

		for (UBuildingComponent* NextComp : NextComponents)
		{
			Result.Append(NextComp->RemoveConnectionToComponent(this));
		}

		FTileData TileDataToUpdate;
		CombatGridManagerRef->TryGetTileDataByIndex(OccupiedTileIndex, TileDataToUpdate);
		TileDataToUpdate.TileHolder = nullptr;
		CombatGridManagerRef->TryUpdateTileData(OccupiedTileIndex, TileDataToUpdate);
	}

	return Result;
}

bool UBuildingComponent::TryToDestroyYourself()
{
	if (ComponentState.HullPoints == 0)
	{
		TArray<UBuildingComponent*> ComponentsWithoutBaseConnection;

		for (UBuildingComponent* Component : NextComponents)
		{
			ComponentsWithoutBaseConnection.Append(Component->RemoveConnectionToComponent(this));
		}

		for (UBuildingComponent* Component : ComponentsWithoutBaseConnection)
		{
			Component->TryToFall();
		}

		FTileData TileDataToUpdate;
		CombatGridManagerRef->TryGetTileDataByIndex(OccupiedTileIndex, TileDataToUpdate);
		TileDataToUpdate.TileHolder = nullptr;
		CombatGridManagerRef->TryUpdateTileData(OccupiedTileIndex, TileDataToUpdate);

		DeactivateComponent();

		CollisionBoxRef->Deactivate();
		bIsDestroyed = true;

		return true;
	}

	return false;
}

bool UBuildingComponent::TryToFall()
{
	if (PreviousComponents.Num() == 0 && !bIsABase)
	{
		FTileData CurrTileData;
		FMatrixIndex CurrTileIndex = FMatrixIndex(OccupiedTileIndex.IndexX, OccupiedTileIndex.IndexY, OccupiedTileIndex.IndexZ - 1);

		while (CombatGridManagerRef->TryGetTileDataByIndex(CurrTileIndex, CurrTileData))
		{
			if (CurrTileData.TileHolder != nullptr)
			{
				CurrTileData.TileHolder->ApplyEnvironmentalDamage(CurrTileIndex, 1);
				break;
			}

			if (!CurrTileData.bIsVoid)
			{
				break;
			}
		}

		CollisionBoxRef->Deactivate();
		bIsDestroyed = true;

		return true;
	}

	return false;
}

void UBuildingComponent::NotifyNextComponentsOfAcquirementOfABaseComponent(UBuildingComponent* BaseComponent)
{
	if (PreviousComponents.Num() == 0)
	{
		for (UBuildingComponent* Component : NextComponents)
		{
			Component->NotifyNextComponentsOfAcquirementOfABaseComponent(this);
		}
	}

	PreviousComponents.Add(BaseComponent);
}

void UBuildingComponent::UpdateComponentState(FGridObjectComponentState ComponentStateReplacement)
{
	ComponentState = ComponentStateReplacement;

	TryToDestroyYourself();
}

void UBuildingComponent::ActivateComponent()
{
	if (bIsAPlatform)
	{
		FTileData TileData;
		FMatrixIndex TileIndex = OccupiedTileIndex;
		TileIndex.IndexZ++;
		if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, TileData))
		{
			TileData.bIsVoid = false;

			CombatGridManagerRef->TryUpdateTileData(TileIndex, TileData);
		}
	}
}

void UBuildingComponent::DeactivateComponent()
{
	if (bIsAPlatform)
	{
		FTileData TileData;
		FMatrixIndex TileIndex = OccupiedTileIndex;
		TileIndex.IndexZ++;
		if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, TileData))
		{
			AGridObject* GridObjectRef = TileData.TileHolder;
			TileData.bIsVoid = false;

			CombatGridManagerRef->TryUpdateTileData(TileIndex, TileData);

			if (GridObjectRef != nullptr)
			{
				GridObjectRef->TryToFall();
			}
		}
	}
}

bool UBuildingComponent::IsComponentDestroyed()
{
	return bIsDestroyed;
}

FMatrixIndex UBuildingComponent::GetTileToHighlight()
{
	return OccupiedTileIndex;
}
