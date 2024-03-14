//
// Created by bigfoot on 2024/3/14.
//

#include"leds.h"
#include"file.h"
#include<string.h>

class MultiColorLEDInterface final:public MultiColorLED{
	public:
		MultiColorLEDInterface(const std::string&name);
		~MultiColorLEDInterface(void);
		std::string GetName(void);
		LEDColor GetColor(void);
		void SetColor(LEDColor color);
		std::string name;
};

MultiColorLEDInterface::MultiColorLEDInterface(const std::string&name){
	this->name=name;
}

MultiColorLEDInterface::~MultiColorLEDInterface(void){
}

std::string MultiColorLEDInterface::GetName(void){
	return name;
}

LEDColor MultiColorLEDInterface::GetColor(void){
	LEDColor lc;
	uint64_t max=0,cur=0;
	file_read_uint64_f(&max,"/sys/class/leds/%s/max_brightness",name.c_str());
	file_read_uint64_f(&cur,"/sys/class/leds/%s/brightness",name.c_str());
	if(max<=0)max=255;
	lc.alpha=cur*255/max;
	char buff[256];
	file_read_buff_f(buff,sizeof(buff),"/sys/class/leds/%s/multi_intensity",name.c_str());
	if(buff[0]){
		int r=0,g=0,b=0;
		sscanf(buff,"%d %d %d",&r,&g,&b);
		lc.red=r,lc.green=g,lc.blue=b;
	}
	return lc;
}

void MultiColorLEDInterface::SetColor(LEDColor color){
	uint64_t max=0;
	file_read_uint64_f(&max,"/sys/class/leds/%s/max_brightness",name.c_str());
	if(max<=0)max=255;
	uint64_t level=color.alpha*255/max;
	file_write_uint64_f(level,"/sys/class/leds/%s/brightness",name.c_str());
	char buff[256];
	memset(buff,0,sizeof(buff));
	snprintf(buff,sizeof(buff)-1,"%d %d %d",color.red,color.green,color.blue);
	file_write_buff_f(buff,strlen(buff),"/sys/class/leds/%s/multi_intensity",name.c_str());
}

std::shared_ptr<MultiColorLED>LookupLED(const std::string&name){
	return std::make_shared<MultiColorLEDInterface>(name);
}
