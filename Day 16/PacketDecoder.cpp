#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Packet{
  int version;
  int typeId;
  vector<Packet*> subpackets;
  static int versions;
public:

  Packet(){
    version = 0;
    typeId = 0;
    versions = 0;
  }

  void assignVersion(int newVersion){
    version = newVersion;
    versions += version;
  }

  void assignTypeId(int typeId){
    typeId = typeId;
  }

  void addSubpackets(Packet* newP){
    subpackets.push_back(newP);
  }
};

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
    for(int i = 0; i < input.length(); i++)
      decodedMsg+= decode[input[i]];
  }

  int whichBitIsIt(bool& isVersion, bool& isId, bool& isInfo){
    if(isVersion){
      isVersion = false;
      isId = true;
      return 0;
    } else if(isId){
      isId = false;
      isInfo = true;
      return 1;
    } else {
      currentPackets = string();
      return 2;
    }
  }

  void extract(int bit, int elements){
    if(bit == 0 || bit == 1){
      result = stoi(decodedMsg.substr(0, elements), 0, 2);
      decodedMsg.erase(0, elements);
    }
    else {
      return 0;
    }
  }

  void decodeType4(){
    while(decodedMsg[0] == '1'){
      currentPackets += decodedMsg.substr(1,4);
      decodedMsg.erase(0,5);
    }
    currentPackets += decodedMsg.substr(1,4);
    decodedMsg.erase(0,8);
  }

  void decodeOthers(){
    bool lengthTypeId = (decodedMsg[0] - '0');
    unsigned int length = 0;
    if(lengthTypeId){
      length = decodedMsg.substr(1, 15);
      decodedMsg.erase(0,16);
    }
    else{
      length = decodedMsg.substr(1, 11);
      decodedMsg.erase(0,12);
    }
  }

  void extractPackets(){
    if(currentTypeId == 4){
      decodeType4();
    } else{
      decodeOthers();
    }
  }

  void analysePacket(){
    if(bit == 0)
      currentVersion += result;
    else if(bit == 1)
      currentTypeId += result;
  }

  void decFunc(){
    if(decodedMsg.length() <= 0){
      return;
    }

    bool isVersion = true;
    bool isId = false;
    bool isInfo = false;

    while(isInfo == false){
      int bit = whichBitIsIt(isVersion, isId, isInfo);
      int result = extract(bit);
    }
    extractPackets();
  }
};

int main(){
  Decoder* dec = new Decoder();
  dec->init();
  dec->decFunc();

  delete dec;
  return 0;
}
