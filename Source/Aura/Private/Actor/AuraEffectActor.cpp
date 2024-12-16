// Copyright Dark Horse


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor() {
	/** Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it. */
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(Mesh);
	SphereCollision->SetSphereRadius(50.0f);
}


/** Called when the game starts or when spawned */
void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnSphereCollisionOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnSphereCollisionEndOverlap);
	
}


/*
 * Todo: Change to apply a gameplay effect once learned because this is a shit implementation. Nairafarm needs me 
 */
void AAuraEffectActor::OnSphereCollisionOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult ) {
	if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(OtherActor)) {
		UAbilitySystemComponent* ASComponent = AbilitySystem->GetAbilitySystemComponent();
		const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(ASComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		/*
		 * Todo: this is an abomination for a programmer
		 */
		UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.0f);
		Destroy();
	}
}


void AAuraEffectActor::OnSphereCollisionEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex ) {
	
}


