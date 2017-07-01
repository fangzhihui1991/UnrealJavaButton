$engine='C:\Program Files\Epic Games\UE_4.16'
# Set to the Unreal-style path to the project
$javabo='C:/Users/user/UnrealJavaButton/JavaBo/JavaBo.uproject'

$ubt=$engine+'\Engine\Binaries\DotNET\UnrealBuildTool.exe'

Invoke-Expression "& ""$ubt"" JavaBo Development Win64 -project=""$javabo"" -editorrecompile -NoHotReloadFromIDE"
