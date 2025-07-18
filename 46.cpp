//PREPEND BEGIN
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

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
    virtual ~AbstractSmartDevice() = default; 
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
    // std::cout << "AbstractSmartDevice for " << name_ << " created with ID " << id_.getIDString() << std::endl; // Optional debug
}

// (Chinese) 如果解構子在 .h 中沒有使用 =default 或 {}，則在這裡提供定義
// (English) If the destructor was not defaulted or defined inline in .h, provide its definition here
// AbstractSmartDevice::~AbstractSmartDevice() {
//     std::cout << "AbstractSmartDevice for " << name_ << " destroyed." << std::endl; // Optional debug
// }

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
    // std::cout << "LightDevice " << getName() << " created." << std::endl;
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
    // std::cout << "ThermostatDevice " << getName() << " created." << std::endl;
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
    // std::cout << "SecurityDevice " << getName() << " created." << std::endl;
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

DeviceRegistry::DeviceRegistry() {
    // TODO: Constructor can be empty if devices_ is default-initialized correctly (which it is).
    // You might add a print statement for debugging if you wish.
    // std::cout << "DeviceRegistry created." << std::endl;
}

DeviceRegistry::~DeviceRegistry() {
    // TODO: VERY IMPORTANT - Iterate through 'devices_' and delete each dynamically allocated AbstractSmartDevice.
    // After deleting all objects, clear the vector.
    // std::cout << "DeviceRegistry destroying " << devices_.size() << " devices..." << std::endl;
    for (AbstractSmartDevice* device_ptr : devices_) {
        // (Chinese) 在此處 delete device_ptr。如果 device_ptr 的解構子有輸出，你會看到。
        // (English) Delete device_ptr here. If device_ptr's destructor has output, you'll see it.
        delete device_ptr; 
    }
    devices_.clear(); // Clear the vector of now-dangling pointers.
    // std::cout << "DeviceRegistry destroyed. All devices freed." << std::endl;
}

void DeviceRegistry::addDevice(AbstractSmartDevice* device_ptr) {
    // TODO: Add the provided 'device_ptr' to the 'devices_' vector.
    // Assume device_ptr is a valid pointer to a dynamically allocated object.
    // The registry now "owns" this pointer and is responsible for deleting it.
    if (device_ptr != nullptr) {
        devices_.push_back(device_ptr);
    }
}

AbstractSmartDevice* DeviceRegistry::findDeviceByID(const std::string& id_string) const {
    // TODO: Iterate through the 'devices_' vector.
    // For each device, get its ID string (e.g., using device_ptr->getDeviceIDString()).
    // If it matches 'id_string', return the device_ptr.
    // If no device is found after checking all, return nullptr.
    for (AbstractSmartDevice* device_ptr : devices_) {
        if (device_ptr && device_ptr->getDeviceIDString() == id_string) {
            return device_ptr;
        }
    }
    return nullptr;
}

void DeviceRegistry::displayAllDevicesInfo() const {
    // TODO: Iterate through 'devices_'.
    // For each valid device_ptr, call its getDeviceInfo() method and print the result.
    // Add some formatting for readability.
    if (devices_.empty()) {
        std::cout << "Device Registry is empty." << std::endl;
        return;
    }
    // std::cout << "--- Devices in Registry ---" << std::endl; // Optional header
    for (const AbstractSmartDevice* device_ptr : devices_) {
        if (device_ptr) {
            std::cout << device_ptr->getDeviceInfo() << std::endl;
            // (Chinese) 如果想更詳細，可以也呼叫 getStatusString()
            // (English) If you want more details, you can also call getStatusString()
            // std::cout << "Status: " << device_ptr->getStatusString() << std::endl;
            std::cout << "-------------------------" << std::endl; // Separator
        }
    }
}

bool DeviceRegistry::removeDeviceByID(const std::string& id_string) {
    // TODO: (Optional) Implement this method.
    // 1. Find the iterator to the element in 'devices_' whose ID matches 'id_string'.
    //    (Hint: You might need a loop or std::find_if with a lambda).
    // 2. If found:
    //    a. Get the AbstractSmartDevice* from the iterator.
    //    b. Erase the element (pointer) from the 'devices_' vector using the iterator.
    //    c. IMPORTANT: delete the AbstractSmartDevice object that the pointer was pointing to.
    //    d. Return true.
    // 3. If not found, return false.
    for (auto it = devices_.begin(); it != devices_.end(); ++it) {
        if (*it && (*it)->getDeviceIDString() == id_string) {
            AbstractSmartDevice* device_to_delete = *it; // Get the pointer
            devices_.erase(it);                         // Remove pointer from vector
            delete device_to_delete;                    // Delete the object
            // std::cout << "Device with ID " << id_string << " removed and deleted." << std::endl;
            return true;
        }
    }
    // std::cout << "Device with ID " << id_string << " not found for removal." << std::endl;
    return false;
}

class Room {
private:
    UID uid_;
    std::string roomName_;
    std::vector<AbstractSmartDevice*> device_references_in_room_; // Non-owning pointers

public:
    // (Chinese) 建構子
    // (English) Constructor
    Room(const std::string& name, char uid_prefix = 'R');

    // (Chinese) Room 不擁有 device_references_in_room_ 中的指標所指向的物件，
    //           所以預設的解構子即可，不需要手動 delete 這些指標。
    // (English) Room does not own the objects pointed to by pointers in device_references_in_room_,
    //           so the default destructor is fine; no need to manually delete these pointers.
    ~Room() = default;

    // (Chinese) 預設的複製建構子和賦值運算子會複製指標，這對於非擁有型指標通常是可接受的，
    //           但需注意潛在的懸置指標問題，如果原始裝置被銷毀。
    // (English) Default copy constructor and assignment operator will copy pointers, which is
    //           generally acceptable for non-owning pointers, but be mindful of potential
    //           dangling pointer issues if the original devices are destroyed.
    Room(const Room&) = default;
    Room& operator=(const Room&) = default;
    // (Chinese) 移動建構子和移動賦值運算子也可以預設。
    // (English) Move constructor and move assignment can also be defaulted.
    Room(Room&&) = default;
    Room& operator=(Room&&) = default;


    std::string getRoomIDString() const;
    std::string getRoomName() const;
    int getDeviceCount() const;

    // (Chinese) 向房間新增一個裝置的引用 (不取得所有權)
    // (English) Adds a reference to a device to the room (does not take ownership)
    void addDeviceReference(AbstractSmartDevice* device_ptr);

    // (Chinese) 從房間移除一個裝置的引用 (不刪除裝置本身)
    // (English) Removes a device reference from the room (does not delete the device itself)
    bool removeDeviceReference(const std::string& device_id_string);

    // (Chinese) 顯示房間內所有裝置的資訊
    // (English) Displays information for all devices in the room
    void displayDevicesInRoom() const;

    // (Chinese) 關閉房間內所有燈光裝置
    // (English) Turns off all light devices in the room
    void turnOffAllLightsInRoom();
};

Room::Room(const std::string& name, char uid_prefix)
    : uid_(uid_prefix), roomName_(name) {
    // TODO: Initialize uid_ (done by member initializer list using UID's constructor)
    // TODO: Initialize roomName_ (done by member initializer list)
    // device_references_in_room_ is default-initialized as an empty vector.
    // std::cout << "Room '" << roomName_ << "' created with ID " << uid_.getIDString() << std::endl;
}

std::string Room::getRoomIDString() const {
    // TODO: Return the room's UID string.
    return uid_.getIDString();
}

std::string Room::getRoomName() const {
    // TODO: Return the room's name.
    return roomName_;
}

int Room::getDeviceCount() const {
    // TODO: Return the number of device references in the room.
    return static_cast<int>(device_references_in_room_.size());
}

void Room::addDeviceReference(AbstractSmartDevice* device_ptr) {
    // TODO: Add the non-owning device_ptr to the vector.
    // Perform a check to ensure device_ptr is not null before adding.
    // Optional: Check if the device (by ID) is already in the room to prevent duplicates.
    if (device_ptr) {
        // Optional duplicate check:
        // for (const auto* existing_dev : device_references_in_room_) {
        //     if (existing_dev && existing_dev->getDeviceIDString() == device_ptr->getDeviceIDString()) {
        //         std::cout << "Device " << device_ptr->getDeviceIDString() << " already in room " << roomName_ << std::endl;
        //         return;
        //     }
        // }
        device_references_in_room_.push_back(device_ptr);
    } else {
        // std::cerr << "Warning: Attempted to add a null device pointer to room " << roomName_ << std::endl;
    }
}

bool Room::removeDeviceReference(const std::string& device_id_string) {
    // TODO: Find and remove the device reference (pointer) with the matching device_id_string
    // from device_references_in_room_.
    // This method does NOT delete the device object itself.
    // Return true if found and removed, false otherwise.
    // (Hint: Use an iterator loop or std::remove_if with a lambda and vector's erase method)
    auto it = std::remove_if(device_references_in_room_.begin(), device_references_in_room_.end(),
        [&](AbstractSmartDevice* ptr) {
            return (ptr && ptr->getDeviceIDString() == device_id_string);
        });

    if (it != device_references_in_room_.end()) {
        device_references_in_room_.erase(it, device_references_in_room_.end());
        return true;
    }
    return false;
}

void Room::displayDevicesInRoom() const {
    // TODO: Iterate through device_references_in_room_.
    // For each valid (non-null) pointer, print the device's information
    // (e.g., using getDeviceInfo() or getStatusString()).
    // IMPORTANT: Be mindful that pointers in this vector might become dangling
    // if the actual device object is deleted from DeviceRegistry.
    // Robust code might check if a device is still "valid" if possible,
    // or this function relies on external logic to keep references valid.
    // For this stage, a simple iteration is fine, but highlight the risk.
    if (device_references_in_room_.empty()) {
        std::cout << "Room '" << roomName_ << "' has no devices." << std::endl;
        return;
    }
    std::cout << "Devices in Room '" << roomName_ << "' (ID: " << getRoomIDString() << "):" << std::endl;
    for (const AbstractSmartDevice* device_ptr : device_references_in_room_) {
        if (device_ptr) { // Basic check for null
            // Ideally, we'd also need a way to know if device_ptr is dangling.
            // For now, we assume if it's not null, we try to use it.
            std::cout << "  - " << device_ptr->getDeviceInfo() << " [Status: " << device_ptr->getStatusString() << "]" << std::endl;
        } else {
            std::cout << "  - <Null device reference>" << std::endl;
        }
    }
}

void Room::turnOffAllLightsInRoom() {
    // TODO: Iterate through device_references_in_room_.
    // For each device, use dynamic_cast to check if it's a LightDevice.
    // If it is, and the cast is successful (pointer is not null), call its turnOff() method.
    // std::cout << "Attempting to turn off all lights in room: " << roomName_ << std::endl;
    int lights_found = 0;
    for (AbstractSmartDevice* device_ptr : device_references_in_room_) {
        if (device_ptr) { // Check if pointer is not null
            LightDevice* light = dynamic_cast<LightDevice*>(device_ptr);
            if (light) { // If cast is successful, it's a LightDevice
                lights_found++;
                light->turnOff();
                // std::cout << "  Light " << light->getName() << " turned off." << std::endl;
            }
        }
    }
    if (lights_found == 0) {
        // std::cout << "  No light devices found in " << roomName_ << " to turn off." << std::endl;
    }
}

//PREPEND END

//TEMPLATE BEGIN
enum class UserAccessLevel {
    GUEST,
    RESIDENT,
    ADMIN,
    UNKNOWN // Default or unknown
};

class User {
private:
    UID userID_;
    std::string username_;
    UserAccessLevel accessLevel_;
    // Example of a resource that would make move semantics more obvious:
    // std::vector<std::string>* activityLog_; 

public:
    // (Chinese) 建構子
    // (English) Constructor
    User(const std::string& username, UserAccessLevel level);

    // (Chinese) 解構子
    // (English) Destructor
    ~User();

    // (Chinese) 複製建構子
    // (English) Copy Constructor
    User(const User& other);

    // (Chinese) 移動建構子
    // (English) Move Constructor
    User(User&& other) noexcept;

    // (Chinese) 複製賦值運算子
    // (English) Copy Assignment Operator
    User& operator=(const User& other);

    // (Chinese) 移動賦值運算子
    // (English) Move Assignment Operator
    User& operator=(User&& other) noexcept;

    // (Chinese) Getter 方法
    // (English) Getter methods
    std::string getUserIDString() const;
    std::string getUsername() const;
    UserAccessLevel getAccessLevel() const;
    std::string getAccessLevelString() const; // Helper to convert enum to string

    // (Chinese) 友元函數聲明
    // (English) Friend function declaration
    
};

//TEMPLATE END

//APPEND BEGIN
// Friend function implementation - MUST be defined
void displayUserPrivilegedReport(const User& user) {
    std::cout << "[Privileged Report for User]" << std::endl;
    // Let's assume userID_ and accessLevel_ are private in User class.
    // The friend declaration allows this function to access them.
    // To demonstrate, we'll try to access what getDeviceIDString() and getAccessLevelString() provide,
    // but also imagine we could access raw private members if they existed and were different.
    // For this example, we directly use getters as User's private members (userID_, accessLevel_)
    // are accessed via their respective getters in the public interface.
    // A better example of friend use would be if it needed to access something NOT exposed by public getters.
    // Let's simulate accessing a hypothetical private log count or internal status.
    // For now, we'll just re-display public info and state its 'privileged'.
    std::cout << "  User System ID (Privileged): " << user.getUserIDString() << std::endl;
    std::cout << "  Username (Privileged): " << user.getUsername() << std::endl;
    std::cout << "  Access Level Enum (Privileged): " << static_cast<int>(user.getAccessLevel()) << std::endl; 
    std::cout << "  Access Level (Privileged): " << user.getAccessLevelString() << std::endl;
    // If User had: private int login_attempts_ = 0;
    // std::cout << "  Login Attempts (Privileged): " << user.login_attempts_ << std::endl;
    std::cout << "------------------------------------" << std::endl;
}


int main() {
    UID::resetCounter(0); // Reset UID counter for predictable User IDs

    // --- Test Constructor and Getters ---
    std::cout << "--- Testing Constructor and Getters ---" << std::endl;
    User user1("AliceAdmin", UserAccessLevel::ADMIN);
    std::cout << "User 1 ID: " << user1.getUserIDString() << ", Name: " << user1.getUsername()
              << ", Level: " << user1.getAccessLevelString() << std::endl;

    User user2("BobResident", UserAccessLevel::RESIDENT);
    std::cout << "User 2 ID: " << user2.getUserIDString() << ", Name: " << user2.getUsername()
              << ", Level: " << user2.getAccessLevelString() << std::endl;
    std::cout << std::endl;

    // --- Test Copy Constructor ---
    std::cout << "--- Testing Copy Constructor ---" << std::endl;
    User user3 = user1; // Calls copy constructor
    std::cout << "User 1 (Original): " << user1.getUsername() << " (ID: " << user1.getUserIDString() << ")" << std::endl;
    std::cout << "User 3 (Copied from User 1): " << user3.getUsername() << " (ID: " << user3.getUserIDString() << ")" <<  std::endl;
    // If User had a mutable member or setter:
    // user1.setUsername("AliceAdmin_Modified"); 
    // std::cout << "User 1 (Modified): " << user1.getUsername() << std::endl;
    // std::cout << "User 3 (Should be unchanged): " << user3.getUsername() << std::endl;
    std::cout << "Are User 1 and User 3 the same object? " << (&user1 == &user3 ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // --- Test Copy Assignment Operator ---
    std::cout << "--- Testing Copy Assignment Operator ---" << std::endl;
    User user4("CharlieGuest", UserAccessLevel::GUEST);
    std::cout << "User 4 (Before assignment): " << user4.getUsername() << " (ID: " << user4.getUserIDString() << ")" << std::endl;
    user4 = user2; // Calls copy assignment operator
    std::cout << "User 2 (Source): " << user2.getUsername() << " (ID: " << user2.getUserIDString() << ")" << std::endl;
    std::cout << "User 4 (After assignment from User 2): " << user4.getUsername() << " (ID: " << user4.getUserIDString() << ")" << std::endl;
    std::cout << "Are User 2 and User 4 the same object? " << (&user2 == &user4 ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // --- Test Move Constructor ---
    std::cout << "--- Testing Move Constructor ---" << std::endl;
    User user5("DavidToMove", UserAccessLevel::RESIDENT);
    std::cout << "User 5 (Original before move): " << user5.getUsername() << " (ID: " << user5.getUserIDString() << ")" << std::endl;
    User user6 = std::move(user5); // Calls move constructor
    std::cout << "User 6 (Moved from User 5): " << user6.getUsername() << " (ID: " << user6.getUserIDString() << ")" << std::endl;
    std::cout << "User 5 (After move - username state is valid but unspecified, often empty for std::string): "
              << "'" << user5.getUsername() << "'" << " (ID: " << user5.getUserIDString() << ")" << std::endl;
    std::cout << std::endl;

    // --- Test Move Assignment Operator ---
    std::cout << "--- Testing Move Assignment Operator ---" << std::endl;
    User user7("EveToMoveAssign", UserAccessLevel::ADMIN);
    User user8("TargetForMoveAssign", UserAccessLevel::GUEST);
    std::cout << "User 7 (Original before move assign): " << user7.getUsername() << " (ID: " << user7.getUserIDString() << ")" << std::endl;
    std::cout << "User 8 (Target before move assign): " << user8.getUsername() << " (ID: " << user8.getUserIDString() << ")" << std::endl;
    user8 = std::move(user7); // Calls move assignment operator
    std::cout << "User 8 (Target after move assign from User 7): " << user8.getUsername() << " (ID: " << user8.getUserIDString() << ")" << std::endl;
    std::cout << "User 7 (After move assign - username state is valid but unspecified): "
              << "'" << user7.getUsername() << "'" << " (ID: " << user7.getUserIDString() << ")" << std::endl;
    std::cout << std::endl;

    // --- Test Friend Function ---
    std::cout << "--- Testing Friend Function ---" << std::endl;
    displayUserPrivilegedReport(user1);
    displayUserPrivilegedReport(user6);

    std::cout << "--- End of Main ---" << std::endl;
    // Destructors will be called for user1, user2, user3, user4, user5, user6, user7, user8
    return 0;
}
//APPEND END