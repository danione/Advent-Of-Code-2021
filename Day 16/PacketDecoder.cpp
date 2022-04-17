#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

class Packet{
  bool lenTypeId;
  unsigned int value;
  int version;
  int typeId;
  bool literal;
  unsigned int valueLen;
public:
  vector<Packet*> daughterPackets;
  static int versions;

  Packet(){
    version = 0;
    typeId = 0;
    literal = false;
    value = 0;
    valueLen = 0;
  }

  void assignVersion(int newVersion){
    version = newVersion;
    versions += version;
  }

  int getVersion(){return version;}

  void assignTypeId(int typeId){typeId = typeId;}

  void setLiteral(bool val){literal = val;}

  bool getLiteral(){return literal;}

  void setValue(string val){if(!val.empty()) value = stoull(val, 0, 2);}

  void setValueLen(int newLen){valueLen += newLen;}

  int getValueLen(){return valueLen;}

  void addPackets(Packet* packet){daughterPackets.push_back(packet);}
};

int Packet::versions = 0;

class Decoder{
  unordered_map<char, string> decode;
  string decodedMsg;

public:
  Decoder(){
    decode = {{'0',"0000"}, {'1',"0001"}, {'2',"0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
  }

  void init(){
    ifstream infile("input.txt");
    string input;
    getline(infile, input);
    for(unsigned int i = 0; i < input.length(); i++)
      decodedMsg+= decode[input[i]];
  }

  string normalExtraction(Packet* pack, int bits){
    string val;
    val+=decodedMsg.substr(1, bits + 1);
    decodedMsg.erase(0, bits + 2);
    pack->setValueLen(bits + 2);
    return val;
  }

  void infoHandle(Packet* pack){
    if(decodedMsg.length() <= 0)
      return;

    if(pack->getLiteral()){
      string val;
      while(decodedMsg[0] == '1')
        val += normalExtraction(pack, 3);
      if(decodedMsg[0] == '0'){
        val += normalExtraction(pack, 3);
      }
      if(val.empty()) return;
      pack->setValue(val);
    } else{
      if(decodedMsg[0] == '1'){
        if(decodedMsg.empty())
          return;
        long long unsigned length = stoull(decodedMsg.substr(1,11),0,2);
        decodedMsg.erase(0, 12);
        for(unsigned int i = 0; i < length; i++){
          Packet* newP = decFunc();
          pack->addPackets(newP);
        }
      } else{
        if(decodedMsg.empty())
          return;
        unsigned int length = stoull(decodedMsg.substr(1,15),0,2);
        decodedMsg.erase(0, 16);
        while(length > 0 && decodedMsg.length() > 0){
          Packet* newP = decFunc();
          pack->addPackets(newP);
          length -= newP->getValueLen();
        }
      }
    }
    cout << pack->versions << endl;
  }

  Packet* decFunc(){
    Packet* newP = new Packet();
    if(decodedMsg.length() > 0){
      packetAssign(newP);
      infoHandle(newP);
    }
    return newP;
  }

  void packetAssign(Packet* pack){
    int version = stoull(decodedMsg.substr(0,3), 0, 2);
    int typeId = stoull(decodedMsg.substr(3,3), 0, 2);
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
  dec->decFunc();

  delete dec;
  return 0;
}
