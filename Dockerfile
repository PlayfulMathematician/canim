
FROM ubuntu:latest


WORKDIR /
RUN apt-get update -y
RUN apt-get install git curl zip unzip cmake tar tree -y 

RUN git clone https://github.com/microsoft/vcpkg.git


RUN cd vcpkg && ./bootstrap-vcpkg.sh --disableMetrics


RUN cd ..
COPY . canim
RUN mkdir canim/out
RUN ls
RUN cd canim && /vcpkg/vcpkg install  
