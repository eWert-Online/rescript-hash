// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var Int64 = require("bs-platform/lib/js/int64.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_int64 = require("bs-platform/lib/js/caml_int64.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function rotr(x, n) {
  return Caml_int64.or_(Caml_int64.lsr_(x, n), Caml_int64.lsl_(x, 64 - n | 0));
}

function change(x, y, z) {
  return Caml_int64.xor(Caml_int64.and_(x, y), Caml_int64.and_(Int64.lognot(x), z));
}

function majority(x, y, z) {
  return Caml_int64.xor(Caml_int64.xor(Caml_int64.and_(x, y), Caml_int64.and_(x, z)), Caml_int64.and_(y, z));
}

function sum0(x) {
  return Caml_int64.xor(Caml_int64.xor(rotr(x, 28), rotr(x, 34)), rotr(x, 39));
}

function sum1(x) {
  return Caml_int64.xor(Caml_int64.xor(rotr(x, 14), rotr(x, 18)), rotr(x, 41));
}

function sigma0(x) {
  return Caml_int64.xor(Caml_int64.xor(rotr(x, 1), rotr(x, 8)), Caml_int64.lsr_(x, 7));
}

function sigma1(x) {
  return Caml_int64.xor(Caml_int64.xor(rotr(x, 19), rotr(x, 61)), Caml_int64.lsr_(x, 6));
}

function append64(hash, value, offset) {
  for(var j = 0; j <= 7; ++j){
    Belt_Array.set(hash, j + offset | 0, Caml_int64.to_int32(Caml_int64.and_(Caml_int64.lsr_(value, 56 - (j << 3) | 0), /* @__PURE__ */Caml_int64.mk(255, 0))));
  }
  return hash;
}

var k = [
  /* @__PURE__ */Caml_int64.mk(-685199838, 1116352408),
  /* @__PURE__ */Caml_int64.mk(602891725, 1899447441),
  /* @__PURE__ */Caml_int64.mk(-330482897, -1245643825),
  /* @__PURE__ */Caml_int64.mk(-2121671748, -373957723),
  /* @__PURE__ */Caml_int64.mk(-213338824, 961987163),
  /* @__PURE__ */Caml_int64.mk(-1241133031, 1508970993),
  /* @__PURE__ */Caml_int64.mk(-1357295717, -1841331548),
  /* @__PURE__ */Caml_int64.mk(-630357736, -1424204075),
  /* @__PURE__ */Caml_int64.mk(-1560083902, -670586216),
  /* @__PURE__ */Caml_int64.mk(1164996542, 310598401),
  /* @__PURE__ */Caml_int64.mk(1323610764, 607225278),
  /* @__PURE__ */Caml_int64.mk(-704662302, 1426881987),
  /* @__PURE__ */Caml_int64.mk(-226784913, 1925078388),
  /* @__PURE__ */Caml_int64.mk(991336113, -2132889090),
  /* @__PURE__ */Caml_int64.mk(633803317, -1680079193),
  /* @__PURE__ */Caml_int64.mk(-815192428, -1046744716),
  /* @__PURE__ */Caml_int64.mk(-1628353838, -459576895),
  /* @__PURE__ */Caml_int64.mk(944711139, -272742522),
  /* @__PURE__ */Caml_int64.mk(-1953704523, 264347078),
  /* @__PURE__ */Caml_int64.mk(2007800933, 604807628),
  /* @__PURE__ */Caml_int64.mk(1495990901, 770255983),
  /* @__PURE__ */Caml_int64.mk(1856431235, 1249150122),
  /* @__PURE__ */Caml_int64.mk(-1119749164, 1555081692),
  /* @__PURE__ */Caml_int64.mk(-2096016459, 1996064986),
  /* @__PURE__ */Caml_int64.mk(-295247957, -1740746414),
  /* @__PURE__ */Caml_int64.mk(766784016, -1473132947),
  /* @__PURE__ */Caml_int64.mk(-1728372417, -1341970488),
  /* @__PURE__ */Caml_int64.mk(-1091629340, -1084653625),
  /* @__PURE__ */Caml_int64.mk(1034457026, -958395405),
  /* @__PURE__ */Caml_int64.mk(-1828018395, -710438585),
  /* @__PURE__ */Caml_int64.mk(-536640913, 113926993),
  /* @__PURE__ */Caml_int64.mk(168717936, 338241895),
  /* @__PURE__ */Caml_int64.mk(1188179964, 666307205),
  /* @__PURE__ */Caml_int64.mk(1546045734, 773529912),
  /* @__PURE__ */Caml_int64.mk(1522805485, 1294757372),
  /* @__PURE__ */Caml_int64.mk(-1651133473, 1396182291),
  /* @__PURE__ */Caml_int64.mk(-1951439906, 1695183700),
  /* @__PURE__ */Caml_int64.mk(1014477480, 1986661051),
  /* @__PURE__ */Caml_int64.mk(1206759142, -2117940946),
  /* @__PURE__ */Caml_int64.mk(344077627, -1838011259),
  /* @__PURE__ */Caml_int64.mk(1290863460, -1564481375),
  /* @__PURE__ */Caml_int64.mk(-1136513023, -1474664885),
  /* @__PURE__ */Caml_int64.mk(-789014639, -1035236496),
  /* @__PURE__ */Caml_int64.mk(106217008, -949202525),
  /* @__PURE__ */Caml_int64.mk(-688958952, -778901479),
  /* @__PURE__ */Caml_int64.mk(1432725776, -694614492),
  /* @__PURE__ */Caml_int64.mk(1467031594, -200395387),
  /* @__PURE__ */Caml_int64.mk(851169720, 275423344),
  /* @__PURE__ */Caml_int64.mk(-1194143544, 430227734),
  /* @__PURE__ */Caml_int64.mk(1363258195, 506948616),
  /* @__PURE__ */Caml_int64.mk(-544281703, 659060556),
  /* @__PURE__ */Caml_int64.mk(-509917016, 883997877),
  /* @__PURE__ */Caml_int64.mk(-976659869, 958139571),
  /* @__PURE__ */Caml_int64.mk(-482243893, 1322822218),
  /* @__PURE__ */Caml_int64.mk(2003034995, 1537002063),
  /* @__PURE__ */Caml_int64.mk(-692930397, 1747873779),
  /* @__PURE__ */Caml_int64.mk(1575990012, 1955562222),
  /* @__PURE__ */Caml_int64.mk(1125592928, 2024104815),
  /* @__PURE__ */Caml_int64.mk(-1578062990, -2067236844),
  /* @__PURE__ */Caml_int64.mk(442776044, -1933114872),
  /* @__PURE__ */Caml_int64.mk(593698344, -1866530822),
  /* @__PURE__ */Caml_int64.mk(-561857047, -1538233109),
  /* @__PURE__ */Caml_int64.mk(-1295615723, -1090935817),
  /* @__PURE__ */Caml_int64.mk(-479046869, -965641998),
  /* @__PURE__ */Caml_int64.mk(-366583396, -903397682),
  /* @__PURE__ */Caml_int64.mk(566280711, -779700025),
  /* @__PURE__ */Caml_int64.mk(-840897762, -354779690),
  /* @__PURE__ */Caml_int64.mk(-294727304, -176337025),
  /* @__PURE__ */Caml_int64.mk(1914138554, 116418474),
  /* @__PURE__ */Caml_int64.mk(-1563912026, 174292421),
  /* @__PURE__ */Caml_int64.mk(-1090974290, 289380356),
  /* @__PURE__ */Caml_int64.mk(320620315, 460393269),
  /* @__PURE__ */Caml_int64.mk(587496836, 685471733),
  /* @__PURE__ */Caml_int64.mk(1086792851, 852142971),
  /* @__PURE__ */Caml_int64.mk(365543100, 1017036298),
  /* @__PURE__ */Caml_int64.mk(-1676669620, 1126000580),
  /* @__PURE__ */Caml_int64.mk(-885112138, 1288033470),
  /* @__PURE__ */Caml_int64.mk(-60457430, 1501505948),
  /* @__PURE__ */Caml_int64.mk(987167468, 1607167915),
  /* @__PURE__ */Caml_int64.mk(1246189591, 1816402316)
];

function pad(msg) {
  var size = (msg.length + 16 | 0) + 1 | 0;
  while(size % 128 !== 0) {
    size = size + 1 | 0;
  };
  var length = msg.length;
  var bytes = Belt_Array.makeBy(size, (function (index) {
          if (index < length) {
            return msg.charCodeAt(index) | 0;
          } else if (index === length) {
            return 128;
          } else {
            return 0;
          }
        }));
  var va = (length << 3);
  for(var i = 1; i <= 15; ++i){
    Belt_Array.set(bytes, bytes.length - i | 0, va & 255);
    va = (va >> 8);
  }
  return bytes;
}

function make(message) {
  var message$1 = pad(message);
  var chunks = message$1.length / 128 | 0;
  var a = {
    contents: /* @__PURE__ */Caml_int64.mk(-1056596264, -876896931)
  };
  var b = {
    contents: /* @__PURE__ */Caml_int64.mk(914150663, 1654270250)
  };
  var c = {
    contents: /* @__PURE__ */Caml_int64.mk(812702999, -1856437926)
  };
  var d = {
    contents: /* @__PURE__ */Caml_int64.mk(-150054599, 355462360)
  };
  var e = {
    contents: /* @__PURE__ */Caml_int64.mk(-4191439, 1731405415)
  };
  var f = {
    contents: /* @__PURE__ */Caml_int64.mk(1750603025, -1900787065)
  };
  var g = {
    contents: /* @__PURE__ */Caml_int64.mk(1694076839, -619958771)
  };
  var h = {
    contents: /* @__PURE__ */Caml_int64.mk(-1090891868, 1203062813)
  };
  for(var i = 0; i < chunks; ++i){
    var w = Belt_Array.make(80, Caml_int64.zero);
    for(var t = 0; t <= 15; ++t){
      for(var j = 0; j <= 7; ++j){
        var result = Caml_int64.add(Caml_int64.lsl_(Belt_Option.getWithDefault(Belt_Array.get(w, t), Caml_int64.zero), 8), Caml_int64.of_int32(Belt_Option.getWithDefault(Belt_Array.get(message$1, j + ((i << 7) + (t << 3) | 0) | 0), 0) & 255));
        Belt_Array.set(w, t, result);
      }
    }
    for(var t$1 = 16; t$1 <= 79; ++t$1){
      var t2 = Belt_Option.getWithDefault(Belt_Array.get(w, t$1 - 2 | 0), Caml_int64.zero);
      var t7 = Belt_Option.getWithDefault(Belt_Array.get(w, t$1 - 7 | 0), Caml_int64.zero);
      var t15 = Belt_Option.getWithDefault(Belt_Array.get(w, t$1 - 15 | 0), Caml_int64.zero);
      var t16 = Belt_Option.getWithDefault(Belt_Array.get(w, t$1 - 16 | 0), Caml_int64.zero);
      var result$1 = Caml_int64.add(Caml_int64.add(Caml_int64.add(sigma1(t2), t7), sigma0(t15)), t16);
      Belt_Array.set(w, t$1, result$1);
    }
    var originalA = a.contents;
    var originalB = b.contents;
    var originalC = c.contents;
    var originalD = d.contents;
    var originalE = e.contents;
    var originalF = f.contents;
    var originalG = g.contents;
    var originalH = h.contents;
    Belt_Array.forEachWithIndex(k, (function(w){
        return function (t, k) {
          var temp1 = Caml_int64.add(Caml_int64.add(Caml_int64.add(Caml_int64.add(h.contents, sum1(e.contents)), change(e.contents, f.contents, g.contents)), k), Belt_Option.getWithDefault(Belt_Array.get(w, t), Caml_int64.zero));
          var temp2 = Caml_int64.add(sum0(a.contents), majority(a.contents, b.contents, c.contents));
          h.contents = g.contents;
          g.contents = f.contents;
          f.contents = e.contents;
          e.contents = Caml_int64.add(d.contents, temp1);
          d.contents = c.contents;
          c.contents = b.contents;
          b.contents = a.contents;
          a.contents = Caml_int64.add(temp1, temp2);
          
        }
        }(w)));
    a.contents = Caml_int64.add(originalA, a.contents);
    b.contents = Caml_int64.add(originalB, b.contents);
    c.contents = Caml_int64.add(originalC, c.contents);
    d.contents = Caml_int64.add(originalD, d.contents);
    e.contents = Caml_int64.add(originalE, e.contents);
    f.contents = Caml_int64.add(originalF, f.contents);
    g.contents = Caml_int64.add(originalG, g.contents);
    h.contents = Caml_int64.add(originalH, h.contents);
  }
  var input = Belt_Array.reduce(append64(append64(append64(append64(append64(append64(Belt_Array.make(48, 0), a.contents, 0), b.contents, 8), c.contents, 16), d.contents, 24), e.contents, 32), f.contents, 40), "", (function (acc, curr) {
          return acc + String.fromCharCode(curr);
        }));
  var hex = "0123456789abcdef";
  return Belt_Array.reduce(input.split(""), "", (function (acc, curr) {
                var charCode = curr.charCodeAt(0) | 0;
                return acc + (hex.charAt((charCode >>> 4) & 15) + hex.charAt(charCode & 15));
              }));
}

exports.make = make;
/* No side effect */
