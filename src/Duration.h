#pragma once
class Duration
{
public:
	enum EDuration {
		QUARTER = 4,
		EIGHT = 8
	};
	Duration();
	Duration(EDuration dur) {
		duration = dur;
	};
	EDuration getDuration() {
		return duration;
	}
	int changeDuration(EDuration newDuration) {
		duration = newDuration;
	}
	~Duration();
private:
	EDuration duration;
};

