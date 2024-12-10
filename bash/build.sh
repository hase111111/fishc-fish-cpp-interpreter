
# search build directory. If not found, create it
if [ ! -d "build" ]; then
  echo "[ERR] build directory not found. Creating build directory..."
  mkdir build
fi

# change to build directory
cd build

# if not installed, install cmake
if ! command -v cmake &> /dev/null
then
    echo "[ERR] cmake could not be found. Installing cmake..."
    sudo apt-get install cmake
fi

# run cmake
echo "[INFO] Running cmake..."
cmake ..

# bulid the project
cmake --build .
echo "[INFO] Project built successfully."

# run the project
./src/fishc
