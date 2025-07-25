#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
// ============================================================================
// Assume these declarations exist elsewhere in your codebase:
//
//    class UID {
//    public:
//        UID(char prefix);
//        std::string getIDString() const;
//        static void resetCounter();
//    };
//
//    class Location {
//    public:
//        Location(const std::string& name);
//        Location(const std::string& name, const std::string& description);
//        std::string getName() const;
//        // …
//    };
//
    class AbstractSmartDevice {
//    protected:
//        UID           id_;
//        std::string   name_;
//        Location      location_;
//        bool          is_on_;
//
//    public:
//        AbstractSmartDevice(const std::string& name,
//                            const Location& location,
//                            char uid_prefix = 'D');
//        virtual ~AbstractSmartDevice() = default;
//
//        virtual std::string getDeviceInfo() const = 0;
//        virtual void        turnOn()             = 0;
//        virtual void        turnOff()            = 0;
//        virtual std::string getStatusString()    = 0;
//
//        bool isOn() const { return is_on_; }
//        // … possibly other getters/setters …
//    };
// ============================================================================


// ============================================================================
// 1) LightDevice
// ============================================================================
class LightDevice : public AbstractSmartDevice{
private:
    int         brightness_; // 0–100
    std::string color_;

public:
    // Constructor: calls base with prefix 'L'
    LightDevice(const std::string& name,
                const Location&      location,
                int                   initial_brightness = 0,
                const std::string&    initial_color      = "White")
        : AbstractSmartDevice(name, location, 'L'),
          brightness_(initial_brightness),
          color_(initial_color)
    {
        // Base constructor set is_on_ = false by default
        // brightness_ is already 0..100, color_ default "White" if none passed
    }

    // -------------------------------
    // Overridden methods from AbstractSmartDevice
    // -------------------------------
    std::string getDeviceInfo() const override {
        std::ostringstream oss;
        oss << "Device Info: Light - "
            << name_
            << " (ID: " << id_.getIDString() << ") "
            << "at " << location_.getRoomName() << ". "
            << "Color: " << color_ << ", "
            << "Brightness: " << brightness_ << "%";
        return oss.str();
    }

    void turnOn() override {
        is_on_ = true;
        // If brightness_ was already nonzero, keep it; otherwise keep at whatever it was
        // (In practice, sample code calls setBrightness right after turnOn.)
    }

    void turnOff() override {
        is_on_ = false;
        // According to sample output, turning off sets brightness back to 0
        brightness_ = 0;
        // color_ remains whatever it was last set to
    }

    std::string getStatusString() const override {
        std::ostringstream oss;
        if (is_on_) {
            oss << "ON, "
                << "Brightness: " << brightness_ << "%, "
                << "Color: " << color_;
        } else {
            oss << "OFF, "
                << "Brightness: " << brightness_ << "%, "
                << "Color: " << color_;
        }
        return oss.str();
    }

    // -------------------------------
    // LightDevice‐specific methods
    // -------------------------------
    void setBrightness(int brightness) {
        if (brightness < 0) brightness = 0;
        if (brightness > 100) brightness = 100;
        brightness_ = brightness;
    }

    int getBrightness() const {
        return brightness_;
    }

    void setColor(const std::string& color) {
        color_ = color;
    }

    std::string getColor() const {
        return color_;
    }
};


// ============================================================================
// 2) ThermostatDevice
// ============================================================================
class ThermostatDevice : public AbstractSmartDevice {
private:
    double current_temperature_celsius_;
    double target_temperature_celsius_;

public:
    // Constructor: prefix 'T'. By sample, new thermostats start in "ON" mode
    ThermostatDevice(const std::string& name,
                     const Location&      location,
                     double               initial_target_temp  = 22.0,
                     double               initial_current_temp = 20.0)
        : AbstractSmartDevice(name, location, 'T'),
          current_temperature_celsius_(initial_current_temp),
          target_temperature_celsius_(initial_target_temp)
    {
        // Thermostats come ON by default
        is_on_ = true;
    }

    // -------------------------------
    // Overridden methods from AbstractSmartDevice
    // -------------------------------
    std::string getDeviceInfo() const override {
        std::ostringstream oss;
        oss << "Device Info: Thermostat - "
            << name_
            << " (ID: " << id_.getIDString() << ") "
            << "at " << location_.getRoomName() << ". "
            << "Current Temp: "
            << std::fixed << std::setprecision(1)
            << current_temperature_celsius_ << "C"
            << ", Target Temp: "
            << std::fixed << std::setprecision(1)
            << target_temperature_celsius_ << "C";
        return oss.str();
    }

    void turnOn() override {
        // "Starts/resumes regulation"
        is_on_ = true;
    }

    void turnOff() override {
        // "Stops regulation"
        is_on_ = false;
    }

    std::string getStatusString() const override {
        std::ostringstream oss;
        if (is_on_) {
            oss << "ON, "
                << "Current: "
                << std::fixed << std::setprecision(1)
                << current_temperature_celsius_ << "C"
                << ", Target: "
                << std::fixed << std::setprecision(1)
                << target_temperature_celsius_ << "C";
        } else {
            oss << "OFF, "
                << "Current: "
                << std::fixed << std::setprecision(1)
                << current_temperature_celsius_ << "C"
                << ", Target: "
                << std::fixed << std::setprecision(1)
                << target_temperature_celsius_ << "C";
        }
        return oss.str();
    }

    // -------------------------------
    // ThermostatDevice‐specific methods
    // -------------------------------
    void setTargetTemperature(double temp_celsius) {
        target_temperature_celsius_ = temp_celsius;
    }

    double getTargetTemperature() const {
        return target_temperature_celsius_;
    }

    double getCurrentTemperature() const {
        return current_temperature_celsius_;
    }

    // (Optional) A method to simulate a change in current_temperature_celsius_
    // void simulateTemperatureChange() { … }
};


// ============================================================================
// 3) SecurityDevice
// ============================================================================
class SecurityDevice : public AbstractSmartDevice {
private:
    bool is_armed_;
    bool alarm_triggered_;

public:
    // Constructor: prefix 'S'. Start powered ON, disarmed, no alarm.
    SecurityDevice(const std::string& name, const Location& location)
        : AbstractSmartDevice(name, location, 'S'),
          is_armed_(false),
          alarm_triggered_(false)
    {
        is_on_ = true;
    }

    // -------------------------------
    // Overridden methods from AbstractSmartDevice
    // -------------------------------
    std::string getDeviceInfo() const override {
        std::ostringstream oss;
        oss << "Device Info: Security - "
            << name_
            << " (ID: " << id_.getIDString() << ") "
            << "at " << location_.getRoomName() << ". "
            << "Armed: "  << (is_armed_ ? "Yes" : "No")
            << ", Alarm: " << (alarm_triggered_ ? "Yes" : "No");
        return oss.str();
    }

    void turnOn() override {
        // Powers on the device (goes into Standby if not already armed)
        is_on_ = true;
        // Do not automatically arm—must call arm() explicitly
    }

    void turnOff() override {
        // Powers off the device
        is_on_ = false;
        // Per sample, we do NOT forcibly change armed/alarm here;
        // (In sample, they disarmed/reset before turning off.)
    }

    std::string getStatusString() const override {
        std::ostringstream oss;
        if (is_on_) {
            oss << "ON (Standby), "
                << "Armed: " << (is_armed_ ? "Yes" : "No")
                << ", Alarm Triggered: " << (alarm_triggered_ ? "Yes" : "No");
        } else {
            oss << "OFF, "
                << "Armed: " << (is_armed_ ? "Yes" : "No")
                << ", Alarm Triggered: " << (alarm_triggered_ ? "Yes" : "No");
        }
        return oss.str();
    }

    // -------------------------------
    // SecurityDevice‐specific methods
    // -------------------------------
    void arm() {
        if (is_on_) {
            is_armed_ = true;
        }
        // If the device is OFF, calling arm() does nothing.
    }

    void disarm() {
        is_armed_ = false;
    }

    void triggerAlarm() {
        // Only if powered on AND already armed
        if (is_on_ && is_armed_) {
            alarm_triggered_ = true;
        }
    }

    void resetAlarm() {
        alarm_triggered_ = false;
    }

    bool isArmed() const {
        return is_armed_;
    }
    bool isAlarmTriggered() const {
        return alarm_triggered_;
    }
};
