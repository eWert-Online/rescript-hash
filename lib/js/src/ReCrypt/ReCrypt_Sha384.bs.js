// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Char = require("bs-platform/lib/js/char.js");
var Bytes = require("bs-platform/lib/js/bytes.js");
var Int64 = require("bs-platform/lib/js/int64.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_int64 = require("bs-platform/lib/js/caml_int64.js");
var ReCrypt_Utils = require("./ReCrypt_Utils.bs.js");
var ReCrypt_Constants = require("./ReCrypt_Constants.bs.js");
var ReCrypt_Functions = require("./ReCrypt_Functions.bs.js");
var ReCrypt_Preprocess = require("./ReCrypt_Preprocess.bs.js");

var initialHash = [
  /* int64 */[
    /* hi */-876896931,
    /* lo */3238371032
  ],
  /* int64 */[
    /* hi */1654270250,
    /* lo */914150663
  ],
  /* int64 */[
    /* hi */-1856437926,
    /* lo */812702999
  ],
  /* int64 */[
    /* hi */355462360,
    /* lo */4144912697
  ],
  /* int64 */[
    /* hi */1731405415,
    /* lo */4290775857
  ],
  /* int64 */[
    /* hi */-1900787065,
    /* lo */1750603025
  ],
  /* int64 */[
    /* hi */-619958771,
    /* lo */1694076839
  ],
  /* int64 */[
    /* hi */1203062813,
    /* lo */3204075428
  ]
];

function make(message) {
  var messageBytes = Bytes.of_string(message);
  var message$1 = ReCrypt_Preprocess.Sha384_512.pad(messageBytes);
  var chunks = message$1.length / 128 | 0;
  var a = Caml_array.caml_array_get(initialHash, 0);
  var b = Caml_array.caml_array_get(initialHash, 1);
  var c = Caml_array.caml_array_get(initialHash, 2);
  var d = Caml_array.caml_array_get(initialHash, 3);
  var e = Caml_array.caml_array_get(initialHash, 4);
  var f = Caml_array.caml_array_get(initialHash, 5);
  var g = Caml_array.caml_array_get(initialHash, 6);
  var h = Caml_array.caml_array_get(initialHash, 7);
  for(var i = 0 ,i_finish = chunks - 1 | 0; i <= i_finish; ++i){
    var w = Caml_array.caml_make_vect(80, Int64.zero);
    for(var t = 0; t <= 15; ++t){
      Caml_array.caml_array_set(w, t, ReCrypt_Utils.int64_of_bytes(message$1, (i << 7) + (t << 3) | 0));
    }
    for(var t$1 = 16; t$1 <= 79; ++t$1){
      Caml_array.caml_array_set(w, t$1, Caml_int64.add(Caml_int64.add(Caml_int64.add(ReCrypt_Functions.Sha384_512.sigma1(Caml_array.caml_array_get(w, t$1 - 2 | 0)), Caml_array.caml_array_get(w, t$1 - 7 | 0)), ReCrypt_Functions.Sha384_512.sigma0(Caml_array.caml_array_get(w, t$1 - 15 | 0))), Caml_array.caml_array_get(w, t$1 - 16 | 0)));
    }
    var originalA = a;
    var originalB = b;
    var originalC = c;
    var originalD = d;
    var originalE = e;
    var originalF = f;
    var originalG = g;
    var originalH = h;
    for(var t$2 = 0; t$2 <= 79; ++t$2){
      var temp1 = Caml_int64.add(Caml_int64.add(Caml_int64.add(Caml_int64.add(h, ReCrypt_Functions.Sha384_512.sum1(e)), ReCrypt_Functions.Sha384_512.change(e, f, g)), Caml_array.caml_array_get(ReCrypt_Constants.sha384, t$2)), Caml_array.caml_array_get(w, t$2));
      var temp2 = Caml_int64.add(ReCrypt_Functions.Sha384_512.sum0(a), ReCrypt_Functions.Sha384_512.majority(a, b, c));
      h = g;
      g = f;
      f = e;
      e = Caml_int64.add(d, temp1);
      d = c;
      c = b;
      b = a;
      a = Caml_int64.add(temp1, temp2);
    }
    a = Caml_int64.add(originalA, a);
    b = Caml_int64.add(originalB, b);
    c = Caml_int64.add(originalC, c);
    d = Caml_int64.add(originalD, d);
    e = Caml_int64.add(originalE, e);
    f = Caml_int64.add(originalF, f);
    g = Caml_int64.add(originalG, g);
    h = Caml_int64.add(originalH, h);
  }
  var sha384raw = Bytes.make(48, Char.chr(0));
  ReCrypt_Utils.append64(sha384raw, a, 0);
  ReCrypt_Utils.append64(sha384raw, b, 8);
  ReCrypt_Utils.append64(sha384raw, c, 16);
  ReCrypt_Utils.append64(sha384raw, d, 24);
  ReCrypt_Utils.append64(sha384raw, e, 32);
  ReCrypt_Utils.append64(sha384raw, f, 40);
  return ReCrypt_Utils.stringToHex(Bytes.to_string(sha384raw));
}

exports.make = make;
/* No side effect */