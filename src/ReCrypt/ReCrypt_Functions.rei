module Sha224_256: {
  let rotr: (int32, int) => int32;
  let change: (int32, int32, int32) => int32;
  let majority: (int32, int32, int32) => int32;
  let parity: (int32, int32, int32) => int32;
  let sum0: int32 => int32;
  let sum1: int32 => int32;
  let sigma0: int32 => int32;
  let sigma1: int32 => int32;
};

module Sha384_512: {
  let rotr: (int64, int) => int64;
  let change: (int64, int64, int64) => int64;
  let majority: (int64, int64, int64) => int64;
  let sum0: int64 => int64;
  let sum1: int64 => int64;
  let sigma0: int64 => int64;
  let sigma1: int64 => int64;
};