@echo off
if exist build (rmdir /s /q build)
mkdir build
cd build
cmake ..
make
cd ..
echo Build completed!
