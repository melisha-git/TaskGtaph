Сборка

```bash
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg install boost-test boost-graph
./vcpkg install benchmark
cd ../
mkdir build
cd build
cmake ..
make
```
