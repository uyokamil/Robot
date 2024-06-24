// © 2024, Kamil Czarnecki for the 2024 Climate Jam. All rights reserved.

#include "Framework/RobotGameMode.h"
#include "Player/RobotCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARobotGameMode::ARobotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
