#/bin/bash

# set pwd variable
PWD=$(pwd)

execute_scripts() {
    cd ../
    git apply patches/cspice_path.patch
    git apply patches/egm96_path.patch
    git apply patches/nrlmsise00_path.patch
    git apply patches/cmakelists_path.patch
    # execute the scripts
    cd scripts/Common
    bash download_EGM96coefficients.sh
    bash download_HIPcatalogue.sh
    bash download_nrlmsise00_src_and_table.sh
    cd ../Docker_Ubuntu
    bash download_cspice_Linux_gcc.sh
    # copy the sample settings folder to the root dir
    cd ../../

    git apply patches/cspice_path.patch --reverse
    git apply patches/egm96_path.patch --reverse
    git apply patches/nrlmsise00_path.patch --reverse
    git apply patches/cmakelists_path.patch --reverse


    cp -r example/settings/. settings/
    cp -r ExtLibraries/cspice/. settings/environment/cspice/
}
# check if the binary files are already built
if [ ! -f "$PWD/../example/build/S2E" ]; then
    execute_scripts
else
    echo "The build directory already exists. Skipping script execution."
    cd ../
fi


cd example
# create build directory
/usr/bin/cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ --no-warn-unused-cli -S $PWD -B $PWD/build -G "Unix Makefiles"

/usr/bin/cmake --build $PWD/build --config Debug --target all -j 16 --

./build/S2E ../settings/ ../settings/sample_simulation_base.ini