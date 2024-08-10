#include "Json.h"
#include "EFile.h"
#include <rapidjson/istreamwrapper.h>
#include <iostream>

namespace Json
{
    // Loads entire json file as document
    bool Load(const std::string & filename, rapidjson::Document& document)
    {
        std::string buffer;
        if (!File::ReadFile(filename, buffer))
        {
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        document.ParseStream(istream);
        if (!document.IsObject())
        {
            std::cerr << "Could not parse json: " << filename << std::endl;
            return false;
        }

        return true;
    }
    // Reading Int
    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could not read json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }
    // Reading Bool
    bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            std::cerr << "Could not read json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }
    // Reading String
    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            std::cerr << "Could not read json value: " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }
    // Reading Vector2 using array
    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
    // Reading Color using array
    bool Read(const rapidjson::Value& value, const std::string& name, Color& data)
    {

        // check if the value has the "<name>" and is an array with 4 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read json value : " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }
        return true;
    }
}