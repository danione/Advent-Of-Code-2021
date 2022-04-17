#include <vector>
#include <string>
using namespace std;

class Packet{
  bool lenTypeId;
  long long value;
  int version;
  int typeId;
  bool literal;
  unsigned int valueLen;
public:
  static int versions;
  vector<Packet*> daughterPackets;
  Packet();
  void assignVersion(int);
  int getVersion(void);
  void assignTypeId(int);
  int getTypeId(void);
  void setLiteral(bool);
  bool getLiteral(void);
  void setValue(string);
  long long getValue(void);
  void setValueLen(int);
  int getValueLen(void);
  void addPackets(Packet*);
};
