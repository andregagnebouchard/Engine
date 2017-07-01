REM Create output directories if it doesn't already exist
mkdir "..\..\Bin\x86\Debug\"
mkdir "..\..\Bin\x86\Release\"
mkdir "..\..\Bin\x64\Debug\"
mkdir "..\..\Bin\x64\Release\"

REM Copy GLEW dll'S
copy "..\..\Components\glew-2.0.0\bin\Release\Win32\glew32.dll" "..\..\Bin\x86\Debug\glew32.dll" /Y
copy "..\..\Components\glew-2.0.0\bin\Release\Win32\glew32.dll" "..\..\Bin\x86\Release\glew32.dll" /Y
copy "..\..\Components\glew-2.0.0\bin\Release\x64\glew32.dll" "..\..\Bin\x64\Debug\glew32.dll" /Y
copy "..\..\Components\glew-2.0.0\bin\Release\x64\glew32.dll" "..\..\Bin\x64\Release\glew32.dll" /Y

REM Copy SDL dll's
copy "..\..\Components\SDL2-2.0.5\lib\x86\SDL2.dll" "..\..\Bin\x86\Debug\SDL2.dll" /Y
copy "..\..\Components\SDL2-2.0.5\lib\x86\SDL2.dll" "..\..\Bin\x86\Release\SDL2.dll" /Y
copy "..\..\Components\SDL2-2.0.5\lib\x64\SDL2.dll" "..\..\Bin\x64\Debug\SDL2.dll" /Y
copy "..\..\Components\SDL2-2.0.5\lib\x64\SDL2.dll" "..\..\Bin\x64\Release\SDL2.dll" /Y