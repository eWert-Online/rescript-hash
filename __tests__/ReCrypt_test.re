open Jest;
open Expect;

type test = {
  input: string,
  sha256: string,
  sha512: string,
};

let tests = [|
  {
    input: "unicorn",
    sha256: "c6cb50e7eea0df1fd3eaf52ada2358f5423afd7c0b5ee2395231a9b3208ffcaf",
    sha512: "e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27",
  },
  {
    input: "",
    sha256: "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
    sha512: "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
  },
  {
    input: "Some pretty long string which probably exeed the length of one message block (now it really does it...aaaaaaaaaaaaaaaaaaaaaaah)",
    sha256: "69c22a11ab4c21beeb184e4fa40556d41bc4d8fe431618b21715352fac67e9ec",
    sha512: "f2dc19af2097fba02ce5a3293ae7981ee782a8c2b879e76922a095985168a3f57cb64ba716d7aa905ca6d0a06c21ab0cfd3d103527338b635032369ec3567448",
  },
  {
    input: "This message is exactly one bit longer than one 128bit word: f49932d6b40a4e4d8424196af7c3477397818e59e748f722186",
    sha256: "1a99b57fe8b12fcc8294f9238d1c1e893d19d798bd20a45a19f1d45d2543f891",
    sha512: "048093ddb5126f147c056cd7e99b741df0423a45e6305ecf542e9612e6b450a113c9bf79c689d421077893c56a2b712d940ac543123cd7dbb11c865f4daae53e",
  },
  {
    input: "This message is exactly one bit longer than a 64bit word",
    sha256: "15cba6d94c28070f62aa1a16e51d44c0514f0acd5272d482ae3cfdb9a4f79f29",
    sha512: "af07decb831f19434525de42f36e9317695f8e52158a3141308e653b67007ede719c0bbd43a5418b1bf9180ef050c580ff3d787279ab0b4d8a259f148f0abfcd",
  },
|];

describe("Sha512", () => {
  describe("make()", () => {
    test("\"" ++ tests[0].input ++ "\"", () =>
      expect(ReCrypt.Sha512.make(tests[0].input)) |> toBe(tests[0].sha512)
    );
    test("\"" ++ tests[1].input ++ "\"", () =>
      expect(ReCrypt.Sha512.make(tests[1].input)) |> toBe(tests[1].sha512)
    );
    test("\"" ++ tests[2].input ++ "\"", () =>
      expect(ReCrypt.Sha512.make(tests[2].input)) |> toBe(tests[2].sha512)
    );
    test("\"" ++ tests[3].input ++ "\"", () =>
      expect(ReCrypt.Sha512.make(tests[3].input)) |> toBe(tests[3].sha512)
    );
    test("\"" ++ tests[4].input ++ "\"", () =>
      expect(ReCrypt.Sha512.make(tests[4].input)) |> toBe(tests[4].sha512)
    );
  })
});

describe("Sha256", () => {
  describe("make()", () => {
    test("\"" ++ tests[0].input ++ "\"", () =>
      expect(ReCrypt.Sha256.make(tests[0].input)) |> toBe(tests[0].sha256)
    );
    test("\"" ++ tests[1].input ++ "\"", () =>
      expect(ReCrypt.Sha256.make(tests[1].input)) |> toBe(tests[1].sha256)
    );
    test("\"" ++ tests[2].input ++ "\"", () =>
      expect(ReCrypt.Sha256.make(tests[2].input)) |> toBe(tests[2].sha256)
    );
    test("\"" ++ tests[3].input ++ "\"", () =>
      expect(ReCrypt.Sha256.make(tests[3].input)) |> toBe(tests[3].sha256)
    );
    test("\"" ++ tests[4].input ++ "\"", () =>
      expect(ReCrypt.Sha256.make(tests[4].input)) |> toBe(tests[4].sha256)
    );
  })
});