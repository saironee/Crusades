#pragma once

UENUM(BlueprintType)
enum class EFatherMode : uint8
{
	None			UMETA(DisplayName = "None"),
	Inventory		UMETA(DisplayName = "Inventory"),
	Acting			UMETA(DisplayName = "Acting"),
};