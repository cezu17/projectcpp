#include <iostream>
#include <string>
using namespace std;

class Location {
private:
    int maxSeats = 0;
    int numRows = 0;
    int numberOfZones = 0;  // Updated name to avoid conflict
    string* zones = nullptr;
    string name = "";

public:
    static const int MIN_SIZE_FOR_NAME = 3;

    void setName(string newName) {
        if (newName.size() < Location::MIN_SIZE_FOR_NAME) {
            throw exception("Short name for location");
        }
        if (newName[0] < 'A' || newName[0] > 'Z') {
            throw exception("First letter of location is not a capital letter");
        }

        this->name = newName;
    }

    void setMaxSeats(int newMaxSeats) {
        if (newMaxSeats < 0) {
            throw exception("Incorrect number of seats");
        }
        this->maxSeats = newMaxSeats;
    }

    void setNumRows(int newNumRows) {
        if (newNumRows < 0) {
            throw exception("Incorrect number of rows");
        }
        this->numRows = newNumRows;
    }

    void setNumberOfZones(int newNumberOfZones) {
        if (newNumberOfZones < 0) {
            throw exception("Incorrect number of zones");
        }
        this->numberOfZones = newNumberOfZones;
    }

    void setZones(string* newZones, int numberOfZones) {
        this->zones = new string[numberOfZones];
        for (int i = 0; i < numberOfZones; i++) {
            this->zones[i] = newZones[i];
        }
        this->numberOfZones = numberOfZones;
    }

    Location(string name, int maxSeats, int numRows, string* zones, int numberOfZones) {
        this->setName(name);
        this->setMaxSeats(maxSeats);
        this->setNumRows(numRows);
        this->setZones(zones, numberOfZones);
    }

    Location(const Location& source) {
        this->setName(source.name);
        this->setMaxSeats(source.maxSeats);
        this->setNumRows(source.numRows);

        this->zones = new string[source.numberOfZones];
        for (int i = 0; i < source.numberOfZones; i++) {
            this->zones[i] = source.zones[i];
        }
        this->numberOfZones = source.numberOfZones;
    }

    Location& operator=(const Location& source) {
        if (this != &source) {
            this->setName(source.name);
            this->setMaxSeats(source.maxSeats);
            this->setNumRows(source.numRows);

            delete[] this->zones;  
            this->zones = new string[source.numberOfZones];
            for (int i = 0; i < source.numberOfZones; i++) {
                this->zones[i] = source.zones[i];
            }
            this->numberOfZones = source.numberOfZones;
        }
        return *this;
    }

    ~Location() {
        delete[] this->zones;
    }
};

	class EventDetails
	{
		string EventName = "";
		int* participants = nullptr;
        int NoOfParticipants = 0;
        char date[11] = "";
        char time[6] = "";
    public:
        static const int MIN_PARTICIPANTS = 1;
        static const int MIN_NAME_EVENT = 5;

        void setEventName(string newEventName) {
            if (newEventName.size() <MIN_NAME_EVENT) {
				throw exception("Short name for event name");
			}
            if (newEventName[0] < 'A' || newEventName[0] > 'Z') {
				throw exception("First letter of event name is not a capital letter");
			}
			this->EventName = newEventName;
		}
        void setDate(const char* newDate) {
            if (strlen(newDate) != 10) {
                throw exception("Wrong date");
            }
            if (newDate[2] != '/' || newDate[5] != '/') {
                throw exception("Wrong date format");
            }

            strcpy_s(this->date, newDate);
        }
        void setTime(const char* newTime) {
            if (strlen(newTime) != 6) {
				throw exception("Wrong time");
			}
            if (newTime[2] != ':') {
				throw exception("Wrong time format");
			}

			strcpy_s(this->time, newTime);
		}
        void setParticipants(int* newParticipants, int newNoOfParticipants) {
            if (newNoOfParticipants < MIN_PARTICIPANTS) {
                throw exception("Number of participants is less than minimum allowed");
            }
            this->participants = new int[newNoOfParticipants];
            for (int i = 0; i < newNoOfParticipants; i++) {
                this->participants[i] = newParticipants[i];
            }
            this->NoOfParticipants = newNoOfParticipants;
        }
        EventDetails(string eventName, int* participants, int noOfParticipants, const char* date, const char* time) {
            this->setEventName(eventName);
            this->setParticipants(participants, noOfParticipants);
            this->setDate(date);
            this->setTime(time);
        }

        EventDetails(string eventName, int noOfParticipants, const char* date, const char* time) {
            this->setEventName(eventName);
            this->NoOfParticipants = noOfParticipants;
            this->setDate(date);
            this->setTime(time);
        }
        EventDetails(const EventDetails& source) {
            this->EventName = source.EventName;
            this->NoOfParticipants = source.NoOfParticipants;
            strcpy_s(this->date, sizeof(this->date), source.date);
            strcpy_s(this->time, sizeof(this->time), source.time);

            if (source.participants != nullptr) {
                this->participants = new int[source.NoOfParticipants];
                for (int i = 0; i < source.NoOfParticipants; i++) {
                    this->participants[i] = source.participants[i];
                }
            }
        }
        EventDetails& operator=(const EventDetails& source) {
            if (this != &source) {
                delete[] participants;

                this->EventName = source.EventName;
                this->NoOfParticipants = source.NoOfParticipants;
                strcpy_s(this->date, sizeof(this->date), source.date);
                strcpy_s(this->time, sizeof(this->time), source.time);

                if (source.participants != nullptr) {
                    this->participants = new int[source.NoOfParticipants];
                    for (int i = 0; i < source.NoOfParticipants; i++) {
                        this->participants[i] = source.participants[i];
                    }
                }
            }
            return *this;
        }
        ~EventDetails() {
			delete[] participants;
		}
        void displayInfoEvent() const {
            cout << "Event Name: " << EventName << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "Number of Participants: " << NoOfParticipants << endl;
            if (participants != nullptr) {
                cout << "Participants: ";
                for (int i = 0; i < NoOfParticipants; i++) {
                    cout << participants[i] << " ";
                }
                cout << endl;
            }
        }
        friend istream& operator>>(istream& input, EventDetails& e) {
            input >> e.EventName;
            input >> e.NoOfParticipants;
            input >> e.date;
            input >> e.time;

            e.participants = new int[e.NoOfParticipants];
            for (int i = 0; i < e.NoOfParticipants; i++) {
                input >> e.participants[i];
            }

            return input;
        }

        friend ostream& operator<<(ostream& output, const EventDetails& e) {
            output << "Event Name: " << e.EventName << endl;
            output << "Date: " << e.date << endl;
            output << "Time: " << e.time << endl;
            output << "Number of Participants: " << e.NoOfParticipants << endl;
            if (e.participants != nullptr) {
                output << "Participants: ";
                for (int i = 0; i < e.NoOfParticipants; i++) {
                    output << e.participants[i] << " ";
                }
                output << endl;
            }

            return output;
        }
	}
};
int main()
{
	std::cout << "Hello World!" << std::endl;
}