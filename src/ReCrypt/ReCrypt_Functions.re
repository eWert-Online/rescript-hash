/**
  * Logical functions [§4.1]
  */
module MD5 = {
  let rotl = (x, n) => {
    x lsl n lor x lsr (64 - n);
  };
};

module Sha1 = {
  let rotl = (x, n) => {
    Int32.logor(
      Int32.shift_left(x, n),
      Int32.shift_right_logical(x, 64 - n),
    );
  };

  let change = (x, y, z) => {
    Int32.logand(x, y)->Int32.logxor(Int32.logand(Int32.lognot(x), z));
  };

  let majority = (x, y, z) => {
    Int32.logand(x, y)
    ->Int32.logxor(Int32.logand(x, z))
    ->Int32.logxor(Int32.logand(y, z));
  };

  let parity = (x, y, z) => {
    x->Int32.logxor(y)->Int32.logxor(z);
  };

  let f = (t, x, y, z) => {
    switch (t) {
    | t when t >= 0 && t <= 19 => change(x, y, z)
    | t when t >= 20 && t <= 39 => parity(x, y, z)
    | t when t >= 40 && t <= 59 => majority(x, y, z)
    | t when t >= 60 && t <= 79 => parity(x, y, z)
    | _ => 0x00l
    };
  };
};

module Sha224_256 = {
  let rotr = (x, n) => {
    Int32.logor(
      Int32.shift_right_logical(x, n),
      Int32.shift_left(x, 64 - n),
    );
  };

  let change = (x, y, z) => {
    Int32.logand(x, y)->Int32.logxor(Int32.logand(Int32.lognot(x), z));
  };

  let majority = (x, y, z) => {
    Int32.logand(x, y)
    ->Int32.logxor(Int32.logand(x, z))
    ->Int32.logxor(Int32.logand(y, z));
  };

  let sum0 = x => {
    rotr(x, 2)->Int32.logxor(rotr(x, 13))->Int32.logxor(rotr(x, 22));
  };

  let sum1 = x => {
    rotr(x, 6)->Int32.logxor(rotr(x, 11))->Int32.logxor(rotr(x, 25));
  };

  let sigma0 = x => {
    rotr(x, 7)
    ->Int32.logxor(rotr(x, 18))
    ->Int32.logxor(Int32.shift_right_logical(x, 3));
  };

  let sigma1 = x => {
    rotr(x, 17)
    ->Int32.logxor(rotr(x, 19))
    ->Int32.logxor(Int32.shift_right_logical(x, 10));
  };
};

module Sha384_512 = {
  let rotr = (x, n) => {
    Int64.logor(
      Int64.shift_right_logical(x, n),
      Int64.shift_left(x, 64 - n),
    );
  };

  let change = (x, y, z) => {
    Int64.logand(x, y)->Int64.logxor(Int64.logand(Int64.lognot(x), z));
  };

  let majority = (x, y, z) => {
    Int64.logand(x, y)
    ->Int64.logxor(Int64.logand(x, z))
    ->Int64.logxor(Int64.logand(y, z));
  };

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