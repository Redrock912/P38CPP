// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DAY4_2_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimInfo")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimInfo")
		float Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimInfo")
	bool bIsCrouch;
};
