#include <iostream>
#include <fstream>
#include <json/json.h> // or jsoncpp/json.h , or json/json.h etc.

using namespace std;

void convertJsonToPcl(string fileName){

        ifstream ifs(fileName); 
        Json::Reader reader;
        Json::Value obj;
        reader.parse(ifs, obj); // reader can also read strings

        ofstream file_pcd;
        file_pcd.open("point_cloud.pcd");

        int len = obj["18555"].size();
        string string_len = to_string(len);

        file_pcd<<"VERSION .7"<<endl<<"FIELDS x y z"<<endl<<"SIZE 4 4 4"<<endl<<"TYPE F F F"<<endl<<"COUNT 1 1 1"<<endl<<"WIDTH " + string_len<<endl<<"HEIGHT 1"<<endl<<"VIEWPOINT 0 0 0 1 0 0 0"<<endl<<"POINTS " + string_len<<endl<<"DATA DATA ascii"<<endl;

        cout<<obj["18555"][0]<<endl;
        int count = 1;

        //j<obj["transformed_cloud"]["data"].size()
        
        for (int i=0 ; i<obj["18555"].size() ; i++){

            for(int j=0 ; j<obj["18555"][i].size(); j++){
                
                if(count == 3){
                    file_pcd<<obj["18555"][i][j].asString()<<endl;
                    count =1;
                }else{
                    file_pcd<<obj["18555"][i][j].asString()<<" ";
                    count++;
                }
            }

        }
        

        file_pcd.close();

        cout<<"=================== Completed! ==============================="<<endl;
}


int main(int argc, char* argv[]) {

    if(argc < 2){
        cout<<"You must inform the file names... Ex: ./simple_read pos_1.son"<<endl;
    }else{
    
        convertJsonToPcl(argv[1]);  

    
}

}