
#include "utils.h"


enum Log_Level{
    DEBUG = -1,
    INFO = 0,
    WARN = 1,
    ERROR = 2
};

class Logger{
    public:
        ~Logger();
        Logger(std::string filename);

        void close();
        int32_t log( std::string out , Log_Level iLogLevel = INFO);
        
    private:
        std::ofstream m_fout;
        std::map<int32_t, std::string> m_log_level_map;

};