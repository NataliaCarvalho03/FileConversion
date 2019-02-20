#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void convertXmlToPcl(string fileName){

        FileStorage xml_file(fileName, FileStorage::READ);
        xml_file.open(fileName, FileStorage::READ);

        Mat pc;
        xml_file["points"]>>pc;

        if(pc.empty()){
            cout<<"Erro! Não foi possível ler a nuvem de pontos!"<<endl;
            exit(1);
        }else{
            cout<<"Nuvem lida com sucesso!"<<endl;
            
        }

        int pc_width = pc.rows;
        string string_pc_width = to_string(pc_width);

        ofstream file_pcd;
        file_pcd.open("point_cloud18556.pcd");    

        file_pcd<<"VERSION .7"<<endl<<"FIELDS x y z rgb"<<endl<<"SIZE 4 4 4 4"<<endl<<"TYPE F F F F"<<endl<<"COUNT 1 1 1 1"<<endl<<"WIDTH " + string_pc_width<<endl<<"HEIGHT 1"<<endl<<"VIEWPOINT 0 0 0 1 0 0 0"<<endl<<"POINTS " + string_pc_width<<endl<<"DATA ascii"<<endl;

        int count = 1;

        //cout<<pc.at<double>(0,2)<<endl;
        
        for(int i=0 ; i<pc.rows ; i++){
            for(int j=0 ; j<pc.cols ; j++){
                if(count == 4){
                    file_pcd<<pc.at<double>(i,j)<<endl;
                    count = 1;
                }else{
                    file_pcd<<pc.at<double>(i,j)<<" ";
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
    
        convertXmlToPcl(argv[1]);

    
}

}