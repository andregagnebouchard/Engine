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

REM Copy SDLImage dll's
REM Debug x86
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libjpeg-9.dll" "..\..\Bin\x86\Debug\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libpng16-16.dll" "..\..\Bin\x86\Debug\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libtiff-5.dll" "..\..\Bin\x86\Debug\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libwebp-4.dll" "..\..\Bin\x86\Debug\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\SDL2_image.dll" "..\..\Bin\x86\Debug\SDL2_image.dll" /Y

REM Release x86
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libjpeg-9.dll" "..\..\Bin\x86\Release\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libpng16-16.dll" "..\..\Bin\x86\Release\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libtiff-5.dll" "..\..\Bin\x86\Release\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libwebp-4.dll" "..\..\Bin\x86\Release\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\SDL2_image.dll" "..\..\Bin\x86\Release\SDL2_image.dll" /Y

REM Debug x64
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libjpeg-9.dll" "..\..\Bin\x64\Debug\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libpng16-16.dll" "..\..\Bin\x64\Debug\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libtiff-5.dll" "..\..\Bin\x64\Debug\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libwebp-4.dll" "..\..\Bin\x64\Debug\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\SDL2_image.dll" "..\..\Bin\x64\Debug\SDL2_image.dll" /Y

REM Release x64
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libjpeg-9.dll" "..\..\Bin\x64\Release\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libpng16-16.dll" "..\..\Bin\x64\Release\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libtiff-5.dll" "..\..\Bin\x64\Release\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libwebp-4.dll" "..\..\Bin\x64\Release\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\SDL2_image.dll" "..\..\Bin\x64\Release\SDL2_image.dll" /Y