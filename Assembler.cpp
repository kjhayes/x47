#include<fstream>
#include<iostream>
#include<string>

int main(int argc, char **argv){
    if(argc != 3){std::cout<<"Not The Correct Number Of Arguments!"<<std::endl;return -1;}
    char* assembly = argv[1];
    char* output = argv[2];

    std::ifstream astream;
    astream.open(assembly, std::ios::in);

    std::ofstream file(output, std::ios::trunc);

    file<<"v2.0 raw\n0\n";

    std::string lnBuffer;

    int line_count = 0;

    while(std::getline(astream, lnBuffer)){

    std::string opCode = lnBuffer.substr(0,3);
    
    if(!opCode.compare("JMP")){
        file<<lnBuffer.substr(4,2);
        file<<"01\n";
        goto END;
    }
    if(!opCode.compare("LOD")){
        file<<lnBuffer.substr(7,1);
        file<<lnBuffer.substr(4,2);
        file<<"02\n";
        goto END;
    }
    if(!opCode.compare("STR")){
        file<<lnBuffer.substr(7,1);
        file<<lnBuffer.substr(4,2);
        file<<"03\n";
        goto END;
    }
    if(!opCode.compare("MOV")){
        file<<lnBuffer.substr(6,1);
        file<<lnBuffer.substr(4,1);
        file<<"04\n";
        goto END;
    }
    if(!opCode.compare("ALM")){
        std::string s = lnBuffer.substr(6,1);
        if(s[0] == 'A'){file<<'0';}
        if(s[0] == 'B'){file<<'1';}
        file<<lnBuffer.substr(4,1);
        file<<"05\n";
        goto END;
    }
    if(!opCode.compare("ALC")){
        file<<lnBuffer.substr(6,1);
        file<<lnBuffer.substr(4,1);
        file<<"06\n";
        goto END;
    }
    if(!opCode.compare("JPI")){
        std::string s = lnBuffer.substr(9,1);
        if(s[0] == 'A'){file<<'0';}
        if(s[0] == 'O'){file<<'1';}
        file<<lnBuffer.substr(7,1);
        file<<lnBuffer.substr(4,2);
        file<<"07\n";
        goto END;
    }
    if(!opCode.compare("HLT")){
        file<<"0f\n";
        goto END;
    }
    if(!opCode.compare("DAT")){
        file<<lnBuffer.substr(4,8)<<"\n";
        goto END;
    }
    std::cout<<"SYNTAX ERROR ON LINE: "<<line_count<<std::endl;
    

END:
    line_count++;
    }

    astream.close();
    file.close();

    return 0;
}