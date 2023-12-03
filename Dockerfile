FROM talonas/debian-i386-gcc-3.4
RUN rm /etc/apt/sources.list
RUN echo "deb http://archive.debian.org/debian-security jessie/updates main" >> /etc/apt/sources.list.d/jessie.list
RUN echo "deb http://archive.debian.org/debian jessie main" >> /etc/apt/sources.list.d/jessie.list
RUN apt update
RUN apt install -y --force-yes ed
COPY ../../ /usr/src/app
WORKDIR /usr/src/app
RUN chmod +x ./gnu-decstation-ultrix/decstation-ultrix/2.95.3/*
WORKDIR /usr/src/app/nachos-3.4/code/
RUN make
