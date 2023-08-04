// Copyright (C) Navpreet Singh, 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VFXReplicationComponent.generated.h"


// Creating a enum to get the input if the Niagara is spawned on a location or attached to an actor
UENUM(BlueprintType)
enum class ENiagaraType : uint8
{
	AtLocation UMETA(DisplayName = "AtLocation"),
	SystemAttached UMETA(DisplayName = "SystemAttached"),
};

class UNiagaraComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOA_API UVFXReplicationComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UNiagaraComponent* NiagaraEffect;

public:

	// Creating a blueprint callable function so it is easier to call niagara vfx throughout the network
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ExecuteNiagaraOnServer(ENiagaraType NiagaraType, UNiagaraSystem* NiagaraSystem,
								USceneComponent* AttachtoComponent, FName AttachPointname = NAME_None, 
								FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator,
								bool bAutoDestroy = true);
	
	UFUNCTION(NetMulticast, Reliable)
	void ExecuteNiagaraOnNetMulticast(ENiagaraType NiagaraType, UNiagaraSystem* NiagaraSystem,
										USceneComponent* AttachtoComponent, FName AttachPointname = NAME_None, 
										FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator,
										bool bAutoDestroy = true);

};
