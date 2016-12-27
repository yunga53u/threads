#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <thread>
#include<sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "reader.h"

using namespace std;
//===================================================
Reader::Reader()
{
    in_file_name = "file.txt";
    out_file_name_sum = "out_file_sum.txt";
    out_file_name_sub = "out_file_sub.txt";
    out_file_name_xor = "out_file_xor.txt";
    infile_size = 0;
}
//===================================================
Reader::~Reader()
{
    close_file();
}
//===================================================
void Reader::work()
{
    open_file();
    //string data = read_file();
    char * data = read_file();

    thread th_sum(&Reader::make_sum, this, ref(data) );
    thread th_sub(&Reader::make_sub, this, ref(data) );
    thread th_xor(&Reader::make_xor, this, ref(data) );
    //thread th_sum(&Reader::make_sum, this, data );
    //thread th_sub(&Reader::make_sub, this, data );
    //thread th_xor(&Reader::make_xor, this, data );
    th_sum.join();
    th_sub.join();
    th_xor.join();
}
//===================================================
//string Reader::read_file()
char * Reader::read_file()
{
    //get_file_id();
    //char * data = (char *)mmap(0, 10, PROT_READ, MAP_SHARED, 3, 0);
    char * data = (char *)mmap(0, infile_size, PROT_READ, MAP_SHARED, 3, 0);
    if(MAP_FAILED == data)
        throw "Error:::while mmap";
    //return static_cast<char *>(data);
    return data;
    
      /*
    string str( (istreambuf_iterator<char>( 
                *(auto_ptr<ifstream>( 
                new ifstream(in_file_name)
                )).get() )), istreambuf_iterator<char>() );
    return str;
    */
}
//===================================================
void Reader::get_file_id()
{
    int fd = open(in_file_name.c_str(), O_RDONLY );
    cout << "fd:" << fd << ",name:" <<in_file_name.c_str() << endl;
    //int fd = open(in_file_name.c_str(), O_RDONLY );
    if(fd < 0)
        throw "ERROR:::Can't open file to read!1";
    infile_id = fd;
    close(fd);
}
//===================================================
void Reader::close_file()
{
    if(infile)
        infile.close();
    if(outfile_sum)
        outfile_sum.close();
    if(outfile_sub)
        outfile_sub.close();
    if(outfile_xor)
        outfile_xor.close();
}
//===================================================
void Reader::open_file()
{
    infile.open(in_file_name, ios::in | ios::binary);
    if(!infile.good())
        throw "ERROR:::Can't open file to read!2";
    else
    {
        infile.seekg(0, ios_base::end);
        infile_size = infile.tellg();
    }
    outfile_sum.open(out_file_name_sum, ios::binary);
    if(!outfile_sum.good())
        throw "ERROR:::Can't open file to write SUM!";
    outfile_sub.open(out_file_name_sub, ios::binary);
    if(!outfile_sub.good())
        throw "ERROR:::Can't open file to write SUB!";
    outfile_xor.open(out_file_name_xor, ios::binary);
    if(!outfile_xor.good())
        throw "ERROR:::Can't open file to write XOR!";
}
//===================================================
//void Reader::make_sum(string& buf)
void Reader::make_sum(const char * const buf)
{
    unsigned int i = 0;
    while(i<strlen(buf)-1)
    //while(i<buf.size()-1)
    {
        //if('9' == buf.at(i))
        if('9' == buf[i])
        {
            outfile_sum << "10";
        }
        else
            outfile_sum << static_cast<char>(buf[i] + 1);
            //outfile_sum << static_cast<char>((buf.at(i)) + 1) << endl;
        i++;
    }
    cout << "END SUM" << endl;
}
//===================================================
//void Reader::make_sub(string& buf)
void Reader::make_sub(const char * const buf)
{
    unsigned int i = 0;
    while(i<strlen(buf)-1)
    //while(i<buf.size()-1)
    {
        //if('0' == buf.at(i))
        if('0' == buf[i])
        {
            outfile_sub << "-1";
        }
        else
            outfile_sub << static_cast<char>(buf[i] - 1);
            //outfile_sub << static_cast<char>((buf.at(i)) - 1) << endl;
        i++;
    }
    cout << "END SUB" << endl;
}
//===================================================
//void Reader::make_xor(string& buf)
void Reader::make_xor(const char * const buf)
{
    unsigned int i = 0;
    while(i<strlen(buf)-1)
    //while(i<buf.size()-1)
    {
        outfile_xor << static_cast<char>(buf[i] ^ 1);
        //outfile_xor << static_cast<char>((buf.at(i)) ^ 1) << endl;
        i++;
    }
    cout << "END XOR" << endl;
}
//===================================================
