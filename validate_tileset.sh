#!/bin/bash
# validate_tileset.sh
# This script validates that assets/tileset.png has dimensions that are multiples of TILE_SIZE.

# Define your expected tile size (in pixels)
TILE_SIZE=8
FILE="assets/tileset.png"

# Check if the file exists
if [ ! -f "$FILE" ]; then
  echo "Error: Tileset file not found: $FILE"
  exit 1
fi

# Get dimensions using ImageMagick's identify command
dimensions=$(identify -format "%w %h" "$FILE")
width=$(echo $dimensions | cut -d' ' -f1)
height=$(echo $dimensions | cut -d' ' -f2)

# Check if width is a multiple of TILE_SIZE
if (( width % TILE_SIZE != 0 )); then
  echo "Error: Tileset width ($width) is not a multiple of TILE_SIZE ($TILE_SIZE)."
  exit 1
fi

# Check if height is a multiple of TILE_SIZE
if (( height % TILE_SIZE != 0 )); then
  echo "Error: Tileset height ($height) is not a multiple of TILE_SIZE ($TILE_SIZE)."
  exit 1
fi

echo "Tileset validation passed: ${width}x${height} is valid."
exit 0
