// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCamera.h"

// Sets default values
ACombatCamera::ACombatCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACombatCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACombatCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACombatCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACombatCamera::SetDefaultPosition(UCameraComponent* Camera)
{
	FTransform Transform = Camera->GetRelativeTransform();
	FVector Vector = Transform.GetTranslation();
	float Angle = Transform.GetRotation().Euler().Y;
	float RadAngle = Angle * PI / 180 * -1;
	float Distance = MinZoomDistance + (MaxZoomDistance - MinZoomDistance) / 2;

	float Z = Distance * sin(RadAngle);
	float X = Distance * cos(RadAngle) * -1;

	Vector.Z = Z;
	Vector.X = X;
	Transform.SetTranslation(Vector);
	Camera->SetRelativeTransform(Transform);
}

FTransform ACombatCamera::CalculateZoomTransform(FTransform Transform, float ZoomingScale)
{
	FVector Vector = Transform.GetTranslation();
	float Angle = Transform.GetRotation().Euler().Y;
	float RadAngle = Angle * PI / 180 * -1;
	float Z = Vector.Z + sin(RadAngle) * ZoomStep * ZoomingScale;
	float X = Vector.X + cos(RadAngle) * ZoomStep * ZoomingScale * -1;
	float Distance = sqrt(pow(Z, 2) + pow(X, 2));

	if (Distance > MaxZoomDistance)
	{
		Z = sin(RadAngle) * MaxZoomDistance;
		X = cos(RadAngle) * MaxZoomDistance * -1;
	}
	if (Distance < MinZoomDistance || Z < 0)
	{
		Z = sin(RadAngle) * MinZoomDistance;
		X = cos(RadAngle) * MinZoomDistance * -1;
	}

	Vector.Z = Z;
	Vector.X = X;
	Transform.SetTranslation(Vector);

	return Transform;
}

