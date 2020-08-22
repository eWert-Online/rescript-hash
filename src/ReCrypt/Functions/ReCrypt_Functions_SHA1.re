let rotl = (x, n) => {
  Int32.logor(Int32.shift_left(x, n), Int32.shift_right_logical(x, 64 - n));
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
