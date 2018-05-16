// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P38Pawn.generated.h"

UCLASS()
class P38CPP2_API AP38Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP38Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Fire();

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void Turn(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UStaticMeshComponent* Left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UStaticMeshComponent* Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	class UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* Arrow;

	// 블루프린트를 부르는 첫번째 방법
	class UClass* Rocket;

	// 블루프린트를 부르는 두번째 방법
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class TSubclassOf<class AP38Rocket> RocketBlueprint;
};
