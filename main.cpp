#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "randgen.h"
#include <iomanip>
#include <stdlib.h>

using namespace std;

string int2str(int i);

string int2str(int i){
        stringstream ss;
        ss<<i;
        return ss.str();
}

int main(int argc, char* argv[]){

	RandGen rnd;

	int nwin;
	int rmin, rmax;
	string executable;
	ifstream infile("input");
	infile>>nwin>>executable>>rmin>>rmax;
	infile.close();

	int ndig=0;
	int temp=argc;
	for (;temp>0;ndig++) temp/=10;
	int dig;

	ofstream outfile;

	int max=-1;
	int x, y;
	int natom;

	string dir;
	string str;
	string name;

	for (x=1; x<=argc; x++){
		cout<<"Pass 1: "<<x<<"/"<<argc<<endl;

		infile.open(argv[x]);
		getline(infile,str);
		infile>>str>>str>>natom;
		infile.close();

		outfile.open("his2xyz.in");
		outfile<<argv[x]<<endl;
		outfile<<nwin<<endl;
		outfile<<natom<<endl;
		outfile.close();

		if (natom>max) max=natom;
		
		system((executable+" < his2xyz.in").c_str());

		temp=x;
		for (;temp>0;dig++) temp/=10;

		name="";
		for (y=0; y<ndig-dig; y++){
			name+=int2str(0);
		}
		name+=int2str(x);

		system(("tail -"+int2str(natom+2)+" HIS.xyz > frame"+name+".xyz").c_str());
		
	}	
	
	int length=int2str(max).length();

	for (x=1; x<=argc; x++){
		cout<<"Pass 2: "<<x<<"/"<<argc<<endl;
		
		dig=int2str(x).length();
		name="";
		for (y=0; y<ndig-dig; y++){
			name+=int2str(0);
		}	
		name+=int2str(x);
		
		outfile.open(("frame"+name+".xyz").c_str());
		outfile<<" "<<max;
		infile.open((name+".xyz").c_str());
		infile>>natom;
		while (getline(infile,str)) outfile<<str<<endl;
		infile.close();		
		for (y=natom; y<max; y++){
			outfile<<"XX    ";
			outfile<<rnd.RandInt(rmin,rmax)<<".0000    ";
			outfile<<rnd.RandInt(rmin,rmax)<<".0000    ";
			outfile<<rnd.RandInt(rmin,rmax)<<".0000"<<endl;
		}
		outfile.close();
	}
	system("rm frame*.xyz");
	
	system("catdcd -o traj.dcd -xyz *.xyz");
	
	cout<<"Movie generation complete"<<endl;
	
	return 0;
}
