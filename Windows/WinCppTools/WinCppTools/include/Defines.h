#pragma once

/**
 * PARAMETER TYPES
 */
#define in__ 
#define out__
#define ref__

/**
 * BUFFER SIZES
 */
#define CHAR_SMALL_BUFFER      128     // 2^7   old 50
#define CHAR_BUFFER            256     // 2^8   old 120
#define CHAR_MEDIUM_BUFFER     1024    // 2^10  old 500
#define CHAR_LARGE_BUFFER      8192    // 2^13  old 1000
#define CHAR_HUGE_BUFFER       65536   // 2^16  old 10000
#define CHAR_MEGA_BUFFER       1048576

 /**
  * POWERS
  */
#define KILO_POWER             1000
#define MEGA_POWER             1000000

/**
 * FILE PROCESSING 
 */
#define READ   0
#define WRITE  1