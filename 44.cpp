//PREPEND BEGIN
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

class UID {
private:
    std::string id_value_;
    // (Chinese) 預設前綴，設為靜態常數
    // (English) Default prefix, set as a static constant
    static const char default_prefix_ = 'D'; 
    // (Chinese) 靜態計數器，用於確保ID唯一
    // (English) Static counter to ensure ID uniqueness
    static int counter_; 

public:
    // (Chinese) 建構子，允許指定前綴，預設使用 default_prefix_
    // (English) Constructor, allows specifying a prefix, uses default_prefix_ by default
    UID(char prefix = default_prefix_);

    // (Chinese) 獲取ID字串
    // (English) Gets the ID string
    std::string getIDString() const;

    // (Chinese) (可選) 重設計數器，方便測試
    // (English) (Optional) Resets the counter, useful for testing
    static void resetCounter(int start_value = 0);
};
int UID::counter_ = 0; // Start counter from 0 or 1 as you prefer

UID::UID(char prefix) {
    // TODO: 
    // 1. Increment the static counter_ BEFORE using it for the current ID,
    //    or use it then increment, depending on whether you want IDs to start from 000 or 001.
    //    Let's assume we increment then use, so IDs start from 1.
    // 2. Create a std::ostringstream to format the ID string.
    // 3. Append the prefix.
    // 4. Append a hyphen "-".
    // 5. Append the counter_ value, formatted to three digits with leading zeros
    //    (e.g., use std::setw(3) and std::setfill('0')).
    // 6. Store the resulting string in id_value_.

    counter_++; // Increment first, so IDs start from 1
    std::ostringstream oss;
    oss << prefix << "-" << std::setw(3) << std::setfill('0') << counter_;
    this->id_value_ = oss.str();
    std::cout << "UID created with ID: " << id_value_ << std::endl;
}

std::string UID::getIDString() const {
    // TODO: Return the id_value_
    return this->id_value_;
}

void UID::resetCounter(int start_value) {
    // TODO: Set the static counter_ to start_value.
    // Note: If IDs are generated like "D-001", "D-002", and you reset to 0,
    // the first ID after reset would be "D-001" (if counter is incremented before use).
    // If you reset to 1, the first ID would be "D-002". Adjust as needed.
    // For simplicity, if start_value is 0, next ID uses 1. If start_value is N, next ID uses N+1.
    // So, setting counter_ to start_value itself is fine if it's incremented before use.
    counter_ = start_value;
}
class Location {
private:
    std::string roomName_;
    std::string details_; // Optional details

public:
    // (Chinese) 建構子
    // (English) Constructor
    Location(const std::string& roomName, const std::string& details = "");

    // (Chinese) Getter 方法
    // (English) Getter methods
    std::string getRoomName() const;
    std::string getDetails() const;

    // (Chinese) (可選) 轉換為字串的方法
    // (English) (Optional) Method to convert to string
    std::string toString() const;

    // (Chinese) 友元函數，用於重載 << 運算子
    // (English) Friend function for overloading the << operator
    friend std::ostream& operator<<(std::ostream& os, const Location& loc);
};

Location::Location(const std::string& roomName, const std::string& details) {
    // TODO: Initialize roomName_ and details_ from the parameters.
    this->roomName_ = roomName;
    this->details_ = details;
}

std::string Location::getRoomName() const {
    // TODO: Return roomName_.
    return this->roomName_;
}

std::string Location::getDetails() const {
    // TODO: Return details_.
    return this->details_;
}

std::string Location::toString() const {
    // TODO: (Optional) Implement this method.
    // It should return a string representation like "RoomName (Details)" if details exist,
    // or just "RoomName" if details are empty.
    if (this->details_.empty()) {
        return this->roomName_;
    } else {
        return this->roomName_ + " (" + this->details_ + ")";
    }
}

// (Chinese) 實作重載的 << 運算子
// (English) Implementation of the overloaded << operator
std::ostream& operator<<(std::ostream& os, const Location& loc) {
    // TODO: Send a formatted string representation of 'loc' to the output stream 'os'.
    // You can use the logic from loc.toString() here if you've implemented it,
    // or implement the formatting directly.
    // Example:
    os << loc.roomName_;
    if (!loc.details_.empty()) {
        os << " (" << loc.details_ << ")";
    }
    return os; // Don't forget to return the stream!
}

class AbstractSmartDevice {
protected:
    UID id_;
    std::string name_;
    Location location_;
    bool is_on_; // Common state for on/off

public:
    // (Chinese) 建構子
    // (English) Constructor
    AbstractSmartDevice(const std::string& name, const Location& location, char uid_prefix = 'D');

    // (Chinese) 虛擬解構子 (預設或空實作)
    // (English) Virtual destructor (defaulted or empty implementation)
    virtual ~AbstractSmartDevice();// = default; 
    // Or: virtual ~AbstractSmartDevice() {}
    // Or: virtual ~AbstractSmartDevice(); // Then define in .cpp

    // (Chinese) Getter 方法
    // (English) Getter methods
    std::string getDeviceIDString() const;
    std::string getName() const;
    Location getLocation() const;
    bool isOn() const; // Concrete method to get the on/off state

    // (Chinese) 純虛擬函數 - 定義裝置介面
    // (English) Pure virtual functions - defining the device interface
    virtual std::string getDeviceInfo() const = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatusString() const = 0; // For device-specific status like brightness, temp, etc.

    // (Chinese) 禁止複製和賦值，因為每個智慧裝置應是唯一的 (透過ID)，且抽象類別通常不應被複製。
    // (English) Forbid copying and assignment, as each smart device should be unique (via ID),
    //           and abstract classes are generally not meant to be copied.
    AbstractSmartDevice(const AbstractSmartDevice&) = delete;
    AbstractSmartDevice& operator=(const AbstractSmartDevice&) = delete;

    // (Chinese) (可選) 允許移動，如果衍生類別需要且能正確實作
    // (English) (Optional) Allow moving if derived classes need it and can implement it correctly.
    // AbstractSmartDevice(AbstractSmartDevice&&) = default; 
    // AbstractSmartDevice& operator=(AbstractSmartDevice&&) = default;
    // For now, let's keep it simple and not explicitly define move operations unless needed.
};

// (Chinese) 建構子實作
// (English) Constructor Implementation
AbstractSmartDevice::AbstractSmartDevice(const std::string& name, const Location& location, char uid_prefix)
    : id_(uid_prefix), name_(name), location_(location), is_on_(false) { // Initialize id_ by calling UID's constructor
    // TODO: Initialize name_ with the provided name.
    // TODO: Initialize location_ with the provided location.
    // TODO: Initialize is_on_ to a default state (e.g., false).
    // The member initializer list above already does this. No further action needed here if so.
    std::cout << "AbstractSmartDevice for " << name_ << " created with ID " << id_.getIDString() << std::endl; // Optional debug
}

// (Chinese) 如果解構子在 .h 中沒有使用 =default 或 {}，則在這裡提供定義
// (English) If the destructor was not defaulted or defined inline in .h, provide its definition here
AbstractSmartDevice::~AbstractSmartDevice() {
    // std::cout << "Destructor AbstractSmartDevice for " << name_ << destroyed." << std::endl; // Optional debug
    std::cout << "Destructor AbstractSmartDevice for " << name_ << " (ID: " << id_.getIDString() << ")" << std::endl;
}

// (Chinese) Getter 方法實作
// (English) Getter method implementations
std::string AbstractSmartDevice::getDeviceIDString() const {
    // TODO: Return the string representation of the device's UID.
    return id_.getIDString();
}

std::string AbstractSmartDevice::getName() const {
    // TODO: Return the device's name.
    return name_;
}

Location AbstractSmartDevice::getLocation() const {
    // TODO: Return the device's location.
    return location_;
}

bool AbstractSmartDevice::isOn() const {
    // TODO: Return the current on/off state (is_on_).
    return is_on_;
}

// (Chinese) 注意：純虛擬函數沒有「實作」在基底類別中。
// (English) Note: Pure virtual functions do not have "implementations" in the base class.
//           They must be implemented by concrete derived classes.

class LightDevice : public AbstractSmartDevice {
private:
    int brightness_; // 0-100
    std::string color_;

public:
    LightDevice(const std::string& name, const Location& location, 
                int initial_brightness = 0, const std::string& initial_color = "White");
    virtual ~LightDevice() {
        std::cout << "Destructor: " << name_ << " (ID: " << id_.getIDString() << ") destroyed." << std::endl;
    }

    // Overridden methods from AbstractSmartDevice
    std::string getDeviceInfo() const override;
    void turnOn() override;
    void turnOff() override;
    std::string getStatusString() const override;

    // LightDevice specific methods
    void setBrightness(int brightness);
    int getBrightness() const;
    void setColor(const std::string& color);
    std::string getColor() const;
};

LightDevice::LightDevice(const std::string& name, const Location& location, 
                         int initial_brightness, const std::string& initial_color)
    : AbstractSmartDevice(name, location, 'L'), // Pass 'L' as UID prefix for Light
      brightness_(0), color_(initial_color) {
    // TODO: Initialize brightness_ ensuring it's within a valid range (e.g., 0-100).
    // TODO: If initial_brightness > 0, set this->is_on_ (protected member from base) to true.
    //       Otherwise, set this->is_on_ to false.
    //       Also, set brightness_ accordingly.
    if (initial_brightness > 0) {
        if (initial_brightness > 100) initial_brightness = 100;
        this->brightness_ = initial_brightness;
        this->is_on_ = true; // from AbstractSmartDevice
    } else {
        this->brightness_ = 0;
        this->is_on_ = false; // from AbstractSmartDevice
    }
    std::cout << "LightDevice " << getName() << " created." << std::endl;
}

std::string LightDevice::getDeviceInfo() const {
    // TODO: Return a string containing ID, name, location, type ("Light"), and specific info (color, brightness).
    // Example: "Device Info: Light - [Name] (ID: [ID]) at [Location Room]. Color: [Color], Brightness: [Brightness]%"
    std::ostringstream oss;
    oss << "Device Info: Light - " << getName() << " (ID: " << getDeviceIDString() << ") at "
        << getLocation().getRoomName() << ". Color: " << this->color_ 
        << ", Brightness: " << this->brightness_ << "%";
    return oss.str();
}

void LightDevice::turnOn() {
    // TODO: Set is_on_ to true.
    // If brightness_ was 0, maybe set it to a default value (e.g., 50).
    this->is_on_ = true;
    if (this->brightness_ == 0) {
        this->brightness_ = 50; // Default brightness when turned on from fully off
    }
    // std::cout << getName() << " turned ON." << std::endl;
}

void LightDevice::turnOff() {
    // TODO: Set is_on_ to false.
    // Optionally, set brightness_ to 0.
    this->is_on_ = false;
    // this->brightness_ = 0; // Set brightness to 0 when turned off
    // std::cout << getName() << " turned OFF." << std::endl;
}

std::string LightDevice::getStatusString() const {
    // TODO: Return a string describing current status, e.g., "ON, Brightness: 75%, Color: Warm Yellow" or "OFF"
    std::ostringstream oss;
    if (isOn()) { // Use the base class isOn() method
        oss << "ON, Brightness: " << this->brightness_ << "%, Color: " << this->color_;
    } else {
        oss << "OFF, Brightness: " << this->brightness_ << "%, Color: " << this->color_; // Show last settings even if off
        // or simply: oss << "OFF";
    }
    return oss.str();
}

void LightDevice::setBrightness(int brightness) {
    // TODO: Set brightness_, ensuring it's within range [0, 100].
    // If brightness becomes 0, is_on_ should probably be set to false.
    // If brightness becomes > 0 and device was off, is_on_ should be set to true.
    if (brightness < 0) this->brightness_ = 0;
    else if (brightness > 100) this->brightness_ = 100;
    else this->brightness_ = brightness;

    if (this->brightness_ == 0) {
        this->is_on_ = false;
    } else {
        this->is_on_ = true; // If brightness > 0, device must be on
    }
}

int LightDevice::getBrightness() const {
    // TODO: Return brightness_
    return this->brightness_;
}

void LightDevice::setColor(const std::string& color) {
    // TODO: Set color_
    this->color_ = color;
}

std::string LightDevice::getColor() const {
    // TODO: Return color_
    return this->color_;
}

class ThermostatDevice : public AbstractSmartDevice {
private:
    double current_temperature_celsius_;
    double target_temperature_celsius_;

public:
    ThermostatDevice(const std::string& name, const Location& location, 
                     double initial_target_temp = 22.0, double initial_current_temp = 20.0);

    virtual ~ThermostatDevice() {
        std::cout << "Destructor: " << name_ << " (ID: " << id_.getIDString() << ") destroyed." << std::endl;
    }

    // Overridden methods
    std::string getDeviceInfo() const override;
    void turnOn() override; // Starts/resumes regulation
    void turnOff() override; // Stops regulation
    std::string getStatusString() const override;

    // Thermostat specific methods
    void setTargetTemperature(double temp_celsius);
    double getTargetTemperature() const;
    double getCurrentTemperature() const;
    // void simulateTemperatureChange(); // Optional for more complex behavior later
};

ThermostatDevice::ThermostatDevice(const std::string& name, const Location& location, 
                                   double initial_target_temp, double initial_current_temp)
    : AbstractSmartDevice(name, location, 'T'), // 'T' for Thermostat
      current_temperature_celsius_(initial_current_temp), 
      target_temperature_celsius_(initial_target_temp) {
    // TODO: Initialize is_on_ (e.g., true by default, meaning it's regulating if powered)
    this->is_on_ = true; // Assume it's on and regulating by default
    std::cout << "ThermostatDevice " << getName() << " created." << std::endl;
}

std::string ThermostatDevice::getDeviceInfo() const {
    // TODO: Return ID, name, location, type ("Thermostat"), current temp, target temp.
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1); // For temperature display
    oss << "Device Info: Thermostat - " << getName() << " (ID: " << getDeviceIDString() << ") at "
        << getLocation().getRoomName() << ". Current Temp: " << this->current_temperature_celsius_
        << "C, Target Temp: " << this->target_temperature_celsius_ << "C";
    return oss.str();
}

void ThermostatDevice::turnOn() {
    // TODO: Set is_on_ to true (start/resume temperature regulation).
    this->is_on_ = true;
    // std::cout << getName() << " temperature regulation ON." << std::endl;
}

void ThermostatDevice::turnOff() {
    // TODO: Set is_on_ to false (stop temperature regulation).
    this->is_on_ = false;
    // std::cout << getName() << " temperature regulation OFF." << std::endl;
}

std::string ThermostatDevice::getStatusString() const {
    // TODO: Return status string, e.g., "ON, Current: 21.5C, Target: 22.0C" or "OFF"
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    if (isOn()) {
        oss << "ON, Current: " << this->current_temperature_celsius_ << "C, Target: " << this->target_temperature_celsius_ << "C";
    } else {
        oss << "OFF, Current: " << this->current_temperature_celsius_ << "C, Target: " << this->target_temperature_celsius_ << "C";
        // or simply: oss << "OFF";
    }
    return oss.str();
}

void ThermostatDevice::setTargetTemperature(double temp_celsius) {
    // TODO: Set target_temperature_celsius_. Add any validation if necessary.
    this->target_temperature_celsius_ = temp_celsius;
    // If device is on, it will start working towards this new target.
    // We could add a simple simulation: if (isOn()) current_temperature_celsius_ = target_temperature_celsius_ (instant)
    // or a more complex one over time. For now, just set target.
}

double ThermostatDevice::getTargetTemperature() const {
    // TODO: Return target_temperature_celsius_.
    return this->target_temperature_celsius_;
}

double ThermostatDevice::getCurrentTemperature() const {
    // TODO: Return current_temperature_celsius_.
    // In a real simulation, this might change over time based on target and environment.
    // For now, it's just a stored value, possibly updated by a setter or internal logic not yet defined.
    return this->current_temperature_celsius_;
}

class SecurityDevice : public AbstractSmartDevice {
private:
    bool is_armed_;
    bool alarm_triggered_;

public:
    SecurityDevice(const std::string& name, const Location& location);

    virtual ~SecurityDevice() {
        std::cout << "Destructor: " << name_ << " (ID: " << id_.getIDString() << ") destroyed." << std::endl;
    }

    // Overridden methods
    std::string getDeviceInfo() const override;
    void turnOn() override; // Powers on the device, may not arm it directly
    void turnOff() override; // Powers off the device
    std::string getStatusString() const override;

    // SecurityDevice specific methods
    void arm();
    void disarm();
    void triggerAlarm();
    void resetAlarm();
    bool isArmed() const;
    bool isAlarmTriggered() const;
};

SecurityDevice::SecurityDevice(const std::string& name, const Location& location)
    : AbstractSmartDevice(name, location, 'S'), // 'S' for Security
      is_armed_(false), alarm_triggered_(false) {
    // TODO: Initialize is_on_ (e.g., true, as security devices are often powered on for standby)
    this->is_on_ = true; // Assume security device is powered on by default (standby)
    std::cout << "SecurityDevice " << getName() << " created." << std::endl;
}
std::string SecurityDevice::getDeviceInfo() const {
    // TODO: Return ID, name, location, type ("Security"), armed status, alarm status.
    std::ostringstream oss;
    oss << "Device Info: Security - " << getName() << " (ID: " << getDeviceIDString() << ") at "
        << getLocation().getRoomName() << ". Armed: " << (this->is_armed_ ? "Yes" : "No")
        << ", Alarm Triggered: " << (this->alarm_triggered_ ? "Yes" : "No");
    return oss.str();
}

void SecurityDevice::turnOn() {
    // TODO: Set is_on_ to true. This might represent powering the device unit on.
    // Arming is a separate action.
    this->is_on_ = true;
    // std::cout << getName() << " powered ON." << std::endl;
}

void SecurityDevice::turnOff() {
    // TODO: Set is_on_ to false. This might also disarm the device and reset any alarm.
    this->is_on_ = false;
    this->is_armed_ = false;
    this->alarm_triggered_ = false;
    // std::cout << getName() << " powered OFF." << std::endl;
}

std::string SecurityDevice::getStatusString() const {
    // TODO: Return status string, e.g., "ON (Standby), Armed: No, Alarm: No" or "OFF"
    std::ostringstream oss;
    if (isOn()) { // Base class isOn()
        oss << "ON (Standby), Armed: " << (this->is_armed_ ? "Yes" : "No") 
            << ", Alarm Triggered: " << (this->alarm_triggered_ ? "Yes" : "No");
    } else {
        oss << "OFF";
    }
    return oss.str();
}

void SecurityDevice::arm() {
    // TODO: Set is_armed_ to true, but only if the device is on (is_on_ is true).
    if (this->is_on_) {
        this->is_armed_ = true;
        // std::cout << getName() << " ARMED." << std::endl;
    } else {
        // std::cout << getName() << " cannot arm, device is powered off." << std::endl;
    }
}

void SecurityDevice::disarm() {
    // TODO: Set is_armed_ to false.
    this->is_armed_ = false;
    // std::cout << getName() << " DISARMED." << std::endl;
}

void SecurityDevice::triggerAlarm() {
    // TODO: If is_on_ and is_armed_, set alarm_triggered_ to true.
    if (this->is_on_ && this->is_armed_) {
        this->alarm_triggered_ = true;
        // std::cout << "ALARM TRIGGERED for " << getName() << "!" << std::endl;
    } else {
        // std::cout << getName() << " cannot trigger alarm (not armed or off)." << std::endl;
    }
}

void SecurityDevice::resetAlarm() {
    // TODO: Set alarm_triggered_ to false.
    this->alarm_triggered_ = false;
    // std::cout << "Alarm for " << getName() << " RESET." << std::endl;
}

bool SecurityDevice::isArmed() const {
    // TODO: Return is_armed_
    return this->is_armed_;
}

bool SecurityDevice::isAlarmTriggered() const {
    // TODO: Return alarm_triggered_
    return this->alarm_triggered_;
}
//PREPEND END
//TEMPLATE BEGIN
class DeviceRegistry {
private:
    std::vector<AbstractSmartDevice*> devices_;

public:
    // (Chinese) 建構子
    // (English) Constructor
    DeviceRegistry();

    // (Chinese) 解構子 - 負責釋放所有儲存的裝置記憶體
    // (English) Destructor - responsible for freeing memory of all stored devices
    ~DeviceRegistry();

    // (Chinese) 禁用複製建構子和複製賦值運算子
    // (English) Disable copy constructor and copy assignment operator
    DeviceRegistry(const DeviceRegistry&) = delete;
    DeviceRegistry& operator=(const DeviceRegistry&) = delete;

    // (Chinese) 新增裝置 (註冊表取得指標所有權)
    // (English) Adds a device (registry takes ownership of the pointer)
    void addDevice(AbstractSmartDevice* device_ptr);

    // (Chinese) 依ID尋找裝置 (返回非擁有型裸指標)
    // (English) Finds a device by ID (returns a non-owning raw pointer)
    AbstractSmartDevice* findDeviceByID(const std::string& id_string) const;

    // (Chinese) 顯示所有裝置資訊
    // (English) Displays info for all devices
    void displayAllDevicesInfo() const;

    // (Chinese) (可選) 依ID移除並刪除裝置
    // (English) (Optional) Removes and deletes a device by ID
    bool removeDeviceByID(const std::string& id_string);
};
//TEMPLATE END
//APPEND BEGIN
int main() {
    UID::resetCounter(); // For predictable IDs in this test run

    std::cout << "--- Creating DeviceRegistry ---" << std::endl;
    DeviceRegistry registry;
    std::cout << std::endl;

    // --- Adding Devices ---
    std::cout << "--- Adding Devices to Registry ---" << std::endl;
    std::cout << "(Constructor messages for each device if you have them, e.g.:)" << std::endl;
    Location livingRoom("Living Room");
    Location kitchen("Kitchen");
    Location bedroom("Bedroom");

    // Dynamically allocate devices and add them to the registry
    // The registry now owns these pointers.
    registry.addDevice(new LightDevice("Living Room Light", livingRoom));
    registry.addDevice(new ThermostatDevice("Main Thermostat", livingRoom, 22.0, 21.0));
    registry.addDevice(new SecurityDevice("Kitchen Smoke Detector", kitchen));
    registry.addDevice(new LightDevice("Bedroom Lamp", bedroom, 30, "Soft White"));
    std::cout << "4 devices added." << std::endl << std::endl;

    // --- Display All Devices ---
    std::cout << "--- Displaying All Devices in Registry ---" << std::endl;
    registry.displayAllDevicesInfo();
    std::cout << std::endl;

    // --- Find Device ---
    std::cout << "--- Finding Devices ---" << std::endl;
    std::string idToFind = "L-001"; // Assuming LightDevice uses 'L' and is the first 'L' type
    AbstractSmartDevice* foundDevice = registry.findDeviceByID(idToFind);
    if (foundDevice) {
        std::cout << "Found device by ID " << idToFind << ":" << std::endl;
        std::cout << foundDevice->getDeviceInfo() << std::endl;
    } else {
        std::cout << "Device with ID " << idToFind << " not found." << std::endl;
    }

    idToFind = "X-999"; // Non-existent ID
    foundDevice = registry.findDeviceByID(idToFind);
    if (foundDevice) {
        std::cout << "Found device by ID " << idToFind << ":" << std::endl;
        std::cout << foundDevice->getDeviceInfo() << std::endl;
    } else {
        std::cout << "Device with ID " << idToFind << " not found." << std::endl;
    }
    std::cout << std::endl;
    
    // --- (Optional) Test Remove Device ---
    #ifdef TEST_REMOVE_DEVICE // Define this macro to enable this test block
    std::cout << "--- Testing Remove Device (Optional) ---" << std::endl;
    std::string idToRemove = "T-002"; // Assuming ThermostatDevice uses 'T' and is ID T-002
    std::cout << "Attempting to remove device with ID: " << idToRemove << std::endl;
    if (registry.removeDeviceByID(idToRemove)) {
        std::cout << "Device " << idToRemove << " removed successfully." << std::endl;
    } else {
        std::cout << "Failed to remove device " << idToRemove << " (or not found)." << std::endl;
    }
    std::cout << "\nRegistry after removal attempt:" << std::endl;
    registry.displayAllDevicesInfo();
    std::cout << std::endl;
    #endif


    std::cout << "--- End of main function ---" << std::endl;
    std::cout << "(Destructor messages appear here as 'registry' is destroyed, e.g.:)" << std::endl;
    // When 'registry' goes out of scope here, its destructor will be called,
    // which should delete all dynamically allocated SmartDevice objects it owns.
    // If device destructors print messages, you'll see them now.
    return 0;
}
//APPEND END