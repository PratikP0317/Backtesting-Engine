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
RUN mkdir -p logs && \
    cp build/bin/backtesting-engine .

# Copy sample data if it exists
RUN if [ -f ../data/spy_minute.csv ]; then \
    cp ../data/spy_minute.csv sample_data.csv; \
    else \
    echo "timestamp,symbol,open,high,low,close,volume,trade_count,vwap" > sample_data.csv && \
    echo "2025-06-13 12:23:00+00:00,SPY,100.0,101.0,99.0,100.5,1000,10,100.2" >> sample_data.csv && \
    echo "2025-06-13 12:24:00+00:00,SPY,100.5,102.0,100.0,101.5,1200,12,101.0" >> sample_data.csv; \
    fi

# Default command - run the backtesting engine
CMD ["./backtesting-engine"]
