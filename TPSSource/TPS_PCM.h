// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "TPS_PCM.generated.h"

/**
 * 
 */
UCLASS()
class DAY4_2_API ATPS_PCM : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ATPS_PCM();
	
	virtual void BeginPlay() override;
	// virtual void Tick 이 아니고 카메라는 다른걸 쓴다.
	virtual void UpdateCamera(float DeltaTime) override;

	// Camera value for crouched position
	float CrouchOffset;
	float DefaultCameraZ;

	float NormalFOV = 90.0f;	
	float IronsightFOV = 60.0f;	 
	

};
