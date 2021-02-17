// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABuilding::SetComponentsRelations()
{
	TArray<UBuildingComponent*> TempComponentsList;
	TempComponentsList.Append(Components);

	UCombatGridManager* CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();
	for (UBuildingComponent* Component : Components)
	{
		Component->OccupiedTileIndex = CombatGridManagerRef->ConvertCoordinatesToIndexes(Component->CollisionBoxRef->GetComponentLocation());
	}

	while (TempComponentsList.Num() > 0)
	{
		for (int i = 1; i < TempComponentsList.Num(); i++)
		{
			int DiffX, DiffY, DiffZ;
			DiffX = abs(TempComponentsList[0]->OccupiedTileIndex.IndexX - TempComponentsList[i]->OccupiedTileIndex.IndexX);
			DiffY = abs(TempComponentsList[0]->OccupiedTileIndex.IndexY - TempComponentsList[i]->OccupiedTileIndex.IndexY);
			DiffZ = abs(TempComponentsList[0]->OccupiedTileIndex.IndexZ - TempComponentsList[i]->OccupiedTileIndex.IndexZ);

			if ((DiffX + DiffY + DiffZ) == 1)
			{
				if (TempComponentsList[0]->IsComponentABase() || TempComponentsList[0]->PreviousComponents.Num() > 0)
				{
					TempComponentsList[i]->NotifyNextComponentsOfAcquirementOfABaseComponent(TempComponentsList[0]);
				}

				if (TempComponentsList[i]->IsComponentABase() || TempComponentsList[i]->PreviousComponents.Num() > 0)
				{
					TempComponentsList[0]->NotifyNextComponentsOfAcquirementOfABaseComponent(TempComponentsList[i]);
				}

				TempComponentsList[0]->NextComponents.Add(TempComponentsList[i]);
				TempComponentsList[i]->NextComponents.Add(TempComponentsList[0]);
			}
		}

		TempComponentsList.RemoveAt(0);
	}
}

void ABuilding::Activate()
{
	SetComponentsRelations();

	for (UBuildingComponent* BuildingComp : Components)
	{
		BuildingComp->ActivateComponent();
	}
}

