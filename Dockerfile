# Use a C++ dev base image with Python
FROM gcc:13

# Install Python and pip
RUN apt update && apt install -y python3 python3-pip cmake

# Set working directory
WORKDIR /app

# Copy all files into container
COPY . .

# Default command (can be changed later)
CMD ["/bin/bash"]
