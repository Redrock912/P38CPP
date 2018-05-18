// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "Player/MyCharacter.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Char = Cast<AMyCharacter>(TryGetPawnOwner());

	if (Char&&Char->IsValidLowLevel())
	{
		Speed = Char->GetVelocity().Size();
		Direction = CalculateDirection(Char->GetVelocity(), Char->GetActorRotation());

		bIsCrouch = Char->bIsCrouched;
	}
}



