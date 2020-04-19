/**
 */
let append: (bytes, int, int) => unit;

/**
 */
let append32: (bytes, int32, int) => unit;

/**
 */
let append64: (bytes, int64, int) => unit;

/**
  Convert the given string into a hex representation
 */
let stringToHex: string => string;