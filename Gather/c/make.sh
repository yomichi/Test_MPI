rm -rf build
mkdir build
cd build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../
echo Finish cmake
echo 
cp compile_commands.json ..
make VERBOSE=1
