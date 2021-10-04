#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <iterator>
using namespace std;

string way_to_file = "Stream_of_data.txt";
string typeWar = "char";
bool inFunc = 0;
bool inArgs =1 ;
vector<string> dequeVars; // проверяет очерёдность типов переменных
vector<string> dequeArgs; // проверяет очерёдность типов аргументов
map<string, char> globalVarChar;
map<string, int> globalVarInt;
map<string, short> globalVarShort;
map<string, int> argInts; 
map<string, char> argChars; 
map<string, short> argShorts; 
map<string, int> localInts; 
map<string, char> localChars;
map<string, short> localShorts; 

////////////// 
vector<char> forbidden_symbols = { '!','@','"','#','№','$',';','^',':','&','?','*','<','>','`','~','/','|','\'','\\','.',',','+','-','%','=' };
void static Forbidden_symbols_and_name(string nameVar) {

    for (auto forbsimb : forbidden_symbols) {

        if (nameVar.find(forbsimb) != -1) { throw exception(); };
    }
    for (auto save_map : globalVarInt) {
        if (nameVar == save_map.first) { throw exception(); }
    };
    for (auto save_map : globalVarChar) {
        if (nameVar == save_map.first) { throw exception(); }
    };
    for (auto save_map : globalVarShort) {
        if (nameVar == save_map.first) { throw exception(); }
    };
    for (auto save_map : argInts) {
        if (nameVar == save_map.first) { throw exception(); }
    };
    for (auto save_map : argChars) {
        if (nameVar == save_map.first) { throw exception(); }
    };
    for (auto save_map : argShorts) {
        if (nameVar == save_map.first) { throw exception(); }
    };
};
void writing_arguments(string nameVar, int value, string typeVar) {
    if ((inFunc == 0)&&(inArgs==0)) {
        globalVarInt.emplace(pair<string, int>(nameVar, value));
    }
    else if (inArgs == 1){
         argInts.emplace(pair<string, int>(nameVar, value));
         dequeArgs.push_back(typeVar);
    }
    else {
        localInts.emplace(pair<string, int>(nameVar, value));
        dequeVars.push_back(typeVar);
    }
}
void writing_arguments(string nameVar, char value, string typeVar) {
    if ((inFunc == 0) && (inArgs == 0)) {
        globalVarChar.emplace(pair<string, char>(nameVar, value));
    }
    else if(inArgs ==1) {
        argChars.emplace(pair<string, char>(nameVar, value));
        dequeArgs.push_back(typeVar);
    }
    else {
        localChars.emplace(pair<string, char>(nameVar, value));
        dequeVars.push_back(typeVar);
    }
}
void writing_arguments(string nameVar, short value, string typeVar) {
    if ((inFunc == 0) && (inArgs == 0)) {

        globalVarShort.emplace(pair<string, short>(nameVar, value));
    }
     else if(inArgs == 1) {
        argShorts.emplace(pair<string, short>(nameVar, value));
        dequeArgs.push_back(typeVar);
    }
     else {
        localShorts.emplace(pair<string, short>(nameVar, value));
        dequeVars.push_back(typeVar);
    }
}
////////////

void ParsVars(ifstream& stream, const string& typeVar) {
    if ((inFunc == 1)&&( inArgs == 1)) { throw exception(); };
    string nameVar, endCommand, word;
    int int_value = 0; char char_value = ' ';  short short_value =0;
    stream >> word;


    if (inArgs == 1) {
        auto comma = word.rfind(",");
        auto skoba = word.rfind(")");
        if (skoba != -1) {
            if (word.length() == skoba + 1) {
                nameVar = word.erase(skoba);
                if ((nameVar.find(")") != -1) || (nameVar == "")) {
                    throw exception();
                }
                endCommand = ")";
                Forbidden_symbols_and_name(nameVar);
                
                if (typeVar == "int") { writing_arguments(nameVar, int_value, typeVar); }
                if (typeVar == "short") { writing_arguments(nameVar, short_value, typeVar); }
                if (typeVar == "char") { writing_arguments(nameVar, char_value, typeVar); }
            }
            else { throw exception(); };

        }
        else if (comma != -1) {
            if (word.length() == comma + 1) {
                nameVar = word.erase(comma);
                if ((nameVar.find(",") != -1) || (nameVar == "")) {
                    throw exception();
                }
                endCommand = ",";
                Forbidden_symbols_and_name(nameVar);
                if (typeVar == "int") { writing_arguments(nameVar, int_value,typeVar); }
                if (typeVar == "short") { writing_arguments(nameVar, short_value, typeVar); }
                if (typeVar == "char") { writing_arguments(nameVar, char_value, typeVar); }
            }
            else { throw exception(); };



        }
        else {
            nameVar = word;
            stream >> word;
            if (word == ")") {

                Forbidden_symbols_and_name(nameVar);
                endCommand = ")";
                if (typeVar == "int") { writing_arguments(nameVar, int_value, typeVar); };
                if (typeVar == "short") { writing_arguments(nameVar, short_value, typeVar); };
                if (typeVar == "char") { writing_arguments(nameVar, char_value, typeVar); };
            }
            else { throw exception(); }
        }
    }
    else {
        auto semicolon = word.rfind(";");
        auto comma = word.rfind(",");
        auto equals = word.rfind("=");
        if ((semicolon != -1) && (comma == -1) && (equals == -1)) {
            if (word.length() == semicolon + 1) {
                nameVar = word.erase(semicolon);
                if ((nameVar.find(";") != -1) || (nameVar == "")) {
                    throw exception();
                }
                endCommand = ";";
                Forbidden_symbols_and_name(nameVar);
                if (typeVar == "int") { writing_arguments(nameVar, int_value, typeVar); }
                if (typeVar == "short") { writing_arguments(nameVar, short_value, typeVar); }
                if (typeVar == "char") { writing_arguments(nameVar, char_value, typeVar); }
            }
            else { throw exception(); };
        }
        else {
            if (comma != -1) {
                if (word.length() == comma + 1) {
                    nameVar = word.erase(comma);
                    if ((nameVar.find(",") != -1) || (nameVar == "")) {
                        throw exception();
                    }
                    Forbidden_symbols_and_name(nameVar);
                    if (typeVar == "int") { writing_arguments(nameVar, int_value, typeVar); }
                    if (typeVar == "short") { writing_arguments(nameVar, short_value, typeVar); }
                    if (typeVar == "char") { writing_arguments(nameVar, char_value, typeVar); }
                    return ParsVars(stream, typeVar);

                }
                else { throw exception(); }
            }

            else {
                nameVar = word;
                stream >> word;
                if (word == ";") {

                    Forbidden_symbols_and_name(nameVar);
                    endCommand = ";";
                    if (typeVar == "int") { writing_arguments(nameVar, int_value, typeVar); }
                    if (typeVar == "short") { writing_arguments(nameVar, short_value, typeVar); }
                    if (typeVar == "char") { writing_arguments(nameVar, char_value, typeVar); }
                }
                else {
                    if (word == "=") {
                        stream >> word;
                        semicolon = word.rfind(";");
                        if (semicolon != -1) {
                            if (word.length() == semicolon + 1) {
                                word = word.erase(semicolon);
                                if (typeVar == "char") {
                                    if ((word[0] == '\'') && (word[word.size() - 1] == '\'')) {
                                        word.erase(0, 1); word.erase(word.size() - 1);
                                    }
                                    else { throw exception(); }

                                }
                                Forbidden_symbols_and_name(word);
                                endCommand = ";";
                                if (typeVar == "int") { int_value = stoi(word); writing_arguments(nameVar, int_value, typeVar); };
                                if (typeVar == "short") { int orowe = stoi(word); short_value = (short)orowe; writing_arguments(nameVar, short_value, typeVar); };
                                if (typeVar == "char") { char_value = word[0]; writing_arguments(nameVar, char_value, typeVar); };
                            }
                            else { throw exception(); };
                        }
                        else {
                            comma = word.rfind(",");
                            if (comma != -1) {
                                if (word.length() == comma + 1) {
                                    word = word.erase(comma);
                                    if (typeVar == "char") {
                                        if ((word[0] == '\'') && (word[word.size() - 1] == '\'')) {
                                            word.erase(0, 1); word.erase(word.size() - 1);
                                        }
                                        else { throw exception(); }

                                    }
                                    Forbidden_symbols_and_name(word);
                                    if (typeVar == "int") { int_value = stoi(word); writing_arguments(nameVar, int_value, typeVar); };
                                    if (typeVar == "short") { int orowe = stoi(word); short_value = (short)orowe; writing_arguments(nameVar, short_value, typeVar); };
                                    if (typeVar == "char") { char_value = word[0]; writing_arguments(nameVar, char_value, typeVar); };
                                    return ParsVars(stream, typeVar);
                                }
                                else { throw exception(); };

                            }
                            else {
                                stream >> word;
                                semicolon = word.rfind(";");
                                if (word == ";") { endCommand = ";"; }
                                else { throw exception(); }
                            }
                        }
                    }
                    else { throw exception(); };
                };
            };
        };
    }
    if ((endCommand != ";") && (endCommand != ",") && (endCommand != ")"))
    {
            throw exception();
        }
}


int main() {
    ifstream file;
    file.open(way_to_file);
    ParsVars(file, typeWar);
    cout << "   globalVarShort" << endl;
    for (auto command : globalVarShort) {
        cout <<command.first<<"  "<<command.second<<endl;
    }
    cout << "    globalVarChar" << endl;
    for (auto command : globalVarChar) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   globalVarInt" << endl;
    for (auto command : globalVarInt) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   argInts" << endl;
    for (auto command : argInts) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   argChars" << endl;
    for (auto command : argChars) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   argShorts" << endl;
    for (auto command : argShorts) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   localInts" << endl;
    for (auto command : localInts) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   localChars" << endl;
    for (auto command : localChars) {
        cout << command.first << "  " << command.second << endl;
    }
    cout << "   localShorts" << endl;
    for (auto command : localShorts) {
        cout << command.first << "  " << command.second << endl;
    }
    for (auto command : dequeArgs) {
        cout << command << "  " << command << endl;
    }
    file.close();
  
};