#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Packet.h"
using namespace std;

class Decoder{
  unordered_map<char, string> decode;
  string decodedMsg;
  Packet* firstPacket;
public:
  Decoder(){
    decode = {{'0',"0000"}, {'1',"0001"}, {'2',"0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
  }

  Packet* getFirstPacket(){return firstPacket;}

  void init(){
    ifstream infile("input.txt");
    string input;
    getline(infile, input);
    for(unsigned int i = 0; i < input.length(); i++)
      decodedMsg+= decode[input[i]];
    firstPacket = new Packet();
  }

  string normalExtraction(Packet* pack, int bits){
    string val;
    val+=decodedMsg.substr(1, bits + 1);
    decodedMsg.erase(0, bits + 2);
    pack->setValueLen(bits + 2);
    return val;
  }

  void literalHandle(Packet* pack){
    string val;
    while(decodedMsg[0] == '1')
      val += normalExtraction(pack, 3);
    if(decodedMsg[0] == '0'){
      val += normalExtraction(pack, 3);
    }
    if(val.empty()) return;
    pack->setValue(val);
  }

  void operatorCount(Packet* pack, unsigned int length){
    decodedMsg.erase(0, 12);
    for(unsigned int i = 0; i < length; i++){
      Packet* newP = new Packet();
      decFunc(newP);
      pack->addPackets(newP);
    }
  }

  void operatorLen(Packet* pack, unsigned int& length){
    decodedMsg.erase(0, 16);
    while(length > 0 && decodedMsg.length() > 0){
      Packet* newP = new Packet();
      decFunc(newP);
      pack->addPackets(newP);
      length -= newP->getValueLen();
    }
  }

  void infoHandle(Packet* pack){
    if(decodedMsg.length() <= 0)
      return;

    if(pack->getLiteral()){
      literalHandle(pack);
    } else{
      if(decodedMsg.empty())
        return;
      unsigned int length;
      if(decodedMsg[0] == '1'){
        try {length = stoull(decodedMsg.substr(1,11),0,2);} catch (...)
        {decodedMsg.erase();}

        operatorCount(pack, length);
      } else{
        try {length = stoull(decodedMsg.substr(1,15),0,2);} catch (...)
        {decodedMsg.erase();}

        operatorLen(pack, length);
      }
    }
    cout << pack->versions << endl;
  }

  void decFunc(Packet* newP){
    if(decodedMsg.length() > 0){
      packetAssign(newP);
      infoHandle(newP);
    }
  }

  void packetAssign(Packet* pack){
    int version;
    int typeId;

    try {
      version = stoull(decodedMsg.substr(0,3), 0, 2);
      typeId = stoull(decodedMsg.substr(3,3), 0, 2);
    } catch (...) {decodedMsg.erase();}

    pack->assignVersion(version);
    pack->assignTypeId(typeId);
    if(typeId == 4)
      pack->setLiteral(true);
    pack->setValueLen(6);
    decodedMsg.erase(0,6);
  }

};

int main(){
  Decoder* dec = new Decoder();
  dec->init();
  dec->decFunc(dec->getFirstPacket());
  dec->eval();
  delete dec;
  return 0;
}
