/**
  Converts the byte array input starting at index j into an int64
 */
let int64_of_bytes: (bytes, int) => int64;

/**
 */
let append32: (bytes, int32, int) => unit;

/**
 */
let append64: (bytes, int64, int) => unit;

/**
 */
let toBytes: (int, bytes) => bytes;

/**
  Convert the given string into a hex representation
 */
let stringToHex: string => string;