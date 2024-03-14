//
// Created by bigfoot on 2024/3/14.
//

#include"main_window.h"
#include"path.h"
#include<err.h>
#include<QColorDialog>

void MainWindow::SetupUI(void){
	QPalette pal_window,pal_button;
	setWindowIcon(QIcon(ResolvePath(root["icon"])));
	setFixedSize(root["width"].asInt(),root["height"].asInt());
	pal_window.setColor(QPalette::Window,Qt::white);
	setAutoFillBackground(true);
	setPalette(pal_window);
	SetupUIPictures();
	SetupUIButtons();
}

void LED::SetupButton(QWidget*p,std::function<void(LED*led)>callback){
	QPalette pal_button;
	pal_button.setColor(QPalette::Button,Qt::transparent);
	btn=new QPushButton(p);
	btn->setFixedSize(node["width"].asInt(),node["height"].asInt());
	btn->move(node["x"].asInt(),node["y"].asInt());
	btn->setFlat(true);
	btn->setPalette(pal_button);
	p->connect(
		btn,&QPushButton::clicked,
		p,[this,callback](){callback(this);}
	);
}

void MainWindow::SetupUIButtons(void){
	auto cb=[this](LED*led){OnRGBClicked(led);};
	if(!root["leds"].isArray())return;
	for(int i=0;i<root["leds"].size();i++){
		auto led=new LED(root["leds"][i]);
		auto str=led->node["color"].asString();
		led->led=LookupLED(led->node["id"].asString());
		auto c=led->led->GetColor();
		led->color=QColor::fromRgb(c.red,c.green,c.blue,c.alpha);
		led->SetupButton(this,cb);
		leds.push_back(led);
	}
}

void MainWindow::SetupUIPictures(void){
	overlay=new QSvgWidget(this);
	overlay->setFixedSize(size().width(),size().height());

	img=new QSvgWidget(ResolvePath(root["background"]),this);
	img->setFixedSize(size().width(),size().height());
}

MainWindow::MainWindow(
	const char*path,
	Json::Value&root,
	QWidget*p
):path(path),root(root),QMainWindow(p){
	SetupUI();
	Retranslate();
	RedrawLEDs();
}

void MainWindow::Retranslate(){
	setWindowTitle(root["title"].asCString());
}

void MainWindow::OnRGBClicked(LED*led){
	auto c=QColorDialog::getColor(
		led->color,this,QString(),
		QColorDialog::ShowAlphaChannel
	);
	if(!c.isValid())return;
	led->color=c;
	LEDColor lc;
	lc.alpha=c.alpha();
	lc.red=c.red();
	lc.green=c.green();
	lc.blue=c.blue();
	led->led->SetColor(lc);
	RedrawLEDs();
}

void MainWindow::RedrawLEDs(void){
	if(overlay_data.isEmpty()){
		QFile res(ResolvePath(root["overlay"]));
		if(!res.open(QIODevice::ReadOnly|QIODevice::Text)){
			warnx("open overlay failed");
			return;
		}
		auto size=res.size();
		auto data=res.read(size);
		res.close();
		if(data.length()!=size){
			warnx("read overlay mismatch");
			return;
		}
		overlay_data=data;
	}
	QString svg(overlay_data);
	for(auto led:leds){
		auto i=led->node["id"].asCString();
		svg.replace(
			QString("{color-%1}").arg(i),
			QString("#%1").arg(led->color.rgb()&0xFFFFFF,6,16,QChar('0'))
		);
	}
	if(!overlay->renderer()->load(svg.toLocal8Bit()))
		warnx("load svg failed");
}

QString MainWindow::ResolvePath(Json::Value&val){
	std::string value=val.asString();
	if(!path||!*path)return QString::fromStdString(value);
	char buff[4096];
	memset(buff,0,sizeof(buff));
	realpath(path,buff);
	auto dir=path_dirname(std::string(buff));
	auto real=path_merge(0,dir,value);
	return QString("/%1").arg(QString::fromStdString(real));
}
