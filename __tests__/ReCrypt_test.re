open Jest;
open Expect;
open ReCrypt;

describe("Sha512", () => {
  test("make(\"unicorn\")", () =>
    expect(Sha512.make("unicorn"))
    |> toBe(
         "e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27",
       )
  );
  test("make(\"\")", () =>
    expect(Sha512.make(""))
    |> toBe(
         "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
       )
  );
  test(
    "make(\"Some pretty long string which probably exeed the length of one message block\")",
    () =>
    expect(
      Sha512.make(
        "Some pretty long string which probably exeed the length of one message block",
      ),
    )
    |> toBe(
         "080f575bf58758f2e57105307c89628c9e60faa868e18997f8d29736f54521b0f4960dff620c5958158466c767aa20f76c4d4d7ffd0e7287fa300790bfe99dd9",
       )
  );
});