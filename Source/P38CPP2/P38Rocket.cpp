// Fill out your copyright notice in the Description page of Project Settings.

#include "P38Rocket.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "P38Rocket.h"

// Sets default values
AP38Rocket::AP38Rocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);

	

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Body->SetRelativeRotation(FRotator(-90.0f, 0, 0));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Rocket(TEXT("StaticMesh'/Game/Data/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Body->SetStaticMesh(SM_Rocket.Object);
	}

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	Movement->InitialSpeed = 600.0f;
	Movement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AP38Rocket::BeginPlay()
{
	Super::BeginPlay();
	//SetLifeSpan(5.0f);

	GetWorldTimerManager().SetTimer(TimerHandle,this, &AP38Rocket::Timer, 3.0f, false,3.0f);
	GetWorldTimerManager().ClearTimer(TimerHandle);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AP38Rocket::BeginOverlap);
}

void AP38Rocket::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<APawn>(OtherActor) == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("Overlap %s"), *OtherActor->GetName());
		/*UGameplayStatics::SpawnEmitterAtLocation();
		UGameplayStatics::SpawnSoundAtLocation();*/
	}
}

// Called every frame
void AP38Rocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AP38Rocket::Timer()
{
	Destroy();
}

