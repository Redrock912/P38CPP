// Fill out your copyright notice in the Description page of Project Settings.

#include "P38Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "P38Rocket.h"
#include "Components/ArrowComponent.h"



// Sets default values
AP38Pawn::AP38Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Body(TEXT("StaticMesh'/Game/Data/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Propeller(TEXT("StaticMesh'/Game/Data/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37, -21, 0));
	Right->SetRelativeLocation(FVector(37, 21, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(80, 0, 0));

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Rocket(TEXT("Blueprint'/Game/Blueprint/BP_P38Rocket.BP_P38Rocket'"));
	if (BP_Rocket.Succeeded())
	{
		Rocket = Cast<UClass>(BP_Rocket.Object->GeneratedClass);
	}

}

// Called when the game starts or when spawned
void AP38Pawn::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AP38Pawn::BeginOverlap);
	
}

void AP38Pawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogClass, Warning, TEXT("Overlap"));
}

// Called every frame
void AP38Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddMovementInput(GetActorForwardVector(), 1.0f);

	Left->AddLocalRotation(FRotator(0, 0, 1080 * DeltaTime));
	Right->AddLocalRotation(FRotator(0, 0, 1080 * DeltaTime));
}

// Called to bind functionality to input
void AP38Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AP38Pawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AP38Pawn::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AP38Pawn::Fire);
}

void AP38Pawn::Fire()
{
	UE_LOG(LogClass, Warning, TEXT("Fire"));
	
	//GetWorld()->SpawnActor<AP38Rocket>(AP38Rocket::StaticClass(),Arrow->GetComponentLocation(),Arrow->GetComponentRotation());
	
	/*GetWorld()->SpawnActor<AP38Rocket>(Rocket, Arrow->GetComponentLocation(), Arrow->GetComponentRotation());*/

	GetWorld()->SpawnActor<AP38Rocket>(RocketBlueprint, Arrow->GetComponentLocation(), Arrow->GetComponentRotation());
}

void AP38Pawn::MoveForward(float Value)
{

		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

		AddActorLocalRotation(FRotator(60 * Value*DeltaTime, 0, 0));
	
	
}

void AP38Pawn::Turn(float Value)
{
		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

		AddActorLocalRotation(FRotator(0, 0, 60 * Value*DeltaTime));

}