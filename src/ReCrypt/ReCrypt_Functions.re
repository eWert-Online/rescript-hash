/**
  * Logical functions [§4.1]
  */

let rotr = (x, n) => {
  Int64.logor(Int64.shift_right_logical(x, n), Int64.shift_left(x, 64 - n));
};

let change = (x, y, z) => {
  Int64.logand(x, y)->Int64.logxor(Int64.logand(Int64.lognot(x), z));
};

let majority = (x, y, z) => {
  Int64.logand(x, y)
  ->Int64.logxor(Int64.logand(x, z))
  ->Int64.logxor(Int64.logand(y, z));
};

let parity = (x, y, z) => {
  x->Int64.logxor(y)->Int64.logxor(z);
};

module Sha256 = {
  let sum0 = x => {
    rotr(x, 2)->Int64.logxor(rotr(x, 13))->Int64.logxor(rotr(x, 22));
  };

  let sum1 = x => {
    rotr(x, 6)->Int64.logxor(rotr(x, 11))->Int64.logxor(rotr(x, 25));
  };

  let sigma0 = x => {
    rotr(x, 7)
    ->Int64.logxor(rotr(x, 18))
    ->Int64.logxor(Int64.shift_right_logical(x, 3));
  };

  let sigma1 = x => {
    rotr(x, 17)
    ->Int64.logxor(rotr(x, 19))
    ->Int64.logxor(Int64.shift_right_logical(x, 10));
  };
};

module Sha512 = {
  let sum0 = x => {
    rotr(x, 28)->Int64.logxor(rotr(x, 34))->Int64.logxor(rotr(x, 39));
  };

  let sum1 = x => {
    rotr(x, 14)->Int64.logxor(rotr(x, 18))->Int64.logxor(rotr(x, 41));
  };

  let sigma0 = x => {
    rotr(x, 1)
    ->Int64.logxor(rotr(x, 8))
    ->Int64.logxor(Int64.shift_right_logical(x, 7));
  };

  let sigma1 = x => {
    rotr(x, 19)
    ->Int64.logxor(rotr(x, 61))
    ->Int64.logxor(Int64.shift_right_logical(x, 6));
  };
};