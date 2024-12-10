
# search build directory. If not found, create it
if [ ! -d "build" ]; then
  mkdir build
fi

# change to build directory
cd build

# run cmake
cmake ..

# bulid the project
cmake --build .

# run the project
./src/fishc
