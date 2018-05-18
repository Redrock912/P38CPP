// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS_GM.h"
#include "TPS_PC.h"
#include "Player/MyCharacter.h"
#include "ConstructorHelpers.h"

ATPS_GM::ATPS_GM()
{
	// bp 가져와서 쓰기위해선 이방법을
	static ConstructorHelpers::FClassFinder<ATPS_PC>PC_Class(TEXT("Blueprint'/Game/Blueprints/BP_PC.BP_PC'"));
	if (PC_Class.Succeeded())
	{
		PlayerControllerClass = PC_Class.Class;
	}

	static ConstructorHelpers::FClassFinder<AMyCharacter>TPS_Class(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter2.BP_MyCharacter2_C'"));
	if (TPS_Class.Succeeded())
	{
		DefaultPawnClass = TPS_Class.Class;
	}
	
	/*PlayerControllerClass = ATPS_PC::StaticClass();
	DefaultPawnClass = AMyCharacter::StaticClass();*/
}

