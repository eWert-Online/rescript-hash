let k = t => {
  switch (t) {
  | t when t >= 0 && t <= 19 => 0x5A827999l
  | t when t >= 20 && t <= 39 => 0x6ED9EBA1l
  | t when t >= 40 && t <= 59 => 0x8F1BBCDCl
  | t when t >= 60 && t <= 79 => 0xCA62C1D6l
  | _ => 0x00l
  };
};

let initialHash = [|
  0x67452301l,
  0xEFCDAB89l,
  0x98BADCFEl,
  0x10325476l,
  0xC3D2E1F0l,
|];