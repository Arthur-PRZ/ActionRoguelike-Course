# 📖 Action Roguelike

**An Unreal Engine learning project** making a roguelike game using **C++** following Tom Looman course.

## Introduction

I'm following [Tom Looman's Unreal Engine C++ course](https://www.tomlooman.com/) to improve my skills with Unreal Engine. The game is built step by step as I go through the course, and this README tracks what I learn along the way.

---

## What I learned

### Basics
I covered the fundamentals of Unreal Engine:
- **Editor & workflow** — using the editor, compiling from the IDE, then launching the `.uproject`
- **Reflection system** — exposing variables and functions to the editor and Blueprints with `UPROPERTY()` and `UFUNCTION()`
- **Components** — how they work and how to create them in the constructor with `CreateDefaultSubobject<>()`
- **Blueprints** — creating Blueprint subclasses of my C++ classes to tweak their values and place them in the level
- **Core classes** — the role of `AActor`, `APawn`, `ACharacter` and `AController`
- **Debug** — using `UE_LOG()`, `AddOnScreenDebugMessage()`, `DrawDebugLine()` and `DrawDebugSphere()`

### Enhanced Input System
Handled player movement and actions using **Input Actions** and an **Input Mapping Context**, bound in C++ with `BindAction()`.

![Player movement](Docs/movement.gif)

### Collision System
Created custom **Collision Channels** and defined how my classes respond to them, using `SetCollisionProfileName()`/`SetCollisionEnabled()`, `SetCollisionResponseToChannel()`/`SetCollisionResponseToAllChannels()`. I used it to build the black hole for example.

![Black hole](Docs/black_hole.gif)

### Traces & math structs
I used Unreal's trace functions with `FVector` and `FRotator`:
- **`SweepMultiByObjectType()`** — detects the chest in front of the player so they can open it.

![Chest](Docs/chest.gif)

- **`LineTraceSingleByChannel()`** with **`UKismetMathLibrary::FindLookAtRotation()`** — finds the aimed point, then computes the rotation to give projectiles the right trajectory.

![Projectile](Docs/projectile.gif)

This project is not finished i'm still working on it.

## Authors

Made by [Arthur-PRZ](https://github.com/Arthur-PRZ)
