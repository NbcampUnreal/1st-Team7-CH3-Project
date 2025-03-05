#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"  //  Spot Light Ãß°¡
#include "Components/StaticMeshComponent.h"
#include "CP_TacticalLight.generated.h"

UCLASS()
class CYBERPUNK_API ACP_TacticalLight : public AActor
{
	GENERATED_BODY()

public:
	ACP_TacticalLight();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, Category = "Light")
	USpotLightComponent* TacticalSpotLight;

	void ToggleLight();

	UPROPERTY()
	TArray<UStaticMesh*> PreloadedMeshes;

	void AddLightPart(UStaticMesh* Mesh, FTransform Transform = FTransform::Identity);
};
