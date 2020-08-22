module Preprocess = ReCrypt_Sha256_Preprocess;
module Process = ReCrypt_Sha256_Process;

let make = message => {
  message->Preprocess.pad->Process.make;
};
