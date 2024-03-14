//
// Created by bigfoot on 2024/3/14.
//

#ifndef RGB_LED_LEDS_H
#define RGB_LED_LEDS_H
#include<string>
#include<cstdint>
#include<memory>
struct LEDColor{
	uint8_t alpha;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

class MultiColorLED{
	public:
		virtual ~MultiColorLED(void)=default;
		virtual std::string GetName(void)=0;
		virtual LEDColor GetColor(void)=0;
		virtual void SetColor(LEDColor color)=0;
};

extern std::shared_ptr<MultiColorLED>LookupLED(const std::string&name);
#endif
