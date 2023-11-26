#include <iostream>
#include <string>
using namespace std;

class ToCopy {
public:
    static char* copyString(const char* source) {
        if (source == nullptr) {
            return nullptr;
        }
        char* value = new char[strlen(source) + 1];
        strcpy_s(value, strlen(source) + 1, source);
        return value;
    }
};


class Location {
private:
    int maxSeats = 0;
    int numRows = 0;
    int numberOfZones = 0;
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
    string getName() const {
		return this->name;
	}

    void setMaxSeats(int newMaxSeats) {
        if (newMaxSeats < 0) {
            throw exception("Incorrect number of seats");
        }
        this->maxSeats = newMaxSeats;
    }
    int getMaxSeats() {
        return this->maxSeats;
    }

    void setNumRows(int newNumRows) {
        if (newNumRows < 0) {
            throw exception("Incorrect number of rows");
        }
        this->numRows = newNumRows;
    }
    int getNumRows() const {
		return this->numRows;
	}

    void setNumberOfZones(int newNumberOfZones) {
        if (newNumberOfZones < 0) {
            throw exception("Incorrect number of zones");
        }
        this->numberOfZones = newNumberOfZones;
    }
    int getNumberOfZones() const {
        return this->numberOfZones;

    }

    void setZones(string* newZones, int numberOfZones) {
        this->zones = new string[numberOfZones];
        for (int i = 0; i < numberOfZones; i++) {
            this->zones[i] = newZones[i];
        }
        this->numberOfZones = numberOfZones;
    }
    string* getZones()
    {
        string* copy = new string[this->numberOfZones];
        for (int i = 0; i < this->numberOfZones; i++) {
			copy[i] = this->zones[i];
		}
        return copy;
    }

    Location(string name, int maxSeats, int numRows, string* zones, int numberOfZones) {
        this->setName(name);
        this->setMaxSeats(maxSeats);
        this->setNumRows(numRows);
        this->setZones(zones, numberOfZones);
    }
    Location(string name, int maxSeats, int numRows, int numberOfZones) {
		this->setName(name);
		this->setMaxSeats(maxSeats);
		this->setNumRows(numRows);
		this->setNumberOfZones(numberOfZones);
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
    friend istream& operator>>(istream& input, Location& l) {
		input >> l.name;
		input >> l.maxSeats;
		input >> l.numRows;
		input >> l.numberOfZones;

		l.zones = new string[l.numberOfZones];
        for (int i = 0; i < l.numberOfZones; i++) {
			input >> l.zones[i];
		}

		return input;
	}
    friend ostream& operator<<(ostream& output, const Location& l) {
        output << "Name: " << l.name << endl;
        output << "Max seats: " << l.maxSeats << endl;
        output << "Number of rows: " << l.numRows << endl;
        output << "Number of zones: " << l.numberOfZones << endl;
        output << "Zones: ";
        for (int i = 0; i < l.numberOfZones; i++) {
			output << l.zones[i] << " ";
		}
        output << endl;

		return output;
	}
    void DisplayLocationInfo() const {
		cout << "Name: " << name << endl;
		cout << "Max seats: " << maxSeats << endl;
		cout << "Number of rows: " << numRows << endl;
		cout << "Number of zones: " << numberOfZones << endl;
		cout << "Zones: ";
        for (int i = 0; i < numberOfZones; i++) {
			cout << zones[i] << " ";
		}
		cout << endl;
	}

    ~Location() {
        delete[] this->zones;
    }
    bool operator ==(Location l)
    {
        if (this->name == l.name && this->maxSeats == l.maxSeats)
        {
            return true;
        }
        else
        {
            return false;
        }
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
        string getEventName() const {
            return this->EventName;

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
        char* getDate()
        {
            char* copy= ToCopy::copyString(this->date);
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
        char* getTime()
        {
			char* copy = ToCopy::copyString(this->time);
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
        int* getParticipants()
        {
			int* copy = new int[NoOfParticipants];
            for (int i = 0; i < NoOfParticipants; i++) {
				copy[i] = participants[i];
            }
            return copy;
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
    bool operator ==(EventDetails e)
	{
        if (this->EventName == e.EventName && this->NoOfParticipants == e.NoOfParticipants)
        {
			return true;
		}
        else
        {
			return false;
		}
	}
    bool operator !=(EventDetails e)
	{
        if (this->EventName != e.EventName && this->NoOfParticipants != e.NoOfParticipants)
        {
			return true;
		}
        else
        {
			return false;
		}
	}
};

enum class Type { REGULAR, VIP, STUDENT, CHILDREN };
class Ticket
{
private:
    int id = 0;
    Type type = Type::REGULAR;
    int price = 0;
    int row = 0;
    int seat = 0;
    string* ownerName = nullptr;
    bool isBooked = false;
    public:
        static int const MIN_SIZE_FOR_OWNER_NAME = 3;
        static string typeToString(Type type) {
            switch (type) {
			case Type::REGULAR:
				return "Regular ticket";
			case Type::VIP:
				return "VIP ticket";
			case Type::STUDENT:
				return "Student ticket";
			case Type::CHILDREN:
				return "Children ticket";
			default:
				throw exception ("Unknown");
			}
		}
		void setId(int newId) {
            if (newId < 0) {
				throw exception("Incorrect id");
			}
			this->id = newId;
		}
        int getId() {
            return this->id;
        }

		void setType(Type newType) {
			this->type = newType;
		}
        Type getType() {
			return this->type;
		}
		void setPrice(int newPrice) {
            if (newPrice < 0) {
				throw exception("Incorrect price");
			}
			this->price = newPrice;
		}
        int getPrice() {
			return this->price;
		}
		void setRow(int newRow) {
            if (newRow < 0) {
				throw exception("Incorrect row");
			}
			this->row = newRow;
		}
        int getRow() {
            return this->row;
        }
		void setSeat(int newSeat) {
            if (newSeat < 0) {
				throw exception("Incorrect seat");
			}
			this->seat = newSeat;
		}
        int getSeat()  {
			return this->seat;
		}
		void setOwnerName(string* newOwnerName) {
            if (newOwnerName->size() < MIN_SIZE_FOR_OWNER_NAME)
            {
                throw exception("Short name for owner name");
            }
			this->ownerName = new string(*newOwnerName);
		}
        string* getOwnerName()  {
			return this->ownerName;
		}
		void setIsBooked(bool newIsBooked) {
			this->isBooked = newIsBooked;
		}
        bool getIsBooked()  {
            return this->isBooked;
        }
        Ticket()
        {
            this->setId(0);
			this->setType(Type::REGULAR);
			this->setPrice(0);
			this->setRow(0);
			this->setSeat(0);
			this->setOwnerName(new string(""));
			this->setIsBooked(false);
		}
     
		Ticket(int id, Type type, int price, int row, int seat, string* ownerName, bool isBooked) {
			this->setId(id);
			this->setType(type);
			this->setPrice(price);
			this->setRow(row);
			this->setSeat(seat);
			this->setOwnerName(ownerName);
			this->setIsBooked(isBooked);
		}
		Ticket(const Ticket& source) {
			this->id = source.id;
			this->type = source.type;
			this->price = source.price;
			this->row = source.row;
			this->seat = source.seat;
			this->ownerName = new string(*source.ownerName);
			this->isBooked = source.isBooked;
		}
		Ticket& operator=(const Ticket& source) {
            if (this != &source) {
				this->id = source.id;
				this->type = source.type;
				this->price = source.price;
				this->row = source.row;
				this->seat = source.seat;
				delete this->ownerName;
				this->ownerName = new string(*source.ownerName);
				this->isBooked = source.isBooked;
			}
			return *this;
		}
		~Ticket() {
			delete ownerName;
		}
		void displayInfoTicket() const {
			cout << "Id: " << id << endl;
			cout << "Type: " << typeToString(type) << endl;
			cout << "Price: " << price << endl;
			cout << "Row: " << row << endl;
			cout << "Seat: " << seat << endl;
			cout << "Owner name: " << *ownerName << endl;
			cout << "Is booked: " << isBooked << endl;
		}
        friend istream& operator>>(istream& input, Ticket& t) {
			input >> t.id;
			int type;
			input >> type;
			t.type = static_cast<Type>(type);
			input >> t.price;
			input >> t.row;
			input >> t.seat;
			string ownerName;
			input >> ownerName;
			t.ownerName = new string(ownerName);
			input >> t.isBooked;

			return input;
		}
        friend ostream& operator<<(ostream& output, const Ticket& t) {
			output << "Id: " << t.id << endl;
			output << "Type: " << typeToString(t.type) << endl;
			output << "Price: " << t.price << endl;
			output << "Row: " << t.row << endl;
			output << "Seat: " << t.seat << endl;
			output << "Owner name: " << *t.ownerName << endl;
			output << "Is booked: " << t.isBooked << endl;

			return output;
		}
        bool operator ==(Ticket t)
        {
            if (this->id == t.id && this->price == t.price)
            {
				return true;
			}
            else
            {
                return false;
            }
		}
        bool operator !=(Ticket t)
        {
            if (this->id != t.id && this->price != t.price)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        bool operator >=(Ticket t)
		{
            if (this->id >= t.id && this->price >= t.price)
            {
				return true;
			}
            else
            {
				return false;
			}
		}
        int operator[](int index) const {
            switch (index) {
            case 0:
                return id;
            case 1:
                return price;
                
            default:
                throw exception("Invalid ticket attribute");
            }
        }
};
