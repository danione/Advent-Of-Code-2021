#include "Packet.h"
using namespace std;

Packet::Packet(){
  version = 0;
  typeId = 0;
  literal = false;
  value = 0;
  valueLen = 0;
}

void Packet::assignVersion(int newVersion){
  version = newVersion;
  versions += version;
}

int Packet::getVersion(){return version;}

void Packet::assignTypeId(int typeId){typeId = typeId;}

void Packet::setLiteral(bool val){literal = val;}

bool Packet::getLiteral(){return literal;}

void Packet::setValue(string val){if(!val.empty()) value = stoull(val, 0, 2);}

void Packet::setValueLen(int newLen){valueLen += newLen;}

int Packet::getValueLen(){return valueLen;}

void Packet::addPackets(Packet* packet){daughterPackets.push_back(packet);}

int Packet::versions = 0;
