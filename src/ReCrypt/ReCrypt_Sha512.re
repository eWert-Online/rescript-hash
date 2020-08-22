module Preprocess = ReCrypt_Sha512_Preprocess;
module Process = ReCrypt_Sha512_Process;

let make = message => {
  message->Preprocess.pad->Process.make;
};
