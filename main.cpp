#include "main.h"
#include<sys/stat.h>

using namespace caffe;
using namespace std;
using namespace cv;


#define wantWriteVideo0
#define dir0
#define Parser1

// ----------------------------------------------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------------------------------------------
std::vector<std::string> listpath;
void recursive_listing(char *ptr)
{

        DIR *dp;
        dirent *d;

	if((dp = opendir(ptr)) == NULL)
		perror("opendir");

	while((d = readdir(dp)) != NULL)
	{
            
		if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
                {
			continue;
                }
                 string dirpath=string(ptr)+"/"+d->d_name;
		struct stat sb;

if (stat(dirpath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
{
//			cout << d->d_name << ":" << endl;
//                        string dirpath=string(ptr)+"/"+d->d_name;
                       // cout<<"dirpath :"<<dirpath<<endl;
			recursive_listing(dirpath.c_str());	
		}
		else
                {
                     string dirpath1=string(ptr)+"/"+d->d_name;
                     listpath.push_back(dirpath1);
                    // cout << "File :"<< dirpath1 << endl;
                }
                
	}
	return;
}
int main(int argc, char** argv)
{
#ifdef dir
    mkdir("Anger", 0777);
  //mkdir("Contempt", 0777);
    mkdir("Disgust", 0777);
  //mkdir("Fear", 0777);
    mkdir("Happy", 0777);
    mkdir("Neutral", 0777);
    mkdir("Sadness", 0777);
    mkdir("Surprise", 0777);
#endif
    // ----------------------
    // Create output window
    // ----------------------  
   // cv::namedWindow("img");

    //VideoCapture cap("Pain_no_pain video.avi");
   VideoCapture cap;

//    if (!cap.isOpened())
//    {
//        cout << "Capture is not opened!" << endl;
//    }

    // ----------------------
    // Current frame
    // ----------------------
   
      int countcheck2=0;
      BlackBox black_box(argv[0], &cap, "./deploy.prototxt", "./FaceRec.caffemodel", "./mean.jpg", false);
#ifdef Parser
    recursive_listing(argv[1]);
    for(int i=0;i<listpath.size();i++)
    {
     cv::Mat frame=imread(listpath[i]);
     cout << "File :"<< listpath[i] << endl;
      black_box.FaceCropping(frame,listpath[i]);
      waitKey(10);
    }
//      DIR *dir;
//         
//    struct dirent *ent;
//     if ((dir = opendir ("./testing_few/Bill_Gates")) != NULL) {
//  /* print all the files and directories within directory */
//  while ((ent = readdir (dir)) != NULL) {
//  //  printf ("%s\n", ent->d_name);
//     if(strcmp(ent->d_name,"..")==0 || strcmp(ent->d_name,".")==0 ) 
//         continue;
//    string path="./testing_few/Bill_Gatesdgdfg/"+string(ent->d_name);
//    cout<<"path :"<<path<<endl;
//    
//   
//     cv::Mat frame=imread(path);
//   cv::Mat frameone=imread(path);
      
#else
//      recursive_listing(argv[1]);
//      int des=0;
//    for(int i=0;i<listpath.size();i++)
//    {
//     cv::Mat frame=imread(listpath[i]);
//     cv::imshow("image",frame);
//     if (frame.empty())
//    {
//        cout << "Frame is empty! " << endl;
//        return;
//    }
//     cout << "File :"<< listpath[i] << endl;
//     // black_box.FaceCropping(frame,listpath[i]);
//       black_box.process(frame);
//       int len=listpath[i].find_first_of("\\/");
//       string cele=listpath[i].substr(len+1);
//        cout<<"name last :"<<cele<<endl;
//        int len1=cele.find_first_of("\\/");
//       string namecel=cele.substr(0,len1);
//       cout<<"name :"<<namecel<<endl;
//       
//       string comp=black_box.class_names[int(black_box.faceSample->max_class)];
//       cout<<"decision string "<<comp<<endl;
//       if(comp==namecel && black_box.count1==1)
//       {
//          des++; 
//         // cout<<"correct decision "<<black_box.class_names[i]<<endl;
//       }
//       
//      waitKey(10);
//    }
    cv::Mat frame=imread(argv[1]);
   
     if (frame.empty())
    {
        cout << "Frame is empty! " << endl;
        return -1;
    }
    black_box.process(frame);
     cv::imshow("image",frame);
     waitKey(0);
#endif 
//       cout<<"des "<<des<<endl;
//        cout<<"black_box.count"<<black_box.count<<endl;
//      float per=float(des)/float(black_box.count);
//      cout<<"Total per"<<(per*100)<<endl;
    cv::destroyAllWindows();

    return 0;
}