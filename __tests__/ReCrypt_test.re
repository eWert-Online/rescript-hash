open Jest;
open Expect;
open ReCrypt;

type test = {
  input: string,
  output: string,
};

let tests = [|
  {
    input: "unicorn",
    output: "e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27",
  },
  {
    input: "",
    output: "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
  },
  {
    input: "Some pretty long string which probably exeed the length of one message block (now it really does it...aaaaaaaaaaaaaaaaaaaaaaah)",
    output: "f2dc19af2097fba02ce5a3293ae7981ee782a8c2b879e76922a095985168a3f57cb64ba716d7aa905ca6d0a06c21ab0cfd3d103527338b635032369ec3567448",
  },
  {
    input: "This message is exactly one bit longer than one word: 658f14df49932d6b40a4e4d8424196af7c3477397818e59e748f722186",
    output: "384b8be9a3d0d13a73b32806d4087c47f236b0692420a2cd023c52403310f7fcb68c637ce55b9cd12aeafeffa3a94f9e96300238989b4b1d27f98c17491c2321",
  },
|];

describe("Sha512", () => {
  describe("make()", () => {
    test("\"" ++ tests[0].input ++ "\"", () =>
      expect(Sha512.make(tests[0].input)) |> toBe(tests[0].output)
    );
    test("\"" ++ tests[1].input ++ "\"", () =>
      expect(Sha512.make(tests[1].input)) |> toBe(tests[1].output)
    );
    test("\"" ++ tests[2].input ++ "\"", () =>
      expect(Sha512.make(tests[2].input)) |> toBe(tests[2].output)
    );
    test("\"" ++ tests[3].input ++ "\"", () =>
      expect(Sha512.make(tests[3].input)) |> toBe(tests[3].output)
    );
  })
});