#ifndef CURSOR_H
#define CURSOR_H

#include <map>
#include <tuple>
#include <vector>

#include "addr_space.hpp"
#include "axis.hpp"
#include "instruction.hpp"
#include "ram.hpp"

using namespace std;

class Cursor {
  public:
    Cursor(Ram &ramIn) : ram(ramIn) {
      cursorPosition[CODE][X] = 0;
      cursorPosition[CODE][Y] = 0;
      cursorPosition[DATA][X] = 0;
      cursorPosition[DATA][Y] = 0;
    }

    //////// ADDR SPACE API //////////

    void switchAddressSpace();
    AddrSpace getAddressSpace() const;
    Address getAddress() const;

    //////// COORDINATES API /////////

    int getAbsoluteBitIndex() const;
    int getX() const;
    int getY() const;
    void increaseX();
    void increaseY();
    void decreaseX();
    void decreaseY();
    void setBitIndex(int bitIndex);
    void setByteIndex(int byteIndex);
    void goToAddress(Address adr);
    void goToEndOfWord();
    void goToBeginningOfWord();
    void goToBeginningOfNextWord();
    void goToInstructionsAddress();

    /////////// RAM API ////////////

    bool getBit() const;
    void setBit(bool bit);
    void switchBit();
    void eraseByte();
    vector<bool> getWord() const;
    void setWord(vector<bool> word);
    void moveByteUp();
    void moveByteDown();
    bool insertByteAndMoveRestDown();
    bool deleteByteAndMoveRestUp();
    bool isAddressUsed(Address adr);

  private:
    Ram &ram;
    // Selected address space.
    AddrSpace addrSpace = CODE;
    // Selected bit with the cursor.
    map<AddrSpace, map<Axis, int>> cursorPosition;
    // Map of data addresses to instructions that use them.
    static map<int, Instruction> BOUND_DATA_ADDRESSES;

    bool addressReferenced(Address adr);
    vector<Address> getAddressesOfEffectiveInstructions();
    bool shouldNotModifyData(bool insert);
    // vector<Instruction> getEffectiveInstructions();
    void incOrDecAddressesPastTheIndex(AddrSpace space, int index, int delta);
    static void setAddress(vector<bool> &word, int val, int adrIndex);
    void actuallyInsert();
    void actuallyDelete();
    int getBitIndex() const;
    int getAddr() const;
    void setAddr(int addr);
};

#endif
