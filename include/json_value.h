#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <ostream>

namespace jsonparse{
    class JSonValue;

    using JSonNull = std::monostate;
    using JSonBoolean = bool;
    using JSonNumber = double;
    using JSonString = std::string;
    using JSonArray = std::vector<std::unique_ptr<JSonValue>>;
    using JSonObject = std::unordered_map<std::string, std::unique_ptr<

    class JSonValue {
    public:
        using ValueType = std::variant<JSonNull, JSonBoolean, JSonNumber, JSonString, JSonArray, JSonObject>;

        private:
        ValueType value;

       public:
        JSonValue();
        explicit JSonValue(JSonBoolean b);
        explicit JSonValue(JSonNumber n);
        explicit JSonValue(const JSonString& s);
        explicit JSonValue(const JSonArray& a);
        explicit JSonValue(const JSonObject& o);
        
        template<typename T>
        bool is() const{
            return std::holds_alternative<T>(value);
        }

        const JsonArray* getArray() const;
        const JsonObject* getObject() const;
        const JSonString* getString() const;
        const JSonNumber* getNumber() const;
        const JSonBoolean* getBool() const;
        bool isNull() const;
    }   

    
}
#endif // JSON_VALUE_H