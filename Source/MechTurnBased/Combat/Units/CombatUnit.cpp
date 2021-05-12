// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatUnit.h"
#include "CoreMechComponent.h"
#include "MovementMechComponent/MovementMechComponent.h"
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
	if (MechComponent->IsA<UMovementMechComponent>())
	{
		MovementMechComponent = Cast<UMovementMechComponent>(MechComponent);
	}
	else
	{
		if (MechComponent->IsA<UCoreMechComponent>())
		{
			CoreMechComponent = Cast<UCoreMechComponent>(MechComponent);
		}
		else 
		{
			MechComponents.Add(MechComponent);
		}
	}
}

TArray<UMechComponent*> ACombatUnit::GetMechComponentsHavingCollisionBoxes()
{
	TArray<UMechComponent*> Result;

	for (int i = 0; i < MechComponents.Num(); i++)
	{
		TArray<UMechComponent*> SubComponents;

		if (MechComponents[i]->TryGetSubComponents(SubComponents))
		{
			Result.Append(SubComponents);
		}
		else
		{
			Result.Add(MechComponents[i]);
		}
	}

	return Result;
}

TArray<UMechComponent*> ACombatUnit::GetMechComponentsRepresentingFunctionality()
{
	return MechComponents;
}

UMechComponent* ACombatUnit::GetMechMovementComponent()
{
	return MovementMechComponent;
}

bool ACombatUnit::TryToFall()
{
	return MovementMechComponent->TryToFall();
}

TArray<UGridObjectComponent*> ACombatUnit::GetGridObjectComponents()
{
	TArray<UGridObjectComponent*> Result;

	for (UMechComponent* MechComp : MechComponents)
	{
		Result.Add(MechComp);
	}

	return Result;
}

TArray<UActionResult*> ACombatUnit::GetActionResultArray()
{
	TArray<UActionResult*> Result;

	for (UMechComponent* MechComp : MechComponents)
	{
		Result.Add(MechComp->GetActionResult());
	}

	return Result;
}

TArray<UGridObjectComponent*> ACombatUnit::GetGridObjectComponentsOccupyingTileIndex(FMatrixIndex TileIndex)
{
	TArray<UGridObjectComponent*> Result;

	Result.Append(MechComponents);

	return Result;
}

void ACombatUnit::DestroyCombatUnit()
{
	this->Destroy();
}

bool ACombatUnit::TryPlaceCombatUnitOnTile(FMatrixIndex TileIndex)
{
	return MovementMechComponent->TryAnchorUnitToTile(TileIndex);
}
