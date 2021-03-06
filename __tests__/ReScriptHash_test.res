open Jest
open Expect

type test = {
  input: string,
  md5: string,
  sha1: string,
  sha224: string,
  sha256: string,
  sha384: string,
  sha512: string,
}

let tests = [
  {
    input: "unicorn",
    md5: "1abcb33beeb811dca15f0ac3e47b88d9",
    sha1: "84de6753b298abd027fcd1d790eade2413eafb5a",
    sha224: "983d515094574856a57db3a13741f0a65509bb640bfa551e78fa01d9",
    sha256: "c6cb50e7eea0df1fd3eaf52ada2358f5423afd7c0b5ee2395231a9b3208ffcaf",
    sha384: "de41efa2be0844783ea107630a79246fb1f7b3ab97b35c5e4b70130804f876f64b645c1064a775507a7ac3be457539f2",
    sha512: "e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27",
  },
  {
    input: "",
    md5: "d41d8cd98f00b204e9800998ecf8427e",
    sha1: "da39a3ee5e6b4b0d3255bfef95601890afd80709",
    sha224: "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f",
    sha256: "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
    sha384: "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b",
    sha512: "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
  },
  {
    input: "Some pretty long string which probably exeed the length of one message block (now it really does it...aaaaaaaaaaaaaaaaaaaaaaah)",
    md5: "f59fbeaf0597357d7fb6cf4755211e99",
    sha1: "87fd7e086d40019262d6fc1ceccd9d731afa6be3",
    sha224: "935f26cf156817962231e82021da64b808b3c68fb9ff9f53ce9c75cc",
    sha256: "69c22a11ab4c21beeb184e4fa40556d41bc4d8fe431618b21715352fac67e9ec",
    sha384: "72fc789c77cce0797d67d62d27f93c0fe550b48e3069d4a354430dac61992946b25c37257eaf0df33ea319202de5767e",
    sha512: "f2dc19af2097fba02ce5a3293ae7981ee782a8c2b879e76922a095985168a3f57cb64ba716d7aa905ca6d0a06c21ab0cfd3d103527338b635032369ec3567448",
  },
  {
    input: "This message is exactly one bit longer than one 128bit word: f49932d6b40a4e4d8424196af7c3477397818e59e748f722186",
    md5: "c46500acee5415406c471da700f1511c",
    sha1: "b0aec6e4ac57547d24be7b38768a7c29c9456a7b",
    sha224: "19f7516f806e661dd2b72326bdfee7b4805560122becadb3801d8da7",
    sha256: "1a99b57fe8b12fcc8294f9238d1c1e893d19d798bd20a45a19f1d45d2543f891",
    sha384: "53cf6f7f2520d951de56c82d09954b61ec04e502ac49831a7e0e3cde0a15b096f48e70eb599b26ca4d4f608f36ada480",
    sha512: "048093ddb5126f147c056cd7e99b741df0423a45e6305ecf542e9612e6b450a113c9bf79c689d421077893c56a2b712d940ac543123cd7dbb11c865f4daae53e",
  },
  {
    input: "This message is exactly one bit longer than a 64bit word",
    md5: "7d3febf8022523df2093238bf6a07792",
    sha1: "042a302c0fb5ee74143d99a795bcc1036683f602",
    sha224: "a671f59e0187aef4a1812bb7380e3988b2ed9f41fd2e8a1db91ebbbe",
    sha256: "15cba6d94c28070f62aa1a16e51d44c0514f0acd5272d482ae3cfdb9a4f79f29",
    sha384: "db5889404ed7f067781fcb61f800d58bed3791b7f4eef2ca16984501db5549708bd0170dcf3c9bd2877bc571af65dbf9",
    sha512: "af07decb831f19434525de42f36e9317695f8e52158a3141308e653b67007ede719c0bbd43a5418b1bf9180ef050c580ff3d787279ab0b4d8a259f148f0abfcd",
  },
]

describe("MD5", () =>
  describe("make()", () =>
    tests->Js.Array2.forEach(t =>
      test("\"" ++ (t.input ++ "\""), () =>
        expect(ReScriptHash.MD5.makeU(. t.input)) |> toBe(t.md5)
      )
    )
  )
)

describe("Sha1", () =>
  describe("make()", () =>
    tests->Js.Array2.forEach(t =>
      test("\"" ++ (t.input ++ "\""), () =>
        expect(ReScriptHash.Sha1.makeU(. t.input)) |> toBe(t.sha1)
      )
    )
  )
)

describe("Sha224", () =>
  describe("make()", () =>
    tests->Js.Array2.forEach(t =>
      test("\"" ++ (t.input ++ "\""), () =>
        expect(ReScriptHash.Sha224.makeU(. t.input)) |> toBe(t.sha224)
      )
    )
  )
)

describe("Sha256", () =>
  describe("make()", () =>
    tests->Js.Array2.forEach(t =>
      test("\"" ++ (t.input ++ "\""), () =>
        expect(ReScriptHash.Sha256.makeU(. t.input)) |> toBe(t.sha256)
      )
    )
  )
)

describe("Sha384", () =>
  describe("make()", () =>
    tests->Js.Array2.forEach(t =>
      test("\"" ++ (t.input ++ "\""), () =>
        expect(ReScriptHash.Sha384.makeU(. t.input)) |> toBe(t.sha384)
      )
    )
  )
)

describe("Sha512", () =>
  describe("make()", () =>
    tests->Js.Array2.forEach(t =>
      test("\"" ++ (t.input ++ "\""), () =>
        expect(ReScriptHash.Sha512.makeU(. t.input)) |> toBe(t.sha512)
      )
    )
  )
)
