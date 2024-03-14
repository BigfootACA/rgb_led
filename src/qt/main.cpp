#include<err.h>
#include<fstream>
#include<json/json.h>
#include<QApplication>
#include<QScreen>
#include"main_window.h"

int main(int argc,char*argv[]){
	Json::Reader reader;
	Json::Value val;
	QApplication a(argc,argv);
	if(argc!=2)errx(1,"Usage: rgb-led <CONFIG>");
	std::ifstream in(argv[1],std::ios::binary);
	if(!in.is_open())err(2,"open %s failed",argv[1]);
	if(!reader.parse(in,val))errx(
		2,"parse %s failed: %s",argv[1],
		reader.getFormattedErrorMessages().c_str()
	);
	MainWindow w(argv[1],val);
	w.show();
	auto r=a.primaryScreen()->availableGeometry();
	w.move(
		(r.width()-w.width())/2,
		(r.height()-w.height())/2
	);
	return QApplication::exec();
}
