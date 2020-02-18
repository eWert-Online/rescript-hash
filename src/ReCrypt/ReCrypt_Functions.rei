let rotr: (int64, int) => int64;
let change: (int64, int64, int64) => int64;
let majority: (int64, int64, int64) => int64;

module Sha256: {
  let sum0: int64 => int64;
  let sum1: int64 => int64;
  let sigma0: int64 => int64;
  let sigma1: int64 => int64;
};

module Sha512: {
  let sum0: int64 => int64;
  let sum1: int64 => int64;
  let sigma0: int64 => int64;
  let sigma1: int64 => int64;
};