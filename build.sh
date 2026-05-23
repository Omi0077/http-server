#!/bin/bash

# Build script for HTTP Server project
# This script compiles the main application and sample server

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Project directories
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRC_DIR="$PROJECT_DIR/src"
SAMPLE_DIR="$PROJECT_DIR/sample"
BUILD_DIR="$PROJECT_DIR/build"
INCLUDE_DIR="$PROJECT_DIR/include"

# Compiler flags
CXX_FLAGS="-std=c++17 -Wall -Wextra -O2"
INCLUDE_FLAGS="-I$INCLUDE_DIR"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir -p "$BUILD_DIR"
fi

# Function to compile and link
compile_executable() {
    local source_file=$1
    local output_name=$2
    
    echo -e "${YELLOW}Compiling $source_file -> $output_name...${NC}"
    
    if g++ $CXX_FLAGS $INCLUDE_FLAGS "$source_file" -o "$BUILD_DIR/$output_name"; then
        echo -e "${GREEN}✓ Successfully compiled $output_name${NC}"
    else
        echo -e "${RED}✗ Failed to compile $output_name${NC}"
        return 1
    fi
}

# Compile main application
compile_executable "$SRC_DIR"/*.cpp "main"

# # Compile sample server (optional)
# if [ -f "$SAMPLE_DIR/server.cpp" ]; then
#     compile_executable "$SAMPLE_DIR/server.cpp" "server"
# fi

echo ""
echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${GREEN}================================${NC}"
echo ""
echo "Executables built in: $BUILD_DIR/"
echo "Available executables:"
ls -lh "$BUILD_DIR" | grep -v "^total" | awk '{print "  - " $NF}'
