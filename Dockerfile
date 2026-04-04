
FROM kuyoh/vcpkg:2026.02.27-ubuntu AS vcpkg-canim-base
WORKDIR /canim

COPY . .
RUN apt-get update
RUN    apt-get install python3 -y
RUN apt-get install -y libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev ninja-build cmake
RUN cmake -DCMAKE_TOOLCHAIN_FILE:STRING=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release \
    -H/canim -B/canim/build -G Ninja 
RUN cmake --build /canim/build --config Release --target all -j 6 --
RUN mkdir /canim/out 
RUN cp   /canim/build/lib/* /canim/out
RUN ls /canim/build
