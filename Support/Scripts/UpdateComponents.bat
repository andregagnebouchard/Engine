REM Create output directories if it doesn't already exist
mkdir "..\..\Bin\Debug\x86\"
mkdir "..\..\Bin\Release\x86\"
mkdir "..\..\Bin\Debug\x64\"
mkdir "..\..\Bin\Release\x64\"

REM Copy GLEW dependencies dll's
copy "..\..\Components\glew-2.0.0\bin\Release\Win32\glew32.dll" 	"..\..\Bin\Debug\x86\glew32.dll" /Y
copy "..\..\Components\glew-2.0.0\bin\Release\Win32\glew32.dll" 	"..\..\Bin\Release\x86\glew32.dll" /Y
copy "..\..\Components\glew-2.0.0\bin\Release\x64\glew32.dll" 		"..\..\Bin\Debug\x64\glew32.dll" /Y
copy "..\..\Components\glew-2.0.0\bin\Release\x64\glew32.dll" 		"..\..\Bin\Release\x64\glew32.dll" /Y

REM Copy SDL dll's
copy "..\..\Components\SDL2-2.0.5\lib\x86\SDL2.dll" 						"..\..\Bin\Debug\x86\SDL2.dll" /Y
copy "..\..\Components\SDL2-2.0.5\lib\x86\SDL2.dll" 						"..\..\Bin\Release\x86\SDL2.dll" /Y
copy "..\..\Components\SDL2-2.0.5\lib\x64\SDL2.dll" 						"..\..\Bin\Debug\x64\SDL2.dll" /Y
copy "..\..\Components\SDL2-2.0.5\lib\x64\SDL2.dll" 						"..\..\Bin\Release\x64\SDL2.dll" /Y

REM Copy SDLImage dll's
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libjpeg-9.dll" 		"..\..\Bin\Debug\x86\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libpng16-16.dll" 	"..\..\Bin\Debug\x86\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libtiff-5.dll" 			"..\..\Bin\Debug\x86\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libwebp-4.dll" 		"..\..\Bin\Debug\x86\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\SDL2_image.dll" 	"..\..\Bin\Debug\x86\SDL2_image.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libjpeg-9.dll" 		"..\..\Bin\Release\x86\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libpng16-16.dll" 	"..\..\Bin\Release\x86\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libtiff-5.dll" 			"..\..\Bin\Release\x86\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\libwebp-4.dll" 		"..\..\Bin\Release\x86\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x86\SDL2_image.dll" 	"..\..\Bin\Release\x86\SDL2_image.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libjpeg-9.dll" 		"..\..\Bin\Debug\x64\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libpng16-16.dll" 	"..\..\Bin\Debug\x64\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libtiff-5.dll" 			"..\..\Bin\Debug\x64\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libwebp-4.dll" 		"..\..\Bin\Debug\x64\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\SDL2_image.dll" 	"..\..\Bin\Debug\x64\SDL2_image.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libjpeg-9.dll" 		"..\..\Bin\Release\x64\libjpeg-9.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libpng16-16.dll" 	"..\..\Bin\Release\x64\libpng16-16.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libtiff-5.dll" 			"..\..\Bin\Release\x64\libtiff-5.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\libwebp-4.dll" 		"..\..\Bin\Release\x64\libwebp-4.dll" /Y
copy "..\..\Components\SDL2_image-2.0.1\lib\x64\SDL2_image.dll" 	"..\..\Bin\Release\x64\SDL2_image.dll" /Y

REM Copy SFML dll's
copy "..\..\Components\SFML\extlibs\bin\x86\openal32.dll" 	"..\..\Bin\Debug\x86\openal32.dll" /Y
copy "..\..\Components\SFML\extlibs\bin\x86\openal32.dll" 	"..\..\Bin\Release\x86\openal32.dll" /Y
copy "..\..\Components\SFML\extlibs\bin\x64\openal32.dll" 	"..\..\Bin\Debug\x64\openal32.dll" /Y
copy "..\..\Components\SFML\extlibs\bin\x64\openal32.dll" 	"..\..\Bin\Release\x64\openal32.dll" /Y