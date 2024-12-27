#pragma once

#ifndef TIME_HPP
#define TIME_HPP

#include <string>

class Time {
public:
	Time() = default;
	//Time(int seconds);
	Time(int seconds, int minutes = 0, int hours = 0, int days = 0)
		:seconds_(seconds),
		minutes_(minutes),
		hours_(hours),
		days_(days)
	{
		//код проверки корректных значений
		ErrorWhenSecondsWrong_();
	}

	void SetSeconds(int seconds) {
		seconds_ = seconds;
		ErrorWhenSecondsWrong_();
	}

	void SetMinutes(int minutes) {
		minutes_ = minutes;
		ErrorWhenMinutesWrong_();
	}

	void SetHours(int hours) {
		hours_ = hours;
		ErrorWhenHoursWrong_();
	}

	void SetDays(int days) {
		days_ = days;
		ErrorWhenDaysWrong_();
	}

	int GetSeconds()const {
		return seconds_;
	}

	int GetAllSecons()const {
		int result = days_ * 24 * 60 * 60;
		result += hours_ * 60 * 60;
		result += minutes_ * 60;
		result += seconds_;
		return result;
	}

	int GetMinutes()const {
		return minutes_;
	}
	int GetHours()const {
		return hours_;
	}
	int GetDays()const {
		return days_;
	}


	void AddSeconds(int seconds) {
		if ((seconds + seconds_) > 59) {
			AddMinutes((seconds + seconds_) / 60);
		}
		seconds_ = (seconds + seconds_) % 60;
	}

	void AddMinutes(int minutes) {
		if ((minutes + minutes_) > 59) {
			AddHours((minutes + minutes_) / 60);
		}
		minutes_ = (minutes + minutes_) % 60;
	}

	void AddHours(int hours) {
		if ((hours + hours_) > 23) {
			AddDays((hours + hours_) / 24);
		}
		hours_ = (hours + hours_) % 24;
	}


	void AddDays(int days) {
		days_ += days;
	}

	std::string GetData()const {
		return std::to_string(seconds_) + ':' +
			std::to_string(minutes_) + ':' +
			std::to_string(hours_) + ':' +
			std::to_string(days_);
	}

protected:
	void ErrorWhenSecondsWrong_() {
		if (seconds_ > 59 || seconds_ <0) {
			throw "seconds overload";
		}
	}

	void ErrorWhenMinutesWrong_() {
		if (minutes_ > 59 || minutes_ < 0) {
			throw "minutes overload";
		}
	}

	void ErrorWhenHoursWrong_(){
		if (hours_ > 23 || hours_ < 0) {
			throw "hours overload";
		}
	}

	void ErrorWhenDaysWrong_() {
		if (days_ < 0) {
			throw "days overload";
		}
	}

private:
	int seconds_;
	int minutes_;
	int hours_;
	int days_;
};





#endif // !TIME_HPP

