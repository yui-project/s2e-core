#/bin/bash

# set pwd variable
PWD=$(pwd)

execute_scripts() {
   # patching the path to cspice directory
    git apply patches/cspice_path.patch


    # execute the scripts

    bash scripts/Common/download_EGM96coefficients.sh
    bash scripts/Common/download_HIPcatalogue.sh
    bash scripts/Common/download_nrlmsise00_src_and_table.sh
    bash scripts/Docker_Ubuntu/download_cspice_Linux_gcc.sh
    # copy the sample settings folder to the root dir

    cp -r example/settings/. settings/
    cp -r ExtLibraries/cspice/. settings/environment/cspice/
}
# check if the binary files are already built
if [ ! -f "$PWD/example/build/S2E" ]; then
    execute_scripts
else
    echo "The build directory already exists. Skipping script execution."
fi
    cp -r example/settings/. settings/

# create build directory
/usr/bin/cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ --no-warn-unused-cli -S $PWD/example -B $PWD/example/build -G "Unix Makefiles"

/usr/bin/cmake --build $PWD/example/build --config Debug --target all -j 16 --

cd ./example

./build/S2E ../settings/ ../settings/sample_simulation_base.ini