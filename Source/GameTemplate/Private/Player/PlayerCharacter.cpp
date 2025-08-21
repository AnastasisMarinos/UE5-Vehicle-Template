// © Anastasis Marinos


#include "Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Camera Component & Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom Arm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	//Setting spring arm defaults for camera lag.
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->CameraLagSpeed = 20.0f;
	SpringArm->CameraRotationLagSpeed = 25.0f;

	CameraSensitivity = 0.5f;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Sets the input mapping context to register key presses for input actions.
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Player Input & Movement //
// Called to bind functionality to input.
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayerMove);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayerLook);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &APlayerCharacter::PlayerJump);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &APlayerCharacter::PlayerStartCrouch);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &APlayerCharacter::PlayerStopCrouch);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &APlayerCharacter::PlayerStartSprint);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &APlayerCharacter::PlayerStopSprint);
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &APlayerCharacter::PlayerInteract);
	}
}

void APlayerCharacter::PlayerMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FVector ForwardVector = GetActorForwardVector();
	const FVector RightVector = GetActorRightVector();

	AddMovementInput(ForwardVector, MovementVector.Y);
	AddMovementInput(RightVector, MovementVector.X);
}

void APlayerCharacter::PlayerLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y * CameraSensitivity);
	AddControllerYawInput(-LookAxisVector.X * CameraSensitivity);
}

void APlayerCharacter::PlayerJump(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Input : Jump"));
	Jump();
}

void APlayerCharacter::PlayerStartCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Input : Start Crouch"));
}

void APlayerCharacter::PlayerStopCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Input : Stop Crouch"));
}

void APlayerCharacter::PlayerStartSprint()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Input : Start Sprint"));	
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void APlayerCharacter::PlayerStopSprint()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Input : Stop Sprint"));
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void APlayerCharacter::PlayerInteract(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Purple, TEXT("Input : Interact"));	
}

