#!/bin/sh
BASE_PATH=/mnt/desktop/work
UBT_PATH=${BASE_PATH}/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe
PJ_PATH=${BASE_PATH}/UnrealJavaButton/JavaBo/JavaBo.uproject
mono "$UBT_PATH" JavaBo Development Linux "$PJ_PATH" -editorrecompile -NoHotReloadFromIDE

