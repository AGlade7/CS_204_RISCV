#include <bits/stdc++.h>
using namespace std;

#define M 32
void write_data_memory();
static unsigned int X[32];
static unsigned int MEM[4000];//only 4000?
static int DMEM[1000000];//give lui in range of 0x00010
static unsigned int instruction_word;
static unsigned int operand1;
static unsigned int operand2;
char Type = '0';
static bitset<M> inst;
static unsigned int des_reg;
static int des_res;
string subtype;
static int imm;
static int  pc = 0;
unsigned int sz = 0;
// 0x14 0xFE32CCE3
// -----------DOUBT------------
// should the instuction memory be in byte format
// like the first 8 bits(1 byte) of instruction in index 0 of MEM then next 8 bits in MEM[1] so that a single instruction will be 32 bits and will take
// MEM[0]-MEM[3] , then next instruction will me from MEM[4] so the pc will be adjusted to move 4 at one time 
// like when they give recursion type code we have to keep in mind that the space there while craeting stack is sp-4 i.e handle the recursion 

// does this handle the msb extension and arithmetic and logical sign extension?
// In provided RISCV refernce card immediate value bit is not correct in U type instruction?
// test >> with Arithmatic shift and logical shift

// checking the instruction set
char op_R_type(bitset<7> op)
{
  bitset<7> opr("0110011");
  if (op == opr)
    return 'R';
  else
    return '0';
}
char op_I_type(bitset<7> op)
{
  bitset<7> opi1("0010011");
  bitset<7> opi2("1100111");
  bitset<7> opi3("0000011");

  if (op == opi1 || op == opi2|| op == opi3)
    return 'I';
  else
    return '0';
}
char op_J_type(bitset<7> op)
{
  bitset<7> opj("1101111");
  if (op == opj)
    return 'J';
  else
    return '0';
}
char op_B_type(bitset<7> op)
{
  bitset<7> opb("1100011");
  if (op == opb)
    return 'B';
  else
    return '0';
}
char op_S_type(bitset<7> op)
{
  bitset<7> ops("0100011");
  if (op == ops)
    return 'S';
  else
    return '0';
}
char op_U_type(bitset<7> op)
{
  bitset<7> opu1("0110111");
  bitset<7> opu2("0010111");
  if (op == opu1 || op == opu2)
    return 'U';
  else
    return '0';
}
// end checking
string findTwoscomplement(string str)
{
    int n = str.length();
 
    // Traverse the string to get first '1' from
    // the last of string
    int i;
    for (i = n-1 ; i >= 0 ; i--)
        if (str[i] == '1')
            break;
 
    // If there exists no '1' concatenate 1 at the
    // starting of string
    if (i == -1)
        return '1' + str;
 
    // Continue traversal after the position of
    // first '1'
    for (int k = i-1 ; k >= 0; k--)
    {
        //Just flip the values
        if (str[k] == '1')
            str[k] = '0';
        else
            str[k] = '1';
    }
 
    // return the modified string
    return str;
}
string subtype_select(bitset<3> func3, bitset<7> func7,bitset<7> op)
{
  string Func3=func3.to_string(),Func7=func7.to_string(),Op = op.to_string();
  switch(Type){
    case 'R':{
      if(Func3=="000" && Func7 =="0000000"){
        subtype="add";
      }
      else if(Func3=="111" && Func7 =="0000000"){
        subtype= "and";
      }
      else if(Func3=="110" && Func7 =="0000000"){
        subtype= "or";
      }
      else if(Func3=="001" && Func7 =="0000000"){
        subtype= "sll";
      }
      else if(Func3=="010" && Func7 =="0000000"){
        subtype= "slt";
      }
      else if(Func3=="101" && Func7 =="0100000"){
        subtype= "sra";
      }
      else if(Func3=="101" && Func7 =="0000000"){
        subtype= "srl";
      }
      else if(Func3=="000" && Func7 =="0100000"){
        subtype= "sub";
      }
      else if(Func3=="100" && Func7 =="0000000"){
        subtype= "xor";
      }
      break;
    }
    case 'I':{
      if(Func3=="000"&& Op =="0010011" ){
        subtype="addi";
      }
      else if(Func3=="111" ){
        subtype="andi";
      }
      else if(Func3=="110" ){
        subtype="ori";
      }
      else if(Func3=="000" && Op =="0000011" ){
        subtype="lb";
      }
      else if(Func3=="001"  && Op =="0000011"){
        subtype="lh";
      }
      else if(Func3=="010"  && Op =="0000011" ){
        subtype="lw";
      }
      else if(Func3=="000" && Op =="1100111" ){
        subtype="jalr";
      }
      else if(Func3=="001" && Op =="0010011" ){
        subtype="slli";
      }
      
      
      break;
    }
    case 'B':{
      if(Func3=="000" ){
        subtype="beq";
      }
      else if(Func3=="001" ){
        subtype="bne";
      }
      else if(Func3=="101" ){
        subtype="bge";
      }
      else if(Func3=="100"  ){
        subtype="blt";
      }
      break;
    }
    case 'J':{
  
        subtype="jal";
      break;
    }
    case 'S':{
      if(Func3=="000" ){
        subtype="sb";
      }
      else if(Func3=="001" ){
        subtype="sh";
      }
      else if(Func3=="010" ){
        subtype="sw";
      }
      break;
    }
    case 'U':{
      if(Op =="0010111" ){
        subtype="auipc";
      }
      else if(Op =="0110111" ){
        subtype="lui";
      }
      break;
    }
    default:{
      cout<<"error"<<endl;
    }
  }

}
void swi_exit() {
  //  write_data_memory();
  cout<<X[3]<<" "<<X[1]<<endl;
   exit(0);
 }

void reset_proc()
{
  for (auto i : X)
  {
    i = 0;
  }
  X[2]=999999;
  for (auto p : MEM)
  {
    p = 0;
  }
  for (auto q : DMEM)  q = 0;
}
// read and write in file start
int read_word(unsigned int *mem, unsigned int address)
{
  int *data;
  data = (int *)(mem + address);
  return *data;
}
void write_word(unsigned int *mem, unsigned int address, unsigned int data)
{
  int *data_p;
  data_p = (int *)(mem + address);
  *data_p = data;
  sz++;
}
// read and write ends
void write_data_memory()
{
  FILE *fp;
  unsigned int i;
  fp = fopen("data_out.mem", "w");
  if (fp == NULL)
  {
    printf("Error opening dataout.mem file for writing\n"); return;
  }
  for (i = 0; i <= 4*sz; i = i + 4){fprintf(fp, "%u %u\n", i, read_word(MEM, i));}
  fclose(fp);
}

void load_program_memory()
{
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen("simple_add.mem", "r");
  if (fp == NULL)
  {
    printf("Error opening input mem file\n");
    exit(1);
  }

  while (fscanf(fp, "%x %x", &address, &instruction) != EOF)
  {
    write_word(MEM, address, instruction);
  }
  write_data_memory();
  fclose(fp);
}

// reads from the instruction memory and updates the instruction register
void fetch()
{
  inst = MEM[pc];
  cout<<inst<<endl;
  bitset<32> exitcode("11101111000000000000000000010001");
  if(inst == exitcode ){
    swi_exit();
  }

}
// reads the instruction register, reads operand1, operand2 fromo register file, decides the operation to be performed in execute stage
void decode()
{
  bitset<7> op;
  bitset<7> func7;
  bitset<3> func3;
  bitset<5> rs1, rs2, rd;

  for (int i = 0; i < 7; i++)
  {
    op[i] = inst[i];
  }
  cout<<op<<endl;
  while (1)
  {
    if (Type == '0')
    {
      Type = op_R_type(op);
    }
    if (Type == '0')
      Type = op_I_type(op);
    if (Type == '0')
      Type = op_J_type(op);
    if (Type == '0')
      Type = op_B_type(op);
    if (Type == '0')
      Type = op_S_type(op);
    if (Type == '0')
      Type = op_U_type(op);
    break;
  }
  cout<< Type<<endl;
  // cout<<inst<<endl;
      int j = 0;
    for (int i = 25; i < 32; i++)
    {
      func7[j] = inst[i];
      j++;
    }
    j = 0;
    for (int i = 12; i < 15; i++)
    {
      func3[j] = inst[i]; j++;
    }
    j = 0;
    for (int i = 15; i < 20; i++)
    {
      rs1[j] = inst[i]; j++;
    }
    operand1 = rs1.to_ulong();
    j = 0;
    for (int i = 20; i < 25; i++)
    {
      rs2[j] = inst[i];
      j++;
    }
    operand2 = rs2.to_ulong();
  switch (Type)
  {
  case 'R':
  {

    j = 0;
    for (int i = 7; i < 12; i++)
    {
      rd[j] = inst[i];
      j++;
    }
    des_reg = rd.to_ulong();
    cout << des_reg << endl; 
    break;
   
  } 
  case 'I':{
    bitset<12> immb;
     j = 0;
      bool isneg = false;
    for (int i = 7; i < 12; i++)
    {
      rd[j] = inst[i];
      j++;
    }
    des_reg = rd.to_ulong();
    j=0;
    for (int i = 20; i < 32; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    if(immb[11]==1){
      isneg = true;
    }
    if(immb[11]==1){
    string s1= immb.to_string();  
    string s = findTwoscomplement(s1);
    cout<<s<<endl;
    bitset<12> opl(s);
    immb = opl;
    }
    imm = immb.to_ulong();
    if(isneg){
      imm = -1*imm;
    }
    cout << imm << " "<< operand1<<" "<< des_reg<< endl; 
    break;

  }
  case 'S':{
    bitset<12> immb;
     j=0;
    for (int i = 7; i < 12; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    for (int i = 25; i < 32; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    imm = immb.to_ulong();
    if(immb[11]==1){
      imm = -1*imm;
    }
    break;

  }
  case 'B':{
    bitset<13> immb;
    bool isneg = false;
     
     immb[0]=0;
    j=1;
    for (int i = 8; i < 12; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    for (int i = 25; i < 31; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    immb[j]=inst[7];
    j++;
    immb[j]= inst[31];
    cout<<immb<<endl;
    if(immb[12]==1){
       isneg = true;
    }
    if(immb[12]==1){
    string s1= immb.to_string();  
    string s = findTwoscomplement(s1);
    cout<<s<<endl;
    bitset<13> opl(s);
    immb=opl;
    }
    cout<<immb<<endl;
    imm = immb.to_ulong();
    if(isneg){
      imm = -1*imm;
    }
    cout<<imm<<endl;
    break;
  }
  case 'U':{
        j = 0;
    for (int i = 7; i < 12; i++)
    {
      rd[j] = inst[i];
      j++;
    }
    des_reg = rd.to_ulong();
    bitset<20> immb;
    j=0;
    for (int i = 12; i < 32; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    cout<<immb<<endl;
    imm = immb.to_ulong();
    // if(immb[19]==1){
    //   imm = -1*imm;
    // }
    cout<<imm<<endl;

    break;
  }
  case 'J':{
    j=0;
    bitset<21> immb;
     bool isneg = false;
    j=0;
    immb[0]=0;
    j=12;
     for (int i = 12; i < 20; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    immb[11]=inst[20];
    j=1;
     for (int i = 21; i < 31; i++)
    {
      immb[j] = inst[i];
      j++;
    }
    immb[20]=inst[31];
    if(immb[20]==1){
      isneg = true;
    }
    if(immb[20]==1){
    string s1= immb.to_string();  
    string s = findTwoscomplement(s1);
    cout<<s<<endl;
    bitset<21> opl(s);
    immb = opl;
    }
    imm = immb.to_ulong();
    if(isneg){
      imm = -1*imm;
    }
    cout<<immb<<endl;
    cout<<imm<<endl;
    j = 0;
    for (int i = 7; i < 12; i++)
    {
      rd[j] = inst[i];
      j++;
    }
    des_reg = rd.to_ulong();
    cout << des_reg << endl; 
    break;
  }
  default:{
    cout<<"error"<<endl;}
  }
  subtype_select(func3,func7,op);
}
// executes the ALU operation based on ALUop
void execute()
{
  cout<<subtype<<endl;
  if(Type == 'R'){ //add, and, or, sll, slt, sra, srl, sub, xor
    if(subtype == "add")  des_res = X[operand1] + X[operand2];
    else if(subtype == "sub") des_res = X[operand1] - X[operand2];
    else if(subtype == "and") des_res = X[operand1] & X[operand2];
    else if(subtype == "or")  des_res = X[operand1] | X[operand2];
    else if(subtype == "sll") des_res = X[operand1] << X[operand2];
    else if(subtype == "slt") des_res = (X[operand1] < X[operand2])?1:0;
    else if(subtype == "sra") des_res = X[operand1] >> X[operand2];
    else if(subtype == "xor") des_res = X[operand1] ^ X[operand2];
    else if(subtype == "srl") des_res = X[operand1] >> X[operand2];
    pc=pc+4;
  }
  else if(Type == 'I'){ //addi, andi, ori, lb, lh, lw, jalr
    if(subtype == "addi") des_res = X[operand1]+imm; 
    else if(subtype == "andi") des_res = X[operand1]&imm; 
    else if(subtype == "ori") des_res = X[operand1]|imm; 
    else if(subtype == "lb" || subtype == "lh" || subtype == "lw") des_res = X[operand1]+imm; 
    else if(subtype == "jalr") { des_res = pc + 4; pc = X[operand1]+imm;} 
    else if(subtype =="slli"){des_res = X[operand1] << imm ;}
    if(subtype != "jalr"){
      pc=pc+4;
    }
    cout<<des_res<<endl;
  }
  else if(Type == 'B'){//beq, bne, bge, blt
    if(subtype == "beq"){ if(X[operand1] == X[operand2]) pc += imm;else pc += 4;}
    else if(subtype == "bne") {if(X[operand1] != X[operand2]) pc += imm;else pc += 4;}
    else if(subtype == "bge") {if(X[operand1] >= X[operand2]) pc += imm;else pc += 4;}
    else if(subtype == "blt") {if(X[operand1] < X[operand2]) pc += imm;else pc += 4;}
  }
  else if(Type == 'J'){//jal
    des_res = pc+4; pc += imm;
  }
  else if(Type == 'S'){//sb, sw, sh
    des_res = X[operand1]+imm;
    pc=pc+4;
  }
  else if(Type == 'U'){//auipc, lui
    if(subtype == "auipc"){ des_res = pc + (imm<<12) ;}
    else if(subtype == "lui"){ des_res = imm<<12;}
    pc=pc+4;
    // cout<<des_res<<endl;
  }
}
// perform the memory operation
void mem()
{
  if(subtype == "lw"|| subtype == "lh" || subtype == "lb"){
    des_res = DMEM[des_res];
  }
  else if(subtype == "sw"|| subtype == "sh" || subtype == "sb"){
    DMEM[des_res] = X[operand2];
  }

  cout<<" "<<DMEM[8192]<<" "<<DMEM[8196]<<" "<<DMEM[8200]<<" "<<DMEM[8204]<<" "<<DMEM[8208]<<" "<<DMEM[8212]<<" "<<DMEM[8216]<<" "<<DMEM[8220]<<" "<<DMEM[8224]<<" "<<DMEM[8228]<<endl;
  cout<<" "<<DMEM[4096]<<" "<<DMEM[4100]<<" "<<DMEM[4104]<<" "<<DMEM[4108]<<endl;
}
// writes the results back to register file
void write_back()
{
  if(Type != 'S' && Type != 'B'){ X[des_reg] = des_res;}
  X[0]=0;
  cout<< X[des_reg]<<endl;
  Type = '0';
  cout<<pc<<endl;
  cout<<" X0 "<<X[0]<<" X1 "<<X[1]<<" X2 "<<X[2]<<" X3 "<<X[3]<<" X4 "<<X[4]<<" X5 "<<X[5]<<" X6 "<<X[6]<<" X7 "<<X[7]<<endl;

}
// should be called when instruction is swi_exit
void run_riscvsim()
{
  while (1)
  {
    fetch();
    decode();
    execute();
    mem();
    write_back();
    // break;
  }
}

int main()
{
  // reset the processor
  reset_proc();
  // load the program memory
  load_program_memory();
  // run the simulator
  run_riscvsim();
  return 0;
}