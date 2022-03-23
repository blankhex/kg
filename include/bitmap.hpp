#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <vector>
#include <fstream>
#include <string>

namespace kg
{

class bitmap
{
public:

    bool load(const std::string& path)
    {
        std::fstream file(path, std::ios::binary | std::ios::in);
        if (!file.is_open())
            return false;
        
        file.seekg(0, std::ios::end);
        std::vector<std::uint8_t> content(file.tellg());
        file.seekg(0, std::ios::beg);

        file.read(reinterpret_cast<char*>(content.data()), content.size());
        file.close();

        if (content[0] != 'B' && content[1] != 'M')
            return false;
        
        bool no_alpha = true;

        if (content[28] == 24)
            no_alpha = true;
        else if (content[28] == 32)
            no_alpha = false;
        else
            return false;
        
        if (content[30] != 0)
            return false;

        _width = content[18] + (content[19] << 8);
        _height = content[22] + (content[23] << 8);
        size_t row_length = ((((no_alpha)?(3):(4)) * _width + 3) / 4) * 4;
        std::cout << row_length << std::endl;
        _data.clear();
        _data.reserve(_width * _height * 4);

        std::uint8_t* image = &content[content[10] + (content[11] << 8)];
        for (int y = 0; y < _height; y++)
        {
            std::uint8_t* row = image + y * row_length;
            for (int x = 0; x < _width; x++)
            {
                if (no_alpha)
                {
                    // rgb
                    // bgr
                    _data.push_back(row[x * 3 + 2]);
                    _data.push_back(row[x * 3 + 1]);
                    _data.push_back(row[x * 3]);
                    _data.push_back(255);
                }
                else
                {
                    _data.push_back(row[x * 4 + 2]);
                    _data.push_back(row[x * 4 + 1]);
                    _data.push_back(row[x * 4]);
                    _data.push_back(row[x * 4 + 3]);
                }
            }
        }

        return true;
    }

    const int width() const { return _width; }
    const int height() const { return _height; }
    
    const std::vector<std::uint8_t>& data() const { return _data; }
    std::vector<std::uint8_t>& data() { return _data; }

private:
    int _width;
    int _height;
    std::vector<std::uint8_t> _data;
};

}

#endif // BITMAP_HPP