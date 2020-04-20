module Preprocess = ReCrypt_Sha1_Preprocess;
module Process = ReCrypt_Sha1_Process;

let make = message => {
  let messageBytes = Bytes.of_string(message);
  let paddedMessage = Preprocess.pad(messageBytes);
  Process.make(paddedMessage);
};