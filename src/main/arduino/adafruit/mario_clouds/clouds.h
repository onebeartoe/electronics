// Cloud bitmaps for scrolling pendant project.

#include <Arduino.h>

// Tiles are stored in a 'raw' 16-bit color format (5/6/5 R/G/B);
// no color table, no run-length encoding.  This keeps the blitting
// function simple and quick.  Each tile requires nearly 800 bytes of
// program space, but it's OK as there's not much else going on.

//        Hi   Lo
#define K 0x00,0x00 // Black
#define W 0xFF,0xFF // White
#define B 0x6C,0x3F // Blue (sky)
#define G 0x04,0xBE // Gray (cloud shadow, alt blue really)

// First byte is height of tile in pixels.

const uint8_t PROGMEM
 tile_a[] = { 16, // Left cloud tile
  B,B,B,B,B,B,B,B,B,K,K,B,B,B,B,B,B,B,B,B,B,B,B,B,
  B,B,B,B,B,B,B,B,K,W,W,K,B,B,B,B,B,B,B,B,B,B,B,B,
  B,B,B,B,B,B,B,K,W,W,W,K,B,B,B,B,B,B,B,B,B,B,B,B,
  B,B,B,B,B,B,K,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,B,B,
  B,B,B,B,K,K,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,B,
  B,B,B,K,W,W,W,G,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,
  B,B,B,K,W,W,G,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,
  B,B,B,K,W,G,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,
  B,B,K,W,W,G,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,
  B,K,W,W,W,G,G,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,
  B,K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,K,K,K,B,B,B,
  K,W,W,W,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,B,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,B,
  B,K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,W,K,
  B,B,K,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K },
 tile_b[] = { 16, // Middle (possibly repeating) cloud tile
  B,K,W,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,
  B,K,W,W,G,G,W,G,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,K,B,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,
  K,W,W,W,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,
  B,K,W,W,W,G,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,
  B,K,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,K,K,B,B,B,B,B,
  B,B,K,W,W,G,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,
  B,K,W,W,W,G,G,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,
  B,K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,K,K,K,B,B,B,
  K,W,W,W,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,B,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,B,
  B,K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,W,K,
  B,B,K,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K },
 tile_c[] = { 17, // Right cloud tile
  B,K,W,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,
  B,K,W,W,G,G,W,G,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,G,W,W,W,W,K,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,K,B,B,
  K,W,W,G,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,
  K,W,W,W,G,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,
  B,K,W,W,W,G,W,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,
  B,K,W,W,W,W,W,W,W,W,W,W,W,W,W,W,K,K,K,B,B,B,B,B,
  B,B,K,W,W,W,W,W,W,W,W,W,W,W,K,K,B,B,B,B,B,B,B,B,
  B,K,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,B,B,
  B,K,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,B,
  B,B,K,W,W,W,W,W,W,W,W,W,W,W,W,K,B,B,B,B,B,B,B,B,
  B,B,K,W,W,W,W,W,W,W,W,W,K,K,K,B,B,B,B,B,B,B,B,B,
  B,B,B,K,W,W,W,K,W,W,W,K,B,B,B,B,B,B,B,B,B,B,B,B,
  B,B,B,K,W,W,K,B,K,W,W,W,K,B,B,B,B,B,B,B,B,B,B,B,
  B,B,B,B,B,K,B,B,B,K,K,K,B,B,B,B,B,B,B,B,B,B,B,B,
  B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B };