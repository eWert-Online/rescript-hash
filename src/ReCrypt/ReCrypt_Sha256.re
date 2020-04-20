module Preprocess = ReCrypt_Sha256_Preprocess;
module Process = ReCrypt_Sha256_Process;

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = Preprocess.pad(messageBytes);
  Process.make(paddedMessage);
};