#include "CP_GunSpawn.h"
#include "CP_Guns.h"
#include "CP_BarrelInfo.h"
#include "CP_BodyInfo.h"
#include "CP_TriggerInfo.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"  // SphereComponent 추가

// 생성자에서 Tick 활성화
ACP_GunSpawn::ACP_GunSpawn()
{
    PrimaryActorTick.bCanEverTick = true;  // Tick 함수가 호출되도록 설정

    // 기본적으로 루트 씬을 설정
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    // PlatformMesh와 충돌 영역 설정 (SphereComponent)
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(100.0f);  // 충돌 범위 설정
    CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));
    CollisionComponent->SetupAttachment(RootComponent);

    // 충돌 감지 이벤트 연결
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACP_GunSpawn::OnItemOverlap);
}

void ACP_GunSpawn::BeginPlay()
{
    Super::BeginPlay();

    // 스폰 총기 파츠
    SpawnGunParts();
}

void ACP_GunSpawn::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    // 겹친 파츠의 정보를 출력
    if (OtherActor)
    {
        if (SpawnedPart) // Overlap이 발생했을 때, 스폰된 파츠의 정보를 가져옴
        {
            // Barrel인지 체크
            if (ACP_BarrelInfo* BarrelInfo = Cast<ACP_BarrelInfo>(SpawnedPart))
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawned Barrel Info: %s | Hitscan: %s | Damage: %f"),
                    *BarrelInfo->PartName, BarrelInfo->bIsHitscan ? TEXT("Yes") : TEXT("No"), BarrelInfo->Damage);
            }
            // Body인지 체크
            else if (ACP_BodyInfo* BodyInfo = Cast<ACP_BodyInfo>(SpawnedPart))
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawned Body Info: %s | Damage: %f | MovementSpeed: %f"),
                    *BodyInfo->PartName, BodyInfo->Damage, BodyInfo->MovementSpeed);
            }
            // Trigger인지 체크
            else if (ACP_TriggerInfo* TriggerInfo = Cast<ACP_TriggerInfo>(SpawnedPart))
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawned Trigger Info: %s | Damage: %f | MagazineCapacity: %d"),
                    *TriggerInfo->PartName, TriggerInfo->Damage, TriggerInfo->MagazineCapacity);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Unknown part spawned: %s"), *SpawnedPart->GetName());
            }

            // 파츠를 먹었으면 파괴
            SpawnedPart->Destroy();
            SpawnedPart = nullptr;  // 파츠를 null로 설정하여 참조 해제
        }

        Destroy();  // 현재 Actor도 삭제
    }
}


void ACP_GunSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (SpawnedPart)
    {
        float Amplitude = 0.2f;  // 위아래 이동 범위
        float Speed = 0.7f;       // 움직이는 속도

        // Spawn된 파츠의 초기 위치를 기준으로 Z축 이동
        FVector SpawnLocation = SpawnedPart->GetActorLocation();

        // 사인파를 이용한 부드러운 이동
        float Offset = Amplitude * FMath::Sin(GetWorld()->GetTimeSeconds() * Speed);

        // 현재 위치를 기준으로 X, Y는 그대로 두고, Z축만 변동
        FVector NewLocation = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z + Offset);

        // 새 위치로 파츠 이동
        SpawnedPart->SetActorLocation(NewLocation);
    }


}


void ACP_GunSpawn::SpawnGunParts()
{
    if (BarrelClass && BodyClass && TriggerClass)  // BarrelMeshes가 아니라, AActor 클래스를 활용해야 함
    {
        TSubclassOf<AActor> SelectedClass = nullptr;

        // 랜덤으로 Barrel, Body, Trigger 중 하나 선택
        int32 RandomIndex = FMath::RandRange(0, 2);
        if (RandomIndex == 0)
        {
            SelectedClass = BarrelClass;
        }
        else if (RandomIndex == 1)
        {
            SelectedClass = BodyClass;
        }
        else
        {
            SelectedClass = TriggerClass;
        }

        if (SelectedClass)
        {
            FVector RootLocation = GetActorLocation();  // Root 위치

            // Z축을 확실히 올려서 위치 수정
            FVector SpawnLocation = FVector(RootLocation.X, RootLocation.Y, RootLocation.Z); 

            FRotator SpawnRotation = FRotator::ZeroRotator;
            AActor* NewPart = GetWorld()->SpawnActor<AActor>(SelectedClass, SpawnLocation, SpawnRotation);
            if (NewPart)
            {
                // Body 파츠의 경우, 랜덤으로 메시 초기화
                if (ACP_BodyInfo* BodyInfo = Cast<ACP_BodyInfo>(NewPart))
                {
                    TArray<FString> MeshNames = { "SK_BodyTesla", "SK_BodyNormal", "SK_BodyFire" };
                    FString RandomMeshName = MeshNames[FMath::RandRange(0, MeshNames.Num() - 1)];
                    BodyInfo->Initialize(RandomMeshName);
                }

                // Barrel 파츠의 경우, 랜덤으로 메시 초기화
                else if (ACP_BarrelInfo* BarrelInfo = Cast<ACP_BarrelInfo>(NewPart))
                {
                    TArray<FString> MeshNames = { "SK_BarrelBeam", "SK_BarrelBeamScatter", "SK_BarrelBulletScatter", "SK_BarrelRocketScatter" };
                    FString RandomMeshName = MeshNames[FMath::RandRange(0, MeshNames.Num() - 1)];
                    BarrelInfo->Initialize(RandomMeshName);
                }

                // Trigger 파츠의 경우, 랜덤으로 메시 초기화
                else if (ACP_TriggerInfo* TriggerInfo = Cast<ACP_TriggerInfo>(NewPart))
                {
                    TArray<FString> MeshNames = { "SK_TriggerAuto", "SK_TriggerBurst", "SK_StockStandard", "SK_StockHeavy" };
                    FString RandomMeshName = MeshNames[FMath::RandRange(0, MeshNames.Num() - 1)];
                    TriggerInfo->Initialize(RandomMeshName);
                }

                // Scale을 X, Y, Z 모두 2배로 설정
                NewPart->SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));

                SpawnedPart = NewPart;  // 스폰된 파츠 저장

                UE_LOG(LogTemp, Warning, TEXT("Spawned Part: %s"), *NewPart->GetName());
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Missing part classes for spawn!"));
    }
}
