#include <iostream>
#include <fstream>
#include <json/json.h> // or jsoncpp/json.h , or json/json.h etc.

using namespace std;

void convertJsonToXml(Json::Value obj, string keyValue){

        
        ofstream file_xml;
        file_xml.open("point_cloud "+ keyValue +".xml");

        int cloud_len = obj[keyValue].size();
        string string_cloud_len = to_string(cloud_len);
        cout<<string_cloud_len<<endl;

        file_xml<<"<?xml version=\"1\"?>"<<endl<<"<opencv_storage>"<<endl<<"<points type_id=\"opencv-matrix\">"<<endl<<"<rows>"+ string_cloud_len+"</rows>"<<endl<<"<cols>4</cols>"<<endl<<"<dt>d</dt>"<<endl<<"<data>"<<endl;


        for(int i=0; i< obj[keyValue].size() ; i++){
            for(int j=0 ; j<obj[keyValue][i].size() ; j++){
                
                if(j == (obj[keyValue][i].size() -1)){
                    file_xml<<obj[keyValue][i][j].asString()<<endl;
                }else{
                    file_xml<<obj[keyValue][i][j].asString()<<" ";
                }
            }        
        }

        file_xml<<"</data>"<<endl<<"</points>"<<endl<<"</opencv_storage>";
        file_xml.close();

        cout<<"=================== Completed! ==============================="<<endl;
}


int main(int argc, char* argv[]) {

    if(argc < 2){
        cout<<"You must inform the file names... Ex: ./simple_read pos_1.son"<<endl;
    }else{
        cout<<argc<<endl;
        ifstream ifs(argv[1]); 
        Json::Reader reader;
        Json::Value obj;
        reader.parse(ifs, obj); // reader can also read strings

        vector<string> keys = obj.getMemberNames();

        for(int i=0 ; i<keys.size() ; i++){
        convertJsonToXml(obj, keys[i]);
        }
        

        
    

    
}

}
