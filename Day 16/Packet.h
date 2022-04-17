#include <vector>
#include <string>
using namespace std;

class Packet{
  bool lenTypeId;
  unsigned int value;
  int version;
  int typeId;
  bool literal;
  unsigned int valueLen;
  vector<Packet*> daughterPackets;
public:
  static int versions;
  Packet();
  void assignVersion(int);
  int getVersion(void);
  void assignTypeId(int);
  void setLiteral(bool);
  bool getLiteral(void);
  void setValue(string);
  void setValueLen(int);
  int getValueLen(void);
  void addPackets(Packet*);
};
