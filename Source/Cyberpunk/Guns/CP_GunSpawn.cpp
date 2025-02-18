#include "CP_GunSpawn.h"
#include "CP_Guns.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "Engine/World.h"

// 생성자에서 Tick 활성화
ACP_GunSpawn::ACP_GunSpawn()
{
    PrimaryActorTick.bCanEverTick = true;  // Tick 함수가 호출되도록 설정

    // 기본적으로 루트 씬을 설정
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    // 플랫폼 메쉬를 설정
    PlatformMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlatformMesh"));
    PlatformMesh->SetupAttachment(RootScene);
}

void ACP_GunSpawn::BeginPlay()
{
    Super::BeginPlay();

    // 스폰 총기 파츠
    SpawnGunParts();
}

void ACP_GunSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // SpawnedPart가 유효하면 자기 자신을 중심으로 회전
    if (SpawnedPart)
    {
        FRotator RotationSpeed(0, 100 * DeltaTime, 0); // Yaw 방향(위에서 봤을 때 반시계 방향)
        SpawnedPart->AddLocalRotation(RotationSpeed);
    }
}

void ACP_GunSpawn::SpawnGunParts()
{
    if (BarrelMeshes.Num() > 0 && BodyMeshes.Num() > 0 && TriggerMeshes.Num() > 0)
    {
        // 각 파츠에서 랜덤으로 하나를 선택
        int32 RandomBarrelIndex = FMath::RandRange(0, BarrelMeshes.Num() - 1);
        int32 RandomBodyIndex = FMath::RandRange(0, BodyMeshes.Num() - 1);
        int32 RandomTriggerIndex = FMath::RandRange(0, TriggerMeshes.Num() - 1);

        // 선택된 파츠에 대한 스켈레탈 메쉬 설정
        USkeletalMeshComponent* SpawnedBarrel = NewObject<USkeletalMeshComponent>(this);
        USkeletalMeshComponent* SpawnedBody = NewObject<USkeletalMeshComponent>(this);
        USkeletalMeshComponent* SpawnedTrigger = NewObject<USkeletalMeshComponent>(this);

        // 하나의 파츠만 스폰
        USkeletalMeshComponent* SelectedPart = nullptr;

        // 랜덤으로 선택된 파츠를 하나만 스폰
        if (FMath::RandBool()) // Barrel 선택
        {
            SelectedPart = SpawnedBarrel;
            if (SelectedPart && BarrelMeshes.IsValidIndex(RandomBarrelIndex))
            {
                SelectedPart->SetSkeletalMesh(BarrelMeshes[RandomBarrelIndex]);
            }
        }
        else if (FMath::RandBool()) // Body 선택
        {
            SelectedPart = SpawnedBody;
            if (SelectedPart && BodyMeshes.IsValidIndex(RandomBodyIndex))
            {
                SelectedPart->SetSkeletalMesh(BodyMeshes[RandomBodyIndex]);
            }
        }
        else // Trigger 선택
        {
            SelectedPart = SpawnedTrigger;
            if (SelectedPart && TriggerMeshes.IsValidIndex(RandomTriggerIndex))
            {
                SelectedPart->SetSkeletalMesh(TriggerMeshes[RandomTriggerIndex]);
            }
        }

        if (SelectedPart)
        {
            SelectedPart->SetupAttachment(RootComponent); // RootComponent에 붙이기
            SelectedPart->RegisterComponent(); // 컴포넌트 등록
            SelectedPart->SetWorldLocation(GetActorLocation() + FVector(0, 0, 50)); // Z축으로 +50만큼 위로 스폰
            SelectedPart->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f)); // 스케일을 2배로 설정
            SpawnedPart = SelectedPart; // 스폰된 파츠를 SpawnedPart에 저장
        }

        // 디버깅을 위한 로그 출력
        UE_LOG(LogTemp, Warning, TEXT("Spawned Part: %s"), *SelectedPart->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Missing part meshes for spawn!"));
    }
}
