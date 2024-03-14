//
// Created by bigfoot on 2024/3/14.
//

#ifndef RGB_LED_MAIN_WINDOW_H
#define RGB_LED_MAIN_WINDOW_H
#include<QMainWindow>
#include<QLocale>
#include<QLabel>
#include<QFile>
#include<QSvgWidget>
#include<QSvgRenderer>
#include<QPushButton>
#include<memory>
#include<vector>
#include<json/json.h>
#include"leds.h"

class LED{
	public:
		inline LED(Json::Value&node):node(node){}
		void SetupButton(QWidget*p,std::function<void(LED*led)>callback);
		QColor color;
		QPushButton*btn;
		Json::Value&node;
		std::shared_ptr<MultiColorLED>led;
};

class MainWindow:public QMainWindow{
	Q_OBJECT
	public:
		explicit MainWindow(const char*path,Json::Value&root,QWidget*p=nullptr);
		void Retranslate(void);
		void RedrawLEDs(void);
	protected slots:
		void OnRGBClicked(LED*led);
	private:
		QString ResolvePath(Json::Value&val);
		void SetupUI(void);
		void SetupUIButtons(void);
		void SetupUIPictures(void);
		const char*path;
		Json::Value&root;
		QSvgWidget*img,*overlay;
		std::vector<LED*>leds;
		QString overlay_data="";
};
#endif
