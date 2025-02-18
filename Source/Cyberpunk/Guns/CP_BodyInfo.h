#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.h"
#include "CP_BodyInfo.generated.h"

UCLASS(Blueprintable)
class CYBERPUNK_API ACP_BodyInfo : public ACP_GunInfo
{
    GENERATED_BODY()

public:
    ACP_BodyInfo();


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    USkeletalMeshComponent* BodyMesh; 

    // 바디 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    FString PartName;

    // 바디 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float Damage;

    // 이동 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Info")
    float MovementSpeed;

    void InitializeBodyInfo(const FString& MeshName);

    USkeletalMeshComponent* GetBodyMesh() const;
};
