// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CppProject : ModuleRules
{
	public CppProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		//헤더 추가에 필요한 모듈(플러그인)이 빌드 파일에 필요함(문서에 Build가 Engine이 아니면 따로 추가해야 함). 
		//아래에 추가이후, 에디터 닫고 비주얼스튜디오 프로젝트 컴파일.
		//!Groom 붙이려면 HairStandsCore와 Niagara 모듈 동시에 추가해야함
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayTasks" ,"InputCore", "EnhancedInput", "HairStrandsCore", "Niagara"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
