#!/bin/bash

DIRNAME=$1
FILENAME=$2
WORKSPACE=$3

# Function to find Cargo.toml in parent directories
find_cargo() {
    if [ -f "$1/Cargo.toml" ]; then
        echo "$1"
    elif [ "$1" != "/" ]; then
        find_cargo "$(dirname "$1")"
    else
        echo ""
    fi
}

CARGO_DIR=$(find_cargo "$DIRNAME")

if [ "$CARGO_DIR" != "" ]; then
    cd "$CARGO_DIR" && cargo build --bin "$FILENAME"
else
    rustc "$DIRNAME/$FILENAME.rs" -o "$WORKSPACE/rust/target/debug/$FILENAME"
fi
