#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_GunInfo.generated.h"

UCLASS()
class CYBERPUNK_API ACP_GunInfo : public AActor
{
    GENERATED_BODY()

public:
    ACP_GunInfo();

    // 총기 이름 (각각 파츠의 이름은 여기에서 관리)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Info")
    FString GunName;

 
    // GunInfo 관련 속성들을 정의하는 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    ACP_GunInfo* BarrelInfo; // Barrel 파츠 정보

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    ACP_GunInfo* BodyInfo; // Body 파츠 정보

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    ACP_GunInfo* TriggerInfo; // Trigger 파츠 정보


    /*
    // 스코프 정보 (Scope_Info를 자식 클래스에서 상속받아 세부 정보를 정의)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Parts")
    UGun_Info* ScopeInfo;
    */
};
