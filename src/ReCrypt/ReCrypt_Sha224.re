module Preprocess = ReCrypt_Sha224_Preprocess;
module Process = ReCrypt_Sha224_Process;

let make = message => {
  message->Preprocess.pad->Process.make;
};
