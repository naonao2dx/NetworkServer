rm build/NetworkServer
cmake --build ./ --target NetworkServer
mv NetworkServer build/
cd build
./NetworkServer Web console