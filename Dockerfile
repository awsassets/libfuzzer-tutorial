FROM ubuntu:18.04

ENV user fuzz

RUN apt-get update
RUN apt-get install -y git build-essential clang zlib1g
RUN adduser $user
ADD ./build.sh /home/$user/build.sh
ADD ./run.sh /home/$user/run.sh
ADD ./harness.cc /home/$user/harness.cc
ADD ./tester.c /home/$user/tester.c
ADD ./make_seeds.py /home/$user/make_seeds.py
COPY ./cpython /home/$user/cpython

RUN chown root:$user /home/$user/build.sh
RUN chmod 750 /home/$user/build.sh
RUN chown root:$user /home/$user/run.sh
RUN chmod 750 /home/$user/run.sh
RUN chown root:$user /home/$user/make_seeds.py
RUN chmod 750 /home/$user/make_seeds.py

RUN /home/$user/build.sh
USER $user
CMD /home/$user/run.sh
