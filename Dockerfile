# Use a C++ dev base image with Python
FROM gcc:13

# Install Python and pip, cmake, and other necessary tools
RUN apt update && apt install -y \
    python3 \
    python3-pip \
    cmake \
    make \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy all files into container
COPY . .

# Build the C++ application using CMake
WORKDIR /app/engine
RUN mkdir -p build && cd build && \
    cmake .. && \
    make -j$(nproc)

# Create logs directory and copy executable
RUN cp build/bin/backtesting-engine  /app


# Default command - run the backtesting engine
#CMD ["./backtesting-engine"]
# Run with -it
#CMD [ "/bin/bash" ]
CMD ["/bin/bash", "-c", "./backtesting-engine && exec bash"]


