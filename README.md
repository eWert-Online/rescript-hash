# What is it?

Secure Hash Algorithms implemented in ReasonML based on
[FIPS180-4](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)

# What state is it in?

**Incomplete**

- [ ] SHA-1
- [ ] SHA224
- [x] SHA256
- [ ] SHA-384
- [x] SHA512

# How do I install it?

```
yarn add @ewert-online/re-crypt
```

or

```
npm install @ewert-online/re-crypt --save
```

Then add `@ewert-online/re-crypt` as a dependency to `bsconfig.json`:

```diff
"bs-dependencies": [
+  "@ewert-online/re-crypt"
]
```

# How do I use it?

### SHA-1

_Not yet implemented_

### SHA224

_Not yet implemented_

### SHA256

```reason
let hash = ReCrypt.Sha256.make("unicorn");
```

produces the following hash:

```
c6cb50e7eea0df1fd3eaf52ada2358f5423afd7c0b5ee2395231a9b3208ffcaf
```

### SHA-384

_Not yet implemented_

### SHA512

```reason
let hash = ReCrypt.Sha512.make("unicorn");
```

produces the following hash:

```
e233b19aabc7d5e53826fb734d1222f1f0444c3a3fc67ff4af370a66e7cadd2cb24009f1bc86f0bed12ca5fcb226145ad10fc5f650f6ef0959f8aadc5a594b27
```
