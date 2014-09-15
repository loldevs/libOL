#include "Value.h"

#include <sstream>
#include <cassert>

Value Value::create(Object& val) {
    Value value;
    value.type = OBJECT;
    value.value = new Object(val);
    return value;
}

Value Value::create(Array& val) {
    Value value;
    value.type = ARRAY;
    value.value = new Array(val);
    return value;
}

Value Value::create(float& val) {
    Value value;
    value.type = FLOAT;
    value.value = new float(val);
    return value;
}

Value Value::create(bool& val) {
    Value value;
    value.type = BOOL;
    value.value = new bool(val);
    return value;
}

Value Value::create(uint64_t& val) {
    assert(!(val & ((uint64_t) 1 << 61))); // assert that the msb is not set
    return create((int64_t&) val);
}

Value Value::create(uint32_t& val) {
    if(val >= 2147483648) {
        int64_t large = (int64_t) val;
        return create(large);
    }
    return create((int32_t&) val);
}

Value Value::create(uint16_t& val) {
    int32_t intval = (int32_t) val;
    return create(intval);
}

Value Value::create(uint8_t& val) {
    int32_t intval = (int32_t) val;
    return create(intval);
}

Value Value::create(int64_t& val) {
    Value value;
    value.type = LARGE_INTEGER;
    value.value = new int64_t(val);
    return value;
}

Value Value::create(int32_t& val) {
    Value value;
    value.type = INTEGER;
    value.value = new int32_t(val);
    return value;
}

Value Value::create(int16_t& val) {
    int32_t intval = (int32_t)val;
    return create(intval);
}

Value Value::create(int8_t& val) {
    int32_t intval = (int32_t) val;
    return create(intval);
}

Value Value::create(std::string& val) {
    Value value;
    value.type = STRING;
    value.value = new std::string(val);
    return value;
}

Value Value::create(const char*& val) {
    std::string str = std::string(val);
    return create(str);
}

std::string Value::toString() {
    std::stringstream result;
    switch(type) {
        case OBJECT: {
            Object& obj = this->as<Object>();
            result << "{" << std::endl;
            for(auto it = obj.begin(); it != obj.end();) {
                result << "\"" << it->first << "\": ";
                result << it->second.toString();
                if(++it != obj.end())
                    result << ",";
                result << std::endl;
            }
            result << "}" << std::endl;
            break;
        }
        case ARRAY: {
            Array &arr = this->as<Array>();
            result << "[";
            for(size_t i = 0; i < arr.size(); i++) {
                result << arr.at(i).toString();
                if (i + 1 < arr.size())
                    result << ",";
            }
            result << "]";
            break;
        }
        case STRING:
            result << "\"" << this->as<std::string>() << "\"";
            break;
        case INTEGER:
            result << this->as<int32_t>();
            break;
        case LARGE_INTEGER:
            result << this->as<int64_t>();
            break;
        case FLOAT:
            result << this->as<float>();
            break;
        case BOOL:
            result << (this->as<bool>() ? "true" : "false");
            break;
        default:
            result << "undefined";
            break;
        case UNDEFINED:break;
    }
    return result.str();
}

void Object::set(std::string name, Value value) {
    map.insert(std::pair<std::string, Value> {name, value});
}

Value Object::get(std::string name) {
    return map.at(name);
}

size_t Object::size() {
    return map.size();
}

void Array::push(Value value) {
    vector.push_back(value);
}

size_t Array::size() {
    return vector.size();
}

Value Array::at(size_t index) {
    return vector.at(index);
}