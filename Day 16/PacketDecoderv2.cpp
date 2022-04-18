#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <stdexcept>
using namespace std;

struct Packet{
  int version_;
  int typeId_;
  long long value_;
  vector<pair<int, Packet*>> packets;
};

class PacketDecoder{
  string line;
  unordered_map<char, string> decode;
public:

  PacketDecoder(){
    decode = {{'0',"0000"}, {'1',"0001"}, {'2',"0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

    string dec;
    ifstream infile("input.txt");

    getline(infile, dec);
    for(int i = 0; i < dec.length(); i++)
      line += decode[dec[i]];
    }

    int read (int advance, int& indexAt) {
     int result = (int)stoull(line.substr(indexAt, advance), 0, 2);
     indexAt += advance;
     return result;
    }

    pair<int,Packet*> parsePacket(int& pos){

      int version = read(3, pos);
      int typeId = read(3, pos);

      if(typeId == 4){
        int chunk = read(5, pos);
        long long value = chunk & 0b1111; // get only the last 4 bits
        while(chunk & 0b10000) // if the first bit is 1, then continue
        {
          chunk = read(5, pos);
          value <<= 4;
          value += chunk & 0b1111;
        }
        return pair<int,Packet*>(pos, new Packet{.version_ = version, .typeId_ = typeId, .value_ = value});
      } else {
        bool mode = read(1, pos);
        if(!mode){
          int bits_length = read(15, pos);
          int start = pos;
          pos = pos + bits_length;
          vector<pair<int,Packet*>> packets;
          while(start < pos){
            auto packet = parsePacket(start);
            start = packet.first;
            packets.push_back(packet);
          }
          return pair<int,Packet*>(pos, new Packet{.version_ = version, .typeId_ = typeId, .packets = packets});
        } else{
          int count = read(11, pos);
          vector<pair<int,Packet*>> packets;
          for(int i = 0; i < count; i++){
            auto packet = parsePacket(pos);
            pos = packet.first;
            packets.push_back(packet);
          }
          return pair<int,Packet*>(pos, new Packet{.version_ = version, .typeId_ = typeId, .packets = packets});
        }
      }
    }
};

int versionCaller(Packet* pack){
  int sum = pack->version_;

  for(auto p: pack->packets)
    sum += versionCaller(p.second);

  return sum;
}

long long eval(Packet* pack){
  int id = pack->typeId_;

  if(id == 0){
    long long sum = 0;
    for(auto p: pack->packets)
      sum += eval(p.second);
    return sum;
  } else if(id == 1){
    long long product = 1;
    for(auto p: pack->packets)
      product *= eval(p.second);
    return product;
  } else if(id == 2){
    long long min = INT_MAX;
    for(auto p: pack->packets){
      long long ev = eval(p.second);
      if(min > ev) min = ev;
    }
    return min;
  }else if(id == 3){
    long long max = INT_MIN;
    for(auto p: pack->packets){
      long long ev = eval(p.second);
      if(max < ev) max = ev;
    }
    return max;
  } else if(id == 4) return pack->value_;
  else if(id == 5)
    return eval(pack->packets[0].second) > eval(pack->packets[1].second);
  else if(id == 6)
    return eval(pack->packets[0].second) < eval(pack->packets[1].second);
  else if(id == 7)
    return eval(pack->packets[0].second) == eval(pack->packets[1].second);
  else
    throw bad_typeid();

}

int main(){
  PacketDecoder* decoder = new PacketDecoder();
  int start = 0;
  Packet* pack = decoder->parsePacket(start).second;
  cout << eval(pack) << endl;


  return 0;
}
