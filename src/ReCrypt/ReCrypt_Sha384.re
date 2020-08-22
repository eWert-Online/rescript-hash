module Preprocess = ReCrypt_Sha384_Preprocess;
module Process = ReCrypt_Sha384_Process;

let make = message => {
  message->Preprocess.pad->Process.make;
};
