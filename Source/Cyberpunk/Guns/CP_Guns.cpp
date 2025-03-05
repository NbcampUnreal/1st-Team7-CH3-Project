#include "CP_Guns.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CP_Player.h"
#include "CP_Projectile.h"
#include "Cyberpunk.h"

#include "Core/CP_GameInstance.h"
#include "Core/CP_PlayerHUD.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootScene);

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootScene);

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootScene);

    // 파츠 정보 
    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    // 나이아가라 이펙트 
    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootScene);
    NiagaraEffect->SetAutoActivate(false);
    NiagaraEffect->SetVisibility(false);
    NiagaraEffect->Deactivate();


    // 오디오 컴포넌트
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootScene);

    static ConstructorHelpers::FClassFinder<AActor> HitEffectBP(TEXT("Blueprint'/Game/FXVarietyPack/Blueprints/BP_ky_hit2.BP_ky_hit2_C'"));
    if (HitEffectBP.Succeeded())
    {
        HitEffectBPClass = HitEffectBP.Class;
    }

    AActor* OwnerActor = GetOwner();
    ACP_Player* Player = Cast<ACP_Player>(OwnerActor);
    if (Player)
    {
        InventoryRef = Player->PlayerInventory;
        UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] InventoryRef successfully set."));
    }
    // 발사 타이머
    AmmoCount = 0;
    MaxAmmo = 0;

    //발사할 프로젝타일 
    static ConstructorHelpers::FClassFinder<ACP_Projectile> ProjectileBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BP_Projectile.BP_Projectile_C'"));
    if (ProjectileBPClass.Succeeded())
    {
        ProjectileClass = ProjectileBPClass.Class;
    }

    // 발사 사운드 
    static ConstructorHelpers::FObjectFinder<USoundCue> FireSoundCueAsset(TEXT("SoundCue'/Game/Gun_BluePrint/MuzzleFlash/Demo/FPWeapon/Cue/FirstPersonTemplateWeaponFire02_Cue.FirstPersonTemplateWeaponFire02_Cue'"));
    if (FireSoundCueAsset.Succeeded() && AudioComponent)
    {
        AudioComponent->SetSound(FireSoundCueAsset.Object);
    }

    //기본 파츠 로드 
    LoadGunParts();

}


void ACP_Guns::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld())
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    TacticalLight = GetWorld()->SpawnActor<ACP_TacticalLight>(ACP_TacticalLight::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParams);

    if (TacticalLight)
    {

        // 총기 바디에 붙이기
        TacticalLight->AttachToComponent(BodyMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Light"));
    }

}


// 틱 함수 
void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ACP_Guns::EquipPart(const FString& PartName, EGunPartType PartType)
{
    if (PartType == EGunPartType::Barrel)
    {
        if (BarrelInfo)
        {
            BarrelInfo->Initialize(PartName);
            BarrelMesh->SetSkeletalMesh(BarrelInfo->GetMesh()->SkeletalMesh);
        }
    }
    else if (PartType == EGunPartType::Body)
    {
        if (BodyInfo)
        {
            BodyInfo->Initialize(PartName);
            BodyMesh->SetSkeletalMesh(BodyInfo->GetMesh()->SkeletalMesh);
        }
    }
    else if (PartType == EGunPartType::Trigger)
    {
        if (TriggerInfo)
        {
            TriggerInfo->Initialize(PartName);
            TriggerMesh->SetSkeletalMesh(TriggerInfo->GetMesh()->SkeletalMesh);
        }
    }
}





//기본 파츠 로드 
void ACP_Guns::LoadGunParts()
{
    USkeletalMesh* BarrelSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
    if (BarrelSkeletalMesh)
    {
        BarrelMesh->SetSkeletalMesh(BarrelSkeletalMesh);
        if (BarrelInfo)
        {
            BarrelInfo->Initialize("SK_BarrelBulletScatter");
        }

        UNiagaraSystem* NiagaraAsset = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, TEXT("NiagaraSystem'/Game/Gun_BluePrint/MuzzleFlash/MuzzleFlash/Niagara/NS_MuzzleFlash.NS_MuzzleFlash'")));
        if (NiagaraAsset)
        {
            NiagaraEffect->SetAsset(NiagaraAsset);
            NiagaraEffect->SetupAttachment(BarrelMesh, FName("Muzzle"));
        }
    }

    USkeletalMesh* BodySkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
    if (BodySkeletalMesh)
    {
        BodyMesh->SetSkeletalMesh(BodySkeletalMesh);
        BodyInfo->Initialize("SK_BodyFire");
    }

    USkeletalMesh* TriggerSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerSingle.SK_TriggerSingle")));
    if (TriggerSkeletalMesh)
    {
        TriggerMesh->SetSkeletalMesh(TriggerSkeletalMesh);
        TriggerInfo->Initialize("SK_TriggerAuto");
        AmmoCount = TriggerInfo->MagazineCapacity;
        MaxAmmo = TriggerInfo->MagazineCapacity * 2;
    }
}

//void ACP_Guns::StartFire()
//{
//    if (!bIsFiring)
//    {
//        bIsFiring = true;
//        Fire(); // 즉시 한 발 발사
//        GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ACP_Guns::Fire, FireRate, true);
//    }
//}
//
//void ACP_Guns::StopFire()
//{
//    if (bIsFiring)
//    {
//        bIsFiring = false;
//        GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
//    }
//}


// 무기 발사 
void ACP_Guns::Fire()
{
    UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
    if (GameInstance == nullptr)
    {
        CP_LOG(Warning, TEXT("GameInstance == nullptr"));
        return;
    }

    UCP_PlayerHUD* Hud = GameInstance->GetPlayerHUD();
    if (Hud == nullptr)
    {
        CP_LOG(Warning, TEXT("Hud == nullptr"));
        return;
    }

    if (!BarrelInfo) return;
    if (!TriggerInfo || AmmoCount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo"));
        return;
    }

    AmmoCount--;
    Hud->UpdateAmmo(AmmoCount);

    AActor* OwnerActor = GetOwner();
    if (!OwnerActor) return;

    APawn* OwnerPawn = Cast<APawn>(OwnerActor);
    if (!OwnerPawn) return;

    APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
    if (!PC) return;

    // 카메라 위치와 회전값
    FVector CameraLocation;
    FRotator CameraRotation;
    PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * 5000.0f); // 카메라 방향으로 5000 유닛 거리 체크

    // 레이캐스트
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(GetOwner()); // 플레이어 무시

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, QueryParams);

    FVector HitLocation = bHit ? HitResult.ImpactPoint : TraceEnd; // 히트한 지점이 있으면 그곳을 사용, 없으면 최대 거리 사용

    // 총구 위치에서 목표 지점까지의 방향 설정
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));
    FVector FireDirection = (HitLocation - MuzzleLocation).GetSafeNormal(); // 단위 벡터로 변환

    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();
        NiagaraEffect->SetVisibility(true);
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACP_Guns::DeactivateNiagaraEffect, 0.1f, false);
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    if (BarrelInfo->bIsHitscan)
    {
        FHitResult BulletHit;
        bool bBulletHit = GetWorld()->LineTraceSingleByChannel(BulletHit, MuzzleLocation, HitLocation, ECC_GameTraceChannel1, QueryParams);

        FVector FinalHitLocation = bBulletHit ? BulletHit.ImpactPoint : HitLocation;

        if (bBulletHit && BulletHit.GetActor())
        {
            ApplyDamage(BulletHit.GetActor());
        }

        if (HitEffectBPClass)
        {
            AActor* HitEffect = GetWorld()->SpawnActor<AActor>(HitEffectBPClass, FinalHitLocation, FRotator::ZeroRotator);
            if (HitEffect)
            {
                HitEffect->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
            }
        }
    }
    else
    {
        if (ProjectileClass)
        {
            FRotator ProjectileRotation = FireDirection.Rotation();
            ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);
            if (Projectile)
            {
                Projectile->SetOwner(this);
                if (Projectile->ProjectileMovement)
                {
                    FVector Velocity = FireDirection * 12000.f;
                    Projectile->ProjectileMovement->Velocity = Velocity;
                    Projectile->ProjectileMovement->Activate();
                }
            }
        }
    }

    if (PC)
    {
        FRotator CurrentRotation = PC->GetControlRotation();
        float SpeedFactor = (BodyInfo && BodyInfo->MovementSpeed > 0) ? BodyInfo->MovementSpeed : 1.0f;
        float AdjustedRecoilYaw = RecoilYaw / SpeedFactor;
        float AdjustedRecoilPitch = RecoilPitch / SpeedFactor;
        float RandomYaw = FMath::RandRange(-AdjustedRecoilYaw, AdjustedRecoilYaw);
        float RandomPitch = FMath::RandRange(AdjustedRecoilPitch * 0.8f, AdjustedRecoilPitch * 1.2f);
        FRotator NewRotation = CurrentRotation + FRotator(-RandomPitch, RandomYaw, 0);
        PC->SetControlRotation(NewRotation);
    }
}



//npc 총 발사
void ACP_Guns::Fire(FVector FireDirection)
{
    UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
    if (GameInstance == nullptr)
    {
        CP_LOG(Warning, TEXT("GameInstance == nullptr"));
        return;
    }

    UCP_PlayerHUD* Hud = GameInstance->GetPlayerHUD();
    if (Hud == nullptr)
    {
        CP_LOG(Warning, TEXT("Hud == nullptr"));
        return;
    }

    if (!BarrelInfo) return;

    if (!TriggerInfo || AmmoCount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No ammo"));
        return;
    }

    AmmoCount--;
    Hud->UpdateAmmo(AmmoCount);

    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));

    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();
        NiagaraEffect->SetVisibility(true);
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACP_Guns::DeactivateNiagaraEffect, 0.1f, false);
    }

    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    if (ProjectileClass)
    {
        FRotator ProjectileRotation = FireDirection.Rotation();
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);

        if (Projectile)
        {
            Projectile->SetOwner(this);

            AActor* OwnerActor = GetOwner();
            if (OwnerActor && OwnerActor->ActorHasTag("Enemy"))
            {
                Projectile->bIsNPCProjectile = true;
            }

            if (Projectile->ProjectileMovement)
            {
                FVector Velocity = FireDirection * 8000.f;
                Projectile->ProjectileMovement->Velocity = Velocity;
                Projectile->ProjectileMovement->Activate();
            }
        }
    }

}




void ACP_Guns::SetInventory(UCP_Inventory* Inventory)
{
    InventoryRef = Inventory;
}


void ACP_Guns::DeactivateNiagaraEffect()
{
    if (NiagaraEffect)
    {
        NiagaraEffect->Deactivate();
        NiagaraEffect->SetVisibility(false);
    }
}

void ACP_Guns::ApplyDamage(AActor* HitActor)
{
    if (!HitActor) return;

    float TotalDamage = CalculateTotalDamage();

    AActor* OwnerActor = GetOwner();
    AController* OwnerController = nullptr;

    if (OwnerActor)
    {
        APawn* OwnerPawn = Cast<APawn>(OwnerActor);
        if (OwnerPawn)
        {
            OwnerController = OwnerPawn->GetController();
        }
    }

    // 피격 대상이 ACP_CharacterBase를 상속받는지 확인
    ACP_CharacterBase* Character = Cast<ACP_CharacterBase>(HitActor);
    if (Character)
    {
        float AppliedDamage = UGameplayStatics::ApplyDamage(
            Character,  // 적이든 플레이어든 모두 처리 가능
            TotalDamage,
            OwnerController,
            this,
            UDamageType::StaticClass()
        );
    }
}



float ACP_Guns::CalculateTotalDamage()
{
    float TotalDamage = 0.0f;
    if (TriggerInfo) TotalDamage += TriggerInfo->Damage;
    if (BodyInfo) TotalDamage += BodyInfo->Damage;
    if (BarrelInfo) TotalDamage += BarrelInfo->Damage;
    return TotalDamage;
}

void ACP_Guns::Reload()
{
    UCP_GameInstance* GameInstance = Cast<UCP_GameInstance>(UGameplayStatics::GetGameInstance(this));
    if (GameInstance == nullptr)
    {
        CP_LOG(Warning, TEXT("GameInstance == nullptr"));
        return;
    }

    UCP_PlayerHUD* Hud = GameInstance->GetPlayerHUD();
    if (Hud == nullptr)
    {
        CP_LOG(Warning, TEXT("Hud == nullptr"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("[ACP_guns] Reload() called."));
    if (!TriggerInfo)
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_Guns] ERROR: TriggerInfo is nullptr! Cannot reload."));
        return;
    }

    if (!InventoryRef)
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_Guns] ERROR: InventoryRef is nullptr! Cannot reload."));
        return;
    }

    int32 MagazineCapacity = TriggerInfo->MagazineCapacity;
    int32 AmmoBox = InventoryRef->GetItemCount("Ammo Pack");

    if (AmmoBox <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[ACP_Guns] No ammo available for reload!"));
        return;
    }

    if (MaxAmmo <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[ACP_Guns] Not enough reserve ammo to reload!"));
        return;
    }


    int32 AmmoNeeded = MagazineCapacity - AmmoCount;
    int32 AmmoToLoad = FMath::Min(AmmoNeeded, MaxAmmo); // MaxAmmo와 필요한 탄약 중 작은 값 선택

    AmmoCount += AmmoToLoad;
    MaxAmmo -= AmmoToLoad;
    Hud->UpdateAmmo(AmmoCount);
    Hud->UpdateMaxAmmo(MaxAmmo);

    // 사운드 재생
    USoundBase* ReloadSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Gun_BluePrint/Sound/ak_reload.ak_reload'"));
    if (ReloadSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
        UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Reload sound played successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[ACP_Guns] Failed to load reload sound! Check path."));
    }

    // 인벤토리에서 `Ammo` 1개만 제거
    UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Removing 1 Ammo from inventory."));
    FCP_ItemInfo AmmoItem;
    AmmoItem.ItemName = "Ammo Pack";
    AmmoItem.ItemType = ECP_ItemType::Ammo;
    InventoryRef->ReduceItemCountByName("Ammo Pack", 1);

    UE_LOG(LogTemp, Log, TEXT("[ACP_Guns] Reload complete. AmmoCount: %d, MaxAmmo: %d"), AmmoCount, MaxAmmo);
}


void ACP_Guns::ToggleLight()
{
    TacticalLight->ToggleLight();
}

void ACP_Guns::DestroyWeapon()
{
    if (TacticalLight)
    {
        TacticalLight->Destroy();
        TacticalLight = nullptr;
    }

    Destroy();
}

