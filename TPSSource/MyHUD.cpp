// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "ConstructorHelpers.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"


AMyHUD::AMyHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>T_Crosshair(TEXT("Texture2D'/Game/Weapons/crosshair.crosshair'"));
	if (T_Crosshair.Succeeded())
	{
		Crosshair = T_Crosshair.Object;
	}
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	if (Crosshair)
	{
		DrawTextureSimple(Crosshair, Canvas->SizeX * 0.5f - Crosshair->GetSizeX()*0.5f, Canvas->SizeY*0.5f-Crosshair->GetSizeY()*0.5f);
	}
}
