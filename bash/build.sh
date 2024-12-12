
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

# if not successful, exit
if ! cmake ..; then
    echo "[ERR] cmake failed. Exiting..."
    exit 1
fi

# bulid the project, also check if successful
echo "[INFO] Building project..."
if ! make; then
    echo "[ERR] Project build failed. Exiting..."
    exit 1
fi
echo "[INFO] Project built successfully."

# run the project
./fishc --code ";" 
